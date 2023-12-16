#include <string.h>
#include "quantum.h"
#include "qp.h"
#include "qp_lvgl.h"
#include "lvgl.h"
#include <hal_pal.h>
#include "raw_hid.h"


// Surfaces
painter_device_t display;
static painter_device_t cover_surface;
static uint16_t  cover_buffer[100 * 100];
static uint8_t cbuf[LV_CANVAS_BUF_SIZE_TRUE_COLOR(100, 100)];


// Album Art
painter_image_handle_t loaded_image;
uint8_t raw_image_buffer[12000];

// Track Title
char track_title[1024] = {0};
bool track_set = false;

// LVGL Objects
lv_obj_t * layer_label;
lv_obj_t * track_label;
lv_obj_t * track_progress;
lv_obj_t * img;
lv_obj_t * canvas;
lv_draw_img_dsc_t dsc;

lv_img_dsc_t loaded_image_dsc = {
    .header.always_zero = 0,
    .header.w = 100,
    .header.h = 100,
    .data_size = 100 * 100 * 16 / 8,
    .header.cf = LV_IMG_CF_TRUE_COLOR,
    .data = (uint8_t *)cover_buffer
};

typedef struct {
    double h;
    double s;
    double v;
} hsv;

enum pages {
    MAIN    = 0x00,
    MUSIC   = 0x01,
    PANDORA = 0x02,
}

enum hid_codes {
    UPDT_LAYER = 0x00, // LAYER UPDATE
    UPDT_PAGE  = 0x01, // UPDATE DISPLAY PAGE
    UPDT_TITLE = 0x02, // UPDATE SONG TITLE - Page 0
    UPDT_IMAGE = 0x03, // UPDATE IMAGE      - Page 0
};


void display_init(void) {
    lv_obj_t * disp = lv_scr_act();
    lv_obj_set_scrollbar_mode(disp, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_bg_color(disp, lv_color_make(0, 0, 0), LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(disp, lv_color_make(255, 255, 255), LV_STATE_DEFAULT);

    layer_label = lv_label_create(disp);
    lv_obj_set_width(layer_label, 128);
    lv_obj_align(layer_label, LV_ALIGN_TOP_LEFT, 2, 2);

    extern const char *current_layer_string(void);
    const char        *layer_name = current_layer_string();
    char buf[64] = {0};
    snprintf(buf, sizeof(buf), "layer: %s", layer_name);
    lv_label_set_text(layer_label, buf);

    track_label = lv_label_create(disp);
    lv_label_set_long_mode(track_label, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_obj_set_width(track_label, 128);
    lv_label_set_text(track_label, "Connecting to Lobster Control...");
    lv_obj_align_to(track_label, layer_label, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 5);

    track_progress = lv_bar_create(disp);
    lv_obj_set_size(track_progress, 126, 10);
    lv_obj_align_to(track_progress, track_label, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 4);
    lv_bar_set_value(track_progress, 1, LV_ANIM_OFF);

    canvas = lv_canvas_create(lv_scr_act());
    lv_canvas_set_buffer(canvas, cbuf, 100, 100, LV_IMG_CF_TRUE_COLOR_CHROMA_KEYED);

    lv_obj_align(canvas, LV_ALIGN_BOTTOM_MID, 0, 0);
    lv_draw_img_dsc_init(&dsc);
}


void keyboard_post_init_kb(void) {
    setPinOutput(GP15); // Backlight Pin
    writePinHigh(GP15);

    // Below pins are CS, DC, RST
    display = qp_st7735_make_spi_device(128, 161, GP21, GP13, GP12, 4, 3);
    qp_init(display, QP_ROTATION_0);

    extern const hsv current_layer_colour(void);
    const hsv  lc = current_layer_colour();
    qp_rect(display, 0, 0, 129, 160, lc.h, lc.s, lc.v, true);

    // Init cover surface too
    cover_surface = qp_rgb565_make_surface(100, 100, cover_buffer);
    qp_init(cover_surface, QP_ROTATION_0);


    if (qp_lvgl_attach(display)) {
        wait_ms(50);
        display_init();
    }
}

// Turn display on/off based on keeb power
void suspend_power_down_user(void) {
    writePinLow(GP15);
}

void suspend_wakeup_init_user(void) {
    writePinHigh(GP15);
}



void reset_display(void) {
    lv_obj_t * disp = lv_scr_act();

    extern const hsv current_layer_colour(void);
    const hsv  lc = current_layer_colour();
    lv_obj_set_style_bg_color(disp, lv_color_make(lc.h, lc.s, lc.v), LV_STATE_DEFAULT);

    extern const char *current_layer_string(void);
    const char        *layer_name = current_layer_string();
    char buf[64] = {0};
    snprintf(buf, sizeof(buf), "layer: %s", layer_name);
    lv_label_set_text(layer_label, buf);

    lv_label_set_text(track_label, "Not playing anything...");
    lv_bar_set_value(track_progress, 0, LV_ANIM_OFF);
}


static uint32_t last_layer_state   = 0;
uint8_t raw_hid_send_buffer[32] = {0};

void update_ui(void) {
    if (last_layer_state != layer_state) {
        last_layer_state   = layer_state;

        lv_obj_t * disp = lv_scr_act();

        extern const hsv current_layer_colour(void);
        const hsv  lc = current_layer_colour();
        lv_obj_set_style_bg_color(disp, lv_color_make(lc.h, lc.s, lc.v), LV_STATE_DEFAULT);

        extern const char *current_layer_string(void);
        const char        *layer_name = current_layer_string();
        char buf[64] = {0};
        snprintf(buf, sizeof(buf), "layer: %s", layer_name);
        lv_label_set_text(layer_label, buf);

        raw_hid_send_buffer[0] = UPDT_LAYER;
        raw_hid_send_buffer[1] = layer_state; // Send new layer_state
        raw_hid_send_buffer[2] = lc.h;  // Send layer colour
        raw_hid_send_buffer[3] = lc.s;
        raw_hid_send_buffer[4] = lc.v;
        raw_hid_send(raw_hid_send_buffer, RAW_EPSIZE);
    }
}

void housekeeping_task_kb(void) {
    update_ui();
}


int point = 0;
int track_point = 0;

void display_image(void) {
    loaded_image = qp_load_image_mem(raw_image_buffer);
    qp_drawimage(cover_surface, 0, 0, loaded_image);
    qp_flush(cover_surface);

    lv_canvas_draw_img(canvas, 0, 0, &loaded_image_dsc, &dsc);
    qp_close_image(loaded_image);
    qp_flush(cover_surface);
    memset(raw_image_buffer, 0, 12000);
}

void raw_hid_receive(uint8_t *data, uint8_t length) {
    // TODO: Figure out a better way of doing this :( it is bad rn
    if (data[0] == 23 && data[1] == 23 && data[2] == 24 && data[3] == 0 && data[4] == 0) {
        println("End of sequence");
        display_image();
        point = 0;
        return;
    }

    if (data[0] == 'R' && data[1] == 'T' && data[2] == 24) {
        println("Resetting...");
        reset_display();
        qp_flush(display);
        memset(raw_image_buffer, 0, 12000);
        point = 0;
        memset(track_title, 0, 1024);
        return;
    }

    if (data[0] == 31 && data[1] == 20) { // title transmission
        println("Adding to title");
        for (int i = 2; i < length; i++) {
            track_title[track_point] = data[i];
            track_point++;
        }
        return;
    }

    if (data[0] == 24 && data[1] == 24 && data[2] == 24 && data[3] == 20) {
        println("Displaying title");
        lv_label_set_text(track_label, track_title);
        lv_label_set_long_mode(track_label, LV_LABEL_LONG_SCROLL_CIRCULAR);
        track_point = 0;
        track_set = true;
        return;
    }

    if (data[0] == 'P' && data[1] == 'R' && data[2] == 'G') {
        lv_bar_set_value(track_progress, data[3], LV_ANIM_ON);
        return;
    }

    // Image loading from a stream of transmissions
    int n = sizeof raw_image_buffer / sizeof *raw_image_buffer;
    printf("Buffer size: %d Point: %d\n", n, point);
    for (int i = 0; i < length; i++) {
        raw_image_buffer[point] = data[i];
        point++;
    }
}

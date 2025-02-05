// Copyright 2022 twitch0001 (@twitch0001)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define QUANTUM_PAINTER_DEBUG
#define QUANTUM_PAINTER_SUPPORTS_256_PALETTE true

#define MATRIX_ROWS 1
#define MATRIX_COLS 4

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED GP25
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 500U

#define SPI_DRIVER SPID1
#define SPI_SCK_PIN GP10
#define SPI_MOSI_PIN GP11
#define SPI_MISO_PIN GP12

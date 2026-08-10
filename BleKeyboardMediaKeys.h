// SPDX-License-Identifier: GPL-3.0-only
// Copyright (c) 2019 T-vK (upstream: https://github.com/T-vK/ESP32-BLE-Keyboard)
// Copyright (c) 2026 TheReider
// See the LICENSE file and the License section of the README for details.

#ifndef ESP32_BLE_KEYBOARD_MEDIA_KEYS_H
#define ESP32_BLE_KEYBOARD_MEDIA_KEYS_H

#include <stdint.h>

typedef uint16_t MediaKey;

// Power / System
const MediaKey KEY_MEDIA_POWER = 0x0030;
const MediaKey KEY_MEDIA_SLEEP = 0x0032;

// Menu navigation
const MediaKey KEY_MEDIA_MENU = 0x0040;
const MediaKey KEY_MEDIA_MENU_PICK = 0x0041;
const MediaKey KEY_MEDIA_MENU_UP = 0x0042;
const MediaKey KEY_MEDIA_MENU_DOWN = 0x0043;
const MediaKey KEY_MEDIA_MENU_LEFT = 0x0044;
const MediaKey KEY_MEDIA_MENU_RIGHT = 0x0045;
const MediaKey KEY_MEDIA_MENU_ESCAPE = 0x0046;

// Display / brightness
const MediaKey KEY_MEDIA_BRIGHTNESS_UP = 0x006F;
const MediaKey KEY_MEDIA_BRIGHTNESS_DOWN = 0x0070;

// Media transport
const MediaKey KEY_MEDIA_PLAY = 0x00B0;
const MediaKey KEY_MEDIA_PAUSE = 0x00B1;
const MediaKey KEY_MEDIA_RECORD = 0x00B2;
const MediaKey KEY_MEDIA_FAST_FORWARD = 0x00B3;
const MediaKey KEY_MEDIA_REWIND = 0x00B4;
const MediaKey KEY_MEDIA_NEXT_TRACK = 0x00B5;
const MediaKey KEY_MEDIA_PREVIOUS_TRACK = 0x00B6;
const MediaKey KEY_MEDIA_STOP = 0x00B7;
const MediaKey KEY_MEDIA_EJECT = 0x00B8;
const MediaKey KEY_MEDIA_RANDOM_PLAY = 0x00B9;
const MediaKey KEY_MEDIA_REPEAT = 0x00BC;
const MediaKey KEY_MEDIA_PLAY_PAUSE = 0x00CD;

// Volume / audio
const MediaKey KEY_MEDIA_MUTE = 0x00E2;
const MediaKey KEY_MEDIA_BASS_BOOST = 0x00E3;
const MediaKey KEY_MEDIA_LOUDNESS = 0x00E5;
const MediaKey KEY_MEDIA_VOLUME_INCREMENT = 0x00E7;
const MediaKey KEY_MEDIA_VOLUME_DECREMENT = 0x00E8;
const MediaKey KEY_MEDIA_VOLUME_UP = 0x00E9;
const MediaKey KEY_MEDIA_VOLUME_DOWN = 0x00EA;

// Application launch
const MediaKey KEY_MEDIA_CONSUMER_CONTROL_CONFIGURATION = 0x0183; // Media Selection
const MediaKey KEY_MEDIA_EMAIL_READER = 0x018A;
const MediaKey KEY_MEDIA_CALCULATOR = 0x0192;
const MediaKey KEY_MEDIA_LOCAL_MACHINE_BROWSER = 0x0194; // Opens "My Computer" on Windows

// WWW / browser
const MediaKey KEY_MEDIA_WWW_SEARCH = 0x0221;
const MediaKey KEY_MEDIA_WWW_HOME = 0x0223;
const MediaKey KEY_MEDIA_WWW_BACK = 0x0224;
const MediaKey KEY_MEDIA_WWW_FORWARD = 0x0225;
const MediaKey KEY_MEDIA_WWW_STOP = 0x0226;
const MediaKey KEY_MEDIA_WWW_REFRESH = 0x0227;
const MediaKey KEY_MEDIA_WWW_BOOKMARKS = 0x022A;

#endif // ESP32_BLE_KEYBOARD_MEDIA_KEYS_H

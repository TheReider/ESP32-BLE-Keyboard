# ESP32 BLE Keyboard

Bluetooth LE HID keyboard library for the ESP32 (Arduino IDE compatible).

**This is a maintained fork of [T-vK/ESP32-BLE-Keyboard](https://github.com/T-vK/ESP32-BLE-Keyboard).** The original project is no longer actively developed. This fork continues maintenance with bug fixes and compatibility updates for current ESP32 Arduino cores.

For the original project and its history, see [T-vK/ESP32-BLE-Keyboard](https://github.com/T-vK/ESP32-BLE-Keyboard).

**Issues and support:** Please use [this repository](https://github.com/TheReider/ESP32-BLE-Keyboard/issues), not the upstream repo.

---

## Features

- Send keystrokes and text (`print`, `write`)
- Press and release individual keys and modifiers
- Media / consumer keys via HID usage codes
- Function keys F1–F24 and numpad keys
- Set battery level, device name, and manufacturer
- `end()` to disconnect and stop advertising
- Intended for use with BLE-capable hosts (Windows, Linux, macOS, Android, iOS — see [Platform compatibility](#platform-compatibility))

## Requirements

| Requirement | Notes |
|---|---|
| [ESP32 Arduino Core](https://github.com/espressif/arduino-esp32) | 2.x and **3.x** supported (3.x compatibility fixed in v0.3.3+) |
| ESP32 board with BLE | All ESP32 variants with BLE except ESP32-S2 |

## Installation

This library is **not** available in the Arduino Library Manager. Install it manually:

1. Install the [ESP32 board support](https://github.com/espressif/arduino-esp32#installation-instructions) in the Arduino IDE.
2. Download the [latest release](https://github.com/TheReider/ESP32-BLE-Keyboard/releases) from this repository.
3. In the Arduino IDE: **Sketch → Include Library → Add .ZIP Library…** and select the downloaded file.
4. Open **File → Examples → ESP32 BLE Keyboard → SendKeyStrokes** to get started.

---

## Quick Start

```cpp
#include <BleKeyboard.h>

BleKeyboard bleKeyboard;

void setup() {
  Serial.begin(115200);
  bleKeyboard.begin();
}

void loop() {
  if (bleKeyboard.isConnected()) {
    Serial.println("Connected — sending keystrokes");
    bleKeyboard.print("Hello world");
    bleKeyboard.write(KEY_RETURN);
    bleKeyboard.write(KEY_MEDIA_PLAY_PAUSE);
  } else {
    Serial.println("Waiting for connection...");
  }
  delay(5000);
}
```

### Pairing

1. Flash the sketch to your ESP32.
2. Open the Bluetooth settings on your host device.
3. Look for **ESP32 Keyboard** (or your custom device name) and pair/connect.
4. Once connected, `isConnected()` returns `true` and keystrokes are sent.

If you change the HID descriptor (e.g. after upgrading to v0.4.0), remove the old pairing on your host and connect again.

---

## Platform compatibility

> **Disclaimer:** BLE HID keyboard support varies by operating system, device, and OS version. This fork is actively tested on **Windows** only. Android, Linux, macOS, and iOS may work but are not regularly verified here. **Always test on your target platform before relying on this library in a project.**

| Platform | Status |
|---|---|
| Windows | Tested |
| Linux | Community-reported; not regularly tested |
| macOS | Community-reported; not regularly tested |
| Android | Community-reported; not regularly tested |
| iOS | Community-reported; not regularly tested |

If you have tested this library on another platform, please [open an issue](https://github.com/TheReider/ESP32-BLE-Keyboard/issues) or pull request to update this table.

---

## API

The `BleKeyboard` interface is similar to the [Arduino Keyboard library](https://www.arduino.cc/reference/en/language/functions/usb/keyboard/). Use `bleKeyboard` instead of `Keyboard`, and include `BleKeyboard.h`.

### Constructor

```cpp
BleKeyboard bleKeyboard;                                              // defaults
BleKeyboard bleKeyboard("My Keyboard", "My Company", 100);            // name, manufacturer, battery %
```

| Parameter | Default | Description |
|---|---|---|
| `deviceName` | `"ESP32 Keyboard"` | Name shown when pairing (max 15 characters; longer names are truncated) |
| `deviceManufacturer` | `"Espressif"` | Manufacturer string |
| `batteryLevel` | `100` | Initial battery level (1–100) |

### Lifecycle

| Method | Description |
|---|---|
| `begin()` | Start BLE advertising and make the device discoverable |
| `end()` | Disconnect, stop advertising, and deinitialize BLE |
| `isConnected()` | Returns `true` when a host is connected |

### Typing and keys

| Method | Description |
|---|---|
| `print(text)` | Type a string (handles case and punctuation) |
| `write(key)` | Press and release a single key or media key |
| `press(key)` | Hold a key down |
| `release(key)` | Release a held key |
| `releaseAll()` | Release all held keys (keyboard and media) |
| `setDelay(ms)` | Delay between key events (default: 7 ms) |

Keyboard key constants are defined in `BleKeyboardKeys.h` (modifiers, arrows, F1–F24, numpad, etc.).

Media key constants are defined in `BleKeyboardMediaKeys.h` and use the `KEY_MEDIA_*` prefix, for example:

- `KEY_MEDIA_PLAY_PAUSE`, `KEY_MEDIA_VOLUME_UP`, `KEY_MEDIA_VOLUME_DOWN`, `KEY_MEDIA_MUTE`
- `KEY_MEDIA_NEXT_TRACK`, `KEY_MEDIA_PREVIOUS_TRACK`, `KEY_MEDIA_STOP`
- `KEY_MEDIA_BRIGHTNESS_UP`, `KEY_MEDIA_BRIGHTNESS_DOWN`
- `KEY_MEDIA_WWW_HOME`, `KEY_MEDIA_WWW_SEARCH`, `KEY_MEDIA_CALCULATOR`

See `BleKeyboardMediaKeys.h` for the full list.

### Bluetooth settings

| Method | Description |
|---|---|
| `setBatteryLevel(level)` | Update reported battery percentage |
| `setName(name)` | Change device name (call before `begin()`) |
| `set_vendor_id(vid)` | Set USB vendor ID (call before `begin()`) |
| `set_product_id(pid)` | Set USB product ID (call before `begin()`) |
| `set_version(version)` | Set USB version (call before `begin()`) |

The `set_vendor_id`, `set_product_id`, and `set_version` methods use snake_case for historical compatibility with the original library.

### Modifier example

```cpp
bleKeyboard.press(KEY_LEFT_CTRL);
bleKeyboard.press(KEY_LEFT_ALT);
bleKeyboard.press(KEY_DELETE);
delay(100);
bleKeyboard.releaseAll();
```

---

## Troubleshooting

| Problem | Solution |
|---|---|
| Keystrokes are not sent | Wait until `isConnected()` is `true` before calling `print()` / `write()` |
| Device not visible after flashing | Call `begin()` in `setup()`; ensure no other BLE sketch is running |
| Media keys stopped working after upgrade | Upgrade to v0.4.0+ and **re-pair** the device so the new HID descriptor is applied |
| `std::string` / `String` compile errors (ESP32 core 3.x) | Use **v0.3.3** or later from this repository |
| Name or USB IDs not applied | Call `setName()`, `set_vendor_id()`, etc. **before** `begin()` |
| Keys are skipped or dropped | Increase the delay with `setDelay(ms)` (default: 7 ms) |

---

## Migration from T-vK/ESP32-BLE-Keyboard

This fork is intended as a drop-in replacement for most sketches. Two areas changed:

### ESP32 Arduino Core 3.x

If you see `std::string` / `String` conversion errors with core 3.x, upgrade to **v0.3.3** or later from this repository.

### Media keys (v0.4.0 — breaking change)

Media keys now use real HID Consumer Control usage codes instead of bitmask values.

- Constant names like `KEY_MEDIA_PLAY_PAUSE` are unchanged.
- `MediaKeyReport` was removed; use `MediaKey` (`uint16_t`) instead.
- `press()`, `release()`, and `write()` for media keys take a single `MediaKey` value.

After upgrading to v0.4.0, **re-pair** the device with your host so the updated HID descriptor is applied.

---

## NimBLE mode (optional)

The library includes optional support for [NimBLE-Arduino](https://github.com/h2zero/NimBLE-Arduino) — an alternative Bluetooth stack that uses less RAM and flash. This comes from the original project and is **not actively tested in this fork**.

To enable it, uncomment `#define USE_NIMBLE` at the top of `BleKeyboard.h` and install the NimBLE-Arduino library in the Arduino IDE.

---

## License

This project is licensed under the **GNU General Public License v3.0** (GPL-3.0). See the [LICENSE](LICENSE) file for the full text.

### Why GPL-3.0 — code provenance

This repository contains code from multiple sources, and GPL-3.0 is the license that covers all of them:

**Upstream (T-vK):** The original [T-vK/ESP32-BLE-Keyboard](https://github.com/T-vK/ESP32-BLE-Keyboard) has no `LICENSE` file. However, in [issue #60](https://github.com/T-vK/ESP32-BLE-Keyboard/issues/60), T-vK granted permission for his code (October 2021):

> "In regards to the code that I wrote, you can use that as if licensed under MIT or GPLv3. You're probably fine if you consider the whole project GPLv3."

This fork relies on that permission and, as T-vK himself suggested, applies **GPLv3** to the project as a whole. Copyright in the upstream code remains with T-vK (copyright © 2019 T-vK).

**chegewara:** Parts of the upstream HID code trace back to [chegewara](https://github.com/chegewara), who stated in the same issue that his code "can be considered MIT or Apache". Both licenses permit inclusion in a GPLv3 work.

**Arduino Keyboard library:** The keyboard logic derives from the [Arduino Keyboard library](https://github.com/arduino-libraries/Keyboard) (**LGPL-3.0**). LGPL-3.0 code may be conveyed under GPL-3.0.

**Fork modifications (TheReider):** Bug fixes, compatibility updates, documentation, and other changes made in this repository (copyright © 2026 TheReider) are likewise licensed under GPL-3.0.

Note that GPL-3.0 is a copyleft license: if you distribute a project that includes this library, the project must be licensed under GPL-3.0 as well and its source code must be made available. See the [LICENSE](LICENSE) file for the exact terms.

---

## Credits

Based on [T-vK/ESP32-BLE-Keyboard](https://github.com/T-vK/ESP32-BLE-Keyboard), with work by [chegewara](https://github.com/chegewara), [duke2421](https://github.com/T-vK/ESP32-BLE-Keyboard/issues/1), and [sivar2311](https://github.com/sivar2311) (NimBLE support).

Maintained by [TheReider](https://github.com/TheReider).

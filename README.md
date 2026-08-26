# Lily58 RGB Wireless firmware (ZMK)

ZMK firmware for a **Lily58 RGB wireless** kit (PandaKB-style: nRF52840 / nice!nano clone, per-key RGB, 0.91" OLED).

[kata0510/Lily58](https://github.com/kata0510/Lily58) is **hardware** (PCB/case). Stock Lily58 Pro is **wired QMK**. This wireless RGB board needs **ZMK**.

| Bootloader drive | Controller | Flash |
| --- | --- | --- |
| `NICENANO` or `NRF52BOOT` | nRF52840 | The `.uf2` files from this repo's Actions tab |
| `RPI-RP2` | RP2040 | Wired QMK/Vial only. Do not use these ZMK files. |

## Screen

Stock ZMK Lily58 leaves OLED **off**. This config enables SSD1306 on **both halves**, plus RGB.

If your panels are **Sharp / nice!view** (not a small OLED), this firmware will not drive them.

## Build

GitHub Actions builds on every push. Open **Actions** → latest **Build ZMK firmware** run → download the `firmware` zip:

- `lily58_rgb_left-nice_nano_v2-zmk.uf2` — left (central, talks to the PC)
- `lily58_rgb_right-nice_nano_v2-zmk.uf2` — right
- `settings_reset-nice_nano_v2-zmk.uf2` — wipe BLE bonds, then reflash left/right

Edit `config/lily58_rgb.keymap` and `config/lily58_rgb.conf`, then push to rebuild.

## Flash

Data USB-C cable. Power switches **on**. One half at a time.

### 1. Reset bonds (first flash, or if halves will not pair)

1. Plug in the **right** half, double-tap reset, `NICENANO` appears.
2. Copy `settings_reset-nice_nano_v2-zmk.uf2` onto it. Ignore a Windows copy error.
3. Repeat on the **left** half.

### 2. Flash firmware

1. Left half → double-tap reset → copy `lily58_rgb_left-nice_nano_v2-zmk.uf2`
2. Right half → double-tap reset → copy `lily58_rgb_right-nice_nano_v2-zmk.uf2`

Do not swap left and right files.

### 3. Pair

1. Power **both** halves on together. They pair to each other.
2. Windows Bluetooth → add **Lily58**. Only the left half appears to the PC.
3. Remove any old **Lily58** pairing first if it already exists.

Lower-layer Bluetooth keys (left inner thumb = Lower):

- Top-left `BTCLR` forgets the current PC
- `BT1`–`BT5` select a profile

## Program

Plug the **left** half in over USB and open [ZMK Studio](https://zmk.studio/) in Chrome or Edge.

Default RGB: inner extra key on the right (beside N) toggles lights. Hold Lower + Raise for hue/brightness/effect.

## OLED still blank

1. Left file on left, right file on right.
2. Panel is 0.91" SSD1306 OLED, not Sharp/nice!view.
3. Original Lily58 Pro needs four OLED jumpers bridged next to the MCU; PandaKB RGB PCBs are usually already routed.
4. Display blanks after 10 minutes idle — tap a key.
5. Lower-layer `EXTPWR` toggles extra power to the OLED/RGB.

## Sources

- Hardware: https://github.com/kata0510/Lily58
- Wireless ZMK (RGB): https://github.com/PandaKBLab/zmk-for-keyboards/tree/zmk-for-lily
- Wired QMK/Vial: https://github.com/PandaKBLab/QMK-firmware-for-keyboards/tree/main/lily58
- ZMK setup: https://zmk.dev/docs/user-setup

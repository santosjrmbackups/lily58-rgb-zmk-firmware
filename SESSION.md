# Lily58 RGB wireless — session state

Saved: 2026-08-26

Resume by opening this folder and saying: continue Lily58 firmware / right OLED.

## Hardware

- Keyboard: Lily58 RGB wireless (PandaKB-style, based on kata0510/Lily58 Pro)
- Controllers: nice!nano (nRF52840)
- Bootloader drive: `NICENANO` (Adafruit nRF UF2, S140 6.1.1)
- Confirmed by flashing both halves over USB

## Firmware

- Buildable repo: https://github.com/santosjrmbackups/lily58-rgb-zmk-firmware
- Local path: `C:\Users\santo\lily58-rgb-zmk-firmware`
- ZMK pinned to **v0.3**
- Shield name: `lily58_rgb` (custom, RGB + SSD1306 OLED on both halves)
- Successful Actions run: https://github.com/santosjrmbackups/lily58-rgb-zmk-firmware/actions/runs/33020004246

UF2 files (already on disk):

| File | Path |
| --- | --- |
| Left | `firmware\lily58_rgb_left-nice_nano_v2-zmk.uf2` |
| Right | `firmware\lily58_rgb_right-nice_nano_v2-zmk.uf2` |
| Settings reset | `firmware\settings_reset-nice_nano_v2-zmk.uf2` |

Right-half build **does** include OLED (`CONFIG_ZMK_DISPLAY=y`, `CONFIG_SSD1306=y`).

## Flashing already done

1. Left: settings_reset, then left firmware — OK (`NICENANO` dropped off after copy)
2. Right: settings_reset, then right firmware — OK (second bootloader attempt succeeded)

Do **not** re-flash unless pairing or OLED work needs a clean wipe.

## Open issue

**Right OLED is blank.** Not expected on this firmware. Left-only screens are common on *other* Lily58 builds; this one enables both.

Checks not finished:

- [ ] Is the left OLED working?
- [ ] Is the right power switch on (battery or USB)?
- [ ] Are both halves powered together so they can pair?
- [ ] Extra power toggle: hold Lower, tap EXTPWR / EP_TOG
- [ ] Right OLED seated / 4-pin header / jumper pads on that PCB
- [ ] Windows Bluetooth paired to **Lily58** (left is central). Remove old Lily58 entries first

RGB toggle: inner extra key on the right, next to N.

## How to program later

- Live keymap: plug **left** half USB, open https://zmk.studio/ in Chrome/Edge
- Rebuild firmware: edit `config/lily58_rgb.keymap` or `config/lily58_rgb.conf`, git push, download Actions `firmware` zip

## Other local copies (ignore unless needed)

- `C:\Users\santo\lily58-zmk-config` — earlier PandaKB clone; not the build repo
- GitHub `santosjrmbackups/lily58-zmk-config` — leftover empty-ish repo from a failed first push (no workflow scope)

## Sources

- Hardware: https://github.com/kata0510/Lily58
- Vendor wireless ZMK: https://github.com/PandaKBLab/zmk-for-keyboards/tree/zmk-for-lily
- Vendor wired QMK (RP2040 only, drive name `RPI-RP2`): https://github.com/PandaKBLab/QMK-firmware-for-keyboards/tree/main/lily58

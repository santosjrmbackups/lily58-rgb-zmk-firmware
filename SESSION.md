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

## RGB flicker — fixed (I2S)

Left (central) pulsed; right breathed smoothly. Bootloader/reset looked stable because the MCU stopped updating the strip. Screen off / unplugged did not help.

Cause: nRF52 BLE radio on the central interrupting WS2812 **SPI**.
Fix: `CONFIG_WS2812_STRIP_I2S=y` and I2S DMA on D1/P0.06 (clocks on unused D0/D4). Left confirmed smooth after flash.

Still to do: flash matching I2S firmware on the **right** half. OLED currently off on the left (user removed the panel).

## RGB: left pulses, right breathes smoothly (resolved)

Left is ZMK central (USB + host BLE + OLED). Bootloader looks stable because ZMK stops updating the strip (LEDs freeze).

Tried: dedicated OLED thread (still pulsed).
Next: remove Studio USB-UART on left, drop BLE TX from +8 dBm to default. Rebuild and reflash both.

Quick test: unplug left USB, run on battery + Bluetooth. If it smooths, the hitch is USB/radio load.

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

## Keymap currently on the board

Source: `config/lily58_rgb.keymap`. 58 keys: 6×4 alphas + 4 thumbs per side, plus inner extra keys (mute / RGB, often encoder positions).

Layers:

- **0 default** — US QWERTY, numbers on the top row
- **1 lower** — hold left inner thumb (`LOWER`)
- **2** — hold right inner thumb (comment says RAISE; bindings are RGB/BT, not a classic raise layer)
- **3** — hold LOWER+RAISE together (ZMK Studio reserved; empty)

Quirk: there is no separate raise/nav layer. `&mo 2` is the RGB “adjust” map. Both thumbs together do **not** get you those RGB keys; they get empty layer 3.

```
Default
ESC  1  2  3  4  5                6  7  8  9  0  `
TAB  Q  W  E  R  T                Y  U  I  O  P  -
CTRL A  S  D  F  G                H  J  K  L  ;  '
SHFT Z  X  C  V  B  MUTE    RGB   N  M  ,  .  /  SHFT
            ALT GUI LOWER SPACE  ENTER RAISE BSPC GUI

Lower (hold LOWER)
BTCLR BT1 BT2 BT3 BT4 BT5              ·  ·  ·  ·  ·  ·
F1    F2  F3  F4  F5  F6               F7 F8 F9 F10 F11 F12
`     !   @   #   $   %                ^  &  *  (   )   ~
·    EP_ON EP_OFF EP_TOG ·  ·  ·    ·  ·  _  +  {   }   |
            ·   ·    ·     ·        ·    ·     ·    ·

Layer 2 (hold RAISE) — RGB / BT
BTCLR  BT1    BT2    BT3    BT4    BT5               · · · · · ·
EP_TOG RGB_HUD RGB_HUI RGB_SAD RGB_SAI RGB_EFF        · · · · · ·
·      RGB_BRD RGB_BRI ·      ·      ·               · · · · · ·
·      ·      ·      ·      ·      ·   RGB_TOG    ·  · · · · · ·
              ·      ·      ·      ·              ·  · · ·

Encoders (if installed): left = vol up/down, right = page up/down.
```

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

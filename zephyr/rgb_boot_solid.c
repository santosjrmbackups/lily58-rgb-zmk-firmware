#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/init.h>
#include <zephyr/kernel.h>

#include <zmk/rgb_underglow.h>

#if IS_ENABLED(CONFIG_ZMK_EXT_POWER)
#include <drivers/ext_power.h>
#endif

/* Neutral gray/white: hue unused at sat 0. Brightness 40 of 100, then scaled
 * by CONFIG_ZMK_RGB_UNDERGLOW_BRT_MAX (80) so white does not brown out. */
static void rgb_apply_solid_neutral(void) {
    struct zmk_led_hsb color = {
        .h = 0,
        .s = 0,
        .b = 40,
    };

    /* set_hsb does not save; select_effect persists the whole RGB state. */
    zmk_rgb_underglow_set_hsb(color);
    /* 0 = UNDERGLOW_EFFECT_SOLID. Spectrum/swirl ignore stored hue and look
     * like a rapid rainbow when you try to set white/gray. */
    zmk_rgb_underglow_select_effect(0);
    zmk_rgb_underglow_on();
}

static void rgb_boot_enable_oled_power(void) {
#if IS_ENABLED(CONFIG_ZMK_EXT_POWER) && DT_HAS_COMPAT_STATUS_OKAY(zmk_ext_power_generic)
    const struct device *ext_power = DEVICE_DT_GET(DT_INST(0, zmk_ext_power_generic));
    if (device_is_ready(ext_power)) {
        /* nice!nano P0.13 FET. Saved EP_OFF after a crash blacks both OLEDs. */
        ext_power_enable(ext_power);
    }
#endif
}

static void rgb_boot_solid_work_fn(struct k_work *work) {
    ARG_UNUSED(work);
    rgb_boot_enable_oled_power();
    rgb_apply_solid_neutral();
}

static K_WORK_DELAYABLE_DEFINE(rgb_boot_solid_work, rgb_boot_solid_work_fn);

/* After RGB init (APPLICATION 90) and settings load, which restore EEPROM
 * swirl/spectrum over *_START defaults. Short delay so settings win first. */
static int rgb_boot_solid_init(void) {
    k_work_schedule(&rgb_boot_solid_work, K_MSEC(50));
    return 0;
}

SYS_INIT(rgb_boot_solid_init, APPLICATION, 99);

#include <zephyr/init.h>
#include <zephyr/kernel.h>

#include <zmk/rgb_underglow.h>

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

static void rgb_boot_solid_work_fn(struct k_work *work) {
    ARG_UNUSED(work);
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

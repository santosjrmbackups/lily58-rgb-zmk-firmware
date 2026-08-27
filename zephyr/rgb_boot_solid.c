#include <zephyr/init.h>
#include <zephyr/kernel.h>

#include <zmk/rgb_underglow.h>

static void rgb_boot_solid_work_fn(struct k_work *work) {
    ARG_UNUSED(work);

    struct zmk_led_hsb color = {
        .h = 0,
        .s = 0,
        .b = 100,
    };

    zmk_rgb_underglow_set_hsb(color);
    /* 0 = solid/static; select_effect persists EEPROM so reboot stays solid. */
    zmk_rgb_underglow_select_effect(0);
    zmk_rgb_underglow_on();
}

static K_WORK_DELAYABLE_DEFINE(rgb_boot_solid_work, rgb_boot_solid_work_fn);

/* After RGB + settings init (same APPLICATION class, default priority 90). */
static int rgb_boot_solid_init(void) {
    k_work_schedule(&rgb_boot_solid_work, K_MSEC(500));
    return 0;
}

SYS_INIT(rgb_boot_solid_init, APPLICATION, 99);

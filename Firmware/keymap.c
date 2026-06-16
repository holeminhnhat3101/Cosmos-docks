// Copyright 2026 Ho Le Minh Nhat
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layers {
    _BASE,
    _FN
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * Base layer
     *
     * ┌─────┬─────┬─────┐
     * │  1  │  2  │  3  │
     * ├─────┼─────┼─────┤
     * │  4  │  5  │  6  │
     * ├─────┼─────┼─────┤
     * │  7  │  8  │ FN  │
     * └─────┴─────┴─────┘
     */
    [_BASE] = LAYOUT(
        KC_1,    KC_2,    KC_3,
        KC_4,    KC_5,    KC_6,
        KC_7,    KC_8,    MO(_FN)
    ),

    /*
     * Function layer
     *
     * ┌─────────┬─────────┬─────────┐
     * │ LED TOG │ LED MOD │ HUE +   │
     * ├─────────┼─────────┼─────────┤
     * │ SAT +   │ VAL +   │ MUTE    │
     * ├─────────┼─────────┼─────────┤
     * │ PREV    │ NEXT    │ TRNS    │
     * └─────────┴─────────┴─────────┘
     */
    [_FN] = LAYOUT(
        RM_TOGG, RM_NEXT, RM_HUEU,
        RM_SATU, RM_VALU, KC_MUTE,
        KC_MPRV, KC_MNXT, _______
    )
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_FN]   = { ENCODER_CCW_CW(RM_VALD, RM_VALU) }
};
#endif

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_0;
}

bool oled_task_user(void) {
    oled_write_ln_P(PSTR("Starcatcher"), false);
    oled_write_ln_P(PSTR("cosmos_docks"), false);
    oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state)) {
        case _BASE:
            oled_write_ln_P(PSTR("BASE"), false);
            break;
        case _FN:
            oled_write_ln_P(PSTR("FN"), false);
            break;
        default:
            oled_write_ln_P(PSTR("?"), false);
            break;
    }

    return false;
}
#endif
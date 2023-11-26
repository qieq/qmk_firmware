/* 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
#include <raw_hid.h>
#include "print.h"

#define _MEDIA 0
#define _FL 1
#define _CONTROLS 2
#define _RGB 3

const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_MEDIA] = LAYOUT_ortho_2x4(
        LT(_RGB, KC_MNXT), KC_MPRV,       KC_MPLY,          DF(1),
        KC_VOLD,           KC_VOLU,       LCTL_T(KC_MUTE),  KC_F23
    ),
    [_FL] = LAYOUT_ortho_2x4(
        KC_LCTL,           KC_C,          LCTL(LALT(KC_Z)), DF(2),
        LSFT_T(KC_P),      KC_T,          LCTL(KC_L),       KC_SPC
    ),
    [_CONTROLS] = LAYOUT_ortho_2x4(
        KC_MS_L,           KC_MS_D,       KC_BTN1,          DF(0), 
        KC_MS_R,           KC_MS_U,       KC_BTN2,          LALT(KC_TAB)
    )
    ,[_RGB] = LAYOUT_ortho_2x4(
        KC_TRNS,           RGB_VAD,       RGB_SAD,          RGB_HUD, 
        RGB_TOG,           RGB_VAI,       RGB_SAI,          RGB_HUI
    )
};

// bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
//     rgb rgb = {0, 255, 255};

//     if (layer_state_is(layer_index._MEDIA)) {
//         rgb.h = 130; rgb.g = 255, rgb.b = 255;
//     } else {
//        rgb.h = 30; rgb.g = 255, rgb.b = 255;
//     }

//     if (rgb.b > rgb_matrix_get_val()) {
//         rgb.b = rgb_matrix_get_val();
//     }
    
//     return false;
// }

layer_state_t default_layer_state_set_user(layer_state_t state) {
    RGB rgb = { 0, 0, 0 };

    switch (biton32(state)) {
        case _MEDIA:
            rgb.r = 255; rgb.g = 0, rgb.b = 0;
            break;
        case _FL:
            rgb.r = 0; rgb.g = 255, rgb.b = 0;
            break;
        case _CONTROLS:
            rgb.r = 0; rgb.g = 0, rgb.b = 255;
            break;
        case _RGB:
            rgb.r = 130; rgb.g = 0, rgb.b = 255;
            break;
        default: //  for any other layers, or the default layer
            rgb.r = 10; rgb.g = 100, rgb.b = 200;
            break;
    }

    uprintf("\nrgb: %i, %i, %i", rgb.r, rgb.g, rgb.b);

    rgb_matrix_step();

    return state;
}
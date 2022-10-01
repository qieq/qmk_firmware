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

#undef RGB_MATRIX_STARTUP_MODE
#define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_SOLID_COLOR

enum layer_number { _MEDIA = 0, _FL, _CONTROLS, _RGB };


const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_MEDIA] = LAYOUT_ortho_2x4(
        LT(_RGB, KC_MNXT), KC_MPRV,       KC_MPLY,          DF(1),
        KC_VOLD,           KC_VOLU,       LCTL_T(KC_MUTE),  KC_F23
    )
    ,[_FL] = LAYOUT_ortho_2x4(
        KC_LCTL,           KC_C,          LCTL(LALT(KC_Z)), DF(0),
        LSFT_T(KC_P),      KC_T,          LCTL(KC_L),       KC_SPC
    )
    ,[_RGB] = LAYOUT_ortho_2x4(
        KC_TRNS,           RGB_VAD,       RGB_SAD,          RGB_HUD, 
        RGB_TOG,           RGB_VAI,       RGB_SAI,          RGB_HUI
    )
};

void set_layer_key_color(uint8_t led_min, uint8_t led_max, uint16_t hue)
{
    // uprintf("\nset_layer_key_color (led_min:%u, led_max:%u, hue:%u)", led_min, led_max, hue);
    HSV layer_hsv = rgb_matrix_get_hsv();
    // uprintf("\nlayer_hsv: %u, %u, %u", layer_hsv.h, layer_hsv.s, layer_hsv.v);
    layer_hsv.h = hue;
    RGB rgb = hsv_to_rgb(layer_hsv);
    // uprintf("\nlayer rgb: %u, %u, %u", rgb.r, rgb.g, rgb.b);
    
    for (int i = led_min; i < led_max; i++) 
    {
        if (HAS_FLAGS(g_led_config.flags[i], LED_FLAG_KEYLIGHT))
        {
           RGB_MATRIX_INDICATOR_SET_COLOR(i, rgb.r, rgb.g, rgb.b);
        }
    }
}

uint8_t layer = -1;

layer_state_t layer_set_changed(layer_state_t state)
{
    switch (get_highest_layer(state)) 
    {
        case _MEDIA:
        {
            layer = _MEDIA;
            return state;
        }
        case _FL:
        {
            layer = _FL;
            return state;
        }
        case _RGB:
        {
            layer = _RGB;
            return state;
        }
    }

    return state;
}

void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    switch (layer) 
    {
        case _MEDIA:
        {
            // printf("\nlayer set: _MEDIA");
            set_layer_key_color(led_min, led_max, 60);
        }
        case _FL:
        {
            // printf("\nlayer set: _FL");
            set_layer_key_color(led_min, led_max, 310);
        }
        case _RGB:
        {
            // printf("\nlayer set: _RGB");
            set_layer_key_color(led_min, led_max, 180);
        }
    }
}

layer_state_t default_layer_state_set_user(layer_state_t state)
{
    return layer_set_changed(state);
}

layer_state_t layer_state_set_user(layer_state_t state)
{
    return layer_set_changed(state);
}
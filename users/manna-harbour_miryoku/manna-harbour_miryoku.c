// Copyright 2022 Manna Harbour
// https://github.com/manna-harbour/miryoku

// This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 2 of the License, or (at your option) any later version. This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.

#include QMK_KEYBOARD_H
#include "./localization/custom_keycodes.h"
#include "../../quantum/keymap_extras/keymap_german.h"
#include "manna-harbour_miryoku.h"
#include "../../quantum/keymap_extras/sendstring_german.h"


// Additional Features double tap guard

enum {
    U_TD_BOOT,
#define MIRYOKU_X(LAYER, STRING) U_TD_U_##LAYER,
MIRYOKU_LAYER_LIST
#undef MIRYOKU_X
};


void u_td_fn_boot(qk_tap_dance_state_t *state, void *user_data) { \
  if (state->count == 2) {
    reset_keyboard();
  }
}

#define MIRYOKU_X(LAYER, STRING) \
void u_td_fn_U_##LAYER(qk_tap_dance_state_t *state, void *user_data) { \
  if (state->count == 2) { \
    default_layer_set((layer_state_t)1 << U_##LAYER); \
  } \
}
MIRYOKU_LAYER_LIST
#undef MIRYOKU_X

qk_tap_dance_action_t tap_dance_actions[] = {
    [U_TD_BOOT] = ACTION_TAP_DANCE_FN(u_td_fn_boot),
#define MIRYOKU_X(LAYER, STRING) [U_TD_U_##LAYER] = ACTION_TAP_DANCE_FN(u_td_fn_U_##LAYER),
MIRYOKU_LAYER_LIST
#undef MIRYOKU_X
};


// keymap

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
#define MIRYOKU_X(LAYER, STRING) [U_##LAYER] = U_MACRO_VA_ARGS(MIRYOKU_LAYERMAPPING_##LAYER, MIRYOKU_LAYER_##LAYER),
MIRYOKU_LAYER_LIST
#undef MIRYOKU_X
};


// shift functions

const key_override_t capsword_key_override = ko_make_basic(MOD_MASK_SHIFT, CAPSWRD, KC_CAPS);
const key_override_t slsh_ques_override = ko_make_basic(MOD_MASK_SHIFT, DE_SLSH, DE_QUES);
const key_override_t slsh_scln_coln = ko_make_basic(MOD_MASK_SHIFT,DE_SCLN, DE_COLN);
const key_override_t slsh_comm_labk = ko_make_basic(MOD_MASK_SHIFT,DE_COMM, DE_LABK);
const key_override_t slsh_dot_rabk = ko_make_basic(MOD_MASK_SHIFT,DE_DOT, DE_RABK);
const key_override_t slsh_quot_dquo = ko_make_basic(MOD_MASK_SHIFT,DE_QUOT, DE_DQUO);

const key_override_t **key_overrides = (const key_override_t *[]){
  &slsh_ques_override ,
  &slsh_ques_override, 
  &slsh_scln_coln, 
  &slsh_comm_labk, 
  &slsh_dot_rabk, 
  &slsh_quot_dquo, 
  NULL
};



// thumb combos

#if defined (MIRYOKU_KLUDGE_THUMBCOMBOS)
const uint16_t PROGMEM thumbcombos_base_right[] = {LT(U_SYM, KC_ENT), LT(U_NUM, KC_BSPC), COMBO_END};
const uint16_t PROGMEM thumbcombos_base_left[] = {LT(U_NAV, KC_SPC), LT(U_MOUSE, KC_TAB), COMBO_END};
const uint16_t PROGMEM thumbcombos_nav[] = {KC_ENT, KC_BSPC, COMBO_END};
const uint16_t PROGMEM thumbcombos_mouse[] = {KC_BTN2, KC_BTN1, COMBO_END};
const uint16_t PROGMEM thumbcombos_media[] = {KC_MSTP, KC_MPLY, COMBO_END};
const uint16_t PROGMEM thumbcombos_num[] = {KC_0, KC_MINS, COMBO_END};
  #if defined (MIRYOKU_LAYERS_FLIP)
const uint16_t PROGMEM thumbcombos_sym[] = {KC_UNDS, KC_LPRN, COMBO_END};
  #else
const uint16_t PROGMEM thumbcombos_sym[] = {KC_RPRN, KC_UNDS, COMBO_END};
  #endif
const uint16_t PROGMEM thumbcombos_fun[] = {KC_SPC, KC_TAB, COMBO_END};
combo_t key_combos[COMBO_COUNT] = {
  COMBO(thumbcombos_base_right, LT(U_FUN, KC_DEL)),
  COMBO(thumbcombos_base_left, LT(U_MEDIA, KC_ESC)),
  COMBO(thumbcombos_nav, KC_DEL),
  COMBO(thumbcombos_mouse, KC_BTN3),
  COMBO(thumbcombos_media, KC_MUTE),
  COMBO(thumbcombos_num, KC_DOT),
  #if defined (MIRYOKU_LAYERS_FLIP)
  COMBO(thumbcombos_sym, KC_RPRN),
  #else
  COMBO(thumbcombos_sym, KC_LPRN),
  #endif
  COMBO(thumbcombos_fun, KC_APP)
};
#endif


#ifdef ENCODER_ENABLE

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else if (index == 1) {
        if (clockwise) {
            tap_code(KC_PGDOWN);
        } else {
            tap_code(KC_PGUP);
        }
    }
    return true;
}

#endif


// bool process_record_user(uint16_t keycode, keyrecord_t *record) {
//   // handling this once instead of in each keycode uses less program memory.
//   if ((keycode >= SAFE_RANGE) && !(record->event.pressed)) {
//     return false;
//   }
//
//   switch (keycode) {
//     case :
//       if (record->event.pressed) {
//         SEND_STRING("3NV1jY~-PO@n70J=");
//       }
//       return false;
//       break;
//   }
//
//   // this uses less memory than returning in each case.
//   return keycode < SAFE_RANGE;
// };
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SS_CRYPT:
            if (record->event.pressed) {
                SEND_STRING("3NV1jY~-PO@n70J=");
            }
            return false;
        case SS_CIRC:
            if (record->event.pressed) {
                SEND_STRING("^");
            }
            return false;
    }

    return true;
}


#ifdef OLED_ENABLE

static void render_logo(void) {
  static const char PROGMEM qmk_logo[] = {
    0x00, 0x00, 0x00, 0xf8, 0xf8, 0xf8, 0xf8, 0xe0, 0xc0, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x40, 0x78, 0x78, 0x78, 0x00, 0x7c, 0x7c, 0x7c, 0x00, 0x78, 
    0x78, 0x78, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x80, 0x00, 0x80, 0x80, 
    0xc0, 0xe0, 0xf8, 0xf8, 0xf8, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x1f, 0x87, 0xf3, 0xf9, 
    0x3c, 0x0e, 0x1e, 0x83, 0x83, 0xfd, 0x7d, 0xff, 0x03, 0x05, 0x01, 0x01, 0x01, 0x01, 0x02, 0x02, 
    0x04, 0x09, 0xf3, 0x87, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0xe1, 0xcf, 0xbf, 0x79, 0x70, 0xf0, 0xc1, 
    0x81, 0xbd, 0xbe, 0xff, 0xc0, 0xa0, 0xa0, 0x80, 0x80, 0x80, 0x80, 0x40, 0x60, 0xb0, 0xce, 0xe3, 
    0xf8, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x1f, 0x1f, 0x1f, 0x07, 0x03, 0x01, 0x01, 0x01, 
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x1e, 0x1e, 0x1c, 0x00, 0x7e, 
    0x7e, 0x7e, 0x00, 0x1e, 0x1e, 0x1e, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 
    0x01, 0x01, 0x01, 0x01, 0x03, 0x0f, 0x1f, 0x1f, 0x1f, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
  };

    // oled_write_P(qmk_logo, false);
  oled_write_raw_P(qmk_logo, sizeof(qmk_logo));
}

static void print_status_narrow(void) {
    // Print current mode
    oled_write_P(PSTR("\n\n"), false);
    oled_write_ln_P(PSTR("MODE"), false);
    oled_write_ln_P(PSTR(""), false);
    // if (keymap_config.swap_lctl_lgui) {
    //     oled_write_ln_P(PSTR("MAC"), false);
    // } else {
    //     oled_write_ln_P(PSTR("WIN"), false);
    // }

    // switch (get_highest_layer(default_layer_state)) {
    //     case _QWERTY:
    //         oled_write_ln_P(PSTR("Qwrt"), false);
    //         break;
    //     case _COLEMAK:
    //         oled_write_ln_P(PSTR("Clmk"), false);
    //         break;
    //     default:
    //         oled_write_P(PSTR("Undef"), false);
    // }
    // oled_write_P(PSTR("\n\n"), false);
    // Print current layer
    oled_write_ln_P(PSTR("LAYER"), false);
    switch (get_highest_layer(layer_state)) {
        case U_BASE:
            oled_write_P(PSTR("Base\n"), false);
            break;
        case U_SYM:
            oled_write_P(PSTR("Sym\n"), false);
            break;
        case U_NUM:
            oled_write_P(PSTR("Num\n"), false);
            break;
        case U_NAV:
            oled_write_P(PSTR("Nav\n"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undef\n"), false);
    }
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_270;
    }
    return rotation;
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        print_status_narrow();
    } else {
        render_logo();
    }
    return false;
}

#endif

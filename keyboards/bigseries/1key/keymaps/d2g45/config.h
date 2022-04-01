/*
Copyright 2018 Cole Markham

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#define TAPPING_TERM 500

#define TAPPING_FORCE_HOLD

/* key matrix pins */
#undef MATRIX_ROW_PINS
#define MATRIX_ROW_PINS { D4 }

#undef MATRIX_COL_PINS
#define MATRIX_COL_PINS { C6 }

#undef UNUSED_PINS
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#undef DIODE_DIRECTION
#define DIODE_DIRECTION COL2ROW

/* number of backlight levels */
#ifdef BACKLIGHT_PIN
#define BACKLIGHT_LEVELS 1
#endif

/* Set 0 if debouncing isn't needed */
#undef DEBOUNCE
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#undef LOCKING_SUPPORT_ENABLE
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#undef LOCKING_RESYNC_ENABLE
#define LOCKING_RESYNC_ENABLE

/* key combination for command */
#undef IS_COMMAND
#define IS_COMMAND() ( \
    keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT)))

/* prevent stuck modifiers */
#undef PREVENT_STUCK_MODIFIERS
#define PREVENT_STUCK_MODIFIERS

#undef RGB_DI_PIN
#define RGB_DI_PIN D1

#ifdef RGB_DI_PIN
// #define RGBLIGHT_ANIMATIONS
#define RGBLIGHT_EFFECT_ALTERNATING
#define RGBLIGHT_EFFECT_BREATHING
#define RGBLIGHT_EFFECT_RAINBOW_MOOD
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#define RGBLIGHT_EFFECT_ALTERNATING

#undef RGBLED_NUM
#define RGBLED_NUM 16

#undef RGBLIGHT_HUE_STEP
#define RGBLIGHT_HUE_STEP 12

#undef RGBLIGHT_SAT_STEP
#define RGBLIGHT_SAT_STEP 12

#undef RGBLIGHT_VAL_STEP
#define RGBLIGHT_VAL_STEP 12
#endif

#endif

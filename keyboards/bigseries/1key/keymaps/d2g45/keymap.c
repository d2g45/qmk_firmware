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

#include QMK_KEYBOARD_H


typedef struct
{
	bool is_press_action;
	int state;
} tap;

enum TAP_DANCE {
    TD_PLAY = 0,
};

enum
{
	SINGLE_TAP = 1,
	SINGLE_HOLD = 2,
	DOUBLE_TAP = 3,
	DOUBLE_HOLD = 4,
	TRIPLE_TAP = 5,
	TRIPLE_HOLD = 6,
	QUADRUPLE_TAP = 7,
	QUADRUPLE_HOLD = 8,
	QUINTUPLE_TAP = 9,
	QUINTUPLE_HOLD = 10
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    LAYOUT(TD(TD_PLAY)),
};

//instantialize an instance of 'tap' for the 'x' tap dance.
static tap xtap_state = {
	.is_press_action = true,
	.state = 0
};

/* Return an integer that corresponds to what kind of tap dance should be executed.
 *
 * How to figure out tap dance state: interrupted and pressed.
 *
 * Interrupted: If the state of a dance dance is "interrupted", that means that another key has been hit
 *  under the tapping term. This is typically indicitive that you are trying to "tap" the key.
 *
 * Pressed: Whether or not the key is still being pressed. If this value is true, that means the tapping term
 *  has ended, but the key is still being pressed down. This generally means the key is being "held".
 *
 * One thing that is currenlty not possible with qmk software in regards to tap dance is to mimic the "permissive hold"
 *  feature. In general, advanced tap dances do not work well if they are used with commonly typed letters.
 *  For example "A". Tap dances are best used on non-letter keys that are not hit while typing letters.
 *
 * Good places to put an advanced tap dance:
 *  z,q,x,j,k,v,b, any function key, home/end, comma, semi-colon
 *
 * Criteria for "good placement" of a tap dance key:
 *  Not a key that is hit frequently in a sentence
 *  Not a key that is used frequently to double tap, for example 'tab' is often double tapped in a terminal, or
 *    in a web form. So 'tab' would be a poor choice for a tap dance.
 *  Letters used in common words as a double. For example 'p' in 'pepper'. If a tap dance function existed on the
 *    letter 'p', the word 'pepper' would be quite frustating to type.
 *
 * For the third point, there does exist the 'DOUBLE_SINGLE_TAP', however this is not fully tested
 *
 */

int cur_dance(qk_tap_dance_state_t *state)
{
	if (state->count == 1)
	{
		if (state->interrupted || !state->pressed)
			return SINGLE_TAP;
		// key has not been interrupted, but they key is still held. Means you want to send a 'HOLD'.
		else
			return SINGLE_HOLD;
	}
	else if (state->count == 2)
	{
		if (state->interrupted || !state->pressed)
			return DOUBLE_TAP;
		else
			return DOUBLE_HOLD;
	}
	else if (state->count == 3)
	{
		if (state->interrupted || !state->pressed)
			return TRIPLE_TAP;
		else
			return TRIPLE_HOLD;
	}
	else if (state->count == 4)
	{
		if (state->interrupted || !state->pressed)
			return QUADRUPLE_TAP;
		else
			return QUADRUPLE_HOLD;
	}
	else if (state->count == 5)
	{
		if (state->interrupted || !state->pressed)
			return QUINTUPLE_TAP;
		else
			return QUINTUPLE_HOLD;
	}

	else
		return 99; //magic number. At some point this method will expand to work for more presses
}


void x_finished(qk_tap_dance_state_t *state, void *user_data)
{
	xtap_state.state = cur_dance(state);
	switch (xtap_state.state)
	{
	case SINGLE_TAP:
		register_code(KC_ENT);
		break;
	case SINGLE_HOLD:
		// register_code(KC_LALT);
		// register_code(KC_F9);
		register_code(KC_SPC);
		break;
	case DOUBLE_TAP:
		rgblight_step();
		break;
	case DOUBLE_HOLD:
		rgblight_toggle();
		break;
	case TRIPLE_TAP:
		break;
	case TRIPLE_HOLD:
		rgblight_increase_hue();
		break;
	case QUADRUPLE_TAP:
		break;
	case QUADRUPLE_HOLD:
		rgblight_increase_sat();
		break;
	case QUINTUPLE_TAP:
		break;
	case QUINTUPLE_HOLD:
		rgblight_increase_val();
		break;
	}
}

void x_reset(qk_tap_dance_state_t *state, void *user_data)
{
	switch (xtap_state.state)
	{
	case SINGLE_TAP:
		unregister_code(KC_ENT);
		break;
	case SINGLE_HOLD:
		// unregister_code(KC_LALT);
		// unregister_code(KC_F9);
		unregister_code(KC_SPC);
		break;
	case DOUBLE_TAP:
		break;
	case DOUBLE_HOLD:
		break;
	case TRIPLE_TAP:
		break;
	case TRIPLE_HOLD:
		break;
	case QUADRUPLE_TAP:
		break;
	case QUADRUPLE_HOLD:
		break;
	case QUINTUPLE_TAP:
		break;
	case QUINTUPLE_HOLD:
		break;
	}
	xtap_state.state = 0;
}

// All tap dance functions would go here. Only showing this one.
qk_tap_dance_action_t tap_dance_actions[] = {
	[TD_PLAY] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, x_finished, x_reset)
};

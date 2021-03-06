/***************************************************************************
    SDL Based Input Handling.

    Populates keys array with user input.
    If porting to a non-SDL platform, you would need to replace this class.

    Copyright Chris White.
    See license.txt for more details.
***************************************************************************/

#pragma once

#include <SDL.h>

#include "bbox.hpp"

typedef struct touch_s 
	: SDL_MouseMotionEvent
{
	uint8_t key			: 8;
	uint8_t key_pressed : 1;
	uint8_t processed	: 1;
} touch_t;

class Input
{
public:

    enum presses
    {
        LEFT  = 0,
        RIGHT = 1,
        UP    = 2,
        DOWN  = 3,
        ACCEL = 4,
        BRAKE = 5,
        GEAR1 = 6,
        GEAR2 = 7,

        START = 8,
        COIN  = 9,
        VIEWPOINT = 10,
        
        PAUSE = 11,
        STEP  = 12,
        TIMER = 13,
        MENU = 14,     

        _MAX = 15,
	};

	const static int FRONTEND_MASK = (1 << UP) | (1 << DOWN) | (1 << ACCEL);
	const static int START_MASK = (1 << COIN) | (1 << START) | (1 << MENU);
	const static int MUSIC_MASK = (1 << COIN) | (1 << START) | (1 << MENU) |
		(1 << LEFT) | (1 << RIGHT); 
	const static int BEST_MASK = (1 << MENU) | (1 << LEFT) | (1 << RIGHT) | (1 << ACCEL);
	const static int INGAME_MASK = FRONTEND_MASK | (1 << LEFT) | 
		(1 << RIGHT) | (1 << BRAKE) | (1 << GEAR1) | (1 << GEAR2) | (1 << MENU);

	uint16_t active_panels;

    bool keys[15];
    bool keys_old[15];

    // Has gamepad been found?
    bool gamepad;

    // Use analog controls
    int analog;

    // Latch last key press for redefines
    int key_press;

    // Latch last joystick button press for redefines
    int16_t joy_button;

    // Analog Controls
    int a_wheel;
    int a_accel;
    int a_brake;

    Input(void);
    ~Input(void);

	void init(int, int*, int*, const int, int*, int*, const bounding_box_t*);
    void close();

    void handle_key_up(SDL_keysym*);
    void handle_key_down(SDL_keysym*);
    void handle_joy_axis(SDL_JoyAxisEvent*);
    void handle_joy_down(SDL_JoyButtonEvent*);
    void handle_joy_up(SDL_JoyButtonEvent*);
	void handle_motion(SDL_MouseMotionEvent*);
	void handle_mouse(SDL_MouseButtonEvent*);
#if defined (__ANDROID__)
	void handle_finger(SDL_TouchFingerEvent*);
#endif
    void frame_done();
    bool is_pressed(presses p);
    bool is_pressed_clear(presses p);
    bool has_pressed(presses p);
    bool is_analog_l();
    bool is_analog_r();
    bool is_analog_select();

private:
	const static int CENTRE = 0x80;

    // Digital Dead Zone
	const static int DIGITAL_DEAD = 3200;

    // SDL Joystick / Keypad
    SDL_Joystick *stick;

	// SDL Motions [Touch Count]
	bounding_box_t panels_collsion[15];

	// Touches
	const static uint8_t TOUCH_COUNT = 8;
	touch_t touch_list[TOUCH_COUNT];

    // Configurations for keyboard and joypad
    int* pad_config;
    int* key_config;
    int* axis;

    int wheel_zone;
    int wheel_dead;
    int pedals_dead;

	const static int DELAY_RESET = 60;
    int delay;

	void handle_key(const int, const bool);
	void handle_joy(const uint8_t, const bool);
};

extern Input input;
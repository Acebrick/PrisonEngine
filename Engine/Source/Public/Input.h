#pragma once

typedef enum
{
    EE_KEY_UNKNOWN = 0,

    /**
     *  \name Usage page 0x07
     *
     *  These values are from usage page 0x07 (USB keyboard page).
     */
    /* @{ */

    EE_KEY_A = 4,
    EE_KEY_B = 5,
    EE_KEY_C = 6,
    EE_KEY_D = 7,
    EE_KEY_E = 8,
    EE_KEY_F = 9,
    EE_KEY_G = 10,
    EE_KEY_H = 11,
    EE_KEY_I = 12,
    EE_KEY_J = 13,
    EE_KEY_K = 14,
    EE_KEY_L = 15,
    EE_KEY_M = 16,
    EE_KEY_N = 17,
    EE_KEY_O = 18,
    EE_KEY_P = 19,
    EE_KEY_Q = 20,
    EE_KEY_R = 21,
    EE_KEY_S = 22,
    EE_KEY_T = 23,
    EE_KEY_U = 24,
    EE_KEY_V = 25,
    EE_KEY_W = 26,
    EE_KEY_X = 27,
    EE_KEY_Y = 28,
    EE_KEY_Z = 29,

    EE_KEY_1 = 30,
    EE_KEY_2 = 31,
    EE_KEY_3 = 32,
    EE_KEY_4 = 33,
    EE_KEY_5 = 34,
    EE_KEY_6 = 35,
    EE_KEY_7 = 36,
    EE_KEY_8 = 37,
    EE_KEY_9 = 38,
    EE_KEY_0 = 39,

    EE_KEY_RETURN = 40,
    EE_KEY_ESCAPE = 41,
    EE_KEY_BACKSPACE = 42,
    EE_KEY_TAB = 43,
    EE_KEY_SPACE = 44,

    EE_KEY_MINUS = 45,
    EE_KEY_EQUALS = 46,
    EE_KEY_LEFTBRACKET = 47,
    EE_KEY_RIGHTBRACKET = 48,
    EE_KEY_BACKSLASH = 49, /**< Located at the lower left of the return
                                  *   key on ISO keyboards and at the right end
                                  *   of the QWERTY row on ANSI keyboards.
                                  *   Produces REVERSE SOLIDUS (backslash) and
                                  *   VERTICAL LINE in a US layout, REVERSE
                                  *   SOLIDUS and VERTICAL LINE in a UK Mac
                                  *   layout, NUMBER SIGN and TILDE in a UK
                                  *   Windows layout, DOLLAR SIGN and POUND SIGN
                                  *   in a Swiss German layout, NUMBER SIGN and
                                  *   APOSTROPHE in a German layout, GRAVE
                                  *   ACCENT and POUND SIGN in a French Mac
                                  *   layout, and ASTERISK and MICRO SIGN in a
                                  *   French Windows layout.
                                  */
    EE_KEY_NONUSHASH = 50, /**< ISO USB keyboards actually use this code
                                  *   instead of 49 for the same key, but all
                                  *   OSes I've seen treat the two codes
                                  *   identically. So, as an implementor, unless
                                  *   your keyboard generates both of those
                                  *   codes and your OS treats them differently,
                                  *   you should generate EE_KEY_BACKSLASH
                                  *   instead of this code. As a user, you
                                  *   should not rely on this code because SDL
                                  *   will never generate it with most (all?)
                                  *   keyboards.
                                  */
    EE_KEY_SEMICOLON = 51,
    EE_KEY_APOSTROPHE = 52,
    EE_KEY_GRAVE = 53, /**< Located in the top left corner (on both ANSI
                              *   and ISO keyboards). Produces GRAVE ACCENT and
                              *   TILDE in a US Windows layout and in US and UK
                              *   Mac layouts on ANSI keyboards, GRAVE ACCENT
                              *   and NOT SIGN in a UK Windows layout, SECTION
                              *   SIGN and PLUS-MINUS SIGN in US and UK Mac
                              *   layouts on ISO keyboards, SECTION SIGN and
                              *   DEGREE SIGN in a Swiss German layout (Mac:
                              *   only on ISO keyboards), CIRCUMFLEX ACCENT and
                              *   DEGREE SIGN in a German layout (Mac: only on
                              *   ISO keyboards), SUPERSCRIPT TWO and TILDE in a
                              *   French Windows layout, COMMERCIAL AT and
                              *   NUMBER SIGN in a French Mac layout on ISO
                              *   keyboards, and LESS-THAN SIGN and GREATER-THAN
                              *   SIGN in a Swiss German, German, or French Mac
                              *   layout on ANSI keyboards.
                              */
    EE_KEY_COMMA = 54,
    EE_KEY_PERIOD = 55,
    EE_KEY_SLASH = 56,

    EE_KEY_CAPSLOCK = 57,

    EE_KEY_F1 = 58,
    EE_KEY_F2 = 59,
    EE_KEY_F3 = 60,
    EE_KEY_F4 = 61,
    EE_KEY_F5 = 62,
    EE_KEY_F6 = 63,
    EE_KEY_F7 = 64,
    EE_KEY_F8 = 65,
    EE_KEY_F9 = 66,
    EE_KEY_F10 = 67,
    EE_KEY_F11 = 68,
    EE_KEY_F12 = 69,

    EE_KEY_PRINTSCREEN = 70,
    EE_KEY_SCROLLLOCK = 71,
    EE_KEY_PAUSE = 72,
    EE_KEY_INSERT = 73, /**< insert on PC, help on some Mac keyboards (but
                                   does send code 73, not 117) */
    EE_KEY_HOME = 74,
    EE_KEY_PAGEUP = 75,
    EE_KEY_DELETE = 76,
    EE_KEY_END = 77,
    EE_KEY_PAGEDOWN = 78,
    EE_KEY_RIGHT = 79,
    EE_KEY_LEFT = 80,
    EE_KEY_DOWN = 81,
    EE_KEY_UP = 82,

    EE_KEY_NUMLOCKCLEAR = 83, /**< num lock on PC, clear on Mac keyboards
                                     */
    EE_KEY_KP_DIVIDE = 84,
    EE_KEY_KP_MULTIPLY = 85,
    EE_KEY_KP_MINUS = 86,
    EE_KEY_KP_PLUS = 87,
    EE_KEY_KP_ENTER = 88,
    EE_KEY_KP_1 = 89,
    EE_KEY_KP_2 = 90,
    EE_KEY_KP_3 = 91,
    EE_KEY_KP_4 = 92,
    EE_KEY_KP_5 = 93,
    EE_KEY_KP_6 = 94,
    EE_KEY_KP_7 = 95,
    EE_KEY_KP_8 = 96,
    EE_KEY_KP_9 = 97,
    EE_KEY_KP_0 = 98,
    EE_KEY_KP_PERIOD = 99,

    EE_KEY_NONUSBACKSLASH = 100, /**< This is the additional key that ISO
                                        *   keyboards have over ANSI ones,
                                        *   located between left shift and Y.
                                        *   Produces GRAVE ACCENT and TILDE in a
                                        *   US or UK Mac layout, REVERSE SOLIDUS
                                        *   (backslash) and VERTICAL LINE in a
                                        *   US or UK Windows layout, and
                                        *   LESS-THAN SIGN and GREATER-THAN SIGN
                                        *   in a Swiss German, German, or French
                                        *   layout. */
    EE_KEY_APPLICATION = 101, /**< windows contextual menu, compose */
    EE_KEY_POWER = 102, /**< The USB document says this is a status flag,
                               *   not a physical key - but some Mac keyboards
                               *   do have a power key. */
    EE_KEY_KP_EQUALS = 103,
    EE_KEY_F13 = 104,
    EE_KEY_F14 = 105,
    EE_KEY_F15 = 106,
    EE_KEY_F16 = 107,
    EE_KEY_F17 = 108,
    EE_KEY_F18 = 109,
    EE_KEY_F19 = 110,
    EE_KEY_F20 = 111,
    EE_KEY_F21 = 112,
    EE_KEY_F22 = 113,
    EE_KEY_F23 = 114,
    EE_KEY_F24 = 115,
    EE_KEY_EXECUTE = 116,
    EE_KEY_HELP = 117,    /**< AL Integrated Help Center */
    EE_KEY_MENU = 118,    /**< Menu (show menu) */
    EE_KEY_SELECT = 119,
    EE_KEY_STOP = 120,    /**< AC Stop */
    EE_KEY_AGAIN = 121,   /**< AC Redo/Repeat */
    EE_KEY_UNDO = 122,    /**< AC Undo */
    EE_KEY_CUT = 123,     /**< AC Cut */
    EE_KEY_COPY = 124,    /**< AC Copy */
    EE_KEY_PASTE = 125,   /**< AC Paste */
    EE_KEY_FIND = 126,    /**< AC Find */
    EE_KEY_MUTE = 127,
    EE_KEY_VOLUMEUP = 128,
    EE_KEY_VOLUMEDOWN = 129,
/* not sure whether there's a reason to enable these */
/*     EE_KEY_LOCKINGCAPSLOCK = 130,  */
/*     EE_KEY_LOCKINGNUMLOCK = 131, */
/*     EE_KEY_LOCKINGSCROLLLOCK = 132, */
    EE_KEY_KP_COMMA = 133,
    EE_KEY_KP_EQUALSAS400 = 134,

    EE_KEY_INTERNATIONAL1 = 135, /**< used on Asian keyboards, see
                                            footnotes in USB doc */
    EE_KEY_INTERNATIONAL2 = 136,
    EE_KEY_INTERNATIONAL3 = 137, /**< Yen */
    EE_KEY_INTERNATIONAL4 = 138,
    EE_KEY_INTERNATIONAL5 = 139,
    EE_KEY_INTERNATIONAL6 = 140,
    EE_KEY_INTERNATIONAL7 = 141,
    EE_KEY_INTERNATIONAL8 = 142,
    EE_KEY_INTERNATIONAL9 = 143,
    EE_KEY_LANG1 = 144, /**< Hangul/English toggle */
    EE_KEY_LANG2 = 145, /**< Hanja conversion */
    EE_KEY_LANG3 = 146, /**< Katakana */
    EE_KEY_LANG4 = 147, /**< Hiragana */
    EE_KEY_LANG5 = 148, /**< Zenkaku/Hankaku */
    EE_KEY_LANG6 = 149, /**< reserved */
    EE_KEY_LANG7 = 150, /**< reserved */
    EE_KEY_LANG8 = 151, /**< reserved */
    EE_KEY_LANG9 = 152, /**< reserved */

    EE_KEY_ALTERASE = 153,    /**< Erase-Eaze */
    EE_KEY_SYSREQ = 154,
    EE_KEY_CANCEL = 155,      /**< AC Cancel */
    EE_KEY_CLEAR = 156,
    EE_KEY_PRIOR = 157,
    EE_KEY_RETURN2 = 158,
    EE_KEY_SEPARATOR = 159,
    EE_KEY_OUT = 160,
    EE_KEY_OPER = 161,
    EE_KEY_CLEARAGAIN = 162,
    EE_KEY_CRSEL = 163,
    EE_KEY_EXSEL = 164,

    EE_KEY_KP_00 = 176,
    EE_KEY_KP_000 = 177,
    EE_KEY_THOUSANDSSEPARATOR = 178,
    EE_KEY_DECIMALSEPARATOR = 179,
    EE_KEY_CURRENCYUNIT = 180,
    EE_KEY_CURRENCYSUBUNIT = 181,
    EE_KEY_KP_LEFTPAREN = 182,
    EE_KEY_KP_RIGHTPAREN = 183,
    EE_KEY_KP_LEFTBRACE = 184,
    EE_KEY_KP_RIGHTBRACE = 185,
    EE_KEY_KP_TAB = 186,
    EE_KEY_KP_BACKSPACE = 187,
    EE_KEY_KP_A = 188,
    EE_KEY_KP_B = 189,
    EE_KEY_KP_C = 190,
    EE_KEY_KP_D = 191,
    EE_KEY_KP_E = 192,
    EE_KEY_KP_F = 193,
    EE_KEY_KP_XOR = 194,
    EE_KEY_KP_POWER = 195,
    EE_KEY_KP_PERCENT = 196,
    EE_KEY_KP_LESS = 197,
    EE_KEY_KP_GREATER = 198,
    EE_KEY_KP_AMPERSAND = 199,
    EE_KEY_KP_DBLAMPERSAND = 200,
    EE_KEY_KP_VERTICALBAR = 201,
    EE_KEY_KP_DBLVERTICALBAR = 202,
    EE_KEY_KP_COLON = 203,
    EE_KEY_KP_HASH = 204,
    EE_KEY_KP_SPACE = 205,
    EE_KEY_KP_AT = 206,
    EE_KEY_KP_EXCLAM = 207,
    EE_KEY_KP_MEMSTORE = 208,
    EE_KEY_KP_MEMRECALL = 209,
    EE_KEY_KP_MEMCLEAR = 210,
    EE_KEY_KP_MEMADD = 211,
    EE_KEY_KP_MEMSUBTRACT = 212,
    EE_KEY_KP_MEMMULTIPLY = 213,
    EE_KEY_KP_MEMDIVIDE = 214,
    EE_KEY_KP_PLUSMINUS = 215,
    EE_KEY_KP_CLEAR = 216,
    EE_KEY_KP_CLEARENTRY = 217,
    EE_KEY_KP_BINARY = 218,
    EE_KEY_KP_OCTAL = 219,
    EE_KEY_KP_DECIMAL = 220,
    EE_KEY_KP_HEXADECIMAL = 221,

    EE_KEY_LCTRL = 224,
    EE_KEY_LSHIFT = 225,
    EE_KEY_LALT = 226, /**< alt, option */
    EE_KEY_LGUI = 227, /**< windows, command (apple), meta */
    EE_KEY_RCTRL = 228,
    EE_KEY_RSHIFT = 229,
    EE_KEY_RALT = 230, /**< alt gr, option */
    EE_KEY_RGUI = 231, /**< windows, command (apple), meta */

    EE_KEY_MODE = 257,    /**< I'm not sure if this is really not covered
                                 *   by any of the above, but since there's a
                                 *   special KMOD_MODE for it I'm adding it here
                                 */

    /* @} *//* Usage page 0x07 */

    /**
     *  \name Usage page 0x0C
     *
     *  These values are mapped from usage page 0x0C (USB consumer page).
     *  See https://usb.org/sites/default/files/hut1_2.pdf
     *
     *  There are way more keys in the spec than we can represent in the
     *  current scancode range, so pick the ones that commonly come up in
     *  real world usage.
     */
    /* @{ */

    EE_KEY_AUDIONEXT = 258,
    EE_KEY_AUDIOPREV = 259,
    EE_KEY_AUDIOSTOP = 260,
    EE_KEY_AUDIOPLAY = 261,
    EE_KEY_AUDIOMUTE = 262,
    EE_KEY_MEDIASELECT = 263,
    EE_KEY_WWW = 264,             /**< AL Internet Browser */
    EE_KEY_MAIL = 265,
    EE_KEY_CALCULATOR = 266,      /**< AL Calculator */
    EE_KEY_COMPUTER = 267,
    EE_KEY_AC_SEARCH = 268,       /**< AC Search */
    EE_KEY_AC_HOME = 269,         /**< AC Home */
    EE_KEY_AC_BACK = 270,         /**< AC Back */
    EE_KEY_AC_FORWARD = 271,      /**< AC Forward */
    EE_KEY_AC_STOP = 272,         /**< AC Stop */
    EE_KEY_AC_REFRESH = 273,      /**< AC Refresh */
    EE_KEY_AC_BOOKMARKS = 274,    /**< AC Bookmarks */

    /* @} *//* Usage page 0x0C */

    /**
     *  \name Walther keys
     *
     *  These are values that Christian Walther added (for mac keyboard?).
     */
    /* @{ */

    EE_KEY_BRIGHTNESSDOWN = 275,
    EE_KEY_BRIGHTNESSUP = 276,
    EE_KEY_DISPLAYSWITCH = 277, /**< display mirroring/dual display
                                           switch, video mode switch */
    EE_KEY_KBDILLUMTOGGLE = 278,
    EE_KEY_KBDILLUMDOWN = 279,
    EE_KEY_KBDILLUMUP = 280,
    EE_KEY_EJECT = 281,
    EE_KEY_SLEEP = 282,           /**< SC System Sleep */

    EE_KEY_APP1 = 283,
    EE_KEY_APP2 = 284,

    /* @} *//* Walther keys */

    /**
     *  \name Usage page 0x0C (additional media keys)
     *
     *  These values are mapped from usage page 0x0C (USB consumer page).
     */
    /* @{ */

    EE_KEY_AUDIOREWIND = 285,
    EE_KEY_AUDIOFASTFORWARD = 286,

    /* @} *//* Usage page 0x0C (additional media keys) */

    /**
     *  \name Mobile keys
     *
     *  These are values that are often used on mobile phones.
     */
    /* @{ */

    EE_KEY_SOFTLEFT = 287, /**< Usually situated below the display on phones and
                                      used as a multi-function feature key for selecting
                                      a software defined function shown on the bottom left
                                      of the display. */
    EE_KEY_SOFTRIGHT = 288, /**< Usually situated below the display on phones and
                                       used as a multi-function feature key for selecting
                                       a software defined function shown on the bottom right
                                       of the display. */
    EE_KEY_CALL = 289, /**< Used for accepting phone calls. */
    EE_KEY_ENDCALL = 290, /**< Used for rejecting phone calls. */

    /* @} *//* Mobile keys */

    /* Add any other keys here. */

    EE_NUM_KEY = 512 /**< not a key, just marks the number of scancodes
                                 for array bounds */
} EE_Key;

enum EE_MouseButton : unsigned int {
    EE_MOUSE_LEFT = 0,
    EE_MOUSE_MIDDLE,
    EE_MOUSE_RIGHT,

    // Not a key, just marks the number of buttons
    EE_NUM_BUTTONS
};

struct Vector2;

class Input
{
public:
	Input() = default;
	~Input() = default;

	// Process inputs being pressed by the user
	void ProcessInput();

	// Test if the key is pressed
	bool IsKeyDown(EE_Key key);

    bool IsMouseButtonDown(EE_MouseButton button);

    // Get the position of the mouse on the window
    Vector2 GetMousePos() const;
private:
    // State of each button on the mouse
    bool m_MouseState[3] = { false };

    // Detect the state of the mouse
    void DetectMouseButtonState(unsigned int event, bool value);
};

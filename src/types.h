#pragma once

#define WINDOW_TITLE_MAX_LENGTH 256
#define MAX_SPRITE_FRAME_COUNT 100

//
// Forward references to other structs that need a reference to these ones.
// See WarButtonComponent, WarState.building.
//
struct _GameContext;

typedef struct _GameSpriteFrame
{
    u8 dx;
    u8 dy;
    u8 w;
    u8 h;
    u32 off;
    u8* data;
} GameSpriteFrame;

typedef struct _GameSprite
{
    s32 image;
    s32 frameWidth;
    s32 frameHeight;
    s32 framesCount;
    GameSpriteFrame frames[MAX_SPRITE_FRAME_COUNT];
} GameSprite;

// Input
typedef enum _GameMouseButtons
{
    GAME_MOUSE_LEFT,
    GAME_MOUSE_RIGHT,

    GAME_MOUSE_COUNT
} GameMouseButtons;

typedef enum _GameKeys
{
    GAME_KEY_NONE,

    GAME_KEY_SPACE,
    GAME_KEY_APOSTROPHE,
    GAME_KEY_ASTERISK,
    GAME_KEY_PLUS,
    GAME_KEY_COMMA,
    GAME_KEY_MINUS,
    GAME_KEY_PERIOD,
    GAME_KEY_SLASH,

    GAME_KEY_0,
    GAME_KEY_1,
    GAME_KEY_2,
    GAME_KEY_3,
    GAME_KEY_4,
    GAME_KEY_5,
    GAME_KEY_6,
    GAME_KEY_7,
    GAME_KEY_8,
    GAME_KEY_9,

    GAME_KEY_SEMICOLON,
    GAME_KEY_EQUAL,

    GAME_KEY_A,
    GAME_KEY_B,
    GAME_KEY_C,
    GAME_KEY_D,
    GAME_KEY_E,
    GAME_KEY_F,
    GAME_KEY_G,
    GAME_KEY_H,
    GAME_KEY_I,
    GAME_KEY_J,
    GAME_KEY_K,
    GAME_KEY_L,
    GAME_KEY_M,
    GAME_KEY_N,
    GAME_KEY_O,
    GAME_KEY_P,
    GAME_KEY_Q,
    GAME_KEY_R,
    GAME_KEY_S,
    GAME_KEY_T,
    GAME_KEY_U,
    GAME_KEY_V,
    GAME_KEY_W,
    GAME_KEY_X,
    GAME_KEY_Y,
    GAME_KEY_Z,

    GAME_KEY_LEFT_BRACKET,
    GAME_KEY_BACKSLASH,
    GAME_KEY_RIGHT_BRACKET,
    GAME_KEY_GRAVE_ACCENT,

    GAME_KEY_ESC,
    GAME_KEY_ENTER,
    GAME_KEY_TAB,
    GAME_KEY_BACKSPACE,
    GAME_KEY_INSERT,
    GAME_KEY_DELETE,

    GAME_KEY_RIGHT,
    GAME_KEY_LEFT,
    GAME_KEY_DOWN,
    GAME_KEY_UP,

    GAME_KEY_PAGE_UP,
    GAME_KEY_PAGE_DOWN,
    GAME_KEY_HOME,
    GAME_KEY_END,

    GAME_KEY_F1,
    GAME_KEY_F2,
    GAME_KEY_F3,
    GAME_KEY_F4,
    GAME_KEY_F5,
    GAME_KEY_F6,
    GAME_KEY_F7,
    GAME_KEY_F8,
    GAME_KEY_F9,
    GAME_KEY_F10,
    GAME_KEY_F11,
    GAME_KEY_F12,

    GAME_KEY_SHIFT,
    GAME_KEY_CTRL,
    GAME_KEY_ALT,

    GAME_KEY_COUNT
} GameKeys;

typedef struct _GameKeyButtonState
{
    // indicates if the key is pressed in the current frame
    bool pressed;

    // indicate if the key was pressed in the previous frame
    bool wasPressed;
} GameKeyButtonState;

typedef struct _GameInput
{
    // current mouse position
    vec2 pos;

    // state of the mouse buttons
    GameKeyButtonState buttons[GAME_MOUSE_COUNT];

    // state of the keys
    GameKeyButtonState keys[GAME_KEY_COUNT];

    // drag
    bool isDragging;
    bool wasDragging;
    vec2 dragPos;
    rect dragRect;
} GameInput;

typedef struct _Paddle
{
    vec2 position;
    vec2 size;
    f32 speed;
} Paddle;

typedef struct _Ball
{
    vec2 position;
    vec2 size;
    vec2 dir;
    f32 speed;
} Ball;

typedef struct _GameContext
{
    f32 time;
    f32 deltaTime;
    u32 fps;

    bool paused;

    f32 globalScale;
    f32 globalSpeed;

    s32 originalWindowWidth;
    s32 originalWindowHeight;
    s32 windowWidth;
    s32 windowHeight;
    s32 framebufferWidth;
    s32 framebufferHeight;
    f32 devicePixelRatio;
    char windowTitle[WINDOW_TITLE_MAX_LENGTH];
    GLFWwindow* window;

    pthread_mutex_t __mutex;

    NVGcontext* gfx;
    ma_device sfx;

    GameInput input;

    Paddle paddles[2];
    Ball ball;
} GameContext;

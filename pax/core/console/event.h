#ifndef PX_CONSOLE_EVENT_H
#define PX_CONSOLE_EVENT_H

#include "import.h"

typedef enum PxConsoleEventType
{
    PX_CONSOLE_EVENT_NONE,

    PX_CONSOLE_EVENT_KEYBD_PRESS,
    PX_CONSOLE_EVENT_KEYBD_RELEASE,

    PX_CONSOLE_EVENT_MOUSE_PRESS,
    PX_CONSOLE_EVENT_MOUSE_RELEASE,
    PX_CONSOLE_EVENT_MOUSE_MOVE,
    PX_CONSOLE_EVENT_MOUSE_SCROLL,
}
PxConsoleEventType;

typedef enum PxConsoleEventModif
{
    PX_CONSOLE_NONE             = 0x0,
    PX_CONSOLE_MODIF_CTRL_LEFT  = 0x1,
    PX_CONSOLE_MODIF_CTRL_RIGHT = 0x2,
    PX_CONSOLE_MODIF_CTRL       = 0x3,
    PX_CONSOLE_MODIF_ALT_LEFT   = 0x4,
    PX_CONSOLE_MODIF_ALT_RIGHT  = 0x8,
    PX_CONSOLE_MODIF_ALT        = 0xc,
    PX_CONSOLE_MODIF_SHIFT      = 0x10,
}
PxConsoleEventModif;

typedef enum PxConsoleKeybdBtn
{
    PX_CONSOLE_KEYBD_NONE = 0,

    PX_CONSOLE_KEYBD_A,
    PX_CONSOLE_KEYBD_B,
    PX_CONSOLE_KEYBD_C,
    PX_CONSOLE_KEYBD_D,
    PX_CONSOLE_KEYBD_E,
    PX_CONSOLE_KEYBD_F,
    PX_CONSOLE_KEYBD_G,
    PX_CONSOLE_KEYBD_H,
    PX_CONSOLE_KEYBD_I,
    PX_CONSOLE_KEYBD_J,
    PX_CONSOLE_KEYBD_K,
    PX_CONSOLE_KEYBD_L,
    PX_CONSOLE_KEYBD_M,
    PX_CONSOLE_KEYBD_N,
    PX_CONSOLE_KEYBD_O,
    PX_CONSOLE_KEYBD_P,
    PX_CONSOLE_KEYBD_Q,
    PX_CONSOLE_KEYBD_R,
    PX_CONSOLE_KEYBD_S,
    PX_CONSOLE_KEYBD_T,
    PX_CONSOLE_KEYBD_U,
    PX_CONSOLE_KEYBD_V,
    PX_CONSOLE_KEYBD_W,
    PX_CONSOLE_KEYBD_X,
    PX_CONSOLE_KEYBD_Y,
    PX_CONSOLE_KEYBD_Z,

    PX_CONSOLE_KEYBD_ZERO,
    PX_CONSOLE_KEYBD_ONE,
    PX_CONSOLE_KEYBD_TWO,
    PX_CONSOLE_KEYBD_THREE,
    PX_CONSOLE_KEYBD_FOUR,
    PX_CONSOLE_KEYBD_FIVE,
    PX_CONSOLE_KEYBD_SIX,
    PX_CONSOLE_KEYBD_SEVEN,
    PX_CONSOLE_KEYBD_EIGHT,
    PX_CONSOLE_KEYBD_NINE,

    PX_CONSOLE_KEYBD_ENTER,
    PX_CONSOLE_KEYBD_ESCAPE,
    PX_CONSOLE_KEYBD_SPACE,
    PX_CONSOLE_KEYBD_BACK_SPACE,
    PX_CONSOLE_KEYBD_HORIZONTAL_TAB,
    PX_CONSOLE_KEYBD_ARROW_LEFT,
    PX_CONSOLE_KEYBD_ARROW_RIGHT,
    PX_CONSOLE_KEYBD_ARROW_UP,
    PX_CONSOLE_KEYBD_ARROW_DOWN,
    PX_CONSOLE_KEYBD_HOME,
    PX_CONSOLE_KEYBD_END,
    PX_CONSOLE_KEYBD_PAGE_UP,
    PX_CONSOLE_KEYBD_PAGE_DOWN,

    PX_CONSOLE_KEYBD_F1,
    PX_CONSOLE_KEYBD_F2,
    PX_CONSOLE_KEYBD_F3,
    PX_CONSOLE_KEYBD_F4,
    PX_CONSOLE_KEYBD_F5,
    PX_CONSOLE_KEYBD_F6,
    PX_CONSOLE_KEYBD_F7,
    PX_CONSOLE_KEYBD_F8,
    PX_CONSOLE_KEYBD_F9,
    PX_CONSOLE_KEYBD_F10,
    PX_CONSOLE_KEYBD_F11,
    PX_CONSOLE_KEYBD_F12,
}
PxConsoleKeybdBtn;

typedef enum PxConsoleMouseBtn
{
    PX_CONSOLE_MOUSE_NONE,
    PX_CONSOLE_MOUSE_LEFT,
    PX_CONSOLE_MOUSE_RIGHT,
    PX_CONSOLE_MOUSE_MIDDLE,
}
PxConsoleMouseBtn;

typedef struct PxConsoleEventKeybdPress
{
    pxiword button;
    pxuword modifs;
    pxi32   unicode;
}
PxConsoleEventKeybdPress;

typedef struct PxConsoleEventKeybdRelease
{
    pxiword button;
    pxuword modifs;
    pxi32   unicode;
}
PxConsoleEventKeybdRelease;

typedef struct PxConsoleEventMousePress
{
    pxiword button;
    pxuword modifs;
}
PxConsoleEventMousePress;

typedef struct PxConsoleEventMouseRelease
{
    pxiword button;
    pxuword modifs;
}
PxConsoleEventMouseRelease;

typedef struct PxConsoleEventMouseMove
{
    pxiword x;
    pxiword y;
}
PxConsoleEventMouseMove;

typedef struct PxConsoleEventMouseScroll
{
    pxiword x;
    pxiword y;
}
PxConsoleEventMouseScroll;

typedef struct PxConsoleEvent
{
    PxConsoleEventType type;

    union
    {
        PxConsoleEventKeybdPress   keybd_press;
        PxConsoleEventKeybdRelease keybd_release;

        PxConsoleEventMousePress   mouse_press;
        PxConsoleEventMouseRelease mouse_release;
        PxConsoleEventMouseMove    mouse_move;
        PxConsoleEventMouseScroll  mouse_scroll;
    };
}
PxConsoleEvent;

#endif // PX_CONSOLE_EVENT_H

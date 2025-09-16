#ifndef PX_CORE_BASE_DEFINE_H
#define PX_CORE_BASE_DEFINE_H

#define pxas(t, x) ((t)(x))

#define pxvargs(t, ...) (t[]) {__VA_ARGS__}

#define pxsize(x) pxas(pxiword, sizeof(x))

#define pxarraylen(t, x) \
    pxas(pxiword, sizeof(x) / sizeof(t))

#define pxvargslen(t, ...) \
    pxas(pxiword, sizeof(pxvargs(t, __VA_ARGS__)) / sizeof(t))

#define pxmin(x, y) ((x) < (y) ? (x) : (y))
#define pxmax(x, y) ((x) < (y) ? (y) : (x))

#define pxbetween(x, l, r) pxmax(l, pxmin(x, r))

#endif // PX_CORE_BASE_DEFINE_H

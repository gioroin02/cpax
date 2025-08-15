#ifndef PX_BASE_DEFINE_H
#define PX_BASE_DEFINE_H

#define __px_string__(x) # x
#define px_string(x)     __px_string__(x)

#define __px_concat__(x, y) x ## y
#define px_concat(x, y)    __px_concat__(x, y)

#define px_as(t, x) ((t)(x))

#define px_size(x)        px_as(pxint, sizeof (x))
#define px_size_string(x) px_as(pxint, sizeof(x) - 1)

#define px_min(x, y) ((x) < (y) ? (x) : (y))
#define px_max(x, y) ((x) < (y) ? (y) : (x))

#define px_clamp(x, l, r) px_max(l, px_min(x, r))

#endif // PX_BASE_DEFINE_H

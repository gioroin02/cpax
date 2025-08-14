#ifndef PAX_BASE_DEFINE_H
#define PAX_BASE_DEFINE_H

//
// Defines
//

#define __pax_string__(x) # x
#define pax_string(x)     __pax_string__(x)

#define __pax_concat__(x, y) x ## y
#define pax_concat(x, y)    __pax_concat__(x, y)

#define pax_as(t, x) ((t)(x))

#define pax_size(x) pax_as(Int, sizeof x)

#endif // PAX_BASE_DEFINE_H

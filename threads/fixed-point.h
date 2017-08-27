#ifndef THREADS_FIXED_POINT_H
#define THREADS_FIXED_POINT_H

#define FIX_F (1 << 14)

#define fix_fraction(a, b) (((a) * FIX_F) / (b))
#define fix_to_int(x) (((x) >= 0) \
                       ? (((x) + FIX_F / 2) / FIX_F) \
                       : (((x) - FIX_F / 2) / FIX_F))

#define fix_inc(x) ((x) + FIX_F)
#define fix_add_mixed(x, n) ((x) + ((n) * FIX_F))
#define fix_sub_mixed(x, n) ((x) - ((n) * FIX_F))

#define fix_mul(x, y) (((int64_t) (x)) * (y) / FIX_F)
#define fix_div(x, y) (((int64_t) (x)) * FIX_F / (y))

#endif /* threads/fixed_point.h */


typedef struct {
    char data[96];
} __attribute__((aligned(32))) Imath_2_5_V3f;

Imath_2_5_V3f const *Imath_2_5_V3f_normalize(
    Imath_2_5_V3f *self);

Imath_2_5_V3f Imath_2_5_V3f_normalized(
    Imath_2_5_V3f const *self);

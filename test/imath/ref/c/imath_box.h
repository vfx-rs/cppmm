
typedef struct Imath_2_5_V3f;
typedef struct {
    char data[192];
} __attribute__((aligned(32))) Imath_2_5_Box3f;
typedef struct {
    char data[192];
} __attribute__((aligned(32))) Imath_2_5_Box3i;

void Imath_2_5_Box3f_extendBy(
    Imath_2_5_Box3f *self
    , Imath_2_5_V3f const *point);

void Imath_2_5_Box3f_extendBy(
    Imath_2_5_Box3f *self
    , Imath_2_5_Box3f const *box);

void Imath_2_5_Box3i_extendBy(
    Imath_2_5_Box3i *self
    , Imath_2_5_Box3i const *box);

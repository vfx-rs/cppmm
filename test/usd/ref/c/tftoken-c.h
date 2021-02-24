
typedef struct pxrInternal_v0_20__pxrReserved___TfToken_s {
    char data[8];
} __attribute__((aligned(8))) pxrInternal_v0_20__pxrReserved___TfToken;


void pxrInternal_v0_20__pxrReserved___TfToken_copy(
    pxrInternal_v0_20__pxrReserved___TfToken * self
    , pxrInternal_v0_20__pxrReserved___TfToken const * rhs);


pxrInternal_v0_20__pxrReserved___TfToken * pxrInternal_v0_20__pxrReserved___TfToken_assign(
    pxrInternal_v0_20__pxrReserved___TfToken * self
    , pxrInternal_v0_20__pxrReserved___TfToken const * rhs);


void pxrInternal_v0_20__pxrReserved___TfToken_destruct(
    pxrInternal_v0_20__pxrReserved___TfToken * self);


void pxrInternal_v0_20__pxrReserved___TfToken_from_string(
    pxrInternal_v0_20__pxrReserved___TfToken * self
    , char * s);


unsigned long pxrInternal_v0_20__pxrReserved___TfToken_Hash(
    pxrInternal_v0_20__pxrReserved___TfToken const * self);


unsigned long pxrInternal_v0_20__pxrReserved___TfToken_size(
    pxrInternal_v0_20__pxrReserved___TfToken const * self);


char * pxrInternal_v0_20__pxrReserved___TfToken_GetText(
    pxrInternal_v0_20__pxrReserved___TfToken const * self);


char * pxrInternal_v0_20__pxrReserved___TfToken_data(
    pxrInternal_v0_20__pxrReserved___TfToken const * self);


_Bool pxrInternal_v0_20__pxrReserved___TfToken_operator==(
    pxrInternal_v0_20__pxrReserved___TfToken const * self
    , pxrInternal_v0_20__pxrReserved___TfToken const * o);


_Bool pxrInternal_v0_20__pxrReserved___TfToken_operator!=(
    pxrInternal_v0_20__pxrReserved___TfToken const * self
    , pxrInternal_v0_20__pxrReserved___TfToken const * o);


_Bool pxrInternal_v0_20__pxrReserved___TfToken_eq_string(
    pxrInternal_v0_20__pxrReserved___TfToken const * self
    , char * o);


_Bool pxrInternal_v0_20__pxrReserved___TfToken_neq_string(
    pxrInternal_v0_20__pxrReserved___TfToken const * self
    , char * o);


_Bool pxrInternal_v0_20__pxrReserved___TfToken_operator_(
    pxrInternal_v0_20__pxrReserved___TfToken const * self
    , pxrInternal_v0_20__pxrReserved___TfToken const * r);


_Bool pxrInternal_v0_20__pxrReserved___TfToken_IsEmpty(
    pxrInternal_v0_20__pxrReserved___TfToken const * self);


_Bool pxrInternal_v0_20__pxrReserved___TfToken_IsImmortal(
    pxrInternal_v0_20__pxrReserved___TfToken const * self);










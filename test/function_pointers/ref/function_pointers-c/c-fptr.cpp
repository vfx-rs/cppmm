#include <c-fptr_private.h>


void fptr_takes_ages(
    fptr_ProgressCallback_t cb
    , void * data)
{
    fptr::takes_ages(cb, data);
}

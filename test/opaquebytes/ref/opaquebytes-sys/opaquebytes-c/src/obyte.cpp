#include "obyte_private.h"


#include <stdexcept>

OPAQUEBYTES_CPPMM_API unsigned int obyte__Foo_sizeof()
{
        return sizeof(obyte::Foo);
}

OPAQUEBYTES_CPPMM_API unsigned int obyte__Foo_alignof()
{
        return alignof(obyte::Foo);
}


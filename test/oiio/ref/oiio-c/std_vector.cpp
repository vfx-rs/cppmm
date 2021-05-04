#include <std_vector_private.h>

#include <new>

unsigned int std__vector_std__string__vector(
    std_vector_string_t * * this_)
{
    try {
        to_c(this_, new std::vector<std::string>());
        return 0;
    } catch (std::exception& e) {
        return -1;
    }
}
unsigned int std__vector_std__string__dtor(
    std_vector_string_t * this_)
{
    try {
        delete to_cpp(this_);
        return 0;
    } catch (std::exception& e) {
        return -1;
    }
}

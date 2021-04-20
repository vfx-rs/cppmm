#include <fptr.hpp>

#include <cppmm_bind.hpp>

namespace cppmm_bind {

namespace fptr {

// typedef bool (*ProgressCallback)(void* opaque_data, float portion_done);
using ProgressCallback = ::fptr::ProgressCallback;

inline void takes_ages(::fptr::ProgressCallback cb, void* data);

} // namespace fptr

} // namespace cppmm_bind

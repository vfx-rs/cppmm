#pragma once

namespace fptr {

typedef bool (*ProgressCallback)(void* opaque_data, float portion_done);

inline void takes_ages(ProgressCallback cb, void* data) {}

} // namespace fptr

#pragma once

#include <unistd.h>

namespace fptr {

typedef bool (*ProgressCallback)(void* opaque_data, float portion_done);

inline void takes_ages(ProgressCallback cb, void* data) {
    const int steps = 10;
    for (int i = 0; i < steps + 1; ++i) {
        float pc = float(i) / float(steps);
        cb(data, pc);
    }
}

} // namespace fptr

#include "cppmm.h"

#include <string>
#include <vector>

namespace cppmm {

class VecString {
    std::vector<std::string> _vec;

public:
    VecString() {}
    VecString(std::vector<std::string>&& vec) : _vec(std::move(vec)) {}

    const std::string& get(int i) const { return _vec[i]; }

    const int size() const { return _vec.size(); }
};

} // namespace cppmm

CPPMM_API int cppmm_VecString_size(const cppmm_VecString* self) {
    const std::vector<std::string>& vec =
        *reinterpret_cast<const std::vector<std::string>*>(self);
    return vec.size();
}

CPPMM_API const char* cppmm_VecString_get(const cppmm_VecString* self,
                                          int index) {
    const std::vector<std::string>& vec =
        *reinterpret_cast<const std::vector<std::string>*>(self);
    return vec[index].c_str();
}

CPPMM_API void cppmm_VecString_destroy(const cppmm_VecString* self) {
    // move the vec out of our C wrapper then just let it drop to call the
    // destructor
    const std::vector<std::string> vec =
        std::move(*reinterpret_cast<const std::vector<std::string>*>(self));
}

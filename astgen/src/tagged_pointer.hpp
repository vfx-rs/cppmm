#pragma once

// pbrt is Copyright(c) 1998-2020 Matt Pharr, Wenzel Jakob, and Greg Humphreys.
// The pbrt source code is licensed under the Apache License, Version 2.0.
// SPDX: Apache-2.0

// #include <pbrt/pbrt.h>
// #include <pbrt/util/check.h>
// #include <pbrt/util/containers.h>
// #include <pbrt/util/print.h>

#include <algorithm>
#include <string>
#include <type_traits>

namespace cppmm {

namespace detail {

// TypePack Definition
template <typename... Ts>
struct TypePack {
    static constexpr size_t count = sizeof...(Ts);
};

// TypePack Operations
template <typename F, typename... Ts>
void ForEachType(F func, TypePack<Ts...>);

template <typename F>
void ForEachType(F func, TypePack<>) {}

template <typename F, typename T, typename... Ts>
void ForEachType(F func, TypePack<T, Ts...>) {
    func.template operator()<T>();
    ForEachType(func, TypePack<Ts...>());
}

template <typename T>
struct MaxSize;
template <typename T>
struct MaxSize<TypePack<T>> {
    static constexpr size_t size = sizeof(T);
};
template <typename T, typename... Ts>
struct MaxSize<TypePack<T, Ts...>> {
    static constexpr size_t size = (sizeof(T) > MaxSize<TypePack<Ts...>>::size)
                                       ? sizeof(T)
                                       : MaxSize<TypePack<Ts...>>::size;
};

template <typename... Ts>
struct Prepend;
template <typename T, typename... Ts>
struct Prepend<T, TypePack<Ts...>> {
    using type = TypePack<T, Ts...>;
};

template <typename T>
struct RemoveFirst {};
template <typename T, typename... Ts>
struct RemoveFirst<TypePack<T, Ts...>> {
    using type = TypePack<Ts...>;
};

template <typename T>
struct GetFirst {};
template <typename T, typename... Ts>
struct GetFirst<TypePack<T, Ts...>> {
    using type = T;
};

template <int index, typename T, typename... Ts>
struct RemoveFirstN;
template <int index, typename T, typename... Ts>
struct RemoveFirstN<index, TypePack<T, Ts...>> {
    using type = typename RemoveFirstN<index - 1, TypePack<Ts...>>::type;
};
template <typename T, typename... Ts>
struct RemoveFirstN<0, TypePack<T, Ts...>> {
    using type = TypePack<T, Ts...>;
};

template <int index, typename T, typename... Ts>
struct TakeFirstN;
template <int index, typename T, typename... Ts>
struct TakeFirstN<index, TypePack<T, Ts...>> {
    using type =
        typename Prepend<T, typename TakeFirstN<index - 1, TypePack<Ts...>>::type>::type;
};
template <typename T, typename... Ts>
struct TakeFirstN<1, TypePack<T, Ts...>> {
    using type = TypePack<T>;
};

template <typename T, typename... Ts>
struct HasType {};
template <typename T>
struct HasType<T, TypePack<void>> {
    static constexpr bool value = false;
};
template <typename T, typename Tfirst, typename... Ts>
struct HasType<T, TypePack<Tfirst, Ts...>> {
    static constexpr bool value =
        (std::is_same<T, Tfirst>::value || HasType<T, TypePack<Ts...>>::value);
};
// TaggedPointer Helper Templates
template <typename Enable, typename T, typename... Ts>
struct TypeIndexHelper_impl;

template <typename T, typename... Ts>
struct TypeIndexHelper_impl<void, T, T, Ts...> {
    static constexpr size_t value = 1;
};

template <typename T, typename U, typename... Ts>
struct TypeIndexHelper_impl<
    typename std::enable_if_t<std::is_base_of<U, T>::value &&
                              !std::is_same<T, U>::value>,
    T, U, Ts...> {
    static constexpr size_t value = 1;
};

template <typename T, typename U, typename... Ts>
struct TypeIndexHelper_impl<
    typename std::enable_if_t<!std::is_base_of<U, T>::value &&
                              !std::is_same<T, U>::value>,
    T, U, Ts...> {
    static constexpr size_t value =
        1 + TypeIndexHelper_impl<void, T, Ts...>::value;
};

template <typename T, typename... Ts>
class TypeIndexHelper : public TypeIndexHelper_impl<void, T, Ts...> {};

template <int n> struct DispatchSplit;

template <> struct DispatchSplit<1> {
    template <typename F, typename Tp, typename... Ts>
     inline auto operator()(F func, Tp tp, int tag,
                                        TypePack<Ts...> types) {
        // DCHECK_EQ(1, tag);
        static_assert(sizeof...(Ts) == 1);
        using T = typename GetFirst<TypePack<Ts...>>::type;
        return func(tp.template Cast<T>());
    }
};

template <int n> struct DispatchSplit {
    template <typename F, typename Tp, typename... Ts>
     inline auto operator()(F func, Tp tp, int tag,
                                        TypePack<Ts...> types) {
        constexpr int mid = n / 2;

        if (tag - 1 < mid) // 0-based indexing here to be more traditional
            return DispatchSplit<mid>()(
                func, tp, tag,
                typename TakeFirstN<mid, TypePack<Ts...>>::type());
        else
            return DispatchSplit<n - mid>()(
                func, tp, tag - mid,
                typename RemoveFirstN<mid, TypePack<Ts...>>::type());
    }
};

// FIXME: can we at least DispatchCRef this from the caller and dispatch based
// on whether F's return type is a const reference?
//
// https://stackoverflow.com/a/41538114 :-p

template <int n> struct DispatchSplitCRef;

template <> struct DispatchSplitCRef<1> {
    template <typename F, typename Tp, typename... Ts>
     inline auto operator()(F func, Tp tp, int tag,
                                        TypePack<Ts...> types) -> auto&& {
        // DCHECK_EQ(1, tag);
        static_assert(sizeof...(Ts) == 1);
        using T = typename GetFirst<TypePack<Ts...>>::type;
        return func(tp.template Cast<T>());
    }
};

template <int n> struct DispatchSplitCRef {
    template <typename F, typename Tp, typename... Ts>
     inline auto operator()(F func, Tp tp, int tag,
                                        TypePack<Ts...> types) -> auto&& {
        constexpr int mid = n / 2;

        if (tag - 1 < mid) // 0-based indexing here to be more traditional
            return DispatchSplitCRef<mid>()(
                func, tp, tag,
                typename TakeFirstN<mid, TypePack<Ts...>>::type());
        else
            return DispatchSplitCRef<n - mid>()(
                func, tp, tag - mid,
                typename RemoveFirstN<mid, TypePack<Ts...>>::type());
    }
};

template <int n> struct DispatchSplitCPU;

template <> struct DispatchSplitCPU<1> {
    template <typename F, typename Tp, typename... Ts>
    inline auto operator()(F func, Tp tp, int tag, TypePack<Ts...> types) {
        // DCHECK_EQ(1, tag);
        static_assert(sizeof...(Ts) == 1);

        using T = typename GetFirst<TypePack<Ts...>>::type;
        return func(tp.template Cast<T>());
    }
};

template <int n> struct DispatchSplitCPU {
    template <typename F, typename Tp, typename... Ts>
    inline auto operator()(F func, Tp tp, int tag, TypePack<Ts...> types) {
        constexpr int mid = n / 2;

        if (tag - 1 < mid) // 0-based indexing here to be more traditional
            return DispatchSplitCPU<mid>()(
                func, tp, tag,
                typename TakeFirstN<mid, TypePack<Ts...>>::type());
        else
            return DispatchSplitCPU<n - mid>()(
                func, tp, tag - mid,
                typename RemoveFirstN<mid, TypePack<Ts...>>::type());
    }
};

} // namespace detail

// TaggedPointer Definition
template <typename... Ts> class TaggedPointer {
public:
    using Types = detail::TypePack<Ts...>;

    TaggedPointer() = default;

    template <typename T>  TaggedPointer(T* ptr) {
        uintptr_t iptr = reinterpret_cast<uintptr_t>(ptr);
        // Reminder: if this CHECK hits, it's likely that the class
        // involved needs an alignas(8).
        // DCHECK_EQ(iptr & ptrMask, iptr);
        constexpr uint16_t type = TypeIndex<T>();
        bits = iptr | ((uintptr_t)type << tagShift);
    }


    TaggedPointer(std::nullptr_t np) {}


    TaggedPointer(const TaggedPointer& t) { bits = t.bits; }

    TaggedPointer& operator=(const TaggedPointer& t) {
        bits = t.bits;
        return *this;
    }

    template <typename T>  bool is() const {
        return Tag() == TypeIndex<T>();
    }


    explicit operator bool() const { return (bits & ptrMask) != 0; }


    bool operator<(const TaggedPointer& tp) const { return bits < tp.bits; }

    template <typename T>  T* cast() {
        // DCHECK(Is<T>());
        return reinterpret_cast<T*>(ptr());
    }
    template <typename T>  const T* cast() const {
        // DCHECK(Is<T>());
        return reinterpret_cast<const T*>(ptr());
    }
    template <typename T>  T* cast_or_null() {
        if (is<T>())
            return reinterpret_cast<T*>(ptr());
        else
            return nullptr;
    }
    template <typename T>  const T* cast_or_null() const {
        if (is<T>())
            return reinterpret_cast<const T*>(ptr());
        else
            return nullptr;
    }


    uint16_t Tag() const { return uint16_t((bits & tagMask) >> tagShift); }

    static constexpr uint16_t MaxTag() { return sizeof...(Ts); }

    static constexpr uint16_t NumTags() { return MaxTag() + 1; }

    template <typename T>  static constexpr uint16_t TypeIndex() {
        return uint16_t(detail::TypeIndexHelper<T, Ts...>::value);
    }

    // std::string ToString() const {
    //     return StringPrintf("[ TaggedPointer ptr: 0x%p tag: %d ]", ptr(),
    //                         Tag());
    // }


    bool operator==(const TaggedPointer& tp) const { return bits == tp.bits; }

    bool operator!=(const TaggedPointer& tp) const { return bits != tp.bits; }


    void* ptr() { return reinterpret_cast<void*>(bits & ptrMask); }

    const void* ptr() const {
        return reinterpret_cast<const void*>(bits & ptrMask);
    }

    template <typename F>  inline auto Dispatch(F func) {
        // DCHECK(ptr() != nullptr);
        constexpr int n = MaxTag();
        return detail::DispatchSplit<n>()(func, *this, Tag(), Types());
    }

    template <typename F>  inline auto Dispatch(F func) const {
        // DCHECK(ptr() != nullptr);
        constexpr int n = MaxTag();
        return detail::DispatchSplit<n>()(func, *this, Tag(), Types());
    }

    template <typename F>
     inline auto DispatchCRef(F func) -> auto&& {
        // DCHECK(ptr() != nullptr);
        constexpr int n = MaxTag();
        return detail::DispatchSplitCRef<n>()(func, *this, Tag(), Types());
    }

    template <typename F>
     inline auto DispatchCRef(F func) const -> auto&& {
        // DCHECK(ptr() != nullptr);
        constexpr int n = MaxTag();
        return detail::DispatchSplitCRef<n>()(func, *this, Tag(), Types());
    }

    template <typename F> inline auto DispatchCPU(F func) {
        // DCHECK(ptr() != nullptr);
        constexpr int n = MaxTag();
        return detail::DispatchSplitCPU<n>()(func, *this, Tag(), Types());
    }

    template <typename F> inline auto DispatchCPU(F func) const {
        // DCHECK(ptr() != nullptr);
        constexpr int n = MaxTag();
        return detail::DispatchSplitCPU<n>()(func, *this, Tag(), Types());
    }

    template <typename F> static void ForEachType(F func) {
        detail::ForEachType(func, Types());
    }

private:
    static_assert(sizeof(uintptr_t) == 8, "Expected uintptr_t to be 64 bits");

    static constexpr int tagShift = 48;
    static constexpr uint64_t tagMask = (((1ull << 16) - 1) << tagShift);
    static constexpr uint64_t ptrMask = ~tagMask;

    uintptr_t bits = 0;
};

} // namespace cppmm

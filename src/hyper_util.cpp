#include <cstddef>
#include<utility>
#include<functional>
#include<array>

#define MULTISTAR_POINTER(T, D) decltype(multistar_pointer<T, D>::compile())

template<typename T, std::size_t D>
struct multistar_pointer {
    static constexpr auto compile() -> MULTISTAR_POINTER(T, D-1)* {
        return NULL;
    }

    using type = MULTISTAR_POINTER(T, D);
    using pre_type = MULTISTAR_POINTER(T, D-1);

    template<typename... Args>
    static void alloc(type &arr, std::function<void(T&)> func, std::size_t N, Args... args) {
        arr = new pre_type[N];
        for (std::size_t i = 0; i < N; i ++)
            multistar_pointer<T, D-1>::alloc(arr[i], func, args...);
    }

    template<typename... Args>
    static void dealloc(type arr, std::size_t N, Args... args) {
        for (std::size_t i = 0; i < N; i ++) 
            multistar_pointer<T, D-1>::dealloc(arr[i], args...);
        delete[] arr;
    }

    static void alloc_after_unpack(type &arr, std::function<void(T&)> func, const std::array<std::size_t, D> &sizes) {
        alloc_after_unpack_impl(arr, func, sizes, std::make_index_sequence<D>{});
    }

    static void dealloc_after_unpack(type arr, const std::array<std::size_t, D> &sizes) {
        dealloc_after_unpack_impl(arr, sizes, std::make_index_sequence<D>{});
    }

private:
    template<typename Array, std::size_t... I>
    static void alloc_after_unpack_impl(type &arr, std::function<void(T&)> func, const Array &sizes, std::index_sequence<I...>) {
        alloc(arr, func, sizes[I]...);
    }

    template<typename Array, std::size_t... I> 
    static void dealloc_after_unpack_impl(type arr, const Array &sizes, std::index_sequence<I...>) {
        dealloc(arr, sizes[I]...);
    }
};

template<typename T>
struct multistar_pointer<T, 1> {
    static constexpr T* compile() {
        return (T*)NULL;
    }
    
    using type = T*;
    using pre_type = T;

    template<typename... Args>
    static void alloc(T* &arr, std::function<void(T&)> func, std::size_t N, Args... args) {
        arr = new T[N];
        for (std::size_t i = 0; i < N; i ++)
            func(arr[i]);
    }

    template<typename... Args>
    static void dealloc(T *arr, Args... args) {
        delete[] arr;
    }

    static void alloc_after_unpack(T *&arr, std::function<void(T &)> func, const std::array<std::size_t, 1> &sizes) {
        alloc(arr, func, sizes[0]);
    }

    static void dealloc_after_unpack(T *arr, const std::array<std::size_t, 1> &sizes) {
        dealloc(arr, sizes[0]);
    }
};

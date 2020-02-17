#include<algorithm>
#include<functional>
#include"hyper_util.cpp"

template<typename T, std::size_t D>
class hyper_array {
    private:
        typename multistar_pointer<T, D>::type arr;
        std::array<std::size_t, D> sizes;

    public:
        template<typename... Args>
        hyper_array(std::function<void(T&)> func, Args... args) {
            multistar_pointer<T, D>::alloc(arr, func, args...);

            std::size_t idx = 0;
            ((sizes[idx++] = args), ...);
        }

        hyper_array(std::function<void(T&)> func, const std::array<std::size_t, D> &_sizes) {
            sizes = _sizes;
            multistar_pointer<T, D>::alloc_after_unpack(arr, func, sizes);
        }

        ~hyper_array() {
            multistar_pointer<T, D>::dealloc_after_unpack(arr, sizes);
        }

        auto &operator[](std::size_t idx) {
            return arr[idx];
        }

        std::size_t size(int dim) {
            return sizes[dim];
        }
};


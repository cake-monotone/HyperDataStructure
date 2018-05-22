#include<algorithm>
#include<functional>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"
template<typename T, size_t D>
struct return_type_generator {
    auto operator()(void* obj) {
        return return_type_generator<T*, D-1>()(obj);
    }
};

template<typename T>
struct return_type_generator<T, 1> {
    T operator()(void* obj) {
        return (T)obj;
    }
};

template<typename T, size_t D, T INIT_VAL = T()>
class hyper_array {
    private:
        void* arr;
        T init_val;
        std::vector<size_t> sizes;

        void init(void **init_arr, int N) {
            *init_arr = new T[N];
            for (int i = 0; i < N; i ++)
                ((T*)(*init_arr))[i] = INIT_VAL;
        }

        template<typename... Args>
        void init(void **init_arr, int N, Args... args) {
            *init_arr = new void*[N];
            for (int i = 0; i < N; i ++)
            init(&((void**)(*init_arr))[i], args...);
        }
        
        void set_size(int N) { sizes.push_back(N); }

        template<typename... Args>
        void set_size(int N, Args... args) {
            sizes.push_back(N);
            set_size(args...);
        }

    public:
        template<typename... Args>
        hyper_array(Args... args) : init_val() {
            init(&arr, args...);
            set_size(args...);
        }

        ~hyper_array() {
            // not yet..
            // 귀찮..

        }

        auto operator[](size_t idx) {
            return return_type_generator<T*, D>()(arr)[idx];
        }

        size_t size(int dim) {
            return sizes[dim-1];
        }
};
#pragma GCC diagnostic pop


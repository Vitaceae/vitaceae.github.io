#include <iostream>

template <typename T, std::size_t N>
constexpr std::size_t func(const T(&)[N]) {
    return N;
}

template <auto V>
struct ArrInfo {
    enum {
        SIZE = func(*V),
    };
};

int arr[] = {0, 1, 2};

int main(void) {

    std::cout << "size=" << ArrInfo<&arr>::SIZE << std::endl;

    return 0;
}

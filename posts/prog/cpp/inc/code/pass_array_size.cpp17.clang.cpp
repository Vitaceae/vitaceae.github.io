#include <iostream>

template <typename T, std::size_t N>
constexpr std::integral_constant<std::size_t, N> func(const T(&)[N]) {
    return {};
}

template <typename T, T V>
struct ArrInfo
{
    enum {
        SIZE = decltype(func(*std::declval<T>()))::value,
    };
};

static int arr[] = {0, 1, 2};

int main(void) {
    std::cout << "size=" << ArrInfo<decltype(&arr), &arr>::SIZE << std::endl;

    return 0;
}

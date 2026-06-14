#include <iostream>

//reference array + function template
template <typename T, std::size_t N>
constexpr std::size_t f1(T (&arr)[N]) {
    return N;
}

int main(void) {
    int arr[] = {0, 1, 2};

    std::cout << "size=" << f1(arr) << std::endl;

    return 0;
}

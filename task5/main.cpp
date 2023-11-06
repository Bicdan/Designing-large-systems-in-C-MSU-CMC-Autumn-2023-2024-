#include <type_traits>
#include <typeinfo>

template <typename... Types>
struct are_same;

template <typename T>
struct are_same<T> : std::true_type {};

template <typename T, typename U, typename... Rest>
struct are_same<T, U, Rest...> : std::conditional_t<std::is_same_v<std::decay_t<T>, std::decay_t<U>>, are_same<U, Rest...>, std::false_type> {};

template <typename... Types>
constexpr bool are_same_v = are_same<Types...>::value;

int main() {
    static_assert(are_same_v<int, int32_t, signed int>, "compile assert"); // Compiles successfully
    static_assert(are_same_v<int, double, int>, "compile assert"); // Fails compilation
    return 0;
}


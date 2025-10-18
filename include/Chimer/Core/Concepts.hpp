#include <concepts>
#include <iosfwd>

template<typename T>
concept Streamable = requires(std::ostream& os, T value) {
    { os << value } -> std::same_as<std::ostream&>;
};

template<typename T>
concept Callable = requires(T f) {
    { std::invoke(f) };
};
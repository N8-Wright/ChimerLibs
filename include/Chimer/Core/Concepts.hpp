#include <concepts>
#include <iosfwd>

template<typename T>
concept Streamable = requires(std::ostream& os, T value) {
    { os << value } -> std::same_as<std::ostream&>;
};
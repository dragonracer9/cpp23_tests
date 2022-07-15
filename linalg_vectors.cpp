#include <iostream>
#include <optional>
#include <type_traits>
#include <vector>
#include <cstdarg>
#include <concepts>

template<typename T>
concept Numeric = std::is_integral_v<T> or std::is_floating_point_v<T>;

namespace mat
{   
    // i trust these will only be used on numbers so i aint gonna sacrifice speed for security right? although probs would be better
    // actually maybe it rlly would be better
    // yk im too lazy, i wont
    // but as info, i rlly should
    template <Numeric T> 
    inline constexpr auto [[nodiscard]] sq(T x) { return x * x; }
    template <Numeric T>
    inline constexpr auto [[nodiscard]] cu(T x) { return sq(x) * x; }
    template <Numeric T>  
    inline constexpr auto [[nodiscard]] sign(T x) { return ((x) > 0) - ((x) < 0); }

    template <Numeric T, Numeric N>
    constexpr auto maybe_div(T x, N y)
    {
        if (y != 0)
            return std::optional<T>{x / y};
        return std::optional<T>{};
    }

    constexpr auto PI = 3.1415926535897932384626433832795;
    constexpr auto C = 0.5519150244935105707435627; // close enough

} // namespace mat

namespace lalg
{
    template <typename T> requires std::integral<T> or std::floating_point<T>
    class vector
    {
    public:
        constexpr vector(/* T l, T r */ std::initializer_list<T> l) noexcept : v(l /* {l, r} */)
        {
            //static_assert((std::is_integral<T>::value or std::is_floating_point<T>::value), "integer or float required");
        };
        constexpr vector(vector &&) = default;
        constexpr vector(const vector &) = default;
        constexpr vector &operator=(vector &&) = default; // imma be honest idk if this is a good idea lol
        vector &operator=(const vector &) = delete;
        ~vector() = default; // not rlly gonna dynamically do stuff am i?

        vector &operator+=(vector vec)
        {
            for (int i{}; i < 2; ++i)
            {
                v.at(i) += vec.v.at(i);
            }
            return *this;
        }

        vector &operator-=(vector vec)
        {
            for (int i{}; i < 2; ++i)
            {
                v.at(i) -= vec.v.at(i);
            }
            return *this;
        }

        friend std::ostream &operator<<(std::ostream &os, const vector &vec)
        {
            os << '{';
            for (int i{}; i < vec.v.size() - 1; ++i)
            {
                os << vec.v.at(i) << ", ";
            }
            os << vec.v.at(vec.v.size() - 1) << '}';
            return os;
        }

        const int dim() const noexcept
        {
            return 2;
        }

    private:
        std::vector<T> v;
    };

} // namespace linalg

int main(int argc, char const *argv[])
{
    using namespace lalg;

    vector<int> v{1, 1};

    std::cout << v << std::endl; // compile time creation of vector

    std::optional x{mat::maybe_div(10.0, 9)}; // compile time calculation

    //std::cout << mat::avg<double>(1, 3) << std::endl; // for clarification, this was a test of the ellipsis operator ... for function arguments. the fn has since been removed 

    if (x)
        std::cout << x.value() << std::endl;
    else
        std::cout << "div by 0" << std::endl;

    // vector<int*> p_v {nullptr, nullptr}; // should fail the static assert and not compile

    std::cout << mat::sq(100) << std::endl; // compile time calculation

    return 0;
}

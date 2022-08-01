#include <iostream>
#include <chrono>
#include <string_view>
#include <algorithm>

inline auto constexpr_out() -> void
{
    constexpr std::string_view s{std::move("1 2 3 4 5")};
    constexpr int s_len = s.size();
    for (int i{s_len}; i > 0; i -= 2)
    {
        std::cout << s.substr(0, i) << '\n';
    }
}

inline auto out() -> void
{
    for (std::string s{"1 2 3 4 5 "}; s.size() > 0; s = s.substr(0, s.size() - 2))
    {
        std::cout << s << "\n";
    }
}

inline auto out_const_size() -> void
{
    std::string s{"1 2 3 4 5 "};
    std::size_t s_len{s.size()};
    for (; s_len > 0; s = s.substr(0, (s_len -= 2)))
    {
        std::cout << s << "\n";
    }
}

auto main(int argc, char const *argv[]) -> int
{
    auto start = std::chrono::high_resolution_clock::now();
    constexpr_out();
    auto end = std::chrono::high_resolution_clock::now();
    auto time = duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Time taken (const): " << time.count() << " microseconds" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    out();
    end = std::chrono::high_resolution_clock::now();
    time = duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Time taken (original): " << time.count() << " microseconds" << std::endl; // turns out this is faster (by like 500 microseconds)

    start = std::chrono::high_resolution_clock::now();
    out_const_size();
    end = std::chrono::high_resolution_clock::now();
    time = duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Time taken (out_const_size): " << time.count() << " microseconds" << std::endl;

    return 0;
}

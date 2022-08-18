#include <iostream>
#include <vector>

using vec = std::vector<int>;

struct longest_increasing_subsequence
{
    int index;
    int length;
    bool value;
    operator bool() const
    {
        return value;
    }
};

using lis = longest_increasing_subsequence;

void read_input(vec &);
lis find_seq(const vec &);

int main(int argc, const char **argv)
{
    vec vals{};
    read_input(vals);
    const lis seq{find_seq(vals)};

    if (seq)
    {
        for (int i{seq.index}; i < seq.index + seq.length; ++i)
        {
            std::cout << vals.at(i) << ' ';
        }
    }
    else
        std::cout << "empty" << std::endl;

    return 0;
}

void read_input(vec &input)
{
    int in{};
    while (std::cin >> in)
    {
        if (in < 0)
            break;
        input.push_back(in);
    }
}

[[nodiscard]] lis find_seq(const vec &input)
{
    if (input.size() == 0)
        return lis{0, 0, false};
    else
    {
        int index{}, length{}, largest_length{}, mark_first{};
        for (auto current_index{1}; current_index < input.size(); ++current_index)
        {
            if (input.at(current_index) > input.at(current_index - 1)) continue;
            length = current_index - mark_first;
            if (length > largest_length) {
                largest_length = length;
                index = current_index - length;
            }
            mark_first = current_index;
        }
        return lis{index, length, true};
    }
}
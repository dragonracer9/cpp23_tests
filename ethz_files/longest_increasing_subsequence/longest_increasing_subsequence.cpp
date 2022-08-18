#include <iostream>
#include <vector>

using vec = std::vector<int>;

struct longest_increasing_subsequence
{
    int index;
    int length;
    bool value;
    operator bool() const { return value; }
};

using lis = longest_increasing_subsequence;

void read_input(vec &);
lis find_seq(const vec &);

int main(int argc, const char **argv)
{
    vec vals{};
    read_input(vals);
    const lis SEQ{find_seq(vals)};

    if (SEQ)
    {
        for (int i{SEQ.index}; i < SEQ.index + SEQ.length; ++i)
        {
            std::cout << vals.at(i) << ' ';
        }
    } else std::cout << "empty" << std::endl;

    return 0;
}

/**
 * @brief reads vector from std::cin
 * 
 * @param input vector<int> &
 */
void read_input(vec &input)
{
    int in{};
    while (std::cin >> in)
    {
        if (in < 0) break;
        input.push_back(in);
    }
}

/**
 * @brief finds largest strictly increasing sequence in a vector of integers
 * 
 * @param input const vector<int> &
 * @return lis (largest_increasing_sequence)
 */
[[nodiscard]] lis find_seq(const vec &input)
{
    if (input.size() == 0) return lis{0, 0, false};
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
        // std::cout << index << ' ' << length << '\n';
        return lis{index, largest_length, true};
    }
}
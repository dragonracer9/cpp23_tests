#include "run_length.hpp"

inline void error(void) {std::cout << "error";}

void decode()
{
  //implement decode function
  // NOTE: do not printout new line (i.e., std::endl or '\n')
  int len{};
  int val{};
  std::cout << 0 << ' ';

  while ((std::cin >> len) && len != -1)
  {
    std::cin >> val;
    if ((len < 0 || len > 255) || (val < 0 || val > 255)) 
    {
        std::cout << "error";
        return;
    }

    for (int i{len}; i > 0; --i) std::cout << val << ' ';    
  }
  std::cout << -1;
}


void encode()
{
  // implement encode function
  // NOTE: do not printout new line (i.e., std::endl or '\n')
  int val{}, prev_vl{}, len{1};
  std::cout << 1 << ' ';

  std::cin >> prev_vl;
  if (prev_vl > 255 || prev_vl < 0)
  {
    std::cout << "error";
    return;
  }
  //std::cout << prev_vl << '\n';
  while((std::cin >> val) && val != -1)
  {
    //std::cout << val << '\n';
    if (prev_vl > 255 || prev_vl < 0)
    {
        error();
        return;
    } else if (val == prev_vl)
    {
        if (++len > 255)
        {
            std::cout << len - 1 << ' ' << val << ' ';
            len = 1;
        }
    } else {
        std::cout << len << ' ' << prev_vl << ' ';
        prev_vl = val;
        len = 1;
    }
    if (val > 255 or val < 0)
    {
        error();
        return;
    }
  }
  std::cout << len << ' ' << prev_vl << ' ';
  std::cout << -1;
}

/*
Task

Run-length encoding is a simple data compression technique that represents
consecutive identical values (a run) by a tuple

. This method is applied for image compression, for instance. Example:

Image

Write a program that implements run-length encoding and decoding of a byte sequence as described above. By a byte, we mean an integer value in the range [0; 255]

. Use the stepwise refinement method to implement the program. Your solution must consist of at least two functions, encode and decode. Please implement them in run_length.cpp

The input is structured as follows:

    One integer that determines whether to encode: 0

or decode: 1
.
Byte sequence to be encoded or decoded (of arbitrary length). If a value outside the range
(except -1) is entered, output error and stop the en- or decoding.

Integer -1 signaling the end of the byte sequence. Any extra input should be ignored.

For the example above, the inputs are:

Encode:

0 42 42 85 85 85 85 172 172 172 13 13 42 -1

Decode:

1 2 42 4 85 3 172 2 13 1 42 -1

The output is expected on a single line in the following format:

    A start value to indicate the begin of the sequence: either 

0 for decoded values or
1 for encoded values.
The values that make up the encoded or decoded byte sequence.
The value -1 to indicate the end of the sequence.

I.e., you can 'reuse' the output as the input.

Note 1): As the encoded sequence must be a byte sequence, runs of length 256 or longer need to be split into multiple runs of length 255 at most.

Note 2): the first input element (the integer that determines wether to encode or decode), is already consumed by the main, that calls either the encode or decode function.

Note 3): your output should not be followed by new line (i.e., do not use std::endl or \n at the end of your printout)

Note 4): the program will print your output (the result of the decoding or encoding), surrounded by asterisks. You don't have to worry about them, the autograder can safely recognize your solution

Special cases: While decoding a byte sequence two special cases can occur. These must be handled as follows:

    If a byte sequence ends in the middle of a tuple, stop printing the output of en- or decoding and output error.
    Tuples of run-length 0 are possible. For such tuples, output only the leading indicator (

/) and the trailing

    .

Hint: You can enter multiple numbers at once separated with a space on the console, e.g, you can copy and paste the above examples, and sequentially read them using multiple std::cin >> _var_ calls.

Also note that, even though the program's output and the user input are both shown in the same console, they are processed separately internally, so you do not have to worry that the two will mix: if your program outputs something to the console before reading another value, it will only read the user input and not the previous output value. See the Calculator code in the Lecture 4 handout for an example of reading input and producing output in a loop.

Restrictions: using a vector, an array or a similar data structure in any part of your code is not allowed and would result in 0 points.
*/
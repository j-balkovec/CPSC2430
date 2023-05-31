## Radix Sort [C++]

We are given an pre-defined array of intigers:
```
constexpr int const ARR_SIZE = 6;
std::array<int, ARR_SIZE> = { 261, 777, 659, 55, 432, 43 };
```

First we find the maximum element in the array. If we are using `std::array<T, S>` we can utilize the `std::maxelement()` to find it. This will help determine the number of digits to consider during sorting. In our case the maximum element is `777`.

Now we perform the counting sort for each digit, starting from the least significant digit (rightmost) to the most significant digit (leftmost).

#TODO


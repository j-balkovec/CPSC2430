## Radix Sort [C++]

We are given an pre-defined array of intigers:
```
constexpr int const ARR_SIZE = 6;
std::array<int, ARR_SIZE> = { 261, 777, 659, 55, 432, 43 };
```

First we find the maximum element in the array. If we are using `std::array<T, S>` we can utilize the `std::maxelement()` to find it. This will help determine the number of digits to consider during sorting. In our case the maximum element is `777`.

Now we perform the counting sort for each digit, starting from the least significant digit (rightmost) to the most significant digit (leftmost). We first need to determine the range of values for each digit. Since we are dealing with integers, the range is from `0` to `9` for each digit. We will create a counting array to store the count of occurrences of each digit.

### Table representation of Counting Sort

| Step | Array                       | Counting Array       | Updated Array                |
|------|-----------------------------|----------------------|------------------------------|
| 1    | 261 777 659 55 432 43       | 0 0 0 0 0 0 0 0 0 0   |                              |
| 2    |                             | 1 1 1 1 1 0 0 0 0 0   |                              |
| 3    | 261 777 659 55 432 43       | 1 1 1 2 1 1 0 0 0 0   |                              |
| 4    |                             | 2 1 1 2 1 1 0 0 0 0   |                              |
| 5    | 261 777 659 55 432 43       | 2 1 1 2 1 1 1 0 0 0   |                              |
| 6    |                             | 2 1 1 2 1 1 2 0 0 0   |                              |
| 7    | 261 777 659 55 432 43       | 2 1 1 2 1 1 2 0 0 1   |                              |
| 8    |                             | 2 1 1 2 1 1 2 0 0 2   |                              |
| 9    | 261 777 659 55 432 43       | 2 1 1 2 1 1 2 0 0 3   |                              |
| 10   |                             | 2 1 1 2 1 1 2 0 0 4   |                              |
| 11   | 261 777 659 55 432 43       | 2 1 1 2 1 1 2 0 0 4   | 43 432 55 659 777 261        |


Next, we will perform our final step, which is **radix sort**. We will start from the least significant digit and move towards the most significant digit.

### Table representation of Radix Sort

| Step | Array                       | Updated Array                |
|------|-----------------------------|------------------------------|
| 1    | 43 432 55 659 777 261       |                              |
| 2    | 43 261 432 55 659 777       |                              |
| 3    | 43 55 261 432 659 777       |                              |
| 4    | 43 55 261 432 659 777       | 43 55 261 432 659 777        |

After performing radix sort, the final sorted array is:

`std::array<int, ARR_SIZE> = { 43, 55, 261, 432, 659, 777 }; //[sorted array]`

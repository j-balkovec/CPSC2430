/**
* \brief Radix Sort C++ implementation
* 
* {
* Auxilary space: [O(n + b)] where [n] is the number of elements in the input array and [b] is the base. 
* Time complexity: O(d * (n + b)), where [n] is the number of elements in the input array
*                                        [d] is the number of digits in the maximum element
*                                        [b] is the base (usually 10 for decimal numbers).
* }
*
* \file radix.py
* \author Jakob Balkovec
*/

//{
// PRO: Radix sort is a stable sorting algorithm that means that the relative order 
//       of elements with equal values is preserved during the sorting process. 
// 
// CON: The space complexity [O(n + b)] of radix sort is influenced by the number of elements
//       and the base used (usually 10 for decimal numbers). As the input grows larger and larger
//       more memory and space is required to sort the array/container.
//
//       Therefore radix sort is not prefered for sorting large data-sets
//}


//{
// Use of templates is preffered since it allows us to parse any typo at argument into the sorting function
//}

#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std::chrono;

// function to get the maximum element in the array
template <typename T>
T getMax(const std::vector<T>& arr) {
    T max = arr[0];
    for (size_t i = 1; i < arr.size(); i++) {
        if (arr[i] > max)
            max = arr[i];
    }
    return max;
}

// using counting sort to sort elements based on significant place
template <typename T>
void countingSort(std::vector<T>& arr, int exp) {
    int n = arr.size();
    std::vector<T> output(n);
    std::vector<int> count(10, 0);

    // store the count of occurrences in count[]
    for (int i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    // change count[i] so that count[i] now contains the
    // actual position of this digit in output[]
    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    // build the output array
    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    // copy the output array to arr[] so that arr[] contains
    // sorted numbers according to the current digit
    std::copy(output.begin(), output.end(), arr.begin());
}

// sort
template <typename T>
void radixSort(std::vector<T>& arr) {
    T max = getMax(arr);

    for (int exp = 1; max / exp > 0; exp *= 10)
        countingSort(arr, exp);
}

template <typename T>
void printArray(const std::vector<T>& arr) {
    std::cout << "[";
    for (const auto& element : arr)
        std::cout << element << " ";
    std::cout << "]" << std::endl;
}

int main() {
    std::vector<int> arr = { 261, 777, 659, 55, 432, 43 };
    std::cout << "\n[#1]: ";
    printArray(arr);

    auto start_time = high_resolution_clock::now();
    radixSort(arr);
    auto end_time = high_resolution_clock::now();

    std::cout << "\n[#2]: ";
    printArray(arr);
    auto duration = duration_cast<microseconds>(end_time - start_time).count();
    std::cout << "\n[time]: " << duration << " microseconds\n" << std::endl;


    return 0;
}

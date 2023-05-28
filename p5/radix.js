/**
* \brief Radix Sort Python implementation
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
// JavaScript doesn't support the use of templates, but since this
// is an interpreted language just like python, the type of a variable 
// is determined at runtime instead upon compilation like C++ or Java
//}

function radixSort(arr) {
  // Find the maximum number to determine the number of digits
  const max = Math.max(...arr);

  // Perform counting sort for every digit
  for (let exp = 1; Math.floor(max / exp) > 0; exp *= 10) {
    countingSort(arr, exp);
  }
}

function countingSort(arr, exp) {
  const n = arr.length;
  const output = new Array(n);
  const count = new Array(10).fill(0);

  // Count the occurrences of each digit in the current place
  for (let i = 0; i < n; i++) {
    count[Math.floor(arr[i] / exp) % 10]++;
  }

  // Calculate the cumulative count to determine the correct positions
  for (let i = 1; i < 10; i++) {
    count[i] += count[i - 1];
  }

  // Build the sorted output array
  for (let i = n - 1; i >= 0; i--) {
    output[count[Math.floor(arr[i] / exp) % 10] - 1] = arr[i];
    count[Math.floor(arr[i] / exp) % 10]--;
  }

  // Copy the sorted elements back to the original array
  for (let i = 0; i < n; i++) {
    arr[i] = output[i];
  }
}

const arr = [170, 45, 75, 90, 802, 24, 2, 66];

console.log("Original array:", arr);
radixSort(arr);
console.log("Sorted array:", arr);

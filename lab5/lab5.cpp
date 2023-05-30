#include <iostream>
#include <chrono>
#include <random> 
#include <iomanip>
#include <cstring>

// coderodde's mergesort:
void coderodde_merge(int* source_array, int* target_array, int source_offset, int target_offset, int left_run_length, int right_run_length) {
    int target_index = target_offset;
    int left_index = source_offset;
    int left_index_bound = left_index + left_run_length;
    int right_index = left_index_bound;
    int right_index_bound = right_index + right_run_length;

    while (left_index != left_index_bound && right_index != right_index_bound) {
        target_array[target_index++] =
            source_array[right_index] < source_array[left_index] ?
            source_array[right_index++] :
            source_array[left_index++];
    }

    while (left_index != left_index_bound) {
        target_array[target_index++] = source_array[left_index++];
    }

    while (right_index != right_index_bound) {
        target_array[target_index++] = source_array[right_index++];
    }
}

void coderodde_merge_sort(
    int* target_array,
    int* source_array,
    int source_offset,
    int target_offset,
    int range_length) {

    if (range_length < 2) {
        return;
    }

    int middle = range_length / 2;

    coderodde_merge_sort(
        source_array,
        target_array,
        source_offset,
        target_offset,
        middle);

    coderodde_merge_sort(
        source_array,
        target_array,
        source_offset + middle,
        target_offset + middle,
        range_length - middle);

    coderodde_merge(
        source_array,
        target_array,
        source_offset,
        target_offset,
        middle,
        range_length - middle);
}
void coderodde_merge_sort(int* arr, int size) {
    if (size < 2) {
        return;
    }

    int* buf = new int[size];
    std::copy(arr, arr + size, buf);
    coderodde_merge_sort(arr, buf, 0, 0, size);
    delete[] buf;
}

// coderodde's heapsort:

void coderodde_sift_down(int* arr, int index, int heap_size) {
    int left_child_index = index * 2 + 1;
    int right_child_index = left_child_index + 1;
    int maximum_index = index;
    int target = arr[index];

    while (true) {
        if (left_child_index < heap_size && arr[left_child_index] > target) {
            maximum_index = left_child_index;
        }

        if (maximum_index == index) {
            if (right_child_index < heap_size && arr[right_child_index] > target) {
                maximum_index = right_child_index;
            }
        }
        else if (right_child_index < heap_size && arr[right_child_index] > arr[left_child_index]) {
            maximum_index = right_child_index;
        }

        if (maximum_index == index) {
            arr[maximum_index] = target;
            return;
        }

        arr[index] = arr[maximum_index];
        index = maximum_index;
        left_child_index = index * 2 + 1;
        right_child_index = left_child_index + 1;
    }
}

void coderodde_build_max_heap(int* arr, int size) {
    for (int i = size / 2; i >= 0; --i) {
        coderodde_sift_down(arr, i, size);
    }
}

void coderodde_heap_sort(int* arr, int size) {
    if (size < 2) {
        return;
    }

    coderodde_build_max_heap(arr, size);
    int heap_size = size;

    for (int index = size - 1; index >= 1; index--) {
        std::swap(arr[0], arr[index]);
        coderodde_sift_down(arr, 0, --heap_size);
    }
}


/**
 * @brief Maintains the max heap property of a subtree rooted at index 'root'.
 * @param arr The array to be sorted.
 * @param size The size of the heap/subtree.
 * @param root The index of the root of the subtree.
 */
void heapify(int* arr, int size, int root) {
    int largest = root; //largest is the root of the heap
    int left = 2 * root + 1;    // L child
    int right = 2 * root + 2;   // R child

    // if left child is larger than root
    if (left < size && arr[left] > arr[largest]) {
        largest = left;
    }

    // if right child is larger than current largest
    if (right < size && arr[right] > arr[largest]) {
        largest = right;
    }

    // if largest is not root
    if (largest != root) {
        std::swap(arr[root], arr[largest]);
        heapify(arr, size, largest); //recursive call
    }
}

/**
 * @brief Performs heap sort on an array.
 * @param arr The array to be sorted.
 * @param size The size of the array.
 */
void heap_sort(int* arr, int size) {
    // build a max heap
    for (int i = size / 2 - 1; i >= 0; i--) {
        heapify(arr, size, i);
    }

    // extract elements from heap one by one
    for (int i = size - 1; i >= 0; i--) {
        // move current root to the end
        std::swap(arr[0], arr[i]);

        // call max heapify on the reduced heap
        heapify(arr, i, 0);
    }
}

/**
 * @brief Merges two subarrays of arr[]
 * @param arr The array to be sorted
 * @param p Starting index of the first subarray
 * @param q Ending index of the first subarray
 * @param r Ending index of the second subarray
 */
void merge(int* arr, int p, int q, int r) {
    int n1 = q - p + 1; // size of the first subarray
    int n2 = r - q; // size of the second subarray

    //temp arrays
    int* left_sub = new int[n1];
    int* right_sub = new int[n2];

    //copy elements
    for (int i = 0; i < n1; i++) {
        left_sub[i] = arr[p + i];
    }

    //copy elements
    for (int j = 0; j < n2; j++) {
        right_sub[j] = arr[q + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = p;

    // merge the elements from the temporary arrays back into arr[] in sorted order
    while (i < n1 and j < n2) {
        if (left_sub[i] < right_sub[j]) {
            arr[k] = left_sub[i];
            i++;
        }
        else {
            arr[k] = right_sub[j];
            j++;
        }
        k++;
    }

    //copy elements over if any
    while (i < n1) {
        arr[k] = left_sub[i];
        i++;
        k++;
    }

    //copy elements over if any
    while (j < n2) {
        arr[k] = right_sub[j];
        j++;
        k++;
    }

    delete[] left_sub; //free memory
    delete[] right_sub;
}

/**
 * @brief Sorts an array using merge sort algorithm
 * @param arr The array to be sorted
 * @param p Starting index of the array
 * @param r Ending index of the array
 */
void merge_sort_helper(int* arr, int p, int r) {
    if (p < r) {
        int q = (p + r) / 2;
        merge_sort_helper(arr, p, q);
        merge_sort_helper(arr, q + 1, r);
        merge(arr, p, q, r);
    }
}

/**
 * @brief Sorts an array using merge sort algorithm
 * @param arr The array to be sorted
 * @param size The size of the array
 */
void merge_sort(int* arr, int size) {
    merge_sort_helper(arr, 0, size - 1);
}

/**
 * @brief Generates a random pivot index between low and high (inclusive)
 * @param low Starting index of the array
 * @param high Ending index of the array
 * @return Random pivot index
 */
int random_pivot(int low, int high) {
    return low + rand() % (high - low + 1);
}

/**
 * @brief Partitions the array and returns the partition index
 * @param arr The array to be partitioned
 * @param low Starting index of the partition
 * @param high Ending index of the partition
 * @return Partition index
 */
int partition(int* arr, int low, int high) {
    int pivotIndex = random_pivot(low, high);
    int pivot = arr[pivotIndex];
    std::swap(arr[pivotIndex], arr[high]);

    int i = low - 1; // Index of the smaller element

    for (int j = low; j <= high - 1; j++) {
        // If current element is smaller than or equal to the pivot
        if (arr[j] <= pivot) {
            i++; // Increment index of smaller element
            std::swap(arr[i], arr[j]); // Swap current element with the smaller element
        }
    }

    std::swap(arr[i + 1], arr[high]); // Swap the pivot with the element at the partition index
    return i + 1; // Return the partition index
}

/**
 * @brief Sorts an array using the QuickSort algorithm
 * @param arr The array to be sorted
 * @param low Starting index of the array
 * @param high Ending index of the array
 */
void quick_sort_helper(int* arr, int low, int high) {
    if (low < high) {
        int partition_index = partition(arr, low, high); // partition the array and get the partition index
        quick_sort_helper(arr, low, partition_index - 1); // recursively sort the left subarray
        quick_sort_helper(arr, partition_index + 1, high); // recursively sort the right subarray
    }
}

/**
 * @brief Sorts an array using the QuickSort algorithm
 * @param arr The array to be sorted
 * @param size The size of the array
 */
void quick_sort(int* arr, int size) {
    quick_sort_helper(arr, 0, size - 1);
}

/**
 * @brief
 * @param arr
 */
void print_arr(int* arr, int size) {
    std::cout << "[";
    for (int i = 0; i < size; i++) {
        if (i == size - 1) {
            std::cout << arr[i]; //drop comma if last element
        }
        else {
            std::cout << arr[i] << ", ";
        }
    }
    std::cout << "]" << std::endl;
}

/**
 * @brief Checks if the array is sorted by going through every element in the array
 * @param arr Array of integers
 * @param size Size of the Array
 * @return Boolean, True if it's sorted and False if not
 */
bool sorted(int* arr, int size) {
    for (int i = 1; i < size; i++) {
        if (arr[i] < arr[i - 1]) {
            return false;
        }
    }
    return true;
}

/**
 * @brief Measures the execution time of a sorting algorithm on arrays of different sizes.
 * @param sorting_function The sorting function to be measured.
 */
void measure_sort(void (*sorting_function)(int*, int)) {
    int sizes[] = { 10, 100, 1000, 10000, 100000 }; // sizes of the array
    int const MAX = 100000;
    int const SMALL = 10;

    std::random_device rd; // a seed source for the random number engine
    std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distrib(1, MAX);

    for (auto i = 0; i < 5; i++) {
        int* arr = new int[sizes[i]];
        for (auto j = 0; j < sizes[i]; j++) { //fill array with random numbers
            arr[j] = distrib(gen);
        }

        if (sizes[i] == SMALL) { //print og array before sorting
            std::cout << "\n[Original]: "; // << std::setw(2);
            print_arr(arr, sizes[i]);
        }

        //{
        /**
         * @note Measure execution time
         * @typedef std::chrono::high_resolution_clock::time_point as clock for better readability
         * @typedef std::chrono::microseconds as ms for better readability
        */
        //}
        typedef std::chrono::high_resolution_clock::time_point clock;
        typedef std::chrono::microseconds ms;

        clock start = std::chrono::high_resolution_clock::now();
        sorting_function(arr, sizes[i]);
        clock end = std::chrono::high_resolution_clock::now();
        ms duration = std::chrono::duration_cast<ms>(end - start);
        long long durationCount = duration.count();

        if (sizes[i] == SMALL) {
            std::string const SPACE = "   "; //width const to align output
            std::cout << std::setw(4) << "[Sorted]:" << SPACE;
            print_arr(arr, sizes[i]);
            std::cout << std::endl << std::endl;
        }

        if (!sorted(arr, sizes[i])) {
            std::cerr << "ERROR: Unsorted array detected!\n";
            abort();
        }

        int const SIZE_W = 9;
        int const TIME_W = 8;
        int const W = 6;
        std::cout << std::left << std::setw(SIZE_W) << "[size]: " << std::setw(W + 3) << sizes[i] << std::left << std::setw(TIME_W) << "[time]: " << std::setw(W + 2) << durationCount << " [ms]" << std::endl;

        // Clean up dynamically allocated memory
        delete[] arr;
    }
}


/**
 * @brief Brains of the program, handles the logic
 * @return void-type
 */
void run() {
    std::cout << std::endl;
    std::cout << "Measuring Sorting Algorithms" << std::endl;

    std::cout << "\n[***** [Merge Sort] *****]" << std::endl;
    measure_sort(merge_sort);

    std::cout << "\n[***** [Quick Sort] *****]" << std::endl;
    measure_sort(quick_sort);

    std::cout << "\n[***** [Heap Sort] *****]" << std::endl;
    measure_sort(heap_sort);

    std::cout << "\n[***** [coderodde's Heap Sort] *****]" << std::endl;
    measure_sort(coderodde_heap_sort);

    std::cout << "\n[***** [coderodde's Merge Sort] *****]" << std::endl;
    measure_sort(coderodde_merge_sort);

    std::cout << std::endl;
}

/**
 * @brief Main function of the program, calls run()
 * @return EXIT_SUCCESS upon successful execution
 */
int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    for (size_t i = 0; i < 6; i++) {
        std::cout << "[*** ITERATION " << i + 1 << " ***]";
        run();
    }
    return EXIT_SUCCESS;
}

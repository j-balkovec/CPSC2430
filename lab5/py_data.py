import matplotlib.pyplot as plt
import numpy as np

from plot_utils import (
  get_labels,
  plot_comparison,
  plot_scatter,
)

lists = [[]]
sizes = [10, 100, 1000, 10000, 100000]
current_list = 0

def read_data():
    all_lists = [[]]
    current_list_idx = 0

    with open('data.txt') as file:
        lines = file.readlines()

    for line in lines:
        line = line.strip()
        if not line:
            all_lists.append([])
            current_list_idx += 1
        elif line.startswith('[time]'):
            time = int(line.split(':')[1].strip())
            all_lists[current_list_idx].append(time)

    return all_lists

def plot_comparison(x_values, y_values, labels, title):
    plt.figure(figsize=(10, 6))
    for x, y, label in zip(x_values, y_values, labels):
        plt.plot(x, y, marker='o', label=label)
    plt.xlabel('Sizes')
    plt.ylabel('Times [ms]')
    plt.title(f'{title} Comparison')
    plt.legend()
    plt.show()

def plot_scatter(x_data, y_data, colors, labels, title):
    plt.figure(figsize=(10, 6))
    for x, y, color, label in zip(x_data, y_data, colors, labels):
        plt.scatter(x, y, c=color, label=label)
        plt.plot(x, y, c=color, linestyle='-')
    plt.xlabel('Size')
    plt.ylabel('Time')
    plt.title(title)
    plt.legend()
    plt.show()

def get_lists():
    ms_times = [lists[i] for i in range(0, 9, 3)]
    qs_times = [lists[i] for i in range(1, 9, 3)]
    hs_times = [lists[i] for i in range(2, 9, 3)]
    return ms_times, qs_times, hs_times

def get_labels():
    ms_labels = ['MS #1', 'MS #2', 'MS #3']
    qs_labels = ['QS #1', 'QS #2', 'QS #3']
    hs_labels = ['HS #1', 'HS #2', 'HS #3']
    return ms_labels, qs_labels, hs_labels

def plot_comparison(x_data, y_data, labels, title):
    plt.figure(figsize=(10, 6))
    for x, y, label in zip(x_data, y_data, labels):
        plt.plot(x, y, label=label)
    plt.xlabel('Size')
    plt.ylabel('Time')
    plt.title(title)
    plt.legend()
    plt.show()

def plot_scatter(x_data, y_data, colors, labels, title):
    plt.figure(figsize=(10, 6))
    for x, y, color, label in zip(x_data, y_data, colors, labels):
        plt.scatter(x, y, c=color, label=label)
        plt.plot(x, y, c=color, linestyle='-')
    plt.xlabel('Size')
    plt.ylabel('Time')
    plt.title(title)
    plt.legend()
    plt.show()

def plot_data(sizes, ms_times, qs_times, hs_times, ms1_times, qs1_times, hs1_times):
    ms_labels, qs_labels, hs_labels = get_labels()

    plot_comparison(
        [sizes] * 3,
        ms_times,
        ms_labels,
        'Comparison of Measure Sort Execution'
    )
    plot_comparison(
        [sizes] * 3,
        qs_times,
        qs_labels,
        'Comparison of Quick Sort Execution'
    )
    plot_comparison(
        [sizes] * 3,
        hs_times,
        hs_labels,
        'Comparison of Heap Sort Execution'
    )

    y_hs_small = hs1_times[:3]
    y_ms_small = ms1_times[:3]
    y_qs_small = qs1_times[:3]
    
    plot_scatter(
        [sizes[:3]] * 3,
        [y_hs_small, y_ms_small, y_qs_small],
        ['red', 'blue', 'green'],
        ['Heap Sort', 'Merge Sort', 'Quick Sort'],
        'Smaller Sizes [1 - 100]'
    )

    ms_avg = np.mean(ms_times, axis=0)
    qs_avg = np.mean(qs_times, axis=0)
    hs_avg = np.mean(hs_times, axis=0)
    
    plot_comparison(
        [sizes] * 3,
        [ms_avg, qs_avg, hs_avg],
        ['Merge Sort', 'Quick Sort', 'Heap Sort'],
        'Averages of MS, QS, and HS'
    )

    y_hs_large = hs1_times[2:]
    y_ms_large = ms1_times[2:]
    y_qs_large = qs1_times[2:]
    
    plot_scatter(
        [['1000', '10000', '100000']] * 3,
        [y_hs_large, y_ms_large, y_qs_large],
        ['red', 'blue', 'green'],
        ['Heap Sort', 'Merge Sort', 'Quick Sort'],
        'Bigger Sizes [1000 - 100000]'
    )

    ms_10, ms_100, ms_1000 = ms1_times[:3]
    qs_10, qs_100, qs_1000 = qs1_times[:3]
    hs_10, hs_100, hs_1000 = hs1_times[:3]
    x_small = ['10', '100', '1000']
    y_ms_small = [ms_10, ms_100, ms_1000]
    y_qs_small = [qs_10, qs_100, qs_1000]
    y_hs_small = [hs_10, hs_100, hs_1000]
    
    plot_comparison(
        [x_small] * 3,
        [y_ms_small, y_qs_small, y_hs_small],
        ['Merge Sort', 'Quick Sort', 'Heap Sort'],
        'Smaller Sizes [1 - 100]'
    )

    ms_1000, ms_10000, ms_100000 = ms1_times[2:]
    qs_1000, qs_10000, qs_100000 = qs1_times[2:]
    hs_1000, hs_10000, hs_100000 = hs1_times[2:]
    x_large = ['1000', '10000', '100000']
    y_ms_large = [ms_1000, ms_10000, ms_100000] 
    y_qs_large = [qs_1000, qs_10000, qs_100000] 
    y_hs_large = [hs_1000, hs_10000, hs_100000] 
    
    plot_comparison( 
        [x_large] * 3,
        [y_ms_large, y_qs_large, y_hs_large],
        ['Merge Sort', 'Quick Sort', 'Heap Sort'], 
        'Bigger Sizes [1000 - 100000]' )

def main():
    lists = read_data()
    ms_times, qs_times, hs_times = get_lists()
    ms1_times, qs1_times, hs1_times = ms_times[0], qs_times[0], hs_times[0]
    plot_data(sizes, ms_times, qs_times, hs_times, ms1_times, qs1_times, hs1_times)

if __name__ == "__main__":
    main()

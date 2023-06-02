"""
Plot's the imported data
"""

import numpy as np
import matplotlib.pyplot as plt

def read_data(file_name):
    with open(file_name, 'r') as f:
        data = f.readlines()
        data = [list(map(float, line.strip().split())) for line in data]
    return data

def print_sublists(data):
    for sublist in data:
        print(sublist)

def plot_lists(data, titles):
    for i, sublist in enumerate(data):
        plt.plot(sublist)
        plt.title(titles[i])
        plt.show()

def plot_averages(data, title):
    averages = [np.mean(sublist) for sublist in data]
    plt.plot(averages)
    plt.title(title)
    plt.show()

import numpy as np
import matplotlib.pyplot as plt

def read_data(file_name):
    with open(file_name, 'r') as f:
        data = f.readlines()
        data = [list(map(float, line.strip().split())) for line in data]
    return data

def print_sublists(data):
    for sublist in data:
        print(sublist)

def plot_lists(data, titles):
    for i, sublist in enumerate(data):
        plt.plot(sublist)
        plt.title(titles[i])
        plt.show()

def plot_averages(data, title):
    averages = [np.mean(sublist) for sublist in data]
    plt.plot(averages)
    plt.title(title)
    plt.show()

def plot_comparison(bico_data, recursive_bico_data):
    bico_averages = [np.mean(sublist) for sublist in bico_data]
    recursive_bico_averages = [np.mean(sublist) for sublist in recursive_bico_data]

    fig, ax = plt.subplots()
    index = np.arange(len(bico_averages))
    bar_width = 0.20
    opacity = 0.6

    rects1 = ax.bar(index, bico_averages, bar_width, alpha=opacity, color='b', label='Bico')
    rects2 = ax.bar(index + bar_width, recursive_bico_averages, bar_width, alpha=opacity, color='g', label='recursiveBico')

    ax.set_ylabel('Average')
    ax.set_title('Comparison of Iteration vs Recursion')
    ax.set_xticks(index + bar_width / 2)
    ax.set_xticklabels(('(3,2)', '(10,5)', '(30,15)'))
    ax.legend()
    ax.set_ylim(0, max(max(bico_averages), max(recursive_bico_averages[0:2])) * 1.1)

    plt.tight_layout()
    plt.show()

def main():
    bico_data = read_data('bico.txt')
    recursive_bico_data = read_data('recursiveBico.txt')

    print_sublists(bico_data)
    print_sublists(recursive_bico_data)

    bico_titles = ["Bico(3,2) in [ns]", "Bico(10,5) in [ns]", "Bico(30,15) in [ns]"]
    recursive_bico_titles = ["recursiveBico(3,2) in [ns]", "recursiveBico(10,5) in [ns]", "recursiveBico(30,15) in [ns]"]

    plot_lists(bico_data, bico_titles)
    plot_lists(recursive_bico_data, recursive_bico_titles)

    plot_averages(bico_data, 'Averages of Bico Sublists')
    plot_averages(recursive_bico_data, 'Averages of RecursiveBico Sublists')

    plot_comparison(bico_data, recursive_bico_data)


def main():
    bico_data = read_data('bico.txt')
    recursive_bico_data = read_data('recursiveBico.txt')

    print_sublists(bico_data)
    print_sublists(recursive_bico_data)

    bico_titles = ["Bico(3,2) in [ns]", "Bico(10,5) in [ns]", "Bico(30,15) in [ns]"]
    recursive_bico_titles = ["recursiveBico(3,2) in [ns]", "recursiveBico(10,5) in [ns]", "recursiveBico(30,15) in [ns]"]

    plot_lists(bico_data, bico_titles)
    plot_lists(recursive_bico_data, recursive_bico_titles)

    plot_averages(bico_data, 'Averages of Bico Sublists')
    plot_averages(recursive_bico_data, 'Averages of RecursiveBico Sublists')

    plot_comparison(bico_data, recursive_bico_data)


if __name__ == '__main__':
    main()

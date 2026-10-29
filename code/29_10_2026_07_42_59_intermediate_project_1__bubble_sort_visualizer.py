import random
import matplotlib.pyplot as plt
import matplotlib.animation as animation

def bubble_sort(arr):
    n = len(arr)
    for i in range(n-1):
        for j in range(0, n-i-1):
            if arr[j] > arr[j+1]:
                arr[j], arr[j+1] = arr[j+1], arr[j]
    return arr

def visualize_bubble_sort(data):
    fig, ax = plt.subplots()

    x_range = range(len(data))
    line, = ax.plot(x_range, data, 'b-')

    def update(num):
        for i in range(len(data)-1):
            if data[i] > data[i+1]:
                data[i], data[i+1] = data[i+1], data[i]
        line.set_ydata(data)
        return line,

    ani = animation.FuncAnimation(fig, update, frames=range(50), blit=True)

    plt.show()

def main():
    arr = [random.randint(0, 100) for _ in range(10)]
    print("Original array: ", arr)

    sorted_arr = bubble_sort(arr)
    print("Sorted array: ", sorted_arr)

    visualize_bubble_sort(arr)

if __name__ == '__main__':
    main()
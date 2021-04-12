import matplotlib.pyplot as plt

def get_array_from_csv_file(path):
    f = open(path, 'r')
    fileString = f.read()
    f.close()

    if fileString == '':
        print('file is empty')
        return

    arr = fileString.split('\n')
    for i in range(len(arr)):
        arr[i] = arr[i].split(',')
        if (arr[i] == ['']):
            del arr[i]
            continue
        arr[i][0] = int(arr[i][0])  # iterations
        arr[i][1] = float(arr[i][1])# time

    return arr

if __name__ == '__main__':
    arr = get_array_from_csv_file('../option6/data.csv')
    print(arr)

    x_cpp = []
    y_cpp = []
    x_asm = []
    y_asm = []
    for i in range(len(arr)):
        if i % 2 == 0:
            x_cpp.append(arr[i][0])
            y_cpp.append(arr[i][1])
        else:
            x_asm.append(arr[i][0])
            y_asm.append(arr[i][1])


    plt.plot(x_cpp, y_cpp, '>r', label="C++")
    plt.plot(x_asm, y_asm, '<g', label="Assembler")

    plt.xlabel("x: iterations")
    plt.xticks(rotation=45)
    plt.ylabel("y: time, seconds")
    plt.title("Time(iterations)")
    plt.legend()
    plt.grid(True)
    plt.show()
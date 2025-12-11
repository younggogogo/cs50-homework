while True:
    try:
        height = int(input("HEIGHT: "))
        if 0 < height < 9:
            break
    except ValueError:
        pass

for i in range(height):
    print(' ' * (height - 1 - i), end='')
    print('#' * (i + 1), end='')
    print('  ', end='')
    print('#' * (i + 1))

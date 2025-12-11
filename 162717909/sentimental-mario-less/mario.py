# while True:
#         try:
#             height = int(input("Height: "))
#             if 0 < height < 9:
#                 break;
#         except ValueError:
#             pass
from cs50 import get_int

while True:
    height = get_int("Height: ")
    if 0 < height < 9:
        break

for i in range(height):
    print(' ' * (height-1-i), end='')
    print('#' * (i+1))

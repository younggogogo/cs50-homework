from cs50 import get_float
while True:
    cash = get_float("Change: ")
    if 0 < cash:
        break

cash = int(cash*100)
num = 0
print(cash)

while cash >= 25:
    cash -= 25.
    num += 1
while cash >= 10:
    cash -= 10
    num += 1
while cash >= 5:
    cash -= 5
    num += 1
while cash > 0:
    cash -= 1
    num += 1
print(f"{num}")

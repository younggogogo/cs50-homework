from cs50 import get_int
card = get_int("Number: ")

sum = 0
head = str(card)
head = head[0:2]
length = len(str(card))

while card > 0:
    a = card % 10
    sum += a
    card = card // 10
    b = card % 10
    b *= 2
    card = card // 10
    while b > 0:
        sum = sum + b % 10
        b = b // 10

# print(sum)
# print(sum%10)
# print(head)
# print(card)
#  card值已改变，前面要用一个值储存card值
if length in [13, 15, 16] and sum % 10 == 0:
    if head == '34' or head == '37':
        print("AMEX")
    if head[0] == '4':
        print("VISA")
    if head == '51' or head == '52' or head == '53' or head == '54' or head == '55':
        print("MASTERCARD")
    else:
        print("INVALID")
else:
    print("INVALID")

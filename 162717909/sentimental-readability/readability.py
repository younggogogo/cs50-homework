text = input("TEXT: ")
l = 0
s = 0
w = 1
for i in text:
    if i.isalpha():
        l += 1
    elif i == ' ':
        w += 1
    elif i in ['.', '!', '?']:
        s += 1

n = 0.0588 * (l / w * 100) - 0.296 * (s / w * 100) - 15.8
n = round(n)
if n < 1:
    print("Before Grade 1")
elif n >= 16:
    print("Grade 16+")
else:
    print(f"Grade {n}")

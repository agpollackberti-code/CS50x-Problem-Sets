from cs50 import get_int

# get & check input
while True:
    height = get_int("When we say jump Mario we say how high? ")
    if 1 <= height <= 8:
        break

# print based on input
for i in range(height):
    print(" "*(height-i-1), end="")
    for j in (range(i+1)):
        print("#", end="")
    print()
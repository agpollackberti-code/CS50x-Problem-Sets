# import files
from cs50 import get_float

# INPUT
# get user input
while True:
    amountfloat = get_float("Change owed: ")
    if amountfloat >= 0:
        break
# turn float to int to get nearest cent
amount = round(amountfloat*100)

# CALCULATION
coinCount = 0

# quarters
while (amount >= 25):
    coinCount = coinCount + 1
    amount = amount - 25

# dimes
while (amount >= 10):
    coinCount = coinCount + 1
    amount = amount - 10

# nickles
while (amount >= 5):
    coinCount = coinCount + 1
    amount = amount - 5

# pennies
while (amount >= 1):
    coinCount = coinCount + 1
    amount = amount - 1

# OUTPUT
# return min # of coins required to give user change
print(coinCount)


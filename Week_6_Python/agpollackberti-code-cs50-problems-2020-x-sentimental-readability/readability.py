# IMPORT
from cs50 import get_string
import string

# INPUT
input = get_string("Enter Text: ")

# CALCULATIONS
letters = 0
words = 0
sentences = 0

# letters
# https://stackoverflow.com/questions/265960/best-way-to-strip-punctuation-from-a-string
puncOut = input.translate(str.maketrans('', '', string.punctuation))
#https://stackoverflow.com/questions/8270092/remove-all-whitespace-in-a-string
spaceOut = (puncOut.replace(" ", ""))
letters=len(spaceOut)

# words
words = len(input.split())

# sentences
for i in input:
    if ((i == "!") or (i == ".") or (i == "?")):
        sentences = sentences + 1

# Coleman-Liau index calculation
L = ((letters / words) * 100)
S = ((sentences / words) * 100);
index = round(0.0588 * L - 0.296 * S - 15.8)

# OUTPUT
#less than grade1
if (index < 1):
    print("Before Grade 1")

#within range
if (index >= 16):
    print("Grade 16+")

#16+
if (1 < index < 16):
    print("Grade ", index)
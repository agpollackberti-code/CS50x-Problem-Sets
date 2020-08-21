# IMPORTS
import sys
import csv

# Reads database to get STR's from the header row


def match(database, targetfile):
    ismatch = ""

    # NOTE both files are using the same targets because targets come from database
    # convert targetSTRs to fingerprint row
    fingerprint = []
    for target in targetfile:
        fingerprint.append(target["tally"])

    # open database file
    # parse rows into pattern dicts
    with open(database, 'r') as csvfile:
        # creating a csv reader object
        csvreader2 = csv.reader(csvfile)
        # extracting each data row one by one
        csvreader2.__next__()
        dataprint = []
        for row in csvreader2:
            for i in range(1, len(row), 1):
                dataprint.append(int(row[i]))
            if (dataprint == fingerprint):
                ismatch = (row[0])
            dataprint.clear()
    return ismatch

# takes header file of database and creates targets for 'tally'


def targets(database):
    # initialize strs list
    strs = []
    targets = []

    # reading csv file
    with open(database, 'r') as csvfile:
        # creating a csv reader object
        csvreader = csv.reader(csvfile)
        res_dct = {}

        # extracting field names through first row
        strs = next(csvreader)

        # take the strs list and create a list of dictionaries for pattern, length
        for i in range(1, len(strs), 1):
            res_dct["pattern"] = strs[i]
            res_dct["length"] = len(strs[i])
            targets.append(res_dct.copy())  # nasty pointer-like behavior w/o the copy :(
    csvfile.close()
    return targets


# Tallies the max repeat for each STR
def tally(pattern, length, querysequence):
    # open the txt file and read contents to memory
    q = open(querysequence, "r")
    s = q.read()

    maxCount = 0

    # scan for our str's
    i = 0  # start of our window
    p = pattern
    w = length

    # slide along each nucleotide (ATCG), window to assess = length of STR
    for startingnucleotide in s:
        counter = 0
        substring = s[i:i + w]
        if (substring == p):
            counter = counter + 1  # first match
            j = i + w
            while(s[j:j + w] == p):
                counter = counter + 1  # subsequent repeats
                j = j + w

        if (counter > maxCount):
            maxCount = counter

        i = i + 1  # slide the window to next nucleotide/char

    return(maxCount)

# INPUT


# handle incorrect number of args
if((len(sys.argv)) != 3):
    sys.exit("ERROR! 2 input files expected, ex. 'databases/large.csv sequences/5.txt' Please retry.")

# organize the input data
database = sys.argv[1]
querysequence = sys.argv[2]

# ALGORITHM

# set targets
targetSTRs = targets(database)

# tally repeats
for entry in targetSTRs:
    results = tally(entry["pattern"], entry["length"], querysequence)
    entry["tally"] = results

# compare against database entries
matches = match(database, targetSTRs)

# OUTPUT
# print match name or "No match"
if (matches == ""):
    print("No match")
print(matches)
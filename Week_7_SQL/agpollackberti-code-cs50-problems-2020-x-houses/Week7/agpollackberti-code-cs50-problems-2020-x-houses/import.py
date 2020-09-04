import sys
import csv
from cs50 import SQL

# handle incorrect number of args
if((len(sys.argv)) != 2):
    exit("ERROR! 2 input files expected, ex. 'python import.py characters.csv' Please retry.")

# organize the input data, reset the students table to fresh state
characters = sys.argv[1]
db = SQL("sqlite:///students.db")
sqlClearRows = "DELETE from students"
db.execute(sqlClearRows)  # starting with a fresh slate, not adding additional entries
sqlRestartIncrement = "DELETE from sqlite_sequence where name = 'students'"
db.execute(sqlRestartIncrement)  # the auto-increment on index

# shape data into fields for sql insert statement
with open(characters, 'r') as csvfile:
    reader = csv.DictReader(csvfile)
    for row in reader:

        splitName = (row['name']).split()
        house = row['house']
        birth = row['birth']

        if (len(splitName) == 2):
            splitName.insert(1, None)

        # insert each row into the students.db
        sqlInsert = "INSERT INTO students (first, middle, last, house, birth) VALUES (%s, %s, %s, %s, %s)"
        val = (splitName[0], splitName[1], splitName[2], house,  birth)
        db.execute(sqlInsert, val)
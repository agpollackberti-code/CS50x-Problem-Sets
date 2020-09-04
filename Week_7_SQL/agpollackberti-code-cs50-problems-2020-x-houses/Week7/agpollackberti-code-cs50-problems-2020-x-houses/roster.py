import sys
import csv
from cs50 import SQL

# handle incorrect number of args
if((len(sys.argv)) != 2):
    exit("ERROR. 2 input files expected, ex. 'python roster.py *housename* ' Please retry.")

# organize the input data
house = sys.argv[1]

# handle when house is invalid
hogHouses = {'Gryffindor', 'Ravenclaw', 'Slytherin', 'Hufflepuff'}

if(house not in hogHouses):
    exit("ERROR.  expected house names are 'Gryffindor', 'Ravenclaw', 'Slytherin', or 'Hufflepuff' Please retry.")

db = SQL("sqlite:///students.db")
sql = "SELECT first, middle, last, birth from students WHERE house = %s ORDER BY last, first asc"
returnRoster = db.execute(sql, house)

for entry in returnRoster:
    if (entry["middle"] == None):
        print(entry["first"] + " " + entry["last"] + ", born " + (str(entry["birth"])))
    else:
        print(entry["first"] + " " + entry["middle"] + " " + entry["last"] + ", born " + (str(entry["birth"])))
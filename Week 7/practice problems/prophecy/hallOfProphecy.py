""" Learning Goals:
    1. "Refactor a SQL database to eliminate redundancies
    2. Use SELECT, CREATE and INSERT statements to reorganize data
    3. Write Python to load new SQL tables """

import csv
from cs50 import SQL

def main():
    students = []
    houses = []
    house_assignment = []

    db = SQL("sqlite:///roster.db")

    # Open students.csv as dict reader
    with open('students.csv', "r") as csvfile:
        reader = csv.DictReader(csvfile)

        for row in reader:
            name = row["student_name"]
            house = row["house"]
            head = row["head"]

            create_house(house, houses, head)
            create_student(name, students)
            create_house_assignment(name, house, house_assignment)

    # Input student formation into bd
    for student in students:
        db.execute("INSERT INTO students (student_name) VALUES (?)", student["student_name"])

    # Input House inforamtion into db
    for house in houses:
        db.execute("INSERT INTO houses (house, head) VALUES (?,?)", house["house"], house["head"])

    # Input house assignment
    for assignment in house_assignment:
        db.execute("INSERT INTO house_assignment (student_name, house) VALUES (?,?)", assignment["student_name"], assignment["house"])

def create_house(house, houses, head):
    count = 0
    for h in houses:
        if h["house"] == house:
            count += 1

    if count == 0:
        houses.append({"house": house, "head": head})

def create_student(name, students):
    students.append({"student_name": name})

def create_house_assignment(name, house, house_assignment):
    house_assignment.append({"student_name": name, "house": house})

main()

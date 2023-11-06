--- Student Table
CREATE TABLE students(
    id INTEGER,
    student_name TEXT,
    PRIMARY KEY(id)
);

--- House Table
CREATE TABLE houses(
    id INTEGER,
    house TEXT,
    head TEXT,
    PRIMARY KEY(id)
);
--- House Assignment Table
CREATE TABLE house_assignment(
    id INTEGER,
    student_name TEXT,
    house TEXT,
    PRIMARY KEY(id)
);

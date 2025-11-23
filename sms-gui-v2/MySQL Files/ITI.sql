DROP DATABASE IF EXISTS iti_first_proj;

CREATE DATABASE iti_first_proj;
USE iti_first_proj;

CREATE TABLE students (
    student_id INT AUTO_INCREMENT,
    name VARCHAR(255),
    age INT,
    department VARCHAR(255),
    gpa DECIMAL(3,2),
    CONSTRAINT pk_students PRIMARY KEY(student_id)
);

SELECT * FROM students;

SELECT * FROM students ORDER BY gpa DESC LIMIT 5;

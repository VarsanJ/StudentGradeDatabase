/*
Title: Student Grade Database
Purpose: Linked List Implementation of a student grade database
Developer: Varsan Jeyakkumar
*/

typedef struct Student {
    // Defines Student Implementation
    char name[20];
    int grade;
    struct Student *next;
    struct Student *previous;
} Student;

typedef struct List {
    // Defines Database Grade Implementation
    Student *front;
    Student *back;
} List;



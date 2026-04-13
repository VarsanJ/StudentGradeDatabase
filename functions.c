/*
Title: Student Grade Database
Purpose: Linked List Implementation of a student grade database
Developer: Varsan Jeyakkumar
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

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

Student * createStudent(char name[20], int grade){
    // Creates a student and stores information, then returns
    Student *new = (Student *)malloc(sizeof(Student));
    strcpy(new->name, name);
    new->grade=grade;
    new->next=NULL;
    new->previous=NULL;
    printf("Created student %s with grade %d%%\n", name, grade);
    return new;
}

void deleteStudentMemory(Student * toDelete){
    // Frees memory taken up for the student
    free(toDelete);
}

Student * findStudent(List * list, char name[20]){
    // Returns pointer to the student, or null if does not exist
    if (list->front==NULL){
        return NULL;
    }
    Student * check = list->front;
    while(&check!=&(list->back)){
        if (strcmp(name,check->name)==0) return check;
        check = check->next;
    }
    return NULL;
}

void insertStudent(List * list, Student * insert){
    // Edge case if the list does not exist 
    if (list->front==NULL){
        insert->next=insert;
        insert->previous=insert;
        list->front = insert;
        list->back = list->front;
        return;
    }
}

void deleteStudent(List * list){
    // Edge case if the list does not exist 
    if (list->front==NULL){
        printf("There are no students in the system!\n");
        return;
    }
}

void displayStudents(List * list){
    // Edge case if the list does not exist 
    if (list->front==NULL){
        printf("There are no students in the system!\n");
        return;
    }
}

void clearStudents(List * list){
    // Edge case if the list does not exist 
    if (list->front==NULL){
        printf("There are no students in the system!\n");
        return;
    }
}

int main(){
    Student * test = createStudent("John", 50);
    deleteStudentMemory(test);
    return 0;
}

/*
Student * test = createStudent("John", 50);
printf("%d", test->grade);
free(test);
    
*/
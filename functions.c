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
    if (strcmp(name,check->name)==0) return check;
    while(check!=(list->back)){
        if (strcmp(name,check->name)==0) return check;
        check = check->next;
    }
    if (strcmp(name,check->name)==0) return check;
    return NULL;
}

void insertStudent(List * list, Student * insert){
    // Edge case if the list does not exist 
    if (list->front==NULL){
        insert->next=NULL;
        insert->previous=NULL;
        list->front = insert;
        list->back = list->front;
        printf("Inserted student %s as first element of list\n", insert->name);
        return;
    }
    // Edge case for if student already exists
    if (findStudent(list, insert->name)!=NULL){
        printf("This student already exists!");
        deleteStudentMemory(insert);
        return;
    }
    // Edge case if the head is equal to the tail
    if (list->front==list->back){
        int result = strcmp(insert->name, list->front->name);
        if (result<0){
            list->front=insert;
            list->back->previous=list->front;
            insert->next=list->back;
            insert->previous=NULL;
        } else{            
            list->back=insert;
            list->front->next=list->back;
            insert->previous=list->front;
            insert->next=NULL;
        }
        list->front->previous=NULL;
        list->back->next=NULL;
        return;
    }
    // Edge case if it comes before the head
    if (strcmp(insert->name, list->front->name) < 0){
        Student *temp = list->front;
        temp->previous=insert;
        insert->next=temp;
        list->front=insert;
        list->front->previous=NULL;  
        printf("Inserted student %s into list\n", insert->name);
        return;
    }
    // Edge case if comes after the tail
    if (strcmp(insert->name, list->back->name) > 0){
        Student *temp = list->back;
        temp->next=insert;
        insert->previous=temp;
        list->back=insert;     
        list->back->next=NULL;
        printf("Inserted student %s into list\n", insert->name);
        return;
    }
    Student* search = list->front;
    while(strcmp(insert->name, search->name)>0){
        search=search->next;
    }
    insert->next=search;
    insert->previous=search->previous;
    search->previous->next = insert;
    search->previous = insert;     
    printf("Inserted student %s into list\n", insert->name);
    return;
}

void deleteStudent(List * list, char name[20]){
    Student * delete = findStudent(list,name);
    // Edge case if the list does not exist or if the student does not exist
    if (delete==NULL){
        printf("This student does not currently exist in the list!\n");
        return;
    } 
    // Edge Cases for Head and Tail both same and it being node
    if (list->back==list->front&&delete==list->front){
        deleteStudentMemory(list->front);
        list->front=NULL;
        list->back=NULL;
        printf("Student %s has been deleted\n", name);
        return;
    }
    // Edge case for front node
    if (delete==list->front){
        Student * del = list->front;
        list->front=list->front->next;
        list->front->previous=NULL;
        deleteStudentMemory(del);
        printf("Student %s has been deleted\n", name);
        return;
    } 
    // Edge case for tail node   
    if (delete==list->back){
        Student * del = list->back;
        list->back = list->back->previous;
        list->back->next=NULL;
        deleteStudentMemory(del);
        printf("Student %s has been deleted\n", name);
        return;
    }
    // Normal delete function
    delete->next->previous=delete->previous;
    delete->previous->next=delete->next;
    deleteStudentMemory(delete);
    printf("Student %s has been deleted\n", name);
    return;
}

void displayStudents(List * list){
    // Edge case if the list does not exist 
    if (list->front==NULL){
        printf("There are no students in the system!\n");
        return;
    }   
    Student * check = list->front;
    while(check!=(list->back)){     
        printf("%s %d%%\n", check->name, check->grade);
        check=check->next;
    }
    printf("%s %d%%\n", check->name, check->grade);
    return;
}

void clearStudents(List * list){
    // Edge case if the list does not exist 
    if (list->front==NULL){
        printf("There are no students in the system!\n");
        return;
    }
    if (list->front==list->back){
        deleteStudentMemory(list->front);
        list->front=NULL;
        list->back=NULL;
    }
    Student * delete = list->front;
    Student * nextDelete = list->front;
    while (delete!=list->back){
        nextDelete=delete->next;
        deleteStudentMemory(delete);
        delete = nextDelete;
    }
    deleteStudentMemory(list->back);
    list->front=NULL;
    list->back=NULL;
    printf("Successfully cleared list!\n");
    return;
}


// AI Generated Testcases
int main(){
    // Initialize empty list
    List list;
    list.front = NULL;
    list.back = NULL;

    printf("\n--- INSERT INTO EMPTY LIST ---\n");
    Student *s1 = createStudent("John", 50);
    insertStudent(&list, s1);
    displayStudents(&list);

    printf("\n\n--- INSERT MORE STUDENTS ---\n");
    Student *s2 = createStudent("Alice", 90);
    Student *s3 = createStudent("Bob", 75);
    Student *s4 = createStudent("Charlie", 85);

    insertStudent(&list, s2);
    insertStudent(&list, s3);
    insertStudent(&list, s4);

    displayStudents(&list);

    printf("\n\n--- ATTEMPT DUPLICATE INSERT ---\n");
    Student *dup = createStudent("Alice", 100);
    insertStudent(&list, dup);  // should reject

    printf("\n\n--- FIND STUDENTS ---\n");
    Student *found = findStudent(&list, "Bob");
    if (found != NULL){
        printf("Found Bob with grade %d%%\n", found->grade);
    } else {
        printf("Bob not found\n");
    }

    printf("\n--- DELETE FRONT ---\n");
    deleteStudent(&list, "John");
    displayStudents(&list);

    printf("\n\n--- DELETE BACK ---\n");
    deleteStudent(&list, "Charlie");
    displayStudents(&list);

    printf("\n\n--- DELETE MIDDLE ---\n");
    deleteStudent(&list, "Bob");
    displayStudents(&list);

    printf("\n\n--- DELETE NON-EXISTENT ---\n");
    deleteStudent(&list, "Zoe");

    printf("\n\n--- CLEAR LIST ---\n");
    clearStudents(&list);

    printf("\n\n--- FINAL STATE ---\n");
    displayStudents(&list);

    return 0;
}

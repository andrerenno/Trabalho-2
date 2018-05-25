#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grade_control.h"

#define MAX_NAME 100
#define MAX_NUM 20
#define MAX_INPUT 30

void write_students(Student** studArray){
    size_t arr_size;
    for (arr_size = 0; studArray[arr_size] != NULL; arr_size++);
    FILE* studentFile = fopen("Students.txt", "wt");
    for (size_t i = 0; i < arr_size; i++){
        fprintf(studentFile, "\"%s\"\t|%d|\n", studArray[i]->name, studArray[i]->num);
        fprintf(studentFile, "[]{}\n");
   }
    fclose(studentFile);
}

Student** get_students(void){

    Student** studArray = (Student **)malloc(2 * sizeof(Student*));
    if (studArray == NULL)
        return NULL;
    studArray[0] = NULL;


    FILE* studentFile = fopen("Students.txt", "rt");
    if (studentFile == NULL){
        studentFile = fopen("Students.txt", "wt");
        return studArray;
    }

    int ch;    
    int pos = -1;
    int arrpos = 0;
    int namesize, numsize;
    char num[MAX_NUM];
    char tempName[MAX_NAME];
    
    strcpy(tempName, "");
    strcpy(num, "");
    while((ch = fgetc(studentFile)) != EOF){

        if (ch == '"' && pos == -1) {
            pos = 0;
            namesize = numsize = 0;
            continue;
        }

        if (ch == '|' && pos == -1){
            pos = 1;
            continue;
        }

        if (ch == '['){
            pos = 1;
            continue;
        }

        if (ch == '"'){
            pos = -1;
            continue;
        }
        if (ch == '|'){
            studArray = arr_add_student(new_student(tempName, atoi(num)), studArray);
            strcpy(num, "");
            strcpy(tempName, "");
            arrpos++;
            pos = -1;
            continue;
        }
        if (ch == ']' || ch == '}'){
            pos = -1;
        }
        if (pos == 0){ 
            namesize++; 
            char tmpstr[2];
            if (namesize >= MAX_NAME)
                continue;
            tmpstr[0] = ch;
            tmpstr[1] = '\0';
            strcat (tempName, tmpstr);
            continue;
        } 
        if (pos == 1){
            numsize++;
            char tmpstr[2];
            if (numsize >= MAX_NUM)
                continue;
            tmpstr[0] = ch;
            tmpstr[1] = '\0';
            strcat (num, tmpstr);
        } 
    }
    fclose(studentFile);
    return studArray;
}



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "grade_control.h"

#define MAX_NAME 100
#define MAX_NUM 20
#define MAX_INPUT 30

/* Useful definitions to understand how the student file is read */
#define OUTSIDE -1
#define IN_NAME 0
#define IN_NUM 1
#define IN_TEST 2
#define IN_ASSIGN 3

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
    int pos = OUTSIDE;
    int arrpos = 0;
    int namesize, numsize;
    int gradepos = 0;
    char num[MAX_NUM];
    char tempName[MAX_NAME];
    char tempGrade[20];
    double test[2];
    double assign[4];
    
    test[0] = test[1] = assign[0] = assign[1] = assign[2] = assign[3] = 0;
    namesize = numsize = 0;
    strcpy(tempName, "");
    strcpy(num, "");
    strcpy(tempGrade, "");
    while((ch = fgetc(studentFile)) != EOF){

        if (ch == '#')
            while((ch = fgetc(studentFile)) != '\n');

        /* Begin a name */
        if (ch == '"' && pos == OUTSIDE) {
            pos = IN_NAME;
            continue;
        }

        /* Begin a number */
        if (ch == '|' && pos == OUTSIDE){
            pos = IN_NUM;
            continue;
        }

        if (ch == '['){
            strcpy(tempGrade, "");
            pos = IN_TEST;
            continue;
        }

        if (ch == '{'){
            strcpy(tempGrade, "");
            pos = IN_ASSIGN;
            continue;
        }

        if (ch == '"'){
            pos = OUTSIDE;
            continue;
        }
        if (ch == '|'){
            pos = OUTSIDE;
            continue;
        }
        if (ch == ']'){
            test[gradepos] = atof(tempGrade);
            strcpy(tempGrade, "");
            gradepos = 0;
            pos = OUTSIDE;

        }
        if (ch == '}'){
            assign[gradepos] = atof(tempGrade);
            studArray = arr_add_student(new_student(tempName, atoi(num), test[0], test[1], assign[0], assign[1], assign[2], assign[3]), studArray);
            strcpy(num, "");
            strcpy(tempName, "");
            test[0] = test[1] = assign[0] = assign[1] = assign[2] = assign[3] = 0;
            namesize = numsize = 0;
            arrpos++;
            pos = OUTSIDE;
            gradepos = 0;
        }
        if (pos == IN_NAME){ 
            namesize++; 
            char tmpstr[2];
            if (namesize >= MAX_NAME)
                continue;
            tmpstr[0] = ch;
            tmpstr[1] = '\0';
            strcat (tempName, tmpstr);
            continue;
        } 
        if (pos == IN_NUM){
            numsize++;
            char tmpstr[2];
            if (numsize >= MAX_NUM)
                continue;
            tmpstr[0] = ch;
            tmpstr[1] = '\0';
            strcat (num, tmpstr);
        } 
        if (pos == IN_TEST){
            if (ch == ','){
                test[gradepos] = atof(tempGrade);
                strcpy(tempGrade, "");
                gradepos++;
                continue;
            }
            if (gradepos >= 2)
                continue;
            char tmpstr[2];
            tmpstr[0] = ch;
            tmpstr[1] = '\0';
            strcat (tempGrade, tmpstr);
        } 

        if (pos == IN_ASSIGN){
            if (ch == ','){
                assign[gradepos] = atof(tempGrade);
                strcpy(tempGrade, "");
                gradepos++;
                continue;
            }
            if (gradepos >= 4)
                continue;
            char tmpstr[2];
            tmpstr[0] = ch;
            tmpstr[1] = '\0';
            strcat (tempGrade, tmpstr);
        } 


            
        
    }
    fclose(studentFile);
    return studArray;
}



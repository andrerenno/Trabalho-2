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
    fprintf(studentFile, "# This file is formatted as \"name\" |number| [P1, P2]\n");
    fprintf(studentFile, "# If there is not enough information by the time it reaches '}' it will set the missing info to 0\n");
    fprintf(studentFile, "# if there are two of the same type of info (eg. two names) before the '}' it will only read the second.\n");

    for (size_t i = 0; i < arr_size; i++){
        fprintf(studentFile, "\"%s\"\t|%d|\n", studArray[i]->name, studArray[i]->num);
        fprintf(studentFile, "[%.2lf, %.2lf]", studArray[i] -> test[0], studArray[i] -> test[1]);
        fprintf(studentFile, "{%.2lf, %.2lf, %.2lf, %.2lf}\n", studArray[i] -> assignment[0], studArray[i] -> assignment[1], studArray[i] -> assignment[2], studArray[i] -> assignment[3] );
   }
    fclose(studentFile);
}

Student** get_students(char* error){

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
            int repeat_num = 0;
            for (int i = 0; studArray[i] != NULL; i++){
                if (studArray[i] -> num == atoi(num)){
                    strcpy(error, "There are multiple students with the same number! Students with repeated numbers will be ignored.");
                    repeat_num = 1;
                    break;
                }
            }
            if (repeat_num == 0)
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

Group*** get_groups(Student** stud_arr, char* error){
    Group*** group_arr = malloc(4 * sizeof(Group**));

    int group_arr_num = -1;
    int arraypos = -1;


    for (int i = 0; i < 4; i++){
        group_arr[i] = malloc(sizeof(Student*));
        group_arr[i][0] = NULL;
    }

    FILE* groupFile = fopen("Groups.txt", "rt");
    if (groupFile == NULL){
        groupFile = fopen("Groups.txt", "wt");
        return group_arr;
    }
    
    char tempnum[MAX_NUM];
    strcpy(tempnum, "");
    int ch;
    int numsize;

    while((ch = fgetc(groupFile)) != EOF){
        if (ch == '{'){
            if (group_arr_num < 3){
                group_arr_num++;
                arraypos = -1;
            }
        }
        else if (ch == '['){
            if (tempnum[0] != '\0' && arraypos != -1){
                group_arr[group_arr_num][arraypos] -> grade = atof(tempnum);
            }
            arraypos++;
            arr_add_group(group_arr[group_arr_num], new_group(arraypos, 0.0));
            strcpy(tempnum, "");
            numsize = 0;
            while((ch = fgetc(groupFile)) != ']'){
                if (ch == ','){
                    numsize = 0;
                    int studpos;
                    for (studpos = 0; stud_arr[studpos] != NULL; studpos++){
                        if (stud_arr[studpos] -> num == atoi(tempnum))
                            break;
                    }
                    if (stud_arr[studpos] != NULL)
                        group_add_member(stud_arr[studpos], group_arr[group_arr_num][arraypos]);

                    strcpy(tempnum, "");
                }
                else {
                    numsize++;
                    char tmpstr[2];
                    if (numsize >= MAX_NUM)
                        continue;
                    tmpstr[0] = ch;
                    tmpstr[1] = '\0';
                    strcat (tempnum, tmpstr);
                }
            }
            if (tempnum[0] != '\0'){
                int studpos;
                for (studpos = 0; stud_arr[studpos] != NULL; studpos++){
                    if (stud_arr[studpos] -> num == atoi(tempnum))
                        break;
                }
                if (stud_arr[studpos] != NULL)
                    group_add_member(stud_arr[studpos], group_arr[group_arr_num][arraypos]);
            }
            strcpy(tempnum, "");
            numsize = 0;
        }
        else if (ch == '}'){
            if (tempnum[0] != '\0' && arraypos != -1){
                group_arr[group_arr_num][arraypos] -> grade = atof(tempnum);
            }
        }
        else{
            numsize++;
            if (numsize >= MAX_NUM)
                continue;
            char tmpstr[2];
            tmpstr[0] = ch;
            tmpstr[1] = '\0';
            strcat (tempnum, tmpstr);
        }
        

        

    }

    return group_arr;
}
void write_groups(Group*** group_arr){
    FILE* groupsFile = fopen("Groups.txt", "wt");
    for (int i = 0; i < 4; i++){
        fprintf(groupsFile, "{");
        for (int j = 0; group_arr[i][j] != NULL; j++){
            fprintf(groupsFile, "[");
            for(int k = 0; group_arr[i][j] -> members[k] != NULL; k++){
                fprintf(groupsFile, "%s%d", k == 0 ? "" : ",", group_arr[i][j] -> members[k] -> num);
            }
            fprintf(groupsFile, "] %.2lf", group_arr[i][j] -> grade);
            
        }
        fprintf(groupsFile, "}");
    }
}



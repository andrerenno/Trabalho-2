#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grade_control.h"

#define MAX_NAME 100
#define MAX_NUM 20
#define MAX_INPUT 30

void sort_students(Student** arr){
    for (int letter = (MAX_NAME - 1); letter >= 0; letter--){ 
        Student* key;
    	for (int i = 1; arr[i] != NULL; i++){
    		key = arr[i];	
    		int j;
    		for (j = i - 1; j >= 0 && ((arr[j] -> name[letter]) > (key -> name[letter])); j--)
	    		arr[j + 1] = arr[j];
	    	arr[j + 1] = key;
	    }	
    }
}


Student* new_student(char* name, int num){
    Student* p_student = (Student *) malloc(sizeof(Student *));
    p_student -> name = (char *) malloc(strlen(name) * sizeof(char));
    strcpy(p_student->name, name);
    p_student->num = num;
    return p_student;
}

Student** arr_add_student(Student* p_student, Student** stud_arr){

    size_t arr_size;
    for (arr_size = 0; stud_arr[arr_size] != NULL; arr_size++);
    stud_arr = (Student **) realloc(stud_arr, ((int) arr_size + 2) * sizeof(Student *));
    stud_arr[arr_size] = p_student;                             
    stud_arr[(arr_size + 1)] = NULL;                              
    return stud_arr;

    /* Student** new_arr = malloc(((int) arr_size + 2) * sizeof(Student *)); */
    /* for (size_t i = 0; i < arr_size; i++){ */
    /*     new_arr[i] = stud_arr[i]; */
    /* } */
    /* new_arr[arr_size] = p_student; */
    /* new_arr[(arr_size + 1)] = NULL; */
    /* free(stud_arr); */
    /* return new_arr; */
}
Student** arr_rm_student(Student** stud_arr, Student* stud){
    int flag = 0;
    for (int i = 0; stud_arr[i] != NULL; i++){
        if (stud_arr[i] -> num ==  stud -> num)
            flag = 1;
        if (flag == 1)
            stud_arr[i] = stud_arr[i+1];
    }
    return stud_arr; 
}

int main(void){
    Student** studArray;
    studArray = get_students();
    if (studArray == NULL){
        printf("Memory allocation error!\n");
        return 1;
    }

    char input[MAX_INPUT];
    size_t num_of_students;

    while(1){
        printf(">>> ");
        fflush(stdin);
        fgets(input, MAX_INPUT, stdin);
        for (num_of_students = 0; studArray[num_of_students] != NULL; num_of_students++); 
        if (strcmp(input, "list\n") == 0){
            for (size_t i = 0; i < num_of_students; i++){
                printf("%s\t\t%d\n", studArray[i]->name, studArray[i]->num);
            }
        } 
        else if (strcmp(input, "add\n") == 0){
            char name[MAX_NAME], num[MAX_NUM]; 
            printf("Name of the student:  ");
            fgets(name, MAX_NAME, stdin);

            char *pos;                              //
            if ((pos=strchr(name, '\n')) != NULL)   // Removes the trailing '\n' from the string.
                *pos = '\0';                        //

            printf("Number:  ");
            fgets(num, MAX_NUM, stdin);

            studArray = arr_add_student(new_student(name, atoi(num)), studArray);

            printf("Added student: %s, number: %d (write \"save\" to save the student to the file)\n", name, atoi(num));
        }
        else if (strcmp(input, "sort\n") == 0){
            sort_students(studArray);

        }
        else if (strcmp(input, "rm\n") == 0){
            char num[MAX_NUM];
            printf("Enter the number of the student you want to remove:  ");
            fgets(num, MAX_NUM, stdin);

            int i;
            for (i = 0; studArray[i] != NULL; i++){
                if (atoi(num) == studArray[i] -> num)
                    break;
            }

            if (studArray[i] == NULL){
                printf("Couldn't find student with number \"%s\"\n", num);
            } else {
                printf("Are you sure you want to remove student \"%s\",number %d? (y/N) ", studArray[i] -> name, studArray[i] -> num);
                char ans;
                fscanf(stdin, "%c", &ans);
                if(ans == 'Y' || ans == 'y'){
                    printf("Removed student \"%s\",number %d \n", studArray[i] -> name, studArray[i] -> num);
                    arr_rm_student(studArray, studArray[i]);
                }
                fgets(input, MAX_INPUT, stdin);
            }
            fflush(stdin);
        }
        else if (strcmp(input, "save\n") == 0){
            write_students(studArray);
        }
        
        else if (strcmp(input, "quit\n") == 0){
            break;
        }
        else printf("Unknown command: %s", input);
    
    
    }
    for (size_t i = 1; i < num_of_students; i++){
        free(studArray[i]->name);
        free(studArray[i]);
    }
}


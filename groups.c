#include <stdio.h>
#include <curses.h>
#include <stdlib.h>
#include "grade_control.h"
void list_groups(Group** group_arr){
   clear();
   for(int i = 0; group_arr[i] != NULL; i++){
       printw("group %d\n", group_arr[i] -> index); 
       for (int j = 0; group_arr[i] -> members[j] != NULL; j++){
            printw("%s\n", (group_arr[i] -> members[j]) -> name);
       }
   }
   getch();

}
Group* new_group(int index, double grade){
    Group* p_group = (Group*) malloc(sizeof(Group));
    p_group -> members = (Student**) malloc(sizeof(Student*));
    p_group -> members[0] = NULL;
    p_group -> index = index;
    p_group -> grade = grade;

}

Group* group_add_member(Student* stud, Group* group){
    int group_size;

    for (group_size = 0; group -> members[group_size] != NULL; group_size++);

    group -> members = (Student**) realloc(group -> members, (group_size + 2) * sizeof(Student*));
    group -> members[group_size] = stud;
    group -> members[group_size + 1] = NULL; 

    return group;
}

    

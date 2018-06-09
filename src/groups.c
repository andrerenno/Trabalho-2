#include <stdio.h>
#include <curses.h>
#include <stdlib.h>
#include <string.h>
#include "grade_control.h"

#define MAX_NAME 50
#define MAX_NUM 20

int print_table(Student** stud_arr, int mode){
    int maxrow, maxcol;
    getmaxyx(stdscr, maxrow, maxcol);
         
    size_t arr_size;
    for (arr_size = 0; stud_arr[arr_size] != NULL; arr_size++);
            
    int max, min;
    min = 0; 
    if (arr_size < 9)
        max = arr_size;
    else max = 8;
         
    int ch = 0;
    int curpos = 0;
    int edit = 0;
    for (int i = 0; stud_arr[i] != NULL; i++);
    do { 
        for (arr_size = 0; stud_arr[arr_size] != NULL; arr_size++);
        if (max > arr_size)
            max = arr_size;
        /* Handles cursor movement */
        if (edit == 1 && ch == KEY_UP && curpos > 0){
            Student* temp = stud_arr[curpos];
            stud_arr[curpos] = stud_arr[curpos - 1];
            stud_arr[curpos - 1] = temp;
            curpos --;
        }
        else if (edit == 1 && ch == KEY_DOWN && curpos < (arr_size - 1)){
            Student* temp = stud_arr[curpos];
            stud_arr[curpos] = stud_arr[curpos + 1];
            stud_arr[curpos + 1] = temp;
            curpos ++;
        }
        else if (ch == KEY_UP || ch == 'w' || ch == 'W')
	    curpos = (curpos - 1);	
 		else if (ch == KEY_DOWN || ch == 's' || ch == 'S')
			curpos = (curpos + 1) % arr_size;
        if (curpos < 0){
            curpos = arr_size - 1;
            max = arr_size;
            min = (arr_size > 8 ? max - 8: 0);
        }
        if (curpos == 0){
            min = 0;
            max = (arr_size > 8 ? 8 : arr_size);
        }
        if (curpos > (max - 1)){
             max++;
             min++;
        }
        if (curpos < min){
            max--;
            min--;
        }
        if (ch == '-'){
            int flag = 0;
            for (int i = 0; stud_arr[i] != NULL; i++){
                if (stud_arr[i] -> num ==  stud_arr[curpos] -> num)
                    flag = 1;
                if (flag == 1)
                    stud_arr[i] = stud_arr[i+1];
            }
        }

        for (arr_size = 0; stud_arr[arr_size] != NULL; arr_size++);
        if (max > arr_size){
            max = arr_size;
        }

        if (edit == 0 && ch == KEY_RIGHT && mode == 1)
            edit = 1;

        if (edit == 1 && ch == KEY_LEFT)
            edit = 0;
        clear();

        move ((maxrow - (max > 8 ? 8 : max))/ 2 - 3 , (maxcol - MAX_NAME - MAX_NUM)/2);
        addch (ACS_ULCORNER);
        for (int i = 0; i < MAX_NAME + MAX_NUM - 1; i++) addch(ACS_HLINE);
        addch (ACS_URCORNER);

        mvaddch ((maxrow - (max > 8 ? 8 : max))/ 2 - 2 , (maxcol - MAX_NAME - MAX_NUM)/2 , ACS_VLINE);
        mvprintw((maxrow - (max > 8 ? 8 : max))/ 2 - 2 , (maxcol - MAX_NAME - MAX_NUM)/2 + 1 , "Name"); 
        mvprintw((maxrow - (max > 8 ? 8 : max))/ 2 - 2 , (maxcol - MAX_NAME - MAX_NUM)/2 + MAX_NAME , "Number");
        mvaddch ((maxrow - (max > 8 ? 8 : max))/ 2 - 2 , ((maxcol - MAX_NAME - MAX_NUM)/2 + (MAX_NAME + MAX_NUM)), ACS_VLINE);

        move ((maxrow - (max > 8 ? 8 : max))/ 2 - 1 , (maxcol - MAX_NAME - MAX_NUM)/2);
        addch (ACS_LTEE);
        for (int i = 0; i < MAX_NAME + MAX_NUM - 1; i++) addch(ACS_HLINE);
        addch (ACS_RTEE);
        

        for (int i = min; i < max; i++){
            mvaddch((maxrow - (max > 8? 8 : max))/ 2 + i - min, (maxcol - MAX_NAME - MAX_NUM)/2 , ACS_VLINE);
            if (curpos == i)
                attron(A_STANDOUT);
            for (int j = 0; j < MAX_NAME + MAX_NUM; j++) printw(" ");
            move((maxrow - (max > 8? 8 : max))/ 2 + i - min, (maxcol - MAX_NAME - MAX_NUM)/2 + 1 );
            if (edit == 1 && curpos == i)
                printw("  %s", stud_arr[i] -> name); 
            else printw(stud_arr[i] -> name); 

            mvprintw((maxrow - (max > 8 ? 8 : max))/ 2 + i -min, (maxcol - MAX_NAME - MAX_NUM)/2 + MAX_NAME, "%d", stud_arr[i] -> num);
            attroff(A_STANDOUT);
            mvaddch((maxrow - (max > 8 ? 8 : max))/ 2 + i -min, (maxcol - MAX_NAME - MAX_NUM)/2 + MAX_NAME + MAX_NUM, ACS_VLINE);
        }

        move ((maxrow - (max > 8 ? 8 : max))/ 2 + (max > 8 ? 8 : max), (maxcol - MAX_NAME - MAX_NUM)/2);
        addch (ACS_LLCORNER);
        for (int i = 0; i < MAX_NAME + MAX_NUM - 1; i++) addch(ACS_HLINE);
        addch (ACS_LRCORNER);

        if (min > 0)
            mvaddch((maxrow - 8)/ 2, (maxcol - MAX_NAME - MAX_NUM)/2 + MAX_NAME + MAX_NUM - 1, ACS_UARROW);
        if (max < arr_size)
            mvaddch((maxrow - 8)/ 2 + 7, (maxcol - MAX_NAME - MAX_NUM)/2 + MAX_NAME + MAX_NUM - 1, 'v');

        mvprintw ((maxrow - (max > 8 ? 8 : max))/ 2 + (max > 8 ? 8 : max) + 2, (maxcol - 70)/2, "Press <right> and move up and down to change the position of the members");
        mvprintw ((maxrow - (max > 8 ? 8 : max))/ 2 + (max > 8 ? 8 : max) + 3, (maxcol - 39)/2, "(Press <left> to stop moving the student)");
        mvprintw ((maxrow - (max > 8 ? 8 : max))/ 2 + (max > 8 ? 8 : max) + 5, (maxcol - 31)/2, "Press <-> to remove the student");
        mvprintw ((maxrow - (max > 8 ? 8 : max))/ 2 + (max > 8 ? 8 : max) + 7, (maxcol - 24)/2, "Press <ENTER> to go back");
        


        
    } while ((ch = getch()) != '\n');    
    return curpos;

}

Group* show_group(Group* group){
    print_table(group -> members, 1);
    return group;

}
Group** list_groups(Group** group_arr, Student** stud_arr){

    int maxrow, maxcol;
    getmaxyx(stdscr, maxrow, maxcol);

    int ch = 0;
    int num_of_groups;
    int selected_group = 0;
    char msg[200];

    int cfgboxwidth = 15;
    int cfgboxheight = 4;

    char inp_grade[30];

    for (num_of_groups = 0; group_arr[num_of_groups] != NULL; num_of_groups++);
    if (num_of_groups == 0)
            group_arr = arr_add_group(group_arr, new_group(++num_of_groups, 0));
    do {
        strcpy(msg, "");
        for (num_of_groups = 0; group_arr[num_of_groups] != NULL; num_of_groups++){};

        /* Handles cursor movement */
		if (ch == KEY_UP || ch == 'w' || ch == 'W')
	        selected_group = (selected_group - 1);	
 		else if (ch == KEY_DOWN || ch == 's' || ch == 'S')
			selected_group = (selected_group + 1) % num_of_groups;
        if (selected_group < 0)
            selected_group = num_of_groups - 1;

        if (ch == 'n' || ch == 'N')
            group_arr = arr_add_group(group_arr, new_group(++num_of_groups, 0));
        if (ch == 'g' || ch == 'G'){
            draw_box((maxrow - cfgboxheight) / 2, (maxcol - cfgboxwidth) / 2, cfgboxwidth, cfgboxheight);
            
            mvprintw((maxrow - cfgboxheight) / 2 + 2, (maxcol - cfgboxwidth) / 2 + 1, "Score: ");  
            attron(A_STANDOUT);
            for (int i = 0; i < cfgboxwidth - 10; i++) addch(' ');
            attroff(A_STANDOUT);

            move((maxrow - cfgboxheight) / 2 + 2, (maxcol - cfgboxwidth) / 2 + 10);
            attron(A_STANDOUT);
            curs_set(1); echo();
            getnstr(inp_grade, 30);
            curs_set(0); noecho();
            attroff(A_STANDOUT);

            group_arr[selected_group] -> grade  = atof(inp_grade);
        }
        if (ch == '\n')
            group_arr[selected_group] = show_group(group_arr[selected_group]);
        if (ch == 'r' || ch == 'R') 
            group_arr[num_of_groups - 1] = NULL;
        if (ch == '+'){ // Add a student
            int curpos = print_table(stud_arr, 0);
            int already_in_group = 0;
            for (int i = 0; i < num_of_groups; i++){
                for (int j = 0; group_arr[i] -> members[j] != NULL; j++){
                    if (group_arr[i] -> members[j] -> num == stud_arr[curpos] -> num)
                        already_in_group = 1;
                }
            }
            if (already_in_group)
                strcat(msg, "Student already in a group!\n");
            else group_add_member(stud_arr[curpos], group_arr[selected_group]); 
            
        }
        clear();
        
        mvprintw(3, (maxcol - strlen(msg)) / 2, msg);
        int ypos = 5;
        for(int i = 0; group_arr[i] != NULL; i++){
            if (selected_group == i) 
                attron(A_STANDOUT);
            mvprintw(ypos++, (maxcol - 24) / 2, "group %d \t score: %.2lf", group_arr[i] -> index, group_arr[i] -> grade); 
            attroff(A_STANDOUT);
            for (int j = 0; group_arr[i] -> members[j] != NULL; j++){
                mvprintw(ypos++, (maxcol - 24)/2, "  p = %d   %s\n",j , (group_arr[i] -> members[j]) -> name);
            }
        }
        move (ypos + 1, (maxcol - 108)/2);
        attron(A_STANDOUT);
        printw("<ENTER> to edit order or remove student");
        attroff(A_STANDOUT);
        printw(" ");

        attron(A_STANDOUT);
        printw("<+> to add a student to the highlighted group");
        attroff(A_STANDOUT);
        printw(" ");

        attron(A_STANDOUT);
        printw("<N> to add a new group");
        attroff(A_STANDOUT);

        move (ypos + 2, (maxcol - 80)/2);

        attron(A_STANDOUT);
        printw("<Q> to go back");
        attroff(A_STANDOUT);
        printw(" ");

        attron(A_STANDOUT);
        printw("<G> to modify the group's grade");
        attroff(A_STANDOUT);
        printw(" ");

        attron(A_STANDOUT);
        printw("<R> to remove the last group");
        attroff(A_STANDOUT);
        

    } while ((ch = getch()) != 'q');
    return group_arr;

}
Group* new_group(int index, double grade){
    Group* p_group = (Group*) malloc(sizeof(Group));
    p_group -> members = (Student**) malloc(sizeof(Student*));
    p_group -> members[0] = NULL;
    p_group -> index = index;
    p_group -> grade = grade;

    return p_group;
}

Group* group_add_member(Student* stud, Group* group){
    size_t group_size;
    
    /* Gets the previous size of group -> members */
    for (group_size = 0; group -> members[group_size] != NULL; group_size++);

    group -> members = (Student**) realloc(group -> members, (group_size + 2) * sizeof(Student*));
    group -> members[group_size] = stud;
    group -> members[group_size + 1] = NULL; 

    return group;
}

Group** arr_add_group(Group** group_arr, Group* group){
    size_t arr_size;

    /* Gets the previous size of the group array */
    for (arr_size = 0; group_arr[arr_size] != NULL; arr_size++);

    group_arr = realloc(group_arr, sizeof(Group*) * (arr_size + 2));
    group_arr[arr_size] = group;
    group_arr[arr_size + 1] = NULL;

    return group_arr;
}
    

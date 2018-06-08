#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>
#include <math.h>
#include "grade_control.h"

#define MAX_NAME 50
#define MAX_NUM 20
#define MAX_INPUT 30

void draw_box(int ul_corner_row, int ul_corner_col, int boxwidth, int boxheight){
    move (ul_corner_row , ul_corner_col);
    addch (ACS_ULCORNER);
    for (int i = 0; i < boxwidth; i++) addch(ACS_HLINE);
    addch (ACS_URCORNER);
    for (int i = 1; i < boxheight; i++){
        move(ul_corner_row + i, ul_corner_col);  
        addch(ACS_VLINE);
        for (int j = 0; j < boxwidth; j++) addch(' ');
        addch(ACS_VLINE);
    } 
    move (ul_corner_row + boxheight, ul_corner_col);
    addch (ACS_LLCORNER);
    for (int i = 0; i < boxwidth; i++) addch(ACS_HLINE);
    addch (ACS_LRCORNER);
}

Student** user_add_student(Student** stud_arr){
    char inp_name[MAX_NAME];
    char inp_num [MAX_NUM];
    
    int maxrow, maxcol;
    getmaxyx(stdscr, maxrow, maxcol);

    int boxwidth = 30;
    int boxheight = 10;

    draw_box((maxrow - boxheight) / 2, (maxcol - boxwidth)/2 , boxwidth, boxheight);

    mvprintw((maxrow - boxheight) / 2 + 1, (maxcol - 13 ) / 2, "Add a Student");  

    mvprintw((maxrow - boxheight) / 2 + 4, (maxcol - boxwidth ) / 2 + 1, "Name: ");  
    attron(A_STANDOUT);
    for (int i = 0; i < boxwidth - 7; i++) addch(' ');
    attroff(A_STANDOUT);
    
    mvprintw((maxrow - boxheight) / 2 + 6, (maxcol - boxwidth ) / 2 + 1, "Number: ");  
    attron(A_STANDOUT);
    for (int i = 0; i < boxwidth - 9; i++) addch(' ');
    attroff(A_STANDOUT);

    move((maxrow - boxheight) / 2 + 4, (maxcol - boxwidth) / 2 + 6);
    attron(A_STANDOUT);
    curs_set(1); echo();
    getnstr(inp_name, MAX_NAME);
    curs_set(0); noecho();
    attroff(A_STANDOUT);
    char *pos;                                  //
    if ((pos=strchr(inp_name, '\n')) != NULL)   // Removes the trailing '\n' from the string.
        *pos = '\0';                            //

    move((maxrow - boxheight) / 2 + 6, (maxcol - boxwidth) / 2 + 9);
    attron(A_STANDOUT);
    curs_set(1); echo();
    getnstr(inp_num, MAX_NAME);
    curs_set(0); noecho();
    attroff(A_STANDOUT);

    stud_arr = arr_add_student(new_student(inp_name, atoi(inp_num), 0,0,0,0,0,0), stud_arr);
    return stud_arr;
}
void user_rm_student(int arrpos, Student** stud_arr){

    int maxrow, maxcol;
    getmaxyx(stdscr, maxrow, maxcol);

    int boxwidth = 45;
    int boxheight = 5;
    
    draw_box((maxrow - boxheight) / 2, (maxcol - boxwidth)/2 , boxwidth, boxheight);

    mvprintw((maxrow - boxheight) / 2 + 1, (maxcol - 43 ) / 2, "Are you sure you want to remove the student");  
    mvprintw((maxrow - boxheight) / 2 + 2, (maxcol - boxwidth ) / 2 + 1, "Name: %s", stud_arr[arrpos] -> name);  
    mvprintw((maxrow - boxheight) / 2 + 3, (maxcol - boxwidth ) / 2 + 1, "Number: %ld", stud_arr[arrpos] -> num);  

    int curpos = 1;
    int ch = 0;
    do {
        if (ch == KEY_RIGHT || ch == KEY_LEFT || ch == 'A' || ch == 'a' || ch == 'D' || ch == 'D')
            curpos = (curpos == 0 ? 1 : 0);
        if (curpos == 0)
            attron(A_STANDOUT);
        mvprintw((maxrow - boxheight) / 2 + 4, (maxcol - boxwidth ) / 2 + 3, "Y");  
        attroff(A_STANDOUT);

        if (curpos == 1)
            attron(A_STANDOUT);
        mvprintw((maxrow - boxheight) / 2 + 4, (maxcol - boxwidth ) / 2 + boxwidth - 3, "N");  
        attroff(A_STANDOUT);
        
    } while ((ch = getch()) != '\n');

    if (curpos == 0)
        arr_rm_student(stud_arr, stud_arr[arrpos]);
    
}

void show_student(Student* stud){
    
    int maxrow, maxcol;
    getmaxyx(stdscr, maxrow, maxcol);

    int boxwidth = 45;
    int boxheight = 25;

    draw_box((maxrow - boxheight) / 2, (maxcol - boxwidth) / 2, boxwidth, boxheight );
    
    mvprintw((maxrow - boxheight) / 2 + 1, (maxcol - boxwidth) / 2 + 1, "Name: %s", stud -> name);
    mvprintw((maxrow - boxheight) / 2 + 2, (maxcol - boxwidth) / 2 + 1, "Number: %ld", stud -> num);
    
    mvprintw((maxrow - boxheight) / 2 + 4, (maxcol - boxwidth) / 2 + 1, "P1 score: %.2lf", stud -> test[0]);
    mvprintw((maxrow - boxheight) / 2 + 5, (maxcol - boxwidth) / 2 + 1, "P2 score: %.2lf", stud -> test[1]);

    float test_avg = (stud -> test[0] + stud -> test[1]) / 2;
    mvprintw((maxrow - boxheight) / 2 + 7, (maxcol - boxwidth) / 2 + 1, "Test average: %.2lf", test_avg) ;
    
    mvprintw((maxrow - boxheight) / 2 + 9, (maxcol - boxwidth) / 2 + 1, "Assignment 1: %.2lf", stud -> assignment[0]);
    mvprintw((maxrow - boxheight) / 2 + 10, (maxcol - boxwidth) / 2 + 1, "Assignment 2: %.2lf", stud -> assignment[1]);
    mvprintw((maxrow - boxheight) / 2 + 11, (maxcol - boxwidth) / 2 + 1, "Assignment 3: %.2lf", stud -> assignment[2]);
    mvprintw((maxrow - boxheight) / 2 + 12, (maxcol - boxwidth) / 2 + 1, "Assignment 4: %.2lf", stud -> assignment[3]);

    float assignment_avg = (stud -> assignment[0] + stud -> assignment[1] + stud -> assignment[2] + stud -> assignment[3]) / 4;
    mvprintw((maxrow - boxheight) / 2 + 14, (maxcol - boxwidth) / 2 + 1, "Assignment average: %.2lf", assignment_avg) ;

    mvprintw((maxrow - boxheight) / 2 + 16, (maxcol - boxwidth) / 2 + 1, "Final score: %.2lf", sqrt(test_avg * assignment_avg)) ;

    getch();
}

void list_students(Student** stud_arr){

    int maxrow, maxcol;
    getmaxyx(stdscr, maxrow, maxcol);

    size_t arr_size;
    for (arr_size = 0; stud_arr[arr_size] != NULL; arr_size++);

    int ch = 0;
    int curpos = 0;

    do {

        /* Handles cursor movement */
		if (ch == KEY_UP || ch == 'w' || ch == 'W')
			curpos = (curpos - 1);	
 		else if (ch == KEY_DOWN || ch == 's' || ch == 'S')
			curpos = (curpos + 1) % arr_size;
        if (curpos < 0)
            curpos = arr_size - 1;

        if (ch == '+'){
            stud_arr = user_add_student(stud_arr);
        }

        if (ch == '-')
            user_rm_student(curpos, stud_arr);

        if (ch == 'N' || ch == 'n')
            sort_students(stud_arr);

        if (ch == 'P' || ch == 'p')
            write_students(stud_arr);

        if (ch == '\n')
            show_student(stud_arr[curpos]);

        clear();
        
        for (arr_size = 0; stud_arr[arr_size] != NULL; arr_size++);

        move ((maxrow - arr_size)/ 2 - 3 , (maxcol - MAX_NAME - MAX_NUM)/2);
        addch (ACS_ULCORNER);
        for (int i = 0; i < MAX_NAME + MAX_NUM - 1; i++) addch(ACS_HLINE);
        addch (ACS_URCORNER);

        mvaddch ((maxrow - arr_size)/ 2 - 2 , (maxcol - MAX_NAME - MAX_NUM)/2 , ACS_VLINE);
        mvprintw((maxrow - arr_size)/ 2 - 2 , (maxcol - MAX_NAME - MAX_NUM)/2 + 1 , "Name"); 
        mvprintw((maxrow - arr_size)/ 2 - 2 , (maxcol - MAX_NAME - MAX_NUM)/2 + MAX_NAME , "Number");
        mvaddch ((maxrow - arr_size)/ 2 - 2 , ((maxcol - MAX_NAME - MAX_NUM)/2 + (MAX_NAME + MAX_NUM)), ACS_VLINE);

        move ((maxrow - arr_size)/ 2 - 1 , (maxcol - MAX_NAME - MAX_NUM)/2);
        addch (ACS_LTEE);
        for (int i = 0; i < MAX_NAME + MAX_NUM - 1; i++) addch(ACS_HLINE);
        addch (ACS_RTEE);

        for (int i = 0; i < arr_size; i++){
            mvaddch((maxrow - arr_size)/ 2 + i, (maxcol - MAX_NAME - MAX_NUM)/2 , ACS_VLINE);
            if (curpos == i)
                attron(A_STANDOUT);
            for (int j = 0; j < MAX_NAME + MAX_NUM; j++) printw(" ");
            move((maxrow - arr_size)/ 2 + i, (maxcol - MAX_NAME - MAX_NUM)/2 + 1 );
            printw(stud_arr[i] -> name); 
            mvprintw((maxrow - arr_size)/ 2 + i, (maxcol - MAX_NAME - MAX_NUM)/2 + MAX_NAME, "%d", stud_arr[i] -> num);
            attroff(A_STANDOUT);
            mvaddch((maxrow - arr_size)/ 2 + i, (maxcol - MAX_NAME - MAX_NUM)/2 + MAX_NAME + MAX_NUM, ACS_VLINE);
        }

        move ((maxrow - arr_size)/ 2 + arr_size , (maxcol - MAX_NAME - MAX_NUM)/2);
        addch (ACS_LLCORNER);
        for (int i = 0; i < MAX_NAME + MAX_NUM - 1; i++) addch(ACS_HLINE);
        addch (ACS_LRCORNER);

        move ((maxrow - arr_size)/ 2 + arr_size + 2 , (maxcol - 83)/2);
        attron(A_STANDOUT);
        printw("<ENTER> to see more info about student");
        attroff(A_STANDOUT);
        printw(" ");

        attron(A_STANDOUT);
        printw("<+> to add a student");
        attroff(A_STANDOUT);
        printw(" ");
        
        attron(A_STANDOUT);
        printw("<-> to remove a student");
        attroff(A_STANDOUT);

        move ((maxrow - arr_size)/ 2 + arr_size + 3 , (maxcol - 54)/2);

        attron(A_STANDOUT);
        printw("<Q> to go back");
        attroff(A_STANDOUT);
        printw(" ");

        attron(A_STANDOUT);
        printw("<N> to sort by name");
        attroff(A_STANDOUT);
        printw(" ");

        attron(A_STANDOUT);
        printw("<P> to save to file");
        attroff(A_STANDOUT);

        ch = getch();

    } while (ch != 'q' && ch != 'Q' && ch != 27);
}



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


Student* new_student(char* name, int num, double p1, double p2, double t1, double t2, double t3, double t4){

    Student* p_student = (Student *) malloc(sizeof(Student));
    p_student -> name = (char *) malloc(strlen(name) * sizeof(char) + 1);
    strcpy(p_student->name, name);
    p_student -> num = num;
    
    p_student -> test[0] = p1;
    p_student -> test[1] = p2;
    p_student -> assignment[0] = t1;
    p_student -> assignment[1] = t2;
    p_student -> assignment[2] = t3;
    p_student -> assignment[3] = t4;
    
    return p_student;

}

Student** arr_add_student(Student* p_student, Student** stud_arr){

    size_t arr_size;
    for (arr_size = 0; stud_arr[arr_size] != NULL; arr_size++);
    stud_arr = (Student **) realloc(stud_arr, ((int) arr_size + 2) * sizeof(Student *));
    stud_arr[arr_size] = p_student;                             
    stud_arr[(arr_size + 1)] = NULL;                              
    return stud_arr;

}

Student** arr_rm_student(Student** stud_arr, Student* stud){

    int flag = 0;
    for (int i = 0; stud_arr[i] != NULL; i++){
        if (stud_arr[i] -> num ==  stud -> num)
            flag = 1;
        if (flag == 1)
            stud_arr[i] = stud_arr[i+1];
    }
    free(stud);
    return stud_arr; 

}

int main(void){

    Student** stud_arr;
    Group** group_arr;
    stud_arr = get_students();
    group_arr = malloc(sizeof(Group *));;
    group_arr[0] = NULL;
    if (stud_arr == NULL){
        printw("Memory allocation error!\n");
        return 1;
    }
    /* TEMPORARY */
    group_arr = realloc(group_arr, sizeof(Group *) + 2);
    group_arr[0] = new_group(1, 9.8);
    group_arr[1] = new_group(2, 5.3);
    group_arr[2] = NULL;
    group_add_member(stud_arr[0], group_arr[0]);
    group_add_member(stud_arr[1], group_arr[1]);
    
	initscr(); noecho();
	keypad(stdscr, TRUE);
	nodelay(stdscr, FALSE);
	curs_set(0);

    size_t num_of_students;

    int maxrow, maxcol;
    getmaxyx(stdscr, maxrow, maxcol);

    clear();
    move(1,0);

    int ch;
    int curpos = 0;

    while(1){
         
        do {
            if (ch == KEY_UP || ch == 'w' || ch == 'W')
		    	curpos = (curpos - 1);	
 		    else if (ch == KEY_DOWN || ch == 's' || ch == 'S')
		    	curpos = (curpos + 1) % 3;
            if (curpos < 0)
                curpos = 2;
            
            if (ch == 'q'){
                curpos = 2;
                break;
            }


            clear();

            if (curpos == 0)
                attron(A_STANDOUT);
            mvprintw(maxrow / 2, (maxcol - 16) / 2, "LIST STUDENTS");
            attroff(A_STANDOUT);
            if (curpos == 1)
                attron(A_STANDOUT);
            mvprintw(maxrow / 2 + 2, (maxcol - 16) / 2, "LIST GROUPS");
            attroff(A_STANDOUT);
            if (curpos == 2)
                attron(A_STANDOUT);
            mvprintw(maxrow / 2 + 4, (maxcol - 16) / 2, "QUIT\n");
            attroff(A_STANDOUT);
        } while((ch = getch()) != '\n'); 
        if (curpos == 0)
            list_students(stud_arr);
        if (curpos == 1)
            list_groups(group_arr);
        if (curpos == 2)
            break;

    }
    
    for (num_of_students = 0; stud_arr[num_of_students] != NULL; num_of_students++); 
    
    for (size_t i = 1; i < num_of_students; i++){
        free(stud_arr[i] -> name);
        free(stud_arr[i]);
    }

    endwin();
    return 0;
}


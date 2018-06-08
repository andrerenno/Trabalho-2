
typedef struct Student {
    char *name;
    unsigned int num;
    double test[2];
    double assignment[4]; 
} Student;

typedef struct {
    int index;
    Student** members;
    double grade;
} Group;

/* Reads the students from the "Students.txt" file and returns them in an array */
Student ** get_students(void);

/* Writes the array to the "Students.txt" file */
void write_students(Student**);

/* Adds a student to the array */
Student** arr_add_student(Student*, Student**);

/* Removes a student from the array */
Student** arr_rm_student(Student**, Student*);

/* Returns a new pointer to a student */
Student* new_student(char*, int, double, double, double, double, double, double);

/* Sorts the students in the array by name */
void sort_students(Student**);

void draw_box(int, int, int, int);

void list_groups(Group**);
Group* new_group(int, double);
Group* group_add_member(Student*, Group*);

typedef struct Student {
    char *name;
    unsigned int num;
    int test[2];

} Student;

Student ** get_students(void);
void write_students(Student**);
Student** arr_add_student(Student*, Student**);
Student** arr_rm_student(Student**, Student*);
Student* new_student(char*, int);

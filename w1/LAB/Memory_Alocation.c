//Dynamic memory allocation practice

#include <stdio.h>
#include<stdlib.h>
#include <string.h>

struct Student{
    int student_id;
    float *quizes;
};

struct Student* AllocateStudents(int N, int Q)
{   
    struct Student *courses = (struct Student*)malloc(N*sizeof(struct Student*));

    for (int i=0; i< N; i++)
    {
        courses[i].student_id = rand();
        
        for (int j=0;j<Q;j++)
        {
            courses[i].quizes = malloc(sizeof(float));
            courses[i].quizes = rand();
        }
        printf("%d %d\n", courses[i].student_id,(int)courses[i].quizes);
        printf("\n\n");
    }
    return courses;
}

void free_up_memory (struct Student* st, int n)
{
    for (int i=0; i < n; i++)
    {
        free(st[i].quizes);
    }
    
    free(st);
}


int main(void)
{
    struct Student *array = (Student *)malloc (sizeof(struct Student));
    struct Student *students = AllocateStudents(5, 2);
    free_up_memory(students, 2);

    return 0;

}
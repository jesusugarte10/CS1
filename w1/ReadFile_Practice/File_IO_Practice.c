//File opening practice

#include <stdio.h>
#include <stdlib.h>
#define MAX 500

typedef struct Student
{
    int student_ID;
    int g1,g2,g3;
    float average;
} Student;

Student getMaxAverageStudent( Student *s, int  n)
{   
    int max_index = 0;
    float max = - 1;

    for(int i = 0;i < n; i++)
    {
        if (s[i].average > s[i-1].average)
        {
            max_index = i ;
        }
    }
    return s[max_index];
}

int main(void)
{
    int n;
    FILE *infile = fopen("students.txt","r");
    FILE *outfile = fopen("out.txt","w");
    fscanf(infile,"%d",&n);
    Student students[n];

    for(int i = 0; i < n; i++)
    {
        fscanf(infile,"%d",&students[i].student_ID);
        fscanf(infile,"%d %d %d",&students[i].g1,&students[i].g2,&students[i].g3);
        students[i].average = (students[i].g1+students[i].g2+students[i].g3)/3;
        printf("%d %d %d %d %0.2f\n", students[i].student_ID, students[i].g1, students[i].g2, students[i].g3, students[i].average);
        fprintf(outfile, "%d %d %d %d %0.2f\n", students[i].student_ID, students[i].g1, students[i].g2, students[i].g3, students[i].average);
    }
    Student maxStudent = getMaxAverageStudent(students, n);

    printf("\nMaximum Average is %0.2f and the student is %d\n", maxStudent.average, maxStudent.student_ID);
    fprintf(outfile, "\nMaximum Average is %0.2f and the student is %d\n", maxStudent.average, maxStudent.student_ID);
    fclose(infile);
    fclose(outfile);
    
    return 0;
}
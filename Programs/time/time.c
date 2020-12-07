#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct Activities
{
    char *names;
    float value;
}Activities;

int main(void)
{

    FILE *outFile1 = fopen("time_report.csv", "w");
    fprintf(outFile1, "Activity, Time_Spent, Remaining_Hours, Remaining_Days, Remaining_Week\n");

    int n_questions = 10;
    char *names[] = {"Average Daily sleep", "Study", "Family", "Work", "Entertainment", "Friends", "Relationship", "Hobbys", "Social Media", "Reflection"};
    Activities* Activities = malloc(n_questions * sizeof(Activities) + 50 * sizeof(char));

    printf("\nHello, This is a time reflection app made By Jesus..");
    printf("\nPlease answer the following questions in hours Example: ('1.5'hr = '90'min)");
    sleep(1);

    float timeLeft = 24*7;

    for(int i=0;i<n_questions;i++)
    {
        printf("\n-------------------------------------------------------");
        printf("\n-> Weekly time left: %.2f Hr | %.2f Days | %.2f Week" , timeLeft , timeLeft/24, (timeLeft/24)/7);
        

        //Average Sleep Case
        if(i==0)
            Activities[i].value = Activities[i].value * 7;

        //regular case
        if(i!=1)
        {
            printf("\n\nHow much time for %s(Hr): ", names[i]);
            scanf("%f", &Activities[i].value);
        }
        else // school case i==1
        {
            //If there is classes present iterate in loop
            printf("\n\nHow many classes are you taking(Qty): ");
            int nClasses = 0;
            float temp = 0;
            scanf("%d", &nClasses);

            for(int j=0; j<nClasses; j++)
            {
                printf("\n\nHow much time for Class #%d (Hr): ", j+1);
                scanf("%f", &temp);
                Activities[i].value += temp;
            }
        }

        //Warning if no time is left
        if(timeLeft - Activities[i].value < 0)
            printf("\nWARNING: NOT ENOUGH TIME");
        
        Activities[i].names = names[i];
        timeLeft -= Activities[i].value;
        fprintf(outFile1, "%s, %.2f, %.2f, %.2f, %.2f\n", Activities[i].names, Activities[i].value, timeLeft, timeLeft/24, (timeLeft/24)/7);
    }
    fprintf(outFile1, "Not Assigned, -, -, -, %.2f\n", (timeLeft/24)/7);

    printf("\nGenerating Report");
    printf("\n+++++");
    sleep(2);
    printf("\n+++++++++");
    sleep(2);
    printf("\n+++++++++++++");
    sleep(2);
    printf("\n\nReport Created \nThank You Have a Good Day\n");

    free(Activities);

    fclose(outFile1);
    return 0;
}
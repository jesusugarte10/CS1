/* COP 3502C Assignment 1
This program is written by: Jesus Enrique Ugarte Osta */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "leak_detector_c.h"

#define string_MAX 51
#define population_MAX 1000000

//Structures
typedef struct monster 
{   int id;
    char *name;
    char *element;
    int population;
} monster;

typedef struct region 
{   char *name;
    int nmonsters;
    int total_population;
    monster **monsters;
} region;
 
typedef struct itinerary 
{   
    int nregions;
    region **regions;
    int captures; 
} itinerary;
  
typedef struct trainer 
{ 
    char *name;
    itinerary *visits; 
} trainer;

void debug(void)
{
    printf("Made it Here\n");
    fflush(stdout);
}

//Function to Create Monsters
monster* createMonster(char *name, char *element, int population)
{
    //This function returns a dynamically allocated monster filled with provided parameters
    monster *created_Monster = malloc(sizeof(struct monster));
    created_Monster->name = name;
    created_Monster->element = element;
    created_Monster->population = population;

    //Returning Value 
    return created_Monster;
}

//Function to read and return Monsters
monster** readMonsters(FILE* infile, int *monsterCount)
{
    monster **Monster = calloc(*monsterCount, (sizeof(struct monster*)));
    
    for (int i = 0; i < *monsterCount; i++)
    {
        char *temp_name = malloc(string_MAX * sizeof(char));
        char *temp_element = malloc(string_MAX * sizeof(char));
        int population ;

        fscanf(infile,"%s %s %d",temp_name, temp_element, &population);

        //Passing Values to the CreateMonster Function
        Monster[i] = createMonster(temp_name, temp_element, population);
        Monster[i]->id = i;
    }
    return Monster;
}

//Function to read regions
region** readRegions(FILE* infile, monster **Monsters, int *mcount, int *regionCount)
{
    int i,j,k;
    region **created_region = calloc(*regionCount, sizeof(struct region*));

    for (i = 0 ; i < *regionCount; i++)
    {   
        //Allocating Memory
        created_region[i] = malloc (sizeof(struct region));
        created_region[i]->name = malloc(string_MAX * sizeof(char));
        fscanf(infile, "%s", created_region[i]->name);

        fscanf(infile, "%d %*s",&created_region[i]->nmonsters);

        created_region[i]->monsters = malloc( created_region[i]->nmonsters * sizeof(monster*));

        //Loop for n number of monsters in the region
        for ( j = 0; j < created_region[i]->nmonsters ;j++)
        {   
            //allocation memory for array of monster names in regions
            created_region[i]->monsters[j] = malloc(*mcount * sizeof(monster));
            created_region[i]->monsters[j]->name = malloc( string_MAX * sizeof(char));
            fscanf(infile, "%s", created_region[i]->monsters[j]->name);

            for (int k = 0; k < *mcount; k++)
            {   
                //Assigning Values
                if(strcmp(created_region[i]->monsters[j]->name , Monsters[k]->name)==0)
                {
                    created_region[i]->monsters[j]->population = Monsters[k]->population;
                    created_region[i]->total_population += Monsters[k]->population;
                }
            }
        }
    }
    return created_region;
}

//Function to allocate memory for itinerary
trainer* readTrainers(FILE* infile, region **Regions, monster **Monsters,  int *regionCount, int *mcount, int *trainerCount)
{
    int i,j,k;
    trainer *created_trainer = malloc(*trainerCount * sizeof(struct trainer));

    for (i = 0 ; i < *trainerCount; i++)
    {   
        created_trainer[i].name = malloc(string_MAX * sizeof(char));
        fscanf(infile, "%s", created_trainer[i].name);
        
        created_trainer[i].visits = malloc (sizeof(struct itinerary));

        fscanf(infile, "%d %*s", &created_trainer[i].visits->captures);
        fscanf(infile, "%d %*s", &created_trainer[i].visits->nregions);

        created_trainer[i].visits->regions = calloc( created_trainer[i].visits->nregions, sizeof(region*));
        
        //scanning the value of the names of the region for each trainer
        for (int j = 0; j < created_trainer[i].visits->nregions;j++)
        {   
            created_trainer[i].visits->regions[j] = malloc(sizeof(region));
            created_trainer[i].visits->regions[j]->name = malloc(sizeof(string_MAX * sizeof(char)));
            fscanf(infile, "%s", created_trainer[i].visits->regions[j]->name);

            //Setting up total population for each region
            for(int k = 0; k < *regionCount; k++)
            {
                //Comparing Values to start assigning values for each region of trainers
                if(strcmp(created_trainer[i].visits->regions[j]->name, Regions[k]->name)==0)
                {
                    //Assigning name and total population
                    created_trainer[i].visits->regions[j]->total_population = Regions[k]->total_population;
                    created_trainer[i].visits->regions[j]->nmonsters = Regions[k]->nmonsters;

                    //Allocating Memory for array of monsters
                    created_trainer[i].visits->regions[j]->monsters = calloc(created_trainer[i].visits->regions[j]->nmonsters, sizeof(struct monster*));

                    for(int m = 0; m < created_trainer[i].visits->regions[j]->nmonsters; m++)
                    {
                        //Allocating memory
                        created_trainer[i].visits->regions[j]->monsters[m] = malloc(sizeof(struct monster));
                        
                        //Assignning Values 
                        created_trainer[i].visits->regions[j]->monsters[m]->name = Regions[k]->monsters[m]->name;
                        created_trainer[i].visits->regions[j]->monsters[m]->population = Regions[k]->monsters[m]->population; 

                    }
                }
            }     
        }

    }
    return created_trainer;
}

//Function to Calculate and Print Results
void calculate_Results(FILE *outFile, trainer *Trainers, int*tcount)
{
    int estimate = 0;

    for (int  t = 0; t < *tcount; t++)
    {
        printf("%s", Trainers[t].name);
        fprintf(outFile,"%s", Trainers[t].name);

        for (int tr = 0; tr < Trainers[t].visits->nregions; tr++)
        {
            printf("\n%s", Trainers[t].visits->regions[tr]->name);
            fprintf(outFile,"\n%s", Trainers[t].visits->regions[tr]->name);
            
            for (int trm = 0; trm < Trainers[t].visits->regions[tr]->nmonsters ; trm++)
            {
                //Calculating the estimate
                estimate =round((1.0*Trainers[t].visits->regions[tr]->monsters[trm]->population / Trainers[t].visits->regions[tr]->total_population) * Trainers[t].visits->captures);

                //If estimate is not zero go ahead and print the value
                if(estimate != 0)
                {
                    printf("\n%d %s",estimate, Trainers[t].visits->regions[tr]->monsters[trm]->name);
                    fprintf(outFile, "\n%d %s",estimate, Trainers[t].visits->regions[tr]->monsters[trm]->name);
                }
            }
        }
    printf("\n\n");
    fprintf(outFile,"\n\n");
    }
}

//Function to Release Memory
void release_memory(monster **Monsters, int *mcount, region **Regions, int *rcount, trainer *Trainers, int *tcount)
{
    //Free Memory for Trainers Strcucture
    for (int i = 0 ; i < *tcount; i++)
    {   
        for (int j = 0; j < Trainers[i].visits->nregions; j++)
        {   
            for(int k = 0; k < *rcount; k++)
            {   
                if(strcmp(Trainers[i].visits->regions[j]->name, Regions[k]->name)==0)
                {
                    for(int m = 0; m < Trainers[i].visits->regions[j]->nmonsters; m++)
                    {
                        free(Trainers[i].visits->regions[j]->monsters[m]);
                    }
                    free(Trainers[i].visits->regions[j]->monsters);
                } 
            }     
            free(Trainers[i].visits->regions[j]->name);
            free(Trainers[i].visits->regions[j]);
        }
        free(Trainers[i].visits->regions);
        free(Trainers[i].visits);
        free(Trainers[i].name);
    } 
    free(Trainers);

    //Free memory for regions structure
    for (int i = 0 ; i < *rcount; i++)
    {
        for ( int j = 0; j < Regions[i]->nmonsters ;j++)
        {   
            free(Regions[i]->monsters[j]->name);
            free(Regions[i]->monsters[j]);
        }
        free(Regions[i]->name);
        free(Regions[i]->monsters);
        free(Regions[i]);
    }
    free(Regions);

    //Free memory for Monster Structure
    for (int i = 0; i < *mcount;i ++)
    {
        free(Monsters[i]->name);
        free(Monsters[i]->element);
        free(Monsters[i]);
    }
    free (Monsters);
}

//Main Function
int main(void)
{
    atexit(report_mem_leak);

    //Opening Files
    FILE *inFile, *outFile;
    inFile = fopen("in.txt", "r");
    outFile = fopen("out.txt", "w");

    //Making sure the file is not NULL
    if(inFile == NULL)
    {
        printf("Please provide correct input file");
        return 1;
    }
    else
    {   
        monster **Monsters;
        region **Regions;
        trainer *Trainers;

        int mcount, rcount, tcount;
        fscanf(inFile, "%d %*s", &mcount);
        Monsters = readMonsters(inFile, &mcount);

        fscanf(inFile, "%d %*s", &rcount);
        Regions = readRegions(inFile, Monsters, &mcount, &rcount);

        fscanf(inFile, "%d %*s", &tcount);
        Trainers = readTrainers(inFile, Regions, Monsters, &rcount, &mcount, &tcount);

        calculate_Results(outFile , Trainers, &tcount);

        release_memory(Monsters, &mcount, Regions, &rcount, Trainers, &tcount);

        fclose(inFile);
        fclose(outFile);
    }
    return 0;
}
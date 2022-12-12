#include <stdio.h>
#include <string.h>
#include <feature.h>
#include <task.h>
#include <userStory.h>
#include <main.h>
#include <stdlib.h>

/*This function will check for the user is present in the CSV or not and if it is present in the CSV
then it will check that the user is Scrum Master or Team Member and return 1 if user is Scrum Master and 0 if its Team Member*/
int checkLogin(int userId,char password[]){
    int userResult=-1;
    char* data;
    FILE *usersDataFile=fopen("../external/usersData.csv","r");
    if (usersDataFile==NULL){
        printf("Feature File not found");
        exit(0);
    }
    char userData[500];
    while(fgets(userData,500,usersDataFile)!=NULL){
        data=strtok(userData,",");
        data=strtok(NULL,",");
        int data2;
        data2=atoi(data);
        if (userId==data2){
            data=strtok(NULL,",");
            if(strcmp(data,password)==0){
                data=strtok(NULL,",");
                userResult=atoi(data);
                break;
            }
        }
    }
    fclose(usersDataFile);
    return userResult;
}
/*This function will free the memory taken by all Linked Lists in the program for example UserStories
,Tasks and Feature structure*/
void freeStructures(){
    freeUserStoriesLL();
	freeTasksLL();
    freeFeatures();
}
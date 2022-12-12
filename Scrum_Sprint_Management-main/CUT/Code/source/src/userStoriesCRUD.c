#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <feature.h>
#include <userStory.h>
#include <main.h>
#include <task.h>
#define LINE_SIZE 500
userStory *userStoryHead=NULL;
/*This function will take the input values and create a User Story Linked list*/
void createUserStoryLL(int info,int info1,double info2,char name[],char desc[])
{
        userStory *temp,*ptr;
        temp=(userStory *)malloc(sizeof(userStory));
        temp->storyId=info;
        temp->featureId=info1;
        temp->completionStatus=info2;
        strncpy(temp->storyName,name,STORY_NAME_LEN-1);
        strncpy(temp->storyDesc,desc,STORY_DESC_LEN-1);
        temp->next=NULL;
        if(userStoryHead==NULL)
        {
            userStoryHead=temp;
        }
        else
        {
            ptr=userStoryHead;
            while(ptr->next!=NULL)
            {
                ptr=ptr->next;
            }
            ptr->next=temp;
        }
}
/*This will check if the story id is present or not in Linked list*/
int checkStory(int storyId){
    userStory *ptr;
    ptr=userStoryHead;
    while(ptr!=NULL)
    {
        if (ptr->storyId==storyId){
            return 1;
            break;
        }
        ptr=ptr->next ;
    }
    return 0;
}
/*This will update the feature completion status when user story is updated*/
void updateFeatureFromUserStory(){
    double featureStatus=userStoryHead->completionStatus;
    updateFeature(featureStatus);
}
/*This function will print the Linked List of User Stories with all values present in it*/
void displayUserStoryLL()
{
        userStory *ptr;
        if(userStoryHead==NULL)
        {
            printf("\nList is empty:\n");
            return;
        }
        else
        {
            ptr=userStoryHead;
            printf("\n------------------------------------------------User Story Report------------------------------------------------\n");
                printf("\n Story ID:\tReport ID:\tCompletion Status:\tStory Name:\t\t\t\t\tStory Info\n");
            while(ptr!=NULL)
            {
                printf("\t%d\t\t",ptr->storyId);
                printf("%d\t\t",ptr->featureId);
                printf("%lf\t",ptr->completionStatus);
                printf("%s",ptr->storyName);
                printf("\t\t\t%s\n",ptr->storyDesc);
                ptr=ptr->next ;
            }
            printf("\n--------------------------------------------END of User Story Report---------------------------------------------\n");
        }
}
/*This function will take the input and append the userStories.csv file with given values*/
void appendUserStoryCSV(int a,int b,double c,char name[],char desc[]){
    FILE *userStoryFile=fopen("../external/userStories.csv","a");
    if (userStoryFile==NULL){
        printf("User Story File not found");
        exit(0);
    }
    else{
        fprintf(userStoryFile,"%d,%d,%lf,%s,%s\n",a,b,c,name,desc);
    }   
    fclose(userStoryFile);
}
/*This function will take values and append the User Story Linked List with a new node*/
void insert_end(int a,int b,double c,char name[],char desc[])
{
    userStory *temp,*ptr;
    temp=(userStory *)malloc(sizeof(userStory));
    if(temp==NULL)
    {
        printf("\nOut of Memory Space:\n");
        return;
    }
        
    temp->storyId=a;
    temp->featureId=b;
    temp->completionStatus=c;
    strncpy(temp->storyName,name,STORY_NAME_LEN-1);
    strncpy(temp->storyDesc,desc,STORY_DESC_LEN-1);
    temp->next =NULL;
    if(userStoryHead==NULL)
    {
        userStoryHead=temp;
        }
    else
    {
        ptr=userStoryHead;
        while(ptr->next !=NULL)
        {
            ptr=ptr->next ;
        }
        ptr->next =temp;
    }
}
/*This function will update the completion status of the User Story if the task of that user Story updated
by the user*/
void updateUserStoriesLLfromTaskData(task *taskHead){
    userStory *userStoryptr;
    task *taskPtr;
    userStoryptr=userStoryHead;
    taskPtr=taskHead;
    while(userStoryptr!=NULL)
    {
        int totalCompletionStatus=0;
        int countOfNodes=0;
        while(taskPtr!=NULL){
            if (userStoryptr->storyId==taskPtr->storyId){
                totalCompletionStatus+=taskPtr->completionStatus;
                countOfNodes+=1;
            }
            taskPtr=taskPtr->next;
        }
        userStoryptr->completionStatus=(double)totalCompletionStatus/(double)countOfNodes;
        userStoryptr=userStoryptr->next;
    }
    updateUserStoryCSVFromLL();
}
/*This function will update the userStories.csv file if the Linked List of user Stories is updated*/
void updateUserStoryCSVFromLL(){
    userStory *ptr;
    if(userStoryHead==NULL)
    {
        printf("\nList is empty:\n");
        return;
    }
    else{
        ptr=userStoryHead;
        FILE *taskFile=fopen("../external/userStories.csv","w");
        while(ptr!=NULL)
        {
            fprintf(taskFile,"%d,%d,%lf,%s,%s\n",ptr->storyId,ptr->featureId,ptr->completionStatus,ptr->storyName,ptr->storyDesc);
            ptr=ptr->next ;
        }
        fclose(taskFile);
    }
}
/*This function will load the data in userStories.csc and create a user Stories Linked List from it when the program starts*/
void loadUserStories(){
    FILE *userStoryFile=fopen("../external/userStories.csv","r");
    if (userStoryFile==NULL){
        printf("User Story File not found");
        exit(0);
    }
    else{
		char userStoryFileData[LINE_SIZE];
        char *data;
		while(1){
            if (fgets(userStoryFileData, LINE_SIZE, userStoryFile) == NULL){
                break;
            }
            else{
                if (userStoryFileData[0]!='\n'){
                    data=strtok(userStoryFileData,",");
                    int a=atoi(data);
                    data=strtok(NULL,",");
                    int b=atoi(data);
                    data=strtok(NULL,",");
                    double c=atoi(data);
                    char name[100];
                    char desc[300];
                    data=strtok(NULL,",");
                    strncpy(name,data,STORY_NAME_LEN-1);
                    data=strtok(NULL,",");
                    strncpy(desc,data,STORY_DESC_LEN-1);
                    insert_end(a,b,c,name,desc);
                }
            }
        }
    }
    fclose(userStoryFile);
}
/*This function will free the User Stories Linked List memory when program is exiting*/
void freeUserStoriesLL(){
    userStory *tempNode=NULL;
    while ((tempNode=userStoryHead)!=NULL)
    {
        userStoryHead=userStoryHead->next;
        free(tempNode);
    }
    
}
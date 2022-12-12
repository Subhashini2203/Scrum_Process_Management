#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <feature.h>
#include <userStory.h>
#include <main.h>
#include <task.h>
#define LINE_SIZE 500

task *taskHead=NULL;
/*This function will take the input values and create a task Linked list*/
void createTaskLL(int info,int info1,int info2,int info3,char name[],char desc[])
{
        task *temp,*ptr;
        temp=(task *)malloc(sizeof(task));
        temp->taskId=info;
        temp->storyId=info1;
        temp->completionStatus=info2;
        temp->userid=info3;
        strncpy(temp->taskName,name,TASK_NAME_LEN-1);
        strncpy(temp->taskDesc,desc,TASK_DESC_LEN-1);
        temp->next=NULL;
        if(taskHead==NULL)
        {
            taskHead=temp;
        }
        else
        {
            ptr=taskHead;
            while(ptr->next!=NULL)
            {
                ptr=ptr->next;
            }
            ptr->next=temp;
        }
}
int checkTask(int taskId){
    task *tmp;
    tmp=taskHead;
    while(tmp!=NULL)
    {
        if (tmp->taskId==taskId){
            return 1;
            break;
        }   
        tmp=tmp->next ;
    }
    return 0;

}
/* This function is providing head of linked list to the updateUserStoriesLLfromTaskData()*/
void calculations(){
    task *temp;
    temp=taskHead;
    updateUserStoriesLLfromTaskData(temp);
}
/*This function will update the completion status of a Task when user enter new value of completion status*/
void updateCompletionStatus(int taskId,int newCompletionStatus){
    task *ptr;
    if(taskHead==NULL)
    {
        printf("nList is empty:n");
        return;
    }
    else{
        ptr=taskHead;
        while(ptr!=NULL)
        {
            if (ptr->taskId==taskId){
                ptr->completionStatus=newCompletionStatus;
                printf("\nTask Updated\n");
                break;
            }
            ptr=ptr->next ;
        }
    }
    updateTaskCSVFromLL();
}
/*This function will update the tasks.csv file if the Linked List of user Stories is updated*/
void updateTaskCSVFromLL(){
    task *ptr;
    if(taskHead==NULL)
    {
        printf("\nList is empty:\n");
        return;
    }
    else{
        ptr=taskHead;
        FILE *taskFile=fopen("../external/tasks.csv","w");
        while(ptr!=NULL)
        {
            fprintf(taskFile,"%d,%d,%d,%d,%s,%s\n",ptr->taskId,ptr->storyId,ptr->completionStatus,ptr->userid,ptr->taskName,ptr->taskDesc);
            ptr=ptr->next ;
        }
        fclose(taskFile);
    }
}
/*This function will print the Linked List of task with all values present in it*/
void displayTaskLL()
{
        task *ptr;
        if(taskHead==NULL)
        {
            printf("\nList is empty:\n");
            return;
        }
        else
        {
            ptr=taskHead;
            printf("\n------------------------------------------------Tasks Report------------------------------------------------\n");
                printf("\n Task ID:\tStory ID:\tCompletion Status:\tUser ID: \tTask Name:\t\t\t\t\tTask Info\n");
            while(ptr!=NULL)
            {
                printf("\t%d\t\t",ptr->taskId);
                printf("%d\t\t",ptr->storyId);
                printf("%d\t",ptr->completionStatus);
                printf("\t%d\t",ptr->userid);
                printf("\t%s",ptr->taskName);
                printf("\t\t\t%s\n",ptr->taskDesc);
                ptr=ptr->next ;
            }
            printf("\n-------------------------------------------END of Tasks Report---------------------------------------------\n");
        }
}
/*This function will display the tasks assigned to a user by Scrum Master by taking useId as input*/
void displayUserTasks(int userid){
    task *ptr;
    if(taskHead==NULL)
    {
        printf("\nList is empty:\n");
        return;
    }
    else{
        ptr=taskHead;
        printf("\n------------------------------User Story Report  ----------------------------------------\n");
        printf("\n Task ID:\tStory ID:\tCompletion Status:\tUser ID: \tTask Name:\t\t\tTask Info\n");
        while(ptr!=NULL)
        {
            if (ptr->userid==userid){
                printf("\t%d\t\t",ptr->taskId);
                printf("%d\t\t",ptr->storyId);
                printf("%d\t",ptr->completionStatus);
                printf("\t%d\t",ptr->userid);
                printf("\t%s",ptr->taskName);
                printf("\t\t%s\n",ptr->taskDesc);
            }
            ptr=ptr->next ;
        }
        printf("\n-----------------------------END of User Story  Report----------------------------------\n");
    }
}
/*This function will append the Linked List of Tasks*/
void appendTaskLL(int a,int b,int c,int d,char name[],char desc[])
{
    task *temp,*ptr;
    temp=(task *)malloc(sizeof(task));
    if(temp==NULL)
    {
        printf("\nOut of Memory Space:n");
        return;
    }
        
    temp->taskId=a;
    temp->storyId=b;
    temp->completionStatus=c;
    temp->userid=d;
    strncpy(temp->taskName,name,TASK_NAME_LEN-1);
    strncpy(temp->taskDesc,desc,TASK_DESC_LEN-1);
    temp->next =NULL;
    if(taskHead==NULL)
    {
        taskHead=temp;
    }
    else
    {
        ptr=taskHead;
        while(ptr->next !=NULL)
        {
            ptr=ptr->next ;
        }
        ptr->next =temp;
    }
    
}
/*This function will load the Tasks from tasks.csv and create a linked list by extracting the data from CSV*/
void loadTasks(){
    FILE *taskFile=fopen("../external/tasks.csv","r");
    if (taskFile==NULL){
        printf("User Story File not found");
        exit(0);
    }
    else{
		char taskFileData[LINE_SIZE];
        char *data;
		while(1){
            if (fgets(taskFileData, LINE_SIZE, taskFile) == NULL){
                break;
            }
            else{
                if (taskFileData[0] != '\n'){
                    data=strtok(taskFileData,",");
                    int a=atoi(data);
                    data=strtok(NULL,",");
                    int b=atoi(data);
                    data=strtok(NULL,",");
                    int c=atoi(data);
                    data=strtok(NULL,",");
                    int d=atoi(data);
                    char name[100];
                    char desc[300];
                    data=strtok(NULL,",");
                    strncpy(name,data,TASK_NAME_LEN-1);
                    data=strtok(NULL,",");
                    strncpy(desc,data,TASK_DESC_LEN-1);
                    appendTaskLL(a,b,c,d,name,desc);
                }         
            }
        }
    }
    fclose(taskFile);
}
/*This function will take the input and append the tasks.csv file with given values*/
void appendTasksCSV(int a,int b,int c,int d,char name[],char desc[]){
    FILE *taskFile=fopen("../external/tasks.csv","a");
    if (taskFile==NULL){
        printf("User Story File not found");
        exit(0);
    }
    else{
        fprintf(taskFile,"%d,%d,%d,%d,%s,%s\n",a,b,c,d,name,desc);
    }   
    fclose(taskFile);
}
/*This function will free the memory taken by Tasks Linked List when program is exiting*/
void freeTasksLL(){
    task *tempNode=NULL;
    while ((tempNode=taskHead)!=NULL)
    {
        taskHead=taskHead->next;
        free(tempNode);
    }
    
}
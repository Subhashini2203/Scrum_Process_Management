#include <stdio.h>
#include <string.h>
#include <feature.h>
#include <task.h>
#include <userStory.h>
#include <main.h>
#include <stdlib.h>
int main()
{
	loadFeatures();
	loadUserStories();
	loadTasks();
	printf("\n\t--------------------------------------------");
    printf("\n\t---     Welcome to Scrum Process Management      ---");
    printf("\n\t------------------------------------------------");
	int ch=1;
	while(ch!=0)
	{
		printf("\n1 to Login as Scrum Master:");
		printf("\n2 to Login as Team Member:");
		printf("\n0 to Exit:\n");
		scanf("%d",&ch);
		if (ch==1)
		{
			int userId;
			char userPassword[50];
			printf("\nEnter Scrum Master ID:");
			scanf("%d",&userId);
			printf("\nEnter Password:");
			scanf("%s",userPassword);
			int userBelonging;
			userBelonging=checkLogin(userId,userPassword);
			if (userBelonging==-1)
			{
				printf("\nEither userid or password is incorrect!\n");
				continue;
			}
			else if(userBelonging==1)
			{
				printf("\nLogged in as Scrum Master!\n");
				int tlChoice1=1;
				while(tlChoice1!=0)
				{
					printf("\n1. Print Report:");
					printf("\n2. Add New User Story:");
					printf("\n3. Add New Task:\n");
					scanf("%d",&tlChoice1);
					if (tlChoice1==1)
					{
						// printFeatures(f1);
						printFeatures();
						printf("\n");
						displayUserStoryLL();
						printf("\n");
						displayTaskLL();
						continue;
					}
					else if(tlChoice1==2)
					{
						int storyId,featureId;
						double completionStatus;
						char storyName[STORY_NAME_LEN]; 
						char storyDesc[STORY_DESC_LEN];
						printf("\nEnter User Story Details:");
						printf("\nEnter Story ID:");
						scanf("%d",&storyId);
						printf("\nEnter Report ID:");
						scanf("%d",&featureId);
						int res=checkFeature(featureId);
						if (res==0){
							printf("\nReport Id is not present Currently!\n");
							continue;
						}
						else{
							printf("\nEnter Completion Status:");
							scanf("%lf",&completionStatus);
							printf("\nEnter Story Name:");
							scanf("%s",storyName);
							printf("\nEnter Story Description:");
							scanf("%s",storyDesc);
							if((storyId<0 || storyId>99999) || (featureId<0 || featureId>99) || (completionStatus<0 || completionStatus>100)){
								printf("\nEntered data is not Correct!\n");
								continue;
							}
							else{
								insert_end(storyId,featureId,completionStatus,storyName,storyDesc);
								appendUserStoryCSV(storyId,featureId,completionStatus,storyName,storyDesc);
								displayUserStoryLL();
								continue;
							}
						}
						
					}
					else if(tlChoice1==3)
					{
						int taskId,storyId,completionStatusTask,userId;
						char taskName[TASK_NAME_LEN];
						char taskDesc[TASK_DESC_LEN];
						printf("\nEnter Task Details:");
						printf("\nEnter Task ID:");
						scanf("%d",&taskId);
						printf("\nEnter Story ID:");
						scanf("%d",&storyId);
						int res=checkStory(storyId);
						if (res==0){
							printf("\nInvalid Story Id.\n");
							continue;
						}
						else{
							printf("\nEnter Completion Status:");
							scanf("%d",&completionStatusTask);
							printf("\nEnter User ID:");
							scanf("%d",&userId);
							printf("\nEnter Task Name:");
							scanf("%s",taskName);
							printf("\nEnter Task Description:");
							scanf("%s",taskDesc);
							if((taskId<0 || taskId>99999) || (storyId<0 || storyId>99) || (userId<0 || userId>99999)|| (completionStatusTask<0 || completionStatusTask>100)){
								printf("\nEntered data is not Correct!\n");
								continue;
							}
							else{
								appendTaskLL(taskId,storyId,completionStatusTask,userId,taskName,taskDesc);
								appendTasksCSV(taskId,storyId,completionStatusTask,userId,taskName,taskDesc);
								displayTaskLL();
								continue;
							}
						}	
					}
					else{
						if(tlChoice1!=0){
							printf("\nPlease enter a valid choice!\n");
							continue;
						}
						
					}
				}
				freeStructures();
				exit(0);
			}
			else
			{
				printf("\nYou cannot login as Scrum Master from here!\n");
				continue;
			}
		}
		else if (ch==2)
		{
			int userId;
			char userPassword[50];
			printf("\nEnter Team member ID:");
			scanf("%d",&userId);
			printf("\nEnter User Password:");
			scanf("%s",userPassword);
			int userBelonging;
			userBelonging=checkLogin(userId,userPassword);
			if (userBelonging==-1)
			{
				printf("\nEither Team member id or password is incorrect!\n");
				continue;
			}
			else if(userBelonging==0)
			{
				printf("\nLogged in as team Member!\n");
				int tlchoice2=1;
				while(tlchoice2!=0)
				{
					printf("\n1. print My Assigned Tasks:");
					printf("\n2. Update Task:");
					printf("\n0. Exit:\n");
					scanf("%d",&tlchoice2);
					if (tlchoice2==1)
					{
						displayUserTasks(userId);
						continue;
					}
					else if (tlchoice2==2)
					{
						int taskId,completionStatus;
						printf("\n Enter Task ID to Update:");
						scanf("%d",&taskId);
						int res=checkTask(taskId);
						if (res==0){
							printf("\nInvalid Task Id:\n");
							continue;
						}
						else{
							printf("\n Enter New Completion Status:");
							scanf("%d",&completionStatus);
							updateCompletionStatus(taskId,completionStatus);
							calculations();
							updateFeatureFromUserStory();
							continue;
						}	
					}
					else
					{
						if (tlchoice2!=0){
							printf("\nEnter a valid choice!\n");
							continue;
						}
						
					}
				}
				freeStructures();
				exit(0);
			}
			else
			{
				printf("\nYou cannot login as Scrum Master from here!\n");
				continue;
			}
		}
		else{
			if(ch!=0){
				printf("\nPlease enter a valid choice!\n");
				continue;
			}
		}
	}
	freeStructures();
	printf("\nExiting...!\n");
	exit(0);
}

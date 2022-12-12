#ifndef __MAIN_H__
#define __MAIN_H__
#include <feature.h>
#include <task.h>
#include <userStory.h>
#define STORY_NAME_LEN 100
#define STORY_DESC_LEN 300
#define TASK_NAME_LEN 100
#define TASK_DESC_LEN 200
extern void printFeatures();
extern void loadFeatures();
extern void createTaskLL(int info,int info1,int info2,int info3,char name[],char desc[]);
extern void calculations();
extern void updateCompletionStatus(int taskId,int newCompletionStatus);
extern void updateTaskCSVFromLL();
extern void displayTaskLL();
extern void displayUserTasks(int userid);
extern void appendTaskLL(int a,int b,int c,int d,char name[],char desc[]);
extern void loadTasks();
extern void appendTasksCSV(int a,int b,int c,int d,char name[],char desc[]);
extern void create(int info,int info1,double info2,char name[],char desc[]);
extern void displayUserStoryLL();
extern void appendUserStoryCSV(int a,int b,double c,char name[],char desc[]);
extern void insert_end(int a,int b,double c,char name[],char desc[]);
extern void updateUserStoriesLLfromTaskData(task *taskHead);
extern void updateUserStoryCSVFromLL();
extern void loadUserStories();
extern int checkLogin(int userId,char password[]);
extern void freeStructures();
extern void freeUserStoriesLL();
extern void freeTasksLL();
extern void freeFeatures();
extern int checkFeature();
extern int checkTask();
extern int checkStory();
extern void updateFeature(double status);
extern void updateFeatureCSV();
extern void updateFeatureFromUserStory();
#endif
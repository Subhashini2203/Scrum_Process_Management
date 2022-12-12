#pragma once
#define TASK_NAME_LEN 100
#define TASK_DESC_LEN 200
typedef struct _task_
{
    int taskId;     
    int storyId;    
    int completionStatus;  
    int userid;
    char taskName[TASK_NAME_LEN];
    char taskDesc[TASK_DESC_LEN];
    struct _task_ *next;
} task;

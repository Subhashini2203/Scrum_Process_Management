#pragma once
#define STORY_NAME_LEN 100
#define STORY_DESC_LEN 300
typedef struct _userStory_
{
    int storyId;     
    int featureId;   
    double completionStatus;
    char storyName[STORY_NAME_LEN];
    char storyDesc[STORY_DESC_LEN];
    struct _userStory_ *next;
} userStory;

#pragma once

#define FEATURE_NAME_LEN 100
#define FEATURE_DESC_LEN 300
typedef struct _feature_
{
    int featureId;           
    double completionStatus; 
    char featureName[FEATURE_NAME_LEN];
    char featureDesc[FEATURE_DESC_LEN];
    
} feature;


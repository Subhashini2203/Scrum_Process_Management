#include <stdio.h>
#include <string.h>
#include <feature.h>
#include <task.h>
#include <userStory.h>
#include <main.h>
#include <stdlib.h>
#define LINE_SIZE 500
feature *f1=NULL;
/*This function will print the Features*/
void printFeatures(){
	printf("\n------------------------------------------------Scrum Master Report------------------------------------------------\n");
	printf("\nReport ID:\tCompletion Status:\tReport Name:\t\t\tComment:");
	printf("\n\t%d",f1->featureId);
	printf("\t\t%lf",f1->completionStatus);
	printf("\t%s",f1->featureName);
	printf("\t\t\t%s\n",f1->featureDesc);
	printf("\n--------------------------------------------END of Report---------------------------------------------\n");

}

/*This function will load the Feature details from the features.csv file and creating a structure of feature with the values
present in the features.csv file*/
void loadFeatures(){
	feature *temp;
    temp=(feature *)malloc(sizeof(feature));
    FILE *feature_file=fopen("../external/features.csv","r");
    if (feature_file==NULL){
        printf("Feature File not found");
        exit(0);
    }
	else{
		char featureFileData[LINE_SIZE];
		fgets(featureFileData,LINE_SIZE,feature_file);
		char* data;
		data=strtok(featureFileData,",");
		if ( data != NULL )
    	{
			temp->featureId=atoi(data);
    	}
		data=strtok(NULL,",");
		if ( data != NULL )
    	{
			temp->completionStatus=atoi(data);
    	}
		data=strtok(NULL,",");
		if ( data != NULL )
    	{
			strncpy(temp->featureName,data,FEATURE_NAME_LEN-1);
    	}
		data=strtok(NULL,",");
		if ( data != NULL )
    	{
			strncpy(temp->featureDesc,data,FEATURE_DESC_LEN-1);
    	}
	}
	fclose(feature_file);
	f1=temp;
}
/*This will free the memory of structure created for the feature file*/
void freeFeatures(){
	free(f1);
}
/*This function will if check the feature id is present in csv or not.*/
int checkFeature(int fid){
	if (f1->featureId==fid){
		return 1;
	}
	else{
		return 0;
	}
}
/*This feature will update the completion status of Feature*/
void updateFeature(double status){
	f1->completionStatus=status;
	updateFeatureCSV();
}
/*This feature will update the CSV of feature*/
void updateFeatureCSV(){
	FILE *ptr=fopen("../external/features.csv","w");
	fprintf(ptr,"%d,%lf,%s,%s\n",f1->featureId,f1->completionStatus,f1->featureName,f1->featureDesc);
	fclose(ptr);
}
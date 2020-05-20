#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "intal.h"

int main(int argc, char const *argv[]) {
	
	char intal1[1000];
	char intal2[1000];
	char result1[1000];
	scanf("%s",intal1);
	scanf("%s",intal2);
	scanf("%s",result1);
	char* result = intal_add(intal1,intal2);
	if(strcmp(result,result1) == 0){
		printf("Addition passed\n");
	}
	else{
		printf("Addition failed\n");
	}
	free(result);
	scanf("%s",result1);
	result = intal_diff(intal1,intal2);
	if(strcmp(result,result1) == 0){
		printf("Subtraction passed\n");
	}
	else{
		printf("Subtraction failed\n");
	}
	free(result);
	result = intal_multiply(intal1,intal2);
	scanf("%s",result1);
	if(strcmp(result,result1) == 0){
		printf("Multiplication passed\n");
	}
	else{
		printf("Multiplication failed");
	}
	free(result);
	scanf("%s",result1);
	result = intal_mod(intal1,intal2);
	if(strcmp(result,result1) == 0){
		printf("Mod passed\n");
	}
	else{
		printf("Mod failed\n");
	}
	free(result);
	unsigned int n;
	scanf("%d",&n);
	scanf("%s",result1);
	result = intal_pow(intal1,n);
	if(strcmp(result,result1) == 0){
		printf("pow passed\n");
	}
	else{
		printf("pow failed\n");
	}
	return 0;

}
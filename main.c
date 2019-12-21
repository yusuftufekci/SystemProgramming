#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void removeEOL(char line[]){
    int i=0;
    while(line[i] != '\n')
        i++;
    line[i] = '\0';
}

void readLine(char line[]){
    fgets(line, 100,stdin);
    removeEOL(line);
}

int processLine(char* args[], char line[]){
    int i = 0;
    args[i] = strtok(line," ");

    if(args[i] == NULL){
        return 1;
    }

    while(args[i] != NULL){
        i++;
        args[i] = strtok(NULL," ");
    }
    return 1;
}


int readParseLine(char* args[], char line[]){
	printf(">");
    readLine(line);
    processLine(args,line);
    return 1;
}
 void sortTheFile(FILE *file,int size){
		
	    	int a[size];
	    	int i;
		
	    	for (i = 0; i <sizeof(a)/sizeof(a[0]) ; i++)
	    	{
	     	   fscanf(file, "%d", &a[i]);
	   	 }
		
		for (int l=0;l<sizeof(a)/sizeof(a[0]);l++){
		printf("%d\n",a[l]);
		}
	    	
	    	qsort(a,sizeof(a)/sizeof(a[0]),sizeof(int),cmpfunc);
		printf("\n");
	     	for (int l=0;l<sizeof(a)/sizeof(a[0]);l++){
		printf("%d\n",a[l]);
	}
  int findTheLinesNumber(FILE*file2){


		int count=0;	   	
		int num;
		while(fscanf(file2,"%d",&num)>0){
		count=count+1;
		}
		fclose(file2);
		return count;





}



int main(){
    char* args[10];
    char line[100];

    while(readParseLine(args,line)){

        pid_t childPid = fork();
        if(childPid == 0){      
          // run
        }
        else {
            waitpid(childPid, 0,0);
        }

    }
    return 0;
}


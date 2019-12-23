#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

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

void printHelp(){
    puts("***********List of Commands supported***************\n"
        "|\t#convert_to_binary arg1(type) arg2(number) |\n"
        "|\t#copy_to_desktop arg1(file name)\t   |\n"
        "|\t#Notepad\t\t\t\t   |\n"
        "|\t#C function-2\t\t\t\t   |\n"
        "|\t#exit\t\t\t\t\t   |");
    puts("****************************************************");
}

void welcomeScreen(){
    char* username = getenv("USER");
    printf("@%s\n", username);
    puts("*******************************************");
    puts("|                                         |");
    puts("|                                         |");
    puts("|        EY Shell is starting...          |");
    puts("|   Type help for supporting commands     |");
    puts("|                                         |");
    puts("|                                         |");
    puts("*******************************************");
}
int cmpfunc (const void * a, const void * b)
    {
    	// Compare function used by qsort
        //We should take that function for use qsort function
    	return ( *(int*)a - *(int*)b );
    }


 void sortTheFile(char b[]){
	 	FILE *myFile;
		file = fopen(b, "r");
		int count=0;	   	
		int num;
		while(fscanf(file,"%d",&num)>0){
		count=count+1;
		}
		fclose(file);
			
	    	int a[count];
	    	int i;
		
		file = fopen(b, "r");	
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
		fclose(file);

}

   

void createNotepad(char* inputName){
    if (inputName == NULL)
       printf("Must enter file name!!");
    
    
    else {
        char data[1000];
        char fileName[50];
        char *extension = ".txt";
        sprintf(fileName,"%s%s",inputName,extension);

        FILE * fPtr;

        fPtr = fopen(fileName, "w");


        if(fPtr == NULL){
            printf("Error\n");
            exit(EXIT_FAILURE);
        }

        printf("\n   :");
        fgets(data, 1000, stdin);

        fputs(data, fPtr);

        fclose(fPtr);

        printf("File created successfully. \n");
    }
}

int main(){

    welcomeScreen();
    char* args[10];
    char line[100];

    while(readParseLine(args,line)){

        char* functions [] = {"help","convert_to_binary","copy_to_desktop","Notepad","c_function_2","exit"};
        char* command = malloc(1000*sizeof(char));
        
        pid_t childPid = fork();
        if(childPid == 0){
            if(!strcmp(*args,functions[5])){
                puts("Terminating...");
                kill(childPid, SIGKILL);
            }
            else if (!strcmp(*args,functions[0])){
                printHelp();
            }
             else if (!strcmp(args[0],functions[1])){
                sprintf(command,"%s %s %s","sh ShellFunction1.sh",args[1],args[2]);
                system(command);
            }
            else if (!strcmp(args[0],functions[2])){
                sprintf(command,"%s %s","sh ShellFunction2.sh",args[1]);
                system(command);
            }
            else if (!strcmp(args[0],functions[3])){
                createNotepad(args[1]);
            }
            else if (!strcmp(args[0],functions[4])){
                puts("c function-2");
            }
              else
                printf("EY: command not found: %s\n",args[0]);
        }
        else {
            waitpid(childPid, 0,0);
        }


    }
    return 1;
}


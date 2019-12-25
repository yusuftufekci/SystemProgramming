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
    puts("\n***********List of Commands supported***************\n"
        "|  #convert_to_binary arg1(type) arg2(number)\t   |\n"
        "|  #compare_files arg1(file1 name) arg2(file2 name)|\n"
        "|  #copy_to_desktop arg1(file name)\t\t   |\n"
        "|  #notepad\t\t\t\t\t   |\n"
        "|  #sort_file arg1 (file name)\t\t\t   |\n"
        "|  #exit\t\t\t\t\t   |");
    puts("****************************************************\n");
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

int cmpfunc (const void * a, const void * b){
    return ( *(int*)a - *(int*)b );
}

void sortTheFile(char b[]){
    FILE *file;
    FILE *writeFile;
    printf("%s\n",b);
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
    writeFile = fopen("sortedFile.txt", "w"); 
    for (i = 0; i <sizeof(a)/sizeof(a[0]) ; i++){
        fscanf(file, "%d", &a[i]);
    }
        
    for (int l=0;l<sizeof(a)/sizeof(a[0]);l++){
        printf("%d\n",a[l]);
    }
            
    qsort(a,sizeof(a)/sizeof(a[0]),sizeof(int),cmpfunc);
    printf("\n");
    for (int l=0;l<sizeof(a)/sizeof(a[0]);l++){
        printf("%d\n",a[l]);
        fprintf(writeFile, "%d\n",a[l]);
    }
    fclose(file);
    fclose(writeFile);
}

void createNotepad(char* inputName){
    if (inputName == NULL) 
       printf("Must enter file name!!\n");
    
    
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

    	char* functions [] = {"help","convert_to_binary","compare_files","copy_to_desktop","notepad","sort_file","exit"};
        char* command = malloc(1000*sizeof(char));
        
        pid_t childPid = fork();
        if(childPid == 0){

	        if (!strcmp(*args,functions[0])){
                printHelp();
	        }
	 		else if (!strcmp(args[0],functions[1])){
                sprintf(command,"%s %s","sh ShellFunction1.sh",args[1]);
                system(command);
	        }
            else if (!strcmp(args[0],functions[2])){
                sprintf(command,"%s %s %s","sh ShellFunction2.sh",args[1],args[2]);
                system(command);
            }
           else if (!strcmp(args[0],functions[3])){
                sprintf(command,"%s %s","sh ShellFunction3.sh",args[1]);
                system(command);
            }
            else if (!strcmp(args[0],functions[4])){
                createNotepad(args[1]);
            }
            else if (!strcmp(args[0],functions[5])){
                sortTheFile(args[1]);
            }
            else if(!strcmp(*args,functions[6])){
                puts("Terminating...");
                kill(childPid, SIGKILL);
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


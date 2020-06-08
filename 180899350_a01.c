#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <ctype.h>
void writeOutput (char* command, char* output){
	printf("the outputof: %s : is \n", command);
	printf(">>>>>>>>>>>>>>>\n%s<<<<<<<<<<<<<<<\n",output);

}
int line_count(char *mem){
	int count =0;
	int i=0;
	while(mem[i] != '\0'){
		if(mem[i] =='\n'){
			count++;
					
		}
		i++;
	}

	return count+1;		
}


int main(int argc, char *argv[])
{
	int shm_fd = shm_open( "shm", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR); 
	ftruncate(shm_fd, 5000);
	char *mem = mmap(NULL, sizeof(char) * 80, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0); 
	char** array;
 	

	if(fork() == 0){ //is child		
		//printf("EXIST"); 
		FILE* fp = fopen(argv[1], "r");
		fread(mem, 1,sizeof(char) * 80, fp);	
		exit(0);
	}

	else { // is parent process
		wait(NULL);	
		//int size = line_count(mem); //size of lines
		
		//printf("%d",size); //print how many lines		
		array = malloc(sizeof(char*) * 1);
		char* token = strtok( (char*)mem, "\r\n");
		array[0] = token;
		int i = 1;

		while(token != NULL) {
			token = strtok(NULL, "\r\n");
			if(token !=NULL){
			array = realloc(array, sizeof(char *) * (i+1));
			array[i] = token;
			i++;
			
			} 
		}	
		array[i] = "\0"; 
	
 	
	for(int i=0; i<=7; i++) {
		puts(array[i]); 	
	
	
		
	}
}


	return 0;
} 







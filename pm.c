#include "stdio.h"
#include "string.h"
//#include "openssl/evp.h"

int main(int argc, char *argv[]){
    FILE *fptr;
    char key[32],buffer[2048];
    char* value;
    int i=0,j,check=0;
    if(!strcmp(argv[1],"add")){
        fptr = fopen(argv[3],"a+");
        printf("Enter password: ");
        scanf("%s",key);
        fprintf(fptr,"%s,%s\n",argv[4],argv[5]);
        fclose(fptr);
    } else if(!strcmp(argv[1],"read")){
        fptr = fopen(argv[3],"r");
        printf("Enter password: ");
        scanf("%s",key);
        while(fgets(buffer,1024,fptr)){
            j=0;
            value= strtok(buffer,",");
            while(value){
                if(j==0){
                    if(!strcmp(value,argv[4])) check=1;
                }
                if(j==1&&check){
                    printf("Key: %s has value: %s\n",argv[4],value);
                    check=0;
                }
                value = strtok(NULL,",");
                j++;
            }
        }
        fclose(fptr);
    } else if(!strcmp(argv[1],"range-read")){
        fptr = fopen(argv[3],"r");
        printf("Enter password: ");
        scanf("%s",key);

    } else {
        puts("Error: Command Not Found");
    }
    
    return 0;
}
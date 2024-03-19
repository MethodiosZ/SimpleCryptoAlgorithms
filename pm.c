#include "stdio.h"
#include "string.h"
#include "stdlib.h"
//#include "openssl/evp.h"

int main(int argc, char *argv[]){
    FILE *fptr;
    char passkey[32],buffer[2048];
    char* value;
    int i=0,j,check=0;
    if(!strcmp(argv[1],"add")){
        fptr = fopen(argv[3],"a+");
        printf("Enter password: ");
        scanf("%s",passkey);
        fprintf(fptr,"%s,%s\n",argv[4],argv[5]);
        fclose(fptr);
    } else if(!strcmp(argv[1],"read")){
        fptr = fopen(argv[3],"r");
        printf("Enter password: ");
        scanf("%s",passkey);
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
        scanf("%s",passkey);
        int intvalue,key;
        int low = atoi(argv[4]);
        int high = atoi(argv[5]);
        if(low<=high){
            while(fgets(buffer,1024,fptr)){
                j=0;
                value= strtok(buffer,",");
                intvalue = atoi(value);
                while(value){
                    if(j==0){
                        if(intvalue>=low && intvalue <= high){
                            check=1;
                            key=intvalue;
                        }
                    }
                    if(j==1&&check){
                        printf("Key: %d has value: %s\n",key,value);
                        check=0;
                    }
                    value = strtok(NULL,",");
                    j++;
                }
            }
        }
        else{
            printf("Incorrect keys!\n");
        }
        fclose(fptr);
    } else {
        puts("Error: Command Not Found");
    }
    
    return 0;
}
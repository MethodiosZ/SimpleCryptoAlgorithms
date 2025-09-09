#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "openssl/evp.h"
#include "openssl/rand.h"
#include "openssl/sha.h"

/*void get_key_IV(char *master,char *key,char *IV){
  char salt[16];
  RAND_bytes(salt,16);
  PKCS5_PBKDF2_HMAC(master,strlen(master),salt,16,1000,EVP_sha256(),64,key);
  memcpy(IV, key +32,32);
  }*/

int main(int argc, char *argv[]){
    FILE *fptr;
    char passkey[32],buffer[2048],key[32],IV[32],encryptkey[32],encryptvalue[32];
    char* value;
    int i=0,j,check=0,len;
    /*OpenSSL_add_all_algorithms();
    const EVP_CIPHER *cipher = EVP_aes_128_cbc();
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();*/
    if(!strcmp(argv[1],"add")){
        fptr = fopen(argv[3],"a+");
        printf("Enter password: ");
        scanf("%s",passkey);
	/*get_key_IV(passkey,key,IV);
	EVP_EncryptInit_ex(ctx,cipher,NULL,key,IV);
	EVP_EncryptUpdate(ctx,encryptkey,&len,argv[4],strlen(argv[4]));
	EVP_EncryptFinal_ex(ctx,encryptkey+len,&len);
	EVP_EncryptInit_ex(ctx,cipher,NULL,key,IV);
	EVP_EncryptUpdate(ctx,encryptkey,&len,argv[5],strlen(argv[5]));
	EVP_EncryptFinal_ex(ctx,encryptkey+len,&len);*/
        fprintf(fptr,"%s,%s\n",argv[4],argv[5]);
        fclose(fptr);
	//EVP_CIPHER_CTX_free(ctx);
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

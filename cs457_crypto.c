#include <stdio.h>
#include <stdlib.h>
#include "cs457_crypto.h"

char* one_time_pad_encr(char* data,int length,char* key){
    char* ciphertext;
    int i;
    for(i=0;i<length;i++){
        ciphertext[i] = (char) (data[i] ^ key[i]);
    }
    return ciphertext;
}

char* one_time_pad_decr(char* data,int length,char* key){
    char* plaintext;
    int i;
    for(i=0;i<length;i++){
        plaintext[i] = (char) (data[i] ^ key[i]);
    }
    return plaintext;
}

char* affine_encr(char* plaintext){

}

char* affine_decr(char* ciphertext){

}

char* decryptor(char* ciphertext){

}

char* trithemius_encr(char* plaintext){

}

char* trithemius_decr(char* ciphertext){

}

char* scytale_encr(char* plaintext,int diameter){

}

char* scytale_decr(char* ciphertext,int diameter){

}

char* rail_fence_encr(char* plaintext,int rails){

}

char* rail_fence_decr(char* ciphertext,int rails){

}

int main(){
    char plaintext[256],key[256];
    char* ciphertext;
    int i=0,length=0;
    puts("Please enter the text you want to encrypt!");
    fgets(plaintext,sizeof(plaintext),stdin);
    while(plaintext[i]!='\n'){
        length++;
        //use of /dev/urandom instead of rand
        key[i]=(char)(rand()%26+97); 
        i++;
    }
    printf("%d\n",i);
    return 0;
}
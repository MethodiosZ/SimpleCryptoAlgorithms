#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cs457_crypto.h"

static const char Letters[] = {'A','B','C','D','E','F','G','H','I','J','K', 
'L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
};

static const char letters[] = { 'a','b','c','d','e','f','g','h','i','j',
'k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
};

int absol(int num){
    if(num<0){
        return 26+num;
    }
    return num;
}

char* one_time_pad_encr(char* data,int length,char* key){
    char* ciphertext = (char*)malloc(length*sizeof(char));
    int count;
    for(count=0;count<length;count++){
        ciphertext[count] = data[count] ^ key[count]; 
    }
    return ciphertext;
}

char* one_time_pad_decr(char* data,int length,char* key){
    char* plaintext = (char*)malloc(length*sizeof(char));
    int count;
    for(count=0;count<length;count++){
        plaintext[count] = data[count] ^ key[count];
    }
    plaintext[length]='\0';
    return plaintext;
}

char* affine_encr(char* plaintext){
    char* ciphertext;
    int xx=0,count=0;
    while(plaintext[count]!='\n'){
        count++;
    }
    ciphertext = (char*)malloc(count*sizeof(char));
    count=0;
    while (plaintext[count]!='\n'){
        if((plaintext[count]>='A')&&(plaintext[count]<='Z')){
            xx = plaintext[count] - 'A';
            ciphertext[count]=Letters[(5*xx+8)%26];
        }
        else if((plaintext[count]>='a')&&(plaintext[count]<='z')){
            xx = plaintext[count] - 'a';
            ciphertext[count]=letters[(5*xx+8)%26];
        }
        else{
            ciphertext[count]=' ';
        }
        count++;
    }
    ciphertext[count]='\0';
    return ciphertext;
}

char* affine_decr(char* ciphertext){
    char* plaintext;
    int count=0,yy=0;
    while(ciphertext[count]!='\0'){
        count++;
    }
    plaintext = (char*)malloc(count*sizeof(char));
    count=0;
    while(ciphertext[count]!='\0'){
        if((ciphertext[count]>='A')&&(ciphertext[count]<='Z')){
            yy = ciphertext[count] - 'A';
            plaintext[count]=Letters[absol(21*(yy-8)%26)];
        }
        else if((ciphertext[count]>='a')&&(ciphertext[count]<='z')){
            yy = ciphertext[count] - 'a';
            plaintext[count]=letters[absol(21*(yy-8)%26)];
        }
        else{
            plaintext[count]=' ';
        }
        count++;
    }
    plaintext[count]='\0';
    return plaintext;
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
    char* ciphertext,*decipheredtext;
    int count=0,diameter,rails;
    puts("Please enter the text you want to encrypt!");
    fgets(plaintext,sizeof(plaintext),stdin);
    /*Start of One Time Pad
    while(plaintext[count]!='\n'){
        //use of /dev/urandom instead of rand
        key[count]=rand()%(126-32+1)+32; 
        count++;
    }
    ciphertext=one_time_pad_encr(plaintext,count,key);
    printf("Ciphertext for One Time Pad is: %s\n",ciphertext);
    decipheredtext=one_time_pad_decr(ciphertext,count,key);
    printf("Plaintext for One Time Pad is: %s\n",decipheredtext);
    End of One Time Pad*/

    //Start of Affine Cipher
    ciphertext=affine_encr(plaintext);
    printf("Ciphertext for Affine Cipher is: %s\n",ciphertext);
    decipheredtext=affine_decr(ciphertext);
    printf("Plaintext for Affine Cipher is: %s\n",decipheredtext);
    //End of Affine Cipher

    /*Start of Decryptor
    decipheredtext=decryptor(ciphertext);
    printf("Plaintext for Decryptor is: %s\n",decipheredtext);
    //End of Decryptor

    //Start of Trithemius Cipher
    ciphertext=trithemius_encr(plaintext);
    printf("Ciphertext for Trithemiys Cipher is: %s\n",ciphertext);
    decipheredtext=trithemius_decr(ciphertext);
    printf("Plaintext for Trithemius Cipher is: %s\n",decipheredtext);
    //End of Trithemius Cipher

    //Start of Scytale Cipher
    ciphertext=scytale_encr(plaintext,diameter);
    printf("Ciphertext for Scytale Cipher is: %s\n",ciphertext);
    decipheredtext=scytale_decr(ciphertext,diameter);
    printf("Plaintext for Scytale Cipher is: %s\n",decipheredtext);
    //End of Scytale Cipher

    //Start of Rail Fence Cipher
    ciphertext=rail_fence_encr(plaintext,rails);
    printf("Ciphertext for Rail Fence Cipher is: %s\n",ciphertext);
    decipheredtext=rail_fence_decr(ciphertext,rails);
    printf("Plaintext for Rail Fence Cipher is: %s\n",decipheredtext);
    //End of Rail Fence Cipher*/
    return 0;
}
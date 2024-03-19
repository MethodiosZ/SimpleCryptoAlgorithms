#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cs457_crypto.h"

#define HASH_SIZE 256

static const char Letters[] = {'A','B','C','D','E','F','G','H','I','J','K', 
'L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
};

static const char letters[] = { 'a','b','c','d','e','f','g','h','i','j',
'k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
};

char hashtable[HASH_SIZE];

char tabula_recta_upper[26][26];

char tabula_recta_lower[26][26];

void init_hashtable(){
    int count;
    for(count=0;count<HASH_SIZE;count++){
        hashtable[count]='0';
    }
}

void init_tabula_recta_upper(){
    int row,col,index;
    char base;
    for (row = 0; row < 26; row++) {
        for (col = 0; col < 26; col++) {
            base = 'A';
            index = (row + col) % 26;
            tabula_recta_upper[row][col] = base + index;
        }
    }
}

void init_tabula_recta_lower(){
    int row,col,index;
    char base;
    for (row = 0; row < 26; row++) {
        for (col = 0; col < 26; col++) {
            base = 'a';
            index = (row + col) % 26;
            tabula_recta_lower[row][col] = base + index;
        }
    }
}

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
    char cipher,plain,word[30];
    puts("Please enter the cipher letter and the letter you want to exchange!");
    //scanf("%c %c",&cipher,&plain);
    puts("Enter a semi decrypted word!");
    fgets(word,sizeof(word),stdin);
    printf("%s\n",word);
}

char* trithemius_encr(char* plaintext){
    char* ciphertext;
    int count=0,col=0;
    while(plaintext[count]!='\n'){
        count++;
    }
    ciphertext = (char*)malloc(count*sizeof(char));
    count=0;
    while(plaintext[count]!='\n'){
        if((plaintext[count]>='A')&&(plaintext[count]<='Z')){
            col = plaintext[count] - 'A';
            ciphertext[count]=tabula_recta_upper[count][col];
        }
        else if((plaintext[count]>='a')&&(plaintext[count]<='z')){
            col = plaintext[count] - 'a';
            ciphertext[count]=tabula_recta_lower[count][col];
        }
        else{
            ciphertext[count]=plaintext[count];
        }
        count++;
    }
    ciphertext[count]='\0';
    return ciphertext;
}

char* trithemius_decr(char* ciphertext){
    char* plaintext;
    int count=0,col=0;
    while(ciphertext[count]!='\0'){
        count++;
    }
    plaintext = (char*)malloc(count*sizeof(char));
    count=0;
    while(ciphertext[count]!='\0'){
        if((ciphertext[count]>='A')&&(ciphertext[count]<='Z')){
            col = ciphertext[count] - 'A';
            plaintext[count]=tabula_recta_upper[count-count*1][col-count];
        }
        else if((ciphertext[count]>='a')&&(ciphertext[count]<='z')){
            col = ciphertext[count] - 'a';
            plaintext[count]=tabula_recta_lower[count-count*1][absol(col-count)];
        }
        else{
            plaintext[count]=ciphertext[count];
        }
        count++;
    }
    plaintext[count]='\0';
    return plaintext;
}

char* scytale_encr(char* plaintext,int diameter){
    char* ciphertext,*truetext;
    int count=0,row=0,col=0,length=0,temp=0;
    init_hashtable();
    while(plaintext[count]!='\n'){
        if((plaintext[count]>='A'&&plaintext[count]<='Z')||(plaintext[count]>='a')&&(plaintext[count]<='z')){
            length++;
        }
        count++;
    }
    ciphertext = (char*)malloc(length*sizeof(char));
    truetext = (char*)malloc(length*sizeof(char));
    char papyrus[length/diameter][diameter];
    count=0;
    temp=0;
    while(plaintext[count]!='\n'){
        if((plaintext[count]>='A'&&plaintext[count]<='Z')||(plaintext[count]>='a')&&(plaintext[count]<='z')){
            truetext[temp]=plaintext[count];
            temp++;
        }
        else{
            hashtable[count]=plaintext[count];
        }
        count++;
    }
    truetext[length]='\0';
    count=0;
    while(truetext[count]!='\0'){
        papyrus[row][col]=truetext[count];
        if(col==diameter-1){
            row++;
            col=-1;
        }
        col++;
        count++;
    }
    count=0;
    for(col=0;col<diameter;col++){
        for(row=0;row<(length/diameter);row++){
            ciphertext[count]=papyrus[row][col];
            count++;
        }
    }
    ciphertext[count]='\0';
    return ciphertext;
}

char* scytale_decr(char* ciphertext,int diameter){
    char* plaintext;
    int count=0,col=0,row=0,length,extrachars=0;
    while(ciphertext[count]!='\0'){
        count++;
    }
    for(length=0;length<HASH_SIZE;length++){
        if(hashtable[length]!='0') {
            extrachars++;
        }
    }
    plaintext = (char*)malloc((count+extrachars)*sizeof(char));
    char papyrus[count/diameter][diameter];
    length=count;
    for(count=0;count<length;count++){
        papyrus[row][col]=ciphertext[count];
        if(row==(length/diameter)-1){
            col++;
            row=-1;
        }
        row++;
    }
    count=0;
    for(row=0;row<(length/diameter);row++){
        for(col=0;col<diameter;col++){   
            if(hashtable[count]!='0'){
                plaintext[count]=hashtable[count];
                plaintext[++count]=papyrus[row][col];
            }
            else{
                plaintext[count]=papyrus[row][col];
            }
            count++;
        }
    }
    if(hashtable[count]!='0') {
        plaintext[count]=hashtable[count];
        count++;
    }
    plaintext[count]='\0';
    return plaintext;
}

char* rail_fence_encr(char* plaintext,int rails){
    char* ciphertext, *truetext;
    int count=0,length=0,temp=0,col=0,row=0,bottom=0;
    init_hashtable();
    while(plaintext[count]!='\n'){
        if((plaintext[count]>='A'&&plaintext[count]<='Z')||(plaintext[count]>='a')&&(plaintext[count]<='z')){
            length++;
        }
        count++;
    }
    ciphertext = (char*)malloc((length+rails)*sizeof(char));
    truetext = (char*)malloc(length*sizeof(char));
    char rail_fence[rails][length];
    for(row=0;row<rails;row++){
        for(col=0;col<length;col++){
            rail_fence[row][col]='0';
        }
    }
    count=0;
    while(plaintext[count]!='\n'){
        if((plaintext[count]>='A'&&plaintext[count]<='Z')||(plaintext[count]>='a')&&(plaintext[count]<='z')){
            truetext[temp]=plaintext[count];
            temp++;
        }
        else{
            hashtable[count]=plaintext[count];
        }
        count++;
    }
    truetext[length]='\0';
    count=0;
    temp=0;
    while(truetext[count]!='\0'){
        rail_fence[temp][count]=truetext[count];
        count++;
        if(temp==rails-1) bottom=1;
        else if(!temp) bottom=0;
        if(!bottom) temp++;
        else temp--;
    }
    count=0;
    for(row=0;row<rails;row++){
        for(col=0;col<length;col++){
            if(rail_fence[row][col]!='0'){
                ciphertext[count]=rail_fence[row][col];
                count++;
            }
        }
        ciphertext[count]=' ';
        count++;
    }
    ciphertext[length+rails]='\0';
    return ciphertext;
}

char* rail_fence_decr(char* ciphertext){
    char* plaintext,*truetext;
    int count=0,rails=0,length=0,col,row,temp,bottom=0,extrachars=0;
    while(ciphertext[count]!='\0'){
        if(ciphertext[count]==' ') rails++;
        count++;
    }
    for(length=0;length<HASH_SIZE;length++){
        if(hashtable[length]!='0') {
            printf("%c at %d\n",hashtable[length],length);
            extrachars++;
        }
    }
    length=count-rails;
    plaintext=(char*)malloc((length+extrachars)*sizeof(char));
    truetext=(char*)malloc((length)*sizeof(char));
    char rail_fence[rails][length];
    for(row=0;row<rails;row++){
        for(col=0;col<length;col++){
            rail_fence[row][col]='0';
        }
    }
    count=0;
    temp=0;
    while(ciphertext[count]!='\0'){
        if(ciphertext[count]!=' '){
            truetext[temp]=ciphertext[count];
            temp++;
        }
        count++;
    }
    truetext[temp]='\0';
    temp=0;
    for(count=0;count<length;count++){
        rail_fence[temp][count]='1';
        if(temp==rails-1) bottom=1;
        else if(!temp) bottom=0;
        if(!bottom) temp++;
        else temp--;
    }
    count=0;
    for(row=0;row<rails;row++){
        for(col=0;col<length;col++){
            if(rail_fence[row][col]=='1') rail_fence[row][col]=truetext[count++];
        }
    }
    temp=0;
    bottom=0;
    for(count=0;count<length;count++){
        truetext[count]=rail_fence[temp][count];
        if(temp==rails-1) bottom=1;
        else if(!temp) bottom=0;
        if(!bottom) temp++;
        else temp--;
    }
    truetext[count]='\0';
    count=0;
    temp=0;
    while(truetext[temp]!='\0'){
        if(hashtable[count]!='0'){
            plaintext[count]=hashtable[count];
            plaintext[++count] = truetext[temp];
        }
        else{
            plaintext[count]=truetext[temp];
        }
        count++;
        temp++;
    }
    if(hashtable[count]!='0') {
        plaintext[count]=hashtable[count];
        count++;
    }
    plaintext[count]='\0';
    return plaintext;
}

int main(){
    char plaintext[256],key[256];
    char* ciphertext,*decipheredtext;
    int count=0,diameter,rails;
    puts("Please enter the text you want to encrypt!");
    fgets(plaintext,sizeof(plaintext),stdin);
    /*//Start of One Time Pad
    while(plaintext[count]!='\n'){
        //use of /dev/urandom instead of rand
        key[count]=rand()%(126-32+1)+32; 
        count++;
    }
    ciphertext=one_time_pad_encr(plaintext,count,key);
    printf("Ciphertext for One Time Pad is: %s\n",ciphertext);
    decipheredtext=one_time_pad_decr(ciphertext,count,key);
    printf("Plaintext for One Time Pad is: %s\n",decipheredtext);
    //End of One Time Pad

    //Start of Affine Cipher
    ciphertext=affine_encr(plaintext);
    printf("Ciphertext for Affine Cipher is: %s\n",ciphertext);
    decipheredtext=affine_decr(ciphertext);
    printf("Plaintext for Affine Cipher is: %s\n",decipheredtext);
    //End of Affine Cipher*/

    /*//Start of Decryptor
    decipheredtext=decryptor(ciphertext);
    printf("Plaintext for Decryptor is: %s\n",decipheredtext);
    //End of Decryptor

    //Start of Trithemius Cipher
    init_tabula_recta_upper();
    init_tabula_recta_lower();
    ciphertext=trithemius_encr(plaintext);
    printf("Ciphertext for Trithemiys Cipher is: %s\n",ciphertext);
    decipheredtext=trithemius_decr(ciphertext);
    printf("Plaintext for Trithemius Cipher is: %s\n",decipheredtext);
    //End of Trithemius Cipher

    //Start of Scytale Cipher
    puts("Please enter the cylinder diameter!");
    scanf("%d",&diameter);
    ciphertext=scytale_encr(plaintext,diameter);
    printf("Ciphertext for Scytale Cipher is: %s\n",ciphertext);
    decipheredtext=scytale_decr(ciphertext,diameter);
    printf("Plaintext for Scytale Cipher is: %s\n",decipheredtext);
    //End of Scytale Cipher*/

    //Start of Rail Fence Cipher
    puts("Please enter the number of rails!");
    scanf("%d",&rails);
    ciphertext=rail_fence_encr(plaintext,rails);
    printf("Ciphertext for Rail Fence Cipher is: %s\n",ciphertext);
    decipheredtext=rail_fence_decr(ciphertext);
    printf("Plaintext for Rail Fence Cipher is: %s\n",decipheredtext);
    //End of Rail Fence Cipher
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// ###### Menuja #######

void menuja();

// ###### Fundi menuja #######


// ####### Administator funksionet ########

void adminMenu(); //vendi ku do mbahen te gjitha funx. e meposhtme
void shtoPerdorues();
void shfaqPerdoruesit();
void kerkoSipasId(int id_user);
void fshiPerdorues(int id_user);
void updatePerdorues(int id_user);
void kerkoSipasUsername(char username[]);
void rradhitSipasUsername();
void adminMenuKategori(); //crud per kategorine
void statistika(); // si tip menuje ku mund te shohesh nr users, total shpenzimesh, mesatare shpenzimesh, kategoria max, etc

// ####### Fund administator funksionet ########


// ######## Perdorues funksionet ##########

void userMenu(); //vendi ku mbahen te gjitha funx. e meposhthme
void shtoShpenzim();
void shtoTeArdhura();
void shfaqShpenzime(int id_user);
void shfaqTeArdhura(int id_user);
void raportMujor(int id_user);
void raportVjetor(int id_user);
void kontrolloBuxhetin(int id_user);
void kerkoShpenzimSipasKategorise(int id_user, int id_kategori);
void fshiShpenzim(int id_shpenzim);
void renditShpenzimeSipasShumes(int id_user);
void renditShpenzimeSipasDates(int id_user);
void kerkoShpenzimSipasId(int id_shpenzim);
void kerkoShpenzimSipasDate(int id_user, char data[]);
void kerkoShpenzimeIntervalDate(int id_user, char data1[], char data2[]);

// ######## Fundi perdorues funksionet ##########


// ######## Validime funksione #########

int eshtIdValid(int id_user);
int eshtUsernameUnik(const char username[]);
int eshtPasswordValid(const char password[]);


// ######## fundi validime funksione


// ######### Strukturat ############

struct Perdorues{
    int id_user;
    char emri[30];
    char username[20];
    char password[50];
    float buxheti_mujor;
};

struct Kategoria{
    int id_kategoria;
    char emertimi[50];
    char pershkrimi[100];
};

struct Shpenzim{
    int id_shpenzim;
    int id_user;
    char pershkrim[50];
    struct Kategoria kategori;
    float shuma;
    char data[20];
};

// ######### Fundi i strukturave ############


int main(){
    menuja();
}









/* #######  Handler funksionet ########### */
int eshtUsernameUnik(const char username[]){
    FILE *fptr=fopen("user.txt","r");
    int id_user;
    char emri[30];
    char Fileusername[20]; //username qe merret nga file
    char password[50];
    float buxheti_mujor;

    if(fptr==NULL){
        return 1; //po, meqe file bosh
    }
    while(fscanf(fptr,"%d %s %s %s %f",&id_user,emri,Fileusername,password,&buxheti_mujor)!=EOF){
        if(strcmp(username,Fileusername)==0){
            fclose(fptr);
            return 0; //un jo unik
        }
    }
    fclose(fptr);
    return 1; //po meqe ploteson kushtin

}

int eshtPasswordValid(const char password[]){
    int i;
    int kaNumber=0;
    int kaSimbol=0;

    // respektimi i karaktereve
    if(strlen(password)<4){
        return 0;
    }
    // respektimi i shkronjes se madhe
    if(!isupper(password[0])){
        return 0;
    }

    for(i=0;password[i]!='\0';i++){
        if(isdigit(password[i])){
            kaNumber=1;
        }
        if(isalnum(password[i])){
            kaSimbol=1;
        }
    }

    if(kaNumber&&kaSimbol){
        return 1; //valid
    }
    return 0; //invalid
}

int eshtIdValid(int id_user){
    FILE *fptr=fopen("user.txt","r");

    int fileId; //Id qe merret nga file
    char emri[30];
    char username[20]; 
    char password[50];
    float buxheti_mujor;

    if(fptr==NULL){
        return 1; // id unike sepse file bosh
    }
    while(fscanf(fptr,"%d %s %s %f",&fileId,emri,password,&buxheti_mujor)!=EOF){
        if(fileId==id_user){
            return 0; //id jo unike
        }
    }
    return 1; // id unike sepse nuk u plotesua kushti ndalues (testimi i jo unicitetit)

}

// ######## Fundi Funx. Handler ########


void menuja(){
    int choice;
    

    do{
        printf("\n####### Mire se vini #######\n");
        printf("1. Administrator\n");
        printf("2. Perdorues\n");
        printf("3. Dil\n");
        printf("Zgjidhni: ");
        scanf("%d",&choice);

        switch(choice){
            case 1:
            adminMenu();
            return;
            case 2:
            userMenu();
            return;
            case 3:
            return;
            default:
            printf("Invalid! Zgjidh perseri!");
            break;
        }
    }while(choice!=3);
}

void userMenu(){
    
}

void adminMenu(){
   

}


//TODO:  handle qe nqs user/admin i paloguar, duhet te beje login qe te aksesoje menu-ne
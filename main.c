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
int eshtUsernameUnik(char username[]);
int eshtPasswordValid(char password[]);


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
    int id_kategori;
    float shuma;
    char data[20];
};

// ######### Fundi i strukturave ############


int main(){

}
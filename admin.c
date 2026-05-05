#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "admin.h"
#include "menu.h"
#include "structs.h"


void adminMenu()
{
    printf("\n\n");
    printf("------------------- Mire se erdhet Admin!  -----------------------------\n");
    int choice;
    int id_user;
    char username[20];
    do{
       printf("1.Shtoni perdorues\n");
       printf("2.Shfaq perdoruesit\n");
       printf("3.Kerko perdorues sipas Id\n");
       printf("4.Fshini kredincialet e nje perdoruesi\n");
       printf("5.Ndryshoni te dhenat e nje perdoruesi ekzistues\n");
       printf("6.Printoni te gjithe te dhenat perdoruesve\n");
       printf("7.Kerko sipas username\n");
       printf("8.Rradhisni te gjithe perdoruesit sipas username (A-Z)\n");
       printf("9.Shto/Ndrysho/Fshi kategori\n");
       printf("10.Statistika te sistemit (Nr perdoruesish,numri total i shpenzimeve,perdoruesi me me shume/pak shpenzime)\n");
       printf("11.Dilni nga menuja e Administratorit\n");
       printf("Vendosni zgjedhjen tuaj:");
       scanf("%d",&choice);

       switch(choice){
        case 1:
        shtoPerdorues();
        break;
        case 2:
        shfaqPerdoruesit();
        break;
        case 3:
        
        printf("Vendosni id qe doni te kerkoni:");
        scanf("%d",&id_user);
        kerkoSipasId(id_user);
        break;
        case 4:
        printf("Vendosni id qe doni te fshihni:");
        scanf("%d",&id_user);
        fshiPerdorues(id_user);
        break;
        case 5:
        printf("Vendosni id qe doni te update:");
        scanf("%d",&id_user);
        updatePerdorues(id_user);
        break;
        case 6:
        shfaqTeTerePerdoruesit();
        break;
        case 7:
        printf("Vendosni username qe doni te kerkoni:");
        scanf("%s",username);
        kerkoSipasUsername(username);
        break;
        case 8:
        rradhitSipasUsername();
        break;
        case 9:
        adminMenuKategori();
        break;
        case 10:
        statistika();
        break;
        case 11:
        menuja();
        break;

        default:
        printf("Zgjedhje e pavlefshme!");
       }
    }while(choice!=11);
}



void shtoPerdorues(){
    printf("Akoma");
}
void shfaqPerdoruesit(){
    FILE *fptr=fopen("user.txt","r");

    if(fptr==NULL){
        printf("Skedari bosh");
    }
    struct Perdorues p;
    printf("\n%-5s %-15s %-15s %-15s %-10s\n",
           "ID", "Emri", "Username", "Password", "Buxheti");
    printf("---------------------------------------------------------------------\n");

    while(fscanf(fptr,"%d %s %s %s %f",&p.id_user,p.emri,p.username,p.password,&p.buxheti_mujor)!=EOF){
        printf("%-5d %-15s %-15s %-15s %-10.2f\n",
               p.id_user,
               p.emri,
               p.username,
               p.password,
               p.buxheti_mujor);
    }
    fclose(fptr);
}

void shfaqTeTerePerdoruesit(){
    printf("Akoma"); //kjo shfaq cdo gje?!
}
void kerkoSipasId(int id_user){
    printf("Akoma");
}
void fshiPerdorues(int id_user){
    printf("Akoma");
}
void updatePerdorues(int id_user){
    printf("Akoma");
}
void kerkoSipasUsername(char username[]){
    printf("Akoma");
}
void rradhitSipasUsername(){
    printf("Akoma");
}
void adminMenuKategori(){
    printf("Akoma");
} // crud per kategorine
void statistika(){
    printf("Akoma");
}


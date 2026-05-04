#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "user.h"
#include "menu.h"







void userMenu(int id_user, char username[])
{
    printf("\n\n");
    printf("------------------- Mire se erdhet perdorues:%s me ID:%d  -----------------------------\n", username, id_user);
    int choice;
    do
    {
        printf("1.Shto nje shpenzim te ri\n");
        printf("2.Shto nje te ardhur te re\n");
        printf("3.Shfaq shpenzimet e mia\n");
        printf("4.Shfaq te ardhurat e mia\n");
        printf("5.Raport Mujor\n");
        printf("6.Raport Vjetor\n");
        printf("7.Kontrollo Buxhetin\n");
        printf("8.Kerko shpenzim sipas kategorise\n");
        printf("9.Fshini te dhenat e nje shpenzimi\n");
        printf("10.Rendit shpenzimet sipas shumes\n");
        printf("11.Rendit shpenzimet sipas dates\n");
        printf("12.Kerko shpenzim sipas ID\n");
        printf("13.Kerko shpenzim sipas dates\n");
        printf("14.Kerko shpenzim sipas nje intervali datash\n");
        printf("15.Dil\n");

        printf("Beni zgjedhjen tuaj:");
        scanf("%d", &choice);
        printf("\n\n");

        switch (choice)
        {
        case 1:
            shtoShpenzim(id_user);
            break;

        case 2:
            shtoTeArdhura(id_user);
            break;

        case 3:
            shfaqShpenzime(id_user);
            break;

        case 4:
            shfaqTeArdhura(id_user);
            break;

        case 5:
            raportMujor(id_user);
            break;

        case 6:
            raportVjetor(id_user);
            break;

        case 7:
            kontrolloBuxhetin(id_user);
            break;

        case 8:
        {
            int id_kategori;
            printf("Vendos ID e kategorise: ");
            scanf("%d", &id_kategori);
            kerkoShpenzimSipasKategorise(id_user, id_kategori);
            break;
        }

        case 9:
        {
            int id_shpenzim;
            printf("Vendos ID e shpenzimit per fshirje: ");
            scanf("%d", &id_shpenzim);
            fshiShpenzim(id_shpenzim);
            break;
        }

        case 10:
            renditShpenzimeSipasShumes(id_user);
            break;

        case 11:
            renditShpenzimeSipasDates(id_user);
            break;

        case 12:
        {
            int id_shpenzim;
            printf("Vendos ID e shpenzimit: ");
            scanf("%d", &id_shpenzim);
            kerkoShpenzimSipasId(id_shpenzim);
            break;
        }

        case 13:
        {
            char data[20];
            printf("Vendos daten (p.sh. 2026-05-03): ");
            scanf("%s", data);
            kerkoShpenzimSipasDate(id_user, data);
            break;
        }

        case 14:
        {
            char data1[20], data2[20];
            printf("Vendos daten e pare: ");
            scanf("%s", data1);
            printf("Vendos daten e dyte: ");
            scanf("%s", data2);
            kerkoShpenzimeIntervalDate(id_user, data1, data2);
            break;
        }

        case 15:
            menuja();
            break;

        default:
            printf("Zgjedhje e pavlefshme!\n");
        }

    } while (choice != 15);
}










void shtoShpenzim(int id_user) {
    printf("shtoShpenzim not implemented yet\n\n");
}

void shtoTeArdhura(int id_user) {
    printf("shtoTeArdhura not implemented yet\n\n");
}

void shfaqShpenzime(int id_user) {
    printf("shfaqShpenzime not implemented yet\n\n");
}

void shfaqTeArdhura(int id_user) {
    printf("shfaqTeArdhura not implemented yet\n\n");
}

void raportMujor(int id_user) {
    printf("raportMujor not implemented yet\n\n");
}

void raportVjetor(int id_user) {
    printf("raportVjetor not implemented yet\n\n");
}

void kontrolloBuxhetin(int id_user) {
    printf("kontrolloBuxhetin not implemented yet\n\n");
}

void kerkoShpenzimSipasKategorise(int id_user, int id_kategori) {
    printf("kerkoShpenzimSipasKategorise not implemented yet\n\n");
}

void fshiShpenzim(int id_shpenzim) {
    printf("fshiShpenzim not implemented yet\n\n");
}

void renditShpenzimeSipasShumes(int id_user) {
    printf("renditShpenzimeSipasShumes not implemented yet\n\n");
}

void renditShpenzimeSipasDates(int id_user) {
    printf("renditShpenzimeSipasDates not implemented yet\n\n");
}

void kerkoShpenzimSipasId(int id_shpenzim) {
    printf("kerkoShpenzimSipasId not implemented yet\n\n");
}

void kerkoShpenzimSipasDate(int id_user, char data[]) {
    printf("kerkoShpenzimSipasDate not implemented yet\n\n");
}

void kerkoShpenzimeIntervalDate(int id_user, char data1[], char data2[]) {
    printf("kerkoShpenzimeIntervalDate not implemented yet\n\n");
}
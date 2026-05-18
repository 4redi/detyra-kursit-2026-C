#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "user.h"
#include "menu.h"
#include "structs.h"
#include "utils.h"

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
            kerkoShpenzimSipasKategorise(id_user);
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
            printf("Vendos daten (p.sh. dd-mm-yyyy): ");
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

void shtoShpenzim(int id_user)
{
    int dita, muaji, viti;

    float te_ardhura = totalTeArdhura(id_user);
    float shpenzime = totalShpenzime(id_user);

    struct Shpenzim s;
    struct Kategoria k;
    int zgjedhje;

    s.id_shpenzim = gjeneroIdShpenzim();
    s.id_user = id_user;

    printf("Pershkrimi: ");
    scanf(" %[^\n]", s.pershkrim);

    FILE *fk = fopen("kategori.txt", "r");
    if (fk == NULL)
    {
        printf("Gabim ne hapjen e kategori.txt!\n");
        return;
    }

    printf("\nKategorite:\n");
    while (fscanf(fk, "%d %s %s",
                  &k.id_kategoria,
                  k.emertimi,
                  k.pershkrimi) == 3)
    {
        printf("%d - %s\n", k.id_kategoria, k.emertimi);
    }

    printf("Zgjidh ID e kategorise: ");
    scanf("%d", &zgjedhje);

    rewind(fk);

    int cat_found = 0;
    while (fscanf(fk, "%d %s %s",
                  &k.id_kategoria,
                  k.emertimi,
                  k.pershkrimi) == 3)
    {
        if (k.id_kategoria == zgjedhje)
        {
            s.kategori = k;
            cat_found = 1;
            break;
        }
    }

    fclose(fk);

    if (!cat_found)
    {
        printf("Kategoria nuk u gjet!\n");
        return;
    }

    printf("Shuma: ");
    scanf("%f", &s.shuma);

    if(s.shuma<=0){
        printf("Shuma duhet me e madhe se 0!\n\n");
        return;
    }

    // Kontroll
    if (shpenzime + s.shuma > te_ardhura)
    {
        printf("\n Nuk lejohet shpenzimi!\n");
        printf("Te ardhura: %.2f\n", te_ardhura);
        printf("Shpenzime aktuale: %.2f\n", shpenzime);
        printf("Kjo shume kalon buxhetin!\n\n");
        return;
    }

    lexoDaten(&dita, &muaji, &viti);
    sprintf(s.data, "%02d-%02d-%04d", dita, muaji, viti);

    FILE *f = fopen("shpenzime.txt", "a");
    if (f == NULL)
    {
        printf("Gabim ne hapjen e shpenzime.txt!\n");
        return;
    }

    fprintf(f, "%d %d %s %d %s %s %.2f %s\n",
            s.id_shpenzim,
            s.id_user,
            s.pershkrim,
            s.kategori.id_kategoria,
            s.kategori.emertimi,
            s.kategori.pershkrimi,
            s.shuma,
            s.data);

    fclose(f);

    printf("Shpenzimi u shtua me sukses!\n\n");
}
void shtoTeArdhura(int id_user)
{
    struct Te_Ardhura t;
    int dita, muaji, viti;

    FILE *fptr = fopen("teArdhura.txt", "a");
    if (fptr == NULL)
    {
        printf("Gabim gjate hapjes");
        return;
    }
    t.id_burimi = gjeneroIdArdhure();
    t.id_user = id_user;
    printf("Burimi i se ardhures:");
    scanf(" %s", t.burimi);
    printf("Shuma: ");
    scanf("%f", &t.shuma);

    if(t.shuma<0){
        printf("E ardhura duhet nr 0 ose pozitiv"); //LOGJIKA: mbase user mbase s'ka vertet lek
        return;
    }

    lexoDaten(&dita, &muaji, &viti);
    sprintf(t.data, "%02d-%02d-%04d", dita, muaji, viti);

    fprintf(fptr, "%d %d %s %.2f %s\n",
            t.id_burimi,
            t.id_user,
            t.burimi,
            t.shuma,
            t.data);

    fclose(fptr);

    printf("Te ardhurat u shtuan me sukses!\n\n");
}

void shfaqShpenzime(int id_user)
{
    FILE *fptr = fopen("shpenzime.txt", "r");
    struct Shpenzim s;

    if (fptr == NULL)
    {
        printf("Dicka shkoi keq!");
    }
    printf("\n%-12s %-10s  %-15s %-15s %-20s %-20s %-10s %-12s\n",
           "ID_Shpenzim", "ID_User", "Pershkrim",
           "ID_Kat", "Kategoria", "Kat_Pershkrim",
           "Shuma", "Data");

    printf("-------------------------------------------------------------------------------------------------------------------------------\n");

    while (fscanf(fptr, "%d %d %s %d %s %s %f %s",
                  &s.id_shpenzim,
                  &s.id_user,
                  s.pershkrim,
                  &s.kategori.id_kategoria,
                  s.kategori.emertimi,
                  s.kategori.pershkrimi,
                  &s.shuma,
                  s.data) != EOF)
    {
        if (s.id_user == id_user)
        {
            printf("%-12d %-10d %-20s %-10d %-15s %-20s %-10.2f %-12s\n",
                   s.id_shpenzim,
                   s.id_user,
                   s.pershkrim,
                   s.kategori.id_kategoria,
                   s.kategori.emertimi,
                   s.kategori.pershkrimi,
                   s.shuma,
                   s.data);
        }
    }
}

void shfaqTeArdhura(int id_user)
{
    FILE *fptr=fopen("teArdhura.txt","r");
    if(fptr==NULL){
        printf("S'hapet file lol");
        return;
    }
    struct Te_Ardhura t;
    printf("\n%-5s %-8s %-20s %-12s %-15s\n",
           "ID", "User", "Burimi", "Shuma", "Data");

    printf("------------------------------------------------------------\n");

    while (fscanf(fptr, "%d %d %s %f %s",
                  &t.id_burimi,
                  &t.id_user,
                  t.burimi,
                  &t.shuma,
                  t.data) == 5)
    {
        if (t.id_user == id_user) {

            printf("%-5d %-8d %-20s %-12.2f %-15s\n",
                   t.id_burimi,
                   t.id_user,
                   t.burimi,
                   t.shuma,
                   t.data);
        }
    }

    fclose(fptr);

}

void raportMujor(int id_user)
{
    int muaji, viti;
    printf("Muaji (1-12): "); scanf("%d", &muaji);
    printf("Viti: "); scanf("%d", &viti);

    FILE *fs = fopen("shpenzime.txt", "r");
    FILE *fa = fopen("teArdhura.txt", "r");

    struct Shpenzim s;
    struct Te_Ardhura t;
    float total_shp = 0, total_ard = 0;
    int dd, mm, yy;

    printf("\n===== RAPORT MUJOR: %02d/%04d =====\n", muaji, viti);

    // Shpenzimet
    printf("\n-- Shpenzimet --\n");
    if (fs != NULL) {
        while (fscanf(fs, "%d %d %s %d %s %s %f %s",
                      &s.id_shpenzim, &s.id_user, s.pershkrim,
                      &s.kategori.id_kategoria, s.kategori.emertimi,
                      s.kategori.pershkrimi, &s.shuma, s.data) == 8) {
            sscanf(s.data, "%d-%d-%d", &dd, &mm, &yy);
            if (s.id_user == id_user && mm == muaji && yy == viti) {
                printf("  [%d] %s - %s - %.2f ALL - %s\n",
                       s.id_shpenzim, s.pershkrim, s.kategori.emertimi, s.shuma, s.data);
                total_shp += s.shuma;
            }
        }
        fclose(fs);
    }

    // Te ardhurat
    printf("\n-- Te Ardhurat --\n");
    if (fa != NULL) {
        while (fscanf(fa, "%d %d %s %f %s",
                      &t.id_burimi, &t.id_user, t.burimi, &t.shuma, t.data) == 5) {
            sscanf(t.data, "%d-%d-%d", &dd, &mm, &yy);
            if (t.id_user == id_user && mm == muaji && yy == viti) {
                printf("  [%d] %s - %.2f ALL - %s\n",
                       t.id_burimi, t.burimi, t.shuma, t.data);
                total_ard += t.shuma;
            }
        }
        fclose(fa);
    }

    printf("\n-- Permbledhje --\n");
    printf("Total shpenzime  : %.2f\n", total_shp);
    printf("Total te ardhura : %.2f\n", total_ard);
    printf("Bilanci          : %.2f\n", total_ard - total_shp);
    printf("\n\n");
}

void raportVjetor(int id_user)
{
    int viti;
    printf("Viti:");
    scanf("%d",&viti);
    FILE *fs = fopen("shpenzime.txt", "r");
    FILE *fa = fopen("teArdhura.txt", "r");
    struct Shpenzim s;
    struct Te_Ardhura t;
    float shp[13] = {0};
    float ard[13] = {0}; //ruajn shumat per cdo muaj
    int dd, mm, yy;

    if (fs != NULL) {
        while (fscanf(fs, "%d %d %s %d %s %s %f %s",
                      &s.id_shpenzim, &s.id_user, s.pershkrim,
                      &s.kategori.id_kategoria, s.kategori.emertimi,
                      s.kategori.pershkrimi, &s.shuma, s.data) == 8) {
            sscanf(s.data, "%d-%d-%d", &dd, &mm, &yy); // e ben split
            if (s.id_user == id_user && yy == viti && mm >= 1 && mm <= 12)
                shp[mm] += s.shuma;
        }
        fclose(fs);
    }

    if(fa!=NULL){
        while(fscanf(fa,"%d %d %s %f %s",&t.id_burimi,&t.id_user,t.burimi,&t.shuma,t.data)==5){
             sscanf(t.data, "%d-%d-%d", &dd, &mm, &yy);
             if(t.id_user==id_user && yy==viti && mm>=1 && mm<=12){
                ard[mm]+=t.shuma;
             }
        }
        fclose(fa);
    }

    float total_shp = 0, total_ard = 0;

    printf("\n===== RAPORT VJETOR: %04d =====\n", viti);
    printf("%-6s %-12s %-12s %-12s\n", "Muaji", "Te Ardhura", "Shpenzime", "Bilanci");
    printf("------------------------------------------\n");
    for (int m = 1; m <= 12; m++) {
        printf("%-6d %-12.2f %-12.2f %-12.2f\n",
               m, ard[m], shp[m], ard[m] - shp[m]);
        total_shp += shp[m];
        total_ard += ard[m];
    }
    printf("------------------------------------------\n");
    printf("%-6s %-12.2f %-12.2f %-12.2f\n",
           "TOT", total_ard, total_shp, total_ard - total_shp);
}

void kontrolloBuxhetin(int id_user)
{
    FILE *fptr=fopen("user.txt","r");
    if(fptr==NULL){
        printf("Dicka shkoi keq!");
        return;
    }

    struct Perdorues p;
    float buxheti=0;

    while(fscanf(fptr,"%d %s %s %s %f",&p.id_user,p.emri,p.username,p.password,&p.buxheti_vjetor)==5){
        if(p.id_user==id_user){
            buxheti=p.buxheti_vjetor;
        }
    }
    fclose(fptr);

    float te_ardhura=totalTeArdhura(id_user);
    float shpenzime=totalShpenzime(id_user);
    float mbetje=te_ardhura-shpenzime;

    printf("========== KONTROLLO BUXHETIN ==========\n");
    printf("Buxheti vjetor : %.2f\n", buxheti);
    printf("Te ardhura     : %.2f\n", te_ardhura);
    printf("Shpenzime      : %.2f\n", shpenzime);
    printf("Mbetur         : %.2f\n", mbetje);

    if (shpenzime > te_ardhura)
        printf("[!] Ke tejkaluar te ardhurat!\n");
    else if (mbetje < buxheti * 0.2f)
        printf("[!] Ke shpenzuar mbi 80%% te buxhetit!\n");
    else
        printf("[OK] Buxheti eshte ne rregull.\n");

    printf("\n\n");
}

void kerkoShpenzimSipasKategorise(int id_user)
{
    // si logjike: Thjesht vendos id e kategorise dhe aty ku id_user==vleren ne file, same thing per kategorine
    FILE *fptr=fopen("shpenzime.txt","r");
    FILE *kat=fopen("kategori.txt","r");
    if(fptr==NULL || kat==NULL){
        printf("Dicka shkoi keq!");
        return;
    }
    struct Shpenzim s;
    struct Kategoria k;
    int found=0;

    printf("\nKategorite:\n");
    while (fscanf(kat, "%d %s %s",
                  &k.id_kategoria,
                  k.emertimi,
                  k.pershkrimi) == 3)
    {
        printf("%d - %s\n", k.id_kategoria, k.emertimi);
    }

            int id_kategori;
            printf("Vendos ID e kategorise: ");
            scanf("%d", &id_kategori);



    printf("============ Kerko shpenzim sipas kategorise: ============\n");
    while (fscanf(fptr, "%d %d %s %d %s %s %f %s",
           &s.id_shpenzim,
           &s.id_user,
           s.pershkrim,
           &s.kategori.id_kategoria,
           s.kategori.emertimi,
           s.kategori.pershkrimi,
           &s.shuma,
           s.data)==8){
            if(s.id_user==id_user && s.kategori.id_kategoria==id_kategori){
                printf("ID : %d | %s | %s | %.2f | %s\n",
                       s.id_shpenzim,
                       s.pershkrim,
                       s.kategori.emertimi,
                       s.shuma,
                       s.data);
                found=1;
            }
           }
           if(!found){
            printf("Nuk gjendet ndonje gje ne lidhje me kete :( ");
           }
           fclose(fptr);
}

void fshiShpenzim(int id_shpenzim)
{
    FILE *fs=fopen("shpenzime.txt","r");
    FILE *temp_s=fopen("temp_shpenzime.txt","w");

    if(fs==NULL||temp_s==NULL){
        printf("Dicka shkoi keq");
        return;
    }
    struct Shpenzim s;
    int found=0;

    while (fscanf(fs, "%d %d %s %d %s %s %f %s",
           &s.id_shpenzim,
           &s.id_user,
           s.pershkrim,
           &s.kategori.id_kategoria,
           s.kategori.emertimi,
           s.kategori.pershkrimi,
           &s.shuma,
           s.data)==8){
            if(s.id_shpenzim==id_shpenzim){
                found=1;
                continue;
            }

            fprintf(temp_s,"%d %d %s %d %s %s %f %s\n",
            s.id_shpenzim,
           s.id_user,
           s.pershkrim,
           s.kategori.id_kategoria,
           s.kategori.emertimi,
           s.kategori.pershkrimi,
           s.shuma,
           s.data);
           }

    fclose(fs);
    fclose(temp_s);
    fcloseall();

    if(!found){
        remove("temp_shpenzime.txt");
        printf("Shpenzimi juaj me kete ID su gjet!");
        return;

    }

    remove("shpenzime.txt");
    rename("temp_shpenzime.txt","shpenzime.txt");
    printf("Shpenzimi juaj me ID %d u fshi me sukses!\n\n",id_shpenzim);

}

void renditShpenzimeSipasShumes(int id_user)
{
    printf("renditShpenzimeSipasShumes not implemented yet\n\n");
}

void renditShpenzimeSipasDates(int id_user)
{
    printf("renditShpenzimeSipasDates not implemented yet\n\n");
}

#include <stdio.h>
#include <string.h>

void kerkoShpenzimSipasId(int id_shpenzim)
{
    FILE *fptr = fopen("shpenzime.txt", "r");

    if (fptr == NULL) {
        printf("Dicka shkoi keq\n");
        return;
    }

    struct Shpenzim s;
    int found=0;

    // Table header
    printf("---------------------------------------------------------------------------------------------\n");
    printf("%-5s %-5s %-20s %-10s %-15s %-10s %-10s\n",
           "ID",
           "User",
           "Pershkrim",
           "KatID",
           "Kategoria",
           "Shuma",
           "Data");
    printf("---------------------------------------------------------------------------------------------\n");

    while (fscanf(fptr, "%d %d %s %d %s %s %f %s",
                  &s.id_shpenzim,
                  &s.id_user,
                  s.pershkrim,
                  &s.kategori.id_kategoria,
                  s.kategori.emertimi,
                  s.kategori.pershkrimi,
                  &s.shuma,
                  s.data) == 8)
    {
        if (s.id_shpenzim == id_shpenzim) {
            found=1;
            printf("%-5d %-5d %-20s %-10d %-15s %-10.2f %-10s\n",
                   s.id_shpenzim,
                   s.id_user,
                   s.pershkrim,
                   s.kategori.id_kategoria,
                   s.kategori.emertimi,
                   s.shuma,
                   s.data);
        }
    }

    printf("---------------------------------------------------------------------------------------------\n\n");

    if (!found) {
        printf("Shpenzimi me ID %d nuk u gjet.\n\n", id_shpenzim);
    }

    fclose(fptr);
    fcloseall();
}

void kerkoShpenzimSipasDate(int id_user, char data[])
{
    printf("kerkoShpenzimSipasDate not implemented yet\n\n");
}

void kerkoShpenzimeIntervalDate(int id_user, char data1[], char data2[])
{
    printf("kerkoShpenzimeIntervalDate not implemented yet\n\n");
}
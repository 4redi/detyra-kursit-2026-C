#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "structs.h"
#include "utils.h"

int eshtUsernameUnik(const char username[])
{
    FILE *fptr = fopen("user.txt", "r");
    int id_user;
    char emri[30];
    char Fileusername[20]; // username qe merret nga file
    char password[50];
    float buxheti_mujor;

    if (fptr == NULL)
    {
        return 1; // po, meqe file bosh
    }
    while (fscanf(fptr, "%d %s %s %s %f", &id_user, emri, Fileusername, password, &buxheti_mujor) != EOF)
    {
        if (strcasecmp(username,Fileusername) == 0)
        {
            fclose(fptr);
            return 0; // un jo unik
        }
    }
    fclose(fptr);
    return 1; // po meqe ploteson kushtin
}

int eshtPasswordValid(const char password[])
{
    int i;
    int kaNumber = 0;
    int kaSimbol = 0;

    // respektimi i karaktereve
    if (strlen(password) < 4)
    {
        return 0;
    }
    // respektimi i shkronjes se madhe
    if (!isupper(password[0]))
    {
        return 0;
    }

    for (i = 0; password[i] != '\0'; i++)
    {
        if (isdigit(password[i]))
        {
            kaNumber = 1;
        }
        if (strchr("!@#$%^&*()-_=+[]{};:,.<>?", password[i]))
        {
            kaSimbol = 1;
        }
    }

    if (kaNumber && kaSimbol)
    {
        return 1; // valid
    }
    return 0; // invalid
}

int gjeneroIdUser()
{
    FILE *fptr = fopen("user.txt", "r");
    if(fptr==NULL){
        return 1; //file bosh, so unike
    }
    int last_id=0;
    struct Perdorues p;
    while (fscanf(fptr, "%d %s %s %s %f",
              &p.id_user,
              p.emri,
              p.username,
              p.password,
              &p.buxheti_mujor) ==5){
                if(p.id_user>last_id){
                    last_id=p.id_user;
                }
              }
    fclose(fptr);
    return last_id+1;

    
}


int gjeneroIdShpenzim()
{
    FILE *f = fopen("shpenzime.txt", "r");
    if (f == NULL)
        return 1;

    int last_id = 0;
    struct Shpenzim s;
    char username[20];

    while (fscanf(f, "%d %d %s %s %d %s %s %f %s",
                  &s.id_shpenzim,
                  &s.id_user,
                  username,
                  s.pershkrim,
                  &s.kategori.id_kategoria,
                  s.kategori.emertimi,
                  s.kategori.pershkrimi,
                  &s.shuma,
                  s.data) == 9)
    {
        if (s.id_shpenzim > last_id)
            last_id = s.id_shpenzim;
    }

    fclose(f);
    return last_id + 1;
}

int lexoDaten(int *dita, int *muaji, int *viti)
{
    int valid = 0;

    while (!valid)
    {
        printf("Data (dd-mm-yyyy): ");
        scanf("%d-%d-%d", dita, muaji, viti);

        int maxDite = diteNeMuaj(*muaji, *viti);

        if (maxDite == 0 ||
            *dita < 1 || *dita > maxDite ||
            *viti < 1900 || *viti > 2100)
        {
            printf("Date e pavlefshme! Provo perseri.\n");
        }
        else
        {
            valid = 1;
        }
    }

    return 1;
}

int eshtVitiBisht(int viti)
{
    return (viti % 4 == 0 && viti % 100 != 0) || (viti % 400 == 0);
}

int diteNeMuaj(int muaji, int viti)
{
    switch (muaji)
    {
        case 1: case 3: case 5: case 7:
        case 8: case 10: case 12:
            return 31;

        case 4: case 6: case 9: case 11:
            return 30;

        case 2:
            return eshtVitiBisht(viti) ? 29 : 28;

        default:
            return 0;
    }
}


float totalTeArdhura(int id_user)
{
    FILE *f = fopen("teArdhura.txt", "r");
    if (!f) return 0;

    struct Te_Ardhura t;
    float total = 0;

    while (fscanf(f, "%d %d %s %f %s",
                  &t.id_burimi,
                  &t.id_user,
                  t.burimi,
                  &t.shuma,
                  t.data) == 5)
    {
        if (t.id_user == id_user)
            total += t.shuma;
    }

    fclose(f);
    return total;
}

float totalShpenzime(int id_user)
{
    FILE *f = fopen("shpenzime.txt", "r");
    if (!f) return 0;
    struct Shpenzim s;
    float total = 0;
    char username[20];

    while (fscanf(f, "%d %d %s %s %d %s %s %f %s",
                  &s.id_shpenzim,
                  &s.id_user,
                  s.pershkrim,
                  username,
                  &s.kategori.id_kategoria,
                  s.kategori.emertimi,
                  s.kategori.pershkrimi,
                  &s.shuma,
                  s.data) == 9)
    {
        if (s.id_user == id_user)
            total += s.shuma;
    }

    fclose(f);
    return total;
}

int gjeneroIdArdhure() {
    FILE *fptr = fopen("teArdhura.txt", "r");

    if (fptr == NULL) {
        return 1;
    }

    int last_id = 0;
    struct Te_Ardhura t;

    while (fscanf(fptr, "%d %d %s %f %s",
                  &t.id_burimi,
                  &t.id_user,
                  t.burimi,
                  &t.shuma,
                  t.data) == 5) {

        if (t.id_burimi > last_id) {
            last_id = t.id_burimi;
        }
    }

    fclose(fptr);

    return last_id + 1;
}
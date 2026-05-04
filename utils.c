#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

int eshtIdValid(int id_user)
{
    if(id_user<=0) return 0;
    FILE *fptr = fopen("user.txt", "r");

    int fileId; // Id qe merret nga file
    char emri[30];
    char username[20];
    char password[50];
    float buxheti_mujor;

    if (fptr == NULL)
    {
        return 1; // id unike sepse file bosh
    }
    while (fscanf(fptr, "%d %s %s %s %f", &fileId, emri, username, password, &buxheti_mujor) != EOF)
    {
        if (fileId == id_user)
        {
            return 0; // id jo unike
        }
    }
    fclose(fptr);
    return 1; // id unike sepse nuk u plotesua kushti ndalues (testimi i jo unicitetit)
}
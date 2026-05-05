#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "auth.h"
#include "utils.h"
#include "structs.h"

int login(int *id_user, char username[])
{
    FILE *fptr = fopen("user.txt", "r");

    char inputUsername[20], password[50];

    printf("Username: ");
    scanf("%19s", inputUsername);

    printf("Password: ");
    scanf("%49s", password);

    if (strcmp(inputUsername, "admin") == 0 && strcmp(password, "Admin123@") == 0)
    {
        strcpy(username, "admin");
        return LOGIN_ADMIN;
    }

    if (fptr == NULL)
    {
        printf("S'ka perdorues!\n");
        return LOGIN_FAIL;
    }

    struct Perdorues p;

    while (fscanf(fptr, "%d %s %s %s %f",
                  &p.id_user, p.emri, p.username, p.password, &p.buxheti_mujor) != EOF)
    {
        if (strcasecmp(inputUsername, p.username) == 0 &&
            strcmp(password, p.password) == 0)
        {
            *id_user = p.id_user;
            strcpy(username, p.username);
            fclose(fptr);
            return LOGIN_USER;
        }
    }

    fclose(fptr);
    printf("User nuk ekziston!\n");

    char choice;
    printf("Doni te krijoni nje user te ri? (p/j): ");
    scanf(" %c", &choice);

    if (choice == 'p' || choice == 'P')
    {
        regjistroPerdorues();
        printf("Tani mund te logoheni.\n");
    }
    return LOGIN_FAIL;
}

void regjistroPerdorues()
{
    FILE *fptr = fopen("user.txt", "a");

    if (fptr == NULL)
    {
        printf("Gabim ne hapjen e file-it!\n");
        return;
    }

    struct Perdorues p;

    // ID
    do
    {
        printf("Vendos ID: ");
        scanf("%d", &p.id_user);

        if (!eshtIdValid(p.id_user))
        {
            printf("Kjo ID ekziston ose eshte me e vogel se 1! Provo perseri.\n");
        }

    } while (!eshtIdValid(p.id_user));

    // Emri
    printf("Emri: ");
    scanf("%s", p.emri);

    // Username
    do
    {
        printf("Username: ");
        scanf("%s", p.username);

        if (!eshtUsernameUnik(p.username))
        {
            printf("Username ekziston! Provo tjeter.\n");
        }
        else if(strlen(p.username)<5){
            printf("Username duhet 5 karaktere e mbi!\n");
        }

    } while (!eshtUsernameUnik(p.username)||strlen(p.username)<5);

    // Password
    do
    {
        printf("Password: ");
        scanf("%s", p.password);

        if (!eshtPasswordValid(p.password))
        {
            printf("Password duhet:\n");
            printf("- Te filloje me shkronje te madhe\n");
            printf("- Te kete numer, karakter special\n");
            printf("- Minimum 4 karaktere\n");
        }

    } while (!eshtPasswordValid(p.password));

    // Buxheti
    printf("Buxheti mujor: ");
    scanf("%f", &p.buxheti_mujor);

    // Ruajtja ne file
    fprintf(fptr, "%d %s %s %s %.2f\n",
            p.id_user,
            p.emri,
            p.username,
            p.password,
            p.buxheti_mujor);

    fclose(fptr);

    printf("Perdoruesi u regjistrua me sukses!\n");
}
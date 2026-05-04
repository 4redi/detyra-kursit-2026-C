#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "menu.h"
#include "auth.h"
#include "user.h"
#include "admin.h"

void menuja()
{
    int choice;
    int id_user;
    int role;
    char username[20];
    do
    {
        printf("\n####### Mire se vini #######\n");
        printf("1. Administrator\n");
        printf("2. Perdorues\n");
        printf("3. Dil\n");
        printf("Zgjidhni: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            role = login(&id_user, username);

            if (role == LOGIN_ADMIN)
            {
                adminMenu();
            }
            else if (role == LOGIN_FAIL)
            {
                printf("Login deshtoi!\n");
            }
            break;

        case 2:
            role = login(&id_user, username);

            if (role == LOGIN_USER)
            {
                userMenu(id_user, username);
            }

            break;

        case 3:
            return;

        default:
            printf("Invalid!\n");
        }
    } while (choice != 3);
}
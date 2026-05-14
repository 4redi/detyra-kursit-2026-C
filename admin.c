#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "admin.h"
#include "menu.h"
#include "structs.h"
#include "auth.h"
#include "utils.h"
#include <errno.h>

void adminMenu()
{
    printf("\n\n");
    printf("------------------- Mire se erdhet Admin!  -----------------------------\n");
    int choice;
    int id_user;
    char username[20];
    do
    {
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
        scanf("%d", &choice);
        printf("\n");

        switch (choice)
        {
        case 1:
            shtoPerdorues();
            break;
        case 2:
            shfaqPerdoruesit();
            break;
        case 3:
            printf("Vendosni id qe doni te kerkoni:");
            scanf("%d", &id_user);
            kerkoSipasId(id_user);
            printf("\n\n");
            break;
        case 4:
            printf("Vendosni id qe doni te fshihni:");
            scanf("%d", &id_user);
            fshiPerdorues(id_user);
            break;
        case 5:
            printf("Vendosni id qe doni te update:");
            scanf("%d", &id_user);
            updatePerdorues(id_user);
            break;
        case 6:
            shfaqTeTerePerdoruesit();
            break;
        case 7:
            printf("Vendosni username qe doni te kerkoni:");
            scanf("%s", username);
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
    } while (choice != 11);
}

void shtoPerdorues()
{
    regjistroPerdorues();
    printf("\n\n");
}
void shfaqPerdoruesit()
{
    FILE *fptr = fopen("user.txt", "r");

    if (fptr == NULL)
    {
        printf("Skedari bosh");
    }
    struct Perdorues p;
    printf("\n%-5s %-15s %-15s\n",
           "ID", "Emri", "Username");
    printf("--------------------------------------\n");

    while (fscanf(fptr, "%d %s %s %s %f", &p.id_user, p.emri, p.username, p.password, &p.buxheti_vjetor) != EOF)
    {
        printf("%-5d %-15s %-15s\n",
               p.id_user,
               p.emri,
               p.username);
    }
    fclose(fptr);
    printf("\n\n");
}

void shfaqTeTerePerdoruesit()
{
    FILE *fu = fopen("user.txt", "r");
    if (fu == NULL)
    {
        printf("Asnje perdorues!\n");
        return;
    }
    struct Perdorues p;
    printf("\n%-5s %-15s %-15s %-15s %-12s %-12s %-12s\n",
           "ID", "Emri", "Username", "Password", "Buxheti", "Te Ardhura", "Shpenzime");
    printf("----------------------------------------------------------------------------------------\n");

    while (fscanf(fu, "%d %s %s %s %f",
                  &p.id_user, p.emri, p.username, p.password, &p.buxheti_vjetor) == 5)
    {
        float ardhura = totalTeArdhura(p.id_user);
        float shpenzime = totalShpenzime(p.id_user);
        printf("%-5d %-15s %-15s %-15s %-12.2f %-12.2f %-12.2f\n",
               p.id_user, p.emri, p.username, p.password,
               p.buxheti_vjetor, ardhura, shpenzime);
    }
    fclose(fu);
}

void kerkoSipasId(int id_user)
{
    FILE *fptr = fopen("user.txt", "r");
    if (fptr == NULL)
    {
        printf("Dicka shkoi keq!");
        return;
    }
    struct Perdorues p;
    int found = 0;

    while (fscanf(fptr, "%d %s %s %s %f",
                  &p.id_user, p.emri, p.username, p.password, &p.buxheti_vjetor) == 5)
    {
        if (p.id_user == id_user)
        {
            printf("\nID       : %d\n", p.id_user);
            printf("Emri     : %s\n", p.emri);
            printf("Username : %s\n", p.username);
            printf("Password : %s\n", p.password);
            printf("Buxheti  : %.2f\n", p.buxheti_vjetor);
            printf("Shpenzime Totale  : %.2f\n", totalShpenzime(p.id_user));
            printf("Ardhura Totale  : %.2f\n", totalTeArdhura(p.id_user));
            printf("Mbetja  : %.2f\n", totalTeArdhura(p.id_user) - totalShpenzime(p.id_user));
            found = 1;
            break;
        }
    }

    fclose(fptr);
    if (!found)
    {
        printf("Perdoruesi me %d ID nuk ekziston!", id_user);
    }
    printf("\n\n");
}
void fshiPerdorues(int id_user)
{

    FILE *fptr = fopen("user.txt", "r");
    FILE *temp = fopen("users_temp.txt", "w");

    if (fptr == NULL || temp == NULL)
    {
        printf("Dicka shkoi keq!\n");
        return;
    }

    struct Perdorues p;
    struct Shpenzim s;
    struct Te_Ardhura t;
    int found = 0;

    while (fscanf(fptr, "%d %s %s %s %f",
                  &p.id_user,
                  p.emri,
                  p.username,
                  p.password,
                  &p.buxheti_vjetor) == 5)
    {

        if (p.id_user == id_user)
        {
            found = 1;
            continue;
        }

        fprintf(temp, "%d %s %s %s %.2f\n",
                p.id_user,
                p.emri,
                p.username,
                p.password,
                p.buxheti_vjetor);
    }

    fclose(fptr);
    fclose(temp);

    fcloseall(); // kam lene file hapur diku

    if (!found)
    {
        remove("users_temp.txt");
        printf("Perdoruesi nuk u gjet!\n");
        return;
    }

    remove("user.txt");
    rename("users_temp.txt", "user.txt");

    // sjpenzimet
    FILE *fs = fopen("shpenzime.txt", "r");
    FILE *tempS = fopen("temp_shpenzime.txt", "w");

    if (fs != NULL && tempS != NULL)
    {
        while (fscanf(fs, "%d %d %s %d %s %s %f %s",
                      &s.id_shpenzim,
                      &s.id_user,
                      s.pershkrim,
                      &s.kategori.id_kategoria,
                      s.kategori.emertimi,
                      s.kategori.pershkrimi,
                      &s.shuma,
                      s.data) == 8)
        {
            if (s.id_user == id_user)
                continue;

            fprintf(tempS, "%d %d %s %d %s %s %.2f %s\n",
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
        fclose(tempS);

        remove("shpenzime.txt");
        rename("temp_shpenzime.txt", "shpenzime.txt");
    }

    // t ardhura

    FILE *fa = fopen("teArdhura.txt", "r");
    FILE *tempA = fopen("temp_ardhura.txt", "w");

    if (fa != NULL && tempA != NULL)
    {
        while (fscanf(fa, "%d %d %s %f %s",
                      &t.id_burimi,
                      &t.id_user,
                      t.burimi,
                      &t.shuma,
                      t.data) == 5)
        {
            if (t.id_user == id_user)
                continue;

            fprintf(tempA, "%d %d %s %.2f %s\n",
                    t.id_burimi,
                    t.id_user,
                    t.burimi,
                    t.shuma,
                    t.data);
        }

        fclose(fa);
        fclose(tempA);

        remove("teArdhura.txt");
        rename("temp_ardhura.txt", "teArdhura.txt");
    }

    printf("Perdoruesi dhe te dhenat e tij u fshine me sukses!\n");

    printf("Perdoruesi u fshi me sukses!\n");
}

void updatePerdorues(int id_user)
{
    FILE *fptr = fopen("user.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (fptr == NULL || temp == NULL)
    {
        printf("Gabim ne hapjen e file-ve");
        return;
    }

    struct Perdorues p;
    int found = 0;
    char newUsername[20];
    while (fscanf(fptr, "%d %s %s %s %f", &p.id_user, p.emri, p.username, p.password, &p.buxheti_vjetor) == 5)
    {
        if (p.id_user == id_user)
        {
            found = 1;
            printf("Username aktual: %s\n", p.username);

            do
            {
                printf("Vendos nje username te ri:");
                scanf("%s", newUsername);
                if (!eshtUsernameUnik(newUsername))
                {
                    printf("Username ekziston!\n");
                }
                else if (strlen(newUsername) < 5)
                {
                    printf("Username duhet te kete te pakten 5 karaktere!\n");
                }
            } while (!eshtUsernameUnik(newUsername));
            strcpy(p.username, newUsername);
        }

        fprintf(temp, "%d %s %s %s %.2f\n",
                p.id_user,
                p.emri,
                p.username,
                p.password,
                p.buxheti_vjetor);
    }
    fclose(fptr);
    fclose(temp);
    fcloseall();

    if (!found)
    {
        remove("temp.txt");
        printf("Perdoruesi nuk u gjet!\n");
        return;
    }

    remove("user.txt");
    rename("temp.txt", "user.txt");

    printf("Username u ndryshua me sukses!\n");
}
void kerkoSipasUsername(char username[])
{
    FILE *fptr = fopen("user.txt", "r");

    if (fptr == NULL)
    {
        printf("Gabim ne hapjen e file!\n");
        return;
    }

    struct Perdorues p;
    int found = 0;

    while (fscanf(fptr, "%d %s %s %s %f",
                  &p.id_user,
                  p.emri,
                  p.username,
                  p.password,
                  &p.buxheti_vjetor) == 5)
    {
        if (_stricmp(username, p.username) == 0)
        {
            found = 1;
            break;
        }
    }

    fclose(fptr);

    if (!found)
    {
        printf("Perdoruesi nuk u gjet!\n");
        return;
    }

    int choice;

    do
    {

        printf("\n===== USER MENU =====\n");
        printf("Username : %s\n", p.username);

        printf("1. Info personale\n");
        printf("2. Total shpenzime\n");
        printf("3. Total te ardhura\n");
        printf("4. Bilanci\n");
        printf("5. Kthehu\n");

        printf("Zgjedhja: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("\n===== INFO =====\n");
            printf("ID         : %d\n", p.id_user);
            printf("Emri       : %s\n", p.emri);
            printf("Username   : %s\n", p.username);
            printf("Buxheti    : %.2f\n", p.buxheti_vjetor);
            break;
        case 2:
            printf("\nTotal shpenzime: %.2f\n",
                   totalShpenzime(p.id_user));
            break;
        case 3:
            printf("\nTotal te ardhura: %.2f\n",
                   totalTeArdhura(p.id_user));
            break;
        case 4:
        {
            float ard = totalTeArdhura(p.id_user);
            float shp = totalShpenzime(p.id_user);
            printf("\nBilanci: %.2f\n", ard - shp);
            break;
        }
        case 5:
            break;
        default:
            printf("Zgjedhje e pavlefshme!\n");
        }

    } while (choice != 5);
}
void rradhitSipasUsername()
{
    // mendoje si nje array dhe do i besh order me bubble sort

    FILE *fptr = fopen("user.txt", "r");
    if (fptr == NULL)
    {
        printf("Dicka shkoi keq");
        return;
    }
    struct Perdorues p[100];
    int n = 0; // iteruesja
    while (fscanf(fptr, "%d %s %s %s %f", &p[n].id_user, p[n].emri, p[n].username, p[n].password, &p[n].buxheti_vjetor) == 5)
    {
        n++;
    }

    fclose(fptr);

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (strcmp(p[j].username, p[j + 1].username) > 0)
            {
                struct Perdorues temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    printf("User-at e afishuar :\n");
    for (int i = 0; i < n; i++)
    {
        printf("%s\n", p[i].username);
    }
}
void adminMenuKategori()
{
    printf("========= Menu kategori =========\n");
    int choice;
    struct Kategoria k;
    do
    {
        printf("1. Shih kategorite\n");
        printf("2. Shto kategori\n");
        printf("3. Perditeso kategori\n");
        printf("4. Fshi kategori\n");
        printf("5.Dil\n");

        printf("Zgjedhja:");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
        {
            FILE *kat = fopen("kategori.txt", "r");
            if (kat == NULL)
            {
                printf("Nuk mund te hapet kategori.txt\n");
                break;
            }
            printf("\n%40s\n", "==========Kategorite==========");
            while (fscanf(kat, "%d %s %s",
                          &k.id_kategoria,
                          k.emertimi,
                          k.pershkrimi) == 3)
            {
                printf("%d - %s - %s\n", k.id_kategoria, k.emertimi, k.pershkrimi);
            }
            fclose(kat);
            printf("\n\n");
            break;
        }
        case 2:
        {
            FILE *kat = fopen("kategori.txt", "a");
            if (kat == NULL)
            {
                printf("Dicka shkoi keq");
                return;
            }
            k.id_kategoria = gjeneroIdKategori();
            printf("Vendosni emertimin:");
            scanf(" %[^\n]",k.emertimi);
            printf("Vendosni pershkrimin:");
            scanf(" %[^\n]",k.pershkrimi);

            fprintf(kat, "%d %s %s\n",
                    k.id_kategoria,
                    k.emertimi,
                    k.pershkrimi);

            printf("Kategoria e %d u shtua me sukses!",k.id_kategoria);
            fclose(kat);
            printf("\n\n");
            break;
        }
        case 3:
            // update
            break;
        case 4:
            // fshirje
            break;
        case 5:
            break;
        default:
            printf("Zgjedhje e pavlefshme!");
        }

    } while (choice != 5);
} // crud per kategorine
void statistika()
{
    printf("Akoma");
}

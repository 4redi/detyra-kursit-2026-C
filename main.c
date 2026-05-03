#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define LOGIN_FAIL 0
#define LOGIN_USER 1
#define LOGIN_ADMIN 2

// ###### Menuja #######

void menuja();
int login(int *id_user);
void regjistroPerdorues();

// ###### Fundi menuja #######

// ####### Administator funksionet ########

void adminMenu(); // vendi ku do mbahen te gjitha funx. e meposhtme
void shtoPerdorues();
void shfaqPerdoruesit();
void kerkoSipasId(int id_user);
void fshiPerdorues(int id_user);
void updatePerdorues(int id_user);
void kerkoSipasUsername(char username[]);
void rradhitSipasUsername();
void adminMenuKategori(); // crud per kategorine
void statistika();        // si tip menuje ku mund te shohesh nr users, total shpenzimesh, mesatare shpenzimesh, kategoria max, etc

// ####### Fund administator funksionet ########

// ######## Perdorues funksionet ##########

void userMenu(int id_user); // vendi ku mbahen te gjitha funx. e meposhthme
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

// * ######### Strukturat ############ //

struct Perdorues
{
    int id_user;
    char emri[30];
    char username[20];
    char password[50];
    float buxheti_mujor;
};

struct Kategoria
{
    int id_kategoria;
    char emertimi[50];
    char pershkrimi[100];
};

struct Shpenzim
{
    int id_shpenzim;
    int id_user;
    char pershkrim[50];
    struct Kategoria kategori;
    float shuma;
    char data[20];
};

// * ######### Fundi i strukturave ############ //

int main()
{
    menuja();
}

// * #######  Handler funksionet ########### //
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
        if (strcmp(username, Fileusername) == 0)
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
    return 1; // id unike sepse nuk u plotesua kushti ndalues (testimi i jo unicitetit)
}

// * ######## Fundi Funx. Handler ########


// * ###### Fillimi i Menuve ####### //
void menuja()
{
    int choice;
    int id_user;
    int role;
    do{
printf("\n####### Mire se vini #######\n");
    printf("1. Administrator\n");
    printf("2. Perdorues\n");
    printf("3. Dil\n");
    printf("Zgjidhni: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        role = login(&id_user);

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
        role = login(&id_user);

        if (role == LOGIN_USER)
        {
            userMenu(id_user);
        }

        break;

    case 3:
        return;

    default:
        printf("Invalid!\n");
    }
    }while(choice!=3);
}



void userMenu(int id_user)
{
    printf("Mireserdhet user %d", id_user);
}

void adminMenu()
{
    printf("Hi lol admin!\n");
}

// * ###### Fundi i Menuve ####### //



// * ###### Regjistrohu dhe Logohu ######  //
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
            printf("Kjo ID ekziston! Provo perseri.\n");
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

    } while (!eshtUsernameUnik(p.username));

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

int login(int *id_user)
{
    FILE *fptr = fopen("user.txt", "r");

    char username[20], password[50];

    printf("Username: ");
    scanf("%s", username);

    printf("Password: ");
    scanf("%s", password);

    // ADMIN
    if (strcmp(username, "admin") == 0 && strcmp(password, "Admin123") == 0)
    {
        return LOGIN_ADMIN;
    }

    if (fptr == NULL)
    {
        printf("S'ka perdorues ne file\n");
        return LOGIN_FAIL;
    }

    int fileId;
    char emri[30], fileUsername[20], filePassword[50];
    float buxheti;

    int foundUser = 0;

    while (fscanf(fptr, "%d %s %s %s %f",
                  &fileId, emri, fileUsername, filePassword, &buxheti) != EOF)
    {

        if (strcmp(username, fileUsername) == 0)
        {
            foundUser = 1;

            if (strcmp(password, filePassword) == 0)
            {
                *id_user = fileId;
                fclose(fptr);
                return LOGIN_USER;
            }
        }
    }

    fclose(fptr);
    char choice;
    // ! User exists por, pw gabim
    if (foundUser)
    {
        printf("Username i sakte por password gabim!\n");
    }
    // ! User nuk ekziston ne file
    else
    {
        printf("User-i nuk ekziston!\n");
    }

    printf("Deshiron te regjistrosh user tjeter? (p/j): ");
    scanf(" %c", &choice);

    if (choice == 'p' || choice == 'P')
    {
        regjistroPerdorues();
    }

    scanf(" %c", &choice);

    if (choice == 'p' || choice == 'P')
    {
        regjistroPerdorues();
    }

    return LOGIN_FAIL;
}

// * ###### Regjistrohu dhe Logohu Fundi ######  //
// TODO: Handle Menu-te, funksionet e perdoruesit
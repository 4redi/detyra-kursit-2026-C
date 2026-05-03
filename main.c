#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define LOGIN_FAIL 0
#define LOGIN_USER 1
#define LOGIN_ADMIN 2

// ###### Menuja #######

void menuja();
int login(int *id_user, char username[]);
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

void userMenu(int id_user, char username[]); // vendi ku mbahen te gjitha funx. e meposhthme
void shtoShpenzim(int id_user);
void shtoTeArdhura(int id_user);
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

// * ######## Fundi Funx. Handler ########

// * ###### Fillimi i Menuve ####### //
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

int login(int *id_user, char username[])
{
    FILE *fptr = fopen("user.txt", "r");

    char inputUsername[20], password[50];

    printf("Username: ");
    scanf("%s", inputUsername);

    printf("Password: ");
    scanf("%s", password);

    if (strcmp(inputUsername, "admin") == 0 && strcmp(password, "Admin123") == 0)
    {
        strcpy(username, "admin");
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

    while (fscanf(fptr, "%d %s %s %s %f",
                  &fileId, emri, fileUsername, filePassword, &buxheti) != EOF)
    {
        if (strcasecmp(inputUsername, fileUsername) == 0)
        {
            if (strcmp(password, filePassword) == 0)
            {
                *id_user = fileId;
                strcpy(username, fileUsername);
                fclose(fptr);
                return LOGIN_USER;
            }
            else
            {
                printf("Password gabim!\n");
                fclose(fptr);
                return LOGIN_FAIL;
            }
        }
    }

    fclose(fptr);
    printf("User-i nuk ekziston!\n");
    char choice;
    printf("Doni te krijoni nje user te ri? (p/j):");
    scanf(" %c",&choice);
    if(choice=='p'||choice=='P'){
        regjistroPerdorues();
    }
    return LOGIN_FAIL;
}

// * ###### Regjistrohu dhe Logohu Fundi ######  //
// TODO: Handle Menu-te, funksionet e perdoruesit



// * ###### User functions ########


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

// * ##### endregion

#ifndef UTILS_H
#define UTILS_H

int gjeneroIdUser();
int eshtUsernameUnik(const char username[]);
int eshtPasswordValid(const char password[]);
int gjeneroIdShpenzim();
int lexoDaten(int *dita, int *muaji, int *viti);
int eshtVitiBisht(int viti);
int diteNeMuaj(int muaji, int viti);
float totalTeArdhura(int id_user);
float totalShpenzime(int id_user);
int gjeneroIdKategori();
int gjeneroIdArdhure();
#endif
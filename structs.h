#ifndef STRUCTS_H
#define STRUCTS_H

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

#endif
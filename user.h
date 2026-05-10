#ifndef USER_H
#define USER_H

void userMenu(int id_user, char username[]);


// ######## Perdorues funksionet ##########

void userMenu(int id_user, char username[]); // vendi ku mbahen te gjitha funx. e meposhthme
void shtoShpenzim(int id_user);
void shtoTeArdhura(int id_user);
void shfaqShpenzime(int id_user);
void shfaqTeArdhura(int id_user);
void raportMujor(int id_user);
void raportVjetor(int id_user);
void kontrolloBuxhetin(int id_user);
void kerkoShpenzimSipasKategorise(int id_user);
void fshiShpenzim(int id_shpenzim);
void renditShpenzimeSipasShumes(int id_user);
void renditShpenzimeSipasDates(int id_user);
void kerkoShpenzimSipasId(int id_shpenzim);
void kerkoShpenzimSipasDate(int id_user, char data[]);
void kerkoShpenzimeIntervalDate(int id_user, char data1[], char data2[]);

// ######## Fundi perdorues funksionet ##########

#endif
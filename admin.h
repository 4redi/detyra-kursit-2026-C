#ifndef ADMIN_H
#define ADMIN_H

void adminMenu();
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
void statistika();  // si tip menuje ku mund te shohesh nr users, total shpenzimesh, mesatare shpenzimesh, kategoria max, etc
void shfaqTeTerePerdoruesit();      
#endif
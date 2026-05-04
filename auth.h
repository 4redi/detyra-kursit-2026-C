#ifndef AUTH_H
#define AUTH_H

#define LOGIN_FAIL 0
#define LOGIN_USER 1
#define LOGIN_ADMIN 2

int login(int *id_user, char username[]);
void regjistroPerdorues();

#endif
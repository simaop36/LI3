#ifndef OUTPUT_H
#define OUTPUT_H

#include "joint.h"

char *escreve_lista(char **elems);
void escreve_artista(gpointer key, gpointer value, gpointer user_data);
void escreve_musica(gpointer key, gpointer value, gpointer user_data);
void escreve_user(gpointer key, gpointer value, gpointer user_data);
int escreve_csv(const char *dir_path, Joint catalogo);


#endif
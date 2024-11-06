#ifndef OUTPUT_H
#define OUTPUT_H

char *escreve_lista(char **elems);
void escreve_artista(gpointer key, gpointer value, gpointer user_data);
void escreve_musica(gpointer key, gpointer value, gpointer user_data);
void escreve_user(gpointer key, gpointer value, gpointer user_data);

#endif
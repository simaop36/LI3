#ifndef HISTORICO_H
#define HISTORICO_H

#include <stdio.h>
#include <time.h>

typedef struct historico *Historico;


Historico create_Historico();
int verifica_historico(char **linha);

gpointer get_IDHistorico_gpointer(Historico h);
//int get_IDHistorico_int(Historico h);
char *get_IDHistorico_string(Historico h);

gpointer get_user_id_gpointer(Historico h);
int get_user_id_int(Historico h);
char *get_user_id_string(Historico h);

gpointer get_musica_id_gpointer(Historico h);
int get_musica_id_int(Historico h);
char *get_musica_id_string(Historico h);

char *get_Timestamp(Historico h);

size_t get_Duration(Historico h);

void setId_Historico(char *id, Historico h);
void set_UserId(char *user_id, Historico h);
void set_MusicId(char *music_id, Historico h);
void set_Timestamp(char *timestamp, Historico h);
void set_Duration(char *duration, Historico h);
void stringToUpper(char *str);

int verifica_plataform(char* plataform);
void free_historico(Historico novo_historico);


#endif
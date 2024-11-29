#ifndef HISTORICO_H
#define HISTORICO_H

typedef struct historico *Historico;
Historico create_Historico();
int verifica_historico(char **linha);
char *get_IDHistorico(Historico h);
char *get_UserId(Historico h);
char *get_MusicId(Historico h);
char *get_Timestamp(Historico h);
double get_Duration(Historico h);
char *get_Plataform(Historico h);
void setId_Historico(char *id, Historico h);
void set_UserId(char *user_id, Historico h);
void setId_MusicId(char *music_id, Historico h);
void set_Timestamp(char *timestamp, Historico h);
void set_Duration(long int duration, Historico h);
void set_Plataform(char *plataform, Historico h);
int verifica_plataform(char* plataform);


#endif
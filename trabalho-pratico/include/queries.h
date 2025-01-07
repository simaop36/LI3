#ifndef QUERIES_H
#define QUERIES_H

typedef struct generoContagem *generoContagem;

void excuta_queries(char *linha, int contador, Joint joint, Stats s);
char *excuta_queries_iterativo(int n_querie,int separador, char * linha, Joint joint, Stats s);
char *Q1(char *ID, Joint catalogo);
int compara_artistas(Artista a, Artista b);
char *Q3(int min, int max, Joint catalogo);
char *Q5(char *username, int num, Joint j, Stats s);

#endif
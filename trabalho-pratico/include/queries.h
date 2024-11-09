#ifndef QUERIES_H
#define QUERIES_H

typedef struct generoContagem *generoContagem;

void excuta_queries(char *linha,int contador,Joint joint);
char* Q1(char* ID,Joint catalogo);
int comparar_generos(gconstpointer a, gconstpointer b);
char *Q3(int min, int max, Joint catalogo);

#endif
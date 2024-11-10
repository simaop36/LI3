#ifndef ESTATISTICAS_H
#define ESTATISTICAS_H

#define NUM_GENEROS 10
#define MAX_AGE 60
#define MIN_AGE 17

typedef struct generoContagem *GeneroContagem;

char *getGenero(GeneroContagem gc);
int getLikes(GeneroContagem gc);
void setGenero(char *genero, GeneroContagem gc);
void setLikes(int like, GeneroContagem gc);
GeneroContagem build_genero_contagem(int i, char *g);
void free_genero_contagem(GeneroContagem g);
int comparar_generosC(GeneroContagem a, GeneroContagem b);
void troca_generosC(int i, int j, GeneroContagem *a);
GeneroContagem *build_Array_GC();
void incrementa_likes_genero(GeneroContagem *array, char *genero);
void incrementa_likes_array(GeneroContagem *a,GeneroContagem *b);
void free_Array_GC(GeneroContagem *array);


#endif
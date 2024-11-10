#include <stdio.h>
#include <stdlib.h>

#include "estatisticas.h"
#include "musica.h"
#include "users.h"


typedef struct generoContagem
{
    char *genero;
    int likes;
} *GeneroContagem;

char *getGenero(GeneroContagem gc){
    return gc->genero;
}
int getLikes(GeneroContagem gc){
    return gc->likes;
}

void setGenero(char *genero, GeneroContagem gc){
    char *gCopy = strdup(genero);
    gc->genero = gCopy;
}

void setLikes(int like, GeneroContagem gc){
    gc->likes = like;
}

GeneroContagem build_genero_contagem(int i, char *g){
    GeneroContagem gc = malloc(sizeof(struct generoContagem));
    char *gCopy = strdup(g);
    setGenero(gCopy,gc);
    setLikes(i,gc);
    return gc;
}

void free_genero_contagem(GeneroContagem g){
    if(g==NULL) return;
    free(g->genero);
    free(g);
}

int comparar_generosC(GeneroContagem a, GeneroContagem b)
{
    if (b->likes != a->likes)
    {
        return b->likes - a->likes; // ordem descendente por likes
    }
    return strcmp(a->genero, b->genero); // ordem alfabetica
}

void troca_generosC(int i, int j, GeneroContagem *a){
    GeneroContagem aux = a[i];
    a[i]=a[j];
    a[j]=aux;
}

char *lista_generos[NUM_GENEROS] = {
    "Blues", "Classical", "Country", "Electronic", "Hip Hop",
    "Jazz", "Metal", "Pop", "Reggae", "Rock"
};

GeneroContagem *build_Array_GC(){
    GeneroContagem *array = (GeneroContagem *)malloc(NUM_GENEROS * sizeof(GeneroContagem));

    for (int i = 0; i < NUM_GENEROS; i++) {
        array[i] = (GeneroContagem)malloc(sizeof(struct generoContagem));
        setGenero(lista_generos[i],array[i]);
        array[i]->likes = 0;
    }
    return array;
}

void incrementa_likes_genero(GeneroContagem *array, char *genero){
    for (int i = 0; i < NUM_GENEROS; i++){
        if(strcmp(array[i]->genero,genero)==0){
            array[i]->likes++;
        }
    }
}

void incrementa_likes_array(GeneroContagem *a,GeneroContagem *b){
    for (int i = 0; i < NUM_GENEROS; i++){
        for (int j = 0; j < NUM_GENEROS; j++){
            if(strcmp(a[i]->genero,b[j]->genero)==0){
                a[i]->likes+=b[j]->likes;
                break;
            }
        }
    }
}

void free_Array_GC(GeneroContagem *array){
    if(array == NULL) return;
    for (int i = 0; i < NUM_GENEROS; i++) {
        free_genero_contagem(array[i]);
    }
    free(array);
}









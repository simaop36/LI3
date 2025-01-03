#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <glib.h>

#include "estatisticas.h"
#include "musica.h"
#include "users.h"
#include "utils.h"
#include "historico.h"


typedef struct estatisticas
{
    int **matriz;
    char **idsUtilizadores;
    char **nomesGeneros;

} *Stats;


Stats create_estatisticas()
{
    Stats estatisticas = malloc(sizeof(struct estatisticas));
    estatisticas->matriz = NULL;
    estatisticas->idsUtilizadores = NULL;
    estatisticas->nomesGeneros = NULL;

    return estatisticas;
}

int **getMatriz(Stats s)
{
    return s->matriz;
}

char **get_ids_users(Stats s)
{
    return s->idsUtilizadores;
}
char **get_nome_Generos(Stats s)
{
    return s->nomesGeneros;
}

void build_stats(Stats s, GPtrArray *values_users)
{
    char **ids = malloc(values_users->len * sizeof(char *)); //aloca o espaço para os ponteiros

    GHashTable *tabela_generos = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, NULL);

    for (guint i = 0; i < values_users->len; i++){
        utilizador u = (utilizador)values_users->pdata[i];
        char *username = get_username_string(u);
        ids[i] = username;
        GArray *array_gc = getArray(u);
        if (array_gc->len == 0) continue;
        for(int j = 0; j < array_gc->len; j++){
            GeneroContagem gc = g_array_index(array_gc, GeneroContagem, j);
            char *genero = getGenero(gc);
            g_hash_table_add(tabela_generos,genero);
        }

    }
    GList *chaves = g_hash_table_get_keys(tabela_generos);
    guint n_generos = g_hash_table_size(tabela_generos);

    char **generos = malloc(n_generos * sizeof(char *));

    int index = 0;
    for (GList *l = chaves; l != NULL; l = l->next) {
        char *gen = (char *)l->data;
        generos[index] = strdup(gen);
        index++;

    }
    g_list_free(chaves);
    g_hash_table_destroy(tabela_generos);


    s->idsUtilizadores = ids;
    s->nomesGeneros = generos;

    if (s->matriz == NULL){
        s->matriz = malloc(values_users->len * sizeof(int));
        for (guint i = 0; i < values_users->len; i++){
            utilizador u = (utilizador)values_users->pdata[i];

            s->matriz[i] = malloc(index * sizeof(int));

            GArray *array_gc = getArray(u);
            if (array_gc->len == 0) continue;
            for(int j = 0; j < array_gc->len; j++){
                GeneroContagem gc = g_array_index(array_gc, GeneroContagem, j);
                int rep = (int)getReproducoes(gc);
                for(int k = 0; k < index; k++){
                    if (strcmp(generos[k], getGenero(gc)) == 0) {
                        s->matriz[i][k] = rep;
                        break;
                    }
                }
            }
        }
    }
}

void free_stats(Stats s)
{
    free_lista_strings(s->idsUtilizadores);
    free_lista_strings(s->nomesGeneros);
    free(s);
}


//___________________________________________________________________________

typedef struct generoContagem
{
    char *genero;
    int likes;
    size_t reproducoes;
} *GeneroContagem;

char *getGenero(GeneroContagem gc){
    return gc->genero;
}
int getLikes(GeneroContagem gc){
    return gc->likes;
}

size_t getReproducoes(GeneroContagem gc)
{
    return gc->reproducoes;
}

void setGenero(char *genero, GeneroContagem gc){
    char *gCopy = strdup(genero);
    gc->genero = gCopy;
}

void setLikes(int like, GeneroContagem gc){
    gc->likes = like;
}

void setReproducoes(size_t num, GeneroContagem gc)
{
    gc->reproducoes = num;
}

GeneroContagem build_genero_contagem(int i, char *g){
    GeneroContagem gc = malloc(sizeof(struct generoContagem));
    char *gCopy = strdup(g);
    setGenero(gCopy,gc);
    setLikes(i,gc);
    setReproducoes(0,gc);
    return gc;
}

void free_genero_contagem(GeneroContagem g){
    if(g==NULL) return;
    if(g->genero != NULL) free(g->genero);
    free(g);
}

gint comparar_generosC(GeneroContagem a, GeneroContagem b)
{
    if (b->likes != a->likes)
    {
        return b->likes - a->likes; // ordem descendente por likes
    }

    return strcmp(a->genero, b->genero); // ordem alfabetica
}

void swap_generos(GArray *arr, guint i, guint j) {
    GeneroContagem temp = g_array_index(arr, GeneroContagem, i);
    g_array_index(arr, GeneroContagem, i) = g_array_index(arr, GeneroContagem, j);
    g_array_index(arr, GeneroContagem, j) = temp;
}


GArray *build_Array_GC(){
    GArray *array = g_array_new(FALSE, FALSE, sizeof(GeneroContagem));
    return array;
}


void incrementa_likes_genero(GArray *array, char *genero){
    for (guint i = 0; i < array->len; i++) {
        GeneroContagem gc = g_array_index(array, GeneroContagem, i);

        if(gc->genero == NULL) {
            gc->genero = strdup(genero);
        }
        if(genero == NULL){
            return;
        }

        if (strcmp(gc->genero, genero) == 0) {
            gc->likes++;
            return;
        }
    }
    // nao encontrou o género
    GeneroContagem new = malloc(sizeof(struct generoContagem));
    new->genero = strdup(genero);
    new->likes = 1;
    new->reproducoes = 0;

    g_array_append_val(array, new);

}

void incrementa_likes_array(GArray *array_a, GArray *array_b){
    for (guint i = 0; i < array_b->len; i++){
        GeneroContagem gc_b = g_array_index(array_b, GeneroContagem, i);

        

        // Se o genero for NULL, nem faz sentido continuar
        if (gc_b->genero == NULL) {
            break;
        }

        gboolean found = FALSE;  // flag pra saber se achou

        // Procura no array_a
        for (guint j = 0; j < array_a->len; j++){
            GeneroContagem gc_a = g_array_index(array_a, GeneroContagem, j);


            // Se o genero desse gc_a ainda é NULL, 
            // inicializamos com o do gc_b e incrementamos 
            // (outra lógica possível)
            if(gc_a->genero == NULL) {
                gc_a->genero = strdup(gc_b->genero);
                gc_a->likes = gc_b->likes;
                found = TRUE;
                break;
            }

            // Se bateu
            if(strcmp(gc_a->genero, gc_b->genero) == 0){
                gc_a->likes += gc_b->likes;
                found = TRUE;
                break;
            }
        }

        // Se terminou o loop e nao encontrou, cria
        if(!found) {
            //printf("%s\n",gc_b->genero);
            GeneroContagem newg = malloc(sizeof(struct generoContagem));
            newg->genero = strdup(gc_b->genero);
            newg->likes = gc_b->likes; // soma total
            newg->reproducoes = 0;

            g_array_append_val(array_a, newg);
        }
    }
}




void incrementa_reproducoes_array(GArray *array, char *genero)
{
    for (guint i = 0; i < array->len; i++) {
        GeneroContagem gc = g_array_index(array, GeneroContagem, i);

        if(gc->genero == NULL) {
            gc->genero = strdup(genero);
        }

        if (strcmp(gc->genero, genero) == 0) {
            gc->reproducoes++;
            return;
        }
    }

    // nao encontrou o género
    GeneroContagem new = malloc(sizeof(struct generoContagem));
    new->genero = strdup(genero);
    new->likes = 0;
    new->reproducoes = 1;

    g_array_append_val(array, new);

    g_array_sort(array, compare_strings);
}

void free_Array_GC(GArray *array){
    if(array == NULL) return;
    for (guint i = 0; i < array->len; i++){
        GeneroContagem gc = g_array_index(array, GeneroContagem, i);
        free_genero_contagem(gc);
    }
    g_array_free(array,TRUE);
}









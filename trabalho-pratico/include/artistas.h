#ifndef ARTISTAS_H
#define ARTISTAS_H

#include "catalogo_artista.h"
#include <glib.h>
#include <stdio.h>
#include <limits.h>

typedef struct artista *Artista;



Artista create_Artista();
int verifica_artistas(char **linha);
gpointer *getId_Artista(Artista a);
//int getId_Artista_int(Artista a);
char *getId_Artista_String(Artista a);

char *getName(Artista a);
double getRecipe_Per_Stream(Artista a);
gpointer *getId_Constituent(Artista a);
char *getCountry(Artista a);
char *getType(Artista a);
double getDiscography_Duration(Artista a);
size_t getNum_albums_indiv(Artista a);
double get_total_recipe(Artista a);
size_t getPlays(Artista a);
void setId_Artista(char *id, Artista a);
void setName(char *name, Artista a);
void setRecipe_Per_Stream(double recipe_per_stream, Artista a);
void setId_Constituent(char *id_constituent, Artista a);
void setCountry(char *country, Artista a);
void setType(char *type, Artista a);
void setDiscography_Duration(size_t disc_Duration, Artista a);
void increaseDiscography_Duration(size_t disc_Duration, Artista a);
void setNum_albums_indiv(size_t num, Artista a);
void increaseNum_albums_indiv(size_t num, Artista a);
void setTotal_recipe(double num, Artista a);
void increaseTotal_recipe(double num, Artista a);
void setPlays(size_t num, Artista a);
void increase_plays(size_t num, Artista a);

void free_artista(Artista novo_artista);


#endif
#include "artistas.h"
#include <glib.h>

typedef struct artista {
    char *id;
    char *name;
    char *description;
    double recipe_per_stream;
    char **id_constituent;
    char *country;
    char *type;
} Artista;

char* getId(Artista* a){
    char* aCopy = strdup(a->id);
    return aCopy;
}
char* getName(Artista* a){
    char* aCopy = strdup(a->name);
    return aCopy;
}
char* getDescription(Artista* a){
    char* aCopy = strdup(a->description);
    return aCopy;
}
double getRecipe_Per_Stream(Artista* a){
    return a->recipe_per_stream;
}
char** getId_Constituent(Artista* a){
    char** aCopy = g_strdupv(a->id_constituent);
    return aCopy;
}

char* getCountry(Artista* a){
    char* aCopy = strdup(a->country);
    return aCopy;
}
char* getType(Artista* a){
    char* aCopy = strdup(a->type);
    return aCopy;
}

void setId(char* id,Artista* a){
    char* copy = strdup(id);
    a->id = copy;
}
void setName(char* name,Artista* a){
    char* copy = strdup(name);
    a->name = copy;
}
void setDescription(char* description,Artista* a){
    char* copy = strdup(description);
    a->description = copy;
}
void setRecipe_Per_Stream(double recipe_per_stream,Artista* a){
    a->recipe_per_stream = recipe_per_stream;
}
void setId_Constituent(char** id_constituent,Artista* a){
    char** copy = g_strdupv(id_constituent);
    a->id_constituent = copy;
}
void setCountry(char* country,Artista* a){
    char* copy = strdup(country);
    a->country = copy;
}
void setType(char* type,Artista* a){
    char* copy = strdup(type);
    a->type = copy;
}

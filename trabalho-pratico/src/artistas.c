#include "artistas.h"

typedef struct artista {
    char *id;
    char *name;
    char *description;
    double recipe_per_stream;
    char **id_constituent;
    char *country;
    char *type;
} artista;
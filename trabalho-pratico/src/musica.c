#include "musicas.h"

typedef struct musica
{
    char *id;
    char *title;
    char **id_artista;
    char *duration;
    char *genre;
    char *year;
    char *lyrics;
} musica;
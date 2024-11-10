#include <stdio.h>
#include <stdlib.h>

#include "estatisticas.h"
#include "musica.h"
#include "users.h"


typedef struct generoContagem
{
    char *genero;
    int likes;
} *generoContagem;

const char *lista_generos[NUM_GENEROS] = {
    "Pop", "Rock", "Jazz", "Classical", "Hip-Hop",
    "Electronic", "Country", "Reggae", "Blues", "Metal"
};

typedef struct idadeGeneros {
    int idade;
    generoContagem *generos;  // Array com 10 géneros
} *IdadeGeneros;





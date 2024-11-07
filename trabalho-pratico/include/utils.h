#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>
#include "utils.h"
#include "catalogo_musica.h"
#include "catalogo_users.h"
#include "users.h"
#include "catalogo_artista.h"
#include "joint.h"

typedef struct musica *musica;
typedef struct utilizador *utilizador;
typedef struct catalogo_artistas *Catalogo_Artistas;
typedef struct Catalogo_Musicas *Catalogo_Musicas;
typedef struct catalogo_utilizadores *catalogo_utilizadores;
typedef struct joint *Joint;

int valida_data(const char *data);
int valida_duracao(const char *duracao);
int valida_email(const char *email);
int valida_tipo(const char *tipo);
int valida_tipo_user(const char *tipo);
int valida_tipo_artista(const char *tipo, const char *id_Constituent);
int valida_lista(const char *str);
char **parse_lista(char *input);
//void aux_valida_liked_music(utilizador u, Joint catalogo);
bool possui_musica_valida(utilizador utilizador, GHashTable *artistas_validos);
void mover_utilizadores_invalidos(GHashTable *utilizadores_validos, GHashTable *utilizadores_invalidos, GHashTable *artistas_validos);
void valida_artistasDamusica(musica m, Joint catalogo);
void free_lista_strings(char **array);

#endif
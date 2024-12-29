#ifndef JOINT_H
#define JOINT_H

#include "catalogo_artista.h"
#include "catalogo_musica.h"
#include "catalogo_users.h"
#include "catalogo_albuns.h"
#include "catalogo_historico.h"


typedef struct joint *Joint;


Joint create_catalago_joint();


catalogo_utilizadores get_catalogo_utilizadores(Joint j);

Catalogo_Musicas get_catalogo_musicas(Joint j);

Catalogo_Artistas get_catalogo_artistas(Joint j);

Catalogo_Albuns get_catalogo_albuns(Joint j);

Catalogo_Historico get_catalogo_historico(Joint j);

void free_joint(Joint j);

#endif
#ifndef JOINT_H
#define JOINT_H

#include "catalogo_artista.h"
#include "catalogo_musica.h"
#include "catalogo_users.h"

typedef struct joint *Joint;

Joint create_catalago_joint(catalogo_utilizadores users,
                            Catalogo_Artistas artistas,
                            Catalogo_Musicas musicas);

catalogo_utilizadores get_catalogo_utilizadores(Joint j);

Catalogo_Musicas get_catalogo_musicas(Joint j);

Catalogo_Artistas get_catalogo_artistas(Joint j);

void free_joint(Joint j);

#endif
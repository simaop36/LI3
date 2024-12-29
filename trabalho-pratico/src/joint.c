#include "joint.h"

#include "catalogo_artista.h"
#include "catalogo_musica.h"
#include "catalogo_users.h"
#include "catalogo_albuns.h"
#include "catalogo_historico.h"
#include "estatisticas.h"


typedef struct joint
{
    Catalogo_Artistas artista_c;
    catalogo_utilizadores users_c;
    Catalogo_Musicas musicas_c;
    Catalogo_Albuns albuns_c;
    Catalogo_Historico historico_c;
} *Joint;


Joint create_catalago_joint()
{
    Catalogo_Artistas artistas = create_catalogo_artistas();
    Catalogo_Musicas musicas = create_Catalogo_Musicas();
    catalogo_utilizadores users = create_catalogo_utilizadores();
    Catalogo_Albuns albuns = create_catalogo_albuns();
    Catalogo_Historico historico = create_catalogo_historico();
    
    Joint new_joint = malloc(sizeof(struct joint));


    new_joint->artista_c = artistas;
    new_joint->musicas_c = musicas;
    new_joint->users_c = users;
    new_joint->albuns_c = albuns;
    new_joint->historico_c = historico;

    return new_joint;
}

catalogo_utilizadores get_catalogo_utilizadores(Joint j)
{
    return j->users_c;
}

Catalogo_Musicas get_catalogo_musicas(Joint j)
{
    return j->musicas_c;
}

Catalogo_Artistas get_catalogo_artistas(Joint j)
{
    return j->artista_c;
}

Catalogo_Albuns get_catalogo_albuns(Joint j)
{
    return j->albuns_c;
}

Catalogo_Historico get_catalogo_historico(Joint j)
{
    return j->historico_c;
}

void free_joint(Joint j)
{
    if (j->users_c)
       free_catalogo_utilizadores(j->users_c);
    if (j->artista_c)
        free_catalogo_artistas(j->artista_c);
    if (j->musicas_c)
        free_Catalogo_Musicas(j->musicas_c);
    if (j->albuns_c)
        free_catalogo_albuns(j->albuns_c);
    if(j->historico_c)
        free_catalogo_historico(j->historico_c);

    free(j);
}
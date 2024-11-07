#include "joint.h"

#include "catalogo_artista.h"
#include "catalogo_musica.h"
#include "catalogo_users.h"
#include "musica.h"
#include "users.h"
#include "utils.h"


typedef struct joint
{
    Catalogo_Artistas artista_c;
    catalogo_utilizadores users_c;
    Catalogo_Musicas musicas_c;
} *Joint;


Joint create_catalago_joint()
{
    Catalogo_Artistas artistas = create_catalogo_artistas();
    Catalogo_Musicas musicas = create_Catalogo_Musicas();
    catalogo_utilizadores users = create_catalogo_utilizadores();
    
    Joint new_joint = malloc(sizeof(struct joint));


    new_joint->artista_c = artistas;
    new_joint->musicas_c = musicas;
    new_joint->users_c = users;

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
/*
void aux_user(gpointer key, gpointer value, gpointer user_data){
    utilizador u = (utilizador)value;
    Joint catalogo = (Joint)user_data;
    aux_valida_liked_music(u,catalogo);
}
*/
void aux_musica(gpointer key, gpointer value, gpointer user_data){
    musica m = (musica)value;
    Joint cat = (Joint)user_data;
    valida_artistasDamusica(m,cat);
}

void segunda_verificação(Joint catalogo){

    Catalogo_Musicas catalogo_musica = get_catalogo_musicas(catalogo);
    GHashTable *musicas_validas = getMusicasValidas(catalogo_musica);
    GHashTable *musicas_invalidas = getMusicasInvalidas(catalogo_musica);
    //g_hash_table_foreach(musicas_validas, aux_musica, catalogo);

    catalogo_utilizadores catalogo_users = get_catalogo_utilizadores(catalogo);
    GHashTable *users_validos = getUtilizadoresValidos(catalogo_users);
    GHashTable *users_invalidos = getUtilizadoresInvalidos(catalogo_users);


    Catalogo_Artistas catalogo_art = get_catalogo_artistas(catalogo);
    GHashTable *art_validos = getArtistasValidos(catalogo_art);

    mover_musicas_invalidos(musicas_validas,musicas_invalidas,art_validos);
    mover_utilizadores_invalidos(users_validos,users_invalidos,musicas_validas);
    //g_hash_table_foreach(users_validos, aux_user, catalogo);

}

void free_joint(Joint j)
{
    if (j->users_c)
       free_catalogo_utilizadores(j->users_c);
    if (j->artista_c)
        free_catalogo_artistas(j->artista_c);
    if (j->musicas_c)
        free_Catalogo_Musicas(j->musicas_c);

    free(j);
}
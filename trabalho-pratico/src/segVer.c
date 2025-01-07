#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <dirent.h>
#include <glib.h>

#include "segVer.h"
#include "utils.h"
#include "catalogo_musica.h"
#include "catalogo_users.h"
#include "catalogo_artista.h"
#include "catalogo_albuns.h"
#include "joint.h"
#include "users.h"
#include "musica.h"


// return 0 : Inválido
// return 1 : Válido

int segVerMusica(musica m, Joint joint)
{
    Catalogo_Artistas cat_artistas = get_catalogo_artistas(joint);
    Catalogo_Albuns cat_album = get_catalogo_albuns(joint);
    gpointer *artistas_id = getId_Artistas_gpointer(m);
    gpointer album_id = getAlbum_id_gpointer(m);
    int result = 1;
    char *duration_char = getDuration(m);
    long int duration_int = converteDuration(duration_char);


    if (artistas_id == NULL)
    {
        free(duration_char);
        return 0;
    }

    if (album_id == NULL)
    {
        free(duration_char);
        return 0;
    }

    Album album = get_album_valido(cat_album,album_id);
    if (album == NULL)
    {
        free(duration_char);
        return 0;
    }

    for (int i = 0; artistas_id[i] != NULL; i++)
    {
        Artista artista = get_artista_valido(cat_artistas, artistas_id[i]);
        if (artista != NULL)
        { // existe
            
            increaseDiscography_Duration(duration_int, artista);
        }
        else
        { // nao existe
            result = 0;
        }

    }
    free(duration_char);
    return result;
}

int segVerUser(utilizador utilizador, Joint joint)
{
    Catalogo_Musicas cat_musicas = get_catalogo_musicas(joint);
    gpointer *liked_musics = get_liked_musics_id(utilizador);
    int result = 1;

    if (liked_musics == NULL)
        return 0;
    for (int i = 0; liked_musics[i] != NULL; i++)
    {
        musica m = get_musica_valida(cat_musicas, liked_musics[i]);
        if (m != NULL)
        { // existe
            char *genero = getGenre(m);
            incrementa_likes_genero(getArray(utilizador), genero);
            free(genero);
        }
        else
        { // nao existe
            result = 0;
        }
    }
    return result;
}


void segVerAlbum(Album a,Joint j)
{
    Catalogo_Artistas cat_artistas = get_catalogo_artistas(j);
    gpointer *artistas = getArtists_id(a);
    for(int i = 0; artistas[i] != NULL; i++)
    {
        Artista art = get_artista_valido(cat_artistas,artistas[i]);
        if (art == NULL) return;
        char *type = getType(art);
        increaseNum_albums_indiv(1,art);

        free(type);
    }
}

void segVerHistory(Historico h, Joint j)
{
    Catalogo_Musicas cat_musicas = get_catalogo_musicas(j);
    Catalogo_Artistas cat_artistas = get_catalogo_artistas(j);
    catalogo_utilizadores cat_users = get_catalogo_utilizadores(j);

    gpointer music_id = get_musica_id_gpointer(h);
    musica m = get_musica_valida(cat_musicas,music_id);

    gpointer *artistas_id = getId_Artistas_gpointer(m);

    for(int i = 0; artistas_id[i] != NULL; i++)
    {
        Artista a = get_artista_valido(cat_artistas,artistas_id[i]);
        increase_plays(1,a);
    }

    char *genero = getGenre(m);
    gpointer user_id = get_user_id_gpointer(h);
    utilizador u = get_utilizador_valido(cat_users,user_id);
    GArray *gc = getArray(u);
    incrementa_reproducoes_array(gc,genero);
    free(genero);


}


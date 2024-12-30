#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#include "input.h"
#include "joint.h"
#include "parser.h"
#include "catalogo_artista.h"
#include "catalogo_musica.h"
#include "catalogo_users.h"
#include "catalogo_albuns.h"
#include "catalogo_historico.h"

void ler_csvs(const char *dir_path, Joint joint)
{
    // CSV esperados
    const char *file_Names[] = {"albums.csv","artists.csv", "musics.csv", "users.csv","history.csv"};

    //___________________________________ALBUM___________________________________________

    char filename_album[256]; // Buffer para armazenar o caminho completo

    // junta o path com o file_Name
    snprintf(filename_album, sizeof(filename_album), "%s/%s", dir_path, file_Names[0]);

    // Abre o arquivo CSV em modo leitura
    FILE *file_album = fopen(filename_album, "r");
    if (file_album == NULL)
    {
        fprintf(stderr, "Erro ao abrir o arquivo: %s\n", filename_album);
    }

    file_parser(file_album, get_catalogo_albuns(joint), build_Album, MAX_ALBUM_TOKENS);
    build_values_albuns(get_catalogo_albuns(joint));
    fclose(file_album);


    //__________________________________ARTISTAS_________________________________________

    char filename_artista[256]; // Buffer para armazenar o caminho completo

    // junta o path com o file_Name
    snprintf(filename_artista, sizeof(filename_artista), "%s/%s", dir_path, file_Names[1]);

    // Abre o arquivo CSV em modo leitura
    FILE *file_artista = fopen(filename_artista, "r");
    if (file_artista == NULL)
    {
        fprintf(stderr, "Erro ao abrir o arquivo: %s\n", filename_artista);
    }

    file_parser(file_artista, get_catalogo_artistas(joint), build_Artista, MAX_ARTISTA_TOKENS);
    build_values_artistas(get_catalogo_artistas(joint));
    fclose(file_artista);

    //___________________________________MUSICS__________________________________________

    char filename_musics[256];
    snprintf(filename_musics, sizeof(filename_musics), "%s/%s", dir_path, file_Names[2]);
    FILE *file_musics = fopen(filename_musics, "r");
    if (file_musics == NULL)
    {
        fprintf(stderr, "Erro ao abrir o arquivo: %s\n", filename_musics);
    }
    file_parser(file_musics, joint, build_musica, MAX_MUSIC_TOKENS);
    build_values_musicas(get_catalogo_musicas(joint));
    fclose(file_musics);

    //____________________________________USERS__________________________________________

    char filename_users[256];
    snprintf(filename_users, sizeof(filename_users), "%s/%s", dir_path, file_Names[3]);
    FILE *file_users = fopen(filename_users, "r");
    if (file_users == NULL)
    {
        fprintf(stderr, "Erro ao abrir o arquivo: %s\n", filename_users);
    }
    file_parser(file_users, joint, build_utilizador, MAX_USERS_TOKENS);
    build_values_users(get_catalogo_utilizadores(joint));
    fclose(file_users);

    //__________________________________HISTORICO________________________________________

    char filename_history[256];
    snprintf(filename_history, sizeof(filename_history), "%s/%s", dir_path, file_Names[4]);
    FILE *file_history = fopen(filename_history, "r");
    if (file_history == NULL)
    {
        fprintf(stderr, "Erro ao abrir o arquivo: %s\n", filename_history);
    }
    file_parser(file_history, get_catalogo_historico(joint), build_Historico, MAX_HISTORICO_TOKENS);
    build_values_history(get_catalogo_historico(joint));
    fclose(file_history);


}

char *ler_queries(const char *file_path, Joint joint)
{
    FILE *queries_file = fopen(file_path, "r");
    if (queries_file == NULL)
    {
        fprintf(stderr, "Erro ao abrir o ficheiro: %s\n", file_path);
        return NULL;
    }
    char *resultado = parse_queries(queries_file, joint);
    fclose(queries_file);
    return resultado;
}

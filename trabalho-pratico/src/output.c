#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>

#include "output.h"
#include "joint.h"
#include "catalogo_artista.h"
#include "catalogo_musica.h"
#include "catalogo_users.h"
#include "artistas.h"
#include "musica.h"
#include "users.h"


char *escreve_lista(char **elems, int tipo) {
    // tipo 0 = artistas;
    // tipo 1 = musica;
    // tipo 2 = user;

    // Verifica o número de elementos até NULL
    int num_elems = 0;
    while (elems[num_elems] != NULL) {
        num_elems++;
    }

    // Caso especial: se há apenas um elemento e o tipo é user (tipo == 2), retorna o elemento diretamente
    if (num_elems == 1 && tipo == 2) {
        char *single_elem = strdup(elems[0]); // copia o único elemento para evitar vazamento
        free(elems[0]);
        free(elems);
        return single_elem;
    }

    // Se a lista estiver vazia, retorna "[]"
    if (num_elems == 0) {
        char *resultado_vazio = malloc(3 * sizeof(char));
        if (resultado_vazio == NULL) {
            perror("Erro ao alocar memória");
            return NULL;
        }
        strcpy(resultado_vazio, "[]");
        free(elems);
        return resultado_vazio;
    }

    // Calcula o tamanho total necessário para a string final
    int tamanho_total = 2; // para os colchetes []

    if (tipo != 3) {
        for (int i = 0; i < num_elems; i++) {
            tamanho_total += strlen(elems[i]) + 3; // 3 caracteres para aspas e vírgula
        }
        tamanho_total -= 1; // Remove o último caractere extra de vírgula
    } else {
        for (int i = 0; i < num_elems; i++) {
            tamanho_total += strlen(elems[i]) + 4; // 4 caracteres para aspas, vírgula e espaço
        }
        tamanho_total -= 2; // Remove os últimos dois caracteres ", "
    }

    // Aloca memória para a string resultante
    char *resultado = malloc((tamanho_total + 1) * sizeof(char));
    if (resultado == NULL) {
        perror("Erro ao alocar memória");
        free(elems);
        return NULL;
    }

    // Preenche a string com o formato desejado
    strcpy(resultado, "[");
    for (int i = 0; i < num_elems; i++) {
        strcat(resultado, "'");
        strcat(resultado, elems[i]);
        strcat(resultado, "'");
        if (i < num_elems - 1) {
            strcat(resultado, ",");
            if (tipo == 3) {
                strcat(resultado, " ");
            }
        }
        free(elems[i]);
    }

    free(elems); // Libera o array de ponteiros após o uso
    strcat(resultado, "]");

    return resultado;
}


void escreve_artista(gpointer key, gpointer value, gpointer user_data)
{
    FILE *file = (FILE *)user_data;
    Artista artista = (Artista)value;

    char *id = getId_Artista(artista);
    char *name = getName(artista);
    char *description = getDescription(artista);
    char *id_constituent = escreve_lista(getId_Constituent(artista), 1);
    char *country = getCountry(artista);
    char *type = getType(artista);

    fprintf(file, "\"%s\";\"%s\";\"%s\";\"%.2f\";\"%s\";\"%s\";\"%s\"\n",
            id,
            name,
            description,
            getRecipe_Per_Stream(artista),
            id_constituent,
            country,
            type);

    free(id);
    free(name);
    free(description);
    free(id_constituent);
    free(country);
    free(type);
}

void escreve_musica(gpointer key, gpointer value, gpointer user_data)
{
    FILE *file = (FILE *)user_data;
    musica m = (musica)value;

    char *id = getId_Musica(m);
    char *title = getTitle(m);
    char *artists = escreve_lista(getId_Artistas(m), 2);
    char *duration = getDuration(m);
    char *genre = getGenre(m);
    char *year = getYear(m);
    char *lyrics = getLyrics(m);

    fprintf(file, "\"%s\";\"%s\";\"%s\";\"%s\";\"%s\";\"%s\";\"%s\"\n",
            id,
            title,
            artists,
            duration,
            genre,
            year,
            lyrics);

    free(id);
    free(title);
    free(artists);
    free(duration);
    free(genre);
    free(year);
    free(lyrics);
}

void escreve_user(gpointer key, gpointer value, gpointer user_data)
{
    FILE *file = (FILE *)user_data;
    utilizador u = (utilizador)value;

    char *username = get_username(u);
    char *email = get_email(u);
    char *first_name = get_first_name(u);
    char *last_name = get_last_name(u);
    char *birth_date = get_birth_date(u);
    char *country = get_country(u);
    char *subscription_style = get_subscription_style(u);
    char *liked_musics = escreve_lista(get_liked_musics_id(u), 3);

    fprintf(file, "\"%s\";\"%s\";\"%s\";\"%s\";\"%s\";\"%s\";\"%s\";\"%s\"\n",
            username,
            email,
            first_name,
            last_name,
            birth_date,
            country,
            subscription_style,
            liked_musics);

    free(username);
    free(email);
    free(first_name);
    free(last_name);
    free(birth_date);
    free(country);
    free(subscription_style);
    free(liked_musics);
}

int escreve_csv(const char *dir_path, Joint catalogo)
{
    const char *file_Names[] = {"/artists_errors.csv", "/musics_errors.csv", "/users_errors.csv"};
    const char *headers[] = {
        "\"id\";\"name\";\"description\";\"recipe_per_stream\";\"id_constituent\";\"country\";\"type\"",                            // artists
        "\"id\";\"title\";\"artist_id\";\"duration\";\"genre\";\"year\";\"lyrics\"",                                                // musics
        "\"username\";\"email\";\"first_name\";\"last_name\";\"birth_date\";\"country\";\"subscription_type\";\"liked_songs_id\""}; // users};

    char *artists_errors = malloc(strlen(dir_path) + strlen(file_Names[0]) + 1);
    strcpy(artists_errors, dir_path);
    strcat(artists_errors, file_Names[0]);

    Catalogo_Artistas catalogo_artistas = get_catalogo_artistas(catalogo);
    GHashTable *artistas_invalidos = getArtistasInvalidos(catalogo_artistas);

    if (g_hash_table_size(artistas_invalidos) == 0)
    {
        free(artists_errors);
        return -1;
    }

    // Abre o ficheiro para escrita
    FILE *file_artists = fopen(artists_errors, "w");
    free(artists_errors); // Liberta a memória alocada para o caminho do ficheiro
    if (file_artists == NULL)
    {
        perror("Erro ao abrir ficheiro artists_errors.csv");
        return -1;
    }

    fprintf(file_artists, "%s\n", headers[0]);

    g_hash_table_foreach(artistas_invalidos, escreve_artista, file_artists);

    fclose(file_artists);

    // musicas

    char *musics_errors = malloc(strlen(dir_path) + strlen(file_Names[1]) + 1);
    strcpy(musics_errors, dir_path);
    strcat(musics_errors, file_Names[1]);

    Catalogo_Musicas catalogo_musica = get_catalogo_musicas(catalogo);
    GHashTable *musicas_invalidas = getMusicasInvalidas(catalogo_musica);
    if (g_hash_table_size(musicas_invalidas) == 0)
    {
        free(musics_errors);
        return -1;
    }

    FILE *file_musics = fopen(musics_errors, "w");
    free(musics_errors);
    if (file_musics == NULL)
    {
        perror("Erro ao abrir ficheiro musics_errors.csv");
        return -1;
    }

    fprintf(file_musics, "%s\n", headers[1]);

    g_hash_table_foreach(musicas_invalidas, escreve_musica, file_musics);

    fclose(file_musics);

    // users

    char *users_errors = malloc(strlen(dir_path) + strlen(file_Names[2]) + 1);
    strcpy(users_errors, dir_path);
    strcat(users_errors, file_Names[2]);

    catalogo_utilizadores catalogo_users = get_catalogo_utilizadores(catalogo);
    GHashTable *users_invalidos = getUtilizadoresInvalidos(catalogo_users);
    if (g_hash_table_size(users_invalidos) == 0)
    {
        free(users_errors);
        return -1;
    }

    FILE *file_users = fopen(users_errors, "w");
    free(users_errors);
    if (file_users == NULL)
    {
        perror("Erro ao abrir ficheiro users_errors.csv");
        return -1;
    }

    fprintf(file_users, "%s\n", headers[2]);

    g_hash_table_foreach(users_invalidos, escreve_user, file_users);

    fclose(file_users);

    return 1;
}

void escreve_querie(char *resultado,int contador){
    const char *dir = "./resultados";
    char filename[100];//nao é necessario free
    sprintf(filename, "%s/command%d_output.txt", dir, contador);

    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Erro ao abrir o ficheiro queries");
        exit(1);
    }

    if (fputs(resultado, file) == EOF) {
        perror("Erro ao escrever no ficheiro queries");
        fclose(file);
        exit(1);
    }
    /*
    if (fputc('\n', file) == EOF) {
        perror("Erro ao escrever /n no ficheiro queries");
        fclose(file);
        exit(1);
    }
    */
    fclose(file);
}

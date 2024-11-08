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


char *escreve_lista(char **elems) {
    // Verifica o número de elementos até NULL
    int num_elems = 0;
    while (elems[num_elems] != NULL) {
        num_elems++;
    }

    // Se a lista estiver vazia (apenas NULL), retorna "[]"
    if (num_elems == 0) {
        char *resultado_vazio = malloc(3 * sizeof(char));
        if (resultado_vazio == NULL) {
            perror("Erro ao alocar memória");
            return NULL;
        }
        strcpy(resultado_vazio, "[]");
        return resultado_vazio;
    }

    // Calcula o tamanho total necessário para a string final
    int tamanho_total = 2; // para []
    for (int i = 0; i < num_elems; i++) {
        tamanho_total += strlen(elems[i]) + 3; // 3 caracteres extras para as aspas e a vírgula
    }
    tamanho_total -= 1; // Remove um caractere para evitar a última vírgula extra

    // Aloca memória para a string resultante
    char *resultado = malloc((tamanho_total + 1) * sizeof(char));
    if (resultado == NULL) {
        perror("Erro ao alocar memória");
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
        }
        free(elems[i]);
    }
    free(elems);
    strcat(resultado, "]");


    return resultado;
}

void escreve_artista(gpointer key, gpointer value, gpointer user_data) {
    FILE *file = (FILE *)user_data;
    Artista artista = (Artista)value;

    char *id = getId_Artista(artista);
    char *name = getName(artista);
    char *description = getDescription(artista);
    char *recipe_per_stream = escreve_lista(getId_Constituent(artista));
    char *country = getCountry(artista);
    char *type = getType(artista);

    fprintf(file, "\"%s\";\"%s\";\"%s\";\"%.2f\";\"%s\";\"%s\";\"%s\"\n",
            id,
            name,
            description,
            getRecipe_Per_Stream(artista),
            recipe_per_stream,
            country,
            type);

    free(id);
    free(name);
    free(description);
    free(recipe_per_stream);
    free(country);
    free(type);
}

void escreve_musica(gpointer key, gpointer value, gpointer user_data) {
    FILE *file = (FILE *)user_data;
    musica m = (musica)value;

    char *id = getId_Musica(m);
    char *title = getTitle(m);
    char *artists = escreve_lista(getId_Artistas(m));
    char *duration = getDuration(m);
    char *genre = getGenre(m);
    char *year = getYear(m);
    char *lyrics = getLyrics(m);

    fprintf(file, "\"%s\";\"%s\";\"%s\";\"%s\";\"%s\";\"%s\";\"%s\";\"%s\"\n",
            id,
            title,
            //artists,
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

void escreve_user(gpointer key, gpointer value, gpointer user_data) {
    FILE *file = (FILE *)user_data;
    utilizador u = (utilizador)value;

    char *username = get_username(u);
    char *email = get_email(u);
    char *first_name = get_first_name(u);
    char *last_name = get_last_name(u);
    char *birth_date = get_birth_date(u);
    char *country = get_country(u);
    char *subscription_style = get_subscription_style(u);
    char *liked_musics = escreve_lista(get_liked_musics_id(u));

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

int escreve_csv(const char *dir_path, Joint catalogo) {
    const char *file_Names[] = {"/artists_errors.csv", "/musics_errors.csv", "/users_errors.csv"};
    const char *headers[] = {
    "\"id\";\"name\";\"description\";\"recipe_per_stream\";\"id_constituent\";\"country\";\"type\"", // artists
    "\"id\";\"title\";\"artist_id\";\"duration\";\"genre\";\"year\";\"lyrics\"", // musics
    "\"username\";\"email\";\"first_name\";\"last_name\";\"birth_date\";\"country\";\"subscription_type\";\"liked_songs_id\""}; // users};


    char *artists_errors = malloc(strlen(dir_path) + strlen(file_Names[0]) + 1);
    strcpy(artists_errors, dir_path);
    strcat(artists_errors, file_Names[0]);

    //verificação de erros:
    Catalogo_Artistas catalogo_artistas = get_catalogo_artistas(catalogo);
    GHashTable *artistas_validas = getArtistasValidos(catalogo_artistas);
    printf("\n\n Depois da segunda verificação: \n\n");
    printf("Tamanho da tabela hash dos artistas validos: %u\n", g_hash_table_size(artistas_validas));
    GHashTable *artistas_invalidas = getArtistasInvalidos(catalogo_artistas);
    printf("Tamanho da tabela hash dos artistas invalidas: %u\n", g_hash_table_size(artistas_invalidas));

    Catalogo_Musicas catalogo_musica = get_catalogo_musicas(catalogo);
    GHashTable *musicas_validas = getMusicasValidas(catalogo_musica);
    printf("Tamanho da tabela hash das musicas validas: %u\n", g_hash_table_size(musicas_validas));
    GHashTable *musicas_invalidas = getMusicasInvalidas(catalogo_musica);
    printf("Tamanho da tabela hash das musicas invalidas: %u\n", g_hash_table_size(musicas_invalidas));

    catalogo_utilizadores catalogo_utilizadores = get_catalogo_utilizadores(catalogo);
    GHashTable *users_validas = getUtilizadoresValidos(catalogo_utilizadores);
    printf("Tamanho da tabela hash dos users validos: %u\n", g_hash_table_size(users_validas));
    GHashTable *users_invalidas = getUtilizadoresInvalidos(catalogo_utilizadores);
    printf("Tamanho da tabela hash dos users invalidos: %u\n", g_hash_table_size(users_invalidas));

    // Abre o ficheiro para escrita
    FILE *file_artists = fopen(artists_errors, "w");
    free(artists_errors); // Liberta a memória alocada para o caminho do ficheiro
    if (file_artists == NULL) {
        perror("Erro ao abrir ficheiro artists_errors.csv");
        return -1;
    }
    fprintf(file_artists, "%s\n", headers[0]);

    //Catalogo_Artistas catalogo_artistas = get_catalogo_artistas(catalogo);
    GHashTable *artistas_invalidos = getArtistasInvalidos(catalogo_artistas);
    g_hash_table_foreach(artistas_invalidos, escreve_artista, file_artists);

    fclose(file_artists);


    //musicas

    char *musics_errors = malloc(strlen(dir_path) + strlen(file_Names[1]) + 1);
    strcpy(musics_errors, dir_path);
    strcat(musics_errors, file_Names[1]);


    FILE *file_musics = fopen(musics_errors, "w");
    free(musics_errors);
    if (file_musics == NULL) {
        perror("Erro ao abrir ficheiro musics_errors.csv");
        return -1;
    }
    fprintf(file_musics, "%s\n", headers[1]);
    
    //Catalogo_Musicas catalogo_musica = get_catalogo_musicas(catalogo);
    //GHashTable *musicas_invalidas = getMusicasInvalidas(catalogo_musica);
    
    g_hash_table_foreach(musicas_invalidas, escreve_musica, file_musics);
    
    fclose(file_musics);


    //users

    char *users_errors = malloc(strlen(dir_path) + strlen(file_Names[2]) + 1);
    strcpy(users_errors, dir_path);
    strcat(users_errors, file_Names[2]);


    FILE *file_users = fopen(users_errors, "w");
    free(users_errors);
    if (file_users == NULL) {
        perror("Erro ao abrir ficheiro users_errors.csv");
        return -1;
    }
    fprintf(file_users, "%s\n", headers[2]);
    
    //catalogo_utilizadores catalogo_users = get_catalogo_utilizadores(catalogo);
    GHashTable *users_invalidos = getUtilizadoresInvalidos(catalogo_utilizadores);
    g_hash_table_foreach(users_invalidos, escreve_user, file_users);
    
    fclose(file_users);


    return 0;
    
}

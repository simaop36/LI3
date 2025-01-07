#include <glib.h>
#include <stdio.h>
#include <stdlib.h>

#include "historico.h"
#include "catalogo_historico.h"
#include "utils.h"
#include "estatisticas.h"
#include "segVer.h"

typedef struct catalogo_historico
{
    GHashTable *historico_validos;
    GPtrArray *keys_history;
} *Catalogo_Historico;

Catalogo_Historico create_catalogo_historico()
{
    Catalogo_Historico catalogo = malloc(sizeof(struct catalogo_historico));
    catalogo->historico_validos = g_hash_table_new_full(NULL, g_direct_equal, NULL, (GDestroyNotify)free_historico);
    catalogo->keys_history = NULL;

    return catalogo;
}

void build_Historico(char **linha, void *cat, Stats stats)
{

    Joint joint = (Joint)cat;
    Catalogo_Historico catalogo = get_catalogo_historico(joint);

    if (verifica_historico(linha))
    {
        Historico historico = create_Historico();

        setId_Historico(linha[0], historico);
        set_UserId(linha[1], historico);
        set_MusicId(linha[2], historico);
        set_Timestamp(linha[3], historico);
        set_Duration(linha[4], historico);
        // set_week(historico);
        segVerHistory(historico, joint);
        add_historico_valido(catalogo, historico);
        // calcula_tree(stats,historico);
    }
    else
    {
        escreve_historico("./resultados", linha);
    }
}

void add_historico_valido(Catalogo_Historico catalogo, Historico historico)
{

    g_hash_table_insert(catalogo->historico_validos, get_IDHistorico_gpointer(historico), historico);
}

GPtrArray *get_keys_history(Catalogo_Historico catalogo)
{
    return catalogo->keys_history;
}

void build_keys_history(Catalogo_Historico catalogo)
{
    GHashTable *hash_table = catalogo->historico_validos;

    if (catalogo->keys_history != NULL)
    {
        g_ptr_array_free(catalogo->keys_history, TRUE);
        catalogo->keys_history = NULL;
    }

    GPtrArray *keys = g_ptr_array_new();
    if (keys == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for GPtrArray.\n");
        return;
    }

    GHashTableIter iter;
    gpointer key, value;

    g_hash_table_iter_init(&iter, hash_table);
    while (g_hash_table_iter_next(&iter, &key, &value))
    {
        g_ptr_array_add(keys, key);
    }

    catalogo->keys_history = keys;
}

Historico get_historico_valido(Catalogo_Historico catalogo, gpointer id)
{
    return (Historico)g_hash_table_lookup(catalogo->historico_validos, id);
}

GHashTable *getHistoricoValidos(Catalogo_Historico historico)
{
    return historico->historico_validos;
}

void free_catalogo_historico(Catalogo_Historico catalogo)
{
    if (catalogo->historico_validos)
    {
        g_hash_table_unref(catalogo->historico_validos);
    }
    g_ptr_array_free(catalogo->keys_history, TRUE);
    free(catalogo);
}

void escreve_historico(const char *dir_path, char **linha)
{
    const char *file_Name = "/history_errors.csv";
    const char *header = "\"id\";\"user_id\";\"music_id\";\"timestamp\";\"duration\";\"platform\"";

    char *history_errors = malloc(strlen(dir_path) + strlen(file_Name) + 1);
    strcpy(history_errors, dir_path);
    strcat(history_errors, file_Name);

    // Abre o ficheiro para escrita
    FILE *file_history = fopen(history_errors, "a");
    free(history_errors); // Liberta a memória alocada para o caminho do ficheiro
    if (file_history == NULL)
    {
        perror("Erro ao abrir ficheiro history_errors.csv");
        return;
    }

    fseek(file_history, 0, SEEK_END); // Move o ponteiro para o final do arquivo
    long size = ftell(file_history);  // Obtém a posição atual do ponteiro (tamanho do arquivo)
    if (size == 0)
    {
        fprintf(file_history, "%s\n", header);
    }

    fprintf(file_history, "\"%s\";\"%s\";\"%s\";\"%s\";\"%s\";\"%s\"\n",
            linha[0],
            linha[1],
            linha[2],
            linha[3],
            linha[4],
            linha[5]);

    fclose(file_history);
}

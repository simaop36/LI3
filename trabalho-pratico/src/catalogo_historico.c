#include <glib.h>
#include <stdio.h>
#include <stdlib.h>

#include "historico.h"
#include "catalogo_historico.h"

typedef struct catalogo_historico
{
    GHashTable *historico_validos;
    GHashTable *historico_invalidos;
} *Catalogo_Historico;

Catalogo_Historico create_catalogo_historico()
{
    Catalogo_Historico catalogo = malloc(sizeof(struct catalogo_historico));
    catalogo->historico_validos = g_hash_table_new_full(g_str_hash, g_str_equal, free, (GDestroyNotify)free_historico);
    catalogo->historico_invalidos = g_hash_table_new_full(g_str_hash, g_str_equal, free, (GDestroyNotify)free_historico);

    return catalogo;
}

void build_Historico(char **linha,void *cat){

    Historico historico = create_Historico();
    Catalogo_Historico catalogo = (Catalogo_Historico)cat;
    
    setId_Historico(linha[0],historico);
    set_UserId(linha[1],historico);
    set_MusicId(linha[2],historico);
    set_Timestamp(linha[3],historico);
    set_Duration(linha[4],historico);
    //printf("%s\n",linha[5]);
    set_Plataform(linha[5],historico);

    if(verifica_historico(linha)){
        add_historico_valido(catalogo,historico);
    } else{
        add_historico_invalido(catalogo,historico);
    }
}

void add_historico_valido(Catalogo_Historico catalogo, Historico historico)
{

    char *key = get_IDHistorico(historico);

    g_hash_table_insert(catalogo->historico_validos, key, historico);
}
void add_historico_invalido(Catalogo_Historico catalogo, Historico historico)
{

    char *key = get_IDHistorico(historico);

    g_hash_table_insert(catalogo->historico_invalidos, key, historico);
}

Historico get_historico_valido(Catalogo_Historico catalogo, char *id)
{
    return (Historico)g_hash_table_lookup(catalogo->historico_validos, id);
}


Historico get_historico_invalido(Catalogo_Historico catalogo, char *id)
{
    return (Historico)g_hash_table_lookup(catalogo->historico_invalidos, id);
}

GHashTable *getHistoricoValidos(Catalogo_Historico historico)
{
    return historico->historico_validos;
}

GHashTable *getHistoricoInvalidos(Catalogo_Historico historico)
{
    return historico->historico_invalidos;
}

void free_catalogo_historico_invalidos(Catalogo_Historico catalogo){
    if (catalogo->historico_invalidos) {
        g_hash_table_unref(catalogo->historico_invalidos);
    }
}

void free_catalogo_historico_validos(Catalogo_Historico catalogo){
    if (catalogo->historico_validos) {
        g_hash_table_unref(catalogo->historico_validos);
    }
}

void free_catalogo_historico(Catalogo_Historico catalogo)
{
    if (catalogo->historico_validos) {
        g_hash_table_unref(catalogo->historico_validos);
    }
    if (catalogo->historico_invalidos) {
        g_hash_table_unref(catalogo->historico_invalidos);
    }
    free(catalogo);
}

void aux_escreve_historico(gpointer key, gpointer value, gpointer user_data)
{
    FILE *file = (FILE *)user_data;
    Historico historico = (Historico)value;

    char *id = get_IDHistorico(historico);
    char *user_id = get_UserId(historico);
    char *music_id = get_MusicId(historico);
    char *time = get_Timestamp(historico);
    char *duration = get_Duration(historico);
    char *platform = get_Plataform(historico);

    fprintf(file, "\"%s\";\"%s\";\"%s\";\"%s\";\"%sf\";\"%s\"\n",
            id,
            user_id,
            music_id,
            time,
            duration,
            platform);

    free(id);
    free(user_id);
    free(music_id);
    free(time);
    free(duration);
    free(platform);
}

void escreve_historico(const char *dir_path, Catalogo_Historico catalogo)
{
    const char *file_Name = "/history_errors.csv";
    const char *header = "\"id\";\"user_id\";\"music_id\";\"timestamp\";\"duration\";\"platform\"" ;

    char *history_errors = malloc(strlen(dir_path) + strlen(file_Name) + 1);
    strcpy(history_errors, dir_path);
    strcat(history_errors, file_Name);

    GHashTable *historicos_invalidos = getHistoricoInvalidos(catalogo);

    if (g_hash_table_size(historicos_invalidos) == 0)
    {
        free(history_errors);
        return;
    }

    // Abre o ficheiro para escrita
    FILE *file_history = fopen(history_errors, "w");
    free(history_errors); // Liberta a memória alocada para o caminho do ficheiro
    if (file_history == NULL)
    {
        perror("Erro ao abrir ficheiro history_errors.csv");
        return;
    }

    fprintf(file_history, "%s\n", header);

    g_hash_table_foreach(historicos_invalidos, aux_escreve_historico, file_history);

    fclose(file_history);

}

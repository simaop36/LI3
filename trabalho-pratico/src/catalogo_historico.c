#include <glib.h>

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
    setId_MusicId(linha[2],historico);
    set_Timestamp(linha[4],historico);
    set_Duration(linha[5],historico);
    set_Plataform(linha[6],historico);

    if(verifica_historico(linha)){
        add_historico_valido(catalogo,historico);
    } else{
        add_historico_invalido(catalogo,historico);
    }
}

void add_historico_invalido(Catalogo_Historico catalogo, Historico historico)
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
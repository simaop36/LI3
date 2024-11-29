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
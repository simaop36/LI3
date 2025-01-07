#ifndef CATALOGO_HISTORICO_H
#define CATALOGO_HISTORICO_H

#include "historico.h"
#include "estatisticas.h"

typedef struct catalogo_historico *Catalogo_Historico;
typedef struct historico *Historico;

Catalogo_Historico create_catalogo_historico();
void build_Historico(char **linha, void *cat, Stats stats);
void add_historico_valido(Catalogo_Historico catalogo, Historico historico);
GPtrArray *get_keys_history(Catalogo_Historico catalogo);
void build_keys_history(Catalogo_Historico catalogo);
Historico get_historico_valido(Catalogo_Historico catalogo, gpointer id);
// GHashTable *getHistoricoValidos(Catalogo_Historico historico);
void free_catalogo_historico(Catalogo_Historico catalogo);
void escreve_historico(const char *dir_path, char **linha);

#endif
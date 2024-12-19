#ifndef CATALOGO_HISTORICO_H
#define CATALOGO_HISTORICO_H

typedef struct catalogo_historico *Catalogo_Historico;
Catalogo_Historico create_catalogo_historico();
void build_Historico(char **linha,void *cat);
void add_historico_valido(Catalogo_Historico catalogo, Historico historico);
void add_historico_invalido(Catalogo_Historico catalogo, Historico historico);
Historico get_historico_valido(Catalogo_Historico catalogo, char *id);
Historico get_historico_invalido(Catalogo_Historico catalogo, char *id);
GHashTable *getHistoricoValidos(Catalogo_Historico historico);
GHashTable *getHistoricoInvalidos(Catalogo_Historico historico);
void free_catalogo_historico_invalidos(Catalogo_Historico catalogo);
void free_catalogo_historico_validos(Catalogo_Historico catalogo);
void free_catalogo_historico(Catalogo_Historico catalogo);

#endif
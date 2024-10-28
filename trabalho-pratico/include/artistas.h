#ifndef ARTISTAS_H
#define ARTISTAS_H

typedef struct artista *Artista;

Artista create_Artista();
void build_Artista(char *id, char *name, char *description, double recipe_per_stream, char **id_constituent, char *country, char *type);

char* getId(Artista a);
char* getName(Artista a);
char* getDescription(Artista a);
double getRecipe_Per_Stream(Artista a);
char** getId_Constituent(Artista a);
char* getCountry(Artista a);
char* getType(Artista a);
void setId(char* id,Artista a);
void setName(char* name,Artista a);
void setDescription(char* description,Artista a);
void setRecipe_Per_Stream(double recipe_per_stream,Artista a);
void setId_Constituent(char** id_constituent,Artista a);
void setCountry(char* country,Artista a);
void setType(char* type,Artista a);
void free_artista(Artista novo_artista);

#endif
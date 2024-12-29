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
#include "catalogo_historico.h"
#include "artistas.h"
#include "musica.h"
#include "users.h"


void escreve_csv(const char *dir_path, Joint joint)
{

    Catalogo_Artistas cat_artistas = get_catalogo_artistas(joint);
    Catalogo_Musicas cat_musicas = get_catalogo_musicas(joint);
    catalogo_utilizadores cat_users = get_catalogo_utilizadores(joint);
    Catalogo_Historico cat_historico = get_catalogo_historico(joint);


    escreve_artistas(dir_path,cat_artistas);
    escreve_musicas(dir_path,cat_musicas);
    escreve_users(dir_path,cat_users);
    escreve_historico(dir_path,cat_historico);
   
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
    fclose(file);

}

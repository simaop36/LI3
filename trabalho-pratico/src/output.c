#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>

#include "output.h"
#include "joint.h"



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

#include <stdio.h>
#include <stdlib.h>

#include "input.h"
#include "output.h"
#include "joint.h"

void run(char *argv[]){

    Joint catalogo = create_catalago_joint();
    ler_csvs(argv[1],catalogo);
    escreve_csv("./resultados",catalogo);
    free_joint(catalogo);
}
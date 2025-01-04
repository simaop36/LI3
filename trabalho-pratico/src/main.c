#include <stdio.h>
#include "controller.h"

int main(int argc, char *argv[])
{
    if (argc == 3)
    { // programa-principal

        run(argv);
    }
    else if (argc == 4)
    { // programa-testes
        run_testes(argv);
    }
    else if (argc == 1)
    {
        run_interactive();
    }
    else
    {
        printf("Número de argumentos errado\n");
        printf("Para programa-principal: \n");
        printf("./programa-principal /caminho para os ficheiros csv de entrada/ /caminho para o ficheiro com as queries/ \n");
        printf("Para programa-testes: \n");
        printf("./programa-testes /caminho para os ficheiros csv de entrada/ /caminho para o ficheiro com as queries/ /caminho para os resultados esperados/ \n");
    }

    return 0;
}
#include <stdio.h>


int main(int argc, char *argv[]){
    if(argc == 3){  //programa-principal

        //ler_csv(argv[1]);

        //executa_queries(argv[2])
        
    } else if (argc == 4){ //programa-testes
        
    } else{
        printf("Número de argumentos errado\n");
        printf("Para programa-principal: \n");
        printf("./programa-principal /caminho para os ficheiros csv de entrada/ /caminho para o ficheiro com as queries/ \n");
        printf("Para programa-testes: \n");
        printf("./programa-testes /caminho para os ficheiros csv de entrada/ /caminho para o ficheiro com as queries/ /caminho para os resultados esperados/ \n");
    }
    
    return 0;
}
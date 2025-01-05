#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/resource.h>

#include "input.h"
#include "output.h"
#include "joint.h"
#include "utils.h"
#include "estatisticas.h"
#include "queries.h"

void run(char *argv[])
{

    Joint catalogo = create_catalago_joint();
    Stats stats = create_estatisticas();
    ler_csvs(argv[1], catalogo, stats);
    char *queries = ler_queries(argv[2], catalogo, stats);
    free_joint(catalogo);
    free(queries);
    free_stats(stats);
}

void run_testes(char *argv[])
{
    struct rusage uso_recurso;
    struct timespec start, end;
    FILE *arquivo;

    clock_gettime(CLOCK_REALTIME, &start);

    Joint catalogo = create_catalago_joint();
    Stats stats = create_estatisticas();
    ler_csvs(argv[1], catalogo, stats);
    char *queries = ler_queries(argv[2], catalogo, stats);
    free_joint(catalogo);
    free_stats(stats);
    clock_gettime(CLOCK_REALTIME, &end);

    getrusage(RUSAGE_SELF, &uso_recurso);
    long memoria_usada = uso_recurso.ru_maxrss;

    char *compara_queries = compara_resultados(argv[3], "./resultados");

    double tempo_execucao = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

    printf("Tempo de execução: %.6f segundos\n", tempo_execucao);
    printf("Memória máxima utilizada: %ld KB\n", memoria_usada);

    arquivo = fopen("resultado.txt", "w");
    if (arquivo == NULL)
    {
        fprintf(stderr, "Erro ao criar o arquivo de resultado\n");
        return;
    }
    fprintf(arquivo, "%s\n", compara_queries);
    fprintf(arquivo, "%s\n", queries);
    fprintf(arquivo, "Tempo de execução total do programa: %.6f segundos\n", tempo_execucao);
    fprintf(arquivo, "Memória máxima utilizada: %ld KB\n", memoria_usada);
    free(compara_queries);
    fclose(arquivo);
    free(queries);
}

void run_interactive()
{
   char caminhoFicheiro[200];

    // caminho dos csv
    printf("Introduza o caminho dos ficheiros de dados: \n");
    if (fgets(caminhoFicheiro, sizeof(caminhoFicheiro), stdin) == NULL) {
        fprintf(stderr, "Erro ao ler o input.\n");
        return;
    }
    // remove \n
    caminhoFicheiro[strcspn(caminhoFicheiro, "\n")] = '\0';

    // precessa csv
    printf("A carregar dataset...\n");
    Joint catalogo = create_catalago_joint();
    Stats stats = create_estatisticas();
    ler_csvs(caminhoFicheiro, catalogo, stats);
    printf("Dataset carregado...\n");

    while (1) {
        char buffer[32];
        int n_querie;
        char input[1000];
        char *output;
        int separador;

        // numero da querie
        printf("Que querie deseja executar: \n");
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            fprintf(stderr, "Erro ao ler o input.\n");
            continue;
        }
        if (sscanf(buffer, "%d", &n_querie) != 1) {
            printf("Entrada inválida.\n");
            continue;
        }
        printf("Que separador deseja usar: \n");
        printf("Escreva 1 para usar \"=\" \n");
        printf("Escreva 0 para usar \";\" \n");
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            fprintf(stderr, "Erro ao ler o input.\n");
            continue;
        }
        if (sscanf(buffer, "%d", &separador) != 1) {
            printf("Entrada inválida.\n");
            continue;
        }

        // argumentos da querie
        printf("Indique os argumentos: \n");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            fprintf(stderr, "Erro ao ler o input.\n");
            continue;
        }
        input[strcspn(input, "\n")] = '\0'; // remove \n

        // executar a querie
        output = excuta_queries_iterativo(n_querie,separador, input, catalogo, stats);
        if (output == NULL || strcmp(output, "\n") == 0) {
            printf("\nSem resposta / Não encontrado\n");
            if (output) free(output);
        } else {
            printf("\nResposta Obtida :\n");
            printf("%s\n", output);
            free(output);
        }

        // nova querie
        char resposta[4];
        printf("Deseja fazer outra query? (s para continuar, qualquer outra tecla para sair): ");
        if (fgets(resposta, sizeof(resposta), stdin) == NULL) {
            fprintf(stderr, "Erro ao ler o input.\n");
            break;
        }
        resposta[strcspn(resposta, "\n")] = '\0'; // remove \n

        if (strcmp(resposta, "s") != 0) {
            printf("A fechar programa...\n");
            free_joint(catalogo);
            free_stats(stats);
            break;
        }
    }

}
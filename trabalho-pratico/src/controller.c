#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/resource.h>

#include "input.h"
#include "output.h"
#include "joint.h"
#include "utils.h"
#include "estatisticas.h"

void run(char *argv[])
{

    Joint catalogo = create_catalago_joint();
    Stats stats = create_estatisticas();
    ler_csvs(argv[1], catalogo,stats);
    char *queries = ler_queries(argv[2], catalogo,stats);
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
    ler_csvs(argv[1], catalogo,stats);
    char *queries = ler_queries(argv[2], catalogo,stats);
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
#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "joint.h"
#include "users.h"
#include "utils.h"



char* Q1(char* ID,Joint catalogo){
    catalogo_utilizadores catU = getUtilizadoresValidos(catalogo);
    utilizador u = get_utilizador_valido(catU,ID);
    char* data_atual = "2024/09/09";
    char* email = get_email(u);
    char* first_name = get_first_name(u);
    char* last_name = get_last_name(u);
    char* birth_date = get_birth_date(u);
    char* country = get_country(u);
    int idade = calcula_idade(data_atual,birth_date);
    
    size_t buffer_size = strlen(email) + strlen(first_name) + strlen(last_name) +
                         strlen(country) + 50; 
    char* resposta = malloc(buffer_size);

    if (resposta == NULL) {
        
        return NULL;
    }

    
    snprintf(resposta, buffer_size, " %s;%s;%s;%d;%s\n",
             email, first_name, last_name, idade, country);

    return resposta;


}
#ifndef UTILS_H
#define UTILS_H

int valida_data(const char *data);
int valida_duracao(const char *duracao);
int valida_email(const char *email);
int valida_tipo(const char *tipo);
int valida_tipo_user(const char *tipo);
int valida_tipo_artista(const char *tipo, const char *id_Constituent);
int valida_lista(const char *str);

#endif
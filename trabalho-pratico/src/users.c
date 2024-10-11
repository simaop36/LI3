#include "users.h"

typedef struct utilizador {
    char *username;
    char *email;
    char *first_name;
    char *last_name;
    char *birth_date;
    char *country;
    char *subscription_style;
    char **liked_musics_id;
} utilizador;
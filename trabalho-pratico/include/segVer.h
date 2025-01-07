#ifndef SEGVER_H
#define SEGVER_H

#include <time.h>
#include <glib.h>

#include "utils.h"
#include "catalogo_musica.h"
#include "catalogo_users.h"
#include "users.h"
#include "catalogo_artista.h"
#include "joint.h"

int segVerMusica(musica m, Joint joint);
int segVerUser(utilizador utilizador, Joint joint);
void segVerAlbum(Album a,Joint j);
void segVerHistory(Historico h, Joint j);

#endif
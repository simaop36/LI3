#ifndef INPUT_H
#define INPUT_H

#include "joint.h"

void ler_csvs(const char *dir_path, Joint joint, Stats stats);
char *ler_queries(const char *file_path, Joint joint, Stats s);

#endif
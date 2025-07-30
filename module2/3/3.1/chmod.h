#ifndef CHMOD_H
#define CHMOD_H

#include <stdio.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>

mode_t parse_input(const char* input);
mode_t modify_mode(mode_t mode, const char* mod);


#endif //CHMOD_H
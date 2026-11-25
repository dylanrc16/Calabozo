#include <string.h>
#include "lugar.h"

void lugar_inicializar(struct Lugar *l, const char *nombre) {
    strncpy(l->nombre, nombre, LARGO_NOMBRE - 1);
    l->nombre[LARGO_NOMBRE - 1] = '\0';
    l->bienestar = 50;
}

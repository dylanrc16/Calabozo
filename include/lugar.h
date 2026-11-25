#ifndef LUGAR_H
#define LUGAR_H

#define LARGO_NOMBRE 64

struct Lugar {
    char nombre[LARGO_NOMBRE];
    int bienestar;          // 0 a 100
    // actores y proyectos: se agregan en el paso 9
};

void lugar_inicializar(struct Lugar *l, const char *nombre);

#endif

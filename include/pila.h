#ifndef PILA_H
#define PILA_H

#define MAX_PILA 200

struct Pila {
    int datos[MAX_PILA];
    int tope;              // cuántos elementos hay
};

void pila_inicializar(struct Pila *p);
int  pila_vacia(const struct Pila *p);
int  pila_llena(const struct Pila *p);
int  pila_push(struct Pila *p, int valor);
int  pila_pop(struct Pila *p, int *valor);

#endif

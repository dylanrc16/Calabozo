#include "unionfind.h"

void uf_inicializar(struct UnionFind *uf, int n) {
    int i;
    if (n > MAX_UF) n = MAX_UF;
    uf->n = n;
    for (i = 0; i < n; i++)
        uf->padre[i] = i;          // cada uno es su propio jefe
}

int uf_encontrar(const struct UnionFind *uf, int x) {
    while (uf->padre[x] != x)      // subir hasta el jefe
        x = uf->padre[x];
    return x;
}

int uf_unir(struct UnionFind *uf, int a, int b) {
    int jefe_a = uf_encontrar(uf, a);
    int jefe_b = uf_encontrar(uf, b);

    if (jefe_a == jefe_b) return 0;   // ya estaban juntos: sería ciclo
    uf->padre[jefe_b] = jefe_a;
    return 1;                          // se unieron
}

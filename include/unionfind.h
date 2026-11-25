#ifndef UNIONFIND_H
#define UNIONFIND_H

#define MAX_UF 200

struct UnionFind {
    int padre[MAX_UF];
    int n;                 // cuántos elementos se usan
};

void uf_inicializar(struct UnionFind *uf, int n);
int  uf_encontrar(const struct UnionFind *uf, int x);
int  uf_unir(struct UnionFind *uf, int a, int b);

#endif

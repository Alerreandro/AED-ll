#ifndef AVL_H
#define AVL_H

typedef struct no {
    int chave;
    struct no *esq, *dir;
    int fb;          // Fator de balanço
    int cresceu;     // Indica se a árvore cresceu após a inserção
    int diminuiu;    // Indica se a árvore diminuiu após a remoção
} no;

typedef no* arvore;

arvore inserir(arvore raiz, int chave, int *cresceu);
arvore remover(arvore raiz, int valor, int *diminuiu);
arvore rotacionar(arvore raiz);
arvore rotacao_simples_direita(arvore raiz);
arvore rotacao_simples_esquerda(arvore raiz);
arvore rotacao_dupla_direita(arvore raiz);
arvore rotacao_dupla_esquerda(arvore raiz);
arvore procurar_maior(arvore raiz);
void preOrder(arvore raiz);
void posOrder(arvore raiz);

#endif

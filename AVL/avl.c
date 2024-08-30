#include "avl.h"
#include <stdlib.h>
#include <stdio.h>

arvore inserir(arvore raiz, int chave, int *cresceu) {
    if (raiz == NULL) {
        arvore novo = (arvore)malloc(sizeof(no));
        novo->chave = chave;
        novo->esq = NULL;
        novo->dir = NULL;
        novo->fb = 0;
        *cresceu = 1;
        return novo;
    } else {
        if (chave > raiz->chave) {
            raiz->dir = inserir(raiz->dir, chave, cresceu);
            if (*cresceu) {
                switch (raiz->fb) {
                    case -1:
                        raiz->fb = 0;
                        *cresceu = 0;
                        break;
                    case 0:
                        raiz->fb = 1;
                        *cresceu = 1;
                        break;
                    case 1:
                        if (raiz->dir->fb >= 0) {
                            raiz = rotacao_simples_esquerda(raiz);
                        } else {
                            raiz = rotacao_dupla_esquerda(raiz);
                        }
                        *cresceu = 0;
                        break;
                }
            }
        } else {
            raiz->esq = inserir(raiz->esq, chave, cresceu);
            if (*cresceu) {
                switch (raiz->fb) {
                    case 1:
                        raiz->fb = 0;
                        *cresceu = 0;
                        break;
                    case 0:
                        raiz->fb = -1;
                        *cresceu = 1;
                        break;
                    case -1:
                        if (raiz->esq->fb <= 0) {
                            raiz = rotacao_simples_direita(raiz);
                        } else {
                            raiz = rotacao_dupla_direita(raiz);
                        }
                        *cresceu = 0;
                        break;
                }
            }
        }
    }
    return raiz;
}

arvore remover(arvore raiz, int valor, int *diminuiu) {
    if (raiz == NULL) {
        *diminuiu = 0;
        return NULL;
    }
    if (valor == raiz->chave) {
        if (raiz->esq == NULL && raiz->dir == NULL) {
            free(raiz);
            *diminuiu = 1;
            return NULL;
        }
        if (raiz->esq != NULL && raiz->dir == NULL) {
            arvore temp = raiz->esq;
            free(raiz);
            *diminuiu = 1;
            return temp;
        }
        if (raiz->esq == NULL && raiz->dir != NULL) {
            arvore temp = raiz->dir;
            free(raiz);
            *diminuiu = 1;
            return temp;
        }
        arvore maior = procurar_maior(raiz->esq);
        raiz->chave = maior->chave;
        raiz->esq = remover(raiz->esq, maior->chave, diminuiu);
    } else if (valor > raiz->chave) {
        raiz->dir = remover(raiz->dir, valor, diminuiu);
        if (*diminuiu) {
            switch (raiz->fb) {
                case -1:
                    raiz->fb = 0;
                    *diminuiu = 1;
                    break;
                case 0:
                    raiz->fb = 1;
                    *diminuiu = 0;
                    break;
                case 1:
                    if (raiz->dir->fb >= 0) {
                        raiz = rotacao_simples_esquerda(raiz);
                    } else {
                        raiz = rotacao_dupla_esquerda(raiz);
                    }
                    *diminuiu = 0;
                    break;
            }
        }
    } else {
        raiz->esq = remover(raiz->esq, valor, diminuiu);
        if (*diminuiu) {
            switch (raiz->fb) {
                case 1:
                    raiz->fb = 0;
                    *diminuiu = 1;
                    break;
                case 0:
                    raiz->fb = -1;
                    *diminuiu = 0;
                    break;
                case -1:
                    if (raiz->esq->fb <= 0) {
                        raiz = rotacao_simples_direita(raiz);
                    } else {
                        raiz = rotacao_dupla_direita(raiz);
                    }
                    *diminuiu = 0;
                    break;
            }
        }
    }
    return raiz;
}

arvore procurar_maior(arvore raiz) {
    while (raiz->dir != NULL) {
        raiz = raiz->dir;
    }
    return raiz;
}

arvore rotacao_simples_direita(arvore raiz) {
    arvore p = raiz;
    arvore u = p->esq;
    p->esq = u->dir;
    u->dir = p;

    if (u->fb == 1) {
        p->fb = 0;
        u->fb = 0;
    } else if (u->fb == 0) {
        p->fb = 0;
        u->fb = 0;
    } else {
        p->fb = 1;
        u->fb = 0;
    }

    return u;
}

arvore rotacao_simples_esquerda(arvore raiz) {
    arvore p = raiz;
    arvore u = p->dir;
    p->dir = u->esq;
    u->esq = p;

    if (u->fb == -1) {
        p->fb = 0;
        u->fb = 0;
    } else if (u->fb == 0) {
        p->fb = 0;
        u->fb = 0;
    } else {
        p->fb = -1;
        u->fb = 0;
    }

    return u;
}

arvore rotacao_dupla_direita(arvore raiz) {
    raiz->esq = rotacao_simples_esquerda(raiz->esq);
    raiz = rotacao_simples_direita(raiz);

    if (raiz->fb == 1) {
        raiz->esq->fb = 0;
        raiz->dir->fb = -1;
    } else if (raiz->fb == -1) {
        raiz->esq->fb = 1;
        raiz->dir->fb = 0;
    } else {
        raiz->esq->fb = 0;
        raiz->dir->fb = 0;
    }

    raiz->fb = 0;
    return raiz;
}

arvore rotacao_dupla_esquerda(arvore raiz) {
    raiz->dir = rotacao_simples_direita(raiz->dir);
    raiz = rotacao_simples_esquerda(raiz);

    if (raiz->fb == 1) {
        raiz->esq->fb = 0;
        raiz->dir->fb = -1;
    } else if (raiz->fb == -1) {
        raiz->esq->fb = 1;
        raiz->dir->fb = 0;
    } else {
        raiz->esq->fb = 0;
        raiz->dir->fb = 0;
    }

    raiz->fb = 0;
    return raiz;
}

void preOrder(arvore raiz) {
    if (raiz != NULL) {
        printf("[%d]\n", raiz->chave);
        preOrder(raiz->esq);
        preOrder(raiz->dir);
    }
}

void posOrder(arvore raiz) {
    if (raiz != NULL) {
        posOrder(raiz->esq); 
        posOrder(raiz->dir);
        printf("[%d]\n", raiz->chave);
    }
}

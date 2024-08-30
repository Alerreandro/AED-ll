#ifndef RB_H
#define RB_H

enum Cor {VERMELHO,PRETO,DUPLO_PRETO,};

typedef int tipoDado;

typedef struct no {
    tipoDado chave;
    struct no *esquerda;
    struct no *direita;
    struct no *pai;
    enum Cor cor;
} no;

typedef no* rb;

int Raiz (rb elemento);
int FilhoEsquerdo (rb elemento);
int FilhoDireito (rb elemento);
rb irmao (rb elemento);
rb tio (rb elemento);
enum Cor cor (rb elemento);
void inicializar (rb *raiz);
rb inserir (rb *raiz, int valor);
void ajustar (rb *raiz, rb elemento);   
void rotacaoDireita (rb *raiz, rb pivo);
void rotacaoEsquerda (rb *raiz, rb pivo);
void rotacaoDuplaDireita (rb *raiz, rb elemento);
void rotacaoDuplaEsquerda (rb *raiz, rb elemento);
void preOrder (rb raiz);
void posOrder (rb raiz);
void retiraDuploPreto (rb *raiz, rb elemento);
void reajustar (rb *raiz, rb elemento);
int maiorElemento (rb raiz);
void remover (int valor, rb *raiz);

#endif
#include <stdio.h>
#include <stdlib.h>
#include "rb.h"

rb noNull;

// Função para iniciar uma árvore vazia
void inicializar (rb *raiz) {
	*raiz = NULL;
	noNull = (rb) malloc(sizeof(no));
	noNull->cor = DUPLO_PRETO;
	noNull->chave = 0;
    noNull->esquerda = NULL;
    noNull->direita = NULL;
}

// Função para verificar se um nó é a raiz da árvore
int Raiz (rb elemento) {
    if (elemento != NULL && elemento->pai == NULL) {
        return 1;
    } else {
        return 0;
    }
}

// Função para verificar se um nó é filho esquerdo
int FilhoEsquerdo (rb elemento) {
    if (elemento->pai != NULL && elemento->pai->esquerda == elemento) {
        return 1;
    } else {
        return 0;
    }
}

// Função para verificar se um nó é filho direito
int FilhoDireito (rb elemento) {
    if (elemento->pai != NULL && elemento->pai->direita == elemento) {
        return 1;
    } else {
        return 0;
    }
}

// Função para encontrar o irmão de um nó
rb irmao (rb elemento) {
    if (elemento == elemento->pai->esquerda) {
        return elemento->pai->direita;
    } else {
        return elemento->pai->esquerda;
    }
}

// Função para encontrar o tio de um nó
rb tio (rb elemento) {
    return(irmao(elemento->pai));
}

// Função para retornar a cor do no
enum Cor cor (rb elemento) {
    enum Cor c;

    if (elemento == NULL) {
        c = PRETO;
    } else {
        c = elemento->cor;
    }
    return c;
}
// Função para inserir um elemento na árvore
rb inserir (rb *raiz, int valor) {
    rb posicao, pai, novo;

    posicao = *raiz;
    pai = NULL;

    while (posicao != NULL) {
        pai = posicao;

        if (valor > posicao->chave) {
            posicao = posicao->direita;
        } else {
            posicao = posicao->esquerda;
        }
    }

    novo = (rb)malloc(sizeof(no));
    novo->chave = valor;
    novo->esquerda = NULL;
    novo->direita = NULL;
    novo->pai = pai;
    novo->cor = VERMELHO;

    if (Raiz(novo)) {
        *raiz = novo;
    } else {
        if (valor > pai->chave) {
            pai->direita = novo;
        } else {
            pai->esquerda = novo;
        }
    }
    ajustar(raiz, novo);
}

// Função para ajustar a árvore RB
void ajustar (rb *raiz, rb elemento) {
    while (cor(elemento->pai) == VERMELHO && cor(elemento) == VERMELHO) {        
        // Caso 1: tio vermelho
        if (cor(tio(elemento)) == VERMELHO) {
            tio(elemento)->cor = PRETO;
            elemento->pai->cor = PRETO;
            elemento->pai->pai->cor = VERMELHO;
            elemento = elemento->pai->pai;
            continue;
        }

        // Caso 2a: rotação simples a direita 
        if (FilhoEsquerdo(elemento) && FilhoEsquerdo(elemento->pai)) {
            rotacaoDireita(raiz, elemento->pai->pai);
            elemento->pai->cor = PRETO;
            irmao(elemento)->cor = VERMELHO;
            continue;
        }

        // Caso 2b: rotação simples a esquerda 
        if (FilhoDireito(elemento) && FilhoDireito(elemento->pai)) {
            rotacaoEsquerda(raiz, elemento->pai->pai);
            elemento->pai->cor = PRETO;
            irmao(elemento)->cor = VERMELHO;
            continue;
        }

        // Caso 3a: rotacao dupla a direita
        if (FilhoDireito(elemento) && FilhoEsquerdo(elemento->pai)) {
            rotacaoDuplaDireita(raiz, elemento->pai);
            elemento->cor = PRETO;
            elemento->direita->cor = VERMELHO;
        }

        // Caso 3b: rotacao dupla a esquerda 
        if (FilhoEsquerdo(elemento) && FilhoDireito(elemento->pai)) {
            rotacaoDuplaEsquerda(raiz, elemento->pai);
            elemento->cor = PRETO;
            elemento->esquerda->cor = VERMELHO;
        }
    }
    (*raiz)->cor = PRETO;
}

// Função para realizar a rotação simples à direita
void rotacaoDireita (rb *raiz, rb pivo) {
    rb u, t1;
    u = pivo->esquerda;
    t1 = u->direita;

    int posicaoPivoEsquerda = FilhoEsquerdo(pivo);

    // Atualizando os ponteiros

    pivo->esquerda = t1;
    
    if (t1 != NULL) {
        t1->pai = pivo;
    }

    u->direita = pivo;
    u->pai = pivo->pai;
    pivo->pai = u;

    // Ligando o resto da arvore a u

    if (Raiz(u)) {
        *raiz = u;
    } else { 
        if (posicaoPivoEsquerda) {
            u->pai->esquerda = u;
        } else {
            u->pai->direita = u;    
        }
    }

}

// Função para realizar a rotação simples à esquerda
void rotacaoEsquerda (rb *raiz, rb pivo) {
    rb u, t2;
    u = pivo->direita;
    t2 = u->esquerda;

    int posicaoPivoEsquerda = FilhoEsquerdo(pivo);

    // Atualizando os ponteiros

    pivo->direita = t2;

    if (t2 != NULL) {
        t2->pai = pivo;
    }

    u->esquerda = pivo;
    u->pai = pivo->pai;
    pivo->pai = u;

    // Ligando o resto da arvore a u

    if (Raiz(u)) {
        *raiz = u;
    } else {
        if (posicaoPivoEsquerda) {
            u->pai->esquerda = u;
        } else {
            u->pai->direita = u;    
        }
    }
}

// Função para realizar a rotação dupla à esquerda
void rotacaoDuplaEsquerda (rb *raiz, rb elemento) {
    rotacaoDireita(raiz, elemento);
    rotacaoEsquerda(raiz, elemento->pai);
}

// Função para realizar a rotação dupla à direita
void rotacaoDuplaDireita (rb *raiz, rb elemento) {
    rotacaoEsquerda(raiz, elemento);
    rotacaoDireita(raiz, elemento->pai);
}

// Função para percorrer a árvore em pré-ordem
void preOrder (rb raiz) {
    if (raiz != NULL) {
        printf("[%d]", raiz->chave);
        preOrder(raiz->esquerda);
        preOrder(raiz->direita);
    }
}

// Função para remover um valor da árvore RB
void remover (int valor, rb *raiz) {
    rb posicao;
    posicao = *raiz;

     while (posicao != NULL) {
        if (valor == posicao->chave) {
            // Elemento possui 2 filhos
            if (posicao->esquerda != NULL && posicao->direita != NULL) {
                posicao->chave = maiorElemento(posicao->esquerda);
                remover(posicao->chave, &(posicao->esquerda));
                break;
            }

            // Elemento com apenas 1 filho (direito)
            if (posicao->esquerda == NULL && posicao->direita != NULL) {
                posicao->direita->cor = PRETO;
                posicao->direita->pai = posicao->pai;

                if (Raiz(posicao)) {
                    *raiz = posicao->direita;
                } else {
                    if (FilhoEsquerdo(posicao)) {
                        posicao->pai->esquerda = posicao->direita;
                    } else {
                        posicao->pai->direita = posicao->direita;
                    }
                }
                free(posicao);
                break;
            }

            // Elemento com apenas 1 filho (esquerdo)
            if (posicao->direita == NULL && posicao->esquerda != NULL) {
                posicao->esquerda->cor = PRETO;
                posicao->esquerda->pai = posicao->pai;

                if (Raiz(posicao)) {
                    *raiz = posicao->esquerda;
                } else {
                    if (FilhoEsquerdo(posicao)) {
                        posicao->pai->esquerda = posicao->esquerda;
                    } else {
                        posicao->pai->direita = posicao->esquerda;
                    }
                }
                free(posicao);
                break;
            }

            // Elemento não possui filhos
            if (posicao->esquerda == NULL && posicao->direita == NULL) {
                // Elemento sendo raiz
                if (Raiz(posicao)) {
                    *raiz = NULL;
                    free(posicao);
                    break;
                }

                // Elemento sendo vermelho
                if (posicao->cor == VERMELHO) {
                    if (FilhoEsquerdo(posicao)) {
                        posicao->pai->esquerda = NULL;
                    } else {
                        posicao->pai->direita = NULL;
                    }
                    free(posicao);
                    break;
                } else {
                    // Elemento preto -> substituido pelo duplo preto
                    noNull->cor = DUPLO_PRETO;
                    noNull->pai = posicao->pai;

                    if (FilhoEsquerdo(posicao)) {
                        posicao->pai->esquerda = noNull;
                    } else {
                        posicao->pai->direita = noNull;
                    }

                    free(posicao);
                    reajustar(raiz, noNull);
                    break;
                }
            }
        }
        if (valor > posicao->chave) {
            posicao = posicao->direita;
        } else {
            posicao = posicao->esquerda;
        }
    }
}

// Função para imprimir o maior elemento da árvore
int maiorElemento (rb raiz) {
	if (raiz == NULL) {
        return -1;
    }
	if (raiz->direita == NULL) {
        return raiz->chave;
    } else {
		return maiorElemento(raiz->direita);
    }
}

// Função para arejustar a árvore RB
void reajustar (rb *raiz, rb elemento) {
    // Caso 1:
    if (Raiz(elemento)) {
        elemento->cor = PRETO;
        if (elemento == noNull) {
            *raiz = NULL;
        }    
        return;
    } 

    // Caso 2:
    if (cor(elemento->pai) == PRETO && cor(irmao(elemento)) == VERMELHO && cor(irmao(elemento)->esquerda) == PRETO && cor(irmao(elemento)->direita) == PRETO) {
        if (FilhoEsquerdo(elemento)) {
            rotacaoEsquerda(raiz, elemento->pai);
        } else {
            rotacaoDireita(raiz, elemento->pai);
        }
        elemento->pai->pai->cor = PRETO;
        elemento->pai->cor = VERMELHO;
        reajustar(raiz, elemento);
        return;
    }

    // Caso 3:   
    if (cor(elemento->pai) == PRETO && cor(irmao(elemento)) == PRETO && cor(irmao(elemento)->esquerda) == PRETO && cor(irmao(elemento)->direita) == PRETO) {
        elemento->pai->cor = DUPLO_PRETO;
        irmao(elemento)->cor = VERMELHO;
        retiraDuploPreto(raiz, elemento);
        reajustar(raiz, elemento->pai);
        return;
    }

    // Caso 4:
    if (cor(elemento->pai) == VERMELHO && cor(irmao(elemento)) == PRETO && cor(irmao(elemento)->esquerda) == PRETO && cor(irmao(elemento)->direita) == PRETO) {
        elemento->pai->cor = PRETO;
        irmao(elemento)->cor = VERMELHO;
        retiraDuploPreto(raiz, elemento);
        return;
    }

    // Caso 5a:
    if (cor(irmao(elemento)) == PRETO && cor(irmao(elemento)->esquerda) == VERMELHO && cor(irmao(elemento)->direita) == PRETO && FilhoEsquerdo(elemento)) { 
        rotacaoDireita(raiz, irmao(elemento));
        irmao(elemento)->cor = PRETO;
        irmao(elemento)->direita->cor = VERMELHO;
        reajustar(raiz, elemento);
        return;
    }

    // Caso 5b: simetrico
    if (cor(irmao(elemento)) == PRETO && cor(irmao(elemento)->direita) == VERMELHO && cor(irmao(elemento)->esquerda) == PRETO && FilhoDireito(elemento)) {
        rotacaoEsquerda(raiz, irmao(elemento));
        irmao(elemento)->cor = PRETO;
        irmao(elemento)->esquerda->cor = VERMELHO;
        reajustar(raiz, elemento);
        return;
    }

    // Caso 6a:
    if (cor(irmao(elemento)) == PRETO && cor(irmao(elemento)->direita) == VERMELHO && FilhoEsquerdo(elemento)) {        
        rotacaoEsquerda(raiz, elemento->pai);
        elemento->pai->pai->cor = elemento->pai->cor;
        elemento->pai->cor = PRETO;
        tio(elemento)->cor = PRETO;
        retiraDuploPreto(raiz, elemento);
        return;
    }

    // Caso 6b:
    if (cor(irmao(elemento)) == PRETO && cor(irmao(elemento)->esquerda) == VERMELHO && FilhoDireito(elemento)) {        
        rotacaoDireita(raiz, elemento->pai);
        elemento->pai->pai->cor = elemento->pai->cor;
        elemento->pai->cor = PRETO;
        tio(elemento)->cor = PRETO;
        retiraDuploPreto(raiz, elemento);
        return;
    }
}

// Função para retirar o duplo preto da árvore
void retiraDuploPreto (rb *raiz, rb elemento) {
	if (elemento == noNull) {
	    if (FilhoEsquerdo(elemento)) {
			elemento->pai->esquerda = NULL;
        } else {
			elemento->pai->direita = NULL;
        }
    } else {
		elemento->cor = PRETO;
    }
}

// Função para percorrer a árvore em ordem
void inOrder (rb raiz) {
    if (raiz != NULL) {
        inOrder(raiz->esquerda);
        printf("[%d]", raiz->chave);
        inOrder(raiz->direita);
    }
}

// Função para percorrer a árvore em pós-ordem
void posOrder (rb raiz) {
    if (raiz != NULL) {
        posOrder(raiz->esquerda);
        posOrder(raiz->direita);
        printf("[%d]", raiz->chave);
    }
}
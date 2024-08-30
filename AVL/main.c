#include "avl.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    arvore arvore1 = NULL;
    int opcao, valor, cresceu, diminuiu, qtd, i;

    printf("\n----------AVL--------\n");
    printf("1. INSERIR \n");
    printf("2. PREORDER \n");
    printf("3. POSORDER \n");
    printf("4. REMOVER \n");
    printf("99. SAIR \n");

    while (1) {
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite o valor a ser inserido:\n ");
                scanf("%d", &valor);
                arvore1 = inserir(arvore1, valor, &cresceu);
                break;
            case 2:
                printf("Pre ordem:\n");
                preOrder(arvore1);
                break;
            case 3:
                printf("Pos ordem:\n");
                posOrder(arvore1);
                break;
            case 4:
                printf("Digite o valor a ser removido:\n ");
                scanf("%d", &valor);
                arvore1 = remover(arvore1, valor, &diminuiu);
                break;
            default:
                printf("Opcao invalida!\n");
            case 99:
                exit(0);
                break;
        
        }
    }

    return 0;
}
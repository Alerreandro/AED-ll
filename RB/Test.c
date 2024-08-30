#include "rb.h"
#include <stdlib.h>
#include <stdio.h>

void liberarArvore(rb raiz);

int main (int argc, char* argv[]) {
    // Inicializa uma árvore vazia
    rb rubro = NULL;

    // Variáveis para opções do usuário
    int opcao, numero;
    
    // Exibe o menu de opções
    printf("\n----------Rubro Negra--------\n");
    printf("1. INSERIR \n");
    printf("2. PREORDER \n");
    printf("3. POSORDER \n");
    printf("4. REMOVER \n");
    printf("99. SAIR \n");

    // Loop principal para processar as opções do usuário
    while (1) {
        // Leitura da opção escolhida pelo usuário
        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao); 
        switch (opcao) {
            case 1:
                // Opção para inserir um novo elemento na árvore
                printf("Digite o numero para ser inserido: ");
                scanf("%d", &numero);
                rubro = inserir(&rubro, numero);
                break;

            case 2:
                // Opção para exibir a árvore em pré-ordem
                preOrder(rubro);
                break;

            case 3:
                // Opção para exibir a árvore em pós-ordem
                posOrder(rubro); // Certifique-se de que essa função está definida no rb.h
                break;

            case 4:
                // Opção para remover um elemento da árvore
                printf("Qual elemento que deseja remover? ");
                scanf("%d", &numero);
                remover(numero, &rubro);
                break;

            case 99:
                // Opção de sair
                liberarArvore(rubro); // Libera toda a árvore
                printf("Finalizado\n");
                exit(0);
                break;

            default:
                // Opção inválida
                printf("Opcao invalida, tente novamente.\n");
                break;
        }
    }
}

// Função para liberar a árvore recursivamente
void liberarArvore(rb raiz) {
    if (raiz != NULL) {
        liberarArvore(raiz->esquerda);
        liberarArvore(raiz->direita);
        free(raiz);
    }
}

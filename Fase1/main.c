/**
 * @file main.c
 * @author Daniel Vilaça (a16939@alunos.ipca.pt)
 * @brief
 * @version 1.0
 * @date 2025-03-30
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "antena.h"
#include "matriz.h"


/**
 * @brief Função principal do programa. Exibe menu para o utilizador interagir com a matriz e antenas
 *
 * Permite carregar matriz de ficheiro, inserir/remover antenas, visualizar matriz e os efeitos nefastos
 *
 * @return int Código de retorno do programa
 */
int main() {

    Antena *listaAntenas = NULL;
    int linhas = 0, colunas = 0;
    int opcao;
    char nomeFicheiro[100];

    do {

        printf("\n1. Load da matriz de ficheiro\n2. Inserir antena\n3. Remover antena\n4. Exibir Matriz\n5. Sair\nEscolha: ");
        scanf("%d", &opcao);

        if (opcao == 1) {

            printf("Nome do ficheiro: ");
            scanf("%s", nomeFicheiro);
            libertarAntenas(listaAntenas);
            listaAntenas = NULL;
            carregarMatrizDoFicheiro(nomeFicheiro, &listaAntenas, &linhas, &colunas);

        } else if (opcao == 2) {

            char freq;
            int linha, coluna;

            printf("Frequencia: ");
            scanf(" %c", &freq);
            printf("Linha: ");
            scanf("%d", &linha);
            printf("Coluna: ");
            scanf("%d", &coluna);
            inserirAntena(&listaAntenas, freq, linha - 1, coluna - 1);

        } else if (opcao == 3) {

            int linha, coluna;
            
            printf("Linha: ");
            scanf("%d", &linha);
            printf("Coluna: ");
            scanf("%d", &coluna);
            removerAntena(&listaAntenas, linha - 1, coluna - 1);

        } else if (opcao == 4) {

            exibirMatriz(listaAntenas, linhas, colunas);
        }

    } while (opcao != 5);

    libertarAntenas(listaAntenas);

    return 0;
}

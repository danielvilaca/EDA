/**
 * @file antena.c
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
#include <locale.h>
#include <stdbool.h>
#include "antena.h"


/**
 * @brief Cria uma nova antena com os dados fornecidos
 *
 * @param freq Char que representa a frequência/tipo de antena
 * @param linha Linha da matriz onde a antena será colocada
 * @param coluna Coluna da matriz onde a antena será colocada
 * @return Antena* Apontador para a nova antena criada
 */
Antena *criarAntena(char freq, int linha, int coluna) {
    Antena *nova = (Antena *)malloc(sizeof(Antena));
    if (!nova) {
        perror("Erro ao alocar memória");
        exit(1);
    }
    nova->freq = freq;
    nova->linha = linha;
    nova->coluna = coluna;
    nova->next = NULL;

    return nova;
}


/**
 * @brief Insere uma nova antena no final da lista ligada de antenas
 *
 * @param aux Apontador para o apontador da lista de antenas
 * @param freq Char que representa a frequência/tipo de antena
 * @param linha Linha onde será inserida
 * @param coluna Coluna onde será inserida
 */
bool inserirAntena(Antena **aux, char freq, int linha, int coluna) {
    Antena *nova = criarAntena(freq, linha, coluna);
    if (!nova) return false;
    if (*aux == NULL) {
        *aux = nova;
    } else {
        Antena *atual = *aux;
        while (atual->next != NULL)
            atual = atual->next;
        atual->next = nova;
    }
    return true;
}


/**
 * @brief Remove uma antena localizada numa posição específica da matriz
 *
 * @param aux Apontador para o apontador da lista de antenas
 * @param linha Linha da antena a remover
 * @param coluna Coluna da antena a remover
 */
bool removerAntena(Antena **aux, int linha, int coluna) {
    Antena *atual = *aux, *anterior = NULL;
    while (atual) {
        if (atual->linha == linha && atual->coluna == coluna) {
            if (anterior) anterior->next = atual->next;
            else *aux = atual->next;
            free(atual);
            return true;
        }
        anterior = atual;
        atual = atual->next;
    }
    return false;
}


/**
 * @brief Lista todas as antenas presentes na lista ligada
 *
 * @param aux Apontador para a lista de antenas
 */
void listarAntenas(Antena *aux) {
    setlocale(LC_ALL, "C");
    printf("\n%-12s %-10s %-10s\n", "Frequencia", "Linha", "Coluna");
    printf("%-12s %-10s %-10s\n", "-----------", "-----", "------");
    while (aux) {
        printf("%-12c %-10d %-10d\n", aux->freq, aux->linha + 1, aux->coluna + 1);
        aux = aux->next;
    }
}


/**
 * @brief Liberta a memória alocada para a lista de antenas
 *
 * @param aux Apontador para a lista de antenas
 */
void libertarAntenas(Antena *aux) {
    Antena *temp;
    while (aux) {
        temp = aux;
        aux = aux->next;
        free(temp);
    }
}

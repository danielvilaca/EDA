/**
 * @file antena.h
 * @author Daniel Vilaça (a16939@alunos.ipca.pt)
 * @brief
 * @version 1.0
 * @date 2025-03-30
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef ANTENA_H
#define ANTENA_H


/**
 * @brief Estrutura que representa uma antena.
 *
 */
typedef struct Antena {
    char freq;
    int linha, coluna;
    struct Antena *next;
} Antena;


/**
 * @brief Função que cria uma nova antena.
 *
 * @param freq Char que representa a frequência/tipo de antena
 * @param linha Linha da matriz onde a antena será colocada
 * @param coluna Coluna da matriz onde a antena será colocada
 * @return Antena* Apontador para a nova antena criada
 */
Antena *criarAntena(char freq, int linha, int coluna);


/**
 * @brief Função que insere uma nova antena na lista.
 *
 * @param aux Apontador para o apontador da lista de antenas
 * @param freq Char que representa a frequência/tipo da nova antena
 * @param linha Linha onde será inserida
 * @param coluna Coluna onde será inserida
 */
bool inserirAntena(Antena **aux, char freq, int linha, int coluna);


/**
 * @brief Função que remove uma antena localizada numa posição especifica da matriz.
 *
 * @param aux Apontador para o apontador da lista de antenas
 * @param linha Linha da antena a remover
 * @param coluna Coluna da antena a remover
 */
bool removerAntena(Antena **aux, int linha, int coluna);


/**
 * @brief Lista todas as antenas presentes na lista ligada
 *
 * @param aux Apontador para a lista de antenas
 */
void listarAntenas(Antena *aux);


/**
 * @brief Liberta a memória ocupada por todas as antenas da lista.
 *
 * @param aux Apontador para a lista de antenas.
 */
void libertarAntenas(Antena *aux);

#endif

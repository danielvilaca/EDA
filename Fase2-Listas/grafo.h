/**
 * @file grafo.h
 * @author Daniel Vilaça (a16939@alunos.ipca.pt)
 * @brief
 * @version 1.0
 * @date 2025-05-31
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef GRAFO_H
#define GRAFO_H

#include <stdbool.h>



typedef struct Adj {
    Vertice *dest; // Apontador para o vértice de destino da aresta
    Adj *prox; // Apontador para o próximo nó na lista de adjacências
}Adj;



typedef struct Vertice {
    int id; // Identificador único do vértice
    int x, y; // Coordenadas da antena na matriz
    char freq; // Frequência/identificador da antena
    Adj *lista; // Cabeça da lista de adjacências (arestas)
    Vertice *next; // Apontador para o próximo vértice na lista de todos os vértices

    bool visited; // Flag auxiliar para marcar vértices visitados em procuras (DFS/BFS)
}Vertice;


typedef struct {
    Vertice *head; // Apontador para o primeiro vértice da lista encadeada de vértices
    int n_vertices; // Contador do número de vértices atualmente no grafo
} Grafo;


/**
 * @brief Inicializa um grafo vazio.
 *
 * @param g Apontador para o grafo a inicializar.
 */
void inicializaGrafo(Grafo *g);

/**
 * @brief Adiciona um novo vértice (antena) ao grafo.
 *
 * @param g Apontador para o grafo onde o vértice será inserido.
 * @param x Coordenada x (coluna) da antena.
 * @param y Coordenada y (linha) da antena.
 * @param freq Char que representa a frequência/identificador da antena.
 * @return int ID atribuído ao novo vértice se a inserção for bem-sucedida, -1 se ocorrer falha de alocação.
 */
int adicionaVertice(Grafo *g, int x, int y, char freq);

/**
 * @brief Adiciona uma aresta não dirigida entre dois vértices do grafo.
 *
 * @param g Apontador para o grafo onde se quer criar a aresta.
 * @param orig_id ID do vértice de origem.
 * @param dest_id ID do vértice de destino.
 * @return true Se a aresta for criada com sucesso ou já existir.
 * @return false Se algum ID for inválido, se as frequências forem diferentes, se tentar ligar o vértice a si próprio, ou se falhar alocação.
 */
bool adicionaAresta(Grafo *g, int orig_id, int dest_id);

/**
 * @brief Imprime o grafo de forma legível, listando cada vértice e as suas adjacências.
 *
 * @param g Apontador para o grafo a ser impresso.
 */
void imprimeGrafo(Grafo *g);

/**
 * @brief Executa Depth-First Search (DFS) a partir de um vértice dado.
 *
 * @param g Apontador para o grafo onde será feita a DFS.
 * @param start_id ID do vértice inicial da procura.
 * @return true Se a procura foi executada (mesmo que só visite um vértice).
 * @return false Se `start_id` não corresponder a nenhum vértice.
 */
bool dfs(Grafo *g, int start_id);

/**
 * @brief Executa Breadth-First Search (BFS) a partir de um vértice dado.
 *
 * @param g Apontador para o grafo onde será feita a BFS.
 * @param start_id ID do vértice inicial da procura.
 * @return true Se a procura foi executada (mesmo que só visite um vértice).
 * @return false Se `start_id` não corresponder a nenhum vértice ou falhar alocação.
 */
bool bfs(Grafo *g, int start_id);

/**
 * @brief Lista todos os caminhos simples entre dois vértices de mesma frequência.
 *
 * @param g Apontador para o grafo onde serão procurados os caminhos.
 * @param origem ID do vértice de origem.
 * @param destino ID do vértice de destino.
 * @return true Se os caminhos foram listados (ou se a invocação foi válida).
 * @return false Se algum ID for inválido ou frequências diferentes.
 */
bool listarCaminhos(Grafo *g, int origem, int destino);

/**
 * @brief Lista todas as combinações de pares de antenas de frequências distintas.
 *
 * @param g Apontador para o grafo onde se procura as interseções.
 * @param freq1 Char representando a primeira frequência.
 * @param freq2 Char representando a segunda frequência.
 */
void listarIntersecoes(Grafo *g, char freq1, char freq2);

/**
 * @brief Remove um vértice do grafo, juntamente com todas as arestas incidentes.
 *
 * @param g Apontador para o grafo onde o vértice será removido.
 * @param id Identificador do vértice a ser removido.
 * @return true Se o vértice existia e foi removido com sucesso.
 * @return false Se não existir vértice com esse ID.
 */
bool removerVertice(Grafo *g, int id);

#endif

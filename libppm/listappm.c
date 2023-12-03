#include <stdio.h>
#include <stdlib.h>

#include "internal.h"
#include "libppm.h"
#include "types.h"

void NoDuploPonto_libera(NoDuploPonto *lista) {
    free(lista);
}

// Lista de Cor
ListaCor *ListaCor_cria() {
    ListaCor *lista = (ListaCor *)malloc(sizeof(*lista));
    lista->fim = NULL;
    lista->inicio = NULL;
    lista->tamanho = 0;
    return lista;
}

void ListaCor_insere_sem_repeticao(ListaCor *lista, rgb cor) {
    NodeCor *cursor = lista->inicio;
    while (cursor != NULL) {
        if (cor_compara(cursor->cor, cor)) {
            return;
        }
        cursor = cursor->proximo;
    }
    ListaCor_insere_fim(lista, cor);
}

void ListaCor_insere_inicio(ListaCor *lista, rgb cor) {
    NodeCor *novo = (NodeCor *)malloc(sizeof(NodeCor));
    novo->cor = cor;
    if (lista->inicio != NULL) {
        lista->inicio->anterior = novo;
        novo->proximo = lista->inicio;
        novo->anterior = NULL;
        lista->inicio = novo;
    } else {
        lista->fim = novo;
        lista->inicio = lista->fim;
        novo->proximo = NULL;
        novo->anterior = novo->proximo;
    }
    lista->tamanho++;
}

void ListaCor_insere_fim(ListaCor *lista, rgb cor) {
    NodeCor *novo = (NodeCor *)malloc(sizeof(NodeCor));
    novo->cor = cor;
    if (lista->fim != NULL) {
        lista->fim->proximo = novo;
        novo->anterior = lista->fim;
        novo->proximo = NULL;
        lista->fim = novo;
    } else {
        lista->inicio = lista->fim = novo;
        novo->proximo = NULL;
        novo->anterior = novo->proximo;
    }
    lista->tamanho++;
}

void ListaCor_remove_inicio(ListaCor *lista) {
    NodeCor *cursor = lista->inicio;
    if (cursor != NULL) {
        lista->inicio = cursor->proximo;
        if (lista->inicio == NULL) {
            lista->fim = NULL;
        }
        free(cursor);
        lista->tamanho--;
    }
}

void ListaCor_remove_fim(ListaCor *lista) {
    NodeCor *cursor = lista->fim;
    if (cursor != NULL) {
        lista->fim = cursor->anterior;
        if (lista->fim == NULL) {
            lista->inicio = NULL;
        }
        free(cursor);
        lista->tamanho--;
    }
}

int ListaCor_busca_indice(ListaCor *l, rgb cor) {
    NodeCor *cursor = l->inicio;
    int indice = 0;
    while (cursor != NULL) {
        if (cor_compara(cursor->cor, cor)) {
            return indice;
        }
        indice++;
        cursor = cursor->proximo;
    }
    return -1;
}

void ListaCor_libera(ListaCor *lista) {
    NodeCor *cursor = lista->inicio;
    while (cursor != NULL) {
        lista->inicio = cursor->proximo;
        free(cursor);
        cursor = lista->inicio;
    }
    lista->fim = lista->inicio = NULL;
    lista->tamanho = 0;
    free(lista);
    lista = NULL;
}

/*
        Linhas sao listas de pontos com a finalidade
        de desenhar cada um desses pontos, um a um,

*/
Linha *Linha_aloca() {
    Linha *linha = (Linha *)malloc(sizeof(Linha));
    linha->primeiro = NULL;
    linha->ultimo = NULL;
    return linha;
}

bool Linha_vazia(Linha *linha) {
    return (linha->primeiro == NULL);
}

void Linha_adiciona(Linha *linha, Ponto ponto) {
    ListaPonto *lista_ponto = (ListaPonto *)malloc(sizeof(ListaPonto));
    if (lista_ponto == NULL) {
        printf("Sem memoria\n");
        Linha_libera(linha);
        exit(1);
    }
    lista_ponto->ponto = ponto;
    lista_ponto->proximo = NULL;
    if (Linha_vazia(linha)) {
        linha->primeiro = lista_ponto;
        linha->ultimo = lista_ponto;
    } else {
        linha->ultimo->proximo = lista_ponto;
        linha->ultimo = lista_ponto;
    }
}

void Linha_cria(Linha *linha, Ponto ponto_inicio, Ponto ponto_final) {
    if (ponto_inicio.x - ponto_final.x == 0) {
        if (ponto_inicio.y > ponto_final.y) {
            int_troca(&ponto_inicio.y, &ponto_final.y);
        }
        for (int i = ponto_inicio.y; i <= ponto_final.y; i++) {
            Linha_adiciona(linha, Ponto_cria_estatico(ponto_inicio.x, i));
        }
    } else {
        int anterior_x = -1;
        int anterior_y = -1;
        int delta_x = ponto_inicio.x - ponto_final.x;
        int delta_y = ponto_final.y - ponto_inicio.y;
        int centro = ponto_final.x * ponto_inicio.y - ponto_inicio.x * ponto_final.y;
        if (ponto_inicio.x > ponto_final.x) {
            int_troca(&ponto_inicio.x, &ponto_final.x);
        }
        for (double d_contador = ponto_inicio.x; d_contador <= ponto_final.x; d_contador += 0.05) {
            int novo_y = float_aproximacao(-((int)d_contador * delta_y + centro) / delta_x);
            if (novo_y != anterior_y || float_aproximacao(d_contador) != anterior_x) {
                Linha_adiciona(linha, Ponto_cria_estatico(float_aproximacao(d_contador), novo_y));
                anterior_x = float_aproximacao(d_contador);
                anterior_y = novo_y;
            }
        }
    }
}

void Linha_remove(Linha *linha, Ponto ponto) {
    ListaPonto *cursor = linha->primeiro;
    ListaPonto *no_a_remover;
    while (cursor != NULL && (ponto.x != cursor->ponto.x || ponto.y != cursor->ponto.y)) {
        no_a_remover = cursor;
        cursor = cursor->proximo;
    }
    if (cursor != NULL) {
        if (linha->ultimo == cursor) {
            linha->ultimo = no_a_remover;
        }
        if (no_a_remover != NULL) {
            no_a_remover->proximo = cursor->proximo;
            free(cursor);
        } else {
            linha->primeiro = cursor->proximo;
            free(cursor);
        }
    }
}

void Linha_libera(Linha *linha) {
    ListaPonto *cursor = linha->primeiro;
    while (cursor != NULL) {
        ListaPonto *anterior = cursor;
        cursor = cursor->proximo;
        free(anterior);
    }
    free(linha);
}

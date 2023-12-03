#include <stdio.h>
#include <stdlib.h>

#include "internal.h"
#include "libdesenho.h"
#include "libppm.h"
#include "libvetorial.h"

/*
        -Poligonos
        Sao estruturas com um ponteiro para o inicio
        de um lista de pontos, com a finalidade de
        desenhar um poligono que passa por esses
        pontos na ordem
*/

Poligono *Poligono_cria() {
    Poligono *poligono = (Poligono *)malloc(sizeof(*poligono));
    poligono->primeiro = NULL;
    poligono->centro = (Ponto *)malloc(sizeof(Ponto));
    return poligono;
}

bool Poligono_vazio(Poligono *poligono) {
    return (poligono->primeiro == NULL);
}

void Poligono_insere(Poligono *poligono, Ponto ponto) {
    NoDuploPonto *no_novo = (NoDuploPonto *)malloc(sizeof(NoDuploPonto));
    if (no_novo == NULL) {
        printf("Sem memoria\n");
        Poligono_libera(poligono);
        exit(1);
    }
    no_novo->ponto = ponto;
    no_novo->proximo = poligono->primeiro;
    no_novo->anterior = NULL;
    if (!Poligono_vazio(poligono)) {
        poligono->primeiro->anterior = no_novo;
    }
    poligono->primeiro = no_novo;
}

Ponto Poligono_pop(Poligono *poligono) {
    if (Poligono_vazio(poligono)) {
        printf("Poligono vazio\n");
        return Ponto_cria_estatico(-1, -1);
    } else {
        Ponto ponto = poligono->primeiro->ponto;
        NoDuploPonto *tmp = poligono->primeiro;
        poligono->primeiro = poligono->primeiro->proximo;
        free(tmp);
        if (poligono->primeiro != NULL) {
            poligono->primeiro->anterior = NULL;
        }
        return ponto;
    }
}

NoDuploPonto *Poligono_busca(Poligono *poligono, Ponto ponto) {
    NoDuploPonto *cursor = poligono->primeiro;
    while (cursor != NULL) {
        if (Ponto_compara(cursor->ponto, ponto)) {
            break;
        }
        cursor = cursor->proximo;
    }
    return cursor;
}

void Poligono_remove(Poligono *poligono, Ponto ponto) {
    NoDuploPonto *no_ponto = Poligono_busca(poligono, ponto);
    if (no_ponto != NULL) {
        if (no_ponto->anterior != NULL)
            no_ponto->anterior->proximo = no_ponto->proximo;
        if (no_ponto->proximo != NULL)
            no_ponto->proximo->anterior = no_ponto->anterior;
        if (no_ponto == poligono->primeiro)
            poligono->primeiro = no_ponto->proximo;
        free(no_ponto);
    }
}

void Poligono_esvazia(Poligono *poligono) {
    while (!Poligono_vazio(poligono)) {
        Poligono_pop(poligono);
    }
}

void Poligono_copia(Poligono *origem, Poligono *destino) {
    Poligono_esvazia(destino);
    NoDuploPonto *cursor = origem->primeiro;
    while (cursor != NULL) {
        Poligono_insere(destino, cursor->ponto);
        cursor = cursor->proximo;
    }
    destino->centro = origem->centro;
}

void Poligono_libera(Poligono *poligono) {
    if (poligono == NULL)
        return;
    NoDuploPonto *cursor = poligono->primeiro;
    while (cursor != NULL) {
        poligono->primeiro = cursor->proximo;
        free(cursor);
        cursor = poligono->primeiro;
    }
    free(poligono->centro);
    free(poligono);
}

void vetorial_retangulo(Poligono *poligono, Ponto centro, int altura, int largura) {
    Poligono_esvazia(poligono);
    *(poligono->centro) = centro;
    Poligono_insere(poligono, Ponto_cria_estatico(centro.x - altura / 2, centro.y - largura / 2));
    Poligono_insere(poligono, Ponto_cria_estatico(centro.x - altura / 2, centro.y + largura / 2));
    Poligono_insere(poligono, Ponto_cria_estatico(centro.x + altura / 2, centro.y + largura / 2));
    Poligono_insere(poligono, Ponto_cria_estatico(centro.x + altura / 2, centro.y - largura / 2));
}

void vetorial_triangulo(Poligono *poligono, Ponto centro, int altura, int base) {
    Poligono_esvazia(poligono);
    *(poligono->centro) = centro;
    Poligono_insere(poligono, Ponto_cria_estatico(centro.x + altura / 2, centro.y - base / 2));
    Poligono_insere(poligono, Ponto_cria_estatico(centro.x - altura / 2, centro.y));
    Poligono_insere(poligono, Ponto_cria_estatico(centro.x + altura / 2, centro.y + base / 2));
}

void vetorial_losango(Poligono *poligono, Ponto centro, int altura, int largura) {
    Poligono_esvazia(poligono);
    *(poligono->centro) = centro;
    Poligono_insere(poligono, Ponto_cria_estatico(centro.x, centro.y - largura / 2));
    Poligono_insere(poligono, Ponto_cria_estatico(centro.x - altura / 2, centro.y));
    Poligono_insere(poligono, Ponto_cria_estatico(centro.x, centro.y + largura / 2));
    Poligono_insere(poligono, Ponto_cria_estatico(centro.x + altura / 2, centro.y));
}

void vetorial_trapezio(Poligono *poligono, Ponto centro, int base1, int base2, int altura) {
    Poligono_esvazia(poligono);
    *(poligono->centro) = centro;
    Poligono_insere(poligono, Ponto_cria_estatico(centro.x - altura / 2, centro.y - base1 / 2));
    Poligono_insere(poligono, Ponto_cria_estatico(centro.x - altura / 2, centro.y + base1 / 2));
    Poligono_insere(poligono, Ponto_cria_estatico(centro.x + altura / 2, centro.y + base2 / 2));
    Poligono_insere(poligono, Ponto_cria_estatico(centro.x + altura / 2, centro.y - base2 / 2));
}

void vetorial_estrela(Poligono *poligono, Ponto ponto, int x, int y) {
    Poligono_esvazia(poligono);
    *(poligono->centro) = ponto;
    Poligono_insere(poligono, Ponto_cria_estatico(ponto.x - x, ponto.y));
    Poligono_insere(poligono, Ponto_cria_estatico(ponto.x - x / 2, ponto.y - y / 3));
    Poligono_insere(poligono, Ponto_cria_estatico(ponto.x - x / 2, ponto.y - y));
    Poligono_insere(poligono, Ponto_cria_estatico(ponto.x, ponto.y - 2 * y / 3));
    Poligono_insere(poligono, Ponto_cria_estatico(ponto.x + x / 2, ponto.y - y));
    Poligono_insere(poligono, Ponto_cria_estatico(ponto.x + x / 2, ponto.y - y / 3));
    Poligono_insere(poligono, Ponto_cria_estatico(ponto.x + x, ponto.y));
    Poligono_insere(poligono, Ponto_cria_estatico(ponto.x + x / 2, ponto.y + y / 3));
    Poligono_insere(poligono, Ponto_cria_estatico(ponto.x + x / 2, ponto.y + y));
    Poligono_insere(poligono, Ponto_cria_estatico(ponto.x, ponto.y + 2 * y / 3));
    Poligono_insere(poligono, Ponto_cria_estatico(ponto.x - x / 2, ponto.y + y));
    Poligono_insere(poligono, Ponto_cria_estatico(ponto.x - x / 2, ponto.y + y / 3));
}

void vetorial_translada(Poligono *poligono, int vertical, int horizontal) {
    *(poligono->centro) = Ponto_cria_estatico(poligono->centro->x + vertical, poligono->centro->y + horizontal);
    NoDuploPonto *cursor = poligono->primeiro;
    while (cursor != NULL) {
        cursor->ponto.x += vertical;
        cursor->ponto.y += horizontal;
        cursor = cursor->proximo;
    }
}

void vetorial_rotaciona(Poligono *poligono, float graus) {
    NoDuploPonto *cursor;
    for (cursor = poligono->primeiro; cursor != NULL; cursor = cursor->proximo)
        cursor->ponto = Ponto_vira(*(poligono->centro), cursor->ponto, graus);
}

void vetorial_escala(Poligono *poligono, double escala) {
    escala -= 1.0;
    NoDuploPonto *cursor = poligono->primeiro;
    while (cursor != NULL) {
        cursor->ponto.x = (cursor->ponto.x - poligono->centro->x) * escala + cursor->ponto.x;
        cursor->ponto.y = (cursor->ponto.y - poligono->centro->y) * escala + cursor->ponto.y;
        cursor = cursor->proximo;
    }
}

void Poligono_cor_desenha(PPM *imagem, Poligono *poligono, rgb cor) {
    NoDuploPonto *cursor = poligono->primeiro->proximo;
    linha_cor_desenha(imagem, poligono->primeiro->ponto, cursor->ponto, cor);
    while (cursor->proximo != NULL) {
        linha_cor_desenha(imagem, cursor->ponto, cursor->proximo->ponto, cor);
        cursor = cursor->proximo;
        cursor->anterior->anterior = cursor->anterior->proximo = NULL;
        NoDuploPonto_libera(cursor->anterior);
        cursor->anterior = NULL;
    }
    linha_cor_desenha(imagem, cursor->ponto, poligono->primeiro->ponto, cor);
    NoDuploPonto_libera(cursor);
    poligono->primeiro->proximo = NULL;
    NoDuploPonto_libera(poligono->primeiro);
    poligono->primeiro = NULL;
}

#include <stdio.h>
#include <stdlib.h>

#include "internal.h"
#include "libdesenho.h"

PPM* PPM_cria_com_dimensoes(Dimensao2D tamanho, int channelRange, rgb cor) {
    PPM* imagem = (PPM*)malloc(sizeof(*imagem));
    imagem->cabecalho = PPMHeader_cria(tamanho.altura, tamanho.largura, channelRange, Key_PPM);
    imagem->pixel = rgb2d_malloc(*imagem->cabecalho->tamanho);
    for (int i = 0; i < tamanho.altura; i++) {
        for (int j = 0; j < tamanho.largura; j++) {
            imagem->pixel[i][j] = cor;
        }
    }
    return imagem;
}

// Cor
void ponto_cor_desenha(PPM* imagem, Ponto ponto, rgb cor) {
    if (ponto.x >= 0 && ponto.x < imagem->cabecalho->tamanho->altura && ponto.y >= 0 && ponto.y < imagem->cabecalho->tamanho->largura) {
        imagem->pixel[ponto.x][ponto.y] = cor;
    }
}

void linha_cor_desenha(PPM* imagem, Ponto ponto_inicial, Ponto ponto_final, rgb cor) {
    if (int_valor_absoluto(ponto_inicial.x - ponto_final.x) < imagem->cabecalho->tamanho->altura / 500) {
        if (ponto_inicial.y > ponto_final.y) {
            int_troca(&ponto_inicial.y, &ponto_final.y);
        }
        for (int i = ponto_inicial.y; i <= ponto_final.y; i++) {
            ponto_cor_desenha(imagem, Ponto_cria_estatico(ponto_inicial.x, i), cor);
        }
    } else {
        int c = ponto_final.x * ponto_inicial.y - ponto_inicial.x * ponto_final.y;
        int delta_x = ponto_inicial.x - ponto_final.x;
        int delta_y = ponto_final.y - ponto_inicial.y;
        if (ponto_inicial.x > ponto_final.x) {
            int_troca(&ponto_inicial.x, &ponto_final.x);
        }
        double d_contador = (double)ponto_inicial.x;
        while (d_contador <= ponto_final.x) {
            ponto_cor_desenha(imagem, Ponto_cria_estatico(d_contador, -(d_contador * delta_y + c) / delta_x), cor);
            d_contador += 0.05;
        }
    }
}

void curva_cor_desenha(PPM* imagem, Ponto ponto_inicial, Ponto ponto_medio, Ponto ponto_final, rgb cor) {
    int limite = Ponto_distancia(ponto_inicial, ponto_medio) + Ponto_distancia(ponto_final, ponto_medio);
    for (int i = 0; i < limite; i++) {
        double d_contador = (double)i;
        Ponto ab = Ponto_interpolacao_linear(ponto_inicial, ponto_medio, d_contador / limite);
        Ponto bc = Ponto_interpolacao_linear(ponto_medio, ponto_final, d_contador / limite);
        Ponto ab2 = Ponto_interpolacao_linear(ponto_inicial, ponto_medio, (d_contador + 1) / limite);
        Ponto bc2 = Ponto_interpolacao_linear(ponto_medio, ponto_final, (d_contador + 1) / limite);

        Ponto interpolado1 = Ponto_interpolacao_linear(ab, bc, d_contador / limite);
        Ponto interpolado2 = Ponto_interpolacao_linear(ab2, bc2, (d_contador + 1) / limite);

        linha_cor_desenha(imagem, interpolado1, interpolado2, cor);
    }
}

void lista_linha_cor_desenha(PPM* imagem, Linha* linha, rgb cor) {
    ListaPonto* cursor = linha->primeiro;
    while (!Linha_vazia(linha)) {
        ponto_cor_desenha(imagem, linha->primeiro->ponto, cor);
        cursor = cursor->proximo;
        free(linha->primeiro);
        linha->primeiro = cursor;
    }
}

void triangulo_cor_desenha(PPM* imagem, Ponto centro, int altura, int base, rgb cor) {
    Ponto ponto[] = {
        Ponto_cria_estatico(centro.x + altura / 2, centro.y - base / 2),
        Ponto_cria_estatico(centro.x - altura / 2, centro.y),
        Ponto_cria_estatico(centro.x + altura / 2, centro.y + base / 2),
    };
    linha_cor_desenha(imagem, ponto[0], ponto[1], cor);
    linha_cor_desenha(imagem, ponto[1], ponto[2], cor);
    linha_cor_desenha(imagem, ponto[2], ponto[0], cor);
}

void retangulo_cor_desenha(PPM* imagem, Ponto centro, int altura, int largura, rgb cor) {
    Ponto ponto[] = {
        Ponto_cria_estatico(centro.x - altura / 2, centro.y - largura / 2),
        Ponto_cria_estatico(centro.x - altura / 2, centro.y + largura / 2),
        Ponto_cria_estatico(centro.x + altura / 2, centro.y + largura / 2),
        Ponto_cria_estatico(centro.x + altura / 2, centro.y - largura / 2),
    };
    linha_cor_desenha(imagem, ponto[0], ponto[1], cor);
    linha_cor_desenha(imagem, ponto[1], ponto[2], cor);
    linha_cor_desenha(imagem, ponto[2], ponto[3], cor);
    linha_cor_desenha(imagem, ponto[3], ponto[0], cor);
}

void losango_cor_desenha(PPM* imagem, Ponto centro, int altura, int largura, rgb cor) {
    Ponto ponto[] = {
        Ponto_cria_estatico(centro.x, centro.y - largura / 2),
        Ponto_cria_estatico(centro.x - altura / 2, centro.y),
        Ponto_cria_estatico(centro.x, centro.y + largura / 2),
        Ponto_cria_estatico(centro.x + altura / 2, centro.y),
    };
    linha_cor_desenha(imagem, ponto[0], ponto[1], cor);
    linha_cor_desenha(imagem, ponto[1], ponto[2], cor);
    linha_cor_desenha(imagem, ponto[2], ponto[3], cor);
    linha_cor_desenha(imagem, ponto[3], ponto[0], cor);
}

void trapezio_cor_desenha(PPM* imagem, Ponto centro, int b1, int b2, int altura, rgb cor) {
    Ponto ponto[] = {
        Ponto_cria_estatico(centro.x - altura / 2, centro.y - b1 / 2),
        Ponto_cria_estatico(centro.x - altura / 2, centro.y + b1 / 2),
        Ponto_cria_estatico(centro.x + altura / 2, centro.y + b2 / 2),
        Ponto_cria_estatico(centro.x + altura / 2, centro.y - b2 / 2),
    };
    linha_cor_desenha(imagem, ponto[0], ponto[1], cor);
    linha_cor_desenha(imagem, ponto[1], ponto[2], cor);
    linha_cor_desenha(imagem, ponto[2], ponto[3], cor);
    linha_cor_desenha(imagem, ponto[3], ponto[0], cor);
}

void estrela_cor_desenha(PPM* imagem, Ponto p, int x, int y, rgb cor) {
    int i;
    Ponto ponto[] = {
        Ponto_cria_estatico(p.x - x, p.y),
        Ponto_cria_estatico(p.x - x / 2, p.y - y / 3),
        Ponto_cria_estatico(p.x - x / 2, p.y - y),
        Ponto_cria_estatico(p.x, p.y - 2 * y / 3),
        Ponto_cria_estatico(p.x + x / 2, p.y - y),
        Ponto_cria_estatico(p.x + x / 2, p.y - y / 3),
        Ponto_cria_estatico(p.x + x, p.y),
        Ponto_cria_estatico(p.x + x / 2, p.y + y / 3),
        Ponto_cria_estatico(p.x + x / 2, p.y + y),
        Ponto_cria_estatico(p.x, p.y + 2 * y / 3),
        Ponto_cria_estatico(p.x - x / 2, p.y + y),
        Ponto_cria_estatico(p.x - x / 2, p.y + y / 3),
    };
    for (i = 0; i < 12; i++) {
        linha_cor_desenha(imagem, ponto[i], ponto[(i + 1) % 12], cor);
    }
}

void circulo_cor_desenha(PPM* imagem, Ponto centro, int raio, rgb cor) {
    int x = raio;
    int y = 0;
    int err = 0;
    while (x >= y) {
        ponto_cor_desenha(imagem, Ponto_cria_estatico(centro.x + x, centro.y + y), cor);
        ponto_cor_desenha(imagem, Ponto_cria_estatico(centro.x + y, centro.y + x), cor);
        ponto_cor_desenha(imagem, Ponto_cria_estatico(centro.x - y, centro.y + x), cor);
        ponto_cor_desenha(imagem, Ponto_cria_estatico(centro.x - x, centro.y + y), cor);
        ponto_cor_desenha(imagem, Ponto_cria_estatico(centro.x - x, centro.y - y), cor);
        ponto_cor_desenha(imagem, Ponto_cria_estatico(centro.x - y, centro.y - x), cor);
        ponto_cor_desenha(imagem, Ponto_cria_estatico(centro.x + y, centro.y - x), cor);
        ponto_cor_desenha(imagem, Ponto_cria_estatico(centro.x + x, centro.y - y), cor);
        y += 1;
        err += 1 + 2 * y;
        if (2 * (err - x) + 1 > 0) {
            x -= 1;
            err += 1 - 2 * x;
        }
    }
}

void elipse_cor_desenha(PPM* imagem, Ponto centro, int altura, int largura, rgb cor) {
    Ponto ponto_inicial = Ponto_cria_estatico(centro.x + altura / 2, centro.y - largura / 2);
    Ponto ponto_final = Ponto_cria_estatico(centro.x - altura / 2, centro.y + largura / 2);

    int valor_absoluto_x = abs(ponto_final.x - ponto_inicial.x);
    int valor_absoluto_y = abs(ponto_final.y - ponto_inicial.y);

    int bit1 = valor_absoluto_y & 1;

    long delta_x = 4 * (1 - valor_absoluto_x) * valor_absoluto_y * valor_absoluto_y;
    long delta_y = 4 * (bit1 + 1) * valor_absoluto_x * valor_absoluto_x;
    long erro = delta_x + delta_y + bit1 * valor_absoluto_x * valor_absoluto_x;

    if (ponto_inicial.x > ponto_final.x) {
        ponto_inicial.x = ponto_final.x;
        ponto_final.x += valor_absoluto_x;
    }
    if (ponto_inicial.y > ponto_final.y) {
        ponto_inicial.y = ponto_final.y;
    }
    ponto_inicial.y += (valor_absoluto_y + 1) / 2;
    ponto_final.y = ponto_inicial.y - bit1;
    valor_absoluto_x *= 8 * valor_absoluto_x;
    bit1 = 8 * valor_absoluto_y * valor_absoluto_y;

    do {
        ponto_cor_desenha(imagem, Ponto_cria_estatico(ponto_final.x, ponto_inicial.y), cor);
        ponto_cor_desenha(imagem, Ponto_cria_estatico(ponto_inicial.x, ponto_inicial.y), cor);
        ponto_cor_desenha(imagem, Ponto_cria_estatico(ponto_inicial.x, ponto_final.y), cor);
        ponto_cor_desenha(imagem, Ponto_cria_estatico(ponto_final.x, ponto_final.y), cor);
        long erro2 = 2 * erro;
        if (erro2 <= delta_y) {
            ponto_inicial.y++;
            ponto_final.y--;
            delta_y += valor_absoluto_x;
            erro += delta_y;
        }
        if (erro2 >= delta_x || 2 * erro > delta_y) {
            ponto_inicial.x++;
            ponto_final.x--;
            erro += delta_x += bit1;
        }
    } while (ponto_inicial.x <= ponto_final.x);

    while (ponto_inicial.y - ponto_final.y < valor_absoluto_y) {
        ponto_cor_desenha(imagem, Ponto_cria_estatico(ponto_inicial.x - 1, ponto_inicial.y), cor);
        ponto_cor_desenha(imagem, Ponto_cria_estatico(ponto_final.x + 1, ponto_inicial.y++), cor);
        ponto_cor_desenha(imagem, Ponto_cria_estatico(ponto_inicial.x - 1, ponto_final.y), cor);
        ponto_cor_desenha(imagem, Ponto_cria_estatico(ponto_final.x + 1, ponto_final.y--), cor);
    }
}

// Formas preenchidas com cor
void curva_cor_preenchido_desenha(PPM* imagem, Ponto ponto_inicial, Ponto ponto_medio, Ponto ponto_final, rgb cor) {
    double lim = Ponto_distancia(ponto_inicial, ponto_medio) + Ponto_distancia(ponto_final, ponto_medio);
    for (int i = 0; i <= (int)lim; i++) {
        Ponto interpolado = Ponto_interpolacao_linear(ponto_medio, Ponto_medio(ponto_inicial, ponto_final), (double)i / lim);
        curva_cor_desenha(
            imagem,
            ponto_inicial,
            interpolado,
            ponto_final,
            cor);
    }
}

void triangulo_cor_preenchido_desenha(PPM* imagem, Ponto centro, int altura, int base, rgb cor) {
    Ponto a = Ponto_cria_estatico(centro.x - altura / 2, centro.y);
    Ponto b = Ponto_cria_estatico(centro.x + altura / 2, centro.y - base / 2);
    Ponto c = Ponto_cria_estatico(centro.x + altura / 2, centro.y + base / 2);
    Linha* linha1 = Linha_aloca();
    Linha* linha2 = Linha_aloca();
    Linha_cria(linha1, a, b);
    Linha_cria(linha2, a, c);
    ListaPonto* cursor1 = linha1->primeiro;
    ListaPonto* cursor2 = linha2->primeiro;
    while (cursor1 != NULL && cursor2 != NULL) {
        linha_cor_desenha(imagem, cursor1->ponto, cursor2->ponto, cor);
        cursor1 = cursor1->proximo;
        cursor2 = cursor2->proximo;
    }
    Linha_libera(linha1);
    Linha_libera(linha2);
}

void retangulo_cor_preenchido_desenha(PPM* imagem, Ponto centro, int altura, int largura, rgb cor) {
    Ponto ponto1 = Ponto_cria_estatico(centro.x - altura / 2, centro.y + largura / 2);
    Ponto ponto2 = Ponto_cria_estatico(centro.x - altura / 2, centro.y - largura / 2);

    while (ponto1.x < centro.x + altura / 2) {
        linha_cor_desenha(imagem, ponto1, ponto2, cor);
        ponto1.x++;
        ponto2.x++;
    }
}

void losango_cor_preenchido_desenha(PPM* imagem, Ponto centro, int altura, int largura, rgb cor) {
    Linha* linhas[4];
    for (int i = 0; i < 4; i++) {
        linhas[i] = Linha_aloca();
    }

    Ponto a = Ponto_cria_estatico(centro.x, centro.y - largura / 2);
    Ponto b = Ponto_cria_estatico(centro.x - altura / 2, centro.y);
    Ponto c = Ponto_cria_estatico(centro.x, centro.y + largura / 2);
    Ponto d = Ponto_cria_estatico(centro.x + altura / 2, centro.y);

    Linha_cria(linhas[0], a, b);
    Linha_cria(linhas[1], b, c);
    Linha_cria(linhas[2], a, d);
    Linha_cria(linhas[3], c, d);

    for (int i = 0; i <= 2; i += 2) {
        ListaPonto* cursor1 = linhas[i]->primeiro;
        ListaPonto* cursor2 = linhas[i + 1]->primeiro;
        while (cursor1 != NULL && cursor2 != NULL) {
            linha_cor_desenha(imagem, cursor1->ponto, cursor2->ponto, cor);
            cursor1 = cursor1->proximo;
            cursor2 = cursor2->proximo;
        }
    }
    for (int i = 0; i < 4; i++) {
        Linha_libera(linhas[i]);
    }
}

void circulo_cor_preenchido_desenha(PPM* imagem, Ponto centro, int raio, rgb cor) {
    int x = raio;
    int y = 0;
    int err = 0;
    while (x >= y) {
        linha_cor_desenha(imagem, Ponto_cria_estatico(centro.x - x, centro.y - y), Ponto_cria_estatico(centro.x - x, centro.y + y), cor);
        linha_cor_desenha(imagem, Ponto_cria_estatico(centro.x - y, centro.y - x), Ponto_cria_estatico(centro.x - y, centro.y + x), cor);
        linha_cor_desenha(imagem, Ponto_cria_estatico(centro.x + y, centro.y - x), Ponto_cria_estatico(centro.x + y, centro.y + x), cor);
        linha_cor_desenha(imagem, Ponto_cria_estatico(centro.x + x, centro.y - y), Ponto_cria_estatico(centro.x + x, centro.y + y), cor);
        y += 1;
        err += 1 + 2 * y;
        if (2 * (err - x) + 1 > 0) {
            x -= 1;
            err += 1 - 2 * x;
        }
    }
}

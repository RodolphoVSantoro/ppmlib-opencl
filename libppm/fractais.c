#include <math.h>
#include <stdlib.h>

#include "internal.h"
#include "libdesenho.h"
#include "libppm.h"
#include "libvetorial.h"

static void fractal_espiral_desenha_recursivo(PPM* imagem, Ponto ponto_1, Ponto ponto_2, double tamanho) {
    tamanho += 180.0;
    Ponto ponto_medio = Ponto_medio(ponto_1, ponto_2);
    double distancia_meio = Ponto_distancia(ponto_1, ponto_medio);
    Ponto ponto_referencia = Ponto_cria_estatico(ponto_1.x, ponto_1.y + sqrt(distancia_meio * distancia_meio * (1 + graus_seno(60.0))));
    Ponto ponto_1_virado = Ponto_vira(ponto_1, ponto_referencia, tamanho);
    curva_desenha(imagem, ponto_1, ponto_1_virado, ponto_2);
    if (Ponto_distancia(ponto_1, ponto_1_virado) > 10) {
        fractal_espiral_desenha_recursivo(imagem, ponto_2, ponto_medio, tamanho);
    }
}

void fractal_espiral_desenha(PPM* imagem, Ponto ponto_1, Ponto ponto_2) {
    Ponto ponto_medio = Ponto_medio(ponto_1, ponto_2);
    int delta_x = (ponto_2.x - ponto_1.x);
    double distancia_meio = Ponto_distancia(ponto_1, ponto_medio);
    double tamanho = 0.0;
    if (delta_x == 0) {
        tamanho = 90.0;
    } else {
        // sei lá o que é fa
        int fa = (ponto_2.y - ponto_1.y) / delta_x;
        tamanho = rad2graus(atan(fa));
    }
    Ponto ponto_referencia = Ponto_cria_estatico(ponto_1.x, ponto_1.y + sqrt(distancia_meio * distancia_meio * (1.0 + graus_seno(60.0))));
    Ponto ponto_1_virado = Ponto_vira(ponto_1, ponto_referencia, tamanho);
    curva_desenha(imagem, ponto_1, ponto_1_virado, ponto_2);
    if (Ponto_distancia(ponto_1, ponto_1_virado) > 10) {
        fractal_espiral_desenha_recursivo(imagem, ponto_2, ponto_medio, tamanho);
    }
}

void fractal_arvore_binaria_desenha(PPM* imagem, Ponto ponto, int tamanho) {
    Ponto ponto_cima = Ponto_cria_estatico(ponto.x - tamanho, ponto.y - tamanho / 2);
    Ponto ponto_baixo = Ponto_cria_estatico(ponto.x - tamanho, ponto.y + tamanho / 2);
    linha_desenha(imagem, ponto, ponto_cima);
    linha_desenha(imagem, ponto, ponto_baixo);
    if (tamanho > 1) {
        fractal_arvore_binaria_desenha(imagem, ponto_cima, tamanho / 2);
        fractal_arvore_binaria_desenha(imagem, ponto_baixo, tamanho / 2);
    }
}

void fractal_arvore_ternaria_desenha(PPM* imagem, Ponto ponto, int tamanho) {
    Ponto ponto_cima = Ponto_cria_estatico(ponto.x - tamanho, ponto.y - tamanho / 2);
    Ponto ponto_meio = Ponto_cria_estatico(ponto.x - tamanho, ponto.y);
    Ponto ponto_baixo = Ponto_cria_estatico(ponto.x - tamanho, ponto.y + tamanho / 2);
    linha_desenha(imagem, ponto, ponto_cima);
    linha_desenha(imagem, ponto, ponto_meio);
    linha_desenha(imagem, ponto, ponto_baixo);
    if (tamanho > 1) {
        fractal_arvore_ternaria_desenha(imagem, ponto_cima, tamanho / 3);
        fractal_arvore_ternaria_desenha(imagem, ponto_meio, tamanho / 3);
        fractal_arvore_ternaria_desenha(imagem, ponto_baixo, tamanho / 3);
    }
}

void fractal_circulo_recursivo_desenha(PPM* imagem, Ponto ponto, int raio) {
    circulo_desenha(imagem, ponto, raio);
    if (raio > 6) {
        fractal_circulo_recursivo_desenha(imagem, Ponto_cria_estatico(ponto.x + raio, ponto.y), raio / 2);
        fractal_circulo_recursivo_desenha(imagem, Ponto_cria_estatico(ponto.x - raio, ponto.y), raio / 2);
        fractal_circulo_recursivo_desenha(imagem, Ponto_cria_estatico(ponto.x, ponto.y + raio), raio / 2);
        fractal_circulo_recursivo_desenha(imagem, Ponto_cria_estatico(ponto.x, ponto.y - raio), raio / 2);
    }
}

void fractal_estrela_recursiva_desenha(PPM* imagem, Ponto ponto, int raio) {
    elipse_desenha(imagem, ponto, raio, 16 * raio / 9);
    if (raio > 6) {
        fractal_estrela_recursiva_desenha(imagem, Ponto_cria_estatico(ponto.x + raio, ponto.y), raio / 2);
        fractal_estrela_recursiva_desenha(imagem, Ponto_cria_estatico(ponto.x - raio, ponto.y), raio / 2);
        fractal_estrela_recursiva_desenha(imagem, Ponto_cria_estatico(ponto.x, ponto.y + raio), raio / 2);
        fractal_estrela_recursiva_desenha(imagem, Ponto_cria_estatico(ponto.x, ponto.y - raio), raio / 2);
    }
}

void fractal_cantor_desenha(PPM* imagem, Ponto ponto, int tamanho) {
    linha_desenha(imagem, ponto, Ponto_cria_estatico(ponto.x, ponto.y + tamanho));
    if (tamanho > 9) {
        tamanho /= 7;
        fractal_cantor_desenha(imagem, Ponto_cria_estatico(ponto.x + 50, ponto.y), tamanho);
        fractal_cantor_desenha(imagem, Ponto_cria_estatico(ponto.x + 50, ponto.y + 2 * tamanho), tamanho);
        fractal_cantor_desenha(imagem, Ponto_cria_estatico(ponto.x + 50, ponto.y + 4 * tamanho), tamanho);
        fractal_cantor_desenha(imagem, Ponto_cria_estatico(ponto.x + 50, ponto.y + 6 * tamanho), tamanho);
    }
}

void apaga_koch(PPM* imagem, Ponto ponto_inicial, Ponto ponto_final) {
    Ponto s = Ponto_cria_estatico((2 * ponto_inicial.x + ponto_final.x) / 3, (2 * ponto_inicial.y + ponto_final.y) / 3);
    Ponto t = Ponto_cria_estatico((2 * ponto_final.x + ponto_inicial.x) / 3, (2 * ponto_final.y + ponto_inicial.y) / 3);
    linha_cor_desenha(imagem, s, t, rgb_cria(255, 255, 255));
    if (Ponto_distancia(ponto_inicial, ponto_final) >= 30) {
        apaga_koch(imagem, ponto_inicial, s);
        apaga_koch(imagem, t, ponto_final);
    }
}

void fractal_koch_desenha(PPM* imagem, Ponto ponto_inicial, Ponto ponto_final) {
    Ponto s = Ponto_cria_estatico((2 * ponto_inicial.x + ponto_final.x) / 3, (2 * ponto_inicial.y + ponto_final.y) / 3);
    Ponto t = Ponto_cria_estatico((2 * ponto_final.x + ponto_inicial.x) / 3, (2 * ponto_final.y + ponto_inicial.y) / 3);
    Ponto v = Ponto_vira(s, t, 60);
    if (Ponto_distancia(ponto_inicial, ponto_final) > 30) {
        fractal_koch_desenha(imagem, ponto_inicial, s);
        fractal_koch_desenha(imagem, s, v);
        fractal_koch_desenha(imagem, v, t);
        fractal_koch_desenha(imagem, t, ponto_final);
    } else {
        linha_desenha(imagem, ponto_inicial, s);
        linha_desenha(imagem, s, v);
        linha_desenha(imagem, v, t);
        linha_desenha(imagem, t, ponto_final);
    }
}

void fractal_koch_2_desenha(PPM* imagem, Ponto ponto_inicial, Ponto ponto_final) {
    Ponto s = Ponto_cria_estatico((2 * ponto_inicial.x + ponto_final.x) / 3, (2 * ponto_inicial.y + ponto_final.y) / 3);
    Ponto t = Ponto_cria_estatico((2 * ponto_final.x + ponto_inicial.x) / 3, (2 * ponto_final.y + ponto_inicial.y) / 3);
    Ponto v = Ponto_vira(s, t, 300);
    if (Ponto_distancia(ponto_inicial, ponto_final) > 30) {
        fractal_koch_2_desenha(imagem, ponto_inicial, s);
        fractal_koch_2_desenha(imagem, s, v);
        fractal_koch_2_desenha(imagem, v, t);
        fractal_koch_2_desenha(imagem, t, ponto_final);
    } else {
        linha_desenha(imagem, ponto_inicial, s);
        linha_desenha(imagem, s, v);
        linha_desenha(imagem, v, t);
        linha_desenha(imagem, t, ponto_final);
    }
}

void fractal_dragon_cor_desenha(PPM* imagem, Ponto ponto_inicial, Ponto ponto_final, rgb cor) {
    const double raiz5 = 1.732050808;
    int x = float_aproximacao((ponto_final.x * ((2 * raiz5 - 1) / 2) + 3 * ponto_inicial.x) / (3 + ((2 * raiz5 - 1) / 2)));
    int y = float_aproximacao((ponto_final.y * ((2 * raiz5 - 1) / 2) + 3 * ponto_inicial.y) / (3 + ((2 * raiz5 - 1) / 2)));
    Ponto c = Ponto_cria_estatico(x, y);
    if (Ponto_distancia(ponto_inicial, ponto_final) > 10) {
        c = Ponto_vira(ponto_final, c, 45);
        fractal_dragon_cor_cima_desenha(imagem, ponto_inicial, c, cor);
        fractal_dragon_cor_baixo_desenha(imagem, c, ponto_final, cor);
    }
}

void fractal_dragon_cor_cima_desenha(PPM* imagem, Ponto ponto_inicial, Ponto ponto_final, rgb cor) {
    const double raiz5 = 1.732050808;
    int x = float_aproximacao((ponto_final.x * ((2 * raiz5 - 1) / 2) + 3 * ponto_inicial.x) / (3 + ((2 * raiz5 - 1) / 2)));
    int y = float_aproximacao((ponto_final.y * ((2 * raiz5 - 1) / 2) + 3 * ponto_inicial.y) / (3 + ((2 * raiz5 - 1) / 2)));
    Ponto c = Ponto_cria_estatico(x, y);
    if (Ponto_distancia(ponto_inicial, ponto_final) > 10) {
        c = Ponto_vira(ponto_final, c, 45);
        fractal_dragon_cor_cima_desenha(imagem, ponto_inicial, c, cor);
        fractal_dragon_cor_baixo_desenha(imagem, c, ponto_final, cor);
    } else {
        linha_cor_desenha(imagem, ponto_inicial, c, cor);
        linha_cor_desenha(imagem, c, ponto_final, cor);
    }
}

void fractal_dragon_cor_baixo_desenha(PPM* imagem, Ponto ponto_inicial, Ponto ponto_final, rgb cor) {
    const double raiz5 = 1.732050808;
    int x = float_aproximacao((ponto_final.x * ((2 * raiz5 - 1) / 2) + 3 * ponto_inicial.x) / (3 + ((2 * raiz5 - 1) / 2)));
    int y = float_aproximacao((ponto_final.y * ((2 * raiz5 - 1) / 2) + 3 * ponto_inicial.y) / (3 + ((2 * raiz5 - 1) / 2)));
    Ponto c = Ponto_cria_estatico(x, y);
    if (Ponto_distancia(ponto_inicial, ponto_final) > 10) {
        c = Ponto_vira(ponto_final, c, 315);
        fractal_dragon_cor_cima_desenha(imagem, ponto_inicial, c, cor);
        fractal_dragon_cor_baixo_desenha(imagem, c, ponto_final, cor);
    } else {
        linha_cor_desenha(imagem, ponto_inicial, c, cor);
        linha_cor_desenha(imagem, c, ponto_final, cor);
    }
}

void fractal_dragon_desenha(PPM* imagem, Ponto ponto_inicial, Ponto ponto_final) {
    const double raiz5 = 1.732050808;
    int x = float_aproximacao((ponto_final.x * ((2 * raiz5 - 1) / 2) + 3 * ponto_inicial.x) / (3 + ((2 * raiz5 - 1) / 2)));
    int y = float_aproximacao((ponto_final.y * ((2 * raiz5 - 1) / 2) + 3 * ponto_inicial.y) / (3 + ((2 * raiz5 - 1) / 2)));
    Ponto c = Ponto_cria_estatico(x, y);
    if (Ponto_distancia(ponto_inicial, ponto_final) > 10) {
        c = Ponto_vira(ponto_final, c, 45);
        fractal_dragon_cima_desenha(imagem, ponto_inicial, c);
        fractal_dragon_baixo_desenha(imagem, c, ponto_final);
    }
}

void fractal_dragon_cima_desenha(PPM* imagem, Ponto ponto_inicial, Ponto ponto_final) {
    const double raiz5 = 1.732050808;
    int x = float_aproximacao((ponto_final.x * ((2 * raiz5 - 1) / 2) + 3 * ponto_inicial.x) / (3 + ((2 * raiz5 - 1) / 2)));
    int y = float_aproximacao((ponto_final.y * ((2 * raiz5 - 1) / 2) + 3 * ponto_inicial.y) / (3 + ((2 * raiz5 - 1) / 2)));
    Ponto c = Ponto_cria_estatico(x, y);
    if (Ponto_distancia(ponto_inicial, ponto_final) > 10) {
        c = Ponto_vira(ponto_final, c, 45);
        fractal_dragon_cima_desenha(imagem, ponto_inicial, c);
        fractal_dragon_baixo_desenha(imagem, c, ponto_final);
    } else {
        linha_desenha(imagem, ponto_inicial, c);
        linha_desenha(imagem, c, ponto_final);
    }
}

void fractal_dragon_baixo_desenha(PPM* imagem, Ponto ponto_inicial, Ponto ponto_final) {
    const double raiz5 = 1.732050808;
    int x = float_aproximacao((ponto_final.x * ((2 * raiz5 - 1) / 2) + 3 * ponto_inicial.x) / (3 + ((2 * raiz5 - 1) / 2)));
    int y = float_aproximacao((ponto_final.y * ((2 * raiz5 - 1) / 2) + 3 * ponto_inicial.y) / (3 + ((2 * raiz5 - 1) / 2)));
    Ponto c = Ponto_cria_estatico(x, y);
    if (Ponto_distancia(ponto_inicial, ponto_final) > 10) {
        c = Ponto_vira(ponto_final, c, 315);
        fractal_dragon_cima_desenha(imagem, ponto_inicial, c);
        fractal_dragon_baixo_desenha(imagem, c, ponto_final);
    } else {
        linha_desenha(imagem, ponto_inicial, c);
        linha_desenha(imagem, c, ponto_final);
    }
}

void fractal_levy_dragon_desenha(PPM* imagem, Ponto ponto_inicial, Ponto ponto_final) {
    const double raiz5 = 1.732050808;
    int x = float_aproximacao((ponto_final.x * ((2 * raiz5 - 1) / 2) + 3 * ponto_inicial.x) / (3 + ((2 * raiz5 - 1) / 2)));
    int y = float_aproximacao((ponto_final.y * ((2 * raiz5 - 1) / 2) + 3 * ponto_inicial.y) / (3 + ((2 * raiz5 - 1) / 2)));
    Ponto c = Ponto_cria_estatico(x, y);
    if (Ponto_distancia(ponto_inicial, ponto_final) > 10) {
        c = Ponto_vira(ponto_final, c, 45);
        fractal_levy_dragon_desenha(imagem, ponto_inicial, c);
        fractal_levy_dragon_desenha(imagem, c, ponto_final);
    } else {
        linha_desenha(imagem, ponto_inicial, c);
        linha_desenha(imagem, c, ponto_final);
    }
}

void fractal_fc_desenha(PPM* imagem, Ponto a, Ponto b) {
    Ponto c = Ponto_cria_estatico((3 * a.x + b.x) / 4, (3 * a.y + b.y) / 4);
    Ponto d = Ponto_vira(a, c, 90);
    c = Ponto_vira(a, c, 270);
    Ponto e = Ponto_cria_estatico((a.x + 3 * b.x) / 4, (a.y + 3 * b.y) / 4);
    Ponto f = Ponto_vira(b, e, 90);
    e = Ponto_vira(b, e, 270);
    linha_desenha(imagem, a, b);
    if (Ponto_distancia(a, b) > 10) {
        fractal_fc_desenha(imagem, c, d);
        fractal_fc_desenha(imagem, e, f);
    }
}

void fractal_pit_desenha(PPM* imagem, Ponto centro, int lado, float graus) {
    Poligono* poligono = Poligono_cria();
    vetorial_retangulo(poligono, centro, lado, lado);
    vetorial_rotaciona(poligono, graus);
    Poligono_desenha(imagem, poligono);
    Poligono_libera(poligono);
    Ponto e = Ponto_cria_estatico(centro.x - (lado * (2.236067977) / 2.0), centro.y);
    Ponto d = Ponto_cria_estatico(centro.x - (lado * (2.236067977) / 2.0), centro.y);
    e = Ponto_vira(centro, e, graus - 26.5);
    d = Ponto_vira(centro, d, graus + 26.5);
    if (lado > 20) {
        fractal_pit_desenha(imagem, d, lado * (1.414213562 / 2.0), graus + 45);
        fractal_pit_desenha(imagem, e, lado * (1.414213562 / 2.0), graus - 45);
    }
}

void fractal_rec_desenha(PPM* imagem, Ponto ponto, int tamanho) {
    circulo_desenha(imagem, ponto, tamanho);
    tamanho /= 2;
    if (tamanho > 2) {
        fractal_rec_desenha(imagem, Ponto_cria_estatico(ponto.x - tamanho, ponto.y - tamanho), tamanho);
        fractal_rec_desenha(imagem, Ponto_cria_estatico(ponto.x - tamanho, ponto.y + tamanho), tamanho);
    }
}

void fractal_rec2_desenha(PPM* imagem, Ponto ponto, int tamanho) {
    circulo_desenha(imagem, ponto, tamanho);
    tamanho /= 2;
    if (tamanho > 10) {
        fractal_rec2_desenha(imagem, Ponto_cria_estatico(ponto.x - tamanho, ponto.y - tamanho), tamanho);
        fractal_rec2_desenha(imagem, Ponto_cria_estatico(ponto.x - tamanho, ponto.y + tamanho), tamanho);
        fractal_rec2_desenha(imagem, Ponto_cria_estatico(ponto.x + tamanho, ponto.y - tamanho), tamanho);
        fractal_rec2_desenha(imagem, Ponto_cria_estatico(ponto.x + tamanho, ponto.y + tamanho), tamanho);
    }
}

void fractal_rec3baixo_desenha(PPM* imagem, Ponto ponto, int tamanho) {
    circulo_desenha(imagem, ponto, tamanho);
    tamanho /= 2;
    if (tamanho > 2) {
        fractal_rec3baixo_desenha(imagem, Ponto_cria_estatico(ponto.x + tamanho, ponto.y - tamanho), tamanho);
        fractal_rec3baixo_desenha(imagem, Ponto_cria_estatico(ponto.x + tamanho, ponto.y + tamanho), tamanho);
    }
}

void fractal_rec3cima_desenha(PPM* imagem, Ponto ponto, int tamanho) {
    circulo_desenha(imagem, ponto, tamanho);
    tamanho /= 2;
    if (tamanho > 2) {
        fractal_rec3cima_desenha(imagem, Ponto_cria_estatico(ponto.x - tamanho, ponto.y - tamanho), tamanho);
        fractal_rec3cima_desenha(imagem, Ponto_cria_estatico(ponto.x - tamanho, ponto.y + tamanho), tamanho);
    }
}

void fractal_rec4_desenha(PPM* imagem, Ponto ponto, int tamanho) {
    circulo_desenha(imagem, ponto, tamanho);
    if (tamanho > 10) {
        fractal_rec4_desenha(imagem, Ponto_cria_estatico(ponto.x - tamanho, ponto.y), tamanho / 2);
        fractal_rec4_desenha(imagem, Ponto_cria_estatico(ponto.x + tamanho, ponto.y), tamanho / 2);
        fractal_rec4_desenha(imagem, Ponto_cria_estatico(ponto.x + tamanho, ponto.y + tamanho), tamanho / 2);
        fractal_rec4_desenha(imagem, Ponto_cria_estatico(ponto.x + tamanho, ponto.y - tamanho), tamanho / 2);
    }
}

void fractal_rec5_desenha(PPM* imagem, Ponto ponto, int tamanho, rgb cor) {
    triangulo_cor_desenha(imagem, ponto, tamanho, tamanho, cor);
    if (tamanho > 10) {
        fractal_rec5_desenha(imagem, Ponto_cria_estatico(ponto.x - tamanho / 4, ponto.y), tamanho / 2, cor);
        fractal_rec5_desenha(imagem, Ponto_cria_estatico(ponto.x + tamanho / 4, ponto.y + tamanho / 4), tamanho / 2, cor);
        fractal_rec5_desenha(imagem, Ponto_cria_estatico(ponto.x + tamanho / 4, ponto.y - tamanho / 4), tamanho / 2, cor);
    }
}

void fractal_rec6_desenha(PPM* imagem, Ponto ponto, int tamanho) {
    circulo_desenha(imagem, ponto, tamanho);
    linha_cor_desenha(imagem, ponto, Ponto_cria_estatico(ponto.x - tamanho, ponto.y - tamanho), rgb_cria(rand() % 255, rand() % 255, rand() % 255));
    linha_cor_desenha(imagem, ponto, Ponto_cria_estatico(ponto.x - tamanho, ponto.y + tamanho), rgb_cria(rand() % 255, rand() % 255, rand() % 255));
    linha_cor_desenha(imagem, ponto, Ponto_cria_estatico(ponto.x + tamanho, ponto.y - tamanho), rgb_cria(rand() % 255, rand() % 255, rand() % 255));
    linha_cor_desenha(imagem, ponto, Ponto_cria_estatico(ponto.x + tamanho, ponto.y + tamanho), rgb_cria(rand() % 255, rand() % 255, rand() % 255));
    if (tamanho > 43) {
        fractal_rec6_desenha(imagem, Ponto_cria_estatico(ponto.x - tamanho * 3 / 2, ponto.y - tamanho * 3 / 2), tamanho / 2);
        fractal_rec6_desenha(imagem, Ponto_cria_estatico(ponto.x - tamanho * 3 / 2, ponto.y + tamanho * 3 / 2), tamanho / 2);
        fractal_rec6_desenha(imagem, Ponto_cria_estatico(ponto.x + tamanho * 3 / 2, ponto.y - tamanho * 3 / 2), tamanho / 2);
        fractal_rec6_desenha(imagem, Ponto_cria_estatico(ponto.x + tamanho * 3 / 2, ponto.y + tamanho * 3 / 2), tamanho / 2);
    }
}

void fractal_rec7_desenha(PPM* imagem, Ponto ponto, int tamanho, char direcao_x, char direcao_y) {
    if (direcao_x == 0 && direcao_y == 0) {
        return;
    }
    if (direcao_x == -1) {
        linha_desenha(imagem, ponto, Ponto_cria_estatico(ponto.x - tamanho, ponto.y));
    }
    if (direcao_x == 1) {
        linha_desenha(imagem, ponto, Ponto_cria_estatico(ponto.x + tamanho, ponto.y));
    }
    if (direcao_y == -1) {
        linha_desenha(imagem, ponto, Ponto_cria_estatico(ponto.x, ponto.y - tamanho));
    }
    if (direcao_y == 1) {
        linha_desenha(imagem, ponto, Ponto_cria_estatico(ponto.x, ponto.y + tamanho));
    }

    if (tamanho >= 1500) {
        return;
    }
    if (direcao_x == -1) {
        fractal_rec7_desenha(imagem, Ponto_cria_estatico(ponto.x - tamanho, ponto.y), tamanho * 1.1, 0, -1);
    }
    if (direcao_x == 1) {
        fractal_rec7_desenha(imagem, Ponto_cria_estatico(ponto.x + tamanho, ponto.y), tamanho * 1.1, 0, 1);
    }
    if (direcao_y == -1) {
        fractal_rec7_desenha(imagem, Ponto_cria_estatico(ponto.x, ponto.y - tamanho), tamanho * 1.1, 1, 0);
    }
    if (direcao_y == 1) {
        fractal_rec7_desenha(imagem, Ponto_cria_estatico(ponto.x, ponto.y + tamanho), tamanho * 1.1, -1, 0);
    }
}

void fractal_rec8_desenha(PPM* imagem, Ponto ponto, int tamanho) {
    linha_desenha(imagem, ponto, Ponto_cria_estatico(ponto.x + tamanho, ponto.y));
    tamanho /= 3;
    if (tamanho > 9) {
        // raiz de 2 = 1,732050808
        fractal_rec8_desenha(imagem, Ponto_cria_estatico(ponto.x + 3 * tamanho / 2, ponto.y - tamanho * 1.732050808 / 2), tamanho);
        fractal_rec8_desenha(imagem, Ponto_cria_estatico(ponto.x + 2 * tamanho, ponto.y - tamanho), tamanho);
        fractal_rec8_desenha(imagem, Ponto_cria_estatico(ponto.x + 3 * tamanho / 2, ponto.y + tamanho * 1.732050808 / 2), tamanho);
        fractal_rec8_desenha(imagem, Ponto_cria_estatico(ponto.x + 2 * tamanho, ponto.y + tamanho), tamanho);
    }
}

#include <stdio.h>

#include "../libppm/libdesenho.h"
#include "../libppm/libppm.h"

int main() {
    Dimensao2D dimensoes = Dimensao2D_cria_estatico(1080, 1920);
    PPM* img = PPM_cria_com_dimensoes(dimensoes, 255, _cor_branco);

    Ponto ponto_inicial = Ponto_cria_estatico(500, 1000);
    Ponto ponto_meio_baixo = Ponto_cria_estatico(400, 900);
    Ponto ponto_meio_cima = Ponto_cria_estatico(600, 1100);
    Ponto ponto_final = Ponto_cria_estatico(500, 1300);

    double rotacao = 360;
    int iteracoes = 8;

    for (int i = 0; i < iteracoes; i++) {
        double angulo = rotacao / iteracoes;
        ponto_final = Ponto_vira(ponto_inicial, ponto_final, angulo);

        ponto_meio_cima = Ponto_vira(ponto_inicial, ponto_meio_cima, angulo);
        curva_cor_preenchido_desenha(img, ponto_inicial, ponto_meio_cima, ponto_final, _cor_laranja);

        ponto_meio_baixo = Ponto_vira(ponto_inicial, ponto_meio_baixo, angulo);
        curva_cor_preenchido_desenha(img, ponto_inicial, ponto_meio_baixo, ponto_final, _cor_laranja);
    }

    circulo_cor_preenchido_desenha(img, ponto_inicial, 75, _cor_amarelo);

    PPM_grava("imgs/girando.ppm", img);
    PPM_libera(img);
    return 0;
}

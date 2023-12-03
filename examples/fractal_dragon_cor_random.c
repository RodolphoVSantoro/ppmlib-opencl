#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../libppm/libdesenho.h"
#include "../libppm/libppm.h"

int main() {
    srand(time(NULL));
    Dimensao2D dimensoes = Dimensao2D_cria_estatico(1000, 1000);
    PPM* img = PPM_cria_com_dimensoes(dimensoes, 255, _cor_branco);

    Ponto ponto_i = Ponto_cria_estatico(500, 500);
    Ponto ponto_f = Ponto_cria_estatico(900, 900);

    for (int i = 0; i < 10; i++) {
        rgb cor = cor_aleatoria();
        fractal_dragon_cor_desenha(img, ponto_i, ponto_f, cor);
        ponto_i.x -= i * 30;
        ponto_i.y += i * 30;
    }

    PPM_grava("imgs/teste.ppm", img);
    PPM_libera(img);
    return 0;
}
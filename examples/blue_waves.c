#include <stdio.h>

#include "../libppm/libdesenho.h"
#include "../libppm/libppm.h"

int main() {
    Dimensao2D dimensoes = Dimensao2D_cria_estatico(1000, 1000);
    PPM* img = PPM_cria_com_dimensoes(dimensoes, 255, _cor_branco);

    Ponto ponto = {500, 500};

    for (int i = 0; i < 1000; i += 10) {
        for (int j = 0; j < 1000; j += 10) {
            ponto.y = j / 2 * 53;
            circulo_cor_desenha(img, ponto, i * 4, rgb_cria(0, i, 255));
        }
    }

    PPM_grava("imgs/blue_waves.ppm", img);
    PPM_libera(img);
    return 0;
}
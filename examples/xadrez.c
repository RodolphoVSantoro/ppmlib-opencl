#include "libdesenho.h"
#include "libppm.h"
#define TAMANHO_CASA 100

int main() {
    Dimensao2D tamanho_tabuleiro = Dimensao2D_cria_estatico(800, 800);
    PPM* imagem = PPM_cria_com_dimensoes(tamanho_tabuleiro, 255, _cor_branco);

    Dimensao2D tamanho_casa = Dimensao2D_cria_estatico(TAMANHO_CASA, TAMANHO_CASA);

    int i, j;
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            if ((i + j) % 2 == 0) {
                Ponto centro = Ponto_cria_estatico(i * tamanho_casa.largura + TAMANHO_CASA / 2, j * tamanho_casa.altura + TAMANHO_CASA / 2);
                retangulo_preenchido_desenha(imagem, centro, TAMANHO_CASA, TAMANHO_CASA);
            }
        }
    }

    PPM_grava("imgs/xadrez.ppm", imagem);
    PPM_libera(imagem);

    return 0;
}
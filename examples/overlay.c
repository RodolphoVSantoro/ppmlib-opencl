#include "../libppm/libdesenho.h"
#include "../libppm/libefeito.h"
#include "../libppm/libppm.h"

int main() {
    PPM* imagem = PPM_leitura("imgs/dark.ppm");
    PPM* imagem2 = PPM_leitura("imgs/light.ppm");
    PPM* imagem3 = efeito_cria_imagem_overlay(imagem, imagem2);

    PPM_libera(imagem);
    PPM_libera(imagem2);

    int altura = imagem3->cabecalho->tamanho->altura;
    int largura = imagem3->cabecalho->tamanho->largura;
    Dimensao2D dimensao = {largura, altura};
    PPM* imagem4 = PPM_cria_com_dimensoes(dimensao, 255, rgb_cria(0, 0, 0));
    PPM* imagem5 = efeito_cria_imagem_overlay(imagem3, imagem4);
    PPM_libera(imagem3);
    PPM_libera(imagem4);

    PPM_grava("imgs/overlay.ppm", imagem5);
    PPM_libera(imagem5);
    return 0;
}

#include "../libppm/libdesenho.h"
#include "../libppm/libefeito.h"
#include "../libppm/libppm.h"

int main() {
    int altura = 1080, largura = 1920;
    Dimensao2D tamanho = Dimensao2D_cria_estatico(altura, largura);
    int canal = 255;
    PPM* imagem = PPM_cria_com_dimensoes(tamanho, canal, _cor_verde_livre_discurso);
    Ponto c = Ponto_cria_estatico(altura / 2, largura / 2);
    losango_cor_preenchido_desenha(imagem, c, altura * 10 / 12, largura * 3 / 4, _cor_amarelo);
    circulo_cor_preenchido_desenha(imagem, c, altura * 99 / 324, _cor_azul);
    efeito_grava_blur_gaussiano("imgs/bandeira_blur.ppm", imagem, 8);
    PPM_grava("imgs/bandeira.ppm", imagem);
    PPM* imagem2 = efeito_cria_imagem_blur_gaussiano(imagem, 8);
    PPM_libera(imagem);
    efeito_aplica_negativo(&imagem2);
    PPM_grava("imgs/bandeira2.ppm", imagem2);
    PPM_libera(imagem2);
    return 0;
}

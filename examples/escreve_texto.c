#include "../libppm/libdesenho.h"
#include "../libppm/libefeito.h"
#include "../libppm/libppm.h"
#include "../libppm/libvetorial.h"

int main() {
    // int altura = 480, largura = 740;
    // Dimensao2D tamanho = Dimensao2D_cria_estatico(altura, largura);
    //  PPM *imagem = PPM_cria_com_dimensoes(tamanho, 255, _cor_branco);
    PPM *imagem = PPM_leitura("imgs/tree.ppm");

    Ponto ponto1 = Ponto_cria_estatico(220, 300);
    circulo_cor_preenchido_desenha(imagem, ponto1, 60, _cor_amarelo);
    //
    Ponto ponto2 = Ponto_cria_estatico(220, 350);
    circulo_cor_preenchido_desenha(imagem, ponto2, 60, _cor_amarelo);
    //
    Ponto centro = Ponto_cria_estatico(100, 320);
    retangulo_cor_preenchido_desenha(imagem, centro, 200, 100, _cor_amarelo);
    //
    Ponto centro3 = Ponto_cria_estatico(100, 600);
    circulo_cor_preenchido_desenha(imagem, centro3, 60, _cor_amarelo);

    efeito_aplica_blur_mint(&imagem, 5);
    Ponto ponto_escrita = Ponto_cria_estatico(250, 10);
    fonte_escreve_string(imagem, "xnove foi torrado", ponto_escrita, 8);
    PPM_grava("imgs/efeito.ppm", imagem);
    PPM_libera(imagem);
    return 0;
}

#include "../libppm/libdesenho.h"
#include "../libppm/libppm.h"

int main() {
    Dimensao2D tamanho = Dimensao2D_cria_estatico(1080, 1920);
    PPM *imagem = PPM_cria_com_dimensoes(tamanho, 255, _cor_branco);
    Ponto centro = Ponto_cria_estatico(500, 200);
    fractal_estrela_recursiva_desenha(imagem, centro, 500);
    PPM_grava("imgs/fractalEstrelaRecursiva.ppm", imagem);
    PPM_libera(imagem);
}
#include "../libppm/libefeito.h"
#include "../libppm/libppm.h"

int main() {
    PPM* imagem = PPM_leitura("imgs/Maldives.ppm");
    PPM* imagem2 = efeito_cria_imagem_ampliado(imagem, 0.1);
    PPM_libera(imagem);
    efeito_aplica_bitmap(&imagem2);
    efeito_aplica_negativo(&imagem2);
    PPM_grava("imgs/beach.ppm", imagem2);
    PPM_libera(imagem2);
    return 0;
}
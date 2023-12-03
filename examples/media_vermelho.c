#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../libppm/libppm.h"

double vermelho_medio(PPM* imagem) {
    double avg, n = 0;
    for (int i = 0; i < imagem->cabecalho->tamanho->altura; i++) {
        for (int j = 0; j < imagem->cabecalho->tamanho->largura; j++) {
            avg += imagem->pixel[i][j].red;
            n += 1.0;
        }
    }
    return avg / n;
}

int main() {
    FILE* arquivo_resultados = fopen("output/res.txt", "a");
    if (arquivo_resultados == NULL) {
        printf("Erro ao abrir arquivo de resultados");
        exit(1);
    }
    const char* fname = "imgs/blue_waves.ppm";
    PPM* img = PPM_leitura(fname);
    double media = vermelho_medio(img);
    fprintf(arquivo_resultados, "%s - %lf\n", fname, media);
    fclose(arquivo_resultados);
    PPM_libera(img);
    return 0;
}
#include "libppm.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "internal.h"

FILE *fopen_or_crash(char fname[], char modo[]) {
    FILE *arquivo = fopen(fname, modo);
    if (arquivo == NULL) {
        printf("Falha ao abrir o arquivo %s\n", fname);
        exit(1);
    }
    return arquivo;
}

void string_copia(char *destino, char *original) {
    int i;
    for (i = 0; original[i] != 0; i++) {
        destino[i] = original[i];
    }
    destino[i] = 0;
}

int string_compara(char *string1, char *string2) {
    int i;
    for (i = 0; string1[i] != 0 && string2[i] != 0; i++) {
        if (string1[i] < string2[i]) {
            return -1;
        } else if (string1[i] > string2[i]) {
            return 1;
        }
    }
    if (string1[i] == string2[i]) {
        return 0;
    } else if (string2[i] != 0) {
        return -1;
    } else {
        return 1;
    }
}

int float_aproximacao(float valor) {
    int valorTruncado = valor;
    float diferenca = valor - (float)valorTruncado;
    if (valor >= 0) {
        return diferenca >= 0.5 ? valorTruncado + 1 : valorTruncado;
    } else {
        return diferenca <= 0.5 ? valorTruncado - 1 : valorTruncado;
    }
}

int int_valor_absoluto(int n) {
    return n >= 0 ? n : -n;
}

void int_troca(int *a, int *b) {
    *a = *a + *b;
    *b = *a - *b;
    *a = *a - *b;
}

float graus_seno(float graus) {
    return sin(graus2rad(graus));
}

float graus_coseno(float graus) {
    return cos(graus2rad(graus));
}

int int_potencia(int base, int expoente) {
    int resultado = 1;
    for (int i = 0; i < expoente; i++) {
        resultado *= base;
    }
    return resultado;
}

rgb rgb_cria(uchar red, uchar green, uchar blue) {
    rgb pixel;
    pixel.red = red;
    pixel.green = green;
    pixel.blue = blue;
    return pixel;
}

rgb int_to_rgb(int numero) {
    int red = numero % 256;
    numero = numero / 256;
    int green = numero % 256;
    numero = numero / 256;
    int blue = numero % 256;
    numero = numero / 256;
    return rgb_cria(red, green, blue);
}

int rgb_to_int(rgb cor) {
    return cor.red + 256 * (cor.green + 256 * cor.blue);
}

Dimensao2D Dimensao2D_cria_estatico(int altura, int largura) {
    Dimensao2D dimensao;
    dimensao.largura = largura;
    dimensao.altura = altura;
    return dimensao;
}

Dimensao2D *Dimensao2D_cria(int altura, int largura) {
    Dimensao2D *dimensao = (Dimensao2D *)malloc(sizeof(*dimensao));
    dimensao->altura = altura;
    dimensao->largura = largura;
    return dimensao;
}

Dimensao2D *Dimensao2D_copia(Dimensao2D *dimensao_original) {
    Dimensao2D *dimensao_nova = Dimensao2D_cria(dimensao_original->altura, dimensao_original->largura);
    return dimensao_nova;
}

void Dimensao2D_libera(Dimensao2D *dimensao) {
    free(dimensao);
    dimensao = NULL;
}

PPMHeader *PPMHeader_cria(int altura, int largura, int channelRange, BMPKey tipoBMP) {
    PPMHeader *cabecalho = (PPMHeader *)malloc(sizeof(*cabecalho));
    if (cabecalho == NULL) {
        printf("Erro ao alocar cabecalho\n");
        exit(1);
    }
    cabecalho->tamanho = (Dimensao2D *)malloc(sizeof(*cabecalho->tamanho));
    if (cabecalho->tamanho == NULL) {
        printf("Erro ao alocar cabecalho\n");
        exit(1);
    }

    cabecalho->tamanho->altura = altura;
    cabecalho->tamanho->largura = largura;
    cabecalho->channelRange = channelRange;
    cabecalho->tipoBMP = tipoBMP;
    return cabecalho;
}

PPMHeader *PPMHeader_copia(PPMHeader *cabecalho_original) {
    PPMHeader *cabecalho_novo = PPMHeader_cria(
        cabecalho_original->tamanho->altura,
        cabecalho_original->tamanho->largura,
        cabecalho_original->channelRange,
        cabecalho_original->tipoBMP);
    if (cabecalho_novo == NULL) {
        printf("Erro ao alocar cabecalho\n");
        exit(1);
    }
    return cabecalho_novo;
}

void PPMHeader_libera(PPMHeader *cabecalho) {
    Dimensao2D_libera(cabecalho->tamanho);
    cabecalho->tamanho = NULL;
    free(cabecalho);
    cabecalho = NULL;
}

BMPKey string_to_key(char *key) {
    if (string_compara(key, "P3") == 0) {
        return Key_PPM;
    } else if (string_compara(key, "P1") == 0) {
        return Key_BW;
    }
    // else if(string_compara(key, "P2") == 0) {
    //	return Key_PGM;
    // }
    else if (string_compara(key, "BM") == 0) {
        return Key_BMP;
    } else {
        printf("Erro ao converter string para key\n");
        exit(1);
    }
}

const char *key_to_string(BMPKey key) {
    switch (key) {
        case Key_PPM:
            return "P3";
        case Key_BM:
            return "P1";
        case Key_BW:
            return "P2";
        case Key_BMP:
            return "BM";
        default:
            printf("Erro ao converter key para string\n");
            exit(1);
    }
}

PPM *PPM_cria() {
    PPM *imagem = (PPM *)malloc(sizeof(*imagem));
    if (imagem == NULL) {
        printf("Erro ao alocar imagem\n");
        exit(1);
    }

    imagem->cabecalho = PPMHeader_cria(0, 0, 255, Key_PPM);
    if (imagem->cabecalho == NULL) {
        printf("Erro ao alocar imagem\n");
        exit(1);
    }

    imagem->pixel = NULL;

    return imagem;
}

PPM *PPM_copia(PPM *imagem_original) {
    PPM *imagem_nova = PPM_temporaria_cria(imagem_original);

    for (int i = 0; i < imagem_nova->cabecalho->tamanho->altura; i++) {
        memccpy(
            imagem_nova->pixel[i],
            imagem_original->pixel[i],
            imagem_nova->cabecalho->tamanho->largura,
            sizeof(**imagem_nova->pixel));
    }

    return imagem_nova;
}

PPM *PPM_temporaria_cria(PPM *imagem_original) {
    PPM *imagem_temporaria = (PPM *)malloc(sizeof(*imagem_temporaria));
    imagem_temporaria->cabecalho = PPMHeader_copia(imagem_original->cabecalho);
    imagem_temporaria->pixel = rgb2d_malloc(*imagem_temporaria->cabecalho->tamanho);
    return imagem_temporaria;
}

void PPM_libera(PPM *imagem) {
    rgb2d_libera(imagem->pixel, *imagem->cabecalho->tamanho);
    PPMHeader_libera(imagem->cabecalho);
    imagem->cabecalho = NULL;
    free(imagem);
    imagem = NULL;
}

rgb **rgb2d_malloc(Dimensao2D tamanho) {
    rgb **Pixel2D = (rgb **)malloc(tamanho.altura * sizeof(*Pixel2D));
    if (Pixel2D == NULL) {
        printf("Falha ao alocar pixels\n");
        exit(1);
    }
    for (int i = 0; i < tamanho.altura; i++) {
        Pixel2D[i] = (rgb *)calloc(tamanho.largura, sizeof(**Pixel2D));
        if (Pixel2D[i] == NULL) {
            printf("Falha ao alocar pixels\n");
            exit(1);
        }
    }
    return Pixel2D;
}

void rgb2d_libera(rgb **pixel, Dimensao2D tamanho) {
    if (pixel == NULL) {
        return;
    }
    for (int i = 0; i < tamanho.altura; i++) {
        free(pixel[i]);
        pixel[i] = NULL;
    }
    free(pixel);
    pixel = NULL;
}

int **int2d_malloc(Dimensao2D tamanho) {
    int **int2d = (int **)malloc(tamanho.altura * sizeof(*int2d));
    if (int2d == NULL) {
        printf("Erro ao alocar array 2d de inteiros\n");
        exit(1);
    }
    for (int i = 0; i < tamanho.altura; i++) {
        int2d[i] = (int *)malloc(sizeof(**int2d) * tamanho.largura);
        if (int2d[i] == NULL) {
            printf("Erro ao alocar array 2d de inteiros\n");
            exit(1);
        }
    }
    return int2d;
}

void int2d_libera(int **int2d, int altura) {
    for (int i = 0; i < altura; i++) {
        free(int2d[i]);
        int2d[i] = NULL;
    }
    free(int2d);
}

ArvoreBinaria *ArvoreBinaria_cria() {
    return NULL;
}

ArvoreBinaria *ArvoreBinaria_folha_cria(int x) {
    ArvoreBinaria *novo = (ArvoreBinaria *)malloc(sizeof(*novo));
    novo->x = x;
    novo->direita = NULL;
    novo->esquerda = NULL;
    return novo;
}

ArvoreBinaria *ArvoreBinaria_insere_sem_repeticao(ArvoreBinaria *arvore, int x) {
    if (arvore == NULL) {
        return ArvoreBinaria_folha_cria(x);
    }
    if (x > arvore->x) {
        arvore->direita = ArvoreBinaria_insere_sem_repeticao(arvore->direita, x);
    }
    if (x < arvore->x) {
        arvore->esquerda = ArvoreBinaria_insere_sem_repeticao(arvore->direita, x);
    }
    return arvore;
}

ArvoreBinaria *ArvoreBinaria_libera(ArvoreBinaria *arvore) {
    if (arvore != NULL) {
        arvore->esquerda = ArvoreBinaria_libera(arvore->esquerda);
        arvore->direita = ArvoreBinaria_libera(arvore->direita);
        free(arvore);
    }
    return NULL;
}

void arvore_imprime_pre_ordem(ArvoreBinaria *arvore) {
    if (arvore != NULL) {
        printf("<%d ", arvore->x);
        arvore_imprime_pre_ordem(arvore->esquerda);
        arvore_imprime_pre_ordem(arvore->direita);
        printf(">");
    }
    if (arvore == NULL) {
        printf("<>");
    }
}

int ArvoreBinaria_quantidade_nodes(ArvoreBinaria *arvore) {
    if (arvore != NULL) {
        return 1 + ArvoreBinaria_quantidade_nodes(arvore->esquerda) + ArvoreBinaria_quantidade_nodes(arvore->direita);
    } else
        return 0;
}

void PPM_pula_comentarios(FILE *arquivo) {
    int c;
    while ((c = fgetc(arquivo)) == '#' || c == ' ' || c == '\n') {
        if (c == '#') {
            while ((c = fgetc(arquivo)) != '\n' && c != EOF)
                ;
        } else {
            while (((c = fgetc(arquivo)) == '\n' || c == ' ') && c != EOF)
                ;
            ungetc(c, arquivo);
        }
    }
    ungetc(c, arquivo);
}

PPM *PPM_leitura(const char *fname) {
    FILE *arquivo = fopen_or_crash((char *)fname, "r");

    int largura;
    int altura;
    int channelRange;
    char tipo[3];
    fscanf(arquivo, "%s", tipo);
    if (string_compara(tipo, "P3") != 0) {
        printf("O arquivo nao e um ppm");
        fclose(arquivo);
        arquivo = NULL;
        exit(1);
    }
    PPM_pula_comentarios(arquivo);

    fscanf(arquivo, "%d %d", &largura, &altura);
    fscanf(arquivo, "%d", &channelRange);
    BMPKey key = Key_PPM;
    PPM *imagem = PPM_cria();
    imagem->cabecalho = PPMHeader_cria(altura, largura, channelRange, key);
    imagem->pixel = rgb2d_malloc(*imagem->cabecalho->tamanho);

    int red, green, blue;
    for (int i = 0; i < imagem->cabecalho->tamanho->altura; i++) {
        for (int j = 0; j < imagem->cabecalho->tamanho->largura; j++) {
            fscanf(arquivo, "%d", &red);
            imagem->pixel[i][j].red = red;
            fscanf(arquivo, "%d", &green);
            imagem->pixel[i][j].green = green;
            fscanf(arquivo, "%d", &blue);
            imagem->pixel[i][j].blue = blue;
        }
    }
    fclose(arquivo);
    arquivo = NULL;
    return imagem;
}

void PPM_grava(char fname[], PPM *imagem) {
    FILE *arquivo = fopen_or_crash(fname, "w");
    fprintf(
        arquivo,
        "P3\n#Created by ppmlib\n%d %d %d\n",
        imagem->cabecalho->tamanho->largura,
        imagem->cabecalho->tamanho->altura,
        imagem->cabecalho->channelRange);
    for (int i = 0; i < imagem->cabecalho->tamanho->altura; i++) {
        for (int j = 0; j < imagem->cabecalho->tamanho->largura; j++) {
            fprintf(
                arquivo,
                "%d %d %d\n",
                imagem->pixel[i][j].red,
                imagem->pixel[i][j].green,
                imagem->pixel[i][j].blue);
        }
    }
    fclose(arquivo);
    arquivo = NULL;
}

// Manipulacao Vetorial Basica

// pontos
Ponto Ponto_cria_estatico(int x, int y) {
    Ponto p;
    p.x = x;
    p.y = y;
    return p;
}

int int_quadrado(int numero) {
    return numero * numero;
}

double Ponto_distancia(Ponto a, Ponto b) {
    return sqrt(
        (float)int_quadrado(a.x - b.x) +
        (float)int_quadrado(a.y - b.y));
}

Ponto Ponto_vira(Ponto ponto, Ponto ponto_referente, float graus) {
    int x = ponto.x + graus_coseno(graus) * (ponto_referente.x - ponto.x) + graus_seno(graus) * (ponto.y - ponto_referente.y);
    int y = ponto.y + graus_coseno(graus) * (ponto_referente.y - ponto.y) + graus_seno(graus) * (ponto_referente.x - ponto.x);
    Ponto ponto_virado = Ponto_cria_estatico(x, y);
    return ponto_virado;
}

Ponto Ponto_medio(Ponto ponto_1, Ponto ponto_2) {
    return Ponto_cria_estatico((ponto_1.x + ponto_2.x) / 2, (ponto_1.y + ponto_2.y) / 2);
}

/*
interpolacao linear
acha o Ponto que divide a linha a->b em 1/ratio vezes
*/
Ponto Ponto_interpolacao_linear(Ponto ponto_1, Ponto ponto_2, double razao) {
    return Ponto_cria_estatico(ponto_1.x + (ponto_2.x - ponto_1.x) * razao, ponto_1.y + (ponto_2.y - ponto_1.y) * razao);
}

bool Ponto_compara(Ponto ponto_1, Ponto ponto_2) {
    return (ponto_1.x == ponto_2.x && ponto_1.y == ponto_2.y);
}

bool cor_compara(rgb cor_1, rgb cor_2) {
    return (cor_1.red == cor_2.red && cor_1.green == cor_2.green && cor_1.blue == cor_2.blue);
}

int cores_diferentes(PPM *imagem) {
    int total = 0;
    char *cores = (char *)malloc(sizeof(char) * 16777216);
    for (int i = 0; i < 16777215; i++) {
        cores[i] = 0;
    }
    for (int i = 0; i < imagem->cabecalho->tamanho->altura; i++) {
        for (int j = 0; j < imagem->cabecalho->tamanho->largura; j++) {
            int corNumero = rgb_to_int(imagem->pixel[i][j]);
            cores[corNumero] = 1;
        }
    }
    for (int i = 0; i < 16777216; i++) {
        total += cores[i];
    }
    free(cores);
    return total;
}

rgb cor_aleatoria() {
    rgb cor;
    cor.red = rand() % 256;
    cor.green = rand() % 256;
    cor.blue = rand() % 256;
    return cor;
}

bool imagem_contem_Ponto(PPM *imagem, Ponto ponto) {
    return (ponto.x >= 0 && ponto.x < imagem->cabecalho->tamanho->largura && ponto.y >= 0 && ponto.y < imagem->cabecalho->tamanho->altura);
}
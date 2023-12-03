#include <stdio.h>
#include <stdlib.h>

#include "internal.h"
#include "libefeito.h"

PPM* efeito_cria_imagem_decomposicao(PPM* imagem, bool red_mantem, bool green_mantem, bool blue_mantem) {
    PPM* imagem_decomposta = PPM_temporaria_cria(imagem);
    for (int i = 0; i < imagem_decomposta->cabecalho->tamanho->altura; i++) {
        for (int j = 0; j < imagem_decomposta->cabecalho->tamanho->largura; j++) {
            if (red_mantem == true) {
                imagem_decomposta->pixel[i][j].red = imagem->pixel[i][j].red;
            } else {
                imagem_decomposta->pixel[i][j].red = 0;
            }
            if (green_mantem == true) {
                imagem_decomposta->pixel[i][j].green = imagem->pixel[i][j].green;
            } else {
                imagem_decomposta->pixel[i][j].green = 0;
            }
            if (blue_mantem == true) {
                imagem_decomposta->pixel[i][j].blue = imagem->pixel[i][j].blue;
            } else {
                imagem_decomposta->pixel[i][j].blue = 0;
            }
        }
    }
    return imagem_decomposta;
}

PPM* efeito_cria_imagem_rotacao(PPM* imagem, int graus) {
    PPM* imagem_rotacionada = PPM_temporaria_cria(imagem);
    int rotacoes_90_graus = graus / 90;
    int vezes = rotacoes_90_graus % 4;
    if (vezes == 0) {
        return imagem_rotacionada;
    }

    PPM* imagem_temporaria = PPM_temporaria_cria(imagem);
    for (int n = 0; n < vezes; n++) {
        rgb2d_libera(imagem_temporaria->pixel, *imagem_temporaria->cabecalho->tamanho);
        int_troca(&imagem_temporaria->cabecalho->tamanho->altura, &imagem_temporaria->cabecalho->tamanho->largura);
        imagem_temporaria->pixel = rgb2d_malloc(*imagem_temporaria->cabecalho->tamanho);
        int b = 0;
        for (int i = 0; i < imagem_temporaria->cabecalho->tamanho->altura; i++) {
            int a = imagem_temporaria->cabecalho->tamanho->largura - 1;
            for (int j = 0; j < imagem_temporaria->cabecalho->tamanho->largura; j++) {
                imagem_temporaria->pixel[i][j] = imagem_rotacionada->pixel[a][b];
                a--;
            }
            b++;
        }
        PPM_libera(imagem_rotacionada);
        imagem_rotacionada = PPM_copia(imagem_temporaria);
    }
    PPM_libera(imagem_temporaria);
    return imagem_rotacionada;
}

PPM* efeito_cria_imagem_negativo(PPM* imagem) {
    PPM* imagem_com_negativo = PPM_temporaria_cria(imagem);
    for (int i = 0; i < imagem_com_negativo->cabecalho->tamanho->altura; i++) {
        for (int j = 0; j < imagem_com_negativo->cabecalho->tamanho->largura; j++) {
            imagem_com_negativo->pixel[i][j].red = 255 - imagem->pixel[i][j].red;
            imagem_com_negativo->pixel[i][j].green = 255 - imagem->pixel[i][j].green;
            imagem_com_negativo->pixel[i][j].blue = 255 - imagem->pixel[i][j].blue;
        }
    }
    return imagem_com_negativo;
}

PPM* efeito_cria_imagem_preto_e_branco(PPM* imagem) {
    PPM* imagem_preto_e_branco = PPM_temporaria_cria(imagem);
    for (int i = 0; i < imagem_preto_e_branco->cabecalho->tamanho->altura; i++) {
        for (int j = 0; j < imagem_preto_e_branco->cabecalho->tamanho->largura; j++) {
            int tom_de_cinza = (imagem->pixel[i][j].red + imagem->pixel[i][j].green + imagem->pixel[i][j].blue) / 3;
            imagem_preto_e_branco->pixel[i][j].red = float_aproximacao(tom_de_cinza);
            imagem_preto_e_branco->pixel[i][j].green = float_aproximacao(tom_de_cinza);
            imagem_preto_e_branco->pixel[i][j].blue = float_aproximacao(tom_de_cinza);
        }
    }
    return imagem_preto_e_branco;
}

PPM* efeito_cria_imagem_bitmap(PPM* imagem) {
    PPM* imagem_bitmap = PPM_temporaria_cria(imagem);
    for (int i = 0; i < imagem_bitmap->cabecalho->tamanho->altura; i++) {
        for (int j = 0; j < imagem_bitmap->cabecalho->tamanho->largura; j++) {
            int val = ((imagem->pixel[i][j].red + imagem->pixel[i][j].green + imagem->pixel[i][j].blue) / 3) < 128 ? 0 : 255;
            imagem_bitmap->pixel[i][j].red = val;
            imagem_bitmap->pixel[i][j].green = val;
            imagem_bitmap->pixel[i][j].blue = val;
        }
    }
    return imagem_bitmap;
}

static rgb efeito_blur_pixel(PPM* imagem, int i, int j, int tamanho_kernel, int** blur_kernel) {
    float total_red = 0.0;
    float total_green = 0.0;
    float total_blue = 0.0;
    int n = 0;
    for (int a = -tamanho_kernel / 2; a < tamanho_kernel / 2; a++) {
        for (int b = -tamanho_kernel / 2; b < tamanho_kernel / 2; b++) {
            bool contido_esquerda = i + a >= 0;
            bool contido_direita = i + a < imagem->cabecalho->tamanho->altura;
            bool contido_cima = j + b >= 0;
            bool contido_baixo = j + b < imagem->cabecalho->tamanho->largura;
            bool ponto_a_b_contido_na_imagem = contido_esquerda && contido_direita && contido_cima && contido_baixo;
            if (ponto_a_b_contido_na_imagem) {
                n += blur_kernel[a + (tamanho_kernel / 2)][b + (tamanho_kernel / 2)];
                total_red += imagem->pixel[i + a][j + b].red * blur_kernel[a + (tamanho_kernel / 2)][b + (tamanho_kernel / 2)];
                total_green += imagem->pixel[i + a][j + b].green * blur_kernel[a + (tamanho_kernel / 2)][b + (tamanho_kernel / 2)];
                total_blue += imagem->pixel[i + a][j + b].blue * blur_kernel[a + (tamanho_kernel / 2)][b + (tamanho_kernel / 2)];
            }
        }
    }
    int media_red = (int)(total_red / n);
    int media_green = (int)(total_green / n);
    int media_blue = (int)(total_blue / n);
    return rgb_cria(media_red, media_green, media_blue);
}

PPM* efeito_cria_imagem_blur(PPM* imagem, int** blur_kernel, int tamanho_kernel) {
    PPM* imagem_com_blur = PPM_temporaria_cria(imagem);

    for (int i = 0; i < imagem_com_blur->cabecalho->tamanho->altura; i++) {
        for (int j = 0; j < imagem_com_blur->cabecalho->tamanho->largura; j++) {
            imagem_com_blur->pixel[i][j] = efeito_blur_pixel(imagem, i, j, tamanho_kernel, blur_kernel);
        }
    }
    return imagem_com_blur;
}

int** efeito_kernel_blur_gaussiano_cria(int tamanho_kernel) {
    Dimensao2D tamanho = Dimensao2D_cria_estatico(tamanho_kernel, tamanho_kernel);
    int** kernel = int2d_malloc(tamanho);
    for (int i = 0; i < tamanho_kernel; i++) {
        for (int j = 0; j < tamanho_kernel; j++) {
            kernel[i][j] = int_quadrado((tamanho_kernel / 2) + 1 - (int_valor_absoluto(i - (tamanho_kernel / 2)) + int_valor_absoluto(j - (tamanho_kernel / 2))));
        }
    }
    return kernel;
}

PPM* efeito_cria_imagem_blur_gaussiano(PPM* img, int tamanho_kernel) {
    int** ker = efeito_kernel_blur_gaussiano_cria(tamanho_kernel);
    PPM* imagem_blur_gaussiano = efeito_cria_imagem_blur(img, ker, tamanho_kernel);
    int2d_libera(ker, tamanho_kernel);
    return imagem_blur_gaussiano;
}

int** efeito_kernel_blur_mint_cria(int tamanho_kernel) {
    Dimensao2D tamanho = Dimensao2D_cria_estatico(tamanho_kernel, tamanho_kernel);
    int** kernel = int2d_malloc(tamanho);
    for (int i = 0; i < tamanho_kernel; i++) {
        for (int j = 0; j < tamanho_kernel; j++) {
            kernel[i][j] = 1;
        }
    }
    return kernel;
}

PPM* efeito_cria_imagem_blur_mint(PPM* img, int tamanho_kernel) {
    int** kernel = efeito_kernel_blur_mint_cria(tamanho_kernel);
    PPM* imagem_blur_mint = efeito_cria_imagem_blur(img, kernel, tamanho_kernel);
    int2d_libera(kernel, tamanho_kernel);
    return imagem_blur_mint;
}

void aplica_aumenta_imagem(PPM* imagem, PPM* imagem_ampliada, float zoom) {
    for (int i = 0; i < imagem->cabecalho->tamanho->altura; i++) {
        for (int j = 0; j < imagem->cabecalho->tamanho->largura; j++) {
            for (int copia_i = i * zoom; copia_i < i * zoom + zoom; copia_i++) {
                for (int copia_j = j * zoom; copia_j < j * zoom + zoom; copia_j++) {
                    imagem_ampliada->pixel[copia_i][copia_j] = imagem->pixel[i][j];
                }
            }
        }
    }
}

void aplica_diminui_imagem(PPM* imagem, PPM* imagem_ampliada) {
    int fator_zoom_altura = imagem->cabecalho->tamanho->altura / imagem_ampliada->cabecalho->tamanho->altura;
    int fator_zoom_largura = imagem->cabecalho->tamanho->largura / imagem_ampliada->cabecalho->tamanho->largura;
    for (int i = 0; i < imagem_ampliada->cabecalho->tamanho->altura; i++) {
        for (int j = 0; j < imagem_ampliada->cabecalho->tamanho->largura; j++) {
            int total_red = 0;
            int total_green = 0;
            int total_blue = 0;
            int n_pixels = 0;
            for (int copia_i = i * fator_zoom_altura; copia_i < i * fator_zoom_altura + fator_zoom_altura; copia_i++) {
                for (int copia_j = j * fator_zoom_largura; copia_j < j * fator_zoom_largura + fator_zoom_largura; copia_j++) {
                    if (copia_j >= imagem->cabecalho->tamanho->largura) {
                        break;
                    }
                    total_red += imagem->pixel[copia_i][copia_j].red;
                    total_green += imagem->pixel[copia_i][copia_j].green;
                    total_blue += imagem->pixel[copia_i][copia_j].blue;
                    n_pixels++;
                }
                if (copia_i >= imagem->cabecalho->tamanho->altura) {
                    break;
                }
            }
            imagem_ampliada->pixel[i][j].red = total_red / n_pixels;
            imagem_ampliada->pixel[i][j].green = total_green / n_pixels;
            imagem_ampliada->pixel[i][j].blue = total_blue / n_pixels;
        }
    }
}

PPM* efeito_cria_imagem_ampliado(PPM* imagem, float zoom) {
    PPM* imagem_ampliada = PPM_cria();
    imagem_ampliada->cabecalho->tamanho->altura = imagem->cabecalho->tamanho->altura * zoom;
    imagem_ampliada->cabecalho->tamanho->largura = imagem->cabecalho->tamanho->largura * zoom;
    imagem_ampliada->pixel = rgb2d_malloc(*imagem_ampliada->cabecalho->tamanho);

    if (zoom < 0) {
        printf("O zoom deve ser maior que 0");
        exit(1);
    }

    if (zoom >= 1.0) {
        aplica_aumenta_imagem(imagem, imagem_ampliada, zoom);
    } else {
        aplica_diminui_imagem(imagem, imagem_ampliada);
    }

    return imagem_ampliada;
}

PPM* efeito_cria_imagem_espelhado(PPM* imagem) {
    PPM* imagem_espelhada = PPM_temporaria_cria(imagem);
    for (int i = 0; i < imagem->cabecalho->tamanho->altura; i++)
        for (int j = 0; j < imagem->cabecalho->tamanho->largura; j++)
            imagem_espelhada->pixel[i][j] = imagem->pixel[i][imagem->cabecalho->tamanho->largura - j - 1];
    return imagem_espelhada;
}

PPM* efeito_cria_imagem_join(PPM* imagem, PPM* imagem2) {
    PPM* imagem_resultado_join = PPM_cria();
    if (imagem2->cabecalho->tamanho->altura > imagem->cabecalho->tamanho->altura) {
        imagem_resultado_join->cabecalho->tamanho->altura = imagem2->cabecalho->tamanho->altura;
    }
    imagem_resultado_join->cabecalho->tamanho->largura = imagem->cabecalho->tamanho->largura + imagem2->cabecalho->tamanho->largura;
    imagem_resultado_join->pixel = rgb2d_malloc(*imagem_resultado_join->cabecalho->tamanho);

    for (int i = 0; i < imagem_resultado_join->cabecalho->tamanho->altura; i++) {
        for (int j = 0; j < imagem_resultado_join->cabecalho->tamanho->largura; j++) {
            imagem_resultado_join->pixel[i][j] = _cor_branco;
        }
    }
    for (int i = 0; i < imagem->cabecalho->tamanho->altura; i++) {
        for (int j = 0; j < imagem->cabecalho->tamanho->largura; j++) {
            imagem_resultado_join->pixel[i][j] = imagem->pixel[i][j];
        }
    }
    for (int i = 0; i < imagem2->cabecalho->tamanho->altura; i++) {
        for (int j = 0; j < imagem2->cabecalho->tamanho->largura; j++) {
            imagem_resultado_join->pixel[i][j + imagem->cabecalho->tamanho->largura] = imagem2->pixel[i][j];
        }
    }
    return imagem_resultado_join;
}

PPM* efeito_cria_imagem_merge(PPM* imagem, PPM* imagem2) {
    PPM* imagem_resultado_merge = PPM_cria();
    imagem_resultado_merge->cabecalho->tamanho->altura = imagem->cabecalho->tamanho->altura + imagem2->cabecalho->tamanho->altura;
    if (imagem2->cabecalho->tamanho->largura <= imagem->cabecalho->tamanho->largura) {
        imagem_resultado_merge->cabecalho->tamanho->largura = imagem->cabecalho->tamanho->largura;
    } else {
        imagem_resultado_merge->cabecalho->tamanho->largura = imagem->cabecalho->tamanho->largura;
    }
    imagem_resultado_merge->pixel = rgb2d_malloc(*imagem_resultado_merge->cabecalho->tamanho);
    for (int i = 0; i < imagem_resultado_merge->cabecalho->tamanho->altura; i++) {
        for (int j = 0; j < imagem_resultado_merge->cabecalho->tamanho->largura; j++) {
            imagem_resultado_merge->pixel[i][j] = _cor_branco;
        }
    }
    for (int i = 0; i < imagem->cabecalho->tamanho->altura; i++) {
        for (int j = 0; j < imagem->cabecalho->tamanho->largura; j++) {
            imagem_resultado_merge->pixel[i][j] = imagem->pixel[i][j];
        }
    }
    for (int i = 0; i < imagem2->cabecalho->tamanho->altura; i++) {
        for (int j = 0; j < imagem2->cabecalho->tamanho->largura; j++) {
            imagem_resultado_merge->pixel[i + imagem->cabecalho->tamanho->altura][j] = imagem2->pixel[i][j];
        }
    }

    return imagem_resultado_merge;
}

PPM* efeito_cria_imagem_overlay(PPM* imagem, PPM* imagem2) {
    PPM* imagem_resultado_overlay = PPM_cria();
    imagem_resultado_overlay->cabecalho->tamanho = Dimensao2D_copia(imagem->cabecalho->tamanho);
    if (imagem_resultado_overlay->cabecalho->tamanho->altura < imagem2->cabecalho->tamanho->altura) {
        imagem_resultado_overlay->cabecalho->tamanho->altura = imagem2->cabecalho->tamanho->altura;
    }
    if (imagem_resultado_overlay->cabecalho->tamanho->largura < imagem2->cabecalho->tamanho->largura) {
        imagem_resultado_overlay->cabecalho->tamanho->largura = imagem2->cabecalho->tamanho->largura;
    }
    imagem_resultado_overlay->pixel = rgb2d_malloc(*imagem_resultado_overlay->cabecalho->tamanho);
    for (int i = 0; i < imagem_resultado_overlay->cabecalho->tamanho->altura; i++) {
        for (int j = 0; j < imagem_resultado_overlay->cabecalho->tamanho->largura; j++) {
            int n_pixels = 0;
            int red = 0;
            int green = 0;
            int blue = 0;
            if (i < imagem->cabecalho->tamanho->altura && j < imagem->cabecalho->tamanho->largura) {
                n_pixels++;
                red = imagem->pixel[i][j].red;
                green = imagem->pixel[i][j].green;
                blue = imagem->pixel[i][j].blue;
            }
            if (i < imagem2->cabecalho->tamanho->altura && j < imagem2->cabecalho->tamanho->largura) {
                n_pixels++;
                red += imagem2->pixel[i][j].red;
                green += imagem2->pixel[i][j].green;
                blue += imagem2->pixel[i][j].blue;
            }
            rgb cor = _cor_branco;
            if (n_pixels > 0) {
                cor = rgb_cria(red / n_pixels, green / n_pixels, blue / n_pixels);
            }
            imagem_resultado_overlay->pixel[i][j] = cor;
        }
    }
    return imagem_resultado_overlay;
}

void efeito_grava_decomposto(char fname[], PPM* imagem, bool red_mantem, bool green_mantem, bool blue_mantem) {
    FILE* arquivo = fopen_or_crash(fname, "w");
    fprintf(arquivo, "P3\n%d %d %d\n", imagem->cabecalho->tamanho->largura, imagem->cabecalho->tamanho->altura, imagem->cabecalho->channelRange);
    for (int i = 0; i < imagem->cabecalho->tamanho->altura; i++) {
        for (int j = 0; j < imagem->cabecalho->tamanho->largura; j++) {
            if (red_mantem == true)
                fprintf(arquivo, "%d ", imagem->pixel[i][j].red);
            else
                fprintf(arquivo, "%d ", 0);
            if (green_mantem == true)
                fprintf(arquivo, "%d ", imagem->pixel[i][j].green);
            else
                fprintf(arquivo, "%d ", 0);
            if (blue_mantem == true)
                fprintf(arquivo, "%d\n", imagem->pixel[i][j].blue);
            else
                fprintf(arquivo, "%d\n", 0);
        }
    }
    fclose(arquivo);
    arquivo = NULL;
}

void efeito_grava_rotacionado(char fname[], PPM* imagem, int graus) {
    PPM* imagem_rotacionada = efeito_cria_imagem_rotacao(imagem, graus);
    PPM_grava(fname, imagem_rotacionada);
    PPM_libera(imagem_rotacionada);
}

void efeito_grava_negativo(char fname[], PPM* img) {
    FILE* arquivo = fopen_or_crash(fname, "w");
    fprintf(arquivo, "P3\n%d %d %d\n", img->cabecalho->tamanho->largura, img->cabecalho->tamanho->altura, img->cabecalho->channelRange);
    for (int i = 0; i < img->cabecalho->tamanho->altura; i++) {
        for (int j = 0; j < img->cabecalho->tamanho->largura; j++) {
            fprintf(arquivo, "%d %d %d\n ", 255 - img->pixel[i][j].red, 255 - img->pixel[i][j].green, 255 - img->pixel[i][j].blue);
        }
    }
    fclose(arquivo);
    arquivo = NULL;
}

void efeito_grava_preto_e_branco(char fname[], PPM* img) {
    FILE* arquivo = fopen_or_crash(fname, "w");
    fprintf(arquivo, "P3\n%d %d %d\n", img->cabecalho->tamanho->largura, img->cabecalho->tamanho->altura, img->cabecalho->channelRange);
    for (int i = 0; i < img->cabecalho->tamanho->altura; i++)
        for (int j = 0; j < img->cabecalho->tamanho->largura; j++) {
            int val = float_aproximacao((img->pixel[i][j].red + img->pixel[i][j].green + img->pixel[i][j].blue) / 3);
            fprintf(arquivo, "%d %d %d\n ", val, val, val);
        }
    fclose(arquivo);
    arquivo = NULL;
}

void efeito_grava_bitmap(char fname[], PPM* img) {
    FILE* arquivo = fopen_or_crash(fname, "w");
    int i, j;
    int val = 0;
    fprintf(arquivo, "P3\n%d %d %d\n", img->cabecalho->tamanho->largura, img->cabecalho->tamanho->altura, img->cabecalho->channelRange);
    for (i = 0; i < img->cabecalho->tamanho->altura; i++) {
        for (j = 0; j < img->cabecalho->tamanho->largura; j++) {
            val = ((img->pixel[i][j].red + img->pixel[i][j].green + img->pixel[i][j].blue) / 3) < 128 ? 0 : 255;
            fprintf(arquivo, "  %d %d %d \n ", val, val, val);
        }
    }
    fclose(arquivo);
    arquivo = NULL;
}

void efeito_grava_blur(char fname[], PPM* imagem, int** kernel, int tamanho_kernel) {
    FILE* arquivo = fopen_or_crash(fname, "w");

    fprintf(arquivo, "P3\n%d %d %d\n", imagem->cabecalho->tamanho->largura, imagem->cabecalho->tamanho->altura, imagem->cabecalho->channelRange);

    for (int i = 0; i < imagem->cabecalho->tamanho->altura; i++) {
        for (int j = 0; j < imagem->cabecalho->tamanho->largura; j++) {
            rgb pixel_com_blur = efeito_blur_pixel(imagem, i, j, tamanho_kernel, kernel);
            fprintf(arquivo, " %d %d %d\n", pixel_com_blur.red, pixel_com_blur.green, pixel_com_blur.blue);
        }
    }
}

void efeito_grava_blur_gaussiano(char fname[], PPM* imagem, int tamanho_kernel) {
    int** kernel = efeito_kernel_blur_gaussiano_cria(tamanho_kernel);
    efeito_grava_blur(fname, imagem, kernel, tamanho_kernel);
    int2d_libera(kernel, tamanho_kernel);
}

void efeito_grava_blur_mint(char fname[], PPM* imagem, int tamanho_kernel) {
    int** kernel = efeito_kernel_blur_mint_cria(tamanho_kernel);
    efeito_grava_blur(fname, imagem, kernel, tamanho_kernel);
    int2d_libera(kernel, tamanho_kernel);
}

void efeito_grava_espelhado(char fname[], PPM* imagem) {
    FILE* arquivo = fopen_or_crash(fname, "w");
    fprintf(arquivo, "P3\n%d %d %d\n", imagem->cabecalho->tamanho->largura, imagem->cabecalho->tamanho->altura, imagem->cabecalho->channelRange);
    for (int i = 0; i < imagem->cabecalho->tamanho->altura; i++) {
        for (int j = 0; j < imagem->cabecalho->tamanho->largura; j++) {
            rgb pixel_espelhado = imagem->pixel[i][imagem->cabecalho->tamanho->largura - j - 1];
            fprintf(arquivo, " %d %d %d \n", pixel_espelhado.red, pixel_espelhado.green, pixel_espelhado.blue);
        }
    }
    fclose(arquivo);
    arquivo = NULL;
}

void efeito_aplica_decomposicao(PPM** imagem, bool red_mantem, bool green_mantem, bool blue_mantem) {
    for (int i = 0; i < (*imagem)->cabecalho->tamanho->altura; i++)
        for (int j = 0; j < (*imagem)->cabecalho->tamanho->largura; j++) {
            if (red_mantem == false)
                (*imagem)->pixel[i][j].red = 0;
            if (green_mantem == false)
                (*imagem)->pixel[i][j].green = 0;
            if (blue_mantem == false)
                (*imagem)->pixel[i][j].blue = 0;
        }
}

void efeito_aplica_rotacao(PPM** imagem, int graus) {
    PPM* imagem_temporaria = efeito_cria_imagem_rotacao((*imagem), graus);
    PPM_libera((*imagem));
    *imagem = imagem_temporaria;
}

void efeito_aplica_negativo(PPM** imagem) {
    for (int i = 0; i < (*imagem)->cabecalho->tamanho->altura; i++)
        for (int j = 0; j < (*imagem)->cabecalho->tamanho->largura; j++) {
            (*imagem)->pixel[i][j].red = 255 - (*imagem)->pixel[i][j].red;
            (*imagem)->pixel[i][j].green = 255 - (*imagem)->pixel[i][j].green;
            (*imagem)->pixel[i][j].blue = 255 - (*imagem)->pixel[i][j].blue;
        }
}

void efeito_aplica_preto_e_branco(PPM** imagem) {
    for (int i = 0; i < (*imagem)->cabecalho->tamanho->altura; i++)
        for (int j = 0; j < (*imagem)->cabecalho->tamanho->largura; j++) {
            double tom_de_cinza = ((*imagem)->pixel[i][j].red + (*imagem)->pixel[i][j].green + (*imagem)->pixel[i][j].blue) / 3;
            (*imagem)->pixel[i][j].red = float_aproximacao(tom_de_cinza);
            (*imagem)->pixel[i][j].green = float_aproximacao(tom_de_cinza);
            (*imagem)->pixel[i][j].blue = float_aproximacao(tom_de_cinza);
        }
}

void efeito_aplica_bitmap(PPM** imagem) {
    for (int i = 0; i < (*imagem)->cabecalho->tamanho->altura; i++) {
        for (int j = 0; j < (*imagem)->cabecalho->tamanho->largura; j++) {
            double val = ((*imagem)->pixel[i][j].red + (*imagem)->pixel[i][j].green + (*imagem)->pixel[i][j].blue) / 3;
            char bit = val >= 128 ? 255 : 0;
            (*imagem)->pixel[i][j] = rgb_cria(bit, bit, bit);
        }
    }
}

void efeito_aplica_blur_gaussiano(PPM** imagem, int tamanho_kernel) {
    int** kernel = efeito_kernel_blur_gaussiano_cria(tamanho_kernel);
    PPM* imagem_temporaria = efeito_cria_imagem_blur(*imagem, kernel, tamanho_kernel);
    PPM_libera(*imagem);
    *imagem = imagem_temporaria;
}

void efeito_aplica_blur_mint(PPM** imagem, int tamanho_kernel) {
    int** kernel = efeito_kernel_blur_mint_cria(tamanho_kernel);
    PPM* imagem_temporaria = efeito_cria_imagem_blur(*imagem, kernel, tamanho_kernel);
    PPM_libera(*imagem);
    *imagem = imagem_temporaria;
}

// void efeito_aplica_espelha(PPM** imagem) {
// 	PPM* imagem_temporaria = espelhar(*imagem);
// 	PPM_libera(*imagem);
// 	*imagem = imagem_temporaria;
// }
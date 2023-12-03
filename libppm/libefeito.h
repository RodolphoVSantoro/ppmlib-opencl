#ifndef _EFEITO_LIB_H_
#define _EFEITO_LIB_H_

#include "internal.h"
#include "types.h"

// Cria nova imagem em memória com com efeitos
PPM* efeito_cria_imagem_decomposicao(PPM* cab, bool r, bool g, bool b);
PPM* efeito_cria_imagem_rotacao(PPM* imagem, int graus);
PPM* efeito_cria_imagem_negativo(PPM* imagem);
PPM* efeito_cria_imagem_preto_e_branco(PPM* imagem);
PPM* efeito_cria_imagem_bitmap(PPM* imagem);
PPM* efeito_cria_imagem_blur(PPM* imagem, int** ker, int tamanhoKernel);
int** efeito_kernel_blur_gaussiano_cria(int tamanhoKernel);
PPM* efeito_cria_imagem_blur_gaussiano(PPM* imagem, int tamanhoKernel);
int** efeito_kernel_blur_mint_cria(int tamanhoKernel);
PPM* efeito_cria_imagem_blur_mint(PPM* imagem, int tamanhoKernel);
PPM* efeito_cria_imagem_ampliado(PPM* imagem, float zoom);
// PPM* efeito_cria_imagem_espelhado(PPM* imagem);
PPM* efeito_cria_imagem_join(PPM* imagem, PPM* imagem2);
PPM* efeito_cria_imagem_merge(PPM* imagem, PPM* imagem2);
PPM* efeito_cria_imagem_overlay(PPM* imagem, PPM* imagem2);

// grava imagem com efeito
void efeito_grava_decomposto(char fname[], PPM* imagem, bool r, bool g, bool b);
void efeito_grava_rotacionado(char fname[], PPM* imagem, int graus);
void efeito_grava_negativo(char fname[], PPM* imagem);
void efeito_grava_preto_e_branco(char fname[], PPM* imagem);
void efeito_grava_bitmap(char fname[], PPM* imagem);
void efeito_grava_blur(char fname[], PPM* imagem, int** ker, int tamanhoKernel);
void efeito_grava_blur_gaussiano(char fname[], PPM* imagem, int tamanhoKernel);
void efeito_grava_blur_mint(char fname[], PPM* imagem, int tamanhoKernel);
// void grava_espelhado(char fname[], PPM* imagem);

// Aplica efeito in-place na imagem(sem criar nova imagem em memória)
void efeito_aplica_decomposicao(PPM** imagem, bool r, bool g, bool b);
void efeito_aplica_rotacao(PPM** imagem, int graus);
void efeito_aplica_negativo(PPM** imagem);
void efeito_aplica_preto_e_branco(PPM** imagem);
void efeito_aplica_bitmap(PPM** imagem);
void efeito_aplica_blur_gaussiano(PPM** imagem, int tamanhoKernel);
void efeito_aplica_blur_mint(PPM** imagem, int tamanhoKernel);
// void efeito_aplica_espelha(PPM** imagem);

#endif

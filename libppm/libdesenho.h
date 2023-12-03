#ifndef _DESENHO_LIB_H_
#define _DESENHO_LIB_H_

#include "internal.h"
#include "types.h"

// Cria uma imagem com dimensoes e cor de fundo
/*
 * Cria uma imagem com dimensoes e cor de fundo
 * @param tamanho Dimensoes da imagem
 * @param channelRange Valor máximo de cada canal de cor
 * @param corFundo Cor de fundo da imagem
 * @return Imagem criada
 */
PPM* PPM_cria_com_dimensoes(Dimensao2D tamanho, int channelRange, rgb corFundo);

// sem cor
#define ponto_desenha(imagem, ponto) ponto_cor_desenha(imagem, ponto, _cor_preto)
#define linha_desenha(imagem, pontoInicial, pontoFinal) linha_cor_desenha(imagem, pontoInicial, pontoFinal, _cor_preto)
#define curva_desenha(imagem, pontoInicial, pm, pontoFinal) curva_cor_desenha(imagem, pontoInicial, pm, pontoFinal, _cor_preto)
#define linha_lista_desenha(imagem, linha) lista_linha_cor_desenha(imagem, linha, _cor_preto) /*desenha linha e remove os pontos da lista*/
#define triangulo_desenha(imagem, centro, altura, base) triangulo_cor_desenha(imagem, centro, altura, base, _cor_preto)
#define retangulo_desenha(imagem, centro, alturaR, larguraR) retangulo_cor_desenha(imagem, centro, alturaR, larguraR, _cor_preto)
#define losango_desenha(imagem, centro, altura, largura) losango_cor_desenha(imagem, centro, altura, largura, _cor_preto)
#define trapezio_desenha(imagem, centro, b1, b2, altura) trapezio_cor_desenha(imagem, centro, b1, b2, altura, _cor_preto)
#define estrela_desenha(imagem, ponto, x, y) estrela_cor_desenha(imagem, ponto, x, y, _cor_preto)
#define circulo_desenha(imagem, centro, raio) circulo_cor_desenha(imagem, centro, raio, _cor_preto)
#define elipse_desenha(imagem, centro, altura, largura) elipse_cor_desenha(imagem, centro, altura, largura, _cor_preto)

// cor
void ponto_cor_desenha(PPM* imagem, Ponto pontoInicial, rgb cor);
void linha_cor_desenha(PPM* imagem, Ponto pontoInicial, Ponto pontoFinal, rgb cor);
void curva_cor_desenha(PPM* imagem, Ponto pontoInicial, Ponto pm, Ponto pontoFinal, rgb cor);
void Linha_lista_cor_desenha(PPM* imagem, Linha* linha, rgb cor);
void triangulo_cor_desenha(PPM* imagem, Ponto centro, int altura, int base, rgb cor);
void retangulo_cor_desenha(PPM* imagem, Ponto centro, int alturaR, int larguraR, rgb cor);
void losango_cor_desenha(PPM* imagem, Ponto centro, int altura, int largura, rgb cor);
void trapezio_cor_desenha(PPM* imagem, Ponto centro, int b1, int b2, int altura, rgb cor);
void estrela_cor_desenha(PPM* imagem, Ponto ponto, int x, int y, rgb cor);
void circulo_cor_desenha(PPM* imagem, Ponto centro, int raio, rgb cor);
void elipse_cor_desenha(PPM* imagem, Ponto centro, int altura, int largura, rgb cor);

// preenchidos
#define curva_preenchido_desenha(imagem, pontoInicial, pm, pontoFinal) curva_cor_preenchido_desenha(imagem, pontoInicial, pm, pontoFinal, _cor_preto)
#define triangulo_preenchido_desenha(imagem, centro, altura, base) triangulo_cor_preenchido_desenha(imagem, centro, altura, base, _cor_preto)
#define retangulo_preenchido_desenha(imagem, centro, altura, largura) retangulo_cor_preenchido_desenha(imagem, centro, altura, largura, _cor_preto)
#define losango_preenchido_desenha(imagem, centro, altura, largura) losango_cor_preenchido_desenha(imagem, centro, altura, largura, _cor_preto)
#define circulo_preenchido_desenha(imagem, centro, raio) circulo_cor_preenchido_desenha(imagem, centro, raio, _cor_preto)

// preenchidos com cor
void curva_cor_preenchido_desenha(PPM* imagem, Ponto pontoInicial, Ponto pm, Ponto pontoFinal, rgb cor);
void triangulo_cor_preenchido_desenha(PPM* imagem, Ponto centro, int altura, int base, rgb cor);
void retangulo_cor_preenchido_desenha(PPM* imagem, Ponto centro, int altura, int largura, rgb cor);
void losango_cor_preenchido_desenha(PPM* imagem, Ponto centro, int altura, int largura, rgb cor);
void circulo_cor_preenchido_desenha(PPM* imagem, Ponto centro, int raio, rgb cor);

// Fractais
void fractal_espiral_desenha(PPM* imagem, Ponto ponto_1, Ponto ponto_2);
void fractal_arvore_binaria_desenha(PPM* imagem, Ponto ponto, int tamanho);
void fractal_arvore_ternaria_desenha(PPM* imagem, Ponto ponto, int tamanho);
void fractal_circulo_recursivo_desenha(PPM* imagem, Ponto ponto, int raio);
void fractal_estrela_recursiva_desenha(PPM* imagem, Ponto ponto, int raio);
void fractal_cantor_desenha(PPM* imagem, Ponto ponto, int tamanho);
void fractal_koch_desenha(PPM* imagem, Ponto pontoInicial, Ponto pontoFinal);
void fractal_koch_2_desenha(PPM* imagem, Ponto pontoInicial, Ponto pontoFinal);
void fractal_dragon_desenha(PPM* imagem, Ponto pontoInicial, Ponto pontoFinal);
void fractal_dragon_cima_desenha(PPM* imagem, Ponto pontoInicial, Ponto pontoFinal);
void fractal_dragon_baixo_desenha(PPM* imagem, Ponto pontoInicial, Ponto pontoFinal);
void fractal_dragon_cor_desenha(PPM* imagem, Ponto pontoInicial, Ponto pontoFinal, rgb cor);
void fractal_dragon_cor_cima_desenha(PPM* imagem, Ponto pontoInicial, Ponto pontoFinal, rgb cor);
void fractal_dragon_cor_baixo_desenha(PPM* imagem, Ponto pontoInicial, Ponto pontoFinal, rgb cor);
void fractal_levy_dragon_desenha(PPM* imagem, Ponto pontoInicial, Ponto pontoFinal);

// Fractais sem nome
void fractal_fc_desenha(PPM* imagem, Ponto a, Ponto b);
void fractal_pit_desenha(PPM* imagem, Ponto centro, int lado, float graus);
void fractal_rec_desenha(PPM* imagem, Ponto ponto, int tamanho);
void fractal_rec2_desenha(PPM* imagem, Ponto ponto, int tamanho);
void fractal_rec3baixo_desenha(PPM* imagem, Ponto ponto, int tamanho);
void fractal_rec3cima_desenha(PPM* imagem, Ponto ponto, int tamanho);
void fractal_rec4_desenha(PPM* imagem, Ponto ponto, int tamanho);
void fractal_rec5_desenha(PPM* imagem, Ponto ponto, int tamanho, rgb cor);
void fractal_rec6_desenha(PPM* imagem, Ponto ponto, int tamanho);
void fractal_rec7_desenha(PPM* imagem, Ponto ponto, int tamanho, char direcao_x, char direcao_y);
void fractal_rec8_desenha(PPM* imagem, Ponto ponto, int tamanho);

#endif
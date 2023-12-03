#ifndef _LIB_VETORIAL_H_
#define _LIB_VETORIAL_H_

#include "internal.h"
#include "types.h"

// Poligonos
Poligono* Poligono_cria();
bool Poligono_vazio(Poligono* poligono);
void Poligono_esvazia(Poligono* poligono);
void Poligono_insere(Poligono* poligono, Ponto ponto);
Ponto Poligono_pop(Poligono* poligono);
NoDuploPonto* Poligono_busca(Poligono* poligono, Ponto ponto);
void Poligono_remove_ponto(Poligono* poligono, Ponto ponto);
void Poligono_libera(Poligono* poligono);

#define Poligono_desenha(imagem, poligono) Poligono_cor_desenha(imagem, poligono, _cor_preto)
void Poligono_cor_desenha(PPM* imagem, Poligono* poligono, rgb cor);

// Vetorial
void vetorial_retangulo(Poligono* poligono, Ponto centro, int altura, int largura);
void vetorial_triangulo(Poligono* poligono, Ponto centro, int altura, int base);
void vetorial_losango(Poligono* poligono, Ponto centro, int altura, int largura);
void vetorial_trapezio(Poligono* poligono, Ponto centro, int b1, int b2, int altura);
void vetorial_estrela(Poligono* poligono, Ponto ponto, int x, int y);
void vetorial_translada(Poligono* poligono, int vertical, int horizontal);
void vetorial_rotaciona(Poligono* poligono, float graus);
void vetorial_escala(Poligono* poligono, double escala);

// Minha Fonte
#define fonte_escreve_string(imagem, string, origem, tamanho) fonte_escreve_string_cor(imagem, string, origem, tamanho, _cor_preto)
#define fonte_escreve_char(imagem, caracter, origem, tamanho) fonte_escreve_char_cor(imagem, caracter, origem, tamanho, _cor_preto)
void fonte_escreve_string_cor(PPM* imagem, char string[], Ponto origem, int tamanho_fonte, rgb cor);
void fonte_escreve_char_cor(PPM* imagem, char c, Ponto o, int size, rgb cor);

#endif
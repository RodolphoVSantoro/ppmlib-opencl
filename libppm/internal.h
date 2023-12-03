#ifndef _INTERNAL_PPM_LIB_
#define _INTERNAL_PPM_LIB_

#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif

#ifndef PHI
#define PHI (1.618033988749894)
#endif

#ifndef NULL
#define NULL 0
#endif

#define graus2rad(graus) (graus * M_PI / 180.0)
#define rad2graus(radianos) (radianos * 180.0 / M_PI)

#include <stdio.h>

#include "libppm.h"
#include "types.h"

// Arquivos
FILE* fopen_or_crash(char fname[], char modo[]);

// Matematica
int int_quadrado(int numero);
int int_potencia(int base, int expoente);
void string_copia(char* destino, char* origem);
int string_compara(char* string1, char* string2);
int float_aproximacao(float val);
int int_valor_absoluto(int n);
void int_troca(int* a, int* b);
float graus_seno(float graus);
float graus_coseno(float graus);

// Árvores Binarias
ArvoreBinaria* ArvoreBinaria_cria();
ArvoreBinaria* ArvoreBinaria_folha_cria(int x);
ArvoreBinaria* ArvoreBinaria_insere_sem_repeticao(ArvoreBinaria* raiz, int x);
ArvoreBinaria* ArvoreBinaria_libera(ArvoreBinaria* raiz);
void ArvoreBinaria_imprime_pre_ordem(ArvoreBinaria* raiz);
int ArvoreBinaria_quantidade_nodes(ArvoreBinaria* raiz);

// Listas
void NoDuploPonto_libera(NoDuploPonto* lista);
// Lista de Cor
ListaCor* ListaCor_cria();
void ListaCor_insere_inicio(ListaCor* lista, rgb cor);
void ListaCor_insere_fim(ListaCor* lista, rgb cor);
void ListaCor_insere_sem_repeticao(ListaCor* lista, rgb cor);
void ListaCor_remove_inicio(ListaCor* lista);
void ListaCor_remove_fim(ListaCor* lista);
int ListaCor_busca_indice(ListaCor* lista, rgb cor);
void ListaCor_libera(ListaCor* lista);

Linha* Linha_aloca();                                                /*aloca lista de pontos vazia*/
bool Linha_vazia(Linha* linha);                                      /*verifica se a lista está vazia*/
void Linha_adiciona(Linha* linha, Ponto ponto);                      /*insere Ponto na lista*/
void Linha_cria(Linha* linha, Ponto pontoInicial, Ponto pontoFinal); /*insere pontos pertencentes a linha de ponto inicial até ponto final*/
void Linha_remove(Linha* linha, Ponto ponto);                        /*remove um Ponto da lista*/
void Linha_libera(Linha* linha);                                     /*remove todos os pontos*/

// minusculas
// preto
#define fonte_escreve_a(imagem, origem, tamanho_fonte) fonte_escreve_a_cor(imagem, origem, tamanho_fonte, _cor_preto)
#define fonte_escreve_b(imagem, origem, tamanho_fonte) fonte_escreve_b_cor(imagem, origem, tamanho_fonte, _cor_preto)
#define fonte_escreve_c(imagem, origem, tamanho_fonte) fonte_escreve_c_cor(imagem, origem, tamanho_fonte, _cor_preto)
#define fonte_escreve_d(imagem, origem, tamanho_fonte) fonte_escreve_d_cor(imagem, origem, tamanho_fonte, _cor_preto)
#define fonte_escreve_e(imagem, origem, tamanho_fonte) fonte_escreve_e_cor(imagem, origem, tamanho_fonte, _cor_preto)
#define fonte_escreve_f(imagem, origem, tamanho_fonte) fonte_escreve_f_cor(imagem, origem, tamanho_fonte, _cor_preto)
#define fonte_escreve_g(imagem, origem, tamanho_fonte) fonte_escreve_g_cor(imagem, origem, tamanho_fonte, _cor_preto)
#define fonte_escreve_h(imagem, origem, tamanho_fonte) fonte_escreve_h_cor(imagem, origem, tamanho_fonte, _cor_preto)
#define fonte_escreve_i(imagem, origem, tamanho_fonte) fonte_escreve_i_cor(imagem, origem, tamanho_fonte, _cor_preto)
#define fonte_escreve_j(imagem, origem, tamanho_fonte) fonte_escreve_j_cor(imagem, origem, tamanho_fonte, _cor_preto)
#define fonte_escreve_k(imagem, origem, tamanho_fonte) fonte_escreve_k_cor(imagem, origem, tamanho_fonte, _cor_preto)
#define fonte_escreve_l(imagem, origem, tamanho_fonte) fonte_escreve_l_cor(imagem, origem, tamanho_fonte, _cor_preto)
#define fonte_escreve_m(imagem, origem, tamanho_fonte) fonte_escreve_m_cor(imagem, origem, tamanho_fonte, _cor_preto)
#define fonte_escreve_n(imagem, origem, tamanho_fonte) fonte_escreve_n_cor(imagem, origem, tamanho_fonte, _cor_preto)
#define fonte_escreve_o(imagem, origem, tamanho_fonte) fonte_escreve_o_cor(imagem, origem, tamanho_fonte, _cor_preto)
#define fonte_escreve_p(imagem, origem, tamanho_fonte) fonte_escreve_p_cor(imagem, origem, tamanho_fonte, _cor_preto)
#define fonte_escreve_q(imagem, origem, tamanho_fonte) fonte_escreve_q_cor(imagem, origem, tamanho_fonte, _cor_preto)
#define fonte_escreve_r(imagem, origem, tamanho_fonte) fonte_escreve_r_cor(imagem, origem, tamanho_fonte, _cor_preto)
#define fonte_escreve_s(imagem, origem, tamanho_fonte) fonte_escreve_s_cor(imagem, origem, tamanho_fonte, _cor_preto)
#define fonte_escreve_t(imagem, origem, tamanho_fonte) fonte_escreve_t_cor(imagem, origem, tamanho_fonte, _cor_preto)
#define fonte_escreve_u(imagem, origem, tamanho_fonte) fonte_escreve_u_cor(imagem, origem, tamanho_fonte, _cor_preto)
#define fonte_escreve_v(imagem, origem, tamanho_fonte) fonte_escreve_v_cor(imagem, origem, tamanho_fonte, _cor_preto)
#define fonte_escreve_x(imagem, origem, tamanho_fonte) fonte_escreve_x_cor(imagem, origem, tamanho_fonte, _cor_preto)
#define fonte_escreve_z(imagem, origem, tamanho_fonte) fonte_escreve_z_cor(imagem, origem, tamanho_fonte, _cor_preto)

// cor
void fonte_escreve_a_cor(PPM* imagem, Ponto origem, int tamanho_fonte, rgb cor);
void fonte_escreve_b_cor(PPM* imagem, Ponto origem, int tamanho_fonte, rgb cor);
void fonte_escreve_c_cor(PPM* imagem, Ponto origem, int tamanho_fonte, rgb cor);
void fonte_escreve_d_cor(PPM* imagem, Ponto origem, int tamanho_fonte, rgb cor);
void fonte_escreve_e_cor(PPM* imagem, Ponto origem, int tamanho_fonte, rgb cor);
void fonte_escreve_f_cor(PPM* imagem, Ponto origem, int tamanho_fonte, rgb cor);
void fonte_escreve_g_cor(PPM* imagem, Ponto origem, int tamanho_fonte, rgb cor);
void fonte_escreve_h_cor(PPM* imagem, Ponto origem, int tamanho_fonte, rgb cor);
void fonte_escreve_i_cor(PPM* imagem, Ponto origem, int tamanho_fonte, rgb cor);
void fonte_escreve_j_cor(PPM* imagem, Ponto origem, int tamanho_fonte, rgb cor);
void fonte_escreve_k_cor(PPM* imagem, Ponto origem, int tamanho_fonte, rgb cor);
void fonte_escreve_l_cor(PPM* imagem, Ponto origem, int tamanho_fonte, rgb cor);
void fonte_escreve_m_cor(PPM* imagem, Ponto origem, int tamanho_fonte, rgb cor);
void fonte_escreve_n_cor(PPM* imagem, Ponto origem, int tamanho_fonte, rgb cor);
void fonte_escreve_o_cor(PPM* imagem, Ponto origem, int tamanho_fonte, rgb cor);
void fonte_escreve_p_cor(PPM* imagem, Ponto origem, int tamanho_fonte, rgb cor);
void fonte_escreve_q_cor(PPM* imagem, Ponto origem, int tamanho_fonte, rgb cor);
void fonte_escreve_r_cor(PPM* imagem, Ponto origem, int tamanho_fonte, rgb cor);
void fonte_escreve_s_cor(PPM* imagem, Ponto origem, int tamanho_fonte, rgb cor);
void fonte_escreve_t_cor(PPM* imagem, Ponto origem, int tamanho_fonte, rgb cor);
void fonte_escreve_u_cor(PPM* imagem, Ponto origem, int tamanho_fonte, rgb cor);
void fonte_escreve_v_cor(PPM* imagem, Ponto origem, int tamanho_fonte, rgb cor);
void fonte_escreve_x_cor(PPM* imagem, Ponto origem, int tamanho_fonte, rgb cor);
void fonte_escreve_z_cor(PPM* imagem, Ponto origem, int tamanho_fonte, rgb cor);

// maiusculas
// preto
#define fonte_escreve_S(imagem, origem, tamanho_fonte) fonte_escreve_S_cor(imagem, origem, tamanho_fonte, _cor_preto)
#define fonte_escreve_V(imagem, origem, tamanho_fonte) fonte_escreve_V_cor(imagem, origem, tamanho_fonte, _cor_preto)

// cor
void fonte_escreve_S_cor(PPM* imagem, Ponto origem, int tamanho_fonte, rgb cor);
void fonte_escreve_V_cor(PPM* imagem, Ponto origem, int tamanho_fonte, rgb cor);

// Simbolos

// preto
#define fonte_escreve_hifen(imagem, origem, tamanho_fonte) fonte_escreve_hifen_cor(imagem, origem, tamanho_fonte, _cor_preto)

// cor
void fonte_escreve_hifen_cor(PPM* imagem, Ponto origem, int tamanho_fonte, rgb cor);

#endif
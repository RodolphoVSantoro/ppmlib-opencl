#include <stdio.h>

#include "internal.h"
#include "libdesenho.h"
#include "libppm.h"
#include "libvetorial.h"

void fonte_escreve_string_cor(PPM* imagem, char string[], Ponto origem, int tamanho_fonte, rgb cor) {
    Ponto cursor = origem;
    for (int i = 0; string[i] != 0; i++) {
        fonte_escreve_char_cor(imagem, string[i], cursor, tamanho_fonte, cor);

        if (cursor.y + tamanho_fonte * 10 > imagem->cabecalho->tamanho->largura) {
            if (string[i + 1] != 0 && string[i + 1] != ' ') {
                cursor.y += tamanho_fonte * 4;
                fonte_escreve_hifen_cor(imagem, cursor, tamanho_fonte, cor);
            }
            cursor.y = origem.y;
            cursor.x += tamanho_fonte * 8;

        } else {
            cursor.y += tamanho_fonte * 4;
        }
    }
}

void fonte_escreve_char_cor(PPM* imagem, char c, Ponto origem, int tamanho_fonte, rgb cor) {
    switch (c) {
        case 'a':
            fonte_escreve_a_cor(imagem, origem, tamanho_fonte, cor);
            break;
        case 'b':
            fonte_escreve_b_cor(imagem, origem, tamanho_fonte, cor);
            break;
        case 'c':
            fonte_escreve_c_cor(imagem, origem, tamanho_fonte, cor);
            break;
        case 'd':
            fonte_escreve_d_cor(imagem, origem, tamanho_fonte, cor);
            break;
        case 'e':
            fonte_escreve_e_cor(imagem, origem, tamanho_fonte, cor);
            break;
        case 'f':
            fonte_escreve_f_cor(imagem, origem, tamanho_fonte, cor);
            break;
        case 'g':
            fonte_escreve_g_cor(imagem, origem, tamanho_fonte, cor);
            break;
        case 'h':
            fonte_escreve_h_cor(imagem, origem, tamanho_fonte, cor);
            break;
        case 'i':
            fonte_escreve_i_cor(imagem, origem, tamanho_fonte, cor);
            break;
        case 'j':
            fonte_escreve_j_cor(imagem, origem, tamanho_fonte, cor);
            break;
        case 'k':
            fonte_escreve_k_cor(imagem, origem, tamanho_fonte, cor);
            break;
        case 'l':
            fonte_escreve_l_cor(imagem, origem, tamanho_fonte, cor);
            break;
        case 'm':
            fonte_escreve_m_cor(imagem, origem, tamanho_fonte, cor);
            break;
        case 'n':
            fonte_escreve_n_cor(imagem, origem, tamanho_fonte, cor);
            break;
        case 'o':
            fonte_escreve_o_cor(imagem, origem, tamanho_fonte, cor);
            break;
        case 'p':
            fonte_escreve_p_cor(imagem, origem, tamanho_fonte, cor);
            break;
        case 'q':
            fonte_escreve_q_cor(imagem, origem, tamanho_fonte, cor);
            break;
        case 'r':
            fonte_escreve_r_cor(imagem, origem, tamanho_fonte, cor);
            break;
        case 's':
            fonte_escreve_s_cor(imagem, origem, tamanho_fonte, cor);
            break;
        case 't':
            fonte_escreve_t_cor(imagem, origem, tamanho_fonte, cor);
            break;
        case 'u':
            fonte_escreve_u_cor(imagem, origem, tamanho_fonte, cor);
            break;
        case 'v':
            fonte_escreve_v_cor(imagem, origem, tamanho_fonte, cor);
            break;
        case 'x':
            fonte_escreve_x_cor(imagem, origem, tamanho_fonte, cor);
            break;
        case 'z':
            fonte_escreve_z_cor(imagem, origem, tamanho_fonte, cor);
            break;
        case 'S':
            fonte_escreve_S_cor(imagem, origem, tamanho_fonte, cor);
            break;
        case 'V':
            fonte_escreve_V_cor(imagem, origem, tamanho_fonte, cor);
            break;
    }
}

/*Minusculas*/

// cor

void fonte_escreve_a_cor(PPM* imagem, Ponto origem, int tamanho_fonte, rgb cor) {
    int escala = 5 * tamanho_fonte;
    Ponto ponto[] = {
        Ponto_cria_estatico(origem.x, origem.y + 2 * escala / 5),
        Ponto_cria_estatico(origem.x + 2 * escala / 5, origem.y + escala / 5),
        Ponto_cria_estatico(origem.x + escala, origem.y + 2 * escala / 5),
        Ponto_cria_estatico(origem.x + 2 * escala / 5, origem.y + 7 * escala / 10),
        Ponto_cria_estatico(origem.x + 4 * escala / 5, origem.y + 4 * escala / 5),
        Ponto_cria_estatico(origem.x + 3 * escala / 5, origem.y + escala + escala / 10),
    };
    curva_cor_desenha(imagem, ponto[1], ponto[0], ponto[3], cor);
    curva_cor_desenha(imagem, ponto[1], ponto[2], ponto[3], cor);
    curva_cor_desenha(imagem, ponto[3], ponto[4], ponto[5], cor);
}

void fonte_escreve_b_cor(PPM* imagem, Ponto origem, int tamanho_fonte, rgb cor) {
    int escala = 4 * tamanho_fonte;
    origem.y += escala / 5;
    Ponto ponto[] = {
        Ponto_cria_estatico(origem.x + 4 * escala / 5, origem.y),
        Ponto_cria_estatico(origem.x + escala, origem.y + escala / 10),
        Ponto_cria_estatico(origem.x + 4 * escala / 5, origem.y + 3 * escala / 10),
        Ponto_cria_estatico(origem.x + escala / 5, origem.y + 3 * escala / 5),
        Ponto_cria_estatico(origem.x, origem.y + 3 * escala / 10),
        Ponto_cria_estatico(origem.x + escala / 5, origem.y + escala / 10),
        Ponto_cria_estatico(origem.x + escala, origem.y + escala / 5),
        Ponto_cria_estatico(origem.x + 4 * escala / 5, origem.y + 4 * escala / 5),
        Ponto_cria_estatico(origem.x + 11 * escala / 20, origem.y + 17 * escala / 20),
        Ponto_cria_estatico(origem.x + escala / 2, origem.y + 7 * escala / 10),
        Ponto_cria_estatico(origem.x + escala / 2, origem.y + escala),
    };
    curva_cor_desenha(imagem, ponto[0], ponto[1], ponto[2], cor);
    curva_cor_desenha(imagem, ponto[2], ponto[3], ponto[4], cor);
    curva_cor_desenha(imagem, ponto[4], ponto[5], ponto[2], cor);
    curva_cor_desenha(imagem, ponto[2], ponto[6], ponto[7], cor);
    curva_cor_desenha(imagem, ponto[7], ponto[8], ponto[9], cor);
    curva_cor_desenha(imagem, ponto[9], ponto[8], ponto[10], cor);
}

void fonte_escreve_c_cor(PPM* imagem, Ponto origem, int tamanho_fonte, rgb cor) {
    int escala = tamanho_fonte * 5;
    Ponto ponto[] = {
        Ponto_cria_estatico(origem.x + 3 * escala / 5, origem.y - escala / 20),
        Ponto_cria_estatico(origem.x + escala - escala / 5, origem.y + escala / 20),
        Ponto_cria_estatico(origem.x + 3 * escala / 5, origem.y + escala / 10),
        Ponto_cria_estatico(origem.x + escala / 5, origem.y + 5 * escala / 10),
        Ponto_cria_estatico(origem.x, origem.y + 19 * escala / 20),
        Ponto_cria_estatico(origem.x + 3 * escala / 5, origem.y + 5 * escala / 10),
        Ponto_cria_estatico(origem.x + 4 * escala / 5, origem.y + 4 * escala / 5),
        Ponto_cria_estatico(origem.x + 7 * escala / 10, origem.y + 9 * escala / 10),
    };
    curva_cor_desenha(imagem, ponto[0], ponto[1], ponto[2], cor);
    curva_cor_desenha(imagem, ponto[2], ponto[3], ponto[4], cor);
    curva_cor_desenha(imagem, ponto[4], ponto[3], ponto[5], cor);
    curva_cor_desenha(imagem, ponto[5], ponto[6], ponto[7], cor);
}

void fonte_escreve_d_cor(PPM* imagem, Ponto origem, int tamanho_fonte, rgb cor) {
    int escala = tamanho_fonte * 5;
    origem.x -= escala / 10;
    origem.y -= escala / 5;
    Ponto ponto[] = {
        Ponto_cria_estatico(origem.x + 4 * escala / 5, origem.y + escala / 5),
        Ponto_cria_estatico(origem.x + 7 * escala / 10, origem.y + escala / 10),
        Ponto_cria_estatico(origem.x + 7 * escala / 10, origem.y + 4 * escala / 10),
        Ponto_cria_estatico(origem.x + 2 * escala / 5, origem.y + escala / 2),
        Ponto_cria_estatico(origem.x + 2 * escala / 5, origem.y + 8 * escala / 10),
        Ponto_cria_estatico(origem.x + escala / 5, origem.y + 15 * escala / 20),
        Ponto_cria_estatico(origem.x, origem.y + 9 * escala / 10),
        Ponto_cria_estatico(origem.x + 7 * escala / 10, origem.y + 7 * escala / 10),
        Ponto_cria_estatico(origem.x + 4 * escala / 5, origem.y + escala),
        Ponto_cria_estatico(origem.x + escala, origem.y + escala / 2),
        Ponto_cria_estatico(origem.x + 7 * escala / 10, origem.y + 8 * escala / 10),
    };
    curva_cor_desenha(imagem, ponto[0], ponto[1], ponto[4], cor);
    curva_cor_desenha(imagem, ponto[2], ponto[3], ponto[4], cor);
    curva_cor_desenha(imagem, ponto[4], ponto[5], ponto[6], cor);
    curva_cor_desenha(imagem, ponto[4], ponto[7], ponto[8], cor);
    curva_cor_desenha(imagem, ponto[2], ponto[9], ponto[10], cor);
}

void fonte_escreve_e_cor(PPM* imagem, Ponto origem, int tamanho_fonte, rgb cor) {
    int escala = tamanho_fonte * 5;
    Ponto ponto[] = {
        Ponto_cria_estatico(origem.x + 7 * escala / 10, origem.y),
        Ponto_cria_estatico(origem.x + 9 * escala / 10, origem.y + escala / 5),
        Ponto_cria_estatico(origem.x + 7 * escala / 10, origem.y + escala / 2),
        Ponto_cria_estatico(origem.x + escala / 10, origem.y + 9 * escala / 10),
        Ponto_cria_estatico(origem.x + escala / 10, origem.y + 7 * escala / 10),
        Ponto_cria_estatico(origem.x + escala / 10, origem.y + 3 * escala / 10),
        Ponto_cria_estatico(origem.x + 11 * escala / 10, origem.y + 4 * escala / 5),
        Ponto_cria_estatico(origem.x + 7 * escala / 10, origem.y + escala),
    };
    curva_cor_desenha(imagem, ponto[0], ponto[1], ponto[2], cor);
    curva_cor_desenha(imagem, ponto[2], ponto[3], ponto[4], cor);
    curva_cor_desenha(imagem, ponto[4], ponto[5], ponto[2], cor);
    curva_cor_desenha(imagem, ponto[2], ponto[6], ponto[7], cor);
}

void fonte_escreve_f_cor(PPM* imagem, Ponto origem, int tamanho_fonte, rgb cor) {
    int escala = tamanho_fonte * 5;
    origem.x -= escala / 10;
    Ponto ponto[] = {
        Ponto_cria_estatico(origem.x + escala, origem.y),
        Ponto_cria_estatico(origem.x + 17 * escala / 20, origem.y + 5 * escala / 18),
        Ponto_cria_estatico(origem.x + 6 * escala / 10, origem.y + escala / 2),
        Ponto_cria_estatico(origem.x + 3 * escala / 10, origem.y + 7 * escala / 9),
        Ponto_cria_estatico(origem.x + escala / 10, origem.y + 2 * escala / 3),
        Ponto_cria_estatico(origem.x + 2 * escala / 10, origem.y + 4 * escala / 9),
        Ponto_cria_estatico(origem.x + 11 * escala / 10, origem.y + 7 * escala / 18),
        Ponto_cria_estatico(origem.x + 15 * escala / 10, origem.y + 2 * escala / 3),
        Ponto_cria_estatico(origem.x + 10 * escala / 10, origem.y + 8 * escala / 9),
        Ponto_cria_estatico(origem.x + 9 * escala / 10, origem.y + 5 * escala / 9),
        Ponto_cria_estatico(origem.x + 5 * escala / 10, origem.y + 4 * escala / 5),
    };
    curva_cor_desenha(imagem, ponto[0], ponto[1], ponto[2], cor);
    curva_cor_desenha(imagem, ponto[2], ponto[3], ponto[4], cor);
    curva_cor_desenha(imagem, ponto[4], ponto[5], ponto[2], cor);
    curva_cor_desenha(imagem, ponto[2], ponto[6], ponto[7], cor);
    curva_cor_desenha(imagem, ponto[7], ponto[8], ponto[2], cor);
    curva_cor_desenha(imagem, ponto[2], ponto[9], ponto[10], cor);
}

void fonte_escreve_g_cor(PPM* imagem, Ponto origem, int tamanho_fonte, rgb cor) {
    int escala = tamanho_fonte * 5;
    origem.x -= escala / 10;
    Ponto ponto[] = {
        Ponto_cria_estatico(origem.x + 3 * escala / 10, origem.y + 7 * escala / 9),
        Ponto_cria_estatico(origem.x + escala / 10, origem.y + 3 * escala / 9),
        Ponto_cria_estatico(origem.x + 8 * escala / 10, origem.y + 2 * escala / 9),
        Ponto_cria_estatico(origem.x + 7 * escala / 10, origem.y + 5 * escala / 9),
        Ponto_cria_estatico(origem.x + 13 * escala / 10, origem.y + 6 * escala / 9),
        Ponto_cria_estatico(origem.x + 14 * escala / 10, origem.y + 3 * escala / 9),
        Ponto_cria_estatico(origem.x + 9 * escala / 10, origem.y + 4 * escala / 9),
        Ponto_cria_estatico(origem.x + 3 * escala / 10, origem.y + escala),
    };
    curva_cor_desenha(imagem, ponto[0], ponto[1], ponto[2], cor);
    curva_cor_desenha(imagem, ponto[2], ponto[3], ponto[0], cor);
    curva_cor_desenha(imagem, ponto[0], ponto[4], ponto[5], cor);
    curva_cor_desenha(imagem, ponto[5], ponto[6], ponto[7], cor);
}

void fonte_escreve_h_cor(PPM* imagem, Ponto origem, int tamanho_fonte, rgb cor) {
    int escala = tamanho_fonte * 5;
    origem.x -= escala / 10;
    Ponto ponto[] = {
        Ponto_cria_estatico(origem.x + 19 * escala / 20, origem.y),
        Ponto_cria_estatico(origem.x + escala, origem.y + escala / 8),
        Ponto_cria_estatico(origem.x + 7 * escala / 10, origem.y + 2 * escala / 8),
        Ponto_cria_estatico(origem.x + escala, origem.y + 3 * escala / 16),
        Ponto_cria_estatico(origem.x + escala / 2, origem.y + 3 * escala / 8),
        Ponto_cria_estatico(origem.x + escala / 10, origem.y + 6 * escala / 8),
        Ponto_cria_estatico(origem.x + 2 * escala / 5, origem.y + 5 * escala / 8),
        Ponto_cria_estatico(origem.x + 4 * escala / 5, origem.y + 6 * escala / 8),
        Ponto_cria_estatico(origem.x + escala, origem.y + 7 * escala / 8),
        Ponto_cria_estatico(origem.x + 9 * escala / 10, origem.y + escala),
    };
    curva_cor_desenha(imagem, ponto[0], ponto[1], ponto[2], cor);
    curva_cor_desenha(imagem, ponto[3], ponto[4], ponto[5], cor);
    curva_cor_desenha(imagem, ponto[2], ponto[6], ponto[7], cor);
    curva_cor_desenha(imagem, ponto[7], ponto[8], ponto[9], cor);
}

void fonte_escreve_i_cor(PPM* imagem, Ponto origem, int tamanho_fonte, rgb cor) {
    int escala = tamanho_fonte * 5;
    origem.x -= 3 * escala / 10;
    Ponto ponto[] = {
        Ponto_cria_estatico(origem.x + escala, origem.y),
        Ponto_cria_estatico(origem.x + 9 * escala / 10, origem.y + escala / 5),
        Ponto_cria_estatico(origem.x + 2 * escala / 5, origem.y + escala / 2),
        Ponto_cria_estatico(origem.x + 4 * escala / 5, origem.y + 3 * escala / 5),
        Ponto_cria_estatico(origem.x + 9 * escala / 10, origem.y + 9 * escala / 10),
        Ponto_cria_estatico(origem.x + escala / 5, origem.y + escala / 2),
    };
    curva_cor_desenha(imagem, ponto[0], ponto[1], ponto[2], cor);
    curva_cor_desenha(imagem, ponto[2], ponto[3], ponto[4], cor);
    circulo_cor_preenchido_desenha(imagem, ponto[5], tamanho_fonte / 100 + 1, cor);
}

void fonte_escreve_j_cor(PPM* imagem, Ponto origem, int tamanho_fonte, rgb cor) {
    int escala = tamanho_fonte * 5;
    origem.x -= escala / 10;
    Ponto ponto[] = {
        Ponto_cria_estatico(origem.x + 8 * escala / 10, origem.y),
        Ponto_cria_estatico(origem.x + 4 * escala / 5, origem.y + 3 * escala / 8),
        Ponto_cria_estatico(origem.x + 2 * escala / 5, origem.y + 9 * escala / 16),
        Ponto_cria_estatico(origem.x + 7 * escala / 10, origem.y + 4 * escala / 8),
        Ponto_cria_estatico(origem.x + escala, origem.y + 5 * escala / 8),
        Ponto_cria_estatico(origem.x + 7 * escala / 5, origem.y + 11 * escala / 16),
        Ponto_cria_estatico(origem.x + 8 * escala / 5, origem.y + 4 * escala / 8),
        Ponto_cria_estatico(origem.x + 13 * escala / 10, origem.y + escala / 6),
        Ponto_cria_estatico(origem.x + 2 * escala / 5, origem.y + 7 * escala / 8),
        Ponto_cria_estatico(origem.x + escala / 5, origem.y + 9 * escala / 16),
    };
    curva_cor_desenha(imagem, ponto[0], ponto[1], ponto[2], cor);
    curva_cor_desenha(imagem, ponto[2], ponto[3], ponto[4], cor);
    curva_cor_desenha(imagem, ponto[4], ponto[5], ponto[6], cor);
    curva_cor_desenha(imagem, ponto[6], ponto[7], ponto[3], cor);
    linha_cor_desenha(imagem, ponto[3], ponto[8], cor);
    circulo_cor_preenchido_desenha(imagem, ponto[9], tamanho_fonte / 100 + 1, cor);
}

void fonte_escreve_k_cor(PPM* imagem, Ponto origem, int tamanho_fonte, rgb cor) {
    int escala = tamanho_fonte * 4;
    Ponto ponto[] = {
        Ponto_cria_estatico(origem.x + escala, origem.y),
        Ponto_cria_estatico(origem.x + 3 * escala / 5, origem.y + escala / 5),
        Ponto_cria_estatico(origem.x, origem.y),
        Ponto_cria_estatico(origem.x + 4 * escala / 5, origem.y + 7 * escala / 10),
        Ponto_cria_estatico(origem.x + escala, origem.y + escala),
        Ponto_cria_estatico(origem.x + 3 * escala / 5, origem.y + 2 * escala / 5),
        Ponto_cria_estatico(origem.x, origem.y + escala),
    };
    Ponto l = Ponto_cria_estatico(origem.x + 3 * escala / 5, origem.y + escala / 10);
    curva_cor_desenha(imagem, ponto[0], ponto[1], ponto[2], cor);
    curva_cor_desenha(imagem, l, ponto[3], ponto[4], cor);
    curva_cor_desenha(imagem, l, ponto[5], ponto[6], cor);
}

void fonte_escreve_l_cor(PPM* imagem, Ponto origem, int tamanho_fonte, rgb cor) {
    int escala = tamanho_fonte * 5;
    origem.x -= escala / 20;
    Ponto ponto[] = {
        Ponto_cria_estatico(origem.x + 8 * escala / 10, origem.y),
        Ponto_cria_estatico(origem.x + escala, origem.y + escala / 5),
        Ponto_cria_estatico(origem.x + 8 * escala / 10, origem.y + escala / 2),
        Ponto_cria_estatico(origem.x + escala / 10, origem.y + 8 * escala / 10),
        Ponto_cria_estatico(origem.x - escala / 10, origem.y + 6 * escala / 10),
        Ponto_cria_estatico(origem.x + escala / 10, origem.y + 2 * escala / 10),
        Ponto_cria_estatico(origem.x + 12 * escala / 10, origem.y + 4 * escala / 5),
        Ponto_cria_estatico(origem.x + 8 * escala / 10, origem.y + escala),
    };
    curva_cor_desenha(imagem, ponto[0], ponto[1], ponto[2], cor);
    curva_cor_desenha(imagem, ponto[2], ponto[3], ponto[4], cor);
    curva_cor_desenha(imagem, ponto[4], ponto[5], ponto[2], cor);
    curva_cor_desenha(imagem, ponto[2], ponto[6], ponto[7], cor);
}

void fonte_escreve_m_cor(PPM* imagem, Ponto origem, int tamanho_fonte, rgb cor) {
    int escala = tamanho_fonte * 5;
    origem.x -= 3 * escala / 10;
    Ponto ponto[] = {
        Ponto_cria_estatico(origem.x + escala, origem.y - escala / 10),
        Ponto_cria_estatico(origem.x, origem.y + escala / 6),
        Ponto_cria_estatico(origem.x + escala, origem.y + 2 * escala / 6),
        Ponto_cria_estatico(origem.x, origem.y + 3 * escala / 6 + escala / 10),
        Ponto_cria_estatico(origem.x + escala, origem.y + 4 * escala / 6),
        Ponto_cria_estatico(origem.x, origem.y + 5 * escala / 6 + escala / 10),
        Ponto_cria_estatico(origem.x + escala, origem.y + 9 * escala / 10),
    };
    curva_cor_desenha(imagem, ponto[0], ponto[1], ponto[2], cor);
    curva_cor_desenha(imagem, ponto[2], ponto[3], ponto[4], cor);
    curva_cor_desenha(imagem, ponto[4], ponto[5], ponto[6], cor);
}

void fonte_escreve_n_cor(PPM* imagem, Ponto origem, int tamanho_fonte, rgb cor) {
    int escala = tamanho_fonte * 5;
    origem.x -= 3 * escala / 10;
    Ponto ponto[] = {
        Ponto_cria_estatico(origem.x + escala, origem.y),
        Ponto_cria_estatico(origem.x + escala / 4, origem.y + 7 * escala / 20),
        Ponto_cria_estatico(origem.x + 9 * escala / 10, origem.y + 9 * escala / 20),
        Ponto_cria_estatico(origem.x + 2 * escala / 5, origem.y + 8 * escala / 10),
        Ponto_cria_estatico(origem.x + escala, origem.y + escala),
    };
    curva_cor_desenha(imagem, ponto[0], ponto[1], ponto[2], cor);
    curva_cor_desenha(imagem, ponto[2], ponto[3], ponto[4], cor);
}

void fonte_escreve_o_cor(PPM* imagem, Ponto origem, int tamanho_fonte, rgb cor) {
    int escala = tamanho_fonte * 4;
    origem.x += escala / 10;
    origem.y += escala / 10;
    Ponto ponto[] = {
        Ponto_cria_estatico(origem.x, origem.y + 4 * escala / 5),
        Ponto_cria_estatico(origem.x, origem.y),
        Ponto_cria_estatico(origem.x + 4 * escala / 5, origem.y + escala / 10),
        Ponto_cria_estatico(origem.x + escala, origem.y + 4 * escala / 5),
        Ponto_cria_estatico(origem.x - escala / 14, origem.y + escala / 5),
        Ponto_cria_estatico(origem.x + 2 * escala / 5, origem.y + escala / 2),
        Ponto_cria_estatico(origem.x + escala / 2, origem.y + 4 * escala / 5),
        Ponto_cria_estatico(origem.x + escala / 5, origem.y + escala + escala / 10),
    };
    curva_cor_desenha(imagem, ponto[0], ponto[1], ponto[2], cor);
    curva_cor_desenha(imagem, ponto[2], ponto[3], ponto[0], cor);
    curva_cor_desenha(imagem, ponto[0], ponto[4], ponto[5], cor);
    curva_cor_desenha(imagem, ponto[5], ponto[6], ponto[7], cor);
}

void fonte_escreve_p_cor(PPM* imagem, Ponto origem, int tamanho_fonte, rgb cor) {
    int escala = tamanho_fonte * 5;
    Ponto ponto[] = {
        Ponto_cria_estatico(origem.x + 13 * escala / 20, origem.y + 2 * escala / 13),
        Ponto_cria_estatico(origem.x + 5 * escala / 10, origem.y + 5 * escala / 13),
        Ponto_cria_estatico(origem.x + escala / 5, origem.y + 7 * escala / 13),
        Ponto_cria_estatico(origem.x + 7 * escala / 5, origem.y + escala / 13),
        Ponto_cria_estatico(origem.x + 2 * escala / 5, origem.y + 6 * escala / 13),
        Ponto_cria_estatico(origem.x + 3 * escala / 5, origem.y + 11 * escala / 13),
        Ponto_cria_estatico(origem.x + 4 * escala / 5, origem.y + 5 * escala / 13),
        Ponto_cria_estatico(origem.x + 9 * escala / 10, origem.y + 10 * escala / 13),
        Ponto_cria_estatico(origem.x + 3 * escala / 5, origem.y + escala),
    };
    curva_cor_desenha(imagem, ponto[0], ponto[1], ponto[2], cor);
    linha_cor_desenha(imagem, ponto[2], ponto[3], cor);
    curva_cor_desenha(imagem, ponto[2], ponto[6], ponto[3], cor);
    curva_cor_desenha(imagem, ponto[4], ponto[5], ponto[6], cor);
    curva_cor_desenha(imagem, ponto[6], ponto[7], ponto[8], cor);
}

void fonte_escreve_q_cor(PPM* imagem, Ponto origem, int tamanho_fonte, rgb cor) {
    int escala = tamanho_fonte * 5;
    origem.x -= 3 * escala / 10;
    Ponto ponto[] = {
        Ponto_cria_estatico(origem.x + 2 * escala / 5, origem.y + 6 * escala / 8),
        Ponto_cria_estatico(origem.x + 3 * escala / 5, origem.y + escala / 8),
        Ponto_cria_estatico(origem.x + escala, origem.y + 4 * escala / 8),
        Ponto_cria_estatico(origem.x + 6 * escala / 5, origem.y + 2 * escala / 8),
        Ponto_cria_estatico(origem.x + 8 * escala / 5, origem.y + 5 * escala / 8),
        Ponto_cria_estatico(origem.x + 6 * escala / 5, origem.y + escala),
        Ponto_cria_estatico(origem.x + 9 * escala / 10, origem.y + 9 * escala / 16),
        Ponto_cria_estatico(origem.x + escala, origem.y + 7 * escala / 8),
        Ponto_cria_estatico(origem.x + 4 * escala / 5, origem.y + escala),
    };
    curva_cor_desenha(imagem, ponto[0], ponto[1], ponto[2], cor);
    curva_cor_desenha(imagem, ponto[0], ponto[3], ponto[4], cor);
    curva_cor_desenha(imagem, ponto[4], ponto[5], ponto[6], cor);
    curva_cor_desenha(imagem, ponto[2], ponto[7], ponto[8], cor);
}

void fonte_escreve_r_cor(PPM* imagem, Ponto origem, int tamanho_fonte, rgb cor) {
    int escala = tamanho_fonte * 5;
    Ponto ponto[] = {
        Ponto_cria_estatico(origem.x + escala, origem.y),
        Ponto_cria_estatico(origem.x + 3 * escala / 5, origem.y + escala / 4),
        Ponto_cria_estatico(origem.x + escala / 10, origem.y + escala / 4),
        Ponto_cria_estatico(origem.x + 2 * escala / 5, origem.y + escala / 2),
        Ponto_cria_estatico(origem.x + escala / 5, origem.y + 7 * escala / 8),
        Ponto_cria_estatico(origem.x + 3 * escala / 5, origem.y + 5 * escala / 8),
        Ponto_cria_estatico(origem.x + escala, origem.y + escala),
    };
    curva_cor_desenha(imagem, ponto[0], ponto[1], ponto[2], cor);
    curva_cor_desenha(imagem, ponto[2], ponto[3], ponto[4], cor);
    curva_cor_desenha(imagem, ponto[4], ponto[5], ponto[6], cor);
}

void fonte_escreve_s_cor(PPM* imagem, Ponto origem, int tamanho_fonte, rgb cor) {
    int escala = tamanho_fonte * 5;
    origem.x -= escala / 5;
    Ponto ponto[] = {
        Ponto_cria_estatico(origem.x + escala, origem.y),
        Ponto_cria_estatico(origem.x + 4 * escala / 5, origem.y + escala / 2),
        Ponto_cria_estatico(origem.x + 3 * escala / 10, origem.y + 2 * escala / 5),
        Ponto_cria_estatico(origem.x + escala, origem.y + escala),
        Ponto_cria_estatico(origem.x + escala, origem.y + 3 * escala / 5),
    };
    curva_cor_desenha(imagem, ponto[0], ponto[1], ponto[2], cor);
    curva_cor_desenha(imagem, ponto[2], ponto[3], ponto[4], cor);
}

void fonte_escreve_t_cor(PPM* imagem, Ponto origem, int tamanho_fonte, rgb cor) {
    int escala = tamanho_fonte * 5;
    Ponto ponto[] = {
        Ponto_cria_estatico(origem.x + escala, origem.y),
        Ponto_cria_estatico(origem.x + 4 * escala / 5, origem.y + 4 * escala / 7),
        Ponto_cria_estatico(origem.x + escala / 5, origem.y + 5 * escala / 14),
        Ponto_cria_estatico(origem.x + 4 * escala / 5, origem.y + 3 * escala / 14),
        Ponto_cria_estatico(origem.x + escala, origem.y + escala),
        Ponto_cria_estatico(origem.x + 3 * escala / 10, origem.y + escala / 14),
        Ponto_cria_estatico(origem.x + 5 * escala / 10, origem.y + 4 * escala / 7),
        Ponto_cria_estatico(origem.x + escala / 5, origem.y + 6 * escala / 7),
    };
    curva_cor_desenha(imagem, ponto[0], ponto[1], ponto[2], cor);
    curva_cor_desenha(imagem, ponto[2], ponto[3], ponto[4], cor);
    curva_cor_desenha(imagem, ponto[5], ponto[6], ponto[7], cor);
}

void fonte_escreve_u_cor(PPM* imagem, Ponto origem, int tamanho_fonte, rgb cor) {
    int escala = tamanho_fonte * 5;
    Ponto ponto[] = {
        Ponto_cria_estatico(origem.x + escala, origem.y),
        Ponto_cria_estatico(origem.x + 9 * escala / 10, origem.y + escala / 7),
        Ponto_cria_estatico(origem.x + escala / 5, origem.y + 5 * escala / 14),
        Ponto_cria_estatico(origem.x + 3 * escala / 2, origem.y + escala / 2),
        Ponto_cria_estatico(origem.x + escala / 5, origem.y + 5 * escala / 7),
        Ponto_cria_estatico(origem.x + 8 * escala / 10, origem.y + 6 * escala / 7),
        Ponto_cria_estatico(origem.x + 9 * escala / 10, origem.y + escala),
    };
    curva_cor_desenha(imagem, ponto[0], ponto[1], ponto[2], cor);
    curva_cor_desenha(imagem, ponto[2], ponto[3], ponto[4], cor);
    curva_cor_desenha(imagem, ponto[4], ponto[5], ponto[6], cor);
}

void fonte_escreve_v_cor(PPM* imagem, Ponto origem, int tamanho_fonte, rgb cor) {
    int escala = tamanho_fonte * 5;
    origem.x += escala / 10;
    Ponto ponto[] = {
        Ponto_cria_estatico(origem.x + 3 * escala / 5, origem.y),
        Ponto_cria_estatico(origem.x + escala / 5, origem.y + escala / 10),
        Ponto_cria_estatico(origem.x + 3 * escala / 10, origem.y + 3 * escala / 10),
        Ponto_cria_estatico(origem.x + 6 * escala / 5, origem.y + 6 * escala / 10),
        Ponto_cria_estatico(origem.x + 3 * escala / 10, origem.y + 8 * escala / 10),
        Ponto_cria_estatico(origem.x + escala / 10, origem.y + 7 * escala / 10),
        Ponto_cria_estatico(origem.x + 3 * escala / 10, origem.y + 6 * escala / 10),
        Ponto_cria_estatico(origem.x + 2 * escala / 5, origem.y + escala),
    };
    curva_cor_desenha(imagem, ponto[0], ponto[1], ponto[2], cor);
    curva_cor_desenha(imagem, ponto[2], ponto[3], ponto[4], cor);
    curva_cor_desenha(imagem, ponto[4], ponto[5], ponto[6], cor);
    linha_cor_desenha(imagem, ponto[6], ponto[7], cor);
}

void fonte_escreve_x_cor(PPM* imagem, Ponto origem, int tamanho_fonte, rgb cor) {
    int escala = tamanho_fonte * 5;
    Ponto ponto[] = {
        Ponto_cria_estatico(origem.x + 3 * escala / 5, origem.y),
        Ponto_cria_estatico(origem.x + escala / 10, origem.y + 2 * escala / 7),
        Ponto_cria_estatico(origem.x + escala / 5, origem.y + 4 * escala / 7),
        Ponto_cria_estatico(origem.x + 3 * escala / 10, origem.y + 9 * escala / 14),
        Ponto_cria_estatico(origem.x + 3 * escala / 5, origem.y + 9 * escala / 14),
        Ponto_cria_estatico(origem.x + escala, origem.y + escala / 2),
        Ponto_cria_estatico(origem.x + 4 * escala / 5, origem.y + escala / 7),
        Ponto_cria_estatico(origem.x + 3 * escala / 10, origem.y + 5 * escala / 7),
        Ponto_cria_estatico(origem.x + escala / 5, origem.y + escala),
        Ponto_cria_estatico(origem.x + 9 * escala / 10, origem.y + 5 * escala / 7),
        Ponto_cria_estatico(origem.x + escala, origem.y + escala),
    };
    curva_cor_desenha(imagem, ponto[0], ponto[1], ponto[2], cor);
    curva_cor_desenha(imagem, ponto[2], ponto[3], ponto[4], cor);
    curva_cor_desenha(imagem, ponto[4], ponto[5], ponto[6], cor);
    curva_cor_desenha(imagem, ponto[4], ponto[7], ponto[8], cor);
    curva_cor_desenha(imagem, ponto[4], ponto[9], ponto[10], cor);
}

void fonte_escreve_z_cor(PPM* imagem, Ponto origem, int tamanho_fonte, rgb cor) {
    int escala = tamanho_fonte * 5;
    Ponto ponto[] = {
        Ponto_cria_estatico(origem.x + 2 * escala / 5, origem.y + 2 * escala / 13),
        Ponto_cria_estatico(origem.x, origem.y + 8 * escala / 13),
        Ponto_cria_estatico(origem.x + 2 * escala / 5, origem.y + 11 * escala / 13),
        Ponto_cria_estatico(origem.x + escala / 2, origem.y + 8 * escala / 13),
        Ponto_cria_estatico(origem.x + 6 * escala / 10, origem.y + 6 * escala / 13),
        Ponto_cria_estatico(origem.x + 6 * escala / 5, origem.y + 11 * escala / 13),
        Ponto_cria_estatico(origem.x + 8 * escala / 5, origem.y + 7 * escala / 13),
        Ponto_cria_estatico(origem.x + 4 * escala / 5, origem.y + 7 * escala / 13),
        Ponto_cria_estatico(origem.x + 3 * escala / 5, origem.y + escala),
    };
    curva_cor_desenha(imagem, ponto[0], ponto[1], ponto[2], cor);
    curva_cor_desenha(imagem, ponto[2], ponto[3], ponto[4], cor);
    curva_cor_desenha(imagem, ponto[4], ponto[5], ponto[6], cor);
    curva_cor_desenha(imagem, ponto[6], ponto[7], ponto[8], cor);
}

/*Maiusculas*/

// cor

void fonte_escreve_S_cor(PPM* imagem, Ponto origem, int tamanho_fonte, rgb cor) {
    int escala = tamanho_fonte * 5;
    origem.x -= escala;
    Ponto ponto[] = {
        Ponto_cria_estatico(origem.x + 7 * escala / 5, origem.y),
        Ponto_cria_estatico(origem.x + 2 * escala, origem.y + 3 * escala / 7),
        Ponto_cria_estatico(origem.x + 9 * escala / 5, origem.y + 5 * escala / 7),
        Ponto_cria_estatico(origem.x + 8 * escala / 5, origem.y + escala),
        Ponto_cria_estatico(origem.x + 6 * escala / 5, origem.y + 4 * escala / 7),
        Ponto_cria_estatico(origem.x + 4 * escala / 5, origem.y + 5 * escala / 14),
        Ponto_cria_estatico(origem.x + 2 * escala / 5, origem.y + 5 * escala / 7),
        Ponto_cria_estatico(origem.x + escala / 5, origem.y + 6 * escala / 7),
        Ponto_cria_estatico(origem.x + escala / 5, origem.y + escala),
    };
    curva_cor_desenha(imagem, ponto[0], ponto[1], ponto[2], cor);
    curva_cor_desenha(imagem, ponto[2], ponto[3], ponto[4], cor);
    curva_cor_desenha(imagem, ponto[4], ponto[5], ponto[6], cor);
    curva_cor_desenha(imagem, ponto[6], ponto[7], ponto[8], cor);
}

void fonte_escreve_V_cor(PPM* imagem, Ponto origem, int tamanho_fonte, rgb cor) {
    int escala = tamanho_fonte * 5;
    origem.x -= escala;
    Ponto ponto[] = {
        Ponto_cria_estatico(origem.x + escala / 5, origem.y - escala / 5),
        Ponto_cria_estatico(origem.x + 4 * escala / 5, origem.y + escala / 6),
        Ponto_cria_estatico(origem.x + 2 * escala, origem.y + escala / 3),
        Ponto_cria_estatico(origem.x + escala, origem.y + escala / 2),
        Ponto_cria_estatico(origem.x, origem.y + 13 * escala / 15),
    };
    curva_cor_desenha(imagem, ponto[0], ponto[1], ponto[2], cor);
    curva_cor_desenha(imagem, ponto[2], ponto[3], ponto[4], cor);
}

// Simbolos

// cor

void fonte_escreve_hifen_cor(PPM* imagem, Ponto origem, int tamanho_fonte, rgb cor) {
    int escala = tamanho_fonte * 5;
    Ponto ponto[] = {
        Ponto_cria_estatico(origem.x + 4 * escala / 10, origem.y + escala / 10),
        Ponto_cria_estatico(origem.x + 6 * escala / 10, origem.y + 4 * escala / 10),
        Ponto_cria_estatico(origem.x + 5 * escala / 10, origem.y + 9 * escala / 10),
    };
    curva_cor_desenha(imagem, ponto[0], ponto[1], ponto[2], cor);
}

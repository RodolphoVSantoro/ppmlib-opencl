#ifndef _TYPES_PPMLIB_H_
#define _TYPES_PPMLIB_H_

#ifndef ARQUIVO
#define ARQUIVO
struct Arquivo {
    char** linha;
    int linhas;
};
typedef struct Arquivo Arquivo;
#endif

enum BOOL {
    false = 0,
    true = 1
};
typedef enum BOOL bool;

enum DIRECAO {
    esquerda = 0,
    direita = 1,
    cima = 2,
    baixo = 3
};
typedef enum DIRECAO Direcao;

typedef unsigned char uchar;

typedef unsigned long long int lint;

struct Ponto {
    int x, y;
};
typedef struct Ponto Ponto;

struct RGB {
    uchar red, green, blue;
};
typedef struct RGB rgb;

struct ArvoreBinaria {
    int x;
    struct ArvoreBinaria* esquerda;
    struct ArvoreBinaria* direita;
};
typedef struct ArvoreBinaria ArvoreBinaria;

struct LISTA_Ponto {
    Ponto ponto;
    struct LISTA_Ponto* proximo;
};
typedef struct LISTA_Ponto ListaPonto;

struct NO_PONTO_DUPLO {
    Ponto ponto;
    struct NO_PONTO_DUPLO* proximo;
    struct NO_PONTO_DUPLO* anterior;
};
typedef struct NO_PONTO_DUPLO NoDuploPonto;

struct LINHA {
    ListaPonto* primeiro;
    ListaPonto* ultimo;
};
typedef struct LINHA Linha;

struct NODECOR {
    rgb cor;
    struct NODECOR* proximo;
    struct NODECOR* anterior;
};
typedef struct NODECOR NodeCor;

struct LISTA_COR {
    NodeCor* fim;
    NodeCor* inicio;
    int tamanho;
};
typedef struct LISTA_COR lista_cor;

typedef struct LISTA_COR ListaCor;

enum BMPKEY {
    Key_BM = 1,
    Key_BW = 2,
    Key_PPM = 3,
    Key_BMP = 6
};
typedef enum BMPKEY BMPKey;

struct DIM2D {
    int largura;
    int altura;
};
typedef struct DIM2D Dimensao2D;

struct PPMHEADER {
    Dimensao2D* tamanho;
    int channelRange;
    BMPKey tipoBMP;
};
typedef struct PPMHEADER PPMHeader;

struct PPM {
    PPMHeader* cabecalho;
    rgb** pixel;
};
typedef struct PPM PPM;

struct poligono {
    NoDuploPonto* primeiro;
    Ponto* centro;
};
typedef struct poligono Poligono;

#endif
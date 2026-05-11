/*Este trabalho foi integralmente
realizado pelos alunos Rodrigo Lopes e António Santos sem recurso a ferramentas de inteligência artificial*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Imagens{
    char imagem[100][100];
    int largura;
    int altura;
};

void iniciarImagem(struct Imagens *img, int largura, int altura)
{
    /*Rodrigo*/
}

void desenharPontos(struct Imagens *img, int x, int y)
{
    /*António*/
    img->imagem;
    if (x >= 0 && x < img->largura && y >= 0 && y < img->altura)
    {
        img->imagem[y][x] = '#';
    }
}

void desenharLinha(struct Imagens *img, int x1, int y1, int x2, int y2)
{
    /*Rodrigo*/
}

void desenharRetangulo(struct Imagens *img, int x1, int y1, int x2, int y2)
{
    /*António*/
    desenharLinha(img, x1, y1, x2, y1);
    desenharLinha(img, x1, y2, x2, y2);
    desenharLinha(img, x1, y1, x1, y2);
    desenharLinha(img, x2, y1, x2, y2);
}

void guardarImagem(struct Imagens *img, int largura, int altura, const char *nomeFicheiro)
{
    /*Rodrigo*/
}

int main(){
    /*António*/
    struct Imagens img;
    printf("Qual o nome do ficheiro em MyVG? ");
    char nomeFicheiro[100];
    scanf("%s", nomeFicheiro);

    int largura, altura;
    fscanf(fopen(nomeFicheiro, "r"), "%d %d", &largura, &altura);
    iniciarImagem(&img, largura, altura);

    char tipoDesenho[20];
    while (fscanf(fopen(nomeFicheiro, "r"), "%s", tipoDesenho) != EOF)
    {
        if (strcmp(tipoDesenho, "p") == 0){
            int x, y;
            fscanf(fopen(nomeFicheiro, "r"), "%d %d", &x, &y);
            desenharPontos(&img, x, y);
        }
        else if (strcmp(tipoDesenho, "l") == 0){
            int x1, y1, x2, y2;
            fscanf(fopen(nomeFicheiro, "r"), "%d %d %d %d", &x1, &y1, &x2, &y2);
            desenharLinha(&img, x1, y1, x2, y2);
        }
        else if (strcmp(tipoDesenho, "r") == 0){
            int x1, y1, x2, y2;
            fscanf(fopen(nomeFicheiro, "r"), "%d %d %d %d", &x1, &y1, &x2, &y2);
            desenharRetangulo(&img, x1, y1, x2, y2);
        }
    }
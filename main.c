#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Imagens
{
    char imagem[100][100];
    int largura;
    int altura;
};


void iniciarImagem(struct Imagens* img, int largura, int altura){
    /*Rodrigo*/
}

void desenharPontos(struct Imagens* img, int x, int y){
    /*António*/
    img->imagem;
    if(x >= 0 && x < img->largura && y >= 0 && y < img->altura) {
        img->imagem[y][x] = '*';
    }
}

void desenharLinha(struct Imagens* img, int x1, int y1, int x2, int y2){
    /*Afonso*/
}

void desenharRetangulo(struct Imagens* img, int x1, int y1, int x2, int y2){
    /*Rodrigo*/
}

void guardarImagem(struct Imagens* img, int largura, int altura, const char* nomeFicheiro){
    /*António*/
}

int main(){
    /*Afonso*/
}
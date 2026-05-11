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
int x,y;
img->largura = largura;
img->altura = altura;
for(y = 0; y < altura; y++){
for(x = 0; x < largura; x++){
img->imagem[y][x] = ' ';
}
} 
}

void desenharPontos(struct Imagens* img, int x, int y){
    /*António*/
    img->imagem;
    if(x >= 0 && x < img->largura && y >= 0 && y < img->altura) {
        img->imagem[y][x] = '#';
    }
}

void desenharLinha(struct Imagens* img, int x1, int y1, int x2, int y2){
    /*Rodrigo*/
int dx=abs(x2-x1);
int dy=abs(y2-y1);
int sx,sy;
if(x1 <x2){
sx=1;
}
else{
sx=-1;
}
if(y1 <y2){
sy=1;
}
else{
sy= -1;
}

int e=dx + dy;
while(1){
desenharPontos(img,x1,y1);
int e2= e + e;
if(e2>=dy){
if(x1==x2){
break;
}
e= e + dy;
x1= x1 + sx;
}
if(e2<=dx){
if(y1==y2){
break;
}
e= e + dx;
y1= y1 + sy;
}
}
}

void desenharRetangulo(struct Imagens* img, int x1, int y1, int x2, int y2){
    /*António*/
    desenharLinha(img, x1, y1, x2, y1);
    desenharLinha(img, x1, y2, x2, y2);
    desenharLinha(img, x1, y1, x1, y2);
    desenharLinha(img, x2, y1, x2, y2);
}

void guardarImagem(struct Imagens* img, int largura, int altura, const char* nomeFicheiro){
    /*Rodrigo*/
FILE *ficheiro = fopen(nomeFicheiro, "w");
for(y =0; y < altura; y++){
for(x = 0; x < largura; x++){
fprintf(ficheiro, "%c",img->imagem[y][x]);
}
fprintf(ficheiro,"\n");
}
fclose(ficheiro);

}

int main(){
    /*António*/
    struct Imagens img;
    printf("Qual o nome do ficheiro em MyVG? ");
    char nomeFicheiro[100];
    scanf("%s", nomeFicheiro);
    // quero ler o ficheiro e agarrar nos primeiros 2 numeros para a largura e altura da imagem
    int largura, altura;
    fscanf(fopen(nomeFicheiro, "r"), "%d %d", &largura, &altura);
    iniciarImagem(&img, largura, altura);
    // quero ler o resto do ficheiro e desenhar os pontos, linhas e retângulos
    char tipoDesenho[20];
    while(fscanf(fopen(nomeFicheiro, "r"), "%s", tipoDesenho) != EOF) {
        if(strcmp(tipoDesenho, "p") == 0) {
            int x, y;
            fscanf(fopen(nomeFicheiro, "r"), "%d %d", &x, &y);
            desenharPontos(&img, x, y);
        } else if(strcmp(tipoDesenho, "l") == 0) {
            int x1, y1, x2, y2;
            fscanf(fopen(nomeFicheiro, "r"), "%d %d %d %d", &x1, &y1, &x2, &y2);
            desenharLinha(&img, x1, y1, x2, y2);
        } else if(strcmp(tipoDesenho, "r") == 0) {
            int x1, y1, x2, y2;
            fscanf(fopen(nomeFicheiro, "r"), "%d %d %d %d", &x1, &y1, &x2, &y2);
            desenharRetangulo(&img, x1, y1, x2, y2);
        }
}
/*Este trabalho foi integralmente
realizado pelos alunos Rodrigo Lopes e António Santos sem recurso a ferramentas de inteligência artificial*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LARGURA 100
#define MAX_ALTURA 100

struct Imagens
{
    char imagem[MAX_ALTURA][MAX_LARGURA];
    int largura;
    int altura;
};

void iniciarImagem(struct Imagens *img, int largura, int altura)
{
    /*Rodrigo*/
    int x, y;
    img->largura = largura;
    img->altura = altura;
    for (y = 0; y < altura; y++)
    {
        for (x = 0; x < largura; x++)
        {
            img->imagem[y][x] = ' ';
        }
    }
}

void desenharPontos(struct Imagens *img, int x, int y)
{
    /*António*/
    if (x >= 0 && x < img->largura && y >= 0 && y < img->altura)
    {
        img->imagem[y][x] = '#';
    }
}

void desenharLinha(struct Imagens *img, int x1, int y1, int x2, int y2)
{
    /*Rodrigo*/
    int dx = abs(x2 - x1);
    int dy = -abs(y2 - y1);
    int sx, sy;
    if (x1 < x2)
    {
        sx = 1;
    }
    else
    {
        sx = -1;
    }
    if (y1 < y2)
    {
        sy = 1;
    }
    else
    {
        sy = -1;
    }

    int e = dx + dy;
    while (1)
    {
        desenharPontos(img, x1, y1);
        int e2 = e + e;
        if (e2 >= dy)
        {
            if (x1 == x2)
            {
                break;
            }
            e = e + dy;
            x1 = x1 + sx;
        }
        if (e2 <= dx)
        {
            if (y1 == y2)
            {
                break;
            }
            e = e + dx;
            y1 = y1 + sy;
        }
    }
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
    int x, y;
    FILE *ficheiro = fopen(nomeFicheiro, "w");
    if (ficheiro == NULL)
    {
        printf("Erro ao criar o ficheiro de saída.\n");
        return;
    }
    for (y = 0; y < altura; y++)
    {
        for (x = 0; x < largura; x++)
        {
            fprintf(ficheiro, "%c", img->imagem[y][x]);
        }
        fprintf(ficheiro, "\n");
    }
    fclose(ficheiro);
}

// Funções Opcionais

void desenharPoligono(struct Imagens *img, int xs[], int ys[], int n){
    //António
}

void inserirImagem(struct Imagens *img, int xInicio, int yInicio, const char nomeFicheiro[]){
    //Rodrigo
}

int main(){
    /*António*/
    struct Imagens img;
    printf("Qual o nome do ficheiro em MyVG? ");
    char nomeFicheiro[100];
    scanf("%s", nomeFicheiro);
    FILE *ficheiro = fopen(nomeFicheiro, "r");
    if (ficheiro == NULL)
    {
        printf("Erro ao abrir o ficheiro.\n");
        return 1;
    }

    int largura, altura;
    if(fscanf(ficheiro, "%d %d", &largura, &altura) != 2)
    {
        printf("Erro ao ler as dimensões da imagem.\n");
        fclose(ficheiro);
        return 1;
    }
    if (largura <= 0 || largura > MAX_LARGURA || altura <= 0 || altura > MAX_ALTURA)
    {
        printf("Dimensões da imagem inválidas. Largura e altura devem ser entre 1 e %d.\n", MAX_LARGURA);
        fclose(ficheiro);
        return 1;
    }
    iniciarImagem(&img, largura, altura);

    char tipoDesenho[20];

    while (fscanf(ficheiro, "%s", tipoDesenho) != EOF)
    {
        if (strcmp(tipoDesenho, "p") == 0){
            int x, y;
            fscanf(ficheiro, "%d %d", &x, &y);
            desenharPontos(&img, x, y);
        }
        else if (strcmp(tipoDesenho, "l") == 0){
            int x1, y1, x2, y2;
            fscanf(ficheiro, "%d %d %d %d", &x1, &y1, &x2, &y2);
            desenharLinha(&img, x1, y1, x2, y2);
        }
        else if (strcmp(tipoDesenho, "r") == 0){
            int x1, y1, x2, y2;
            fscanf(ficheiro, "%d %d %d %d", &x1, &y1, &x2, &y2);
            desenharRetangulo(&img, x1, y1, x2, y2);
        }
    }
    fclose(ficheiro);
    guardarImagem(&img, largura, altura, "output.txt");
    return 0;
}
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
    int i;

    if (n < 2)
    {
        return;
    }

    for (i = 0; i < n - 1; i++)
    {
        desenharLinha(img, xs[i], ys[i], xs[i + 1], ys[i + 1]);
    }

    desenharLinha(img, xs[n - 1], ys[n - 1], xs[0], ys[0]);
}

void inserirImagem(struct Imagens *img, int xInicio, int yInicio, const char nomeFicheiro[])
{
    // Rodrigo
    FILE *ficheiro = fopen(nomeFicheiro, "r");
    if (ficheiro == NULL)
    {
        return;
    }
    int xActual = xInicio;
    int yActual = yInicio;
    int c;
    while ((c = fgetc(ficheiro)) != EOF)
    {
        if (c == '\n')
        {
            yActual++;
            xActual = xInicio;
        }
        else
        {
            if (xActual >= 0 && xActual < img->largura && yActual >= 0 && yActual < img->altura)
            {
                img->imagem[yActual][xActual] = c;
            }
            xActual++;
        }
    }
    fclose(ficheiro);
}

int main()
{
    struct Imagens img;
    char nomeFicheiro[100];
    FILE *ficheiro;
    char linha[256];
    int largura = 0, altura = 0;

    printf("Qual o nome do ficheiro em MyVG? ");
    scanf("%99s", nomeFicheiro);

    ficheiro = fopen(nomeFicheiro, "r");
    if (ficheiro == NULL)
    {
        printf("Erro ao abrir o ficheiro.\n");
        return 1;
    }

    while (fgets(linha, sizeof(linha), ficheiro) != NULL)
    {
        char *comentario = strchr(linha, '#');
        if (comentario != NULL)
        {
            *comentario = '\0';
        }

        if (sscanf(linha, "%d %d", &largura, &altura) == 2)
        {
            break;
        }
    }

    if (largura <= 0 || largura > MAX_LARGURA || altura <= 0 || altura > MAX_ALTURA)
    {
        printf("Dimensões da imagem inválidas.\n");
        fclose(ficheiro);
        return 1;
    }

    iniciarImagem(&img, largura, altura);

    while (fgets(linha, sizeof(linha), ficheiro) != NULL)
    {
        char *comentario = strchr(linha, '#');
        if (comentario != NULL)
        {
            *comentario = '\0';
        }

        char *comando = strtok(linha, " \t\n\r");
        if (comando == NULL)
        {
            continue;
        }

        if (strcmp(comando, "p") == 0)
        {
            char *sx = strtok(NULL, " \t\n\r");
            char *sy = strtok(NULL, " \t\n\r");

            if (sx != NULL && sy != NULL)
            {
                int x = atoi(sx);
                int y = atoi(sy);
                desenharPontos(&img, x, y);
            }
        }
        else if (strcmp(comando, "l") == 0)
        {
            char *sx1 = strtok(NULL, " \t\n\r");
            char *sy1 = strtok(NULL, " \t\n\r");
            char *sx2 = strtok(NULL, " \t\n\r");
            char *sy2 = strtok(NULL, " \t\n\r");

            if (sx1 != NULL && sy1 != NULL && sx2 != NULL && sy2 != NULL)
            {
                int x1 = atoi(sx1);
                int y1 = atoi(sy1);
                int x2 = atoi(sx2);
                int y2 = atoi(sy2);
                desenharLinha(&img, x1, y1, x2, y2);
            }
        }
        else if (strcmp(comando, "r") == 0)
        {
            char *sx1 = strtok(NULL, " \t\n\r");
            char *sy1 = strtok(NULL, " \t\n\r");
            char *sx2 = strtok(NULL, " \t\n\r");
            char *sy2 = strtok(NULL, " \t\n\r");

            if (sx1 != NULL && sy1 != NULL && sx2 != NULL && sy2 != NULL)
            {
                int x1 = atoi(sx1);
                int y1 = atoi(sy1);
                int x2 = atoi(sx2);
                int y2 = atoi(sy2);
                desenharRetangulo(&img, x1, y1, x2, y2);
            }
        }
        else if (strcmp(comando, "z") == 0)
        {
            int xs[50], ys[50];
            int n = 0;

            char *sx = strtok(NULL, " \t\n\r");
            while (sx != NULL && n < 50)
            {
                char *sy = strtok(NULL, " \t\n\r");
                if (sy == NULL)
                {
                    break;
                }

                xs[n] = atoi(sx);
                ys[n] = atoi(sy);
                n++;

                sx = strtok(NULL, " \t\n\r");
            }

            if (n >= 2)
            {
                desenharPoligono(&img, xs, ys, n);
            }
        }
        else if (strcmp(comando, "f") == 0)
        {
            char *sx = strtok(NULL, " \t\n\r");
            char *sy = strtok(NULL, " \t\n\r");
            char *nomeInserir = strtok(NULL, " \t\n\r");

            if (sx != NULL && sy != NULL && nomeInserir != NULL)
            {
                int x = atoi(sx);
                int y = atoi(sy);
                inserirImagem(&img, x, y, nomeInserir);
            }
        }
        else
        {
            printf("Tipo de desenho desconhecido: %s\n", comando);
        }
    }

    fclose(ficheiro);
    guardarImagem(&img, largura, altura, "output.txt");

    return 0;
}

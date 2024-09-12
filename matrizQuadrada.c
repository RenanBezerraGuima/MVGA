#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double cofator(double **matriz, int tamanhoMatriz, int linha, int coluna);
void exibirMatriz(double **matriz, int tamanhoMatriz);

void alocaMatriz(double ***matriz, int tamanhoMatriz)
{
    *matriz = (double **)malloc(tamanhoMatriz * sizeof(double *));
    for (int i = 0; i < tamanhoMatriz; i++)
    {
        (*matriz)[i] = (double *)malloc(tamanhoMatriz * sizeof(double));
    }
}

void inicializaMatriz(double ***matriz, int tamanhoMatriz)
{
    for (int i = 0; i < tamanhoMatriz; i++)
    {
        for (int j = 0; j < tamanhoMatriz; j++)
        {
            printf("Digite o valor da matriz[%i][%i]: ", i, j);
            scanf("%lf", &(*matriz)[i][j]);
        }
    }
}

void liberarMatriz(double **matriz, int tamanhoMatriz)
{
    for (int i = 0; i < tamanhoMatriz; i++)
    {
        free(matriz[i]);
    }
    free(matriz);
}

void multiplicarMatriz(double ***matriz, int tamanhoMatriz, double constante)
{
    for (int i = 0; i < tamanhoMatriz; i++)
    {
        for (int j = 0; j < tamanhoMatriz; j++)
        {
            (*matriz)[i][j] = (*matriz)[i][j] * constante;
        }
    }
}

void matrizTransposta(double ***matriz, int tamanhoMatriz)
{
    double **matrizTransposta;
    alocaMatriz(&matrizTransposta, tamanhoMatriz);

    for (int i = 0; i < tamanhoMatriz; i++)
    {
        for (int j = 0; j < tamanhoMatriz; j++)
        {
            matrizTransposta[i][j] = (*matriz)[j][i];
        }
    }

    liberarMatriz(*matriz, tamanhoMatriz);

    (*matriz) = matrizTransposta;
}

double determinanteMatriz(double **matriz, int tamanhoMatriz)
{
    if (tamanhoMatriz == 1)
        return matriz[0][0];

    if (tamanhoMatriz == 2)
        return matriz[0][0] * matriz[1][1] - matriz[0][1] * matriz[1][0];

    else
    {
        double resultado = 0;
        for (int i = 0; i < tamanhoMatriz; i++)
        {
            resultado += matriz[0][i] * cofator(matriz, tamanhoMatriz, 0, i);
        }

        return resultado;
    }
}

double cofator(double **matriz, int tamanhoMatriz, int linha, int coluna)
{
    double **matrizMenor;
    alocaMatriz(&matrizMenor, tamanhoMatriz - 1);

    int r = 0, c = 0;
    for (int i = 0; i < tamanhoMatriz; i++)
    {
        if (i == linha)
            continue;
        c = 0;
        for (int j = 0; j < tamanhoMatriz; j++)
        {
            if (j == coluna)
                continue;
            matrizMenor[r][c] = matriz[i][j];
            c++;
        }
        r++;
    }

    double resultado = pow(-1, linha + coluna) * determinanteMatriz(matrizMenor, tamanhoMatriz - 1);

    liberarMatriz(matrizMenor, tamanhoMatriz - 1);

    return resultado;
}

void exibirMatriz(double **matriz, int tamanhoMatriz)
{
    for (int i = 0; i < tamanhoMatriz; i++)
    {
        for (int j = 0; j < tamanhoMatriz; j++)
        {
            printf("%.2lf ", matriz[i][j]);
        }
        printf("\n");
    }
}

void matrizAdjunta(double ***matriz, int tamanhoMatriz)
{
    double **matrizAdjunta;
    alocaMatriz(&matrizAdjunta, tamanhoMatriz);

    for (int i = 0; i < tamanhoMatriz; i++)
    {
        for (int j = 0; j < tamanhoMatriz; j++)
        {
            matrizAdjunta[i][j] = cofator(*matriz, tamanhoMatriz, i, j);
        }
    }

    liberarMatriz(*matriz, tamanhoMatriz);

    (*matriz) = matrizAdjunta;
}

void inversaMatriz(double ***matriz, int tamanhoMatriz)
{
    double determinante = determinanteMatriz(*matriz, tamanhoMatriz);
    if (determinante == 0)
    {
        printf("Matriz não possui inversa\n");
        return;
    }

    double determinanteDividido = 1 / determinante;

    matrizAdjunta(matriz, tamanhoMatriz);
    matrizTransposta(matriz, tamanhoMatriz);
    multiplicarMatriz(matriz, tamanhoMatriz, determinanteDividido);
}

int main()
{
    int option;
    double **matriz;
    int tamanhoMatriz;
    printf("Digite o tamanho da matriz quadrada: ");
    scanf("%i", &tamanhoMatriz);
    alocaMatriz(&matriz, tamanhoMatriz);
    inicializaMatriz(&matriz, tamanhoMatriz);
    exibirMatriz(matriz, tamanhoMatriz);

    do
    {
        printf("Escolha uma opção:\n");
        printf("1 - Trocar matriz\n");
        printf("2 - Multiplicar matriz\n");
        printf("3 - Transposta da matriz\n");
        printf("4 - Determinante da matriz\n");
        printf("5 - Exibir a matriz\n");
        printf("6 - Inversa da matriz\n");
        printf("7 - Matriz adjunta\n");
        printf("0 - Sair\n");

        scanf("%i", &option);
        switch (option)
        {
        case 1:
            printf("Digite o tamanho da matriz quadrada: ");
            scanf("%i", &tamanhoMatriz);
            alocaMatriz(&matriz, tamanhoMatriz);
            inicializaMatriz(&matriz, tamanhoMatriz);
            exibirMatriz(matriz, tamanhoMatriz);
            break;
        case 2:
            double constante;
            printf("Digite a constante: ");
            scanf("%lf", &constante);
            multiplicarMatriz(&matriz, tamanhoMatriz, constante);
            exibirMatriz(matriz, tamanhoMatriz);
            break;
        case 3:
            matrizTransposta(&matriz, tamanhoMatriz);
            exibirMatriz(matriz, tamanhoMatriz);
            break;
        case 4:
            double resultado = determinanteMatriz(matriz, tamanhoMatriz);
            exibirMatriz(matriz, tamanhoMatriz);
            printf("Determinante: %.2lf\n", resultado);
            break;
        case 5:
            exibirMatriz(matriz, tamanhoMatriz);
            break;
        case 6:
            inversaMatriz(&matriz, tamanhoMatriz);
            exibirMatriz(matriz, tamanhoMatriz);
            break;
        case 7:
            matrizAdjunta(&matriz, tamanhoMatriz);
            exibirMatriz(matriz, tamanhoMatriz);
            break;
        default:
            break;
        }
    } while (option != 0);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <math.h>

// Limpa a tela
void Limpar() {
    system("cls");
}

// Define a cor no console
void setColor(int cor) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), cor);
}

// Mostra a tabela de cores
void mostrarCores() {
    printf("\nTabela de cores:\n");
    setColor(8);   printf(" 0 - Preto\n");
    setColor(6);   printf(" 1 - Marrom\n");
    setColor(4);   printf(" 2 - Vermelho\n");
    setColor(14);  printf(" 3 - Laranja\n");
    setColor(6);   printf(" 4 - Amarelo\n"); // Corrigido amarelo
    setColor(2);   printf(" 5 - Verde\n");
    setColor(3);   printf(" 6 - Azul\n");
    setColor(1);   printf(" 7 - Violeta\n");
    setColor(8);   printf(" 8 - Cinza\n");
    setColor(15);  printf(" 9 - Branco\n");
    setColor(6);   printf("10 - Dourado (Multiplicador -1, Tolerancia 5%%)\n");
    setColor(7);   printf("11 - Prata   (Multiplicador -2, Tolerancia 10%%)\n");
    setColor(7);   // Reset cor
}

float obterTolerancia(int cor) {
    if (cor == 1) return 1.0;
    if (cor == 2) return 2.0;
    if (cor == 5) return 0.5;
    if (cor == 6) return 0.25;
    if (cor == 7) return 0.1;
    if (cor == 8) return 0.05;
    if (cor == 10) return 5.0;
    if (cor == 11) return 10.0;
    return 20.0;
}

void formatarValor(double valor, char *saida) {
    if (valor >= 1000000) {
        sprintf(saida, "%.2f MOhms", valor / 1000000.0);
    } else if (valor >= 1000) {
        sprintf(saida, "%.2f kOhms", valor / 1000.0);
    } else {
        sprintf(saida, "%.2f Ohms", valor);
    }
}

int validarFaixa(int faixa) {
    return (faixa >= 0 && faixa <= 11);
}

// Calcula valor do resistor com base nas faixas
double calcularResistor(int faixas, int *cores) {
    if (faixas == 4) {
        return (cores[0] * 10 + cores[1]) * pow(10, cores[2]);
    } else {
        return (cores[0] * 100 + cores[1] * 10 + cores[2]) * pow(10, cores[3]);
    }
}

int main() {
    Limpar();
    setColor(7);
    printf("==== CALCULADORA DE RESISTORES ====\n");

    mostrarCores();

    int numResistores;
    char entrada[20];

    // ? TRATAMENTO DE ENTRADA CORRIGIDO
    while (1) {
        printf("\nQuantos resistores deseja calcular? ");
        fgets(entrada, sizeof(entrada), stdin);
        if (sscanf(entrada, "%d", &numResistores) == 1 && numResistores > 0) break;
        else printf("Entrada invalida! Digite um numero inteiro positivo.\n");
    }

    double resistores[numResistores];

    for (int i = 0; i < numResistores; i++) {
        Limpar();
        setColor(7);
        printf("==== RESISTOR %d ====\n", i + 1);
        mostrarCores();

        int faixas;
        while (1) {
            printf("\nQuantas faixas tem o resistor %d (4 ou 5)? ", i + 1);
            fgets(entrada, sizeof(entrada), stdin);
            if (sscanf(entrada, "%d", &faixas) == 1 && (faixas == 4 || faixas == 5)) break;
            else printf("Entrada invalida! Digite 4 ou 5.\n");
        }

        int cores[5];
        for (int j = 0; j < faixas; j++) {
            while (1) {
                printf("Digite o numero da cor da faixa %d (0 a 11): ", j + 1);
                fgets(entrada, sizeof(entrada), stdin);
                if (sscanf(entrada, "%d", &cores[j]) == 1 && validarFaixa(cores[j])) break;
                else printf("Cor invalida!\n");
            }
        }

        resistores[i] = calcularResistor(faixas, cores);
    }

    printf("\nDeseja calcular a resistencia equivalente? (1 - Sim / 0 - Nao): ");
    int calcularReq;
    fgets(entrada, sizeof(entrada), stdin);
    sscanf(entrada, "%d", &calcularReq);

    double req = 0;
    int tipo = 0;

    if (calcularReq == 1) {
        printf("Resistores em serie (1) ou paralelo (2)? ");
        fgets(entrada, sizeof(entrada), stdin);
        sscanf(entrada, "%d", &tipo);

        if (tipo == 1) {
            for (int i = 0; i < numResistores; i++) req += resistores[i];
        } else if (tipo == 2) {
            for (int i = 0; i < numResistores; i++) req += 1.0 / resistores[i];
            req = 1.0 / req;
        } else {
            printf("Opcao invalida.\n");
            return 1;
        }
    }

    printf("\n==== RESULTADOS ====\n");
    for (int i = 0; i < numResistores; i++) {
        char buffer[30];
        formatarValor(resistores[i], buffer);
        printf("Resistor %d: %s\n", i + 1, buffer);
    }

    if (calcularReq == 1) {
        char resultadoFinal[30];
        formatarValor(req, resultadoFinal);
        printf("Resistencia equivalente: %s\n", resultadoFinal);
    }

    printf("\nDeseja salvar os resultados em um arquivo? (1 - Sim / 0 - Nao): ");
    int salvar;
    fgets(entrada, sizeof(entrada), stdin);
    sscanf(entrada, "%d", &salvar);

    if (salvar == 1) {
        FILE *arquivo = fopen("resultado_resistores.txt", "w");
        if (arquivo != NULL) {
            fprintf(arquivo, "==== RESULTADOS ====\n");
            for (int i = 0; i < numResistores; i++) {
                char buffer[30];
                formatarValor(resistores[i], buffer);
                fprintf(arquivo, "Resistor %d: %s\n", i + 1, buffer);
            }

            if (calcularReq == 1) {
                char resultadoFinal[30];
                formatarValor(req, resultadoFinal);
                fprintf(arquivo, "Resistencia equivalente: %s\n", resultadoFinal);
            }

            fclose(arquivo);
            printf("Resultado salvo em 'resultado_resistores.txt'\n");
        } else {
            printf("Erro ao salvar o arquivo.\n");
        }
    }

    printf("\nObrigado por usar a calculadora!\n");
    return 0;
}

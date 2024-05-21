#include <stdio.h> //printf e scanf
#include <ctype.h> //  isdigit
#include <string.h> // strcat
#include <cstdlib> // atof

float Soma(float n1, float n2) {
    return n1 + n2;
}

float Subtracao(float n1, float n2) {
    return n1 - n2;
}

float Multiplicacao(float n1, float n2) {
    return n1 * n2;
}

float Divisao(float n1, float n2) {
    return n1 / n2;
}

float Potencia(float n1, int n2) {
    float res = 1;
    for (int i = 0; i < n2; i++) { 
        res *= n1;
    }    
    return res;
}

float Porcentagem(float n1, float n2) {
    return (n1 / 100) * n2;
}

void linha(int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        printf("=");
    }
}

long double fatorial(int n) {
    if (n == 0) return 1;
    long double resultado = 1;
    for (int i = 1; i <= n; ++i) {
        resultado *= i;
    }
    return resultado;
}

double Seno(double x, int numTermos) {
    double r = 0.0;
    int sinal = 1;

    for (int n = 0; n < numTermos; ++n) {
        r += sinal * (Potencia(x, 2 * n + 1) / fatorial(2 * n + 1));
        sinal = -sinal;
    }
    return r;
}

double cosseno(double x, int numTermos) {
    double r = 0.0;
    int sinal = 1;

    for (int n = 0; n < numTermos; ++n) {
        r += sinal * (Potencia(x, 2 * n) / fatorial(2 * n));
        sinal = -sinal;
    }
    return r;
}

double transformacao(int graus){
    const double pi = 3.1416;
    return (double)graus*(pi / 180.0);
}

void titulo(const char* texto) {
    char mostrar[100] = {0};
    int tamanho = 0;
    int tamLinha = 60;
    
    for (int i = 0; texto[i] != '\0'; i++) {
        tamanho++;
    }
    int espaco = (tamLinha - tamanho) / 2;
    linha(tamLinha);
    printf("\n");

    for (int i = 0; i < espaco; i++) {
        mostrar[i] = ' ';
    }

    for (int i = 0; i < tamanho; i++) {
        mostrar[espaco + i] = texto[i];
    }

    mostrar[espaco + tamanho] = '\0'; // Garante que 'mostrar' eh uma string terminada

    printf("%s\n", mostrar);

    linha(tamLinha);
    printf("\n\n");
}

int menu() {
    int ask;
    titulo("CALCULADORA");
    printf("\n1 - Digite a expressao");
    printf("\n2 - Calculo seno");
    printf("\n3 - Calculo Cosseno");
    printf("\n\nDigite o valor referente ao que quer fazer\n-->  ");
    scanf("%d", &ask);
    return ask;
}

char visor(float resultado){
    linha(30);
    printf("\n");
    printf("--> %.3f",resultado);
    printf("\n");
    linha(30);
}

int main() {
    char end;
    do {

        int q = menu();

        switch (q) {
        case 1: {
            printf("\n");
            titulo("EXPRESSAO");
            char pergunta;
            char expressao[100];

            do {
                visor(0);
                printf("\nDigite a expressao para calculo: ");
                scanf("%s", expressao);
                printf("\n");

                char numerais[100]; // contem os numerais como string 
                char operadores[100]; // contem todos os operadores
                int indice_numerais = 0; // percorre o array numerais e guarda o seu tamanho
                int indice_operadores = 0; // percorre o array operadores e guarda o seu tamanho
                float numerais_limpos[100]; // contem os numerais ja convertidos para float
                int indice_numerais_limpos = 0; // percorre o array numerais limpos e guarda o seu tamanho
                char NumeroConcatenado[100] = ""; // Inicialize com uma string vazia

                for (int i = 0; expressao[i] != '\0'; i++) {
                    if (isdigit(expressao[i]) || expressao[i] == '.') {
                        numerais[indice_numerais++] = expressao[i];
                    }
                    else {
                        numerais[indice_numerais++] = ' '; 
                        operadores[indice_operadores++] = expressao[i];
                    }
                }

                for (int i = 0; i < indice_numerais; i++) {
                    if (numerais[i] != ' ') {
                        strncat(NumeroConcatenado, &numerais[i], 1); // Concatena strings
                    }
                    else {
                        numerais_limpos[indice_numerais_limpos++] = atof(NumeroConcatenado); // Converte para float
                        NumeroConcatenado[0] = '\0'; // Limpa NumeroConcatenado para o próximo número
                    }
                }
                if (NumeroConcatenado[0] != '\0') {
                    numerais_limpos[indice_numerais_limpos++] = atof(NumeroConcatenado);// se tiver um numero em numerais concatenados adiciona
                }

                double resultado = numerais_limpos[0];
                // 1+2*3
                // 1 2 3
                // + *
                for (int i = 0; i < indice_operadores; i++) {
                    switch (operadores[i]) {
                        case '+':
                            resultado = Soma(resultado, numerais_limpos[i + 1]);
                            break;
                        case '-':
                            resultado = Subtracao(resultado, numerais_limpos[i + 1]);
                            break;
                        case '*':
                        case 'x':
                            resultado = Multiplicacao(resultado, numerais_limpos[i + 1]);
                            break;
                        case '/':
                        case '\\':
                        case ':':
                            if( numerais_limpos[i + 1] == 0){
                                printf("Nao eh possivel fazer divisao por 0 !!\n");
                                resultado = 0;
                                break;
                            }
                            else{
                                resultado = Divisao(resultado, numerais_limpos[i + 1]);
                                break;
                            }  
                        case '^':
                        case '~':
                            resultado = Potencia(resultado, numerais_limpos[i + 1]);
                            break;
                        case '%':
                            resultado = Porcentagem(resultado, numerais_limpos[i + 1]);
                            break;
                        default:
                            printf("Operador invalido: %c\n", operadores[i]);
                    }
                }
                
                printf("\n");
                visor(resultado);        
                printf("\n");
                printf("\nDeseja calcular novamente? (s/n): ");
                scanf(" %c", &pergunta);
                if (pergunta == 'n' || pergunta == 'N') {
                    titulo("FIM DA EXPRESSAO");
                }
            
            } while (pergunta == 's' || pergunta == 'S');
            break;
        }

        case 2: {
            printf("\n");
            titulo("SENO");
            char per;

            do{
                double radi;
                int numTermos, graus;

                printf("Insira o grau desejado: ");
                scanf("%d", &graus);
                printf("Insira a quantidade de termos: ");
                scanf("%d", &numTermos);

                radi = transformacao(graus);
                double z = Seno(radi, numTermos);
                printf("\nGraus: %d\nRadianos %.8f\nSeno: %.8f", graus, radi, z);

                printf("\nDeseja calcular novamente? (s/n): ");
                    scanf(" %c", &per);
                    if (per == 'n'|| per == 'N') {
                        titulo("FIM SENO");
                    }
            }while(per == 's'|| per == 'S') ;
            break;   
        }

        case 3: {
            printf("\n");
            titulo("COSSENO");
            char per;

            do{
                double radi;
                int numTermos, graus;

                printf("Insira o grau desejado: ");
                scanf("%d", &graus);
                printf("Insira a quantidade de termos: ");
                scanf("%d", &numTermos);
                radi = transformacao(graus);
                double z = cosseno(radi, numTermos);
                printf("\nGraus: %d\nRadianos %.8f\nCosseno: %.8f", graus, radi, z);
                    printf("\n");
                        printf("\nDeseja calcular novamente? (s/n): ");
                        scanf(" %c", &per);
                        if (per == 'n'|| per == 'N') {
                            titulo("FIM COSSENO");
                        }
            }while(per == 's'|| per == 'S');
            break;
        }
        default:
            printf("Operador invalido!!!\n");
            break;
        }
    
    printf("\nDeseja fazer algum outro tipo de operacao? (s/n): ");
                scanf(" %c", &end);
                if (end == 'n' || end == 'N') {
                    titulo("OBRIGADO POR CALCULAR");
                }
        } while (end == 's' || end == 'S');
    return 0;
}

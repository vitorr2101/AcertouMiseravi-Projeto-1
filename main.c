#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1002

//passos para construção do algoritmo
/*
1)receber imput
2)passar input para a função que decidirá qual função de cálculo deverá ser executada
3)Na função escolhida: transformar valores e calcular o resultado
5)retornar resultado e imprimir
*/

// Função para realizar a soma de vetores de caracteres
char *somaVetores(const char *word1, const char *word2, int t1, int t2){

    //usei static para me certificar de que o estado do resultado durante todo o processo é
    //mantido, assim atualizando result corretamente a cada chamada consecutiva da função.
    static char result[MAX];
    result[0] = '\0'; //inicializar como '\0' garante que a variável seja inicializada como uma string vazia
    int resto = 0; // Vai conter o dígito que "vai para o próximo" na soma
    int p = 0; // marca a posição do dígito resultante
    //inicia do fim da string:
    int i = t1 - 1;
    int j = t2 - 1;


    // Continua somando enquanto houver dígitos em word1 ou word2 ou resto
    while (i >= 0 || j >= 0 || resto > 0)
    {
        int num1 = (i >= 0) ? (word1[i] - '0') : 0;
        int num2 = (j >= 0) ? (word2[j] - '0') : 0;

        int sum = num1 + num2 + resto;
        resto = sum / 10; // Calcula o resto para o próximo dígito
        int sobra = sum % 10; // Obtém o dígito resultante

        //para converter o dígito resultante em caractere: add '0' o que faz
        //o número inteiro virar seu equivalente como caractere
        result[p] = sobra + '0';

        p++;
        i--;
        j--;
    }

    // Encerra a string
    result[p] = '\0';

    // Inverte a string resultante (assim retornando o resultado correto)
    //A lógica é parecida com aquela usada na ordenação decrescente ou crescente de numeros,
    //onde os números são trocados de posição usando uma variável auxiliar.
    int start = 0;
    int end = p - 1;

    while (start < end)
    {
        char aux = result[start];
        result[start] = result[end];
        result[end] = aux;
        start++;
        end--;
    }
    return result;
}

// Função para verificar se a subtração resultará em valor negativo
int verificaSubNegativa(const char *word1, const char *word2, int t1, int t2){

    int teste = 0;
    //1 - teste) verifica se o tamanho do segundo número é maior que o primeiro
    if(t2 > t1)
    {
        teste = 1;
    }
    //2 - teste) caso forem iguais em tamanho, sabemos que basta que apenas 1 digito de num2 seja
    //maior que seu respectivo num1 (em posição) para termos a certeza de que o resultado será negativo!
    if(t2 == t1)
    {
        for(int i = 0 ; i < t1; i++)
        {
            if(word2[i] > word1[i])
            {
               teste = 1;
            }
        }
    }
    return teste;
}

// Função para realizar a subtração de vetores de caracteres
char *subtraiVetores(const char *word1, const char *word2, int t1, int t2){

    static char result[MAX];
    result[0] = '\0';
    int resto = 0; //verifica se teve empréstimo

    int i = t1 - 1;
    int j = t2 - 1;
    int p = 0;

    //caso negativo:
    int negativo = verificaSubNegativa(word1, word2, t1, t2);
    int sinal = 0;

    // Continua subtraindo enquanto houver dígitos em word1 ou word2 ou resto
    while (i >= 0 || j >= 0 || resto > 0)
    {

        int num1 = (i >= 0) ? (word1[i] - '0') : 0;
        int num2 = (j >= 0) ? (word2[j] - '0') : 0;

        //caso negativo: troco os num1-2 de posição e subtraio normalmente, para depois add o sinal(-)
        int aux = 0;

        if(negativo)
        {
            aux = num1;
            num1 = num2;
            num2 = aux;
            sinal = 1;
        }

        //if usado para na situação em que o resto = 1, o que significa que na subtração anterior,
        // havia ocorrido um empréstimo e, portanto, precisamos considerar isso na próxima subtração.
        if(resto == 1)
        {
            num1 = num1 - 1;
            resto = 0;
        }

        num1 += resto;

        //caso precise de repasse
        if (num1 < num2)
        {
            num1 += 10; // Adiciona 10 ao dígito atual para emprestar
            resto +=1;
        }

        int sub = num1 - num2;

        result[p] = sub + '0';
        p++;
        i--;
        j--;
    }

    result[p] = '\0';

    //caso negativo
    if (sinal == 1 && result[p] == '\0')
    {
        printf("-");
    }

    // Inverte a string resultante
    int start = 0;
    int end = p - 1;
    while (start < end)
    {
        char aux = result[start];
        result[start] = result[end];
        result[end] = aux;
        start++;
        end--;
    }

    //Caso tenha zeros à esquerda
    while (result[0] == '0' && result[1] != '\0')
    {
        for (int w = 0; w < strlen(result); w++)
        {
            result[w] = result[w + 1];
        }
    }
    return result;
}

// Função para realizar a multiplicação de vetores de caracteres
char *multVetores(const char *word1, const char *word2, int t1, int t2){

    //o tamanho máximo do resultado é a soma dos tamanhos de word1 e word2!
    int resultSize = t1 + t2;
    static char result[MAX];
    result[resultSize] = '\0';

    // Inicializa o vetor de resultado com '0's
    for (int i = 0; i < resultSize; i++)
    {
        result[i] = '0';
    }

    //a lógica é análoga a multiplicação feita no papel
    // Loop externo: percorre os dígitos de word2(o multiplicador)
    for (int i = t2 - 1; i >= 0; i--)
    {
        int num2 = word2[i] - '0';
        int resto = 0;

        // Loop interno: percorre os dígitos de word1 (o multiplicando)
        for (int j = t1 - 1; j >= 0; j--)
        {
            int num1 = word1[j] - '0';

            // Segue abaixo a multiplicação deste par de dígitos e soma com o resultado existente
            // a posição '[i+j+1]' considera tanto o `i` (posição no primeiro
            //número) quanto o `j` (posição no segundo número) e adicionar 1 porque os arrays são baseados em índices 0.
            //Assim definindo a posição correta do resultado
            int multiplicacao = (num1 * num2) + (result[i + j + 1] - '0') + resto;

            // Calcula o dígito resultante e atualiza o resto para a próxima iteração
            result[i + j + 1] = (multiplicacao % 10) + '0';
            resto = multiplicacao / 10;
        }
        // Após o loop interno, adiciona o valor final do resto ao dígito mais significativo
        result[i] += resto;
    }

    // Remove os zeros à esquerda, se houver
    int inicio = 0;
    while (result[inicio] == '0' && result[inicio + 1] != '\0')
    {
        inicio++;
    }

    //Move os dígitos relevantes para o início da string
    for (int i = inicio; i <= resultSize; i++)
    {
        result[i - inicio] = result[i];
    }
    return result;
}

//Função para definir a função de cálculo a ser executada, o que é possível usando o typedef
//que basicamente declara um ponteiro de função que "aponta" para diferentes
//funções que possuem os mesmos argumentos como entrada.
typedef char *(*FuncaoCalculo)(const char *, const char *, int, int);

int main(void) {
    int n;
    scanf("%d", &n);

    char word1[MAX];
    char word2[MAX];

    //função para definir a função de cálculo a ser executada
    FuncaoCalculo funcao;

    for (int i = 0; i < n; i++)
    {
        scanf(" %s %s", word1, word2);
        int o;
        scanf("%d",&o);
        int t1 = strlen(word1);
        int t2 = strlen(word2);
        char *resultado;

    switch(o) {
        case 1:
    funcao = somaVetores;
        break;

        case 2:
    funcao = subtraiVetores;
        break;

        case 3:
    funcao = multVetores;
        break;
    default:
        return 1;
    }
    resultado = funcao(word1, word2, t1, t2);
        printf("%s\n", resultado);
    }
    return 0;
}

#include "shell.h"

/**
 * Calculadora simples
 * @param value1 Valor 1
 * @param op Operador
 * @param value2 Valor 2
 */
void calc(char *value1, char *op, char *value2)
{
    float v1 = atof(value1), v2 = atof(value2), result = 0;
    switch (op[0])
    {
    case '+': // Somar
        result = v1 + v2;
        break;
    case '-': // Subtrair
        result = v1 - v2;
        break;
    case '*': // Multiplicar
        result = v1 * v2;
        break;
    case '/': // Dividir
        if (fabs(v2) < __FLT_EPSILON__) // Por ser float v2 == 0 não é 0, mas sim uma aproximação de 0 (ex: 1.0e-7)
        {
            printf("Impossivel dividir por 0\n");
            return;
        }
        result = v1 / v2;
        break;
    case '^': // Potencia
        result = powf(v1, v2);
        break;

    default:
        printf("Operador inválido.\n");
        break;
    }
    printf("Resultado calc %f\n", result);
}

/**
 * Calculadora de bits
 * @param op1 Valor 1
 * @param op Operador
 * @param op2 Valor 2
 */
void bits(char *op1, char *op, char *op2)
{
    int result = 0, error = 0;
    int v1 = op1[0] == '~' ? ~atoi(&op1[1]) : atoi(op1);
    if (NULL == op) // Se não houver operador, apenas devolve o v1
        result = v1;
    else
    {
        int v2 = op2[0] == '~' ? ~atoi(&op2[1]) : atoi(op2);
        switch (op[0])
        {
        case '&': // AND
            result = v1 & v2;
            break;
        case '^': // XOR
            result = v1 ^ v2;
            break;
        case '|': // OR
            result = v1 | v2;
            break;
        case '<':
            if (op[1] == '<') // Shift left (<<)
                result = v1 << v2;
            else
                error = 1; // Operador inválido
            break;
        case '>':
            if (op[1] == '>') // Shift right (>>)
                result = v1 >> v2;
            else
                error = 1; // Operador inválido
            break;

        default:
            printf("Operador inválido.\n");
            break;
        }
    }
    // Se houver erro, não imprime o resultado
    !error ? printf("Resultado bits %d\n", result) : printf("Operador inválido.\n");
}

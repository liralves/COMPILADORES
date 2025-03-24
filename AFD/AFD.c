#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define TAM 100

// agrupamento de constantes para representar os estados dos automatos.
typedef enum {
    q0, q1IF, q1ELSE, q1FOR, q1WHILE, q2, q2ELSE, q2FOR, q2WHILE, q3, q3ELSE, q3WHILE, q4, q4WHILE, IF, ELSE, FOR, WHILE, NUM, REJECT
} State;

//função automato qu verifica se a ERs é aceita ou rejeitada
int acceptedAFD(const char *cin){
    State state = q0;
    
    //loop que realiza os casos enquanto o array não for vazio
    for(int i = 0; cin[i] != '\0'; i++){
        char caractere = cin[i];

        switch(state){
            //caso inicial que verifica se o user digitou um numero inteiro ou as iniciais das palavras reservadas IF, ELSE, WHILE E FOR
            case q0:
                if (isdigit(caractere)) state = NUM;
                else if (caractere == 'i') state = q1IF;
                else if (caractere == 'e') state = q1ELSE;
                else if (caractere == 'f') state = q1FOR;
                else if (caractere == 'w') state = q1WHILE;
                else state = REJECT;
                break;
                
                // caso não for um dígito correspondente ao NUM (D+), o programa rejeita.
                case NUM:
                    if(!isdigit(caractere)) state = REJECT;
                    break;
                
                //caso q1 em que verifica se o 'I' do q0 corresponde ao 'F' e forma a keyword IF. 
                case q1IF:
                    if (caractere == 'f') state = IF;
                    else state = REJECT;
                    break;
                
                //caso onde limita o user de continuar a keyword caso ela seja aceita.
                case IF:
                    state = REJECT;
                    break;
                //OBS: O MESMO PARA O RESTANTE DOS TESTES.
                case q1ELSE:
                    if(caractere == 'l') state = q2ELSE;
                    else state = REJECT;
                    break;
                
                case q2ELSE:
                    if(caractere == 's') state = q3ELSE;
                    else state = REJECT;
                    break;
                
                case q3ELSE:
                    if(caractere == 'e') state = ELSE;
                    else state = REJECT;
                    break;
                
                case ELSE:
                    state = REJECT;
                    break;
                
                case q1FOR:
                    if(caractere == 'o') state = q2FOR;
                    else state = REJECT;
                    break;
                
                case q2FOR:
                    if(caractere == 'r') state = FOR;
                    else state = REJECT;
                    break;
                
                case FOR:
                    state = REJECT;
                    break;

                case q1WHILE:
                    if(caractere == 'h') state = q2WHILE;
                    else state = REJECT;
                    break;
                
                case q2WHILE:
                    if(caractere == 'i') state = q3WHILE;
                    else state = REJECT;
                    break;
                
                case q3WHILE:
                    if(caractere == 'l') state = q4WHILE;
                    else state = REJECT;
                    break;
                
                case q4WHILE:
                    if(caractere == 'e') state = WHILE;
                    else state = REJECT;
                    break;

                case WHILE:
                    state = REJECT;
                    break;

                case REJECT:
                    return 0;
        }
    }

    //retorna os resultados caso forem aceitos e verificados pelos testes e casos.
    return (state == NUM || state == IF || state == ELSE || state == FOR || state == WHILE);
}
//função para ler strings eficiente
void lerStr(char *str, int tam) {
    fgets(str, TAM, stdin);
    int len = strlen(str);
    if (str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}


int main() {

    char *testCases = malloc(TAM * sizeof(char));
    printf("Insira uma entrada qualquer:\n");

    do{
        printf("Entrada: ");
        lerStr(testCases, TAM);

        if(acceptedAFD(testCases))
            printf("Entrada: %s -> %s\n", testCases, "Aceito.\n");
        else
            printf("Entrada: %s -> %s\n", testCases, "Rejeitado.\n");

    }while(strcmp(testCases, "0") != 0);

    free(testCases);
    
    return 0;
}

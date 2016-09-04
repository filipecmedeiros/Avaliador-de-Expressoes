#include <stdio.h>
#include <stdlib.h>
# include <math.h>
#include <string.h>

typedef struct Operador{
    char representacao;
    int aridade;
    int linhas;
    int colunas;
    int **tabela;

}operador;

/*A funcao coleta um operador do arquivo e retorna*/
operador f_coleta_operador (){
    int i,j;
    operador temp;


    scanf ("%1s", &temp.representacao); //coleta a representacao do operador
    scanf ("%d", &temp.aridade); //coleta a aridade do operador

    temp.linhas = pow (2, temp.aridade); //qntd de linhas da tabela-verdade é 2 elevado a aridade
    temp.colunas = temp.aridade+1; //qntd de colunas da tabela-verdade é a aridade+1 (resposta do operador)


    temp.tabela = (int**) malloc (temp.linhas *sizeof (int*)); //aloca espaco para a tabela-verdade
    for (j=0; j<temp.linhas;j++){
    temp.tabela[j] = (int*) malloc (temp.colunas*sizeof (int));
    }

    for (i=0; i<temp.linhas; i++){ //coletar a tabela verdade
        for (j=0; j<temp.colunas; j++){
            scanf ("%d", &temp.tabela[i][j]);
        }
    }

    return temp;
}

/*Dado um operador, a funcao imprime as informacoes*/
void f_imprime_operador (operador temp){
    int i,j;

    printf ("representacao:%c\n", temp.representacao);
    printf ("aridade:%d\n", temp.aridade);
    printf ("linhas:%dx%d colunas\n", temp.linhas, temp.colunas);

    for (i=0; i<temp.linhas; i++){
        for (j=0; j<temp.colunas; j++){
            printf ("%d ", temp.tabela[i][j]);
        }
        printf ("\n");
    }

}

/*a funcao calcula o numero de parenteses abrindo de uma expressao*/
int f_parenteses_abrindo (char string [101]){
    int i, numero=0;

    for (i=0; string[i]!= '\0'; i++){ //percorrer ate o fim da string
        if (string [i] == '(')
            numero++;
    }

    return numero;
}

/*a funcao calcula o numero de parenteses fechando de uma expressao*/
int f_parenteses_fechando (char string [101]){
    int i, numero=0;

    for (i=0; string[i]!= '\0'; i++){ //percorrer ate o fim da string
        if (string [i] == ')')
            numero++;
    }

    return numero;
}

/*tendo como argumentos a expressao, o vetor de operadores e o tamanho do vetor,
a funcao calcula o numero de operadores da expressao*/
int f_numero_operadores (char string [101], operador vetor[], int tamanho){
    int i, j, numero=0;

    for (j=0; j<tamanho; j++){ //procurar por todos os operadores

        for (i=0; string[i]!= '\0'; i++){ //percorrer todo o vetor
            if (string [i] == vetor [j].representacao){ //se for igual ao operador, incrementa
                numero++;
            }
        }
    }

    return numero;
}

/*A funcao verifica se a expressao é fbf*/
int f_fbf (char string [101], int cont, int fim, operador vetor [], int nOperadores){
    int fbf, i, j, posicao, op, aridade;

    for (i=cont; i<fim; i++){ //verificar na expressao
        for (j=0;j<nOperadores; j++){ //procurar o operador
            if (string[i] == vetor[j].representacao){ //se achar o operador
                posicao = i; //guardar a posicao do operador
                op = j; //guardar o codigo do operador

                j=nOperadores; //sair do laço
                i=fim; //sair do laço
            }
        }
    }


    for (i=cont, aridade=0; i<fim; i++){ //verificar toda a expressao
        if ( i == posicao){ //se for a posicao do operador, vá pro proximo
            i++;
        }

        if ((string[i] >= 'x' && string [i] <= 'z') || string[i] == '0' || string[i] == '1'){ //se for algum caractere valido
            aridade++;
        }
    }

    if ((aridade == vetor[op].aridade) && (aridade == (fim-cont)-2) ){ //se a aridade do operador for igual e so tiver caracteres validos, é fbf
        fbf = 1;
    }
    else { //se a aridade do operador for diferente da expressao ou tiver caracteres invalidos
        fbf =0;
    }

    return fbf;
}

/*Dada uma expressão, a função calcula o número de sub-expressoes*/
int f_sub_expressoes (char expressao [], int abrindo, int fechando){
    int subExpressoes=0, i;
    int atomico [5] = {0,0,0,0,0}; //vetor para marcar as variaveis contadas (para nao ser repetida)

    for (i=0; expressao[i] != '\0'; i++){ //percorrer a expressão procurando por sub-expressoes atomicas (variável ou constante)
        if (expressao [i] == 'x' && atomico[0] == 0){
            subExpressoes++;
            atomico[0] = 1;
        }
        else if (expressao [i] == 'y' && atomico[1] == 0){
            subExpressoes++;
            atomico[1] = 1;
        }
        else if (expressao [i] == 'z' && atomico[2] == 0){
            subExpressoes++;
            atomico[2] = 1;
        }
        else if (expressao [i] == '1' && atomico[3] == 0){
            subExpressoes++;
            atomico[3] = 1;
        }
        else if (expressao [i] == '0' && atomico[4] == 0){
            subExpressoes++;
            atomico[4] = 1;
        }
    }
    subExpressoes += abrindo;

    //falta calcular o numero de expressoes repetidas

    return subExpressoes;
}

int main()
{
    freopen ("Expressoes.in", "r", stdin);
    freopen ("Expressoes.out", "w", stdout);
    int nOperadores, aux, nExpressoes, abrindo, fechando, qntdOperadores, fbf, cont, fim, i, subExpressoes;
    operador *vetor;
    char expressao [101], copia [101];


    scanf ("%d", &nOperadores); //coleta o numero de operadores

    vetor = (operador*) malloc (nOperadores*sizeof (operador)); //aloca espaco para um vetor de operadores


    for (aux=0; aux < nOperadores; aux++){
        vetor[aux] = f_coleta_operador ();
        //f_imprime_operador(vetor[aux]);
    }

    scanf ("%d", &nExpressoes); //coletar o numero de expressoes

    for (aux = 0; aux<nExpressoes; aux++){
        scanf ("%s", expressao); //coletar a expressao
        //printf ("expressao:%s\n", expressao);

        abrindo = f_parenteses_abrindo(expressao); //calcular o numero de parenteses abrindo
        fechando = f_parenteses_fechando (expressao); //calcular o numero de parentes fechando
        qntdOperadores = f_numero_operadores(expressao, vetor, nOperadores); //calcular o numero de operadores


        /*se a qntd de operadores for igual ao numero de parenteses
        e o numero de parenteses abrindo for igual ao numero de parenteses fechando, verifica se e fbf*/
        if (qntdOperadores == abrindo && abrindo == fechando){
            strcpy (copia, expressao); //copia a expressao


            do{
                i = abrindo;
                for (cont=0; i>0; cont++){ //localiza cont no proximo '(' da string
                    if (copia[cont]=='(')
                        i--;
                }
                cont--; //ele ainda avanca uma casa antes de sair do laço


                for (fim=cont; copia[fim]!= ')'; fim++){ //localiza fim no final da expressao
                }


                fbf = f_fbf (copia, cont, fim, vetor, nOperadores); //verifica se é fbf


                if (fbf == 1){ //se for fbf
                    copia [cont] = '1'; //substitui o '(' por 1


                    for (i=cont+1; copia[fim+1]!= '\0'; i++){ //substituir a expressao por um caractere valido

                        copia[i] = copia[fim+1];
                        fim++;
                    }

                }

                abrindo--;
            }while (abrindo > 0 && fbf ==1);

        }
        else{
            fbf = 0;
        }


        if (fbf ==1){
            printf ("Expressao %d\n", aux+1);
            printf ("Expressao bem-formada\n");

            //Se for fbf, calcular a altura da árvore, o n° de subespressoes e as possíveis valorações
            strcpy (copia, expressao); //copiar a expressao
            abrindo = fechando; //retomar o numero de parentesis abrindo

            subExpressoes = f_sub_expressoes (expressao, abrindo, fechando);
            printf ("Sub-expressoes=%d\n", subExpressoes);

        }
        else{
            printf ("Expressao mal-formada\n");
        }
    }


    free (vetor); //libera espaco alocado para o vetor de operadores
    return 0;
}

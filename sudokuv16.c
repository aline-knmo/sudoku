/**
 * Descrição: jogo sudoku em linguagem c
 * Autor: Aline Diniz
 * Data de criação: 23/10/2017
 */

#include <stdio.h>
#include <stdlib.h>

int sudoku[9][9], i, j;
char sudokuAUX[9][9];
int matrizBase[9][9] = {
							{9, 2, 6, 8, 4, 1, 7, 5, 3 },
							{5, 3, 8, 7, 2, 6, 9, 1, 4 },
							{4, 7, 1, 9, 5, 3, 2, 6, 8 },
							{7, 5, 4, 6, 3, 9, 1, 8, 2 },
							{6, 1, 9, 4, 8, 2, 3, 7, 5 },
							{2, 8, 3, 5, 1, 7, 6, 4, 9 },
							{3, 9, 5, 1, 7, 4, 8, 2, 6 },
							{1, 4, 2, 3, 6, 8, 5, 9, 7 },
							{8, 6, 7, 2, 9, 5, 4, 3, 1 }
						};

void inicializar()
{//a matriz sudoku fica com os valores da matriz de base
	for(i = 0; i < 9; i++)
    {
        for(j = 0; j < 9; j++)
        {
            sudoku[i][j] = matrizBase[i][j];
        }
    }
}

void imprimeSudokuCompleto()
{//printa a solucao do sudoku
	printf("\nSolucao:\n");
	printf("+-----------------+-----------------+-----------------+\n");

	//imprime a matriz sudoku
	for(i = 0; i < 9; i++)
    {
        printf("|");
		for(j = 0; j < 9; j++)
		{
			printf("  %d  |", sudoku[i][j]);
		}
		if ((i+1)%3==0)  printf("\n+-----------------+-----------------+-----------------+\n");
		else  printf("\n-------------------------------------------------------\n");
	}
}

void geraArquivoeImprimeSudoku()
{//imprime o tabuleiro inicial e gera um arquivo de texto
	int aux = 0;

	char matrizaux[9][9];

//----------------------arq1-----------------------
	FILE *arq1;  //ponteiro tipo file
	arq1 = fopen("sudoku_modelo.txt", "r");  //abre o arquivo para leitura

	if(arq1 == NULL)  printf("Problemas na CRIACAO do arquivo\n");


	//i = linha  j = coluna
	for(i = 0; i < 9; i++)
    {
        for(j = 0; j < 9; j++)
        {//le o que está escrito no arquivo e coloca na matrizaux
            fscanf(arq1, "%c", &matrizaux[i][j]);
        }
    }


	for(i = 0; i < 9; i++)
    {
		do {//coloca os espaços em branco
			j = rand() % 9;
			matrizaux[i][j] = ' ';

			j = rand() % 9;
			matrizaux[i][j] = ' ';

			j = rand() % 9;
			matrizaux[i][j] = ' ';

			j = rand() % 9;
			matrizaux[i][j] = ' ';

			j = rand() % 9;
			matrizaux[i][j] = ' ';

			j = rand() % 9;
			matrizaux[i][j] = ' ';

			aux++;
		} while (aux < 5);
	}

	printf("\nLinha\\Coluna\n\n         1     2     3     4     5     6     7     8     9\n");
	printf("      +-----------------+-----------------+-----------------+\n");

	//i = linha  j = coluna
	for(i = 0; i < 9; i++) //printa a matrizaux
    {
        printf("  %d   |",i+1);
		for(j = 0; j < 9; j++)
		{
			printf("  %c  |", matrizaux[i][j]);
		}
		if ((i+1)%3==0)  printf("\n      +-----------------+-----------------+-----------------+\n");
		else  printf("\n      -------------------------------------------------------\n");
	}

	fclose(arq1); //fecha o arquivo

//-------------------------arq2-----------------------------
	FILE *arq2;  //cria ponteiro do tipo file
	arq2 = fopen("sudoku.txt", "w");  //abre arquivo para escrita

	if(arq2 == NULL)  printf("Problemas na CRIACAO do arquivo\n");

	fprintf(arq2, "\nLinha\\Coluna\n\n         1     2     3     4     5     6     7     8     9\n");
	fprintf(arq2, "      +-----------------+-----------------+-----------------+\n");

	//coloca matrizaux no arquivo
	//i = linha  j = coluna
	for(i = 0; i < 9; i++)
    {
        fprintf(arq2, "  %d   |", i+1);
        for(j = 0; j < 9; j++)
        {
            fprintf(arq2, "  %c  |", matrizaux[i][j]);
		}
		if ((i+1)%3==0)  fprintf(arq2, "\n      +-----------------+-----------------+-----------------+\n");
		else fprintf(arq2, "\n      -------------------------------------------------------\n");
    }
	fclose(arq2);  //fecha o arquivo

//-------------------------arq3--------------------------------
	FILE *arq3;  //arquivo sem quebra de linha com os numeros e espaços da matriz (usado na funcao resolve)
	arq3 = fopen("SoSudoku.txt", "w");  //abre arquivo para escrita

	if(arq3 == NULL)  printf("Problemas na CRIACAO do arquivo\n");

	for(i = 0; i < 9; i++)
    {
        for(j = 0; j < 9; j++)
        {
            fprintf(arq3, "%c", matrizaux[i][j]);
		}
    }
    fclose(arq3);

    //---coloca os valores e espacos em branco na matriz auxiliar
    //---necessario para a funcao resolve()
    arq3 = fopen("SoSudoku.txt", "r");
    for(i = 0; i < 9; i++)
    {
        for(j = 0; j < 9; j++)
        {
            fscanf(arq3, "%c", &sudokuAUX[i][j]);
		}
    }
    fclose(arq3);
}

void geraArquivoSudokuModelo()
{//coloca os valores da matriz sudoku em um arquivo
	FILE *arq; //para trabalhar com arquivos criar um ponteiro do tipo FILE

	int aux[9][9];
	int result;

    //----aux = sudoku----
	for(i = 0; i < 9; i++)
    {
        for(j = 0; j < 9; j++)
        {
            aux[i][j] = sudoku[i][j];
        }
    }
    //---------------------------
    //abre o arquivo para escrita
	arq = fopen("sudoku_modelo.txt", "w");
    //se o arquivo não for aberto
	if(arq == NULL)  printf("Problemas na CRIACAO do arquivo\n");

    //i = linha  c = coluna
	for(i = 0; i < 9; i++)
    {
        for(j = 0; j < 9; j++)
        {//escreve o valor de aux[i][j] no arquivo
            fprintf(arq, "%d", aux[i][j]);
        }
    }

	fclose(arq);  //fecha o arquivo
}


void trocaDuasLinhas(int linha1, int linha2)
{
	int aux; // aux variavel auxiliar para trocar os valores das linhas 1 e 2

	for(j = 0; j < 9; j++)
    {//troca os valores das linhas 1 e 2
		aux = sudoku[linha1][j];

		sudoku[linha1][j] = sudoku[linha2][j];
		sudoku[linha2][j] = aux;
	}
}

void trocaMuitasLinhas(int lgrande1, int lgrande2)
{//troca os valores de seis linhas
    //o valor maximo desta funcao é 2 (para não ultrapassar o valor maximo do indice da matriz)
	if(lgrande1 > 2 || lgrande2 > 2)  printf("ERRO LINHA GRANDE");
	else
    {
		trocaDuasLinhas(lgrande1 * 3, lgrande2 * 3);  //0 || 3 || 6
		trocaDuasLinhas(lgrande1 * 3 + 1, lgrande2 * 3 + 1);  //1 || 4 || 7
		trocaDuasLinhas(lgrande1 * 3 + 2, lgrande2 * 3 + 2);  //2 || 5 || 8
	}
}

void trocaDuasColunas(int col1, int col2)
{
	int aux; // aux variavel auxiliar para trocar os valores das colunas 1 e 2

	for(i = 0; i < 9; i++)
    {//troca os valores das colunas 1 e 2
		aux = sudoku[i][col1];

		sudoku[i][col1] = sudoku[i][col2];
		sudoku[i][col2] = aux;
	}
}

void trocamuitascolunas(int cgrande1, int cgrande2)
{//troca os valores de seis colunas
    //o valor maximo desta funcao é 2 (para não ultrapassar o valor maximo do indice da matriz)
	if(cgrande1 > 2 || cgrande2 > 2)  printf("ERRO COLUNA GRANDE");
	else
    {
		trocaDuasColunas(cgrande1 * 3, cgrande2 * 3);//0 || 3 || 6
		trocaDuasColunas(cgrande1 * 3 + 1, cgrande2 * 3 + 1);//1 || 4 || 7
		trocaDuasColunas(cgrande1 * 3 + 2, cgrande2 * 3 + 2);//2 || 5 || 8
	}
}

void giraVertical()
{//inverte os valores da matriz verticalmente (as três colunas das bordas)
    //os valores das colunas "da direita" são trocados com os valores das colunas "da esquerda"
	int aux; //aux variável auxiliar da troca

	//i = linhas e j = colunas
	for(i = 0; i < 9; i++) //0 - 8
    {
		for(j = 0; j < 9/2; j++) //9/2 = 4  |  0 - 3
		{
			aux = sudoku[i][j];

			sudoku[i][j] = sudoku[i][8 - j]; // troca as colunas 0 e 8, 1 e 7 e 2 e 2 e 6
			sudoku[i][8 - j] = aux;
		}
	}
}

void giraHorizontal()
{//inverte os valores da matriz horizontalmente (as três linhas das bordas)
    //os valores das linhas "de cima" são trocados com os valores das linhas "de baixo"
	int aux; //aux variável auxiliar da troca

	//i = linhas e j = colunas
	for(i = 0; i < 9/2; i++) //9/2 = 4  |  0 - 3
    {
		for(j = 0; j < 9; j++)	  // 0 - 8
        {
			aux = sudoku[i][j];

			sudoku[i][j] = sudoku[8 - i][j];
			sudoku[8 - i][j] = aux;  // troca as linhas 0 e 8, 1 e 7 e 2 e 2 e 6
		}
	}
}

void linhaViraColuna()
{//as linha viram colunas
	int aux;

	//i = linha c = coluna
	for(i = 0; i < 9; i++)
    {
		for(j = i; j < 9; j++)
		{
			aux = sudoku[i][j];

			sudoku[i][j] = sudoku[j][i];
			sudoku[j][i] = aux;
		}
	}
}

void inverteMatriz()
{
	giraVertical();//inverte os valores da matriz verticalmente (as três colunas das bordas)
	linhaViraColuna();//as linha viram colunas
}

void substitui(int a, int b)
{//substitui todos os valores da a na matriz pelos valores de b e vise-versa
	//i = linha j = coluna
	for(i = 0; i < 9; i++)
    {
		for(j = 0; j < 9; j++)
		{
		    //a vira b
			if(sudoku[i][j] == a)  sudoku[i][j] = b;
            //b vira a
			else if(sudoku[i][j] == b)  sudoku[i][j] =a;
		}
	}
}

void criaMatriz()
{
	inicializar();
	srand(time(NULL));

	int embaralha, bloco;

	for(i = 0; i < 10; i++)
    {
		embaralha = rand() % 10;  //valores aleatorios de 0 - 9
		bloco = rand() % 3;       //valores aleatorios de 0 - 2

		switch(embaralha){
		case 0:
			switch(bloco)
			{
				case 0: //troca os valores das linhas:
					trocaDuasLinhas(rand() % 3, rand() % 3);  //0 - 2
					break;

				case 1:
					trocaDuasLinhas((rand() % 3)+3, (rand() % 3)+3);  //3 - 5
					break;

				case 2:
					trocaDuasLinhas((rand() % 3)+6, (rand() % 3)+6);  //6 - 8
					break;

			}
			break;
		case 1://troca os valores de seis linhas
			trocaMuitasLinhas((rand() % 3), (rand() % 3));  //nunca sera maior que dois
			break;

		case 2://troca os valores das colunas:
			switch(bloco)
			{
				case 0:
					trocaDuasColunas((rand() % 3), (rand() % 3));  //0 - 2
					break;

				case 1:
					trocaDuasColunas((rand() % 3)+3, (rand() % 3)+3);  //3 - 5
					break;

				case 2:
					trocaDuasColunas((rand() % 3)+6, (rand() % 3)+6);  //6 - 8
					break;
				}
			break;
		case 3://troca os valores de seis colunas
			trocamuitascolunas((rand() % 3), (rand() % 3));  //nunca sera maior que dois
			break;

		case 4://gira os valores das colunas da matriz (os primeiros serão os ultimos e os ultimos os primeiros)
			giraVertical();
			break;

		case 5://gira os valores das linhas da matriz (os primeiros serão os ultimos e os ultimos os primeiros)
			giraHorizontal();
			break;

		case 6://as linhas da matriz viram colunas
			linhaViraColuna();
			break;

		case 7://as linhas da matriz viram colunas
		    linhaViraColuna();
			//inverteMatriz();
			break;

		case 8://chama as funções dos casos 4 e 7
			inverteMatriz();
			break;

		case 9://a vira b e b vira a
			substitui((rand() % 9) + 1, (rand()  % 9)+ 1);
			break;
		}
	}
}

void mostraResposta(char matriz[][9])
{//mostra a matriz com os numeros digitados no lugar dos espacos em branco

    printf("\nLinha\\Coluna\n\n         1     2     3     4     5     6     7     8     9\n");
	printf("      +-----------------+-----------------+-----------------+\n");

	for(i = 0; i < 9; i++)
    {
        printf("  %d   |", i+1);
        for(j = 0; j < 9; j++)
        {
            printf("  %c  |", matriz[i][j]);
		}
		if ((i+1)%3==0)  printf("\n      +-----------------+-----------------+-----------------+\n");
		else  printf("\n      -------------------------------------------------------\n");
    }
    return;
}

int verifica(char matriz[][9], int mcerta[][9])
{//verifica se os numeros digitados estao certos
    for(i=0;i<9;i++)
    {
        for(j=0;j<9;j++)
        {
            if (matriz[i][j]==' ')  return 0;
            else if(matriz[i][j]-'0' != mcerta[i][j])  return 0;
        }
    }

    return 1;
}

void resolve()
{//le os numeros que a pessoa quer digitar
//----------variaveis-------------
    struct coordenadas
    {
        int linha;
        int coluna;
        char valor;
    };
    struct coordenadas coord;

    int x=0, conseguiu;
    char sudokuTemp[9][9];
//--------------------------------------
//--------armazena nas matrizes sudokuTemp e sudokuAUX os numeros e espaços em branco------
        FILE *arq1;  //ponteiro tipo file
        arq1 = fopen("SoSudoku.txt", "r");  //abre o arquivo para leitura

        if(arq1 == NULL)  printf("Problemas na leitura do arquivo\n");

        //i = linha  j = coluna
        for(i = 0; i < 9; i++)
        {
            for(j = 0; j < 9; j++)
            {//le o que está escrito no arquivo e coloca na matriz sudokuTemp
                fscanf(arq1, "%c", &sudokuTemp[i][j]);
            }
        }
        fclose(arq1);
//-----------------------------------------------------------------------
//--------le as coordenadas e o valor---------------------------------
    printf("\ndigite 0 para ir ao menu\n");
    printf("\nDigite as coordenadas e o numero\nLinha....");
    scanf("%d",&coord.linha);
    if (coord.linha==0)  return;  //se o número 0 for digitado volta ao menu
    printf("\ncoluna...");
    scanf("%d", &coord.coluna);
    if (coord.coluna==0)  return;
    printf("\nnumero...");
    scanf(" %c", &coord.valor);
    if (coord.valor == '0')  return;

    coord.linha--;    //eu printei de 1 a 9 e a matriz (neste código) é de 0 a 8
    coord.coluna--;
//--------------------------------------------------------------------
    if (sudokuAUX[coord.linha][coord.coluna] == ' ')  //testa se a coodenada esta disponivel
    {
        sudokuTemp[coord.linha][coord.coluna]= coord.valor;
//---------------gera arquivo sem quebra de linha---------------------
        arq1 = fopen("SoSudoku.txt", "w");
        if(arq1 == NULL)  printf("Problemas na CRIACAO do arquivo\n");
        //coloca a solucao sem quebra de linha no arquivo
        for(i = 0; i < 9; i++)
        {
            for(j = 0; j < 9; j++)
            {
                fprintf(arq1, "%c", sudokuTemp[i][j]);
            }
        }
        fclose(arq1);
//---------------------------------------------------------------
        mostraResposta(sudokuTemp);
    }
    else  printf("\nCoordenada indisponivel\n");

    conseguiu = verifica(sudokuTemp, sudoku);

    if (conseguiu) //se a funcao verifica retornar 1
    {
        printf("Parabens voce conseguiu!!!^^");
        return;
    }
    else  resolve();
}

int main()
{
    //system("clear");  //limpa a tela no linux
    system("cls");  //limpa a tela no windows
	char opcao;

	do {

		printf("\nMenu:\n");
		printf("1. Novo Jogo\n");
		printf("2. Ver Solucao do Jogo Atual\n");
		printf("3. Sair\n");

        //limpa o buffer
        //fflush(stdin);  //no windows
		//__fpurge(stdin);  //no linux (2 underlines)
		scanf(" %c", &opcao);  //espaço em branco antes do c funciona no windows e no linux^^

			switch(opcao) {
				case '1'://caso a opcao 1 seja escolhida
					//system("clear");  //limpa a tela no linux
					system("cls");  //limpa a tela no windows
					criaMatriz();  //gera a matriz sudoku
					geraArquivoSudokuModelo();  //coloca os valores da matriz sudoku em um arquivo
					geraArquivoeImprimeSudoku();//coloca os espacos em branco no arquivo
					resolve();
					break;

				case '2'://caso a opcao 2 seja escolhida
					imprimeSudokuCompleto();  //imprime a solucao
					break;

				case '3'://caso a opcao 3 seja escolhida
					return 0;

				default://caso outra tecla seja pressionada:
					//system("clear");  //limpa a tela no linux
					system("cls");  //limpa a tela no windows
					printf("\nERRO: Opcao invalida.\n");  //printa uma mensagem de erro
					break;
			}

	} while(opcao != 0);

	return 0;
}

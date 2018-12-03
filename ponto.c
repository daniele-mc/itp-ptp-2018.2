#include "ponto.h"

//primeiro ponto.

void criar_tabela()
{
	// atributos é a quantidade de atributos, tipo é o número que corresponde ao tipo,listaAtributos é a lista que vai receber os nomes dos atributos, listaTipos é a lista de atributos já com seu tipo, nomeArquivo é o nome da tabela que vai ser criada.
	//i,j,p e controle, são variáveis de auxílio. 

	int atributos,i,j,tipo,p;
	char chavePrimaria[100];
	char ** listaAtributos;
	int *listaTipos;
	char nomeArquivo[100];
	int controle;
	FILE * arquivo;

	getchar();


	printf("\nPara nomes compostos (mais de uma palavra), use _ como espaço!\n\n");

	printf("Qual o nome da tabela ou do arquivo:\n");
	fgets(nomeArquivo, 100, stdin);

	controle = lendoTabelas(nomeArquivo);

	if (controle == 1)
	{
		printf("essa tabela já existe\n");
		return;
	}

	criandoTabela(nomeArquivo);

	printf("Digite a quantidade de atributos incluindo a chave primaria (colunas):\n");
	scanf("%d", &atributos);
	getchar();

	/*ALOCAÇÃO*/

	listaTipos = alocar_int(atributos);

	listaAtributos = alocar_char(atributos);


	strcat(nomeArquivo,".TXT");
	arquivo = fopen(nomeArquivo,"w+");
	
	if (arquivo == NULL)
	{
		printf("erro na abertura do arquivo\n");
	}

	receber_quantColuna(atributos, arquivo);

	receber_atributos(listaAtributos, atributos, arquivo);

	declarar_tipo(listaTipos, atributos, arquivo);

	fclose(arquivo);

	for(i=0; i<atributos; i++){
		free(listaAtributos[i]);
	}
	free(listaAtributos);
	free(listaTipos);

	return;
}

//funções para alocação.

int * alocar_int(int colunas){
	int *lisTipos;
	lisTipos = (int*) malloc(colunas * sizeof(int));
	if (lisTipos == NULL)
		{
			printf("memoria insuficiente\n");
		}
	return lisTipos;
}


char **alocar_char(int colunas){
	char **lisAtrib;
	int i;
	lisAtrib = (char**) malloc(colunas * sizeof(char*));
	if (lisAtrib == NULL)
		{
			printf("memoria insuficiente\n");
		}	
	for (i = 0; i < colunas; i++)
	{
		lisAtrib[i] = (char*) malloc (colunas * sizeof(char));
		if (lisAtrib[i] == NULL)
		{
			printf("memoria insuficiente\n");
		}
	}
	return lisAtrib;

}

//função para verificar a existência de arquivo ou se o arquivo está vazio.

int get_size()
{
    FILE *file = fopen("tabelas.TXT", "r");

    if (file == NULL)
	{
		printf("erro na abertura do arquivo ou o arquivo não existe!\n");
		return 0;
	}

    fseek(file, 0, SEEK_END);
    int size = ftell(file);
    fclose(file);

    return size;
}

int lendoTabelas(char nomeArquivo[100]){
	int i=0;

	char linha[100];

	char * ptr_palavra;
	
	if(get_size() == 0)
	{
	    printf("O arquivo esta vazio.\n");
	    return 0;
	}

	FILE * todosArquivos;
	todosArquivos = fopen("tabelas.TXT", "r+");

	do{
		i++;
		fgets(linha, 100, todosArquivos);

		ptr_palavra = strpbrk (linha, " ");

		if (strcmp(ptr_palavra+1, nomeArquivo) == 0){
			fclose(todosArquivos);
			return 1;
		}

	}while(!feof(todosArquivos));

    fclose(todosArquivos);
    return 0;
}

//função para efetivamente criar a tabela se ela não existir.

void criandoTabela(char nomeArquivo[100]){
	FILE * todosArquivos;
	if (todosArquivos == NULL)
	{
		printf("erro na abertura do arquivo\n");
	}
	todosArquivos = fopen("tabelas.TXT", "a+");
	fprintf(todosArquivos, "Nome: %s", nomeArquivo);
	
	fclose(todosArquivos);
}

void receber_quantColuna(int colunas, FILE * arquivo){
	fprintf(arquivo, "colunas:%d,\n", colunas);
}

void receber_atributos(char **listAtributos, int colunas, FILE *arquivo){
	int i,j;
	printf("\nPara nomes compostos (mais de uma palavra), use _ como espaço!\n\n");

	for (i = 0; i < colunas; i++)
	{	
		if (i == 0)
		{
			printf("Qual o nome da chave primária?\n(obrigatoriamente ela deve ser um número inteiro positivo):\n");
		}
		else{
			printf("digite o nome do %d atributo\n", i+1);
		}
		fgets(listAtributos[i], 100, stdin);
		fprintf(arquivo, "%s", listAtributos[i]);
		fseek(arquivo, -1 , SEEK_CUR);
		fprintf(arquivo, " |");
	}

	fprintf(arquivo, "\n");
}

void declarar_tipo(int *ponteiroTipo, int colunas,FILE *arquivo){
	int i, tipo;
	printf("\nTipos dos atributos:\ndigite 1 para inteiro\ndigite 2 para double\ndigite 3 para char\ndigite 4 para string\n");

	if (arquivo == NULL)
		{
			printf("erro na abertura do arquivo\n");
		} 

	fseek(arquivo, 0, SEEK_END);

	for (i = 0; i < colunas; i++)
	{
		if (i == 0)
		{
			ponteiroTipo[i] = 1;
		}
		else{
			printf("\ntipo do %d atributo: \n", i+1);
			scanf("%d", &tipo);

			switch (tipo)
			{
   				case 1:
     				ponteiroTipo[i] = 1;
   					break;

   				case 2:
 	    			ponteiroTipo[i] = 2;
   					break;

   				case 3:
   					ponteiroTipo[i] = 3;
   					break;

   				case 4:
   					ponteiroTipo[i] = 4;	
   					break;

   				default:
   					printf("valor invalido\n");
   					printf("insira outro valor\n");
   					i = i-1;
   					break;
			}
		}
	}

	for (i = 0; i < colunas; i++)
	{
		fprintf(arquivo, "%d,", ponteiroTipo[i]);
	}
	fprintf(arquivo, "|\n");

}

//segundo ponto.

void listar_tabela(){

	//ptr_palavra é um ponteiro que aponta para o ínicio dos nomes das tabelas dentro do arquivo, e linha é a variável que vai receber a linha completa.

	int i,j;
	j = 0;
	char linha[100];
	char * ptr_palavra;
	
	FILE * todosArquivos;
	todosArquivos = fopen("tabelas.TXT", "r");
	if (todosArquivos == NULL)
	{
		printf("erro na abertura do arquivo\n");
		return;
	}

	while(!feof(todosArquivos)){
		j++;
		fgets(linha, 100,todosArquivos);
	}

	fseek(todosArquivos, 0, SEEK_SET);

	for (i = 0; i < j-1; i++)
	{
		fgets(linha, 100,todosArquivos);

		ptr_palavra = strpbrk (linha, " ");

		printf("%s", ptr_palavra+1);
	}

    fclose(todosArquivos);
    return;
}

//terceiro ponto.

void criar_novaLinha()
{
	//colunas é a quantidade de colunas, listaChave vai receber as chaves já existentes, lixo é uma variável de auxílio para receber algo que não será usado no momento. 
	//repet é a variavel usada para permite que se insira outro valor para a chave primária caso o anterior já exista, listaTipos é a lista com os tipos de cada atributo.
	//listaAtributos a lista com os nomes dos atributos, e listInformation e a lista que vai receber as informações da linha.
	int colunas,i,p,j,controle,repet,erro;
	repet = 0;
	FILE * arquivo;
	unsigned long int chavePrimaria;
	unsigned long int * chaveP;
	chaveP = &chavePrimaria;
	unsigned long int listaChave[100] = {0};
	char lixo[100];
	char listaTipos[100];
	char **listaAtributos;
	char **listInformation;
	char nomeTabela[100];

	printf("Nome da tabela?\n");
	fgets(nomeTabela, 100, stdin);

	controle = lendoTabelas(nomeTabela);
	if (controle == 0)
	{
		printf("essa tabela não existe!\n");
		return;
	}

	strcat(nomeTabela,".TXT");

	arquivo = fopen(nomeTabela,"r+");

	if (arquivo == NULL)
	{
		printf("erro na abertura do arquivo\n");
		return;
	}

	fscanf(arquivo,"colunas:%d,", &colunas);

	listaAtributos = alocar_char(colunas);
	listInformation = alocar_char(colunas);

	for (i = 0; i < colunas; i++)
	{
		fscanf(arquivo,"%s |", listaAtributos[i]);
	}
	fseek(arquivo, 1, SEEK_CUR);

	fscanf(arquivo, "%s|", listaTipos);

	j = 0;
	while(!feof(arquivo)){
		fscanf(arquivo, "%lu |", &listaChave[j]);
		fgets(lixo, 100, arquivo);
		j++;
	}

	if (arquivo == NULL)
	{
		printf("erro na abertura do arquivo\n");
		return;
	}

	for (i = 0; i < 1; i++)
	{
		erro = verificar_chave(listaAtributos, chaveP);
		if (erro == 1)
		{
			printf("Por favor recomece.\n");
			return;
		}
	}

	for (p = 0; p < j; p++)
	{
			if (chavePrimaria == listaChave[p])
			{
				printf("essa chave já existe\n");
				printf("digite outra chave\n");
				repet = 1;
			}
			if (repet == 1)
			{
				scanf("%lu",&chavePrimaria);
				i = i-1;
				repet = 0;
			}
	}
	fprintf(arquivo, "%lu", chavePrimaria);
	fprintf(arquivo, " |");
	getchar();
	for (i = 0; i < colunas-1; i++)
	{
		printf("digite %s:\n", listaAtributos[i+1]);
		fgets(listInformation[i], 100, stdin);
		fprintf(arquivo, "%s", listInformation[i]);
		fseek(arquivo, -1 , SEEK_CUR);
		fprintf(arquivo, " |");
		
	}

	fprintf(arquivo, "\n");
	fclose(arquivo);

	for(i=0; i<colunas; i++){
		free(listaAtributos[i]);
	}
	free(listaAtributos);

	for(i=0; i<colunas; i++){
		free(listInformation[i]);
	}
	free(listInformation);
	
	return;
}

int verificar_chave(char ** listaAtributos, unsigned long int * chaveP){
	int i = 0;
	char lixo[100];
		printf("digite %s:\n", listaAtributos[i]);
			if(scanf("%lu", chaveP)){
				//faz nada
			}
			else{
				printf("você não digitou um inteiro como chave.\n");
				fgets(lixo,100,stdin);
				return 1;
				}
	return 0;
}

// quarto ponto.

void listar_dadosTabela(){

	//tamanhoString é a variavel que receber o tamanho da string para poder ser subtraindo da constante 19 e dar origem a quantidade de espaços para serem impressos que é armazenados na quantidadeSpace.

	int colunas,i,j,k,p,controle, tamanhoString, quantidadeSpace;
	FILE * arquivo;
	char **listaAtributos;
	char listaTipos[100], string[100];
	char nomeTabela[100];

	printf("existem essas tabelas:\n");
    listar_tabela();
    
	printf("Nome da tabela?\n");
	fgets(nomeTabela, 100, stdin);

	controle = lendoTabelas(nomeTabela);
	if (controle == 0)
	{
		printf("essa tabela não existe!\n");
		return;
	}

	strcat(nomeTabela,".TXT");

	arquivo = fopen(nomeTabela,"r+");

	if (arquivo == NULL)
	{
		printf("erro na abertura do arquivo\n");
		return;
	}

	fscanf(arquivo,"colunas:%d,", &colunas);

	listaAtributos = alocar_char(colunas*100);

	fseek(arquivo, 1, SEEK_CUR);

	fgets(listaAtributos[0], 100, arquivo);

	fgets(listaTipos, 100, arquivo);

	j = 0;
	while(!feof(arquivo)){
		j++;
		fgets(listaAtributos[j], 100, arquivo);
	}

//imprmindo os atributos

	fseek(arquivo, 0, SEEK_SET);
	for (i = 0; i < 4; i++)
	{
		if (i==1)
		{
			for (k = 0; k < colunas; k++)
			{
				fscanf(arquivo,"%s |", string);
				tamanhoString = 0;
				quantidadeSpace= 0;
				tamanhoString = strlen(string);
		    	quantidadeSpace = 15 - tamanhoString;
						
				printf("%s", string);
				for (p = 0; p < quantidadeSpace; p++)
				{
					printf(" ");
				}
			printf("|");
			}
	    	printf("\n");
	    }
		else{
			fgets(listaAtributos[i], 100, arquivo);
		}
	}


	for (i = 0; i < 16*colunas; i++)
	{
		printf("-");
	}
	printf("\n");

//imprimindo as linhas

	for (i = 0; i < j-1; i++){

		for(k = 0; k < colunas; k++){
	
				fscanf(arquivo,"%s |", string);
				tamanhoString = 0;
				quantidadeSpace= 0;
				tamanhoString = strlen(string);
		    	quantidadeSpace = 15 - tamanhoString;
						
						printf("%s", string);
						for (p = 0; p < quantidadeSpace; p++)
						{
							printf(" ");
						}
				printf("|");
			}
		printf("\n");
	}

	fclose(arquivo);
	for(i=0; i<colunas; i++){
		free(listaAtributos[i]);
	}
	free(listaAtributos);
	
	return;
}

//quinto ponto.

void procurar_valor()
{

	int controle, i, colunas, escolha, pesquisa,  j = 0;
	char nomeTabela[100];
	char atributo[100];
	char linha[100];
	int *tipos;
	char lixo[100];

	TIPOS variavel;
	FILE *lerTabela;
	
	printf("Informe o nome da tabela\n");
	fgets(nomeTabela,100,stdin);
// verifica se existe uma tabela com esse nome
	controle = lendoTabelas(nomeTabela);

	if (controle == 0)
	{
		printf("essa tabela não existe\n");
		return;
	}
	else
	{
		strcat(nomeTabela,".TXT");
	}
// lê o arquivo que contém a tabela
	lerTabela = fopen(nomeTabela, "r");

	if (lerTabela == NULL)
	{
		printf("erro na abertura do arquivo\n");
		return;
	}
// lê a quantidade de colunas e armazena em uma variável	
	fscanf(lerTabela,"colunas:%d,", &colunas);
	
	tipos = alocar_int(colunas*100);
// mostra as colunas para o usuário escolher qual valor pesquisar
	printf("As colunas disponíveis são:\n");
	for (i = 0; i < colunas; i++)
	{
		fscanf(lerTabela, "%s |", atributo);
		
		printf("%d - %s\n",i+1, atributo);
	}

	printf("Digite o numero da coluna que deseja pesquisar\n");
	scanf("%d", &escolha);
	for (i = 0; i < colunas; i++)
	{
		fscanf(lerTabela, "%d,", &tipos[i]);
	}

	fseek(lerTabela, 2, SEEK_CUR);
// lê a quantidade de linhas do arquivo
	while(! feof(lerTabela))
	{

		fgets(linha, 100,lerTabela);
		j++;

	}
	fseek(lerTabela, 0, SEEK_SET);
	j = j-1;

	for(i = 0; i < 3; i++)
	{
		fgets(lixo, 100, lerTabela);
	}
// o usuário digita um valor e o programa reconhece se é um inteiro, um float, um caractere ou uma string
// armazena o tipo que o usuario digitou em uma lista
	printf("Digite o valor para pesquisar\n");
	
	switch (tipos[escolha-1]){
		case 1:
			scanf("%lu", &variavel.inteiro);
			break;
		case 2:
			scanf("%f", &variavel.decimal);
			break;
		case 3:
			scanf(" %c", &variavel.caractere);
			break;
		case 4:
			scanf("%s", variavel.string);
			break;
		default:
			printf("Valor invalido");
			break;

	}
// opções de busca
	printf("1 - valores maior que o informado\n");
	printf("2 - valores maior ou igual que o valor informado\n");
	printf("3 - valores igual o valor informado\n");
	printf("4 - valores menor que o valor informado\n");
	printf("5 - valores menor ou igual que o valor informado\n");
	printf("6 - valores próximo ao valor informado (apenas se a coluna for do tipo string)\n");
	scanf("%d", &pesquisa);

	switch (pesquisa){
		case 1:
			procurar_maior(lerTabela, variavel, tipos[escolha-1], j, colunas, escolha);
			break;
		case 2:
			procurar_maior_igual(lerTabela, variavel, tipos[escolha-1], j, colunas, escolha);
			break;

		case 3:
			procurar_igual(lerTabela, variavel, tipos[escolha-1], j, colunas, escolha);
			break;

		case 4:
			procurar_menor(lerTabela, variavel, tipos[escolha-1], j, colunas, escolha);
			break;

		case 5:
			procurar_menor_igual(lerTabela, variavel, tipos[escolha-1], j, colunas, escolha);
			break;
		case 6:
			procurar_aproximado(lerTabela, variavel, tipos[escolha-1], j, colunas, escolha);
			break;
		default:
			printf("Valor invalido");
			break;

	}
	fclose(lerTabela);
	
	free(tipos);
}
// procura maior valor
void procurar_maior(FILE *arquivo, TIPOS variavel, int escolhat, int linhas, int colunas, int escolhaAtributo){
	int i, m, constante, valores = 0, cont = 0, aux = 0;
	unsigned long int caso1, listaValor1[linhas];
	float caso2, listaValor2[linhas];
	char caso3, listaValor3[linhas];
	char *caso4, **listaValor4;
	char **linhaToda;

	linhaToda = alocar_char(colunas *100);
	
	caso4 = (char*) malloc(linhas*colunas*sizeof(char));
	if (caso4 == NULL)
	{
		printf("erro de alocação!\n");
	}

	listaValor4 = alocar_char(linhas*colunas);
	char lixo[100];
	printf("\n");
	
	switch (escolhat){
// se o que o usuário digitou for um inteiro vai para o case 1
		case 1:
			caso1 = variavel.inteiro;

			for (m = 0; m < linhas; m++)
			{
				for (i = 0; i < colunas; i++)
				{
					if (i == (escolhaAtributo-1))
					{
//pega o valor que tem no arquivo e armazena em uma lista
						fscanf(arquivo, "%lu |", &listaValor1[cont]);
						cont++;
					}
					else{
					fscanf(arquivo, "%s |", lixo);
					}
				}
			}
			fseek(arquivo,0,SEEK_SET);

			for (i = 0; i < 3; i++)
			{
				fgets(lixo, 100, arquivo);
			}

			for (i = 0; i < linhas; i++)
			{
				fgets(linhaToda[i], 100, arquivo);
			}
// compara os valores que encontrou no arquivo com o que o usuário digitou para informar quantos resultados encontrou
			for (i = 0; i < linhas; i++)
			{
				if (listaValor1[i] > caso1){
					valores++;
				}
			}
			
			printf("Existe %d valor(es) para o que voce quer:\n\n", valores);

// imprime a linha aonde foi encontrado o resultado da busca
			for (i = 0; i < linhas; i++)
			{
				if (listaValor1[i] > caso1){
					printf("%s\n", linhaToda[i]);
				}
				else{
					aux++;
				}
			}
// imprime uma mensagem caso não tenha encontrado nenhum valor
			if (aux == linhas){
				printf("Não há valores maiores\n");
			}
			break;
// se o que o usuário digitou for um decimal vai para o case 2
		case 2:
			caso2 = variavel.decimal;

			for (m = 0; m < linhas; m++)
			{
				for (i = 0; i < colunas; i++)
				{
					if (i == (escolhaAtributo-1))
					{
						fscanf(arquivo, "%f |", &listaValor2[cont]);
						cont++;
					}
					else{
						fscanf(arquivo, "%s |", lixo);
					}
				}
			}
			fseek(arquivo,0,SEEK_SET);

			for (i = 0; i < 3; i++)
			{
				fgets(lixo, 100, arquivo);
			}

			for (i = 0; i < linhas; i++)
			{
				fgets(linhaToda[i], 100, arquivo);
			}

			for (i = 0; i < linhas; i++)
			{
				if (listaValor2[i] > caso2){
					valores++;
				}
			}
			
			printf("Existe %d valor(es) para o que voce quer:\n\n", valores);


			for (i = 0; i < linhas; i++)
			{
				if (listaValor2[i] > caso2){
					printf("%s\n", linhaToda[i]);
				}
				else{
					aux++;
				}
			}
			if (aux == linhas){
				printf("Não há valores maiores\n");
			}
			break;
// se o que o usuário digitou for um caractere vai para o case 3
		case 3:
			caso3 = variavel.caractere;

			for (m = 0; m < linhas; m++)
			{
				for (i = 0; i < colunas; i++)
				{
					if (i == (escolhaAtributo-1))
					{
						fscanf(arquivo, "%c |", &listaValor3[cont]);
// se o caractere for maiúsculo, converte para minúsculo					
						if ((listaValor3[cont] >= 'A') && (listaValor3[cont] <= 'Z')){
							listaValor3[cont] += 32;
						}
						cont++;
					}
					else{
						
						fscanf(arquivo, "%s |", lixo);
					}
				}
			}
			
			fseek(arquivo,0,SEEK_SET);

			for (i = 0; i < 3; i++)
			{
				fgets(lixo, 100, arquivo);
			}

			for (i = 0; i < linhas; i++)
			{
				fgets(linhaToda[i], 100, arquivo);
			}

			for (i = 0; i < linhas; i++)
			{
				if (listaValor3[i] > caso3){
					valores++;
				}
			}
			
			printf("Existe %d valor(es) para o que voce quer:\n\n", valores);


			for (i = 0; i < linhas; i++)
			{
				if (listaValor3[i] > caso3){
					printf("%s\n", linhaToda[i]);
				}
				else{
					aux++;
				}
			}
			if (aux == linhas){
				printf("Não há valores maiores\n");
			}
			break;
// se o que o usuário digitou for um string vai para o case 4
		case 4:
			caso4 = variavel.string;
			for (m = 0; m < linhas; m++)
			{
				for (i = 0; i < colunas; i++)
				{
					if (i == (escolhaAtributo-1))
					{
						fscanf(arquivo, "%s |", listaValor4[cont]);
						cont++;
					}
					else{
						fscanf(arquivo, "%s |", lixo);
					}
				}
			}
				

			fseek(arquivo,0,SEEK_SET);

			for (i = 0; i < 3; i++)
			{
				fgets(lixo, 100, arquivo);
			}

			for (i = 0; i < linhas; i++)
			{
				fgets(linhaToda[i], 100, arquivo);
			}

			for (i = 0; i < linhas; i++)
			{
				constante = strcmp(listaValor4[i], caso4);
				if (constante>0){
					valores++;
				}
			}
			
			printf("Existe %d valor(es) para o que voce quer:\n\n", valores);


			for (i = 0; i < linhas; i++)
			{
				constante = strcmp(listaValor4[i], caso4);
				if (constante>0){
					printf("%s\n", linhaToda[i]);
				
				}
				else{
					aux++;
				}
			}
			if (aux == linhas){
				printf("Não há valores maiores\n");
			}
			break;

		
		default:
			printf("Valor inválido!\n");
			break;	
	}

}
// procura maior ou igual valor
// a função acima é similar a esta e com as seguintes funções de procurar um valor, com exceção na de buscar um valor aproxima
void procurar_maior_igual(FILE *arquivo, TIPOS variavel, int escolhat, int linhas, int colunas, int escolhaAtributo){
	int i, m, constante, valores = 0, cont = 0, aux = 0;
	unsigned long int caso1, listaValor1[linhas];
	float caso2, listaValor2[linhas];
	char caso3, listaValor3[linhas];
	char *caso4, **listaValor4;
	char **linhaToda;

	linhaToda = alocar_char(colunas *100);
	
	caso4 = (char*) malloc(linhas*colunas*sizeof(char));
	if (caso4 == NULL)
	{
		printf("erro de alocação!\n");
	}

	listaValor4 = alocar_char(linhas*colunas);
	char lixo[100];
	printf("\n");
	switch (escolhat){
		case 1:
			caso1 = variavel.inteiro;
			
			for (m = 0; m < linhas; m++)
			{
				for (i = 0; i < colunas; i++)
				{
					if (i == (escolhaAtributo-1))
					{
						fscanf(arquivo, "%lu |", &listaValor1[cont]);
						cont++;
					}
					else{
						fscanf(arquivo, "%s |", lixo);
					}
				}
			}
			
			fseek(arquivo,0,SEEK_SET);
			
			for (i = 0; i < 3; i++)
			{
				fgets(lixo, 100, arquivo);
			}

			for (i = 0; i < linhas; i++)
			{
				fgets(linhaToda[i], 100, arquivo);
			}

			for (i = 0; i < linhas; i++)
			{
				if (listaValor1[i] >= caso1){
					valores++;
				}
			}
			
			printf("Existe %d valor(es) para o que voce quer:\n\n", valores);

			
			for (i = 0; i < linhas; i++)
			{
				if (listaValor1[i] >= caso1){
					printf("%s\n", linhaToda[i]);
				}
				else{
					aux++;
				}
			}
			if (aux == linhas){
				printf("Não há valores maiores ou iguais\n");
			}
			break;

		case 2:
			caso2 = variavel.decimal;

			for (m = 0; m < linhas; m++)
			{
				for (i = 0; i < colunas; i++)
				{
					if (i == (escolhaAtributo-1))
					{
						fscanf(arquivo, "%f |", &listaValor2[cont]);
						cont++;
					}
					else{
						fscanf(arquivo, "%s |", lixo);
					}
				}
			}

			fseek(arquivo,0,SEEK_SET);
			
			for (i = 0; i < 3; i++)
			{
				fgets(lixo, 100, arquivo);
			}

			for (i = 0; i < linhas; i++)
			{
				fgets(linhaToda[i], 100, arquivo);
			}

			for (i = 0; i < linhas; i++)
			{
				if (listaValor2[i] >= caso2){
					valores++;
				}
			}
			
			printf("Existe %d valor(es) para o que voce quer:\n\n", valores);

			for (i = 0; i < linhas; i++)
			{
				if (listaValor1[i] >= caso1){
					printf("%s\n", linhaToda[i]);
				}
				else{
					aux++;
				}
			}
			if (aux == linhas){
				printf("Não há valores maiores ou iguais\n");
			}
			break;

		case 3:
			caso3 = variavel.caractere;

			for (m = 0; m < linhas; m++)
			{
				for (i = 0; i < colunas; i++)
				{
					if (i == (escolhaAtributo-1))
					{
						fscanf(arquivo, "%c |", &listaValor3[cont]);
						
						if ((listaValor3[cont] >= 'A') && (listaValor3[cont] <= 'Z')){
							listaValor3[cont] += 32;	
						}
						cont++;
					}
					else{
						fscanf(arquivo, "%s |", lixo);
					}
				}
			}
			
			fseek(arquivo,0,SEEK_SET);
			
			for (i = 0; i < 3; i++)
			{
				fgets(lixo, 100, arquivo);
			}

			for (i = 0; i < linhas; i++)
			{
				fgets(linhaToda[i], 100, arquivo);
			}

			for (i = 0; i < linhas; i++)
			{
				if (listaValor3[i] >= caso3){
					valores++;
				}
			}
			
			printf("Existe %d valor(es) para o que voce quer:\n\n", valores);

			
			for (i = 0; i < linhas; i++)
			{
				if (listaValor3[i] >= caso3){
					printf("%s\n", linhaToda[i]);
				}
				else{
					aux++;
				}
			}
			if (aux == linhas){
				printf("Não há valores maiores ou iguais\n");
			}
			break;

		case 4:
			caso4 = variavel.string;
			for (m = 0; m < linhas; m++)
			{
				for (i = 0; i < colunas; i++)
				{
					if (i == (escolhaAtributo-1))
					{
						fscanf(arquivo, "%s |", listaValor4[cont]);
						cont++;
					}
					else{
						fscanf(arquivo, "%s |", lixo);
					}
				}
			}
			
			fseek(arquivo,0,SEEK_SET);
			
			for (i = 0; i < 3; i++)
			{
				fgets(lixo, 100, arquivo);
			}

			for (i = 0; i < linhas; i++)
			{
				fgets(linhaToda[i], 100, arquivo);
			}

			for (i = 0; i < linhas; i++)
			{
				constante = strcmp(listaValor4[i], caso4);
				if (constante>=0){
					valores++;
				}
			}
			
			printf("Existe %d valor(es) para o que voce quer:\n\n", valores);
			
			for (i = 0; i < linhas; i++)
			{
				constante = strcmp(listaValor4[i], caso4);
				if (constante>=0){
					printf("%s\n", linhaToda[i]);
				}
				else{
					aux++;
				}
			}
			if (aux == linhas){
				printf("Não há valores maiores ou iguais\n");
			}
			break;
		
		default:
			printf("Valor inválido!\n");
			break;		
	}

}
// procura igual valor
void procurar_igual(FILE *arquivo, TIPOS variavel, int escolhat, int linhas, int colunas, int escolhaAtributo){
	int i, m, constante, valores = 0,cont = 0, aux = 0;
	unsigned long int caso1, listaValor1[linhas];
	float caso2, listaValor2[linhas];
	char caso3,listaValor3[linhas];
	char *caso4, **listaValor4;
	char **linhaToda;

	linhaToda = alocar_char(colunas *100);
	
	caso4 = (char*) malloc(linhas*colunas*sizeof(char));
	if (caso4 == NULL)
	{
		printf("erro de alocação!\n");
	}

	listaValor4 = alocar_char(linhas*colunas);
	char lixo[100];
	printf("\n");
	switch (escolhat){
		case 1:
			caso1 = variavel.inteiro;
			
			for (m = 0; m < linhas; m++)
			{
				for (i = 0; i < colunas; i++)
				{
					if (i == (escolhaAtributo-1))
					{
						fscanf(arquivo, "%lu |", &listaValor1[cont]);
						cont++;
						
					}
					else{
						fscanf(arquivo, "%s |", lixo);
					}
				}
			}
			fseek(arquivo,0,SEEK_SET);

			for (i = 0; i < 3; i++)
			{
				fgets(lixo, 100, arquivo);
			}

			for (i = 0; i < linhas; i++)
			{
				fgets(linhaToda[i], 100, arquivo);
			}

			for (i = 0; i < linhas; i++)
			{
				if (listaValor1[i] == caso1){
					valores++;
				}
			}
			
			printf("Existe %d valor(es) para o que voce quer:\n\n", valores);

			for (i = 0; i < linhas; i++)
			{
				if (listaValor1[i] == caso1){
					printf("%s\n", linhaToda[i]);
				}
				else{
					aux++;
				}
			}
			if (aux == linhas){
				printf("Não há valores iguais\n");
			}
			break;

		case 2:
			caso2 = variavel.decimal;

			for (m = 0; m < linhas; m++)
			{
				for (i = 0; i < colunas; i++)
				{
					if (i == (escolhaAtributo-1))
					{
						fscanf(arquivo, "%f |", &listaValor2[cont]);
						cont++;	
					}
					else{
						fscanf(arquivo, "%s |", lixo);
					}
				}
			}

			fseek(arquivo,0,SEEK_SET);

			for (i = 0; i < 3; i++)
			{
				fgets(lixo, 100, arquivo);
			}

			for (i = 0; i < linhas; i++)
			{
				fgets(linhaToda[i], 100, arquivo);
			}

			for (i = 0; i < linhas; i++)
			{
				if (listaValor2[i] == caso2){
					valores++;
				}
			}
			
			printf("Existe %d valor(es) para o que voce quer:\n\n", valores);

			for (i = 0; i < linhas; i++)
			{
				if (listaValor2[i] == caso2){
					printf("%s\n", linhaToda[i]);
				}
				else{
					aux++;
				}
			}
			if (aux == linhas){
				printf("Não há valores iguais\n");
			}
			break;

		case 3:
			caso3 = variavel.caractere;

			for (m = 0; m < linhas; m++)
			{
				for (i = 0; i < colunas; i++)
				{
					if (i == (escolhaAtributo-1))
					{
						fscanf(arquivo, "%c |", &listaValor3[cont]);
						
						if ((listaValor3[cont] >= 'A') && (listaValor3[cont] <= 'Z')){
							listaValor3[cont] += 32;
						}
						cont++;
					}
					else{
						fscanf(arquivo, "%s |", lixo);
					}
				}
			}
			
			fseek(arquivo,0,SEEK_SET);

			for (i = 0; i < 3; i++)
			{
				fgets(lixo, 100, arquivo);
			}

			for (i = 0; i < linhas; i++)
			{
				fgets(linhaToda[i], 100, arquivo);
			}

			for (i = 0; i < linhas; i++)
			{
				if (listaValor3[i] == caso3){
					valores++;
				}
			}
			
			printf("Existe %d valor(es) para o que voce quer:\n\n", valores);

			for (i = 0; i < linhas; i++)
			{
				if (listaValor3[i] == caso3){
					printf("%s\n", linhaToda[i]);
				}
				else{
					aux++;
				}
			}
			if (aux == linhas){
				printf("Não há valores iguais\n");
			}
			break;

		case 4:
			caso4 = variavel.string;
			for (m = 0; m < linhas; m++)
			{
				for (i = 0; i < colunas; i++)
				{
					if (i == (escolhaAtributo-1))
					{
						fscanf(arquivo, "%s |", listaValor4[cont]);
						cont++;
					}
					else{
						fscanf(arquivo, "%s |", lixo);
					}
				}
			}
			
			fseek(arquivo,0,SEEK_SET);

			for (i = 0; i < 3; i++)
			{
				fgets(lixo, 100, arquivo);
			}

			for (i = 0; i < linhas; i++)
			{
				fgets(linhaToda[i], 100, arquivo);
			}

			for (i = 0; i < linhas; i++)
			{
				constante = strcmp(listaValor4[i], caso4);
				if (constante==0){
					valores++;
				}
			}
			
			printf("Existe %d valor(es) para o que voce quer:\n\n", valores);

			for (i = 0; i < linhas; i++)
			{
				constante = strcmp(listaValor4[i], caso4);
				if (constante==0){
					printf("%s\n", linhaToda[i]);
				}
				else{
					aux++;
				}
			}
			if (aux == linhas){
				printf("Não há valores iguais\n");
			}
			break;

		default:
			printf("Valor inválido!\n");
			break;
		
	}

}
// procura menor valor
void procurar_menor(FILE *arquivo, TIPOS variavel, int escolhat, int linhas, int colunas, int escolhaAtributo){
	int i, m, constante, valores = 0, cont = 0, aux = 0;
	unsigned long int caso1, listaValor1[linhas];
	float caso2, listaValor2[linhas];
	char caso3,listaValor3[linhas];
	char *caso4, **listaValor4;
	char **linhaToda;

	linhaToda = alocar_char(colunas *100);
	
	caso4 = (char*) malloc(linhas*colunas*sizeof(char));
	
	if (caso4 == NULL)
	{
		printf("erro de alocação!\n");
	}

	listaValor4 = alocar_char(linhas*colunas);
	char lixo[100];
	printf("\n");
	switch (escolhat){
		case 1:
			caso1 = variavel.inteiro;
			
			for (m = 0; m < linhas; m++)
			{
				for (i = 0; i < colunas; i++)
				{
					if (i == (escolhaAtributo-1))
					{
						fscanf(arquivo, "%lu |", &listaValor1[cont]);
						cont++;
					}
					else{
						fscanf(arquivo, "%s |", lixo);
					}
				}
			}
			fseek(arquivo,0,SEEK_SET);

			for (i = 0; i < 3; i++)
			{
				fgets(lixo, 100, arquivo);
			}

			for (i = 0; i < linhas; i++)
			{
				fgets(linhaToda[i], 100, arquivo);
			}

			for (i = 0; i < linhas; i++)
			{
				if (listaValor1[i] < caso1){
					valores++;
				}
			}
			
			printf("Existe %d valor(es) para o que voce quer:\n\n", valores);

			for (i = 0; i < linhas; i++)
			{
				if (listaValor1[i] < caso1){
					printf("%s\n", linhaToda[i]);
				}
				else{
					aux++;
				}
			}
			if (aux == linhas){
				printf("Não há valores menores\n");
			}
			break;

		case 2:
			caso2 = variavel.decimal;

			for (m = 0; m < linhas; m++)
			{
				for (i = 0; i < colunas; i++)
				{
					if (i == (escolhaAtributo-1))
					{
						fscanf(arquivo, "%f |", &listaValor2[cont]);
						cont++;
					}
					else{
						fscanf(arquivo, "%s |", lixo);
					}
				}
			}
			fseek(arquivo,0,SEEK_SET);

			for (i = 0; i < 3; i++)
			{
				fgets(lixo, 100, arquivo);
			}

			for (i = 0; i < linhas; i++)
			{
				fgets(linhaToda[i], 100, arquivo);
			}

			for (i = 0; i < linhas; i++)
			{
				if (listaValor2[i] < caso2){
					valores++;
				}
			}
			
			printf("Existe %d valor(es) para o que voce quer:\n\n", valores);

			for (i = 0; i < linhas; i++)
			{
				if (listaValor2[i] < caso2){
					printf("%s\n", linhaToda[i]);
				}
				else{
					aux++;
				}
			}
			if (aux == linhas){
				printf("Não há valores menores\n");
			}
			break;

		case 3:
			caso3 = variavel.caractere;

			for (m = 0; m < linhas; m++)
			{
				for (i = 0; i < colunas; i++)
				{
					if (i == (escolhaAtributo-1))
					{
						fscanf(arquivo, "%c |", &listaValor3[cont]);
						if ((listaValor3[cont] >= 'A') && (listaValor3[cont] <= 'Z')){
							listaValor3[cont] += 32;	
						}
						cont++;	
					}
					else{
						
						fscanf(arquivo, "%s |", lixo);
					}
				}
			}
			fseek(arquivo,0,SEEK_SET);

			for (i = 0; i < 3; i++)
			{
				fgets(lixo, 100, arquivo);
			}

			for (i = 0; i < linhas; i++)
			{
				fgets(linhaToda[i], 100, arquivo);
			}

			for (i = 0; i < linhas; i++)
			{
				if (listaValor3[i] < caso3){
					valores++;
				}
			}
			
			printf("Existe %d valor(es) para o que voce quer:\n\n", valores);

			for (i = 0; i < linhas; i++)
			{
				if (listaValor3[i] < caso3){
					printf("%s\n", linhaToda[i]);
				}
				else{
					aux++;
				}
			}
			if (aux == linhas){
				printf("Não há valores menores\n");
			}
			break;

		case 4:
			caso4 = variavel.string;
			for (m = 0; m < linhas; m++)
			{
				for (i = 0; i < colunas; i++)
				{
					if (i == (escolhaAtributo-1))
					{
						fscanf(arquivo, "%s |", listaValor4[cont]);
						cont++;
					}
					else{
						fscanf(arquivo, "%s |", lixo);
					}
				}
			}
				
			fseek(arquivo,0,SEEK_SET);

			for (i = 0; i < 3; i++)
			{
				fgets(lixo, 100, arquivo);
			}

			for (i = 0; i < linhas; i++)
			{
				fgets(linhaToda[i], 100, arquivo);
			}

			for (i = 0; i < linhas; i++)
			{
				constante = strcmp(listaValor4[i], caso4);
				if (constante<0){
					valores++;
				}
			}
			
			printf("Existe %d valor(es) para o que voce quer:\n\n", valores);

			for (i = 0; i < linhas; i++)
			{
				constante = strcmp(listaValor4[i], caso4);
				if (constante<0){
					printf("%s\n", linhaToda[i]);
				}
				else{
					aux++;
				}
			}
			if (aux == linhas){
				printf("Não há valores menores\n");
			}
			break;
		default:
			printf("Valor inválido!\n");
			break;
	}

}
// procura menor ou igual valor
void procurar_menor_igual(FILE *arquivo, TIPOS variavel, int escolhat, int linhas, int colunas, int escolhaAtributo){
	int i, m, constante, valores = 0, cont = 0, aux = 0;
	unsigned long int caso1, listaValor1[linhas];
	float caso2, listaValor2[linhas];
	char caso3,listaValor3[linhas];
	char *caso4, **listaValor4;
	char **linhaToda;

	linhaToda = alocar_char(colunas *100);
	
	caso4 = (char*) malloc(linhas*colunas*sizeof(char));
	if (caso4 == NULL)
	{
		printf("erro de alocação!\n");
	}

	listaValor4 = alocar_char(linhas*colunas);
	char lixo[100];
	printf("\n");
	switch (escolhat){
		case 1:
			caso1 = variavel.inteiro;
			
			for (m = 0; m < linhas; m++)
			{
				for (i = 0; i < colunas; i++)
				{
					if (i == (escolhaAtributo-1))
					{
						fscanf(arquivo, "%lu |", &listaValor1[cont]);
						cont++;
					}
					else{
						fscanf(arquivo, "%s |", lixo);
					}
				}
			}
			
			fseek(arquivo,0,SEEK_SET);

			for (i = 0; i < 3; i++)
			{
				fgets(lixo, 100, arquivo);
			}

			for (i = 0; i < linhas; i++)
			{
				fgets(linhaToda[i], 100, arquivo);
			}

			for (i = 0; i < linhas; i++)
			{
				if (listaValor1[i] <= caso1){
					valores++;
				}
			}
			
			printf("Existe %d valor(es) para o que voce quer:\n\n", valores);

			for (i = 0; i < linhas; i++)
			{
				if (listaValor1[i] <= caso1){
					printf("%s\n", linhaToda[i]);
				}
				else{
					aux++;
				}
			}
			if (aux == linhas){
				printf("Não há valores menores ou iguais\n");
			}
			break;

		case 2:
			caso2 = variavel.decimal;

			for (m = 0; m < linhas; m++)
			{
				for (i = 0; i < colunas; i++)
				{
					if (i == (escolhaAtributo-1))
					{
						fscanf(arquivo, "%f |", &listaValor2[cont]);
						cont++;
					}
					else{
						fscanf(arquivo, "%s |", lixo);
					}
				}
			}
			fseek(arquivo,0,SEEK_SET);

			for (i = 0; i < 3; i++)
			{
				fgets(lixo, 100, arquivo);
			}

			for (i = 0; i < linhas; i++)
			{
				fgets(linhaToda[i], 100, arquivo);
			}

			for (i = 0; i < linhas; i++)
			{
				if (listaValor2[i] <= caso2){
					valores++;
				}
			}
			
			printf("Existe %d valor(es) para o que voce quer:\n\n", valores);

			for (i = 0; i < linhas; i++)
			{
				if (listaValor2[i] <= caso2){
					printf("%s\n", linhaToda[i]);
				}
				else{
					aux++;
				}
			}
			if (aux == linhas){
				printf("Não há valores menores ou iguais\n");
			}
			break;

		case 3:
			caso3 = variavel.caractere;

			for (m = 0; m < linhas; m++)
			{
				for (i = 0; i < colunas; i++)
				{
					if (i == (escolhaAtributo-1))
					{
						fscanf(arquivo, "%c |", &listaValor3[cont]);
						
						if ((listaValor3[cont] >= 'A') && (listaValor3[cont] <= 'Z')){
							listaValor3[cont] += 32;		
						}
						cont++;
					}
					else{
						
						fscanf(arquivo, "%s |", lixo);
					}
				}
			}
			
			fseek(arquivo,0,SEEK_SET);

			for (i = 0; i < 3; i++)
			{
				fgets(lixo, 100, arquivo);
			}

			for (i = 0; i < linhas; i++)
			{
				fgets(linhaToda[i], 100, arquivo);
			}

			for (i = 0; i < linhas; i++)
			{
				if (listaValor3[i] <= caso3){
					valores++;
				}
			}
			
			printf("Existe %d valor(es) para o que voce quer:\n\n", valores);

			for (i = 0; i < linhas; i++)
			{
				if (listaValor3[i] <= caso3){
					printf("%s\n", linhaToda[i]);
				}
				else{
					aux++;
				}
			}
			if (aux == linhas){
				printf("Não há valores menores ou iguais\n");
			}
			break;

		case 4:
			caso4 = variavel.string;
			for (m = 0; m < linhas; m++)
			{
				for (i = 0; i < colunas; i++)
				{
					if (i == (escolhaAtributo-1))
					{
						fscanf(arquivo, "%s |", listaValor4[cont]);
						cont++;
					}
						else{
						fscanf(arquivo, "%s |", lixo);
					}
				}
			}
				
			for (i = 0; i < linhas; i++)
			{
				constante = strcmp(listaValor4[i], caso4);
				if (constante<=0){
					printf("%s\n", listaValor4[i]);
				}
				else{
					aux++;
				}
			}
			if (aux == linhas){
				printf("Não há valores menores ou iguais\n");
			}
			break;

			fseek(arquivo,0,SEEK_SET);

			for (i = 0; i < 3; i++)
			{
				fgets(lixo, 100, arquivo);
			}

			for (i = 0; i < linhas; i++)
			{
				fgets(linhaToda[i], 100, arquivo);
			}

			for (i = 0; i < linhas; i++)
			{
				constante = strcmp(listaValor4[i], caso4);
				if (constante<=0){
					valores++;
				}
			}
			
			printf("Existe %d valor(es) para o que voce quer:\n\n", valores);

			for (i = 0; i < linhas; i++)
			{
				constante = strcmp(listaValor4[i], caso4);
				if (constante<=0){
					printf("%s\n", linhaToda[i]);
				}
				else{
					aux++;
				}
			}
			if (aux == linhas){
				printf("Não há valores menores ou iguais\n");
			}
			break;

		default:
			printf("Valor inválido!\n");
			break;
	}
}
// procura valor aproximado
void procurar_aproximado(FILE *arquivo, TIPOS variavel, int escolhat, int linhas, int colunas, int escolhaAtributo){
	int i, m, constante, valores = 0, cont = 0, aux = 0;
	int tam[linhas], tam_palavra, iguais = 0, verificar = 0;
	char *caso4, **listaValor4, **listaParecidos;
	char **linhaToda;

	// se o que o usuário digitar não for uma string		
	if (escolhat != 4)
	{
		printf("Essa coluna não é string\n");
		return;
	}

	linhaToda = alocar_char(colunas *100);

	caso4 = (char*) malloc(linhas*colunas*sizeof(char));
	if (caso4 == NULL)
	{
		printf("erro de alocação!\n");
	}

	listaValor4 = alocar_char(linhas*colunas);
	char lixo[100];
	printf("\n");
	if (escolhat == 4){
		caso4 = variavel.string;
		for (m = 0; m < linhas; m++)
		{
			for (i = 0; i < colunas; i++)
			{
				if (i == (escolhaAtributo-1))
				{
					fscanf(arquivo, "%s |", listaValor4[cont]);
					cont++;
				}
					else{
					fscanf(arquivo, "%s |", lixo);
				}
			}
		}
	}

	fseek(arquivo,0,SEEK_SET);
	for (i = 0; i < 3; i++)
	{
		fgets(lixo,100,arquivo);
	}
	for (i = 0; i < linhas; i++)
	{
		fgets(linhaToda[i], 100, arquivo);
	}
// pega o tamanho da palavra que o usuário digitou
	tam_palavra = strlen(caso4);
// faz uma lista com os nomes parecidos
	listaParecidos = alocar_char(colunas*100);
		
	for (i = 0; i < linhas; i++)
	{
//lista com o tamanho de cada palavra da coluna que vai fazer a pesquisa
		tam[i] = strlen(listaValor4[i]);	
	}
	for (m = 0; m < linhas; m++)
	{
		for (i = 0; i < tam_palavra; i++)
		{
// pega o que o usuário digitou e a palavra da coluna que o programa está comprarando, e verifica a posição dos caracteres das duas palavras
// se o mesmo caractere estiver igual na mesma posição, vai adicionar na variável iguais
			if(caso4[i] == listaValor4[m][i]){
				iguais++;	
			}						
		}
//se a quantidade de palavras que estão na mesma posição for maior ou igual que metade do tamanho da palavra que o usuário digitou, então ele vai imprimir a linha da palavra
		if(iguais >= (tam_palavra)){
			strcpy(listaParecidos[verificar], linhaToda[m]);
			verificar++;
		}
	
		iguais = 0;
	}

	printf("Existe %d valor(es) para o que voce quer:\n\n", verificar);
		
	for (i = 0; i < verificar; ++i)
	{
		printf("%s", listaParecidos[i]);	
	}
// se não achar nenhum valor aproximimado ele imprime uma mensagem
	if (verificar == 0){
		printf("Não há valores aproximados\n");
	}
}

//sexto ponto.

void apagar_linhaTabela(){

//key recebe o valor das chavesprimarias que não serão apagadas e chaveP é a chave cuja linha será apagada.
//todosArquivos é o arquivo da tabela que será apagada a linha, e novoArquivo é o arquivo que futuramente será a nova tabela (tabela sem a linha que foi apagada).
//indices vai receber o que tem no arquivo que não faz parte de alguma linha.
//nova é o nome do arquivo novo que futuramente será mudado para o nome da tabela.	
	int i,j,controle;
	unsigned long int key,chaveP;
	j=0;
	char nomeTabela[100];
	char linha[100];
	FILE * todosArquivos;
	FILE * novoArquivo;
	char indices[100];
	char * nova;

	nova = "transição.TXT";

	printf("Qual o nome da tabela?\n");
	fgets(nomeTabela,100,stdin);

	controle = lendoTabelas(nomeTabela);

	if (controle == 0)
	{
		printf("essa tabela não existe\n");
		return;
	}

	printf("Qual a chave primária da linha?\n");
	scanf("%lu", &chaveP);
	getchar();

	strcat(nomeTabela,".TXT");

	todosArquivos = fopen(nomeTabela, "r");
	novoArquivo = fopen(nova, "w");
	
	if (todosArquivos == NULL)
	{
		printf("erro na abertura do arquivo\n");
		return;
	}

	if (novoArquivo == NULL)
	{
		printf("erro na abertura do arquivo\n");
		return;
	}

	while(!feof(todosArquivos)){
		j++;
		fgets(linha, 100,todosArquivos);
	}

	fseek(todosArquivos, 0, SEEK_SET);

	for (i = 0; i < 3; i++)
	{
		fgets(indices, 100, todosArquivos);
		fprintf(novoArquivo, "%s", indices);

	}
	
	for (i = 0; i < j-4; i++)
	{
		fscanf(todosArquivos, "%lu |", &key);
		fgets(linha, 100, todosArquivos);
	
		if (key != chaveP)
		{
			fprintf(novoArquivo,"%lu |", key);
			fprintf(novoArquivo, "%s", linha);
		}
	}
	remove(nomeTabela);
	rename(nova, nomeTabela);
	fclose(novoArquivo);
	return;
}

//sétimo ponto.

void apagar_tabela(){

//funciona parecido com o anterior mas ao invés de apagar só a linha da tabela, apaga toda a tabela, e a linha do nome da tabela correspondente do arquivo que tem os nomes de todos as tabelas. 

	int i,j,controle;
	j=0;
	char nomeTabela[100];
	char linha[100];
	char * ptr_palavra;
	char **listaTabelas;
	FILE * todosArquivos;
	FILE * novoArquivo;
	char * tabela;
	char * nova;

	listaTabelas = alocar_char(1000);

	tabela = "tabelas.TXT";
	nova = "transição.TXT";

	printf("Qual o nome da tabela que deseja apagar?\n");
	fgets(nomeTabela,100,stdin);

	controle = lendoTabelas(nomeTabela);

	if (controle == 0)
	{
		printf("essa tabela não existe\n");
		return;
	}

	todosArquivos = fopen(tabela, "r");
	novoArquivo = fopen(nova, "w");
	
	if (todosArquivos == NULL)
	{
		printf("erro na abertura do arquivo\n");
		return;
	}

	while(!feof(todosArquivos)){
		j++;
		fgets(linha, 100,todosArquivos);
	}

	fseek(todosArquivos, 0, SEEK_SET);

	for (i = 0; i < j-1; i++)
	{
		fgets(linha, 100,todosArquivos);

		ptr_palavra = strpbrk (linha, " ");

		if (strcmp(ptr_palavra+1, nomeTabela) != 0)
		{
			fprintf(novoArquivo, "Nome: %s", ptr_palavra+1);
		}
	}

	strcat(nomeTabela,".TXT");

	remove(nomeTabela);
	remove(tabela);
	rename(nova, tabela);

	fclose(novoArquivo);

	return;
}

//extra.

void criar_novaColuna()
{
	//criar uma coluna em uma tabela que já existe.

	int col,j,i,tipo,controle;
	j=0;
	char nomeTabela[100];
	char linha[100];
	FILE * todosArquivos;
	FILE * novoArquivo;
	char atributo[100];
	char * nova;

	nova = "transição.TXT";

	printf("Qual o nome da tabela?\n");
	fgets(nomeTabela,100,stdin);

	controle = lendoTabelas(nomeTabela);

	if (controle == 0)
	{
		printf("essa tabela não existe\n");
		return;
	}

	strcat(nomeTabela,".TXT");

	todosArquivos = fopen(nomeTabela, "r");
	novoArquivo = fopen(nova, "w");
	
	if (todosArquivos == NULL)
	{
		printf("erro na abertura do arquivo\n");
		return;
	}

	if (novoArquivo == NULL)
	{
		printf("erro na abertura do arquivo\n");
		return;
	}

	while(!feof(todosArquivos)){
		fgets(linha, 100,todosArquivos);
		j++;
	}

	fseek(todosArquivos, 0, SEEK_SET);

//acrescentando a quantidade

	fscanf(todosArquivos,"colunas:%d,", &col);
	col = col+1;		
	fprintf(novoArquivo, "colunas:%d,", col);
	fprintf(novoArquivo, "\n");
//acrescentando o nome
	for (i = 0; i < col-1; i++)
	{
		fscanf(todosArquivos,"%s |", atributo);
		fprintf(novoArquivo, "%s |", atributo);
	}

	printf("qual será o nome da coluna?\n");
	scanf("%s", atributo);

	fprintf(novoArquivo, "%s |\n", atributo);

	for (i = 0; i < col-1; i++)
	{
		fscanf(todosArquivos, "%d,", &tipo);
		fprintf(novoArquivo, "%d,", tipo);	
	}

	printf("\nTipos dos atributos:\ndigite 1 para inteiro\ndigite 2 para double\ndigite 3 para char\ndigite 4 para string\n");
	printf("qual o tipo desse novo atributo?\n");
	scanf("%d", &tipo);

	fprintf(novoArquivo, "%d,|", tipo);
	fprintf(novoArquivo, "\n");
//pegando lixo
	fgets(atributo, 100, todosArquivos);
	
	for (i = 0; i < j-4; i++)
	{
		fgets(atributo, 100, todosArquivos);
		printf("%s\n", atributo);
		fprintf(novoArquivo, "%s", atributo);
		fseek(novoArquivo, -1, SEEK_CUR);
		fprintf(novoArquivo, "0 |");
		fprintf(novoArquivo, "\n");
	}

	remove(nomeTabela);
	rename(nova, nomeTabela);
	fclose(novoArquivo);

	return;
}

void apagar_coluna(){
	
	//apagar uma coluna que existe em uma tabela.

	int col,j,i,k,tipo,controle,coluna;
	j=0;
	char nomeTabela[100];
	char linha[100];
	FILE * todosArquivos;
	FILE * novoArquivo;
	char atributo[100];
	char * nova;

	nova = "transição.TXT";

	printf("Qual o nome da tabela?\n");
	fgets(nomeTabela,100,stdin);

	controle = lendoTabelas(nomeTabela);

	if (controle == 0)
	{
		printf("essa tabela não existe\n");
		return;
	}

	strcat(nomeTabela,".TXT");

	todosArquivos = fopen(nomeTabela, "r");
	novoArquivo = fopen(nova, "w");
	
	if (todosArquivos == NULL)
	{
		printf("erro na abertura do arquivo\n");
		return;
	}

	if (novoArquivo == NULL)
	{
		printf("erro na abertura do arquivo\n");
		return;
	}

	while(!feof(todosArquivos)){
		fgets(linha, 100,todosArquivos);
		j++;
	}

	fseek(todosArquivos, 0, SEEK_SET);

//acrescentando a quantidade

	fscanf(todosArquivos,"colunas:%d,", &col);
	col = col-1;		
	fprintf(novoArquivo, "colunas:%d,", col);
	fprintf(novoArquivo, "\n");
//acrescentando o nome
	printf("A primeira coluna é a chave primária que não pode ser apagada\n");
	printf("Existem essas colunas:\n");
	for (i = 0; i < col+1; i++)
	{
		fscanf(todosArquivos,"%s |", atributo);
		if (i == 0)
		{
			//faz nada
		}
		else{
			printf("%d-%s\n", i+1, atributo);			
		}
	}
	fseek(todosArquivos, 0, SEEK_SET);
	fgets(atributo, 100, todosArquivos);
	printf("qual o número da coluna que deseja apagar?\n");
	scanf("%d", &coluna);

	for (i = 0; i < col+1; i++)
	{
		fscanf(todosArquivos,"%s |", atributo);
		if (i == coluna-1)
		{
			//faz nada;
		}
		else{
			fprintf(novoArquivo, "%s |", atributo);
		}
	}

	fprintf(novoArquivo,"\n");

	for (i = 0; i < col+1; i++)
	{
		fscanf(todosArquivos, "%d,", &tipo);
		if (i == coluna-1)
		{
			//faz nada;
		}
		else{
			fprintf(novoArquivo, "%d,", tipo);
		}	
	}

	fprintf(novoArquivo, "|");
	fprintf(novoArquivo, "\n");
//pegando lixo
	fgets(atributo, 100, todosArquivos);
//imprimindo na tabela as linhas sem o atributo excluído
	for (i = 0; i < j-4; i++)
	{
		for (k = 0; k < col+1; k++)
		{
			fscanf(todosArquivos,"%s |", atributo);
			if (k == coluna-1)
			{
				//faz nada;
			}
			else{
				fprintf(novoArquivo, "%s |", atributo);
			}
		}
		fprintf(novoArquivo, "\n");
	}

	remove(nomeTabela);
	rename(nova, nomeTabela);
	fclose(novoArquivo);

	return;
}

void alterar_valor()
{
	//key é a chave que o usuário informar, chaveP são as chaves que tem no arquivo, coluna é o número correspondente a coluna que vai ser alterada 

	int col,j,i,k,tipo,controle,coluna;
	unsigned long int key,chaveP;
	j=0;
	char nomeTabela[100];
	char linha[100];
	char alterada[100];
	FILE * todosArquivos;
	FILE * novoArquivo;
	char atributo[100];
	char * nova;

	nova = "transição.TXT";

	printf("Qual o nome da tabela?\n");
	fgets(nomeTabela,100,stdin);

	controle = lendoTabelas(nomeTabela);

	if (controle == 0)
	{
		printf("essa tabela não existe\n");
		return;
	}

	strcat(nomeTabela,".TXT");

	todosArquivos = fopen(nomeTabela, "r");
	novoArquivo = fopen(nova, "w");
	
	if (todosArquivos == NULL)
	{
		printf("erro na abertura do arquivo\n");
		return;
	}

	if (novoArquivo == NULL)
	{
		printf("erro na abertura do arquivo\n");
		return;
	}

	while(!feof(todosArquivos)){
		fgets(linha, 100,todosArquivos);
		j++;
	}

	fseek(todosArquivos, 0, SEEK_SET);

//acrescentando a quantidade

	fscanf(todosArquivos,"colunas:%d,", &col);		
	fprintf(novoArquivo, "colunas:%d,", col);
	fprintf(novoArquivo, "\n");

	printf("A primeira coluna é a da chave primária que não pode ser alterada.\n");
	printf("Existem essas colunas:\n");
	
	for (i = 0; i < col; i++)
	{
		fscanf(todosArquivos,"%s |", atributo);
		if (i == 0)
		{
			//faz nada
		}
		else{
			printf("%d-%s\n", i+1, atributo);			
		}
	}

	fseek(todosArquivos, 0, SEEK_SET);
	fgets(atributo, 100, todosArquivos);
	printf("qual o número da coluna que deseja alterar na linha?\n");
	scanf("%d", &coluna);
	getchar();
//imprimindo no arquivo
	for (i = 0; i < col; i++)
	{
		fscanf(todosArquivos,"%s |", atributo);
		fprintf(novoArquivo, "%s |", atributo);
	}

	fprintf(novoArquivo, "\n");

	for (i = 0; i < col; i++)
	{
		fscanf(todosArquivos, "%d,", &tipo);
		fprintf(novoArquivo, "%d,", tipo);	
	}
	fprintf(novoArquivo, "|");
	fprintf(novoArquivo, "\n");
//pegando lixo
	fgets(atributo, 100, todosArquivos);

	printf("Por gentileza para confirmar.\n");

	listar_dadosTabela();	

	printf("Digite a chave primária da linha que você quer alterar:\n");
	scanf("%lu", &key);
	getchar();
	printf("Digite qual novo valor ou informação:\n");
	scanf("%s", alterada);
	
	for (i = 0; i < j-4; i++)
	{
		fscanf(todosArquivos, "%lu |", &chaveP);
		fprintf(novoArquivo,"%lu |", chaveP);
		for (k = 0; k < col-1; k++)
		{
			fscanf(todosArquivos, "%s |", atributo);
			if (chaveP == key && k == coluna-2)
			{
				fprintf(novoArquivo, "%s", alterada);
				fprintf(novoArquivo, " |");
			}
			else{
				fprintf(novoArquivo, "%s |", atributo);
			}
		}
		fprintf(novoArquivo, "\n");
	}

	remove(nomeTabela);
	rename(nova, nomeTabela);
	fclose(novoArquivo);

	return;
}

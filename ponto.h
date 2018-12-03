#ifndef ponto_h

#define ponto_h
#include<locale.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct tipos{
	unsigned long int inteiro;
	float decimal;
	char caractere;
	char string[100];
}TIPOS;

void criar_tabela();
void listar_tabela();
void criar_novaLinha();
void listar_dadosTabela();
void apagar_linhaTabela();
void apagar_tabela();
void procurar_valor();
void criar_novaColuna();
void apagar_coluna();
void alterar_valor();
int lendoTabelas(char nomeArquivo[100]);
int *alocar_int(int colunas);
char **alocar_char(int colunas);
void receber_quantColuna(int colunas, FILE * arquivo);
void criandoTabela(char nomeArquivo[100]);
void receber_atributos(char **listAtributos, int colunas, FILE *arquivo);
void declarar_tipo(int *ponteiroTipo, int colunas, FILE * arquivo);
int verificar_chave(char **listaAtributos, unsigned long int *chaveP);
void procurar_maior(FILE *arquivo, TIPOS variavel, int escolhat, int linhas, int colunas, int escolhaAtributo);
void procurar_maior_igual(FILE *arquivo, TIPOS variavel, int escolhat, int linhas, int colunas, int escolhaAtributo);
void procurar_igual(FILE *arquivo, TIPOS variavel, int escolhat, int linhas, int colunas, int escolhaAtributo);
void procurar_menor(FILE *arquivo, TIPOS variavel, int escolhat, int linhas, int colunas, int escolhaAtributo);
void procurar_menor_igual(FILE *arquivo, TIPOS variavel, int escolhat, int linhas, int colunas, int escolhaAtributo);
void procurar_aproximado(FILE *arquivo, TIPOS variavel, int escolhat, int linhas, int colunas, int escolhaAtributo);
#endif

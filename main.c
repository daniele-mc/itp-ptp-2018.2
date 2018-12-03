#include "ponto.h"

int main()
{
   setlocale(LC_ALL, "");

	int escolha;

	char continuidade;

	printf("O que você quer fazer?\n");

	
	do{	
		printf("-digite 1 para criar tabela\n-digite 2 para listar tabelas\n-digite 3 para criar nova linha na tabela\n-digite 4 para listar todos os dados de uma tabela\n-digite 5 para procurar um valor na tabela\n-digite 6 para apagar a linha de uma tabela\n-digite 7 para apagar uma tabela\n-digite 8 para criar uma nova coluna em uma tabela já existente\n-digite 9 para apagar uma coluna de uma tabela\n-digite 10 para alterar um valor da tabela\n");
		scanf("%d", &escolha);
		switch (escolha)
			{
   				case 1:
     				   criar_tabela();
   					break;

   				case 2:
 	    			   listar_tabela();
   					break;

   				case 3:
   					getchar();
                  listar_tabela();
                  criar_novaLinha();
   					break;

   				case 4:
   					getchar();
   					listar_dadosTabela();
   					break;

   				case 5:
                  getchar();
                  printf("existem essas tabelas:\n");
                  listar_tabela();
                  procurar_valor();
   					break;

   				case 6:
   					getchar();
   					apagar_linhaTabela();
   					break;

   				case 7:
   					getchar();
   					apagar_tabela();
   					break;

			       case 8:
				  getchar();
				  criar_novaColuna();
				  break;

			       case 9:
				  getchar();
				  apagar_coluna();
				  break;

			       case 10:
				  getchar();
				  alterar_valor();
				  break;

			       default:
   					printf("valor invalido\n");
   					break;
				}
		printf("Quer continuar? (s/n)\n");
		scanf(" %c", &continuidade);
	}while(continuidade == 's');
	return 0;
}

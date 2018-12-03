----------------------------------------------------------------------------------------------------------------------------
SGBD-PROJETO-ITP
----------------------------------------------------------------------------------------------------------------------------


O projeto consiste em implementar um Sistema de Gerenciamento de Banco de Dados (SGBD), porém o SGBD é simplificado e baseado no modelo relacional. Nesse sentido, o objetivo do projeto não é necessariamente para ser usado em produção por sistemas de informação, mas para explorar os conceitos abordados nas disciplinas ITP/PTP.

----------------------------------------------------------------------------------------------------------------------------
O QUE FOI FEITO
----------------------------------------------------------------------------------------------------------------------------

O projeto foi desenvolvido em modularização, possuindo 3 arquivos para o funcionamento do código: 

O arquivo main.c como arquivo principal;
O arquivo ponto.c composto pelas funções;
O arquivo ponto.h constituído pelas assinaturas das funções, da inclusão de bibliotecas e pela declaração de structs.

Além disso, ao rodar o programa, contém um menu na qual oferece 10 opções, sendo 3 extras: 

1- Criar uma tabela.
2- Listar todas as tabelas.
3- Criar uma nova linha na tabela.
4- Listar todos os dados de uma tabela.
5- Pesquisar valor em uma tabela.
6- Apagar apagar a linha de uma tabela.
7- Apagar uma tabela. 
8- Criar uma nova coluna em uma tabela já existente.
9- Apagar uma coluna de uma tabela.
10- Alterar um valor da tabela.


Na 1ª opção, o programa irá propiciar ao usuário a criação da sua própria tabela, a qual gerará um aquivo com o nome da tabela, o número de colunas, os atributos, e os tipos dos atributos (conforme informado no programa, sendo, 1 para inteiro, 2 para float/double, 3 para char e 4 para string), tudo conforme o usuário.

Para criar uma tabela foi utilizado o uso de várias funções: verificar se existe uma tabela de mesmo nome, alocação de memória, receber a quantidade de colunas, atributos e tipos de cada atributo.

Na criação da tabela, o programa também irá gerar outro arquivo (tabelas.TXT), contendo os nomes das tabelas que foram criadas. 

Na 2ª opção, o programa irá ler o arquivo tabelas.TXT e imprimir todas as tabelas existentes.

Na 3ª opção, o usuário pode adicionar as informações (uma nova linha), basta informar o nome da tabela e logo em seguida já irá pedir os valores de cada atributo da nova linha.

Na 4ª opção, o programa irá informar o que está contido na tabela, o usuário deve colocar o nome da tabela e em seguida já aparecerá as informações. 

Na 5ª opção, o programa irá informar o nome das tabelas existentes e o usuário deve digitar o nome da tabela que deseja. Depois o usuário deve informar um número que vai corresponder com a coluna na qual deseja realizar a pesquisa e em seguida deve digitar um número, uma letra ou uma palavra para realizar a pesquisa (com exceção na busca de valor aproximado, na qual não faz busca com números). Então o programa irá fornecer uma lista de opções de busca e o usuário digita um número que corresponda com a opção de busca que deseja.

Na 6ª opção, o usuário pode apagar a linha de uma tabela, ele deve digitar o nome da tabela, e então informar o número correspondente a chave primária.

Na 7ª opção, o usuário deve digitar o nome de uma tabela que foi criada para apagar.

Na 8ª opção, para criar uma nova coluna, o usuário deve informar o nome de uma tabela existente, e então digitar um nome para a nova coluna e qual será o seu tipo.

Na 9ª opção, o usuário deverá informar o nome de uma tabela existente, e em seguida, deve ser digitado um número, que corresponda com as opções informadas pelo programa para escolher uma coluna para apagar.

Na 10ª opção, para alterar o valor de uma informação da tabela, o usuário primeiramente deve digitar o nome da tabela, em seguida digitar um número que corresponde com qual coluna deseja alterar, e logo depois informar de novo o nome da tabela. O usuário deve em seguida digitar um número, correspondente com a chave primária, para pegar a linha que deseja alterar o valor, e então informar o novo valor.

----------------------------------------------------------------------------------------------------------------------------
FUNCIONALIDADE EXTRA
----------------------------------------------------------------------------------------------------------------------------

- Criar uma nova coluna em uma tabela já existente
- Apagar uma coluna de uma tabela
- Alterar um valor da tabela

----------------------------------------------------------------------------------------------------------------------------
O QUE NÃO FOI FEITO
----------------------------------------------------------------------------------------------------------------------------

- O programa não lê nomes compostos, para representar nomes compostos ao invés de espaço pedimos que o usuário coloque underline ( _ ).
- Na busca por valores aproximados, o programa não busca números, apenas palavra ou letra.

----------------------------------------------------------------------------------------------------------------------------
O QUE FARIA DE FORMA DIFERENTE
----------------------------------------------------------------------------------------------------------------------------

- Na busca por valores aproximados, incluiria a busca por números.
- Incluiríamos sistemas de cores.

----------------------------------------------------------------------------------------------------------------------------
COMO COMPILAR O PROJETO
----------------------------------------------------------------------------------------------------------------------------

Para executar o projeto é necessário a biblioteca strign.h, stdio.h, stdlib.h, além da biblioteca criada com as funções do código, na qual determinamos como ponto.h.

Os arquivos ponto.h, ponto.c e main.c devem estar localizados na mesma pasta.

Para rodar o programa no terminar Linux, o usuário deve entrar na pasta em que o programa está localizado e digitar "gcc ponto.c main.c -o main" (tirar as aspas), e depois digitar "./main" (tirar as aspas).

----------------------------------------------------------------------------------------------------------------------------
AUTORES
----------------------------------------------------------------------------------------------------------------------------

Acsa Laiane Arcanjo Augusto.
Daniele Mendonça de Carvalho.

----------------------------------------------------------------------------------------------------------------------------

-Obs: Essa obra foi desenvolvida em conjunto pelas duas alunas.


Acsa Laiane/Daniele Mendonça
IMD-UFRN

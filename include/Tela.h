/**
* Concentra as funções de manipulação de tela.
* Todas as colunas têm o mesmo tamanho.
* Exemplo de tela com 4 colunas:
>
NOME COLUNA 1 | NOME COLUNA 2 | NOME COLUNA 3 | NOME COLUNA 4
blablablah    |               |               |
              | blahblahbblAHB|               | 
              |ABAKBLA        |               |
* Notar que a primeira linha é a linha de comando, em que o usuário pode digitar.
* ====================================
*
* 			ATENÇÃO: Não confundir a tela com o console!
*
* ====================================
*/
//---------------------------------------------------------------------
//			DADOS						
//---------------------------------------------------------------------

struct str_tela{
	int quantidadeColunas; 	//A quantidade de colunas desta tela. 
	int ultimaLinhaEscrita; //A última linha em que houve escrita.
	char** nomesColunas; //Os nomes das colunas da tela.
};

typedef struct str_tela TELA;

//Número máximo de colunas.
#define MAXIMO_COLUNAS 5


//---------------------------------------------------------------------
//			FUNÇÕES						
//---------------------------------------------------------------------
/**
* Inicializa a tela.
* @param TELA	*tela_param A tela em que a operação será realizada.
*/
void tela_inicializar(TELA *tela_param);

/**
* Termina o uso da tela.
* @param TELA	*tela_param A tela em que a operação será realizada.
*/
void tela_fechar(TELA *tela_param);

/**
* Espera que o usuário digite uma linha até [ENTER].
* @param TELA	*tela_param A tela em que a operação será realizada.
* @return int	A linha que o usuário digitou.
*/
char* tela_esperarLinhaUsuario(TELA *tela_param);

/**
* Espera input do usuário e digita na tela.
* @param TELA	*tela_param A tela em que a operação será realizada.
*/
void tela_rodar(TELA *tela_param);

/**
* Adiciona uma coluna a esta tela com o nome dado.
* @param TELA	*tela_param A tela em que a operação será realizada.
* @param char*	nomeColuna_param	O nome que ficará no topo da coluna.
*/
void tela_adicionarColuna(TELA *tela_param, char* nomeColuna_param);

/**
* Escreve o texto na linha dada.
* @param TELA	*tela_param A tela em que a operação será realizada.
* @param char*	texto_param	O texto que será escrito. Como há um espaço limitado para cada linha,
*				o texto pode ser enrolado.
* @param int	coluna_param	Coluna em que o texto será escrito. Começando em 1.
*/
void tela_escreverNaColuna(TELA *tela_param, char* texto_param, int coluna_param);

/**
* Concentra as funções de manipulação de memória.
*/
//---------------------------------------------------------------------
//			DADOS						
//---------------------------------------------------------------------

//Constantes
#define QUANTIDADE_PALAVRAS_MEMORIA 1024
#define QUANTIDADE_PARTICOES_MEMORIA 8
#define QUANTIDADE_PALAVRAS_PARTICAO QUANTIDADE_PALAVRAS_MEMORIA/QUANTIDADE_PARTICOES_MEMORIA

typedef int PALAVRA;
typedef int BYTE;

struct str_memoria{
	PALAVRA particoes[QUANTIDADE_PARTICOES_MEMORIA][QUANTIDADE_PALAVRAS_PARTICAO];
	sem_t mutexAcessoMemoria; //Garante que somente um processo usará a memória por vez.
};

typedef struct str_memoria MEMORIA;

//---------------------------------------------------------------------
//			FUNÇÕES						
//---------------------------------------------------------------------
/**
* @param MEMORIA	*memoria_param	A memória que será inicializada.
*/
void memoria_sincronizado_inicializar(MEMORIA *memoria_param);

/**
* @param MEMORIA	*memoria_param			A memória em que a escrita será feita.
* @param int		endereco_param			Endereço da memória em que a escrita será feita.
* @param PALAVRA 	dadosEscritos_param		O que será efetivamente escrito em endereco_param.
*/
void memoria_sincronizado_escreverPalavra(MEMORIA *memoria_param, int endereco_param, PALAVRA dadosEscritos_param);

/**
* @param MEMORIA	*memoria_param		A memória em que a escrita será feita.
* @param int		endereco_param		Endereço da memória em que a escrita será feita.
* @param BYTE		byte0_param			O byte que ficará na posição 0 da palavra, que conterá o bit mais significativo da palavra.
* @param BYTE		byte1_param			O byte que ficará na posição 1 da palavra.
* @param BYTE		byte2_param			O byte que ficará na posição 2 da palavra.
* @param BYTE		byte3_param			O byte que ficará na posição 3 da palavra.
* ATENÇÃO: Escreve uma PALAVRA na memória, mas permite especifica-la byte-a-byte.
*/
void memoria_sincronizado_escreverBytes(MEMORIA *memoria_param, int endereco_param, 
	BYTE byte0_param, BYTE byte1_param, BYTE byte2param, BYTE byte3_param);

/**
* @param MEMORIA	*memoria_param			A memória em que a leitura será feita.
* @param int		endereco_param			Endereço da memória em que a leitura será feita.
* @return PALAVRA	Conteúdo da memória no endereço dado.
*/
PALAVRA memoria_sincronizado_ler(MEMORIA *memoria_param, int endereco_param);
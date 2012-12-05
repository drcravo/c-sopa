/**
* Concentra as funções de manipulação do processador.
*/
//---------------------------------------------------------------------
//			DADOS						
//---------------------------------------------------------------------

//Constantes
#define TAMANHO_INSTRUCAO_PALAVRAS 4

typedef PALAVRA INSTRUCAO;

struct str_processador{
	int PC;
	PALAVRA IR[TAMANHO_INSTRUCAO_PALAVRAS];
};

typedef struct str_processador PROCESSADOR;

//---------------------------------------------------------------------
//			FUNÇÕES						
//---------------------------------------------------------------------
/**
* @param PROCESSADOR	*processador_param	O processador que será inicializado.
*/
void processador_inicializar(PROCESSADOR *processador_param);

/**
* Inicia thread do processador.
* @param PROCESSADOR	*processador_param O processador que irá rodar.
*/
void processador_rodar(PROCESSADOR *processador_param);

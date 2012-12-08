/**
* Concentra as funções de manipulação do processador.
*/
//---------------------------------------------------------------------
//			DADOS						
//---------------------------------------------------------------------

//Constantes
#define TAMANHO_REGISTRADOR_PALAVRAS 16
#define TAMANHO_INSTRUCAO_PALAVRAS 4

enum enum_instrucao{
	INSTRUCAO_INEXISTENTE,
	INSTRUCAO_JPA,
	INSTRUCAO_INT
};

typedef enum enum_instrucao INSTRUCAO;

struct str_registrador{
	PALAVRA conteudo[TAMANHO_REGISTRADOR_PALAVRAS];
};

typedef struct str_registrador REGISTRADOR;

struct str_processador{
	int PC;
	PALAVRA IR[TAMANHO_INSTRUCAO_PALAVRAS];
	REGISTRADOR registrador;
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

/**
* @param PROCESSADOR	*processador_param	O processador no qual a informação será buscada.
* @return int	PC do processador.
*/
int processador_getPC(PROCESSADOR *processador_param);

/**
* @param PROCESSADOR	*processador_param	O processador no qual a informação será buscada.
* @return REGISTRADOR*	Cópia profunda do registrador do processador.
*/
REGISTRADOR* processador_getRegistrador(PROCESSADOR *processador_param);

/**
* @param PROCESSADOR	*processador_param	O processador no qual a operação será realizada.
* @param int				PC_param		O PC que o processador deverá ter.
*/
void processador_setPC(PROCESSADOR *processador_param, int PC_param);

/**
* @param PROCESSADOR	*processador_param		O processador no qual a operação será realizada.
* @param REGISTRADOR	*registrador_param		Registrador que contém o valor que conterá o registrador 
*												do processador ao fim da operação.
*/
void processador_setRegistrador(PROCESSADOR *processador_param, REGISTRADOR *registrador_param);


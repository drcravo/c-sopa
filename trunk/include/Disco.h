/**
* Concentra as funções de manipulação do disco.
*/
//---------------------------------------------------------------------
//			DADOS						
//---------------------------------------------------------------------
struct str_disco{

};

typedef struct str_disco DISCO;

//---------------------------------------------------------------------
//			FUNÇÕES						
//---------------------------------------------------------------------
/**
* Inicia thread do disco.
* @param DISCO	*disco_param	O disco que irá 'rodar'.
*/
void disco_rodar(DISCO *disco_param);
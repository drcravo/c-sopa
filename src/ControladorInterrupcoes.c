#include "../include/DadosComuns.h"

/**
* Variáveis globais acessíveis somente neste arquivo.
*/



//---------------------------------------------------------------------
//			FUNÇÕES PRIVADAS DESTE ARQUIVO						
//---------------------------------------------------------------------


//---------------------------------------------------------------------
//			FUNÇÕES PÚBLICAS DO HEADER						
//---------------------------------------------------------------------
/**
* Inicializa o controlador de interrupções.
* @param CONTROLADOR_INTERRUPCOES	*controladorInterrupcoes_param O controlador de interrupções que irá ser inicializado.
*/
void controladorInterrupcoes_sincronizado_inicializar(CONTROLADOR_INTERRUPCOES *controladorInterrupcoes_param){
	sem_init(&controladorInterrupcoes_param->mutexAcesso, 0, 1);
	sem_wait(&controladorInterrupcoes_param->mutexAcesso);
	controladorInterrupcoes_param->interrupcaoGuardada = SEM_INTERRUPCAO;
	sem_post(&controladorInterrupcoes_param->mutexAcesso);
}

/**
* @param CONTROLADOR_INTERRUPCOES	*controladorInterrupcoes_param O controlador de interrupções no qual a operação será realizada.
* @param INTERRUPCAO 	interrupcao_param	A interrupção que o controlador deverá guardar.
*/
void controladorInterrupcoes_sincronizado_set(CONTROLADOR_INTERRUPCOES *controladorInterrupcoes_param, INTERRUPCAO interrupcao_param){
	sem_wait(&controladorInterrupcoes_param->mutexAcesso);
	controladorInterrupcoes_param->interrupcaoGuardada = interrupcao_param;
	sem_post(&controladorInterrupcoes_param->mutexAcesso);
}

/**
* @param CONTROLADOR_INTERRUPCOES	*controladorInterrupcoes_param O controlador de interrupções no qual a operação será realizada.
* @return INTERRUPCAO A interrupção que o controlador está guardando.
*/
INTERRUPCAO controladorInterrupcoes_sincronizado_get(CONTROLADOR_INTERRUPCOES *controladorInterrupcoes_param){
	sem_wait(&controladorInterrupcoes_param->mutexAcesso);
	INTERRUPCAO interrupcaoGet = controladorInterrupcoes_param->interrupcaoGuardada;
	sem_post(&controladorInterrupcoes_param->mutexAcesso);
	return interrupcaoGet;
}

/**
* Reseta o valor da interrupção guardada para indicar que não há interrupção guardada.
* @param CONTROLADOR_INTERRUPCOES	*controladorInterrupcoes_param O controlador de interrupções no qual a operação será realizada.
*/
void controladorInterrupcoes_sincronizado_reset(CONTROLADOR_INTERRUPCOES *controladorInterrupcoes_param){
	sem_wait(&controladorInterrupcoes_param->mutexAcesso);
	controladorInterrupcoes_param->interrupcaoGuardada = SEM_INTERRUPCAO;
	sem_post(&controladorInterrupcoes_param->mutexAcesso);
}
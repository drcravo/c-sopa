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
* @param PROCESSADOR	*processador_param	O processador que será inicializado.
*/
void processador_inicializar(PROCESSADOR *processador_param){
	processador_param->PC = 0;
	int palavra=0;
	for(; palavra<TAMANHO_INSTRUCAO_PALAVRAS; palavra++){
		processador_param->IR[palavra] = 0;
	}
}

/**
* Inicia thread do processador.
* @param PROCESSADOR	*processador_param O processador que irá rodar.
*/
void processador_rodar(PROCESSADOR *processador_param){
	while(1){
		usleep(1000*1000/10);
		tela_escreverNaColuna(&global_tela, "Mensagem do PROCESSADOR.",1);
	}
}

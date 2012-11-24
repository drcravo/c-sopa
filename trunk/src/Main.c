/**
* SOPA (Sistema operacional para avaliação)
* UNIVERSIDADE FEDERAL DO RIO GRANDE DO SUL (UFRGS) - INSTITUTO DE INFORMÁTICA (INF)
* SISTEMAS OPERACIONAIS II - 2012/2 - Professor: Marcelo Johann
* Autores: 	Diogo Raphael Cravo
*			Ederson Vieira
*/

/*----------------------------------------------------------------------
*						INCLUDES E DEFINES
----------------------------------------------------------------------*/
	//Aplicação
#include "../include/Tela.h"
#include "../include/Kernel.h"
#include "../include/Processador.h"
#include "../include/Disco.h"
#include "../include/Timer.h"
#include "../include/Memoria.h"
#include "../include/Console.h"
#include "../include/ControladorInterrupcoes.h"
	//Bibliotecas
#include <stdio.h>

/*----------------------------------------------------------------------
*						VARIÁVEIS GLOBAIS
----------------------------------------------------------------------*/
PROCESSADOR 				global_processador;
KERNEL 						global_kernel;
DISCO 						global_disco;
TIMER 						global_timer;
CONTROLADOR_INTERRUPCOES 	global_controladorInterrupcoes;
TELA 						global_tela;
MEMORIA 					global_memoria;
CONSOLE 					global_console;

/*----------------------------------------------------------------------
*						FUNÇÕES GLOBAIS
----------------------------------------------------------------------*/



/*----------------------------------------------------------------------
*							MAIN
----------------------------------------------------------------------*/
int main(void)
{
	tela_inicializar(&global_tela);
	tela_adicionarColuna(&global_tela, "       PROCESSADOR");
	tela_adicionarColuna(&global_tela, "          TIMER");
	tela_adicionarColuna(&global_tela, "         KERNEL");
	tela_adicionarColuna(&global_tela, "          DISCO");
	tela_adicionarColuna(&global_tela, "        CONSOLE");
	tela_escreverNaColuna(&global_tela, "Estah eh a mensagem de coluna um e ela eh muito grande. Tao grande que vai ter que ser enrolada em novas linhas.",1);
	tela_escreverNaColuna(&global_tela, "Estah eh a mensagem de coluna um e ela eh muito grande. Tao grande que vai ter que ser enrolada em novas linhas.",2);
	tela_escreverNaColuna(&global_tela, "ccccccc",2);
	tela_escreverNaColuna(&global_tela, "ddddddd",1);
	tela_escreverNaColuna(&global_tela, "eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee",3);
	tela_escreverNaColuna(&global_tela, "quartaquartaquartaquartaquartaquartaquartaquartaquartaquarta",4);

	tela_rodar(&global_tela);
	processador_rodar(&global_processador);
	kernel_rodar(&global_kernel);
	disco_rodar(&global_disco);
	timer_rodar(&global_timer);
	controladorInterrupcoes_rodar(&global_controladorInterrupcoes);
	console_rodar(&global_console);

	tela_fechar(&global_tela);
	return 0;
}


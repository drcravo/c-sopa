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
#include "../include/DadosComuns.h"

/*----------------------------------------------------------------------
*						VARIÁVEIS GLOBAIS
----------------------------------------------------------------------*/


/*----------------------------------------------------------------------
*						FUNÇÕES GLOBAIS
----------------------------------------------------------------------*/



/*----------------------------------------------------------------------
*							MAIN
----------------------------------------------------------------------*/
int main(void){
	sem_init(&global_mutexAcessoTela, 0, 1);
	sem_init(&global_mutexParaTela, 0, 1);

	tela_inicializar(&global_tela);
	tela_adicionarColuna(&global_tela, "       PROCESSADOR");
	tela_adicionarColuna(&global_tela, "          TIMER");
	tela_adicionarColuna(&global_tela, "         KERNEL");
	tela_adicionarColuna(&global_tela, "          DISCO");
	tela_adicionarColuna(&global_tela, "        CONSOLE");
	
	/*tela_escreverNaColuna(&global_tela, "COLUNA1>Estah eh a mensagem de coluna um e ela eh muito grande. Tao grande que vai ter que ser enrolada em novas linhas.",1);
	tela_escreverNaColuna(&global_tela, "COLUNA2>Estah eh a mensagem de coluna um e ela eh muito grande. Tao grande que vai ter que ser enrolada em novas linhas.",2);
	tela_escreverNaColuna(&global_tela, "COLUNA3>Estah eh a mensagem de coluna um e ela eh muito grande. Tao grande que vai ter que ser enrolada em novas linhas.",3);
	tela_escreverNaColuna(&global_tela, "COLUNA4>Estah eh a mensagem de coluna um e ela eh muito grande. Tao grande que vai ter que ser enrolada em novas linhas.",4);
	tela_escreverNaColuna(&global_tela, "COLUNA5>Estah eh a mensagem de coluna um e ela eh muito grande. Tao grande que vai ter que ser enrolada em novas linhas.",5);
	tela_escreverNaColuna(&global_tela, "COLUNA1>Estah eh a mensagem de coluna um e ela eh muito grande. Tao grande que vai ter que ser enrolada em novas linhas.",1);
	tela_escreverNaColuna(&global_tela, "COLUNA2>Estah eh a mensagem de coluna um e ela eh muito grande. Tao grande que vai ter que ser enrolada em novas linhas.",2);
	tela_escreverNaColuna(&global_tela, "COLUNA3>Estah eh a mensagem de coluna um e ela eh muito grande. Tao grande que vai ter que ser enrolada em novas linhas.",3);
	tela_escreverNaColuna(&global_tela, "COLUNA4>Estah eh a mensagem de coluna um e ela eh muito grande. Tao grande que vai ter que ser enrolada em novas linhas.",4);
	tela_escreverNaColuna(&global_tela, "COLUNA5>Estah eh a mensagem de coluna um e ela eh muito grande. Tao grande que vai ter que ser enrolada em novas linhas.",5);
	tela_escreverNaColuna(&global_tela, "COLUNA1>Estah eh a mensagem de coluna um e ela eh muito grande. Tao grande que vai ter que ser enrolada em novas linhas.",1);
	tela_escreverNaColuna(&global_tela, "COLUNA2>Estah eh a mensagem de coluna um e ela eh muito grande. Tao grande que vai ter que ser enrolada em novas linhas.",2);
	tela_escreverNaColuna(&global_tela, "COLUNA3>Estah eh a mensagem de coluna um e ela eh muito grande. Tao grande que vai ter que ser enrolada em novas linhas.",3);
	tela_escreverNaColuna(&global_tela, "COLUNA4>Estah eh a mensagem de coluna um e ela eh muito grande. Tao grande que vai ter que ser enrolada em novas linhas.",4);
	tela_escreverNaColuna(&global_tela, "COLUNA5>Estah eh a mensagem de coluna um e ela eh muito grande. Tao grande que vai ter que ser enrolada em novas linhas.",5);
*/

	pthread_create(&global_threadIdProcessador, NULL, processador_rodar, &global_processador);
	pthread_create(&global_threadIdTimer, NULL, timer_rodar, &global_timer);
	pthread_create(&global_threadIdDisco, NULL, disco_rodar, &global_disco);
	pthread_create(&global_threadIdKernel, NULL, kernel_rodar, &global_kernel);
	pthread_create(&global_threadIdConsole, NULL, console_rodar, &global_console);
	tela_rodar(&global_tela);

	tela_fechar(&global_tela);
	return 0;
}


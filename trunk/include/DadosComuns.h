/**
* Este arquivo concentra variáveis que devem ser vistas por muitos arquivos.
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
#include <pthread.h>
#include <semaphore.h>

/*----------------------------------------------------------------------
*						VARIÁVEIS GLOBAIS
----------------------------------------------------------------------*/
pthread_t global_threadIdProcessador;
pthread_t global_threadIdTimer;
pthread_t global_threadIdKernel;
pthread_t global_threadIdDisco;
pthread_t global_threadIdConsole;

sem_t global_mutexAcessoTela; //Controla acesso à tela em geral.
sem_t global_mutexParaTela; //Controla acesso à tela somente dos elementos que não são tela.
sem_t global_mutexParaEscritaTela; //Controla acesso da tela à escrita na tela.
sem_t global_mutexParaEscritaConsole; //Controla acesso do console à escrita na tela.

PROCESSADOR 				global_processador;
KERNEL 						global_kernel;
DISCO 						global_disco;
TIMER 						global_timer;
CONTROLADOR_INTERRUPCOES 	global_controladorInterrupcoes;
TELA 						global_tela;
MEMORIA 					global_memoria;
CONSOLE 					global_console;

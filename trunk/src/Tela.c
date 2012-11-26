#include "../include/Util/String.h"
//#include "../include/Tela.h"
//#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include "../include/DadosComuns.h"

/**
* Variáveis globais acessíveis somente neste arquivo.
*/
//Comprimento da tela.
#define TELA_COMPRIMENTO 130
//Largura da tela.
#define TELA_LARGURA 40
//A quantidade total de linhas em que se pode escrever. Medida em caracteres.
#define CARACTERES_POR_COLUNA_PARA_ESCRITA 39
//A quantidade total de colunas em que se pode escrever dentro de uma coluna. Medida em caracteres.
#define CARACTERES_POR_LINHA_PARA_ESCRITA 25
//Linha em que o usuário pode escrever.
#define LINHA_CARACTERE_INPUT_USUARIO 1
//Coluna em que o usuário pode escrever.
#define COLUNA_CARACTERE_INPUT_USUARIO 2

//---------------------------------------------------------------------
//			FUNÇÕES PRIVADAS DESTE ARQUIVO						
//---------------------------------------------------------------------
/**
* Move o cursor para o início da linha e coluna. Enviar 1,1 mandará para a linha de entrada.
* @param TELA	*tela_param A tela em que a operação será realizada.
* @param int	linha_param	A linha, da tela, não de caracteres, em que o cursor irá ficar.
* @param int	coluna_param	A coluna, da tela, não de caracteres, em que o cursor irá ficar.
*/
void privada_moverCursor(TELA *tela_param, int linha_param, int coluna_param){
	if(linha_param != 1){
		move((linha_param-1),1+(coluna_param-1)*TELA_COMPRIMENTO/MAXIMO_COLUNAS);	
	} else {
		move((linha_param-1),(coluna_param-1)*TELA_COMPRIMENTO/MAXIMO_COLUNAS);	
	}		
}

/**
* Move o cursor para o caractere na posição dada. Inicia em 1,1.
* @param TELA	*tela_param A tela em que a operação será realizada.
* @param int	linha_param	A linha, da tela, em caracteres, em que o cursor irá ficar.
* @param int	coluna_param	A coluna, da tela, em caracteres, em que o cursor irá ficar.
*/
void privada_moverCursorParaCaractere(TELA *tela_param, int linha_param, int coluna_param){
	move((linha_param-1),(coluna_param-1));	
}

/**
* @param TELA	*tela_param A tela em que a operação será realizada.
* Desenha os limites da tabela.
* OBS:
*	ACS_HLINE (a one-character piece of a horizontal line)
*	ACS_VLINE (vertical line)
*	ACS_ULCORNER (upper-left corner of a box)
*	ACS_URCORNER (upper-right corner)
*	ACS_LLCORNER (lower-left corner)
*	ACS_LRCORNER (lower-right corner)
*	ACS_TTEE (top T, where the top of a vertical line touches a horizontal line)
*	ACS_BTEE (bottom T)
*	ACS_LTEE (left T)
*	ACS_RTEE (right T)
*	ACS_PLUS (intersection of horizontal and vertical line).
*/
void privada_desenharTabela(TELA *tela_param){
	int linha = 2;
	int coluna = 1;
	for(linha=2; linha<=TELA_LARGURA; linha++){
		if(linha==2){
			privada_moverCursorParaCaractere(tela_param, linha, 1);
			addch(ACS_ULCORNER);
			for(coluna=2; coluna<TELA_COMPRIMENTO; coluna++){
				privada_moverCursorParaCaractere(tela_param, linha, coluna);
				if(coluna%(TELA_COMPRIMENTO/MAXIMO_COLUNAS)==1){
					addch(ACS_TTEE);
				} else {
					addch(ACS_HLINE);
				}
			}
			privada_moverCursorParaCaractere(tela_param, linha, TELA_COMPRIMENTO);
			addch(ACS_URCORNER);
		} else if(linha==TELA_LARGURA){
			privada_moverCursorParaCaractere(tela_param, linha, 1);
			addch(ACS_LLCORNER);
			for(coluna=2; coluna<TELA_COMPRIMENTO; coluna++){
				privada_moverCursorParaCaractere(tela_param, linha, coluna);
				if(coluna%(TELA_COMPRIMENTO/MAXIMO_COLUNAS)==1){
					addch(ACS_BTEE);
				} else {
					addch(ACS_HLINE);
				}
			}
			privada_moverCursorParaCaractere(tela_param, linha, TELA_COMPRIMENTO);
			addch(ACS_LRCORNER);
		} else if(linha==4){
			privada_moverCursorParaCaractere(tela_param, linha, 1);
			addch(ACS_LTEE);
			for(coluna=2; coluna<TELA_COMPRIMENTO; coluna++){
				privada_moverCursorParaCaractere(tela_param, linha, coluna);
				if(coluna%(TELA_COMPRIMENTO/MAXIMO_COLUNAS)==1){
					addch(ACS_PLUS);
				} else {
					addch(ACS_HLINE);
				}
			}
			privada_moverCursorParaCaractere(tela_param, linha, TELA_COMPRIMENTO);
			addch(ACS_RTEE);
		} else {
			int colunaTabela;
			for(colunaTabela=0; colunaTabela<MAXIMO_COLUNAS; colunaTabela++){
				privada_moverCursorParaCaractere(tela_param, linha, 1+(colunaTabela)*TELA_COMPRIMENTO/MAXIMO_COLUNAS);
				addch(ACS_VLINE);
			}		
			privada_moverCursorParaCaractere(tela_param, linha, TELA_COMPRIMENTO);
			addch(ACS_VLINE);
		}
	}
}

/**
* Limpa a tabela, apagando todos os textos.
* @param TELA	*tela_param 			A tela em que a operação será realizada.
*/
void privada_limparTela(TELA *tela_param){
	int linha=0;
	for(linha=5; linha<TELA_LARGURA; linha++){
		privada_moverCursorParaCaractere(tela_param, linha, 1);
		clrtoeol();
	}
	privada_desenharTabela(tela_param);
}

/**
* Imprime na tela todos os caracteres guardados em textosColunas à partir do índice dado, considerando o máximo de 
* caracteres que cabem na tabela.
* @param TELA	*tela_param 			A tela em que a operação será realizada.
* @param int	indiceInicial_param	Índice em textosColunas do texto que ficará na primeira linha da coluna.
*/
void privada_imprimirAPartirDe(TELA *tela_param, int indiceInicial_param){
	int linhaImpressa = 5;	
	int indiceTextoParaExibir;
	for(; linhaImpressa<=CARACTERES_POR_COLUNA_PARA_ESCRITA; linhaImpressa++){
		indiceTextoParaExibir = indiceInicial_param+linhaImpressa-1;
		if(0<=indiceTextoParaExibir && indiceTextoParaExibir<tela_param->totalTextosColunas){
			privada_moverCursor(tela_param, linhaImpressa, tela_param->colunasTextosColunas[indiceTextoParaExibir]);
			printw(tela_param->textosColunas[indiceTextoParaExibir]);
			tela_param->ultimoTextoColunaExibido = indiceTextoParaExibir;
		}
	}
}






//---------------------------------------------------------------------
//			FUNÇÕES PÚBLICAS DO HEADER						
//---------------------------------------------------------------------
/**
* Inicializa a tela.
* @param TELA	*tela_param A tela em que a operação será realizada.
*/
void tela_inicializar(TELA *tela_param){
	initscr();   /*Esta função  inicializa a ncurses. Para todos os programas  
                   devemos sempre inicializar a ncurses e depois finalizar, como 
                  veremos adiante. */

	start_color(); //Esta função torna possível o uso das cores

	assume_default_colors(-1,-1); //Funciona somente em terminais que suportem ISO6429

	//Abaixo estamos definindo os pares de cores que serão utilizados no programa
	//init_pair(1,COLOR_WHITE,COLOR_BLUE); //Texto(Branco) | Fundo(Azul)
	//init_pair(2,COLOR_BLUE,COLOR_WHITE); //Texto(Azul) | Fundo(Branco)
	//init_pair(3,COLOR_RED,COLOR_WHITE);  //Texto(Vermelho) | Fundo(Branco)

	/*bkgd(COLOR_PAIR(1));*/  /*Aqui nós definiremos que a cor de fundo do nosso 
                                      programa será azul e a cor dos textos será branca.*/

	/*attron(COLOR_PAIR(3));*/ /*Estamos alterando o par de cores para 3 em vez 
                                          de utilizar o par de cor por omissão(1).*/

	//move(2,1);  //Aqui estamos movendo o cursor para a linha 2 coluna 1.
	//printw("Olá mundo!!!");  //Imprimimos um texto na tela na posição acima.
	/*attroff(COLOR_PAIR(3));*/  /*Estamos alterando o par com a cor por omissão,
                             ou seja, retornando para o par de cor 1. */
	//attron(COLOR_PAIR(2));  
	//move(3,1);
	/*printw("Qualquer tecla para sair.");*/ /*Imprimimos um texto na tela na
                                                        posição acima. */
	//attroff(COLOR_PAIR(2));
	//refresh();    //Atualiza a tela
	tela_param->ultimaLinhaEscrita = 4;
	tela_param->quantidadeColunas = 0;
	tela_param->totalTextosColunas = 0;
	tela_param->ultimoTextoColunaExibido = 0;
	tela_param->abertaParaImpressoes = 1;
	tela_param->nomesColunas = (char**) malloc(MAXIMO_COLUNAS * sizeof(char**));
	tela_param->totalTextosColunas = 0;
	int i;
	for(i=0; i<MAXIMO_LINHAS_SALVAS; i++){
		tela_param->textosColunas[i] = "";		
	}
	for(i=0; i<MAXIMO_LINHAS_SALVAS; i++){
		tela_param->colunasTextosColunas[i] = 0;		
	}
	privada_moverCursor(tela_param, LINHA_CARACTERE_INPUT_USUARIO,COLUNA_CARACTERE_INPUT_USUARIO-1);
	printw(">");
	privada_desenharTabela(tela_param);

	nocbreak();
}

/**
* Espera que o usuário digite uma linha até [ENTER].
* @param TELA	*tela_param A tela em que a operação será realizada.
*/
char* tela_esperarLinhaUsuario(TELA *tela_param){
	sem_wait(&global_mutexAcessoTela);	
	privada_moverCursorParaCaractere(tela_param, LINHA_CARACTERE_INPUT_USUARIO,COLUNA_CARACTERE_INPUT_USUARIO);
	char* digitado = (char*)malloc(100*sizeof(char));
	sem_post(&global_mutexAcessoTela);	
	echo();
	scanw("%s",digitado);
	sem_wait(&global_mutexAcessoTela);	
	privada_moverCursorParaCaractere(tela_param, LINHA_CARACTERE_INPUT_USUARIO,COLUNA_CARACTERE_INPUT_USUARIO);
	clrtoeol();
	sem_post(&global_mutexAcessoTela);	
	return digitado;      //Fica esperando que o usuário aperte alguma tecla.
}

/**
* Termina o uso da tela.
* @param TELA	*tela_param A tela em que a operação será realizada.
*/
void tela_fechar(TELA *tela_param){
	endwin(); /*Sempre que finalizarmos um programa com a biblioteca curses, 
                     devemos executar este comando.*/
}



/**
* Espera input do usuário e digita na tela.
* @param TELA	*tela_param A tela em que a operação será realizada.
*/
void tela_rodar(TELA *tela_param){
	int codigoTeclaPressionada;
	noecho();
	cbreak();
	keypad(stdscr, true);
	while(true){
		codigoTeclaPressionada = getch();
		sem_wait(&global_mutexAcessoTela);	
		switch(codigoTeclaPressionada){
			case KEY_UP: tela_rolar(tela_param, -1);
				break;
			case KEY_DOWN: tela_rolar(tela_param, 1);
				break;
			case KEY_RIGHT: tela_param->abertaParaImpressoes = 0; sem_wait(&global_mutexParaTela);	
				break;
			case KEY_LEFT: tela_param->abertaParaImpressoes = 1; sem_post(&global_mutexParaTela);	
				break;
		}
		sem_post(&global_mutexAcessoTela);	
	}
}

/**
* Adiciona uma coluna a esta tela com o nome dado.
* @param TELA	*tela_param A tela em que a operação será realizada.
* @param char*	nomeColuna_param	O nome que ficará no topo da coluna.
*/
void tela_adicionarColuna(TELA *tela_param, char* nomeColuna_param){
	tela_param->quantidadeColunas++;
	tela_param->nomesColunas[tela_param->quantidadeColunas-1] = nomeColuna_param;
	privada_moverCursor(tela_param, 3,tela_param->quantidadeColunas);
	attron(A_BOLD);
	printw(nomeColuna_param);
	attroff(A_BOLD);
}

/**
* Escreve o texto na linha dada.
* @param TELA	*tela_param A tela em que a operação será realizada.
* @param char*	texto_param	O texto que será escrito. Como há um espaço limitado para cada linha,
*				o texto pode ser enrolado.
* @param int	coluna_param	Coluna em que o texto será escrito. Começando em 1.
* Obs.: Para maior liberdade, utilize com sprintf (buffer, "%d plus %d is %d", a, b, a+b).
*/
void tela_escreverNaColuna(TELA *tela_param, char* texto_param, int coluna_param){
	if(!tela_param->abertaParaImpressoes){
		sem_wait(&global_mutexParaTela);		
		sem_post(&global_mutexParaTela);	
	}
	sem_wait(&global_mutexAcessoTela);	

	int linhasParaExibir = strlen(texto_param)/CARACTERES_POR_LINHA_PARA_ESCRITA;
	linhasParaExibir+= 0<strlen(texto_param)%CARACTERES_POR_LINHA_PARA_ESCRITA? 1: 0;
	
	int i=0;
	for(i=0; i<linhasParaExibir; i++){
		tela_param->totalTextosColunas++;
		tela_param->ultimoTextoColunaExibido = tela_param->totalTextosColunas-1;
		tela_param->ultimaLinhaEscrita++;
		tela_param->textosColunas[tela_param->totalTextosColunas-1] = 
						string_pegarSubtextoNaOrdem(texto_param, CARACTERES_POR_LINHA_PARA_ESCRITA, i);
		tela_param->colunasTextosColunas[tela_param->totalTextosColunas-1] = coluna_param;

		privada_moverCursor(tela_param, tela_param->ultimaLinhaEscrita, coluna_param);
		printw(tela_param->textosColunas[tela_param->totalTextosColunas-1]);

		if(tela_param->ultimaLinhaEscrita==CARACTERES_POR_COLUNA_PARA_ESCRITA){
			tela_rolar(tela_param, 1);
			tela_param->ultimaLinhaEscrita = CARACTERES_POR_COLUNA_PARA_ESCRITA-1;
		}

	}
	privada_moverCursorParaCaractere(tela_param, LINHA_CARACTERE_INPUT_USUARIO,COLUNA_CARACTERE_INPUT_USUARIO);
	refresh();	

	sem_post(&global_mutexAcessoTela);
}

/**
* Joga a tela para cima ou para baixo, mostrando textos escondidos.
* @param TELA	*tela_param 			A tela em que a operação será realizada.
* @param int	quantidadeLinhas_param 	A quantidade de linhas que se deseja ler.
*										0 < quantidadeLinhas_param esconderá textos acima e mostrará textos abaixo.
*										quantidadeLinhas_param < 0 esconderá textos abaixo e mostrará textos acimo.
*										quantidadeLinhas_param == 0 não fará nada.
*/
void tela_rolar(TELA *tela_param, int quantidadeLinhas_param){
	privada_limparTela(tela_param);	
	if(0 < quantidadeLinhas_param){
		privada_imprimirAPartirDe(tela_param, tela_param->ultimoTextoColunaExibido - CARACTERES_POR_COLUNA_PARA_ESCRITA
			+quantidadeLinhas_param+1);
	} else {
		privada_imprimirAPartirDe(tela_param, tela_param->ultimoTextoColunaExibido - CARACTERES_POR_COLUNA_PARA_ESCRITA
			+quantidadeLinhas_param+1);
	}
	privada_moverCursorParaCaractere(tela_param, LINHA_CARACTERE_INPUT_USUARIO,COLUNA_CARACTERE_INPUT_USUARIO);
}




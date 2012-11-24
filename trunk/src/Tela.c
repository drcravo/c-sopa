#include "../include/Tela.h"
#include <stdio.h>
#include <stdlib.h>
#include <curses.h>

/**
* Variáveis globais acessíveis somente neste arquivo.
*/
//A quantidade de colunas desta tela. 
int quantidadeColunas;
//A última linha em que houve escrita.
int ultimaLinhaEscrita;
//A quantidade total de linhas em que se pode escrever. Medida em caracteres.
#define CARACTERES_POR_LINHA_PARA_ESCRITA 40
//A quantidade total de colunas em que se pode escrever. Medida em caracteres.
#define CARACTERES_POR_COLUNA_PARA_ESCRITA 130
//Os nomes das colunas da tela.
char** nomesColunas;
//Linha em que o usuário pode escrever.
#define LINHA_CARACTERE_INPUT_USUARIO 1
//Coluna em que o usuário pode escrever.
#define COLUNA_CARACTERE_INPUT_USUARIO 2

//---------------------------------------------------------------------
//			FUNÇÕES PRIVADAS DESTE ARQUIVO						
//---------------------------------------------------------------------
/**
* Move o cursor para o início da linha e coluna. Enviar 1,1 mandará para a linha de entrada.
* @param int	linha_param	A linha, da tela, não de caracteres, em que o cursor irá ficar.
* @param int	coluna_param	A coluna, da tela, não de caracteres, em que o cursor irá ficar.
*/
void moverCursor(int linha_param, int coluna_param){
	if(linha_param != 1){
		move((linha_param-1),1+(coluna_param-1)*CARACTERES_POR_COLUNA_PARA_ESCRITA/MAXIMO_COLUNAS);	
	} else {
		move((linha_param-1),(coluna_param-1)*CARACTERES_POR_COLUNA_PARA_ESCRITA/MAXIMO_COLUNAS);	
	}		
}

/**
* Move o cursor para o caractere na posição dada. Inicia em 1,1.
* @param int	linha_param	A linha, da tela, em caracteres, em que o cursor irá ficar.
* @param int	coluna_param	A coluna, da tela, em caracteres, em que o cursor irá ficar.
*/
void moverCursorParaCaractere(int linha_param, int coluna_param){
	move((linha_param-1),(coluna_param-1));	
}

/**
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
void desenharTabela(void){
	int linha = 2;
	int coluna = 1;
	for(linha=2; linha<=CARACTERES_POR_LINHA_PARA_ESCRITA; linha++){
		if(linha==2){
			moverCursorParaCaractere(linha, 1);
			addch(ACS_ULCORNER);
			for(coluna=2; coluna<CARACTERES_POR_COLUNA_PARA_ESCRITA; coluna++){
				moverCursorParaCaractere(linha, coluna);
				if(coluna%(CARACTERES_POR_COLUNA_PARA_ESCRITA/MAXIMO_COLUNAS)==1){
					addch(ACS_TTEE);
				} else {
					addch(ACS_HLINE);
				}
			}
			moverCursorParaCaractere(linha, CARACTERES_POR_COLUNA_PARA_ESCRITA);
			addch(ACS_URCORNER);
		} else if(linha==CARACTERES_POR_LINHA_PARA_ESCRITA){
			moverCursorParaCaractere(linha, 1);
			addch(ACS_LLCORNER);
			for(coluna=2; coluna<CARACTERES_POR_COLUNA_PARA_ESCRITA; coluna++){
				moverCursorParaCaractere(linha, coluna);
				if(coluna%(CARACTERES_POR_COLUNA_PARA_ESCRITA/MAXIMO_COLUNAS)==1){
					addch(ACS_BTEE);
				} else {
					addch(ACS_HLINE);
				}
			}
			moverCursorParaCaractere(linha, CARACTERES_POR_COLUNA_PARA_ESCRITA);
			addch(ACS_LRCORNER);
		} else if(linha==4){
			moverCursorParaCaractere(linha, 1);
			addch(ACS_LTEE);
			for(coluna=2; coluna<CARACTERES_POR_COLUNA_PARA_ESCRITA; coluna++){
				moverCursorParaCaractere(linha, coluna);
				if(coluna%(CARACTERES_POR_COLUNA_PARA_ESCRITA/MAXIMO_COLUNAS)==1){
					addch(ACS_PLUS);
				} else {
					addch(ACS_HLINE);
				}
			}
			moverCursorParaCaractere(linha, CARACTERES_POR_COLUNA_PARA_ESCRITA);
			addch(ACS_RTEE);
		} else {
			int colunaTabela;
			for(colunaTabela=0; colunaTabela<MAXIMO_COLUNAS; colunaTabela++){
				moverCursorParaCaractere(linha, 1+(colunaTabela)*CARACTERES_POR_COLUNA_PARA_ESCRITA/MAXIMO_COLUNAS);
				addch(ACS_VLINE);
			}		
			moverCursorParaCaractere(linha, CARACTERES_POR_COLUNA_PARA_ESCRITA);
			addch(ACS_VLINE);
		}
	}
}


//---------------------------------------------------------------------
//			FUNÇÕES PÚBLICAS DO HEADER						
//---------------------------------------------------------------------
/**
* Inicializa a tela.
*/
void tela_inicializar(void){
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
	ultimaLinhaEscrita = 4;
	quantidadeColunas = 0;
	nomesColunas = (char**) malloc(MAXIMO_COLUNAS * sizeof(char**));

	moverCursor(LINHA_CARACTERE_INPUT_USUARIO,COLUNA_CARACTERE_INPUT_USUARIO-1);
	printw(">");
	desenharTabela();

	nocbreak();
}

/**
* Termina o uso da tela.
*/
void tela_fechar(void){
	endwin(); /*Sempre que finalizarmos um programa com a biblioteca curses, 
                     devemos executar este comando.*/
}

/**
* Espera que o usuário digite uma linha até [ENTER].
*/
char* tela_esperarLinhaUsuario(void){
	moverCursorParaCaractere(LINHA_CARACTERE_INPUT_USUARIO,COLUNA_CARACTERE_INPUT_USUARIO);
	char* digitado = (char*)malloc(CARACTERES_POR_COLUNA_PARA_ESCRITA*sizeof(char));
	scanw("%s",digitado);
	moverCursorParaCaractere(LINHA_CARACTERE_INPUT_USUARIO,COLUNA_CARACTERE_INPUT_USUARIO);
	clrtoeol();
	return digitado;      //Fica esperando que o usuário aperte alguma tecla.
}

/**
* Espera input do usuário e digita na tela.
*/
void tela_run(void){
	char* linhaDigitada;
	while(true){
		linhaDigitada = tela_esperarLinhaUsuario();
		//printw(linhaDigitada);
	}
}

/**
* Adiciona uma coluna a esta tela com o nome dado.
* @param char*	nomeColuna_param	O nome que ficará no topo da coluna.
*/
void tela_adicionarColuna(char* nomeColuna_param){
	quantidadeColunas++;
	nomesColunas[quantidadeColunas-1] = nomeColuna_param;
	moverCursor(3,quantidadeColunas);
	attron(A_BOLD);
	printw(nomeColuna_param);
	attroff(A_BOLD);
}

/**
* Escreve o texto na linha dada.
* @param char*	texto_param	O texto que será escrito. Como há um espaço limitado para cada linha,
*				o texto pode ser enrolado.
* @param int	coluna_param	Coluna em que o texto será escrito. Começando em 1.
*/
void tela_escreverNaColuna(char* texto_param, int coluna_param){
	ultimaLinhaEscrita++;
	moverCursor(ultimaLinhaEscrita,coluna_param);
	int colunasNestaLinha = CARACTERES_POR_COLUNA_PARA_ESCRITA/MAXIMO_COLUNAS-1;
	int i=0;
	while(texto_param[i] != '\0'){
		if(i%colunasNestaLinha == 0 && i!=0){
			ultimaLinhaEscrita++;
			moverCursor(ultimaLinhaEscrita,coluna_param);
		}
		addch(texto_param[i]);
		i++;
	}
}








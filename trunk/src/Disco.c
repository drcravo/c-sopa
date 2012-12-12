#include "../include/DadosComuns.h"

/**
* Variáveis globais acessíveis somente neste arquivo.
*/



//---------------------------------------------------------------------
//			FUNÇÕES PRIVADAS DESTE ARQUIVO						
//---------------------------------------------------------------------
/**
* @param DISCO		*disco_param		O disco em que será gravado.
* @param int		posicao_param		A posição do disco que será testada.
* @return int	Indica se a posição passada está livre. Se ela pode ser sobrescrita.
*/
int privada_posicaoEstahLivre(DISCO *disco_param, int posicao_param){
	if(disco_param->conteudo[posicao_param] == POSICAO_VAZIA){
		return 1;
	} else {
		return 0;
	}
}

/**
* Escreve os bytes na primeira palavra livre do disco.
* Corre o risco de não escrever os dados em posições contíguas quando chamada sucessivamente.
* @param DISCO		*disco_param		O disco em que será gravado.
* @param BYTE		byte0_param			O byte que ficará na posição 0 da palavra, que conterá o bit mais significativo da palavra.
* @param BYTE		byte1_param			O byte que ficará na posição 1 da palavra.
* @param BYTE		byte2_param			O byte que ficará na posição 2 da palavra.
* @param BYTE		byte3_param			O byte que ficará na posição 3 da palavra.
*/
void privada_escreverNaProximaPalavraLivre(DISCO *disco_param, BYTE byte0_param, BYTE byte1_param, BYTE byte2_param, BYTE byte3_param){
	int primeiraPosicaoLivre=0;
	int posicaoDisco=0;
	while(!privada_posicaoEstahLivre(disco_param, posicaoDisco) && posicaoDisco<TAMANHO_DISCO_PALAVRAS){
		posicaoDisco++;
	}
	primeiraPosicaoLivre = posicaoDisco;
	disco_param->conteudo[primeiraPosicaoLivre] = 
		((((byte0_param & 0xFF000000)/256)/256)/256)
		| (((byte1_param & 0x00FF0000)/256)/256)
		| ((byte2_param & 0x0000FF00)/256)
		| (byte3_param & 0x000000FF);
}

/**
* Efetivamente executa a operação dada.
* @param DISCO				*disco_param	O disco em que a operação será realizada.
* @param OPERACAO_DISCO 	operacao_param	A operação que será realizada.s
* @param int				endereco_param	Para operações sobre um endereço, o próprio.
* @param int				dados_param		Para uma escrita, os dados que serão escritos.
*/
void privada_executar(DISCO *disco_param, OPERACAO_DISCO operacao_param, int endereco_param, PALAVRA dados_param){
	if(endereco_param < 0 || TAMANHO_DISCO_PALAVRAS <= endereco_param){
		disco_param->erroUltimaOperacao = ERRO_DISCO_ENDERECO_INVALIDO;
	} else {
		disco_param->erroUltimaOperacao = SEM_ERRO_DISCO;
		switch(operacao_param){
			case OPERACAO_LEITURA_DISCO:
				tela_escreverNaColuna(&global_tela, "Leitura.",4);
				disco_param->tamanhoUltimaLeitura = 1;
				if(disco_param->dadosUltimaLeitura = NULL){
					free(disco_param->dadosUltimaLeitura);
				}
				disco_param->dadosUltimaLeitura = (PALAVRA*) malloc(disco_param->tamanhoUltimaLeitura*sizeof(PALAVRA));
				disco_param->dadosUltimaLeitura[0] = disco_param->conteudo[endereco_param];
				break;
			case OPERACAO_ESCRITA_DISCO:
				tela_escreverNaColuna(&global_tela, "Escrita.",4);
				disco_param->conteudo[endereco_param] = dados_param;
				break;
			case OPERACAO_CARGA_DISCO:
				tela_escreverNaColuna(&global_tela, "Carga.",4);
				tela_escreverNaColuna(&global_tela, "A carga nao foi implementada.",4);
				break;
			case OPERACAO_NENHUMA_DISCO:
				tela_escreverNaColuna(&global_tela, "Algum erro.",4);
		}
	}
}

//---------------------------------------------------------------------
//			FUNÇÕES PÚBLICAS DO HEADER						
//---------------------------------------------------------------------
/**
* Inicia thread do disco.
* @param DISCO	*disco_param	O disco que irá 'rodar'.
*/
void disco_rodar(DISCO *disco_param){
	sem_init(&disco_param->mutexAcessoDisco, 0, 1);
	sem_wait(&disco_param->mutexAcessoDisco);
	int posicaoDisco=0;
	for(; posicaoDisco<TAMANHO_DISCO_PALAVRAS; posicaoDisco++){
		disco_param->conteudo[posicaoDisco] = POSICAO_VAZIA;
	}
	disco_carregar(disco_param, CAMINHO_ARQUIVO_BASE_DISCO);
	disco_param->proximaOperacao = OPERACAO_NENHUMA_DISCO;
	disco_param->erroUltimaOperacao = SEM_ERRO_DISCO;
	disco_param->tamanhoUltimaLeitura = 0;
	disco_param->dadosUltimaLeitura = NULL;
	disco_param->dadosProximaEscrita = POSICAO_VAZIA;
	disco_param->enderecoProximaOperacao = 0;

	while(1){
		sem_wait(&disco_param->mutexAcessoDisco);

		usleep(1000*1000*2);

		privada_executar(disco_param, disco_param->proximaOperacao, 
			disco_param->enderecoProximaOperacao, disco_param->dadosProximaEscrita);

		controladorInterrupcoes_set(&global_controladorInterrupcoes, INTERRUPCAO_DISCO);
	}
}

/**
* Libera o disco para executar uma operação.
* @param DISCO				*disco_param	O disco em que a operação será realizada.
* @param OPERACAO_DISCO 	operacao_param	A operação que será realizada.s
* @param int				endereco_param	Para operações sobre um endereço, o próprio.
* @param int				dados_param		Para uma escrita, os dados que serão escritos.
* ATENÇÃO: A operação não é executada de imediato, mas algum tempo depois.
*/
void disco_executarOperacao(DISCO *disco_param, OPERACAO_DISCO operacao_param, int endereco_param, PALAVRA dados_param){
	disco_param->tamanhoUltimaLeitura = 0;
	disco_param->erroUltimaOperacao = SEM_ERRO_DISCO;
	disco_param->enderecoProximaOperacao = endereco_param;
	disco_param->proximaOperacao = operacao_param;
	if(operacao_param != OPERACAO_LEITURA_DISCO
			&& operacao_param != OPERACAO_CARGA_DISCO
			&& operacao_param != OPERACAO_ESCRITA_DISCO){
		disco_param->enderecoProximaOperacao = 0;
		disco_param->dadosProximaEscrita = POSICAO_VAZIA;
		disco_param->proximaOperacao = OPERACAO_NENHUMA_DISCO;
	} else if(operacao_param == OPERACAO_ESCRITA_DISCO){
		disco_param->dadosProximaEscrita = dados_param;
	}
	sem_post(&disco_param->mutexAcessoDisco);
}


/**
* Carrega os dados do arquivo, juntando-os aos dados que estão no disco.
* Os dados são colocados à partir da primeira posição livre neste disco.
* @param DISCO	*disco_param			O disco em que a operação será realizada.
* @param char*	*caminhoArquivo_param	Arquivo que contém os dados, formatados da seguinte forma:
*										J P A 0
*										255 255 255 255
*										0 0 0 0
*/
void disco_carregar(DISCO *disco_param, char *caminhoArquivo_param){
	int posicaoPalavra = 0;
	int palavra[TAMANHO_INSTRUCAO_PALAVRAS];
	int posicaoEscrita=0;
	char linha[200];
	char* byte;
	char* palavraBytes[TAMANHO_INSTRUCAO_PALAVRAS];
	char mensagem[200];
	FILE *arquivoLido;
	arquivoLido = fopen(caminhoArquivo_param, "r");
	if(arquivoLido == NULL){
		sprintf(mensagem, "Nao consegui carregar o arquivo '%s'.", caminhoArquivo_param);
		tela_escreverNaColuna(&global_tela, mensagem, 4);
	} else {
		while(fgets(linha, 200, arquivoLido)){
			byte=strtok(linha, " \n");
			posicaoPalavra = 0;
			do{
				if(byte != NULL){
					palavraBytes[posicaoPalavra] = byte;
					posicaoPalavra++;
				}
			}while(byte=strtok(NULL," \n"));
			palavra[0] = string_paraInt(palavraBytes[0]);
			palavra[1] = string_paraInt(palavraBytes[1]);
			palavra[2] = string_paraInt(palavraBytes[2]);
			palavra[3] = string_paraInt(palavraBytes[3]);
			tela_escreverNaColuna(&global_tela, mensagem, 4);
			privada_escreverNaProximaPalavraLivre(disco_param, palavra[0], palavra[1], palavra[2], palavra[3]);
			sprintf(mensagem, "Lido '%s %s %s %s', gravado '%d'.", 
				palavraBytes[0], palavraBytes[1], palavraBytes[2], palavraBytes[3], disco_param->conteudo[posicaoEscrita]);
			posicaoEscrita++;
		}
	}
}

/**
* @param DISCO	*disco_param			O disco em que a operação será realizada.
* @return ERRO_DISCO 	O erro que aconteceu, caso tenha acontecido, na última operação realizada no disco.
*/
ERRO_DISCO disco_erroUltimaOperacao(DISCO *disco_param){
	return disco_param->erroUltimaOperacao;
}

/**
* @param DISCO	*disco_param			O disco em que a operação será realizada.
* @return int 	Tamanho em palavras do que foi lido na última operação de leitura.
*/
int disco_tamanhoPalavrasUltimaLeitura(DISCO *disco_param){
	return disco_param->tamanhoUltimaLeitura;
}

/**
* @param DISCO	*disco_param			O disco em que a operação será realizada.
* @param int	posicaoBuffer_param		A posição que será retornada do buffer da última leitura.
* @return PALAVRA 	A palavra lida na última leitura do disco e que está na posicaoBuffer_param.
*/
PALAVRA disco_palavrasUltimaLeituraPosicao(DISCO *disco_param, int posicaoBuffer_param){
	if(posicaoBuffer_param < disco_param->tamanhoUltimaLeitura){
		return disco_param->dadosUltimaLeitura[posicaoBuffer_param];
	} else {
		tela_imprimirTelaAzulDaMorte(&global_tela, "Ocorreu um erro fatal! Um programa tentou ler um endereco do disco inexistente!");
		return 0;
	}
}





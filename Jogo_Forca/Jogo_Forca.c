#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "forca.h"

char palavrasecreta[TAMANHO_PALAVRA]; 
char chutes[26];           //variáveis globais
int chutesdados = 0;

void abertura(){
	printf("/****************/\n");
	printf("/ Jogo de Forca */\n");
	printf("/****************/\n\n");
}

void chuta(){
	char chute;
	printf("Qual letra(MAIUSCULA)? ");
	scanf(" %c", &chute);
	
	chutes[chutesdados]=chute;
	chutesdados++;
}

int chutou(char letra){
	int achou = 0;
	for(int j = 0; j < chutesdados; j++){
		if (chutes[j] == letra){
			achou = 1;
			break;
		}
	}
	return achou;
}

void desenhaforca(){
	int erros = chuteserrados();
    printf("  _______       \n");
    printf(" |/      |      \n");
    printf(" |      %c%c%c  \n", (erros>=1?'(':' '), (erros>=1?'_':' '), (erros>=1?')':' '));
    printf(" |      %c%c%c  \n", (erros>=3?'\\':' '), (erros>=2?'|':' '), (erros>=3?'/': ' '));
    printf(" |       %c     \n", (erros>=2?'|':' '));
    printf(" |      %c %c   \n", (erros>=4?'/':' '), (erros>=4?'\\':' '));
    printf(" |              \n");
    printf("_|___           \n");
    printf("\n\n");
	
	printf("Numero de chutes: %d\n", chutesdados);
	for(int i = 0; i< strlen(palavrasecreta);i++){
		int achou = chutou(palavrasecreta[i]);
		if (achou){
			printf("%c ", palavrasecreta[i]);
		}else{
			printf("_ ");
		}	
	}
	printf("\n");
}

void escolhepalavra(){
	FILE* f; //ponteiro de arquivo

	f = fopen("palavras.txt", "r");
	if (f ==0){
		printf("Desculpe, banco de dados nao disponivel\n\n");
		exit(1);
	}
	
	int qtdpalavras;
	fscanf(f,"%d",&qtdpalavras);
	
	srand(time(0));
	int randomico = rand()%qtdpalavras;
	
	for (int i = 0; i<=randomico; i++){
		fscanf(f,"%s",palavrasecreta);
	}
	fclose(f);
}

void addpalavra(){
	char quer;
	printf("\nQuer adicionar uma palavra nova ao jogo? (S/N) ");
	scanf(" %c", &quer);
	if( quer == 'S'){
		char novapalavra[TAMANHO_PALAVRA];
		printf("Qual a nova palavra? ");
		scanf("%s",novapalavra);
		
		FILE* f;
		
		f = fopen("palavras.txt", "r+");
		
		if (f ==0){
			printf("Desculpe, banco de dados nao disponivel\n\n");
			exit(1);
		}		
		
		int qtd;
		fscanf(f,"%d",&qtd);
		qtd++;
		
		fseek(f,0,SEEK_SET);
		fprintf(f,"%d", qtd);
		
		fseek(f,0,SEEK_END);
		fputc('\n',f);
		fprintf(f,"%s", novapalavra);
		
		fclose(f);
	}
}

int acertou(){
	for(int i =0; i<strlen(palavrasecreta);i++){
		if(!chutou(palavrasecreta[i])){
			return 0;
		}
	}
	return 1;
}

int chuteserrados(){
	int erros = 0;
	for(int i = 0; i<chutesdados;i++){
		int existe = 0;
		for (int j =0; j<strlen(palavrasecreta);j++){
			if(chutes[i] == palavrasecreta[j]){
				existe = 1;
				break;
			}	
		}
		if (!existe) erros++;
	}
	return erros;
}

int enforcado(){
	return chuteserrados()>=7;
}


int main(){
	abertura();
	escolhepalavra(palavrasecreta);

	do{
		desenhaforca();
		chuta();
	}while(!acertou() && !enforcado());
	
	if (acertou()){
		printf("\n Parabens, voce acertou!\n");
		printf(" |\\---/|  \n");      
		printf(" | o_o |  \n");       
		printf("  \\_v_/   \n");      
	}else{
		printf("\nPuxa, voce foi enforcado!\n");
		printf("A palavra era **%s**\n\n", palavrasecreta);
		printf(" |\\---/|  \n");      
		printf(" | >_< |  \n");       
		printf("  \\_^_/   \n");
	}
	addpalavra();
}

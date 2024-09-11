#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main(){
printf("\n\n");
printf(" [][][] /''\\ [][][]        				\n");
printf("  |::| /____\\ |::|         				\n");
printf("  |[]|_|::::|_|[]|      Bem-vindos ao     	\n");
printf("  |::::::__::::::|   Jogo de Adivinhacao!	\n");
printf("  |:::::/||\\:::::|           				\n");
printf("  |:#:::||||::#::|           				\n");
printf("  #%*###&*##&*&#*&##         				\n");
printf("  #%*###&*##&*&#*&##        				\n");
printf("\n\n");
	
	int i,chute,nivel,tottentativas;
	srand(time(0));
	int numerosecreto = rand()%100;
	double pontos=1000;
	int acertou = 0;
	
	printf("\nQual o nivel de dificuldade?");
	printf("\n(1)Facil (2)Medio (3)Dificil");
	printf("\nEscolha: ");
	scanf("%d",&nivel);
	
	switch(nivel){
		case 1:
			tottentativas = 20;
			break;
		case 2:
			tottentativas = 15;
			break;
		default:
			tottentativas = 6;
			break;
	}
	
	for(i=1; i<=tottentativas; i++){
	printf("\nTentativa %d de %d",i, tottentativas);
	printf("\nChute um numero:");
	scanf("%d", &chute);
	
	if (chute<0){
		printf("\nTu n pode chutar numeros negativos!");
		continue; //Continue para n executar código abaixo, volta no loop.
	}

	acertou = (chute == numerosecreto);
	int maior = chute > numerosecreto;
	
	if (acertou){
		break; //Break para parar o loop.
	} else if(maior){
		printf("\nSeu chute foi maior do que o numero secreto!\n");
		}
		else{
		printf("\nSeu chute foi menor do que o numero secreto!\n");
		}
		double pontosperdidos = abs(chute-numerosecreto)/2.0;
		pontos= pontos-pontosperdidos;
}
	if (acertou){
		printf("\nParabens! Acertou miseravel!");
		printf("\nV(-.o)V");
	}else{
		printf("\nPerdeu, miseravel! Tente novamente!");
		printf("\n.·´¯`(>__<)´¯`·. ");
	}
	
	printf("\nSeu total de tentativas foram: %d", i);
	printf("\nPontos:%.2f\n", pontos);
	printf("O numero aleatorio eh:%d", numerosecreto);
	printf("\nFim de jogo!");
}


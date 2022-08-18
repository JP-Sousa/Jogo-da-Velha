/* Criando um tabuleiro de Jogo da Velha Crie um tabuleiro de jogo da velha, usando uma matrizes de caracteres (char) 3×3, onde o usuário pede o número da linha (1 até 3)
 e o da coluna (1 até 3). A cada vez que o usuário entrar com esses dados, colocar um ‘X’ ou ‘O’ no local selecionado */

#include <stdio.h>

#define T 3 // Define o tamanho do tabuleiro

int menu(){ // Menu de opções 
	
	int opcao;
	
	printf("\n1 - Novo Jogo\n"); // Inicia um novo jogo
	printf("0 - Sair\n"); // Sair do programa

	printf("\nEscolha uma opcao: ");
	scanf("%d", &opcao);
	
	return opcao;
}

void tabuleiro(char tabu[T][T]){ // Procedimento para imprimir o tabuleiro
	
	printf("\n");
	
	for(int i = 0; i < T; i++){
		
		if(i == 0){
			printf("    0 1 2"); // Imprime o numero das colunas 
			printf("\n  _______\n"); 
		}
		
		printf("%d | ", i);	// Imprime o numero das linhas
		
		for(int j = 0; j < T; j++)
			printf("%c ", tabu[i][j]); // Imprime o tabuleiro
		
		printf("\n");
	}
	
	printf("\n");
}

void reiniciar(char tabu[T][T]){ // Procedimento para resetar as posições do tabuleiro
	for(int i = 0; i < T; i++)
		for(int j = 0; j < T; j++)
			tabu[i][j] = ' ';
}

int jogo(int jogador, char tabu[T][T]){ // Função que executa o jogo
	
	int l, c; // l = linha, c = coluna
	
	printf("Jogador %d, Digite a linha e a coluna: ", jogador);
	scanf("%d%d", &l, &c);
	
	if(tabu[l][c] == ' '){ // Coloca X ou O no tabuleiro
		
		if(jogador == 1)
			tabu[l][c] = 'X';
		
		else if(jogador == 2)
			tabu[l][c] = 'O';
	}
	else{ // Evita a substituição de um quadrado já preenchido
		printf("\nQuadrado ja preenchido, por favor tente novamente\n\n"); 
	
		jogo(jogador, tabu);
	}
	
	return jogador == 1 ? 2: 1;
}

int verificacao(char tabu[T][T], int jogador){ // Verifica se há um vencedor ou se o jogo empatou
	
	int empate = 0, linha, coluna, diag1, diag2;
	
	for(int i = 0; i < T; i++){
		
		linha = coluna = diag1 = diag2 = 0;
		
		for(int j = 0; j < T; j++){ 
			
			if(tabu[i][j] == 'X') // Verifica as posições horizontais do tabuleiro
				linha++;
			
			if(tabu[j][i] == 'X') // Verifica as posições verticais do tabuleiro
				coluna++;
			
			if(tabu[j][j] == 'X') // Verifica a diagonal principal
				diag1++;
			
			if(tabu[0][2] == 'X' && tabu[1][1] == 'X' && tabu[2][0] == 'X') // Verifica a diagonal secundária
				diag2++;
		}
		
		if(linha == 3 || coluna == 3 || diag1 == 3 || diag2 == 3){ // Se alguma verificação corresponder a 3 do mesmo tipo há um vencedor
			
			printf("Parabens jogador 1 voce venceu!\n");
		
			return 2;
		}
	}
	
	for(int i = 0; i < T; i++){ 
		
		linha = coluna = diag1 = diag2 = 0;
		
		for(int j = 0; j < T; j++){
			
			if(tabu[i][j] == 'O')
				linha++;
			
			if(tabu[j][i] == 'O')
				coluna++;
			
			if(tabu[j][j] == 'O')
				diag1++;
			
			if(tabu[0][2] == 'O' && tabu[1][1] == 'O' && tabu[2][0] == 'O')
				diag2++;
		}
		
		if(linha == 3 || coluna == 3 || diag1 == 3 || diag2 == 3){
			
			printf("Parabens jogador 2 voce venceu!\n");
		
			return 2;
		}
	}
	 
	for(int i = 0; i < T; i++){ // Verifica se o jogo empatou
		for(int j = 0; j < T; j++){
			if(tabu[i][j] == 'X' || tabu[i][j] == 'O') // Se não houver espaços vazios e não houver um vencedor o jogo é declarado empate
				empate++;
		}
	}
	
	if(empate == 9){
		
		printf("\nIh deu velha!\n");
		
		return 2;
	}
	
	return 1;
}

int main(){
	
	int opcao, jogador = 1;
	char tabu[T][T];
	
	do{		
		opcao = menu();
		
		reiniciar(tabu);
		
		while(opcao == 1){
			
			tabuleiro(tabu);
			
			opcao = verificacao(tabu, jogador);
			
			if(opcao == 1)
				jogador = jogo(jogador, tabu);
		}
		
	}while(opcao == 1 || opcao == 2);
	
	return 0;
}
/*
   *Autores:
   *Willian Santos Moura
   *Emely Vitória Vasconcelos Albernaz Lopes
   *Beatriz Vendrame
   *
   *Data:
   *31/03/2017
   *
   *Objetivo do programa:
   *Executar o jogo do PacMan por completo
*/


#include <stdio.h>//Biblioteca padrão
#include <conio.c>//Utilizada para manipulação de cores dos caracteres;
#include <windows.h>//Disponibiliza funções relativas ao sistema
#include <stdlib.h>//Disponibiliza funções relativas ao sistema
#include <math.h>//Fornece operações matemáticas
#include <locale.h>//Garante que a acentuação e os caracteres especiais serão exebidos normalmente
//Definindo alguns valores padrões
#define PACMAN 2
#define FANTASMAS 5
//Constantes referentes a construção do labirinto
#define CHAO 0
#define PAREDEVT 1
#define PAREDEHR 2
#define CANTOSUPESQ 3
#define CANTOSUPDIR 4
#define CANTOINFESQ 5
#define CANTOINFDIR 6
#define INTERS 8
#define PILULA 7
#define SUPPILULA 9
//Constante referente à velocidade
#define VELPACMAN 50
#define DURSUPPIL 250

//Modelo do mapa de interseções como matriz
/*Nele estão todas as intersecções do labirinto (representadas pelo número 8)
utilizadas nos fantasmas que se movimentam aleatóriamente pelo mapa*/
int mapInt[29][45]={
        {0,3,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,4,0,3,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,4,0},
        {0,1,8,0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,0,0,8,1,0,1,8,0,0,0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,8,1,0},
        {0,1,0,3,2,2,2,2,2,4,0,3,2,2,2,2,2,2,2,4,0,1,0,1,0,3,2,2,2,2,2,2,2,4,0,3,2,2,2,2,2,4,0,1,0},
        {0,1,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,1,0,1,0,1,0,1,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,1,0},
        {0,1,0,5,2,2,2,2,2,6,0,5,2,2,2,2,2,2,2,6,0,5,2,6,0,5,2,2,2,2,2,2,2,6,0,5,2,2,2,2,2,6,0,1,0},
        {0,1,8,0,0,0,0,0,0,0,8,0,0,0,8,0,0,0,0,0,8,0,0,0,8,0,0,0,0,0,8,0,0,0,8,0,0,0,0,0,0,0,8,1,0},
        {0,1,0,3,2,2,2,2,2,4,0,3,2,4,0,3,2,2,2,2,2,2,2,2,2,2,2,2,2,4,0,3,2,4,0,3,2,2,2,2,2,4,0,1,0},
        {0,1,0,5,2,2,2,2,2,6,0,1,0,1,0,5,2,2,2,2,4,0,0,0,3,2,2,2,2,6,0,1,0,1,0,5,2,2,2,2,2,6,0,1,0},
        {0,1,8,0,0,0,0,0,0,0,8,1,0,1,8,0,0,0,0,8,1,0,0,0,1,8,0,0,0,0,8,1,0,1,8,0,0,0,0,0,0,0,8,1,0},
        {0,5,2,2,2,2,2,2,2,4,0,1,0,5,2,2,2,2,4,0,1,0,0,0,1,0,3,2,2,2,2,6,0,1,0,3,2,2,2,2,2,2,2,6,0},
        {0,0,0,0,0,0,0,0,0,1,0,1,0,3,2,2,2,2,6,0,5,2,2,2,6,0,5,2,2,2,2,4,0,1,0,1,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,1,0,1,0,1,8,0,0,0,0,8,0,0,8,0,0,8,0,0,0,0,8,1,0,1,0,1,0,0,0,0,0,0,0,0,0},
       {15,2,2,2,2,2,2,2,2,6,0,5,2,6,0,3,2,2,2,2,2,2,15,2,2,2,2,2,2,4,0,5,2,6,0,5,2,2,2,2,2,2,2,2,15},
        {0,0,0,0,0,0,0,0,0,0,8,0,0,0,8,1,8,0,0,0,0,0,8,0,0,0,0,0,8,1,8,0,0,0,8,0,0,0,0,0,0,0,0,0,0},
       {15,2,2,2,2,2,2,2,2,4,0,3,2,4,0,5,2,2,2,2,2,2,2,2,2,2,2,2,2,6,0,3,2,4,0,3,2,2,2,2,2,2,2,2,15},
        {0,0,0,0,0,0,0,0,0,1,0,1,0,1,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,1,0,1,0,1,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,3,2,2,2,2,2,2,2,2,2,2,2,2,2,4,0,1,0,1,0,1,0,0,0,0,0,0,0,0,0},
        {0,3,2,2,2,2,2,2,2,6,0,5,2,6,0,5,2,2,2,2,4,0,0,0,3,2,2,2,2,6,0,5,2,6,0,5,2,2,2,2,2,2,2,4,0},
        {0,1,8,0,0,0,0,0,0,0,8,0,0,0,8,0,0,0,0,8,1,0,0,0,1,8,0,0,0,0,8,0,0,0,8,0,0,0,0,0,0,0,8,1,0},
        {0,1,0,3,2,2,2,2,2,4,0,3,2,2,2,2,2,2,4,0,1,0,0,0,1,0,3,2,2,2,2,2,2,4,0,3,2,2,2,2,2,4,0,1,0},
        {0,1,0,5,2,2,2,4,0,1,0,5,2,2,2,2,2,2,6,0,5,2,2,2,6,0,5,2,2,2,2,2,2,6,0,1,0,3,2,2,2,6,0,1,0},
        {0,1,8,0,0,0,8,1,0,1,8,0,0,0,8,0,0,0,0,8,0,0,0,0,0,8,0,0,0,0,8,0,0,0,8,1,0,1,8,0,0,0,8,1,0},
        {0,5,2,2,2,4,0,1,0,1,0,3,2,4,0,3,2,2,2,2,2,2,2,2,2,2,2,2,2,4,0,3,2,4,0,1,0,1,0,3,2,2,2,6,0},
        {0,3,2,2,2,6,0,5,2,6,0,1,0,1,0,5,2,2,2,2,4,0,0,0,3,2,2,2,2,6,0,1,0,1,0,5,2,6,0,5,2,2,2,4,0},
        {0,1,8,0,0,0,0,0,0,0,8,1,0,1,8,0,0,0,0,8,1,0,0,0,1,8,0,0,0,0,8,1,0,1,8,0,0,0,8,0,0,0,8,1,0},
        {0,1,0,3,2,2,2,2,2,2,2,6,0,5,2,2,2,2,4,0,1,0,0,0,1,0,3,2,2,2,2,6,0,5,2,2,2,2,2,2,2,4,0,1,0},
        {0,1,0,5,2,2,2,2,2,2,2,2,2,2,2,2,2,2,6,0,5,2,2,2,6,0,5,2,2,2,2,2,2,2,2,2,2,2,2,2,2,6,0,1,0},
        {0,1,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,0,0,0,0,0,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,1,0},
        {0,5,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,6,0}
        };

//Protótipos das funções
void ajuda(void);
void menu();
char pause();
void jogo(void);
void desMapa(int*,int map[29][45]);
void esconderCursor(void);
void irparaxy(int, int);
int podeMover(int,int,int);
void comerPilula(int,int,int*,int*,int*,int*,int*,int*,int*,int*,int*,int*,int*,int map[29][45]);
void superPilula(int,int,int*,int*,int*,int*,int*,int*,int*,int*,int*,int*,int*,int*,int*,int*,int*,int*,int*,int*,int*,int*,int*,int*,int*,int*,int*);
void marcarPontos(int,int);
void vencer(char*,int*);
void perder(char*, int*,int*,int*,int*,int*,int*,int*,int*,int*,int*,int*,int*,int*,int*,int*,int map[29][45]);
void fantAleatorio(int,int*,int*,int*,int*,int*,int*,int*,int*,int*,int*,int*,int*,int*,int*,int*,int*,int map[29][45]);

/*Função main():
    Descrição de cada parâmetro da função: Não há parametros;
    Descrição do valor de retorno: Se retornar 0 o programa é finalizado;
    Descrição da funcionalidade: Inicializar o programa;
    Finalidade das variaveis: Não há variáveis;

*/
int main(){
   menu();
   irparaxy(1,30);
   return 0;
}

/*Função ajuda():
    Descrição de cada parâmetro da função: Não há parametros;
    Descrição do valor de retorno: Não retorna nenhum valor;
    Descrição da funcionalidade: Imprime informações sobre as funcionalidades do jogo ao usuário e retorna ao menu ao pressionar qualquer tecla;
    Finalidade das variaveis: Não há variáveis;

*/
void ajuda(void){

   setlocale(LC_ALL,"");
   textcolor(12);
   printf("\n\n                        ### REGRAS DO JOGO ###\n\n");
   textcolor(14);
   printf("       O PacMan é controlado pelo jogador por meio das teclas A(Esquerda),\n\
   D(Direita), W(Cima) e S(Baixo). Com a tecla 'P' o jogador pode pausar o jogo e\n\
   com a tecla 'G' ele pode sair instantaneamente do mesmo. Ele movimenta-se continuamente\n\
   até que seja definida uma nova direção viável. Após o PacMan comer 70 e 1000 pilulas\n\
   surge uma fruta bônus. Ela fica visível por um intervalo de tempo e desaparece. Quando o\n\
   PacMan come as pílulas energéticas, os fantasmas ficam em estado de pânico e mudam para\n\
   cor azul por um intervalo de tempo e depois retornam para sua cor original, neste intervalo\n\
   de tempo eles podem ser capturados. Ele pode andar por todos os caminhos do labirinto,\n\
   exceto atravessar paredes e entrar na casa dos fantasmas. Ele consegue se tele transportar,\n\
   isto é, sair de um lado do labirinto e voltar pelo outro usando as passagens laterais.\n\
   Se colidir com um fantasma perde uma vida, se ainda tem vida(s) retorna para o ponto\n\
   inicial de partida, caso não haja mais vida(s) o jogo é encerrado. Quando um fantasma é\n\
   capturado pelo Pac Man ele retorna instantaneamente para casa dos fantasmas. O fantasma\n\
   ganha novamente o direito de voltar a caçar quando o efeito da pílula energética acaba.\n\
   O jogo termina quando o PacMan perde todas as vidas ou come todos os alimentos sem perder\n\
   todas as vidas.");
   textcolor(12);
   printf("\n\n                        ### MARCAR PONTOS ###\n\n");
   textcolor(14);
   printf("       Basta comer as pílulas, super-pílulas ou fantasmas assustados e escapar dos inimigos\n\
   (fantasmas)");
   textcolor(12);
   printf("\n\n                        ### PONTUAÇÃO ###\n\n");
   textcolor(14);
   printf("   10 pontos = A cada pílula pequena que o PacMan comer .\n\
   50 pontos =  A cada pílula grande que o PacMan comer.\n\
   200 pontos =  Para o primeiro fantasma que o PacMan capturar.\n\
   Para cada fantasma capturado no mesmo estado de pânico (cor azul) o valor da pontuação dobra.\n\
   Assim a captura do quarto fantasma renderá 1600 pontos.\n\
   500 pontos = Para cada fruta que o PacMan comer.\n");
   textcolor(12);
   printf("\n\n                        ### HISTÓRIA DO JOGO ###\n\n");
   textcolor(14);
   printf("       Pac-man é considerado um clássico da história dos videogames. Elaborado para\n\
   o console Atari 2600 no início dos anos 80, tornou-se um dos jogos mais populares do mundo.\n\
   A mecânica do game era simples: Pac-Man comia pastilhas fugindo de fantasmas em um labirinto.\n\
   O objetivo era comer todas as pastilhas sem ser alcançado pelos fantasmas, aumentando\n\
   progressivamente a dificuldade. O designer de jogos da Namco, Tohru Iwatani, idealizou\n\
   o conhecidíssimo Pac-Man em um jantar entre amigos. Sua inspiração partiu de uma pizza que\n\
   viera com uma fatia faltando. Antes de ser o Pac-Man, o personagem dos videogames se chamava\n\
   Puck-Man, porém decidiram mudar seu nome para evitar que “Puck” ganhasse uma conotação\n\
   pejorativa na língua inglesa\n\n");
   textcolor(12);
   printf("\n\n                        ### EQUIPE DE DESENVOLVIMENTO ###\n\n");
   textcolor(14);
   printf("                              - Willian Santos Moura\n");
   printf("                               - Emely Vitória Vasconcelos Albernaz Lopes\n");
   printf("                                - Beatriz Vendrame\n");
   printf("\nPressione qualquer tecla para voltar ao menu...");

   setlocale(LC_ALL,"C");
   fflush(stdin);
   getch();
   system("cls");
   menu();
}

/*Função menu():
    Descrição de cada parâmetro da função: Não há parametros;
    Descrição do valor de retorno: Não retorna nenhum valor;
    Descrição da funcionalidade: Exibe o menu de opções do jogo;
    Finalidade das variaveis:
      int opcao: Guarda a resposta digitada pelo usuário;

*/
void menu(){
   int opcao;
   clrscr();
   textcolor(14);
   printf("\n  ______        __         ______    ___          ___        __        ___      _ \n");
   printf(" |  __  |      /  \\       |  ____|  |   \\        /   |      /  \\      |   \\    | |\n");
   printf(" | |__| |     / /\\ \\      | |       | |\\ \\      / /| |     / /\\ \\     | |\\ \\   | |\n");
   printf(" |  ___ |    / /__\\ \\     | |       | | \\ \\    / / | |    / /__\\ \\    | | \\ \\  | |\n");
   printf(" | |        / _____  \\    | |       | |  \\ \\  / /  | |   / ______ \\   | |  \\ \\ | |\n");
   printf(" | |       / /      \\ \\   | |____   | |   \\ \\/ /   | |  / /      \\ \\  | |   \\ \\| |\n");
   printf(" |_|      /_/        \\_\\  |______|  |_|    \\__/    |_| /_/        \\_\\ |_|    \\___|\n");
   printf("\n");
   printf("                                  1 - JOGAR                                        \n");
   printf("                                    2 - AJUDA                                      \n");
   printf("                                      3 - SAIR                                      \n");
   printf("                                                                                   \n");
   setlocale(LC_ALL,"");
   printf("                                DIGITE A OPÇÃO DESEJADA: ");

   fflush(stdin);//Limpa o buffer de mémoria do teclado//
   scanf("%d", &opcao);
   /*Oferece as opções que podem ser executadas caso escolha alguma das alternativas  */
   switch(opcao){
   case 1:
      setlocale(LC_ALL,"C");
      system("cls");
      jogo();
      break;
   case 2:
      system("cls");
      ajuda();
      break;
   case 3:
      exit(0);
   default:
      textcolor(12);
      irparaxy(25,15);
      printf("Ops... opção incorreta, tente novamente!");
      getch();
      menu();
   }

}

/*Função jogo():
    Descrição de cada parâmetro da função: Não há parametros;
    Descrição do valor de retorno: Não retorna nenhum valor;
    Descrição da funcionalidade:É responsável por chamar todas as funções referentes ao jogo;
    Finalidade das variaveis:
      Variável map: modelo do cenário como matriz;
      VARIÁVEIS DE MOVIMENTAÇÃO DO PACMAN: relacionadas a movimentação do pac-mam;
      VARIÁVEIS DE INFORMAÇÃO AO JOGADOR: relaciondas por toda informação exibida ao jogador;
      VARIÁVEIS DOS FANTASMAS: relcionadas a movimentação aleatória dos fantasmas;
      VARIÁVEIS DE USO GERAL: são as relacionadas ao tempo de efeito das pilulas e fruta; e variáveis de objetos do cenário;

*/
void jogo(void){
   //Modelo do mapa como matriz
   /*É nele que ficam contidas todas as informações referentes ao labirinto visível ao jogador,
   como paredes, posição das pílulas, super-pilulas e etc...
   Cada número na matriz representa um elemento a ser impresso na função desMap()*/
   int map[29][45]={
        {0,3,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,4,0,3,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,4,0},
        {0,1,9,7,7,7,7,7,7,7,0,7,7,7,7,7,7,7,7,7,7,1,0,1,7,7,7,7,7,7,7,7,7,7,0,7,7,7,7,7,7,7,9,1,0},
        {0,1,7,3,2,2,2,2,2,4,7,3,2,2,2,2,2,2,2,4,7,1,0,1,7,3,2,2,2,2,2,2,2,4,7,3,2,2,2,2,2,4,7,1,0},
        {0,1,7,1,0,0,0,0,0,1,7,1,0,0,0,0,0,0,0,1,7,1,0,1,7,1,0,0,0,0,0,0,0,1,7,1,0,0,0,0,0,1,7,1,0},
        {0,1,7,5,2,2,2,2,2,6,7,5,2,2,2,2,2,2,2,6,7,5,2,6,7,5,2,2,2,2,2,2,2,6,7,5,2,2,2,2,2,6,7,1,0},
        {0,1,0,7,7,7,7,7,7,7,0,7,7,7,0,7,7,7,7,7,0,7,7,7,0,7,7,7,7,7,7,7,7,7,0,7,7,7,7,7,7,7,0,1,0},
        {0,1,7,3,2,2,2,2,2,4,7,3,2,4,7,3,2,2,2,2,2,2,2,2,2,2,2,2,2,4,7,3,2,4,7,3,2,2,2,2,2,4,7,1,0},
        {0,1,7,5,2,2,2,2,2,6,7,1,0,1,7,5,2,2,2,2,4,0,0,0,3,2,2,2,2,6,7,1,0,1,7,5,2,2,2,2,2,6,7,1,0},
        {0,1,7,7,7,7,7,7,7,7,0,1,0,1,7,7,7,7,7,7,1,0,0,0,1,7,7,7,7,7,7,1,0,1,0,7,7,7,7,7,7,7,7,1,0},
        {0,5,2,2,2,2,2,2,2,4,7,1,0,5,2,2,2,2,4,7,1,0,0,0,1,7,3,2,2,2,2,6,0,1,7,3,2,2,2,2,2,2,2,6,0},
        {0,0,0,0,0,0,0,0,0,1,7,1,0,3,2,2,2,2,6,7,5,2,2,2,6,7,5,2,2,2,2,4,0,1,7,1,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,1,7,1,0,1,7,7,7,7,7,0,7,7,7,7,7,0,7,7,7,7,7,1,0,1,7,1,0,0,0,0,0,0,0,0,0},
        {8,2,2,2,2,2,2,2,2,6,7,5,2,6,7,3,2,2,2,2,2,2,8,2,2,2,2,2,2,4,7,5,2,6,7,5,2,2,2,2,2,2,2,2,8},
        {0,7,7,7,7,7,7,7,7,7,0,7,7,7,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,7,7,7,0,7,7,7,7,7,7,7,7,7,0},
        {8,2,2,2,2,2,2,2,2,4,7,3,2,4,7,5,2,2,2,2,2,2,2,2,2,2,2,2,2,6,7,3,2,4,7,3,2,2,2,2,2,2,2,2,8},
        {0,0,0,0,0,0,0,0,0,1,7,1,0,1,0,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,0,1,0,1,7,1,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,1,7,1,0,1,7,3,2,2,2,2,2,2,2,2,2,2,2,2,2,4,7,1,0,1,7,1,0,0,0,0,0,0,0,0,0},
        {0,3,2,2,2,2,2,2,2,6,7,5,2,6,7,5,2,2,2,2,4,0,0,0,3,2,2,2,2,6,7,5,2,6,7,5,2,2,2,2,2,2,2,4,0},
        {0,1,7,7,7,7,7,7,7,7,0,7,7,7,0,7,7,7,7,7,1,0,0,0,1,7,7,7,7,7,0,7,7,7,0,7,7,7,7,7,7,7,7,1,0},
        {0,1,7,3,2,2,2,2,2,4,7,3,2,2,2,2,2,2,4,7,1,0,0,0,1,7,3,2,2,2,2,2,2,4,7,3,2,2,2,2,2,4,7,1,0},
        {0,1,7,5,2,2,2,4,0,1,7,5,2,2,2,2,2,2,6,7,5,2,2,2,6,7,5,2,2,2,2,2,2,6,7,1,0,3,2,2,2,6,7,1,0},
        {0,1,7,7,7,7,7,1,0,1,0,7,7,7,0,7,7,7,7,0,7,7,7,7,7,0,7,7,7,7,0,7,7,7,0,1,0,1,7,7,7,7,7,1,0},
        {0,5,2,2,2,4,7,1,0,1,7,3,2,4,7,3,2,2,2,2,2,2,2,2,2,2,2,2,2,4,7,3,2,4,7,1,0,1,7,3,2,2,2,6,0},
        {0,3,2,2,2,6,7,5,2,6,7,1,0,1,7,5,2,2,2,2,4,0,0,0,3,2,2,2,2,6,7,1,0,1,7,5,2,6,7,5,2,2,2,4,0},
        {0,1,7,7,7,7,0,7,7,7,7,1,0,1,7,7,7,7,7,7,1,0,0,0,1,7,7,7,7,7,7,1,0,1,7,7,7,7,0,7,7,7,7,1,0},
        {0,1,7,3,2,2,2,2,2,2,2,6,0,5,2,2,2,2,4,7,1,0,0,0,1,7,3,2,2,2,2,6,0,5,2,2,2,2,2,2,2,4,7,1,0},
        {0,1,7,5,2,2,2,2,2,2,2,2,2,2,2,2,2,2,6,7,5,2,2,2,6,7,5,2,2,2,2,2,2,2,2,2,2,2,2,2,2,6,7,1,0},
        {0,1,9,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,0,7,7,7,7,7,0,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,9,1,0},
        {0,5,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,6,0}
        };


   //VARIÁVEIS DE MOVIMENTAÇÃO DO PACMAN
   int cx=22, cy=21;//Variáveis com posição do player;
   int dir = 0;//Variável que guarda a direção do player (0=esquerda/1=cima/2=direita/3=baixo);
   char tecla;//Variável responsável por quardar a tecla pressionada pelo usuário;

   //VARIÁVEIS DE INFORMAÇÃO AO JOGADOR
   int pontos=0;//Variável que guarda os pontos do jogador.
   int vidas=3;//Variável que guarda a quantidade de vidas do jogador

   //VARIÁVEIS DOS FANTASMAS
   int fantCapturados=0;//Guarda quantos fantasmas já foram capturados pelo jogador
   //***Coordenadas***
   //Fantasma vermelho
   int codXFV=18, codYFV=13;
   //Fantasma rosa
   int codXFR=20, codYFR=13;
   //Fantasma azul
   int codXFA=22, codYFA=13;
   //Fantasma laranja
   int codXFL=24, codYFL=13;
   //***Direções***
   int dirFantA=0;//Fantasma Azul
   int dirFantL=0;//Fantasma Lanja
   int dirFantV=0;//Fantasma Vermelho
   int dirFantR=0;//Fantasma Rosa
   //***Está na "gaiola"?(0=não/1=sim)***
   int fantAGaiola=0;//Fantasma Azul está na "gaiola"?
   int fantLGaiola=0;//Fantasma Laranja está na "gaiola"?
   int fantVGaiola=0;//Fantasma Vermelho está na "gaiola"?
   int fantRGaiola=0;//Fantasma Rosa está na "gaiola"?
   //***Cor dos fantasmas***
   int azul=9;
   int rosa=13;
   int vermelho=12;
   int laranja=14;

   //VARIÁVEIS DE USO GERAL
   int durEfeitoSupP=0;//Guarda o tempo de duração do efeito da super-pílula
   /*Variável resposável por ser o contador principal do jogo.
   É através dela que fazemos os fantasmas serem mais lentos que o Pacman,
   pois o laço de movimentação dos fantasmas só é executado quando este contador é múltiplo de 4,
   diferente do laço de movimentação do Pacman que é executado quando o contador é múltiplo de 3.*/
   int contPrincipal=0;
   //***Variáveis de objetos do cenário***
   int interacaoFruta1=0, interacaoFruta2=0;//variaveis que controlam se ja ouve alguma interacao com as frutas(0=falso/1=verdadeiro)
   int fruta1=0, fruta2=0;//variaveis que controlam se as frutas estao presentes no cenario(0=falso/1=verdadeiro)
   int tempo1=0, tempo2=0;//variaveis que controlam o tempo que as frutas aparecem;
   int supPilulaOn=0;//Variável responsável por controlar quando o efeito da super-pílula é ativado.
   int tempoSupPilula=0;//Controla por quanto tempo dura o efeito da super-pílula.
   int qtdPilulas=0;//Guarda o número de pílulas presentes no cenário.

    system("start /B exe.win-amd64-3.6\\test.exe");
   srand(contPrincipal);//Inicializa a função rand() com uma "semente" para que os números gerados sejam totalmente aleatórios.
   desMapa(&qtdPilulas,map);

   /*
   É nesse primeiro while que o jogo todo roda,
   ele executa o jogo enquanto o jogador não pressiona a tecla 'g' ou 'G'.
    */
    while(tecla != 'g' && tecla != 'G' && qtdPilulas!=0){
        /*
        Esse segundo while faz com que o PacMan se mova sozinho pela tela em uma determinada direção
        enquanto o jogador não pressiona nenhuma tecla de movimento ou as tecla 'g' e 'G'.
        */
        while((tecla != 'g' && tecla != 'G') && !(tecla=kbhit())){
            contPrincipal++;
            esconderCursor();
            comerPilula(cx, cy,&pontos,&durEfeitoSupP,&interacaoFruta1,&interacaoFruta2,&fruta1,&fruta2,&tempo1,&tempo2,&supPilulaOn,&tempoSupPilula,&qtdPilulas,map);
            marcarPontos(pontos,vidas);
            vencer(&tecla,&qtdPilulas);
            superPilula(cx,cy,&pontos,&fantCapturados,&durEfeitoSupP,&supPilulaOn,&tempoSupPilula,&codXFA,&codYFA,&codXFV,&codYFV,&codXFR,&codYFR,&codXFL,&codYFL,&dirFantA,&dirFantV,&dirFantR,&dirFantL,&fantAGaiola,&fantVGaiola,&fantRGaiola,&fantLGaiola,&azul,&vermelho,&rosa,&laranja);
            fantAleatorio(contPrincipal,&codXFA,&codYFA,&codXFV,&codYFV,&codXFR,&codYFR,&codXFL,&codYFL,&dirFantA,&dirFantV,&dirFantR,&dirFantL,&azul,&vermelho,&rosa,&laranja,map);

            irparaxy(cx,cy);
            textcolor(14);
            printf("%c",PACMAN);

            /*Laço de movimentação do Pacman que é executado quando o contador é múltiplo de 3*/
            if(contPrincipal%3==0){
               /*
               Se a variável dir estiver setada em 0 (esquerda)
               então o PacMan será movido uma posição a menos em sua coordenada x.
               */
               if(dir==0 && podeMover(cx,cy,0)==1){
                  irparaxy(cx,cy);
                  printf(" ");
                  cx--;
                  textcolor(14);
                  irparaxy(cx,cy);
                  printf("%c",PACMAN);
               }
               /*
               Se a variável dir estiver setada em 1 (cima)
               então o PacMan será movido uma posição a menos em sua coordenada y.
               */
               if(dir==1 && podeMover(cx,cy,1)==1){
                  irparaxy(cx,cy);
                  printf(" ");
                  cy--;
                  textcolor(14);
                  irparaxy(cx,cy);
                  printf("%c",PACMAN);
               }
               /*
               Se a variável dir estiver setada em 2 (direita)
               então o PacMan será movido uma posição a mais em sua coordenada x.
               */
               if(dir==2 && podeMover(cx,cy,2)==1){
                  irparaxy(cx,cy);
                  printf(" ");
                  cx++;
                  textcolor(14);
                  irparaxy(cx,cy);
                  printf("%c",PACMAN);
               }
               /*
               Se a variável dir estiver setada em 3 (baixo)
               então o PacMan será movido uma posição a mais em sua coordenada y.
               */
               if(dir==3 && podeMover(cx,cy,3)==1){
                  irparaxy(cx,cy);
                  printf(" ");
                  cy++;
                  textcolor(14);
                  irparaxy(cx,cy);
                  printf("%c",PACMAN);
               }


               //Túnel PACMAN
               /*
               Se o PacMan estiver no final do "túnel" do lado direito,
               ele será movido para o início do túnel do lado esquerdo.
               */
               if(cx==44 && cy==13){
                  irparaxy(cx,cy);
                  printf(" ");
                  cx=1;
                  cy=13;
               }
               /*
               Se o PacMan estiver no final do "túnel" do lado esquerdo,
               ele será movido para o início do túnel do lado direito.
               */
               if(cx==0 && cy==13){
                  irparaxy(cx,cy);
                  printf(" ");
                  cx=44;
                  cy=13;
               }
               //Tunel Fantasmas
               /*Se o fantasma estiver no final do "túnel" do lado esquerdo/direito,
               ele será movido para o início do túnel do lado direito/esquerdo.
               */
               //Vermelho
               if(codXFV==44 && codYFV==13){
                  irparaxy(codXFV,codYFV);
                  printf(" ");
                  codXFV=1;
                  codYFV=13;
               }
               if(codXFV==0 && codYFV==13){
                  irparaxy(codXFV,codYFV);
                  printf(" ");
                  codXFV=44;
                  codYFV=13;
               }

               //Rosa
               if(codXFR==44 && codYFR==13){
                  irparaxy(codXFR,codYFR);
                  printf(" ");
                  codXFR=1;
                  codYFR=13;
               }
               if(codXFR==0 && codYFR==13){
                  irparaxy(codXFR,codYFR);
                  printf(" ");
                  codXFR=44;
                  codYFR=13;
               }

               //Azul
               if(codXFA==44 && codYFA==13){
                  irparaxy(codXFA,codYFA);
                  printf(" ");
                  codXFA=1;
                  codYFA=13;
               }
               if(codXFA==0 && codYFA==13){
                  irparaxy(codXFA,codYFA);
                  printf(" ");
                  codXFA=44;
                  codYFA=13;
               }

               //Laranja
               if(codXFL==44 && codYFL==13){
                  irparaxy(codXFL,codYFL);
                  printf(" ");
                  codXFL=1;
                  codYFL=13;
               }
               if(codXFL==0 && codYFL==13){
                  irparaxy(codXFL,codYFL);
                  printf(" ");
                  codXFL=44;
                  codYFL=13;
               }
            }
            /*Quando o contador principal atinge 100 os fantasmas saem da gaiola e andam livremente pelo labirinto*/
            if(contPrincipal==100){
                  irparaxy(codXFV,codYFV);
                  printf(" ");
                  irparaxy(codXFR,codYFR);
                  printf(" ");
                  irparaxy(codXFA,codYFA);
                  printf(" ");
                  irparaxy(codXFL,codYFL);
                  printf(" ");
                  codXFV=18;codYFV=11;dirFantV=0;
                  codXFR=20;codYFR=11;dirFantR=2;
                  codXFA=22;codYFA=11;dirFantA=2;
                  codXFL=24;codYFL=11;dirFantL=0;
               }

            /*Se o efeito da super-pílula não estiver ativo então será chamada a função perder() se tocar no fantasma*/
            if(supPilulaOn==0){
               if(cx==codXFA && cy==codYFA){cx=22;cy=21;perder(&tecla,&vidas,&cx,&cy,&codXFA,&codYFA,&codXFV,&codYFV,&codXFR,&codYFR,&codXFL,&codYFL,&dirFantA,&dirFantV,&dirFantR,&dirFantL,map);}
               if(cx==codXFL && cy==codYFL){cx=22;cy=21;perder(&tecla,&vidas,&cx,&cy,&codXFA,&codYFA,&codXFV,&codYFV,&codXFR,&codYFR,&codXFL,&codYFL,&dirFantA,&dirFantV,&dirFantR,&dirFantL,map);}
               if(cx==codXFV && cy==codYFV){cx=22;cy=21;perder(&tecla,&vidas,&cx,&cy,&codXFA,&codYFA,&codXFV,&codYFV,&codXFR,&codYFR,&codXFL,&codYFL,&dirFantA,&dirFantV,&dirFantR,&dirFantL,map);}
               if(cx==codXFR && cy==codYFR){cx=22;cy=21;perder(&tecla,&vidas,&cx,&cy,&codXFA,&codYFA,&codXFV,&codYFV,&codXFR,&codYFR,&codXFL,&codYFL,&dirFantA,&dirFantV,&dirFantR,&dirFantL,map);}
            }

            /*Essa função pausa a execução do laço durante
            o inteiro inserido em seu parâmetro em milisegundos*/
            Sleep(VELPACMAN);

        }
        /*Se a tecla pressionada pelo jogador não for 'g' nem 'G' então ela será guardada na variável tecla*/
        if(tecla!='g' && tecla!='G')tecla=getch();
        /*Se a tecla 'p' for pressiona os fantasmas e o pacman terão suas posições "congeladas" enquanto o jogador não digitar sua opção(1=voltar ao jogo)*/
        if(tecla=='p' || tecla=='P'){
            /*Se a função pause() retornar 1(Valor digitado) então o texto de pause desaparece e o jogo volta a rodar normalmente*/
            if(pause()=='p'){
               irparaxy(49,10);
               printf("                        ");
               irparaxy(49,12);
               printf("                                                     ");
               irparaxy(49,13);
               printf("                                                     ");
               tecla='m';
            }else{/*Se a função pause() retornar um valor diferente de 1 então o jogador é redirecionado para o menu principal*/
               system("cls");
               menu();
            }
        }
        if(tecla=='a' || tecla=='A')dir=0;/*Se a tecla pressionada for 'a' ou 'A' então a variável direção ganhará 0 (esquerda)*/
        if(tecla=='w' || tecla=='W')dir=1;/*Se a tecla pressionada for 'w' ou 'W' então a variável direção ganhará 1 (cima)*/
        if(tecla=='d' || tecla=='D')dir=2;/*Se a tecla pressionada for 'd' ou 'D' então a variável direção ganhará 2 (direita)*/
        if(tecla=='s' || tecla=='S')dir=3;/*Se a tecla pressionada for 's' ou 'S' então a variável direção ganhará 3 (baixo)*/
    }
}

/*Função pause():
    Descrição de cada parâmetro da função: Não há parametros;
    Descrição do valor de retorno: Retorna a tecla pressionada pelo usuário;
    Descrição da funcionalidade:É responsável por imprimir um aviso ao jogador de que o jogo está pausado,
    mostrar as opções disponíveis e retornar a opção digitada pelo usuário;
    Finalidade das variaveis:
      char opcao: guarda a opção selecionado pelo usuário;
*/
char pause(void){
   int opcao;
   irparaxy(49,10);
   textcolor(12);
   printf("JOGO PAUSADO");
   textcolor(14);
   irparaxy(49,12);
   printf("Pressione 'P' novamente para voltar ao jogo");
   irparaxy(49,13);
   printf("ou qualquer outra tecla para voltar ao menu...");
   fflush(stdin);
   //scanf("%d", &opcao);
   opcao=getch();
   return opcao;


}

/*Função desMapa():
    Descrição de cada parâmetro da função:
      int *qtdPilulas: informa a quantidade de pílulas presentes no labirinto para que a cada pílula impressa essa variável seja incrementada;
      int map[][]: passa a matriz map para a função;
    Descrição do valor de retorno: Não retorna nenhum valor;
    Descrição da funcionalidade: Desenha o cenário principal do jogo;

    Finalidade das variaveis:
    x: Um numero inteiro que controla as linhas do cenário;
    y: Um numero inteiro que controla as colunas do cenário;
*/
void desMapa(int *qtdPilulas,int map[29][45]){
   int x,y;
    /*
     1ºfor: Limita as linhas do cenário, de 0 até 29;
    */
    for (x=0; x<29;x++){
        /*
         2ºfor: Limita as colunas do cenàrio, de 0 até 45;
        */
        for (y=0; y<45; y++){
            if(map[x][y]== CHAO){ // Se na posição [x,y] do vetor for igual a CHAO(0), imprime o espaço em branco;
                printf(" ");
            }
            if(map[x][y]== PAREDEVT){ // Se na posição [x,y] do vetor for igual a PAREDEVT(1), imprime o caractere 186 da tabela ASCII;
                textcolor(9);
                printf("%c", 186);
            }
            if(map[x][y]== PAREDEHR){ // Se na posição [x,y] do vetor for igual a PAREDEHR(2), imprime o caractere 205 da tabela ASCII;
                textcolor(9);
                printf("%c", 205);
            }
            if(map[x][y]== CANTOSUPESQ){ // Se na posição [x,y] do vetor for igual a CANTOSUPESQ(3), imprime o caractere 201 da tabela ASCII;
                textcolor(9);
                printf("%c", 201);
            }
            if(map[x][y]== CANTOSUPDIR){ // Se na posição [x,y] do vetor for igual a CANTOSUPDIR(4), imprime o caractere 187 da tabela ASCII;
                textcolor(9);
                printf("%c", 187);
            }
            if(map[x][y]== CANTOINFESQ){ // Se na posição [x,y] do vetor for igual a CANTOINFESQ(5), imprime o caractere 200 da tabela ASCII;
                textcolor(9);
                printf("%c", 200);
            }
            if(map[x][y]== CANTOINFDIR){ // Se na posição [x,y] do vetor for igual a CANTOINFDIR(6), imprime o caractere 188 da tabela ASCII;
                textcolor(9);
                printf("%c", 188);
            }
            if(map[x][y]== PILULA){ // Se na posição [x,y] do vetor for igual a PILULA(7), imprime o caractere 250 da tabela ASCII e incrementa *qtdPilulas;
                textcolor(14);
                printf("%c", 250);
                *qtdPilulas=*qtdPilulas+1;
            }
            if(map[x][y]== 8){ //Restrição para evitar que se movimente fora do labirinto;
                printf(" ");
            }
            if(map[x][y]== SUPPILULA){ // Se na posição [x,y] do vetor for igual a SUPPILULA(9), imprime o caractere 254 da tabela ASCII e incrementa *qtdPilulas;;
                textcolor(14);
                printf("%c", 254);
                *qtdPilulas=*qtdPilulas+1;
            }


        }
        printf("\n");
    }
}

/*Função irparaxy():
    Descrição de cada parâmetro da função:
        Inteiro x: Define a coordenada da linha do console;
        Inteiro y: Define a coordenada da coluna do console;
    Descrição do valor de retorno: Não retorna nenhum valor;
    Descrição da funcionalidade: Posiciona o cursor nas coordenadas passadas pelo parâmetro;

*/
void irparaxy(int x, int y){
    COORD pos={x,y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

/*Função esconderCursor():
    Descrição de cada parâmetro da função: Não há parâmetro;
    Descrição do valor de retorno: Não retorna nenhum valor;
    Descrição da funcionalidade: Esconde o cursor do console;
*/
void esconderCursor(void){
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}

/*Função podeMover():
    Descrição de cada parâmetro da função:
      int x: coordenada x utilizada para saber se o "objeto" poderá se mover ou não na direção d;
      int y: coordenada y utilizada para saber se o "objeto" poderá se mover ou não na direção d;
      int d: direção em que o "objeto" estará se movendo
    Descrição do valor de retorno: Retorna um valor inteiro binário;
    Descrição da funcionalidade: Retorna um valor inteiro responsável por informar se um "objeto"
    (cujo as coordenadas e direção são passadas por parâmetro) pode ou não se mover (0=falso/1=verdadeiro);
*/
int podeMover(int x, int y, int d){
    int c=1;//variável responsável por guardar a condição verdadeiro ou falso (0/1)

    //será atribuído 0 (falso) à c se o objeto estiver se movendo para a esquerda (dir==0) e 1 posição a sua frente houver algum tipo de parede
    if(d==0 && (mapInt[y][x-1]==PAREDEHR || mapInt[y][x-1]==PAREDEVT || mapInt[y][x-1]==CANTOINFDIR || mapInt[y][x-1]==CANTOINFESQ || mapInt[y][x-1]==CANTOSUPDIR || mapInt[y][x-1]==CANTOSUPESQ || mapInt[y][x-1]==15)){
        c=0;
    }
    //será atribuído 0 (falso) à c se o objeto estiver se movendo para cima (dir==1) e 1 posição a sua frente houver algum tipo de parede
    if(d==1 && (mapInt[y-1][x]==PAREDEHR || mapInt[y-1][x]==PAREDEVT || mapInt[y-1][x]==CANTOINFDIR || mapInt[y-1][x]==CANTOINFESQ || mapInt[y-1][x]==CANTOSUPDIR || mapInt[y-1][x]==CANTOSUPESQ || mapInt[y-1][x]==15)){
        c=0;
    }
    //será atribuído 0 (falso) à c se o objeto estiver se movendo para a direita (dir==2) e 1 posição a sua frente houver algum tipo de parede
    if(d==2 && (mapInt[y][x+1]==PAREDEHR || mapInt[y][x+1]==PAREDEVT || mapInt[y][x+1]==CANTOINFDIR || mapInt[y][x+1]==CANTOINFESQ || mapInt[y][x+1]==CANTOSUPDIR || mapInt[y][x+1]==CANTOSUPESQ || mapInt[y][x+1]==15)){
        c=0;
    }
    //será atribuído 0 (falso) à c se o objeto estiver se movendo para baixo (dir==3) e 1 posição a sua frente houver algum tipo de parede
    if(d==3 && (mapInt[y+1][x]==PAREDEHR || mapInt[y+1][x]==PAREDEVT || mapInt[y+1][x]==CANTOINFDIR || mapInt[y+1][x]==CANTOINFESQ || mapInt[y+1][x]==CANTOSUPDIR || mapInt[y+1][x]==CANTOSUPESQ || mapInt[y+1][x]==15)){
        c=0;
    }
    return c;
}

/*Função comerPilula():
    Descrição de cada parâmetro da função: É passado por parâmetro (por valor/por referência) todas as variáveis presente na função jogo que são utilizadas nessa função;
    Descrição do valor de retorno: Não retorna nenhum valor;
    Descrição da funcionalidade: Após o pacman passar sobre a pilula, super pilula ou fruta, ele "apaga-os" da tela.
    E acrescenta 10, 50 ou 500, respectivamente, à variável pontos. A função também controla quando a fruta aparece
    ou desaparece do cenário;
*/
void comerPilula(int cx,int cy,int *pontos,int *durEf,int *interacaoFruta1,int *interacaoFruta2,int *fruta1,int *fruta2,int *tempo1,int *tempo2,int *supPilulaOn,int *tempoSupPilula, int *qtdPilulas,int map[29][45]){
    //PÍLULAS
    /*
    Se na posição atual do PacMan houver uma pílula, será adicionados 10 pontos ao jogador
    e a pílula será apagada da matriz map.
    */
    if(map[cy][cx]==PILULA){
        *pontos +=10;
        map[cy][cx]=CHAO;
        printf("\a");//beep
        *qtdPilulas=*qtdPilulas-1;
    }
    /*
    Se na posição atual do PacMan houver uma super-pílula, será adicionados 50 pontos ao jogador,
    a super-pílula será apagada da matriz map e a variável supPililaOn ganhará 1 como nível lógico (verdadeiro/ativado).
    */
    if(map[cy][cx]==SUPPILULA){
        *pontos +=50;
        map[cy][cx]=CHAO;
        printf("%c", 7);//beep
        *qtdPilulas=*qtdPilulas-1;
        if((*supPilulaOn=0)){
         *durEf=DURSUPPIL;
         *supPilulaOn=1;
         }else if((*supPilulaOn=1)){*durEf=*durEf+DURSUPPIL;}

    }

    //FRUTAS
    /*
    Se a quantidade de pontos do jogador for igual ou superior a 70, se a primeira fruta não estiver no cenário
    e se o jogador ainda não tiver interagido com a primeira fruta então a primeira fruta aparecerá no cenário
    */
    if(*pontos>=70 && *fruta1==0 && *interacaoFruta1==0){
        textcolor(12);
        irparaxy(22,15);
        printf("%c", 14);
        *fruta1 = 1;
    }
    /*
    Se a quantidade de pontos do jogador for igual ou superior a 1000, se a segunda fruta não estiver no cenário
    e se o jogador ainda não tiver interagido com a segunda fruta então a segunda fruta aparecerá no cenário
    */
    if(*pontos>=1000 && *fruta2==0 && *interacaoFruta2==0){
        textcolor(12);
        irparaxy(22,21);
        printf("%c", 14);
        *fruta2=1;
    }
    //Se a primeira fruta estiver no cenário então tempo1 será incrementado
    if(*fruta1==1){
        *tempo1=*tempo1+1;
    }
    //Se a segunda fruta estiver no cenário então tempo2 será incrementado
    if(*fruta2==1){
        *tempo2=*tempo2+1;
    }
    //Se tempo1=50 então a primeira fruta desaparecerá do cenário
    if(*tempo1==200){
        irparaxy(22,15);
        printf(" ");
        *fruta1=0;
        *interacaoFruta1=1;
        *tempo1=0;
    }
    //Se tempo2=50 então a segunda fruta desaparecerá do cenário
    if(*tempo2==200){
        irparaxy(22,21);
        printf(" ");
        *fruta2=0;
        *interacaoFruta2=1;
        *tempo2=0;
    }
    //Se o PacMan passar "por cima" da primeira fruta serão adicionados 500 pontos ao jogador e a fruta será apagada do cenário
    if(cx==22 && cy==15 && *fruta1==1){
        *pontos +=500;
        printf("%c", 7);//beep
        *fruta1=0;
        *interacaoFruta1=1;
        *tempo1=0;
    }
    //Se o PacMan passar "por cima" da segunda fruta serão adicionados 500 pontos ao jogador e a fruta será apagada do cenário
    if(cx==22 && cy==21 && *fruta2==1){
        *pontos +=500;
        printf("%c", 7);//beep
        *fruta2=0;
        *interacaoFruta2=1;
        *tempo2=0;
    }
}

/*Função superPilula():
    Descrição de cada parâmetro da função: É passado por parâmetro (por valor/por referência) todas as variáveis presente na função jogo que são utilizadas nessa função;
    Descrição do valor de retorno: Não retorna nenhum valor;
    Descrição da funcionalidade: Se o efeito da super-pílula for ativado (supPilulaOn=1) todos os fantasmas ficam azuis e
    os fantasmas são mandados instântaneamente para a "gaiola".
*/
void superPilula(int cx, int cy, int *pontos, int *fantCapturados, int *durEf,int *supPilulaOn,int *tempoSupPilula,int*codXFA,int*codYFA,int*codXFV,int*codYFV,int*codXFR,int*codYFR,int*codXFL,int*codYFL,int*dirFantA,int*dirFantV,int*dirFantR,int*dirFantL,int*fantAGaiola,int*fantVGaiola,int*fantRGaiola,int*fantLGaiola,int*azul,int*vermelho,int*rosa,int*laranja){
   /*Se o efeito a variável supPilulaOn estiver setada em 1 então tempoSupPilula será incrementado,
   a cor de todos os fantasmas passa a ser azul e se o PacMan passar por cima de algum fantasma ele será movido para a "gaiola"*/
   if(*supPilulaOn==1){
      *tempoSupPilula=*tempoSupPilula+1;
      *rosa=*azul;
      *vermelho=*azul;
      *laranja=*azul;
      //Se a posição do PacMan for a mesma do fatasma azul então o fantasma será movido para a "gaiola" e sua direção será 0.
      if(cx==*codXFA && cy==*codYFA){
         *codXFA=20;
         *codYFA=13;
         *dirFantA=0;
         *fantAGaiola=1;
         *fantCapturados=*fantCapturados+1;
         *pontos = *pontos + (pow(2,*fantCapturados))*100;
      }
      //Se a posição do PacMan for a mesma do fatasma laranja então o fantasma será movido para a "gaiola" e sua direção será 2.
      if(cx==*codXFL && cy==*codYFL){
         *codXFL=20;
         *codYFL=13;
         *dirFantL=2;
         *fantLGaiola=1;
         *fantCapturados=*fantCapturados+1;
         *pontos = *pontos + (pow(2,*fantCapturados))*100;
      }
      //Se a posição do PacMan for a mesma do fatasma vermelho então o fantasma será movido para a "gaiola" e sua direção será 2.
      if(cx==*codXFV && cy==*codYFV){
         *codXFV=20;
         *codYFV=13;
         *dirFantV=2;
         *fantVGaiola=1;
         *fantCapturados=*fantCapturados+1;
         *pontos = *pontos + (pow(2,*fantCapturados))*100;
      }
      //Se a posição do PacMan for a mesma do fatasma rosa então o fantasma será movido para a "gaiola" e sua direção será 0.
      if(cx==*codXFR && cy==*codYFR){
         *codXFR=20;
         *codYFR=13;
         *dirFantR=0;
         *fantRGaiola=1;
         *fantCapturados=*fantCapturados+1;
         *pontos = *pontos + (pow(2,*fantCapturados))*100;
      }
   }
   /*Se tempoSupPilula for igual a 200 então a variável supPilulaOn será setada em 0,
   todos os fantasmas voltam a ter suas cores originais e tempoSupPilula é zerado*/
   if(*tempoSupPilula==*durEf){
      *durEf=0;
      *supPilulaOn=0;
      *azul=9;
      *laranja=14;
      *rosa=13;
      *vermelho=12;
      *tempoSupPilula=0;
      //Se o fantasma azul estiver na gaiola, sairá quando tempoSupPilula for igual a 200.
      if(*fantAGaiola==1){
         irparaxy(*codXFA,*codYFA);
         printf(" ");
         *codXFA=18;
         *codYFA=11;
         *dirFantA=0;
         *fantAGaiola=0;
      }
      //Se o fantasma laranja estiver na gaiola, sairá quando tempoSupPilula for igual a 200.
      if(*fantLGaiola==1){
         irparaxy(*codXFL,*codYFL);
         printf(" ");
         *codXFL=20;
         *codYFL=11;
         *dirFantL=2;
         *fantLGaiola=0;
      }
      //Se o fantasma vermelho estiver na gaiola, sairá quando tempoSupPilula for igual a 200.
      if(*fantVGaiola==1){
         irparaxy(*codXFV,*codYFV);
         printf(" ");
         *codXFV=22;
         *codYFV=11;
         *dirFantV=2;
         *fantVGaiola=0;
      }
      //Se o fantasma rosa estiver na gaiola, sairá quando tempoSupPilula for igual a 200.
      if(*fantRGaiola==1){
         irparaxy(*codXFR,*codYFR);
         printf(" ");
         *codXFR=24;
         *codYFR=11;
         *dirFantR=0;
         *fantRGaiola=0;
      }
   }
}

/*Função marcarPontos():
    Descrição de cada parâmetro da função: É passado por parâmetro (por valor) todas as variáveis presente na função jogo que são utilizadas nessa função;
    Descrição do valor de retorno: Não retorna nenhum valor;
    Descrição da funcionalidade: Imprime os pontos do jogador e suas vidas na tela;
*/
void marcarPontos(int pontos, int vidas){
    int i;
    textcolor(10);
    irparaxy(1,29);
    printf("Pontos: %d", pontos);

    irparaxy(1,30);
    textcolor(12);
    printf("%c %c %c", 2,2,2);

    irparaxy(1,30);
    //Imprime as vidas que o PacMan ainda tem em amarelo e as vidas perdidas em vermelho
    for(i=0;i<vidas;i++){
         textcolor(14);
         printf("%c ", 2);
    }


}

/*Função vencer():
    Descrição de cada parâmetro da função: É passado por parâmetro (por referência) todas as variáveis presente na função jogo que são utilizadas nessa função;
    Descrição do valor de retorno: Não retorna nenhum valor;
    Descrição da funcionalidade: Exibe um texto na tela após o jogador ter comido todas as pílulas;
*/
void vencer(char *tecla,int *qtdPilulas){
   /*Se o número de pílulas no cenário for igual à zero exibe "VOCE VENCEU" no centro da tela*/
   if(*qtdPilulas==0){
      system("color 9");//função utilizada para mudar a cor de todos os caracteres da tela de uma só vez.
      irparaxy(17,15);
      textcolor(14);
      printf("VOCE VENCEU!!!");
      irparaxy(1,16);
      printf("Pressione qualquer tecla para voltar ao menu...");
      irparaxy(1,33);
      getch();
      fflush(stdin);
      system("cls");
      menu();
   }
}

/*Função perder():
    Descrição de cada parâmetro da função:É passado por parâmetro (por referência) todas as variáveis presente na função jogo que são utilizadas nessa função;
    Descrição do valor de retorno: Não retorna nenhum valor;
    Descrição da funcionalidade: Tira uma vida se o PacMan ainda tiver alguma, ou exibe VOCE PERDEU se o número de vidas for igual à zero, além de mover o pacman e os fantasmas para suas posições iniciais;
*/
void perder(char *tecla, int *vidas, int *cx, int *cy,int*codXFA,int*codYFA,int*codXFV,int*codYFV,int*codXFR,int*codYFR,int*codXFL,int*codYFL,int*dirFantA,int*dirFantV,int*dirFantR,int*dirFantL,int map[29][45]){

   //Se vidas for diferente de 0, perderá uma.
   if(*vidas>0){
      *vidas= *vidas-1;
      //Fantasma Vermelho
      irparaxy(*codXFV,*codYFV);
      if(map[*codYFV][*codXFV]==PILULA){
         textcolor(14);
         printf("%c", 250);
      }else if(map[*codYFV][*codXFV]==SUPPILULA){
         textcolor(14);
         printf("%c", 254);
      }else if(map[*codYFV][*codXFV]==CHAO){
         printf(" ");
      }
      //Fantasma Rosa
      irparaxy(*codXFR,*codYFR);
      if(map[*codYFR][*codXFR]==PILULA){
         textcolor(14);
         printf("%c", 250);
      }else if(map[*codYFR][*codXFR]==SUPPILULA){
         textcolor(14);
         printf("%c", 254);
      }else if(map[*codYFR][*codXFR]==CHAO){
         printf(" ");
      }
      //Fantasma Azul
      irparaxy(*codXFA,*codYFA);
      if(map[*codYFA][*codXFA]==PILULA){
         textcolor(14);
         printf("%c", 250);
      }else if(map[*codYFA][*codXFA]==SUPPILULA){
         textcolor(14);
         printf("%c", 254);
      }else if(map[*codYFA][*codXFA]==CHAO){
         printf(" ");
      }
      //Fantasma Laranja
      irparaxy(*codXFL,*codYFL);
      if(map[*codYFL][*codXFL]==PILULA){
         textcolor(14);
         printf("%c", 250);
      }else if(map[*codYFL][*codXFL]==SUPPILULA){
         textcolor(14);
         printf("%c", 254);
      }else if(map[*codYFL][*codXFL]==CHAO){
            printf(" ");
      }
      *codXFV=18;*codYFV=11;*dirFantV=0;//Fantasma Vermelho
      *codXFR=20;*codYFR=11;*dirFantR=2;//Fantasma Rosa
      *codXFA=22;*codYFA=11;*dirFantA=2;//Fantasma Azul
      *codXFL=24;*codYFL=11;*dirFantL=0;//Fantasma Laranja
      //PacMan
      irparaxy(*cx,*cy);
      printf(" ");
      *cx=22; *cy=21;
   }

   //Se vidas for igual a 0 exibe VOCE PERDEU na tela.
   if(*vidas==0){
      system("color 4");//função utilizada para mudar a cor de todos os caracteres da tela de uma só vez.
      irparaxy(15,15);
      textcolor(14);
      printf("VOCE PERDEU!!!");
      irparaxy(10,17);
      printf("Pressione qualquer tecla para voltar ao menu...");
      getch();
      fflush(stdin);
      system("cls");
      menu();

   }
}

/*Função fantAleatorio():
    Descrição de cada parâmetro da função: É passado por parâmetro (por valor/por referência) todas as variáveis presente na função jogo que são utilizadas nessa função;
    Descrição do valor de retorno: Não retorna nenhum valor;
    Descrição da funcionalidade:Dar vida aos fantasmas fazendo eles se moverem aleatóriamente pelo labirinto;
*/
void fantAleatorio(int cont,int*codXFA,int*codYFA,int*codXFV,int*codYFV,int*codXFR,int*codYFR,int*codXFL,int*codYFL,int*dirFantA,int*dirFantV,int*dirFantR,int*dirFantL,int*azul,int*vermelho,int*rosa,int*laranja,int map[29][45]){
   /*Laço de movimentação dos fantasmas que é executado quando o contador é múltiplo de 4*/
   if(cont%4==0){
      //Fantasma azul
      /*Se o fantasma azul estiver em uma intersecção então sua direção será "randomizada"*/
      if(mapInt[*codYFA][*codXFA]==INTERS){
         *dirFantA=rand()%4;
      }

      //Se a direção do fantasma for 0 e ele poder se mover nessa direção então ele andará uma posição para lá.
      if(*dirFantA==0 && podeMover(*codXFA, *codYFA, 0)==1){
         irparaxy(*codXFA, *codYFA);
         if(map[*codYFA][*codXFA]==PILULA){
            textcolor(14);
            printf("%c", 250);
         }else if(map[*codYFA][*codXFA]==SUPPILULA){
            textcolor(14);
            printf("%c", 254);
         }else if(map[*codYFA][*codXFA]==CHAO){
            printf(" ");
         }
         *codXFA=*codXFA-1;
         irparaxy(*codXFA, *codYFA);
         textcolor(*azul);
         printf("%c", FANTASMAS);
      }

      //Se a direção do fantasma for 1 e ele poder se mover nessa direção então ele andará uma posição para lá.
      if(*dirFantA==1 && podeMover(*codXFA, *codYFA, 1)==1){
         irparaxy(*codXFA, *codYFA);
         if(map[*codYFA][*codXFA]==PILULA){
            textcolor(14);
            printf("%c", 250);
         }else if(map[*codYFA][*codXFA]==SUPPILULA){
            textcolor(14);
            printf("%c", 254);
         }else if(map[*codYFA][*codXFA]==CHAO){
            printf(" ");
         }
         *codYFA=*codYFA-1;
         irparaxy(*codXFA, *codYFA);
         textcolor(*azul);
         printf("%c", FANTASMAS);
      }

      //Se a direção do fantasma for 2 e ele poder se mover nessa direção então ele andará uma posição para lá.
      if(*dirFantA==2 && podeMover(*codXFA, *codYFA, 2)==1){
         irparaxy(*codXFA, *codYFA);
         if(map[*codYFA][*codXFA]==PILULA){
            textcolor(14);
         printf("%c", 250);
         }else if(map[*codYFA][*codXFA]==SUPPILULA){
            textcolor(14);
            printf("%c", 254);
         }else if(map[*codYFA][*codXFA]==CHAO){
            printf(" ");
         }
         *codXFA=*codXFA+1;
         irparaxy(*codXFA, *codYFA);
         textcolor(*azul);
         printf("%c", FANTASMAS);
      }

      //Se a direção do fantasma for 3 e ele poder se mover nessa direção então ele andará uma posição para lá.
      if(*dirFantA==3 && podeMover(*codXFA, *codYFA, 3)==1){
         irparaxy(*codXFA, *codYFA);
         if(map[*codYFA][*codXFA]==PILULA){
            textcolor(14);
            printf("%c", 250);
         }else if(map[*codYFA][*codXFA]==SUPPILULA){
            textcolor(14);
            printf("%c", 254);
         }else if(map[*codYFA][*codXFA]==CHAO){
            printf(" ");
         }
         *codYFA=*codYFA+1;
         irparaxy(*codXFA, *codYFA);
         textcolor(*azul);
         printf("%c", FANTASMAS);
      }


      //Fantasma Laranja
      /*Se o fantasma laranja estiver em uma intersecção então sua direção será "randomizada"*/
      if(mapInt[*codYFL][*codXFL]==INTERS){
         *dirFantL=rand()%4;
      }

      //Se a direção do fantasma for 0 e ele poder se mover nessa direção então ele andará uma posição para lá.
      if(*dirFantL==0 && podeMover(*codXFL, *codYFL, 0)==1){
         irparaxy(*codXFL, *codYFL);
         if(map[*codYFL][*codXFL]==PILULA){
            textcolor(14);
            printf("%c", 250);
         }else if(map[*codYFL][*codXFL]==SUPPILULA){
            textcolor(14);
            printf("%c", 254);
         }else if(map[*codYFL][*codXFL]==CHAO){
            printf(" ");
         }
         *codXFL=*codXFL-1;
         irparaxy(*codXFL, *codYFL);
         textcolor(*laranja);
         printf("%c", FANTASMAS);
      }

      //Se a direção do fantasma for 1 e ele poder se mover nessa direção então ele andará uma posição para lá.
      if(*dirFantL==1 && podeMover(*codXFL, *codYFL, 1)==1){
         irparaxy(*codXFL, *codYFL);
         if(map[*codYFL][*codXFL]==PILULA){
            textcolor(14);
            printf("%c", 250);
         }else if(map[*codYFL][*codXFL]==SUPPILULA){
            textcolor(14);
            printf("%c", 254);
         }else if(map[*codYFL][*codXFL]==CHAO){
            printf(" ");
         }
         *codYFL=*codYFL-1;
         irparaxy(*codXFL, *codYFL);
         textcolor(*laranja);
         printf("%c", FANTASMAS);
      }

      //Se a direção do fantasma for 2 e ele poder se mover nessa direção então ele andará uma posição para lá.
      if(*dirFantL==2 && podeMover(*codXFL, *codYFL, 2)==1){
         irparaxy(*codXFL, *codYFL);
         if(map[*codYFL][*codXFL]==PILULA){
            textcolor(14);
         printf("%c", 250);
         }else if(map[*codYFL][*codXFL]==SUPPILULA){
            textcolor(14);
            printf("%c", 254);
         }else if(map[*codYFL][*codXFL]==CHAO){
            printf(" ");
         }
         *codXFL=*codXFL+1;
         irparaxy(*codXFL, *codYFL);
         textcolor(*laranja);
         printf("%c", FANTASMAS);
      }

      //Se a direção do fantasma for 3 e ele poder se mover nessa direção então ele andará uma posição para lá.
      if(*dirFantL==3 && podeMover(*codXFL, *codYFL, 3)==1){
         irparaxy(*codXFL, *codYFL);
         if(map[*codYFL][*codXFL]==PILULA){
            textcolor(14);
            printf("%c", 250);
         }else if(map[*codYFL][*codXFL]==SUPPILULA){
            textcolor(14);
            printf("%c", 254);
         }else if(map[*codYFL][*codXFL]==CHAO){
            printf(" ");
         }
         *codYFL=*codYFL+1;
         irparaxy(*codXFL, *codYFL);
         textcolor(*laranja);
         printf("%c", FANTASMAS);
      }

   //Fantasma Vermelho
   /*Se o fantasma vermelho estiver em uma intersecção então sua direção será "randomizada"*/
      if(mapInt[*codYFV][*codXFV]==INTERS){
         *dirFantV=rand()%4;
      }

      //Se a direção do fantasma for 0 e ele poder se mover nessa direção então ele andará uma posição para lá.
      if(*dirFantV==0 && podeMover(*codXFV, *codYFV, 0)==1){
         irparaxy(*codXFV, *codYFV);
         if(map[*codYFV][*codXFV]==PILULA){
            textcolor(14);
            printf("%c", 250);
         }else if(map[*codYFV][*codXFV]==SUPPILULA){
            textcolor(14);
            printf("%c", 254);
         }else if(map[*codYFV][*codXFV]==CHAO){
            printf(" ");
         }
         *codXFV=*codXFV-1;
         irparaxy(*codXFV, *codYFV);
         textcolor(*vermelho);
         printf("%c", FANTASMAS);
      }

      //Se a direção do fantasma for 1 e ele poder se mover nessa direção então ele andará uma posição para lá.
      if(*dirFantV==1 && podeMover(*codXFV, *codYFV, 1)==1){
         irparaxy(*codXFV, *codYFV);
         if(map[*codYFV][*codXFV]==PILULA){
            textcolor(14);
            printf("%c", 250);
         }else if(map[*codYFV][*codXFV]==SUPPILULA){
            textcolor(14);
            printf("%c", 254);
         }else if(map[*codYFV][*codXFV]==CHAO){
            printf(" ");
         }
         *codYFV=*codYFV-1;
         irparaxy(*codXFV, *codYFV);
         textcolor(*vermelho);
         printf("%c", FANTASMAS);
      }

      //Se a direção do fantasma for 2 e ele poder se mover nessa direção então ele andará uma posição para lá.
      if(*dirFantV==2 && podeMover(*codXFV, *codYFV, 2)==1){
         irparaxy(*codXFV, *codYFV);
         if(map[*codYFV][*codXFV]==PILULA){
            textcolor(14);
         printf("%c", 250);
         }else if(map[*codYFV][*codXFV]==SUPPILULA){
            textcolor(14);
            printf("%c", 254);
         }else if(map[*codYFV][*codXFV]==CHAO){
            printf(" ");
         }
         *codXFV=*codXFV+1;
         irparaxy(*codXFV, *codYFV);
         textcolor(*vermelho);
         printf("%c", FANTASMAS);
      }

      //Se a direção do fantasma for 3 e ele poder se mover nessa direção então ele andará uma posição para lá.
      if(*dirFantV==3 && podeMover(*codXFV, *codYFV, 3)==1){
         irparaxy(*codXFV, *codYFV);
         if(map[*codYFV][*codXFV]==PILULA){
            textcolor(14);
            printf("%c", 250);
         }else if(map[*codYFV][*codXFV]==SUPPILULA){
            textcolor(14);
            printf("%c", 254);
         }else if(map[*codYFV][*codXFV]==CHAO){
            printf(" ");
         }
         *codYFV=*codYFV+1;
         irparaxy(*codXFV, *codYFV);
         textcolor(*vermelho);
         printf("%c", FANTASMAS);
      }
      //Fantasma Rosa
      /*Se o fantasma rosa estiver em uma intersecção então sua direção será "randomizada"*/
      if(mapInt[*codYFR][*codXFR]==INTERS){
         *dirFantR=rand()%4;
      }

      //Se a direção do fantasma for 0 e ele poder se mover nessa direção então ele andará uma posição para lá.
      if(*dirFantR==0 && podeMover(*codXFR, *codYFR, 0)==1){
         irparaxy(*codXFR, *codYFR);
         if(map[*codYFR][*codXFR]==PILULA){
            textcolor(14);
            printf("%c", 250);
         }else if(map[*codYFR][*codXFR]==SUPPILULA){
            textcolor(14);
            printf("%c", 254);
         }else if(map[*codYFR][*codXFR]==CHAO){
            printf(" ");
         }
         *codXFR=*codXFR-1;
         irparaxy(*codXFR, *codYFR);
         textcolor(*rosa);
         printf("%c", FANTASMAS);
      }

      //Se a direção do fantasma for 1 e ele poder se mover nessa direção então ele andará uma posição para lá.
      if(*dirFantR==1 && podeMover(*codXFR, *codYFR, 1)==1){
         irparaxy(*codXFR, *codYFR);
         if(map[*codYFR][*codXFR]==PILULA){
            textcolor(14);
            printf("%c", 250);
         }else if(map[*codYFR][*codXFR]==SUPPILULA){
            textcolor(14);
            printf("%c", 254);
         }else if(map[*codYFR][*codXFR]==CHAO){
            printf(" ");
         }
         *codYFR=*codYFR-1;
         irparaxy(*codXFR, *codYFR);
         textcolor(*rosa);
         printf("%c", FANTASMAS);
      }

      //Se a direção do fantasma for 2 e ele poder se mover nessa direção então ele andará uma posição para lá.
      if(*dirFantR==2 && podeMover(*codXFR, *codYFR, 2)==1){
         irparaxy(*codXFR, *codYFR);
         if(map[*codYFR][*codXFR]==PILULA){
            textcolor(14);
         printf("%c", 250);
         }else if(map[*codYFR][*codXFR]==SUPPILULA){
            textcolor(14);
            printf("%c", 254);
         }else if(map[*codYFR][*codXFR]==CHAO){
            printf(" ");
         }
         *codXFR=*codXFR+1;
         irparaxy(*codXFR, *codYFR);
         textcolor(*rosa);
         printf("%c", FANTASMAS);
      }

      //Se a direção do fantasma for 3 e ele poder se mover nessa direção então ele andará uma posição para lá.
      if(*dirFantR==3 && podeMover(*codXFR, *codYFR, 3)==1){
         irparaxy(*codXFR, *codYFR);
         if(map[*codYFR][*codXFR]==PILULA){
            textcolor(14);
            printf("%c", 250);
         }else if(map[*codYFR][*codXFR]==SUPPILULA){
            textcolor(14);
            printf("%c", 254);
         }else if(map[*codYFR][*codXFR]==CHAO){
            printf(" ");
         }
         *codYFR=*codYFR+1;
         irparaxy(*codXFR, *codYFR);
         textcolor(*rosa);
         printf("%c", FANTASMAS);
      }
   }
}

//BIBLIOTECAS
#include <iostream>
#include <time.h>				//NECESSÁRIA PARA O FUNCIONAMENTO DE NÚMEROS RANDÔMICOS - SRAND
#include <windows.h>			//NECESSÁRIA PARA O FUNCIONAMENTO DA FUNÇÃO - GOTOXY
#include <conio.h>				//NECESSÁRIA PARA O FUNCIONAMENTO DAS FUNÇÕES DE TEXTCOLOR E TEXTBACKGROUND
#include <string.h>				//NECESSÁRIA PARA O FUNCIONAMENTO DAS FUNÇÕES DE STRING

//INÍCIO DAS DEFINES - VISUAL
/////////////////////////////////
#define CORMODIFICADA YELLOW	//COR DO TEMA
#define CORPADRAO BLACK			//COR PADRÃO DE FUNDO
#define COLOR_BASE YELLOW	//DEFINE A COR DA FONTE DAS CELULAS QUE PERMITIRÃO ALTERAÇÕES
#define COLOR_ALL WHITE			//DEFINE A COR DA FONTE DO RESTANTE DAS CELULAS


//ENUMERAÇÃO QUE DEFINE A ESTRUTURA DO TIPO DE CORES.
enum COLORS {
	BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN,
	LIGHT_GRAY, DARK_GRAY, LIGHT_BLUE, LIGHT_GREEN, LIGHT_CYAN,
	LIGHT_RED, LIGHT_MAGENTA, YELLOW, WHITE 
};

//TIPO DE DADOS PARA CONFIGURAÇÃO DE CORES
typedef enum COLORS color;


//VARIÁVEIS
char nome_inimigo[] = "DEATH";
char nome_heroi[] = "1";

char resposta[100],senha[100],senha1[100];
int vida_hud,vida_hud_max,vida_inimigo_max, tiro, granada, enemy_atk, i,chute;

int sleepcb = 20;			//VARIÁVEL DO SLEEP DO PRINT DA LINHA DE CIMA E DE BAIXO
int sleeped = 20;			//VARIÁVEL DO SLEEP DO PRINT DA LINHA DA ESQUERDA E DA DIREITA
int linhabaixo = 168;		//VARIÁVEL QUE IMPRIME NA LINHA DEBAIXO
int escolhamenu = 0;		//VARIÁVEL DA ESCOLHA DO MENU DA TELA DO BEM VINDO
int escolhamenu1 = 0;		//VARIÁVEL DA ESCOLHA DO MENU DA TELA DO MENU PRINCIPAL
int vida_inimigo = 100;		//VARIÁVEL DE VIDA DO INIMIGO
int vida_heroi = 100;		//VARIÁVEL DE VIDA DO HEROI
int conttiro = 3;			//VARIÁVEL QUE VERIFICA QUANTOS TIROS TEM DISPONÍVEL PARA ATAQUE
int contgranada = 3;		//VARIÁVEL QUE VERIFICA QUANTAS GRANADAS TEM DISPONÍVEL PARA GRANADAS
int contchute = 6;			//VARIÁVEL QUE VERIFICA QUANTOS CHUTES TEM DISPONÍVEL PARA CHUTES
int contrecovery = 3;			//VARIÁVEL QUE VERIFICA QUANTOS AUMENTOS DE VIDA O HEROI TEM DISPONÍVEL

//PROTÓTIPOS FUNÇÕES
//PROTÓTIPO DE FUNÇÕES DE ATAQUES
void ataquesoco();
void ataquesocoforte();
void ataquechute();

//PROTÓTIPOS DE FUNÇÕES DE DESENHO
void mostrabarravida();
void telainicial();

void luta();
void venceu();
void perdeu();
void fim();

//FUNÇÕES

//VIDEO - GOTOXY
void gotoxy(int x, int y){				//FUNÇÃO GOTOXY PARA CHAMAR A FUNÇÃO GOTOXY EM OUTRAS PARTES DO CÓDIGO
     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x-1,y-1});
}

void textcolor(color iColor) {			//FUNÇÃO TEXTCOLOR: DEFINE A COR DE PRIMEIRO PLANO DOS TEXTOS
	HANDLE hl = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
	BOOL b = GetConsoleScreenBufferInfo(hl, &bufferInfo);
	bufferInfo.wAttributes &= 0x00F0;
	SetConsoleTextAttribute (hl, bufferInfo.wAttributes |= iColor);
	return;
}

void textbackground(color iColor) {		//FUNÇÃO TEXTBACKGROUND: DEFINE A COR DE FUNDO DAS FONTES.
	HANDLE hl = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
	BOOL b = GetConsoleScreenBufferInfo(hl, &bufferInfo);
	bufferInfo.wAttributes &= 0x000F;
	SetConsoleTextAttribute (hl, bufferInfo.wAttributes |= (iColor << 4));
	return;
}

void bordas(){
	for(int l = 0;l<169;l++){			//LINHA CIMA DA ESQUERDA PARA DIREITA / LINHA BAIXO DA DIREITA PARA ESQUERDA	
	gotoxy(l,1);
		//Sleep(sleepcb);
		textbackground(CORMODIFICADA);
		printf(" ");
			
	gotoxy(linhabaixo,57);						
		printf(" ");
	linhabaixo--;
	}	
	textbackground(CORPADRAO);	
		
	for(int l = 2;l<57;l++){			//LINHA DIREITA DE CIMA PARA BAIXO  	//LINHA ESQUERDA DE CIMA PARA BAIXO	
		textbackground(CORPADRAO);
		gotoxy(168,l);  
	    //Sleep(sleeped);						
		printf("%c\n",220);				
		gotoxy(1,l);
		//Sleep(sleeped);				
		printf("%c\n",220);				//LINHA ESQUERDA DE CIMA PARA BAIXO	
	}	
}

void selecaoPersonagem(){				//TELA DE SELEÇÃO DE PERSONAGENS
	int escolha_personagem = -1;
	
	gotoxy(1,1);	
	for(int l = 0;l<168;l++){			//LINHA CIMA DA ESQUERDA PARA DIREITA	
		//Sleep(sleepcb);
		textbackground(CORMODIFICADA);
		printf(" ");
	}
	
	for(int l = 2;l<57;l++){			//LINHA DIREITA DE CIMA PARA BAIXO  	//LINHA ESQUERDA DE CIMA PARA BAIXO	
		textbackground(CORPADRAO);
		gotoxy(168,l);  						
		printf("%c\n",220);				
		gotoxy(1,l);				
		printf("%c\n",220);				//LINHA ESQUERDA DE CIMA PARA BAIXO	
	}	
	
	gotoxy(60,11);
	printf("   _____      _                         ");
	gotoxy(60,12);
	printf("  / ____|    | |                        ");
	gotoxy(60,13);			
	printf(" | (___   ___| | ___  ___ __ _  ___   ");
	gotoxy(60,14);
	printf("  \\___ \\ / _ \\ |/ _ \\/ __/ _` |/ _ \\    ");
	gotoxy(60,15);			
	printf("  ____) |  __/ |  __/ (_| (_| | (_) |");
	gotoxy(60,16);			
	printf(" |_____/ \\___|_|\\___|\\___\\__,_|\\___/");
	
	textbackground(CORMODIFICADA);
	gotoxy(57,18);
	for(int l = 0;l<40;l++){			   //LINHA DE BAIXO DO "SELECAO"
	Sleep(4);
	printf(" ");
	}

	textbackground(CORPADRAO);
	gotoxy(68,19);
	printf("      _      ");
	gotoxy(68,20);
	printf("     | |     ");
	gotoxy(68,21);			
	printf("   __| | ___ ");
	gotoxy(68,22);
	printf("  / _` |/ _ \\");
	gotoxy(68,23);			
	printf(" | (_| |  __/");
	gotoxy(68,24);			
	printf("  \\__,_|\\___|");
	
	
	textbackground(CORMODIFICADA);
	gotoxy(68,26);
	for(int l = 0;l<15;l++){			   //LINHA DE BAIXO DO "DE"
	Sleep(4);
	printf(" ");
	}
	

	textbackground(CORPADRAO);
	gotoxy(50,28);
	printf("  _____                                                     ");
	gotoxy(50,29);
	printf(" |  __ \\                                                    ");
	gotoxy(50,30);			
	printf(" | |__) |__ _ __ ___  ___  _ __   __ _  __ _  ___ _ __  ___ ");
	gotoxy(50,31);
	printf(" |  ___/ _ \\ '__/ __|/ _ \\| '_ \\ / _` |/ _` |/ _ \\ '_ \\/ __|");
	gotoxy(50,32);			
	printf(" | |  |  __/ |  \\__ \\ (_) | | | | (_| | (_| |  __/ | | \\__ \\");
	gotoxy(50,33);			
	printf(" |_|   \\___|_|  |___/\\___/|_| |_|\\__,_|\\__, |\\___|_| |_|___/");
	gotoxy(50,34);			
	printf("                                        __/ |     ");
	gotoxy(50,35);			
	printf("                                       |___/      ");

	textbackground(CORMODIFICADA);
	gotoxy(1,57);
	for(int l = 0;l<168;l++){			   //LINHA BAIXO ESQUERDA PARA DIREITA						
	printf(" ");
	}
	
	textbackground(CORMODIFICADA);
	gotoxy(49,36);
	for(int l = 0;l<63;l++){			   //LINHA DE BAIXO DO "DE"
	Sleep(4);
	printf(" ");
	}

	textbackground(CORPADRAO);
	textcolor(WHITE);
	gotoxy(10,50);
	printf("SHABLAU - [1]");
	
	textbackground(CORMODIFICADA);
	gotoxy(9,51);
	for(int l = 0;l<15;l++){			   //LINHA DE BAIXO DE "SHABLAU"
	Sleep(4);
	printf(" ");
	}
	
	textbackground(CORPADRAO);
	gotoxy(73,50);
	printf("MOISES - [2]");
	
	textbackground(CORMODIFICADA);
	gotoxy(72,51);
	for(int l = 0;l<14;l++){			   //LINHA DE BAIXO DE "MOISÉS"
	Sleep(4);
	printf(" ");
	}
	
	textbackground(CORPADRAO);
	gotoxy(150,50);
	printf("NOE - [3]");

	textbackground(CORMODIFICADA);
	gotoxy(149,51);
	for(int l = 0;l<13;l++){			   //LINHA DE BAIXO DE "NOÉ"
	Sleep(4);
	printf(" ");
	}
    
    textcolor(WHITE);
	textbackground(CORPADRAO);      
	gotoxy(68,54);
	printf("SELECIONE O SEU LUTADOR!");
	
	 
	textbackground(CORMODIFICADA);
	gotoxy(67,55);
	for(int l = 0;l<26;l++){			   //LINHA DEBAIXO DE SELECIONE SEU LUTADOR
	Sleep(4);
	printf(" ");
	}
 	
 	
	textbackground(CORPADRAO);
	
	gotoxy(79,56);
	
	
	escolha_personagem = getche();//GRAVAQ O VALOR NA VARIÁVEL EM FORMA DECIMAL


	while(escolha_personagem != 49 && escolha_personagem != 50 && escolha_personagem != 51){
		system("cls");
		gotoxy(50,50);
		printf("SELECIONE UM HEROI");
		system("pause"); 
		system("cls");		
		selecaoPersonagem();
	}
		switch (escolha_personagem){
			case 49:
				strcpy( nome_heroi, "SHABLAU");
			break;
			case 50:
				strcpy( nome_heroi, "MOISES");
			break;
			case 51:
				strcpy( nome_heroi, "NOE");
			break;
		}
	system("cls");
	luta();	
}

void menu(){							//FUNÇÃO DA TELA DO MENU PRINCIPAL
	
	gotoxy(1,1);	
	for(int l = 0;l<168;l++){			//LINHA CIMA DA ESQUERDA PARA DIREITA	
		//Sleep(sleepcb);
		textbackground(CORMODIFICADA);
		printf(" ");
	}	
	
	for(int l = 2;l<57;l++){			//LINHA DIREITA DE CIMA PARA BAIXO  	//LINHA ESQUERDA DE CIMA PARA BAIXO	
		textbackground(CORPADRAO);
		gotoxy(168,l);  						
		printf("%c\n",220);				
		gotoxy(1,l);				
		printf("%c\n",220);				//LINHA ESQUERDA DE CIMA PARA BAIXO	
	}	
		
	gotoxy(60,16);
	printf("___  ___ _____ _   _ _   _");
	gotoxy(60,17);
	printf("|  \\/  ||  ___| \\ | | | | |");
	gotoxy(60,18);			
	printf("| .  . || |__ |  \\| | | | |");
	gotoxy(60,19);
	printf("| |\\/| ||  __|| . ` | | | |");
	gotoxy(60,20);			
	printf("| |  | || |___| |\\  | |_| |");
	gotoxy(60,21);			
	printf("\\_|  |_/\\____/\\_| \\_/\\___/ ");
	gotoxy(65,27);
	printf("[1] - JOGAR");
	gotoxy(65,32);			
	printf("[0]-SAIR");
	
	textbackground(CORMODIFICADA);
	gotoxy(1,57);
	for(int l = 0;l<168;l++){			   //LINHA BAIXO ESQUERDA PARA DIREITA						
	printf(" ");
	}
	
	gotoxy(57,23);
	for(int l = 0;l<32;l++){			   //LINHA DE BAIXO DO "MENU"
	textbackground(CORMODIFICADA);
	printf(" ");
	}
	
	textbackground(CORPADRAO);
	gotoxy(65,28);
	for(int l = 0;l<12;l++){			   //LINHA DE BAIXO DO "JOGAR"
	printf("%c",220);
	}
	
	gotoxy(65,33);
	for(int l = 0;l<10;l++){			   //LINHA DE BAIXO DO "SAIR"
	printf("%c",220);
	}
		
	gotoxy(155,55);
	printf("VERSAO 2.0 \n\n");			   //PRINTF DA VERSÃO DO JOGO
	
	fflush(stdin);
	escolhamenu1 = getch();
	
	switch(escolhamenu1){		
				
				case '1':
					system("cls");
					selecaoPersonagem();
				break;				
				case '0':	
					exit(0);
				break;
			}			
}

void bemvindo(){						//FUNÇÃO TELA BEM VINDO AO SUDOKU
	
	for(int l = 0;l<169;l++){			//LINHA CIMA DA ESQUERDA PARA DIREITA / LINHA BAIXO DA DIREITA PARA ESQUERDA	
	gotoxy(l,1);
		Sleep(sleepcb);
		textbackground(CORMODIFICADA);
		printf(" ");
			
	gotoxy(linhabaixo,57);						
		printf(" ");
	linhabaixo--;
	}	
	textbackground(CORPADRAO);	
		
	for(int l = 2;l<57;l++){			//LINHA DIREITA DE CIMA PARA BAIXO  	//LINHA ESQUERDA DE CIMA PARA BAIXO	
		textbackground(CORPADRAO);
		gotoxy(168,l);  
	    Sleep(sleeped);						
		printf("%c\n",220);				
		gotoxy(1,l);
		Sleep(sleeped);				
		printf("%c\n",220);				//LINHA ESQUERDA DE CIMA PARA BAIXO	
	}	
	
	gotoxy(53,15);		
	printf("______ ________  ___           _   _ _____ _   _______ _____");
    gotoxy(53,16);
	printf("| ___ \\  ___|  \\/  |          | | | |_   _| \\ | |  _  \\  _  |");	
    gotoxy(53,17);
	printf("| |_/ / |__ | .  . |  ______  | | | | | | |  \\| | | | | | | |");
    gotoxy(53,18);
	printf("| ___ \\  __|| |\\/| | |______| | | | | | | | . ` | | | | | | |");
    gotoxy(53,19);
	printf("| |_/ / |___| |  | |          \\ \\_/ /_| |_| |\\  | |/ /\\ \\_/ /");
    gotoxy(53,20);
	printf("\\____/\\____/\\_|  |_/           \\___/ \\___/\\_| \\_/___/  \\___/");
      
    
    gotoxy(76,23);
	printf(" ___");
    gotoxy(76,24); 
	printf("/ _ \\");
    gotoxy(75,25);
	printf("/ /_\\ \\");
    gotoxy(75,26);
	printf("|  _  |");
    gotoxy(75,27);
	printf("| | | |");
    gotoxy(75,28); 
	printf("\\_| |_/");
	
	gotoxy(41,34);
	printf("_____ ______  ___   _   _______ _____  ______  ___ _____ ___   _      _   _   ___");
    gotoxy(40,35);
	printf("|  __ \\| ___ \\/ _ \\ | \\ | |  _  \\  ___| | ___ \\/ _ \\_   _/ _ \\ | |    | | | | / _ \\");
    gotoxy(40,36);
	printf("| |  \\/| |_/ / /_\\ \\|  \\| | | | | |__   | |_/ / /_\\ \\| |/ /_\\ \\| |    | |_| |/ /_\\ \\");
    gotoxy(40,37);
	printf("| | __ |    /|  _  || . ` | | | |  __|  | ___ \\  _  || ||  _  || |    |  _  ||  _  |");
    gotoxy(40,38);
	printf("| |_\\ \\| |\\ \\| | | || |\\  | |/ /| |___  | |_/ / | | || || | | || |____| | | || | | |");
    gotoxy(41,39);
	printf("\\____/\\_| \\_\\_| |_/\\_| \\_/___/ \\____/  \\____/\\_| |_/\\_/\\_| |_/\\_____/\\_| |_/\\_| |_/");
	

	gotoxy(45,22);
	for(int l = 0;l<75;l++){			   //LINHA DE BAIXO DO "BEMVINDO"
	Sleep(2);
	textbackground(CORMODIFICADA);
	printf(" ");
	}
	
	gotoxy(66,30);
	for(int l = 0;l<25;l++){			   //LINHA DE BAIXO DO "AO"
	Sleep(2);
	printf(" ");
	}
	
	gotoxy(45,41);
	for(int l = 0;l<75;l++){			   //LINHA DE BAIXO DO "SUDOKU"
	Sleep(2);
	printf(" ");
	}
	
	textbackground(CORPADRAO);	
	gotoxy(155,55);
	printf("VERSAO 2.0 \n\n");			   //PRINTF DA VERSÃO DO JOGO

	gotoxy(2,55);
	textbackground(CORMODIFICADA);
	textcolor(BLACK);
	printf("DESENVOLVIDO POR: EBNER SILVA/JOAO DE BRITO /RONALDO SANT'ANA/ ALIANDRO JUAI- UNICESUMAR 2017\n\n");			   //PRINTF DOS DESENVOLVEDORES
	
//----------------------------------------------------------------------------------------------
//LOADING
	textbackground(CORPADRAO);
	textcolor(WHITE);
	gotoxy(44,44);
	for(int l=0;l<77;l++){				   //LINHA DE CIMA DO LOADING
	printf("%c",196);	
	}
	
	gotoxy(44,46);
	for(int l=0;l<77;l++){				   //LINHA DE BAIXO DO LOADING
	printf("%c",196);	
	}
	
	gotoxy(44,45);
	printf("%c",186);					   //BARRA LATERAL ESQUERDA DO LOADING
	
	gotoxy(120,45);						   //BARRA LATERAL DIREITA DO LOADING
	printf("%c",186);
	
	gotoxy(46,45);
	for(int l=0;l<37;l++){				   //CARACTERES DO LOADING 
	Sleep(150);
	printf("%c ", 178);
	}
	
	printf("\n\n");	

//----------------------------------------------------------------------------------------------
//ENTRANDO NO MENU INICIAL
	gotoxy(63,47);
	Sleep(100);
	printf("DIGITE QUALQUER TECLA PARA CONTINUAR! \n\n\n");			
	fflush(stdin);
	escolhamenu = getch();
	system("CLS");
	menu();
}

void resolucao1366x768(){				//FUNÇÃO PARA DEIXAR A TELA DO JOGO EM TELA GRANDE
	keybd_event ( VK_MENU, 0x36, 0, 0 ); 
	keybd_event ( VK_RETURN, 0x1C, 0, 0 );
	keybd_event ( VK_RETURN, 0x1C, KEYEVENTF_KEYUP, 0 ); 
	keybd_event ( VK_MENU, 0x38, KEYEVENTF_KEYUP, 0 );	
}

int hud_vida_heroi(int vida_heroi){		//FUNÇÃO QUE DECREMENTA DA VIDA DO HEROI DEPENDENDO DA LUTA
	//For para preencher barra de vida
	vida_hud = vida_heroi/10;
	vida_hud_max = 100/10;
	
	gotoxy(154,5);
	printf ("[");
	for (int i=1;i<vida_hud;i++){
 		textcolor(GREEN);
		printf("%c",3);
	}
	textcolor(WHITE);
	for(int i=vida_hud+1;i<vida_hud_max;i++){
		printf(" ");
	}
	printf("]  ");
}

int hud_vida_inimigo(int vida_inimigo){	//FUNÇÃO QUE DECREMENTA DA VIDA DO INIMIGO DEPENDENDO DA LUTA
	//For para preencher barra de vida
	vida_hud = vida_inimigo/10;
	vida_hud_max = 100/10;
	
	gotoxy(8,5);
	printf ("[");
	for (int i=1;i<vida_hud;i++){
 		textcolor(GREEN);
		printf("%c",3);
	}
	textcolor(WHITE);
	for(int i=vida_hud+1;i<vida_hud_max;i++){
		printf(" ");
	}
	printf("]  ");
}

void barravidanome(){					//FUNÇÃO QUE MOSTRA A BARRA DE VIDA DOS LUTADORES NO COMEÇO DO JOGO
	gotoxy(4,4);
	printf("INIMIGO: %s",nome_inimigo);
	     
	gotoxy(3,5);
	printf(" VIDA");
	hud_vida_inimigo(vida_inimigo);
	
	gotoxy(150,4);
	printf("HEROI: %s",nome_heroi);
	     
	gotoxy(149,5);
	printf(" VIDA");
	hud_vida_heroi(vida_heroi);
}

void venceu(){							//TELA QUE MOSTRA QUE O JOGADOR VENCEU
	
	for(int l = 0;l<169;l++){			//LINHA CIMA DA ESQUERDA PARA DIREITA / LINHA BAIXO DA DIREITA PARA ESQUERDA	
	gotoxy(l,1);
		//Sleep(sleepcb);
		textbackground(CORMODIFICADA);
		printf(" ");
			
	gotoxy(linhabaixo,57);						
		printf(" ");
	linhabaixo--;
	}	
	textbackground(CORPADRAO);	
		
	for(int l = 2;l<57;l++){			//LINHA DIREITA DE CIMA PARA BAIXO  	//LINHA ESQUERDA DE CIMA PARA BAIXO	
		textbackground(CORPADRAO);
		gotoxy(168,l);  
	    //Sleep(sleeped);						
		printf("%c\n",220);				
		gotoxy(1,l);
		//Sleep(sleeped);				
		printf("%c\n",220);				//LINHA ESQUERDA DE CIMA PARA BAIXO	
	}
	
	textcolor(YELLOW);
	gotoxy(53,20);
	printf("______  ___  ______  ___  ______ _____ _   _  _____ _ _ _ ");
	gotoxy(53,21);
	printf("| ___ \\/ _ \\ | ___ \\/ _ \\ | ___ \\  ___| \\ | |/  ___| | | |");
	gotoxy(53,22);
	printf("| |_/ / /_\\ \\| |_/ / /_\\ \\| |_/ / |__ |  \\| |\\ `--.| | | |");
	gotoxy(53,23);
	printf("|  __/|  _  ||    /|  _  || ___ \\  __|| . ` | `--. \\ | | |");
	gotoxy(53,24);
	printf("| |   | | | || |\\ \\| | | || |_/ / |___| |\\  |/\\__/ /_|_|_|");
	gotoxy(53,25);
	printf("\\_|   \\_| |_/\\_| \\_\\_| |_/\\____/\\____/\\_| \\_/\\____/(_|_|_)");	
	
	
	gotoxy(48,27);
	printf(" _   _  _____ _____  _____   _   _ _____ _   _ _____  _____ _   _ ");
	gotoxy(48,28);
	printf("| | | ||  _  /  __ \\|  ___| | | | |  ___| \\ |  /  __\\|  ___| | | |");
	gotoxy(48,29);
	printf("| | | || | | | /  \\/| |__   | | | | |__ |  \\| | /  \\/| |__ | | | |");	
	gotoxy(48,30);
	printf("| | | || | | | |    |  __|  | | | |  __|| . ` | |    |  __|| | | |");
	gotoxy(48,31);
	printf("\\ \\_/ /\\ \\_/ / \\__/\\| |___  \\ \\_/ / |___| |\\  | \\__/\\| |___| |_| |");
	gotoxy(48,32);
	printf(" \\___/  \\___/ \\____/\\____/   \\___/\\____/\\_| \\_/\\____/\\____/ \\___/");
	
	gotoxy(65,33);
	printf("  ___    _     _   _ _____ ___");
	gotoxy(65,34);
	printf(" / _ \\  | |   | | | |_   _/ _ \\");
	gotoxy(65,35);
	printf("/ /_\\ \\ | |   | | | | | |/ /_\\ \\");
	gotoxy(65,36);
	printf("|  _  | | |   | | | | | ||  _  |");
	gotoxy(65,37);
	printf("| | | | | |___| |_| | | || | | |");
	gotoxy(65,38);
	printf("\\_| |_/ \\_____/\\___/  \\_/\\_| |_/");
	
	textbackground(CORMODIFICADA);
	gotoxy(1,57);
	for(int l = 0;l<168;l++){			   //LINHA BAIXO ESQUERDA PARA DIREITA						
	printf(" ");
	}
	
	gotoxy(55,54);
	textcolor(WHITE);
	textbackground(BLACK);
	system("pause");
}

void perdeu(){							//TELA QUE MOSTRA QUE O JOGADOR PERDEU
	for(int l = 0;l<169;l++){			//LINHA CIMA DA ESQUERDA PARA DIREITA / LINHA BAIXO DA DIREITA PARA ESQUERDA	
	gotoxy(l,1);
		//Sleep(sleepcb);
		textbackground(RED);
		printf(" ");
			
	gotoxy(linhabaixo,34);						
		//Sleep(sleepcb);
		printf(" ");
	linhabaixo--;
	}	
	textbackground(CORPADRAO);	
		
	for(int l = 2;l<57;l++){			//LINHA DIREITA DE CIMA PARA BAIXO  	//LINHA ESQUERDA DE CIMA PARA BAIXO	
		textbackground(CORPADRAO);
		gotoxy(168,l);  
	    //Sleep(sleeped);						
		printf("%c\n",220);				
		gotoxy(1,l);
		//Sleep(sleeped);				
		printf("%c\n",220);				//LINHA ESQUERDA DE CIMA PARA BAIXO	
	}
	
	textcolor(WHITE);
	
	gotoxy(53,27);
	printf("   ____                         ___                 ");
	gotoxy(53,28);
	printf("  / ___| __ _ _ __ ___   ___   / _ \\__   _____ _ __ ");
	gotoxy(53,29);
	printf(" | |  _ / _` | '_ ` _ \\ / _ \\ | | | \\ \\ / / _ \\ '__|");
	gotoxy(53,30);
	printf(" | |_| | (_| | | | | | |  __/ | |_| |\\ \\V /  __/ |   ");
	gotoxy(53,31);
	printf("  \\____|\\__,_|_| |_| |_|\\___|  \\___/  \\_/ \\___|_|   ");

	textbackground(RED);
	gotoxy(1,57);
	for(int l = 0;l<168;l++){			   //LINHA BAIXO ESQUERDA PARA DIREITA						
	printf(" ");
	}

	gotoxy(55,54);
	textcolor(WHITE);
	textbackground(BLACK);
	system("pause");
	
}

void qtdataques(){						//FUNÇÃO QUE MOSTRA A QUANTIDADE DE ATAQUES QUE O LUTADOR TEM DISPONÍVEL
	textcolor(GREEN);
	gotoxy(120,8);
	printf("QUANTIDADE DE RECOVERY DE VIDA DISPONIVEIS: %i",contrecovery);
	
	gotoxy(120,9);
	printf("QUANTIDADE DE TIROS DISPONIVEIS: %i",conttiro);
	
	gotoxy(120,10); 
	printf("QUANTIDADE DE GRANADAS FORTES DISPONIVEIS: %i",contgranada);
	
	gotoxy(120,11);
	printf("QUANTIDADE DE CHUTES DISPONIVEIS: %i",contchute);

	textcolor(WHITE);
}

void tiravida(int golpe){				//FUNÇÃO QUE TIRA A VIDA DO INIMIGO OU DO HEROI
	switch (golpe){
		
		case 49:
		vida_inimigo = vida_inimigo -20;
		
		srand(time(NULL));
		vida_heroi = vida_heroi-rand()%40;
		
		conttiro--;
		break;
		
		case 50:
		vida_inimigo = vida_inimigo - 40;
		
		srand(time(NULL));
		vida_heroi = vida_heroi-rand()%40;
		
		contgranada--;
		break;
		
		case 51:
		vida_inimigo = vida_inimigo - 10;
		
		srand(time(NULL));
		vida_heroi = vida_heroi-rand()%40;
		
		contchute--;
		break;
		case 52:
		
		if(vida_heroi >= 100){
			gotoxy(1,6);
			printf("NAO E POSSIVEL AUMENTAR A VIDA JA QUE VOCE JA TEM 100 % DE VIDA!");
		}else{
			vida_heroi = vida_heroi+20;
			if (vida_heroi > 100){
				vida_heroi = 100;
			}
			contrecovery--;	
		}
		break;
	}
	hud_vida_inimigo(vida_inimigo);
	hud_vida_heroi(vida_heroi);
}

void centroluta(){						//FUNÇÃO QUE MOSTRA O CENTRO DA LUTA, E QUE TAMBÉM FAZ UMAS VALIDAÇÕES DE ATAQUES
	int escolha_ataque = -1;
	
	for(int l = 0;l<169;l++){			//LINHA CIMA DA ESQUERDA PARA DIREITA 
	gotoxy(l,1);
		//Sleep(sleepcb);
		textbackground(CORMODIFICADA);
		printf(" ");	
	}	
	textbackground(CORPADRAO);	
		
	for(int l = 2;l<57;l++){			//LINHA DIREITA DE CIMA PARA BAIXO  	//LINHA ESQUERDA DE CIMA PARA BAIXO	
		textbackground(CORPADRAO);
		gotoxy(168,l);  
	    //Sleep(sleeped);						
		printf("%c\n",220);				
		gotoxy(1,l);
		//Sleep(sleeped);				
		printf("%c\n",220);				//LINHA ESQUERDA DE CIMA PARA BAIXO	
	}	
	
	
	gotoxy(80,30);
	printf("	                          /[-])//  ___");
	gotoxy(80,31);
	printf("                     __ --\\ `_/~--|  / \\");
	gotoxy(80,32);
	printf("                   |  |___|===|_-- | \\ \\ \\");
	gotoxy(80,33);
	printf(" _/~~~~~~~~|~~\\,   ---|---\\___/----|  \\/\\-\\");
	gotoxy(80,34);
	printf(" ~\\________|__/   / // \\__ |  ||  / | |   | |");
	gotoxy(80,35);
	printf("          ,~-|~~~~~\\--, | \\|--|/~|||  |   | |");
	gotoxy(80,36);
	printf("          [3-|____---~~ _--'==;/ _,   |   |_|");
	gotoxy(80,37);
	printf("                      /   /\\__|_/  \\  \\__/--/");
	gotoxy(80,38);
	printf("                     /---/_\\  -___/ |  /,--|");
	gotoxy(80,39);
	printf("                     /  /\\/~--|   | |  \\///");
	gotoxy(80,40);
	printf("                    /  / |-__ \\    |/");
	gotoxy(80,41);
	printf("                   |--/ /      |-- | \\");
	gotoxy(80,42);
	printf("                  \\^~~\\\\/\\      \\   \\/- _");
	gotoxy(80,43);
	printf("                   \\    |  \\     |~~\\~~| \\");
	gotoxy(80,44);
	printf("                    \\    \\  \\     \\   \\  | \\");
	gotoxy(80,45);
	printf("                      \\    \\ |     \\   \\    \\");
	gotoxy(80,46);
	printf("                       |~~|\\/\\|     \\   \\   |");
	gotoxy(80,47);
	printf("                      |   |/         \\_--_- |\\");
	gotoxy(80,48);
	printf("                      |  /            /   |/\\/");
	gotoxy(80,49);
	printf("                       ~~             /  /");
	gotoxy(80,50);
	printf("                                     |__/");

	gotoxy(5,16);
	printf("	                                         .""--..__");
	gotoxy(5,17);
	printf("                     _                     []       ``-.._");
	gotoxy(5,18);
	printf("                  .'` `'.                  ||__           `-._");
	gotoxy(5,19);
	printf("                 /    ,-.\\                 ||_ ```---..__     `-.");
	gotoxy(5,20);
	printf("                /    /:::\\\\               /|//}          ``--._  `.");
	gotoxy(5,21);
	printf("                |    |:::||              |////}                `-. \\");
	gotoxy(5,22);
	printf("                |    |:::||             //'///                    `.\\");
	gotoxy(5,23);
	printf("                |    |:::||            //  ||'                      `|");
	gotoxy(5,24);
	printf("                /    |:::|/        _,-//\\  ||");
	gotoxy(5,25);
	printf("               /`    |:::|`-,__,-'`  |/  \\ ||");
	gotoxy(5,26);
	printf("             /`  |   |'' ||           \\   |||");
	gotoxy(5,27);
	printf("           /`    \\   |   ||            |  /||");
	gotoxy(5,28);
	printf("         |`       |  |   |)            \\ | ||");
	gotoxy(5,29);
	printf("        |          \\ |   /      ,.__    \\| ||");
	gotoxy(5,30);
	printf("        /           `         /`    `\\   | ||");
	gotoxy(5,31);
	printf("       |                     /        \\  / ||");
	gotoxy(5,32);
	printf("       |                     |        | /  ||");
	gotoxy(5,33);
	printf("       /         /           |        `(   ||");
	gotoxy(5,34);
	printf("      /          .           /          )  ||");
	gotoxy(5,35);
	printf("     |            \\          |     ________||");
	gotoxy(5,36);
	printf("    /             |          /     `-------.|");
	gotoxy(5,37);
	printf("   |\\            /          |              ||");
	gotoxy(5,38);
	printf("   \\/`-._       |           /              ||");
	gotoxy(5,39);
	printf("    //   `.    /`           |              ||");
	gotoxy(5,40);
	printf("   //`.    `. |             \\              ||");
	gotoxy(5,41);
	printf("  ///\\ `-._  )/             |              ||");
	gotoxy(5,42);
	printf(" //// )   .(/               |              ||");
	gotoxy(5,43);
	printf(" ||||   ,'` )               /              //");
	gotoxy(5,44);
	printf(" ||||  /                    /             || ");
	gotoxy(5,45);
	printf(" `\\\\` /`                    |             // ");
	gotoxy(5,46);
	printf("     |`                     \\            ||  ");
	gotoxy(5,47);
	printf("    /                        |           //  ");
	gotoxy(5,48);
	printf("  /`                          \\         //   ");
	gotoxy(5,49);
	printf("/`                            |        ||    ");
	gotoxy(5,50);
	printf("`-.___,-.      .-.        ___,'        (/    ");
	gotoxy(5,51);
	printf("         `---'`   `'----'`");

	for(int i = 0;i<167;i++){
		gotoxy(i,52);		
		textcolor(YELLOW);
		printf("_");
	}
	textcolor(WHITE);
	
	textbackground(CORMODIFICADA);
	gotoxy(1,57);
	for(int l = 0;l<168;l++){			   //LINHA BAIXO ESQUERDA PARA DIREITA						
	printf(" ");
	}
	textbackground(CORPADRAO);
	
	gotoxy(80,52);
	printf("ESCOLHA UMA OPCAO:");

	gotoxy(80,53);
	printf("[1] TIRO");
	
	gotoxy(80,54);
	printf("[2] GRANADA");
	
	gotoxy(80,55);
	printf("[3] CHUTE");
	
	gotoxy(80,56);
	printf("[4] RECOVERY");
	
	escolha_ataque = getch();
	
	while(escolha_ataque!=49 && escolha_ataque!=50 && escolha_ataque!=51 && escolha_ataque!=52){		
		textbackground(YELLOW);
		textcolor(BLACK);
		
		gotoxy(1,6);
		printf("OPCAO INVALIDA - POR FAVOR SELECIONE UMA OPCAO!");

		escolha_ataque = getche();
		
		textbackground(BLACK);
		textcolor(WHITE);
		
	}
	system("cls");	
	
	textbackground(YELLOW);
	textcolor(BLACK);
	gotoxy(1,6);
	if(escolha_ataque==49){
		if(conttiro>0){
			tiravida(escolha_ataque);
		}else{
			printf("VOCE NAO TEM ATAQUES DISPONIVEIS!");
			
		}
	}else if(escolha_ataque==50){
		if(contgranada>0){
			tiravida(escolha_ataque);
		}else{
			printf("VOCE NAO TEM ATAQUES DISPONIVEIS!");
		}
	}else if(escolha_ataque==51){
		if(contchute>0){
			tiravida(escolha_ataque);
		}else{
			printf("VOCE NAO TEM ATAQUES DISPONIVEIS!");
		}
	}else if(escolha_ataque==52){
		if(contrecovery>0){
			tiravida(escolha_ataque);
		}else{
			printf("VOCE NAO TEM RECOVERY DISPONIVEIS!");
		}
	}
	textbackground(BLACK);
	textcolor(WHITE);
}

void luta(){							//FUNÇÃO QUE CONTROLA DE A VIDA DOS JOGADORES ESTÃO CHEIAS OU VAZIAS E QUE TERMINA A LUTA
	
	//NESSE WHILE VERIFICAMOS SE O INIMIGO E O HEROI TEM VIDA PARA CONTINUAR A LUTA
	while(vida_inimigo>0&&vida_heroi>0){
		barravidanome();//FUNÇÃO QUE MOSTRA A BARRA DE VIDA DE ACORDO COM A VIDA DOS LUTADORES
		qtdataques();//FUNÇÃO QUE MOSTRA A QUANTIDADE DE ATAQUES DISPONÍVEIS NA LUTA
		centroluta();//FUNÇÃO QUE FAZ TODO O CONTROLE DE ATAQUES E VIDA
	}	
	system("cls");
	
	if(vida_heroi>0 && vida_inimigo<=0){
		venceu();	
	}else if(vida_heroi<=0 && vida_inimigo>0){
		perdeu();
	}
	
	vida_heroi = 100;
	vida_inimigo = 100;
	conttiro = 3;
	contgranada = 3;
	contchute = 6;
	contrecovery = 3;
} 
	
int main(int argc, char** argv) {
resolucao1366x768();	
bemvindo();
escolhamenu1 = 1;	
	
	while(escolhamenu1!=0){
		system("CLS");
		menu();
	}
	
	return 0;
}

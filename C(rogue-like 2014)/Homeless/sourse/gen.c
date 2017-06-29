#include <stdio.h>
#include <windows.h>
#include "gen.h"
#include "mobs.h"
#include "items.h"
#include "global.h"

char m[SIZE1][SIZE2];
int n[SIZE1][SIZE2];
struct room{
	int x, y;
	int x2, y2;
	int gor, ver;
	int num;
	int roomx, roomy;//горизонтальные
	int roomx2, roomy2;//вертикальные
	int doornum;
}rooms[maxrooms];


//сеточный метод
void gen(){

	
	srand(time(NULL));
	system("mode con cols=120 lines=46");
	for (int i = 0; i < SIZE1; i++){
		for (int b = 0; b < SIZE2; b++){
			m[i][b] = ' ';
			n[i][b] = 0;
			m[i][0] = m[0][b] = m[i][80] = m[30][b] = '+';
			n[i][0] = n[0][b] = n[i][80] = n[30][b] = 9;
			oops[i][b] = 0;
		}
	}
	
	for (int i = 0; i < SIZE1; i++){
		for (int b = 0; b < SIZE2; b++){
			n[i][10] = n[i][20] = n[i][30] = n[i][40] = n[i][50] = n[i][60] = n[i][70] = 1;
			n[10][b] = n[20][b] = 1;
			n[2][2] = n[2][12] = n[2][22] = n[2][32] = n[2][42] = n[2][52] = n[2][61] = n[2][71] = 2;
			n[12][2] = n[12][12] = n[12][22] = n[12][32] = n[12][42] = n[12][52] = n[12][62] = n[12][72] = 2;
			n[22][2] = n[22][12] = n[22][22] = n[22][32] = n[22][42] = n[22][52] = n[22][62] = n[22][72] = 2;
			n[12][2] = n[22][2] = 2;
		}
	}
	for (int i = 0; i < SIZE1; i++){
		for (int b = 0; b < SIZE2; b++){
			int r2 = rand() % 4 + 2;
			int r = rand() % r2 + 1;
			if (n[i][b] == 2 && r == 1)
				n[i][b] = 20;
		}
	}

	int a = 0;
	for (int h = 0; h < maxrooms; h++){
		rooms[h].num = h;
		for (int i = 0; i < SIZE1; i++){
			for (int b = 0; b < SIZE2; b++){
				if (n[i][b] == 2){
					rooms[h].y = i;
					rooms[h].x = b;
					rooms[h].x2 = rooms[h].x + (rand() % (maxgor - mingor + 1) + mingor);
					rooms[h].y2 = rooms[h].y + (rand() % (maxver - minver + 1) + minver);
					for (int t = rooms[h].y; t < rooms[h].y2; t++)
						for (int g = rooms[h].x; g < rooms[h].x2; g++){
							m[t][g] = '.';
							n[t][g] = 3;
						}
					a = 1;
					break;
				}

			}
			if (a == 1){
				a = 0;
				break;
			}
		}
	}
	//дверцы
	for (int h = 0; h < maxrooms; h++){//Горизонтальные двери
		int r;
		r = rand() % ((rooms[h].y2 - 2) - (rooms[h].y + 1) + 1) + (rooms[h].y + 1);
		rooms[h].roomx = rooms[h].x2;
		rooms[h].roomy = r;
		m[rooms[h].roomy][rooms[h].roomx] = '|';
		rooms[h].doornum = 0;
		for (int b = rooms[h].roomx + 1; b < SIZE2; b++){
			if (m[rooms[h].roomy][b] == '+'){
				rooms[h].doornum = 1;
				m[rooms[h].roomy][rooms[h].roomx] = ' ';
				break;
			}
			else{
				if (m[rooms[h].roomy][b] == '.' || m[rooms[h].roomy][b] == '|')
					break;
			}
		}
	}
	for (int h = 0; h < maxrooms; h++){
		for (int i = 0; i < 5; i++){
			for (int b = 0; b < 5; b++){
				if (i == rooms[h].roomy &&rooms[h].roomx == b){
					rooms[h].roomy = 0; rooms[h].roomx = 0;
				}


			}
		}
	}

	for (int h = 0; h < maxrooms; h++){
		if (rooms[h].doornum != 1){
			for (int b = rooms[h].roomx + 1; b < SIZE2; b++){
				if (m[rooms[h].roomy][b + 1] == '+')
					break;
				if (m[rooms[h].roomy][b] != '.'&&m[rooms[h].roomy][b] != '|'){
					m[rooms[h].roomy][b] = '.';
					n[rooms[h].roomy][b - 1] = 7;
				}
				else{
					m[rooms[h].roomy][b - 1] = '|';
					break;
				}
			}
		}
	}

	for (int h = 0; h < maxrooms; h++){//Вертикальны двери
		int r;
		r = rand() % ((rooms[h].x2 - 2) - (rooms[h].x + 1) + 1) + (rooms[h].x + 1);
		rooms[h].roomx2 = r;
		rooms[h].roomy2 = rooms[h].y2;
		m[rooms[h].roomy2][rooms[h].roomx2] = '|';
		rooms[h].doornum = 0;
		/*Проверка на то что дверь упрется в следующую комнату */
		for (int i = rooms[h].roomy2 + 1; i < SIZE1; i++){
			if (m[i][rooms[h].roomx2] == '+'){
				rooms[h].doornum = 2;
				m[rooms[h].roomy2][rooms[h].roomx2] = ' ';
				break;
			}
			else{
				if (m[i][rooms[h].roomx2] == '.' || m[i][rooms[h].roomx2] == '|')
					break;
			}
		}

	}
	for (int h = 0; h < maxrooms; h++){
		for (int i = 0; i < 5; i++){
			for (int b = 0; b < 5; b++){
				if (i == rooms[h].roomy2 &&rooms[h].roomx2 == b){
					rooms[h].roomy2 = 0; rooms[h].roomx2 = 0;
				}


			}
		}
	}

	for (int h = 0; h < maxrooms; h++){
		if (rooms[h].doornum != 2){
			for (int i = rooms[h].roomy2 + 1; i < SIZE1; i++){
				if (m[i + 1][rooms[h].roomx2] == '+')
					break;
				if (m[i][rooms[h].roomx2] != '.'&&m[i][rooms[h].roomx2] != '|'){
					m[i][rooms[h].roomx2] = '.';
					n[i - 1][rooms[h].roomx2] = 6;
				}
				else{
					m[i - 1][rooms[h].roomx2] = '|';
					break;
				}
			}
		}
	}
	/*костыль, чтоб ушли сраные баги в левом верхнем*/


	for (int i = 0; i < SIZE1; i++){
		for (int b = 0; b < SIZE2; b++){
			if (m[i][b] == '.' && m[i - 1][b] == ' ')
				m[i - 1][b] = '#';
			if (m[i][b] == '.' && m[i + 1][b] == ' ')
				m[i + 1][b] = '#';
			if (m[i][b] == '.' && m[i][b - 1] == ' ')
				m[i][b - 1] = '#';
			if (m[i][b] == '.' && m[i][b + 1] == ' ')
				m[i][b + 1] = '#';

		}
	}
	for (int i = 0; i < SIZE1; i++)
		for (int b = 0; b < SIZE2; b++){
		if (m[i][b] == ' ' && m[i + 1][b] == '#'&& m[i - 1][b] == '#' && (m[i][b - 1] == '|' || m[i][b + 1] == '|'))
			m[i][b] = '#';
		if (m[i][b] == ' ' && m[i][b + 1] == '#'&& m[i][b - 1] == '#' && (m[i - 1][b] == '|' || m[i + 1][b] == '|'))
			m[i][b] = '#';
		}
	//H
	for (int h = 0; h < maxrooms; h++){
		if ((rooms[h].x2 - rooms[h].x) == 5 && (rooms[h].y2 - rooms[h].y) == 5){
			if (m[rooms[h].y - 1][rooms[h].x] != '|')
				m[rooms[h].y][rooms[h].x] = '#';
			m[rooms[h].y2 - 1][rooms[h].x2 - 1] = '#';
			if (m[rooms[h].y][rooms[h].x2] != '|')
				m[rooms[h].y][rooms[h].x2 - 1] = '#';
			m[rooms[h].y2 - 1][rooms[h].x] = '#';
			m[rooms[h].y + 2][rooms[h].x + 2] = '0';
			n[rooms[h].y][rooms[h].x] = n[rooms[h].y2 - 1][rooms[h].x2 - 1] = 0;
			n[rooms[h].y][rooms[h].x2 - 1] = n[rooms[h].y2 - 1][rooms[h].x] = 0;

		}
	}
	//случайные стенки
	for (int i = 0; i < SIZE1; i++){
		for (int b = 0; b < SIZE2; b++){
			if ((m[i + 1][b] != '|' && m[i - 1][b] != '|' && m[i][b - 1] != '|' && m[i][b + 1] != '|') && n[i][b] == 3)
				if ((m[i + 1][b] != '#' && m[i - 1][b] != '#' && m[i][b - 1] != '#' && m[i][b + 1] != '#') && n[i][b] == 3)
					if ((rand() % 15 + 1) == 1)
						m[i][b] = '#';
		}
	}
	for (int g = 0; g < 2; g++)
		for (int i = 0; i < SIZE1; i++){
			for (int b = 0; b < SIZE2; b++){
				if (m[i][b] == '|'){
					if (m[i - 1][b] == ' ')
						m[i - 1][b] = '#';
					if (m[i + 1][b] == ' ')
						m[i + 1][b] = '#';
					if (m[i][b - 1] == ' ')
						m[i][b - 1] = '#';
					if (m[i][b + 1] == ' ')
						m[i][b + 1] = '#';
				}
			}
		}
	//H
	for (int i = 0; i < SIZE1; i++)
		for (int b = 0; b < SIZE2; b++){
		if (m[i][b] == '|'){
			int u = rand() % 4 + 1;
			if (u == 1)
				m[i][b] = '/';
		}
		}

	for (int i = 0; i < 5; i++)
		for (int b = 0; b < 5; b++){
			m[i][0] = m[0][b] = '+';
			if (m[i][b] == '|' || m[i][b] == '/')
				m[i][b] = '#';
		}
	/*Пипец я это в бреду писал, может переписать потом, на релизе, потому что это индусы говнокодеры*/
	//вода да трава
	for (int i = 0; i < SIZE1; i++){
		for (int b = 0; b < SIZE2; b++){
			int aa, u = rand() % 65 + 1;
			if (n[i][b] == 3 && u == 1){
				m[i][b] = '\''; //глубокая вода
				for (int l = 0; l < SIZE1; l++)
					for (int z = 0; z < SIZE2; z++){
					if (m[l][z] == '\'' || m[l][z] == ':'){
						int e = rand() % 5 + 1;
						if (m[l][z + 1] == '.'&&m[l][z + 1] != '#'&&e == 1)
							m[l][z + 1] = ':';
						if (m[l][z - 1] == '.'&&m[l][z - 1] != '#'&&e == 2)
							m[l][z - 1] = ':';
						if (m[l + 1][z] == '.'&&m[l + 1][z] != '#'&&e == 3)
							m[l + 1][z] = ':';
						if (m[l - 1][z] == '.'&&m[l - 1][z] != '#'&&e == 4)
							m[l - 1][z] = ':';
					}
					}
			}
			u = rand() % 70 + 1;
			if (n[i][b] == 3 && u == 1){
				m[i][b] = ';'; //высокая трава
				aa = rand() % 8 + 4;
				for (int l = 0; l < SIZE1; l++)
					for (int z = 0; z < SIZE2; z++){
					if (m[l][z] == ';' || m[l][z] == ','){
						int e = rand() % 5 + 1;
						if (m[l][z + 1] == '.'&&m[l][z + 1] != '#'&&e == 1)
							m[l][z + 1] = ',';
						if (m[l][z - 1] == '.'&&m[l][z - 1] != '#'&&e == 2)
							m[l][z - 1] = ',';
						if (m[l + 1][z] == '.'&&m[l + 1][z] != '#'&&e == 3)
							m[l + 1][z] = ',';
						if (m[l - 1][z] == '.'&&m[l - 1][z] != '#'&&e == 4)
							m[l - 1][z] = ',';
					}
					}
			}
			u = rand() % 70 + 1;
			if ((n[i][b] == 3 || n[i][b] == 6 || n[i][b] == 7) && u == 1){
				m[i][b] = '='; //доски
				aa = rand() % 8 + 4;
				for (int l = 0; l < SIZE1; l++)
					for (int z = 0; z < SIZE2; z++){
					if (m[l][z] == '=' ){
						int e = rand() % 4 + 1;
						if (m[l][z + 1] == '.'&&m[l][z + 1] != '#'&&e == 1)
							m[l][z + 1] = '=';
						if (m[l][z - 1] == '.'&&m[l][z - 1] != '#'&&e == 2)
							m[l][z - 1] = '=';
						if (m[l + 1][z] == '.'&&m[l + 1][z] != '#'&&e == 3)
							m[l + 1][z] = '=';
						if (m[l - 1][z] == '.'&&m[l - 1][z] != '#'&&e == 4)
							m[l - 1][z] = '=';
					}
					}
			}

		}
	}
	for (int i = 0; i < SIZE1; i++){
		for (int b = 0; b < SIZE2; b++){
			if (m[i][b] == ',' && (rand() % 3) == 2)
				m[i][b] = ';';
		}
	}

	for (int i = 0; i < SIZE1; i++){
		for (int b = 0; b < SIZE2; b++){
			if ((rand() % 25 + 1) == 1 && n[i][b] == 3 && (m[i][b] == '.' || m[i][b] == '='))
				m[i][b] = 'B';
		}
	}


	for (int i = 0; i < SIZE1; i++){
		for (int b = 0; b < SIZE2; b++){
			if (n[i][b] == 6 || n[i][b] == 7 || n[i][b] == 3){
				if ((rand() % 70 + 1) == 1 && m[i][b] == '.')
					oops[i][b] = 1;
				if ((rand() % 70 + 1) == 1 && m[i][b] == '.')
					oops[i][b] = 2;
			}
		}
	}


	
	//Все, карта сгенерирована
	for (int i = 1; i <= 10; i++){
		if (mapnum <= 2){
			if (i == 1)
				mobgen('r', (rand() % 5 + 3));
			if (i == 2)
				mobgen('p', (rand() % 2 + 1));
			if (i == 9)
				mobgen('k', (rand() % 4 + 2));
			if (i == 5)
				mobgen('b', (rand() % 4 + 2));
			if (i == 10)
				mobgen('z', (rand() % 2 + 1));
		}
		
		if (mapnum >= 3 && mapnum <= 4){
			if (i == 1)
				mobgen('r', (rand() % 4 + 2));
			if (i == 2)
				mobgen('p', (rand() % 3 + 2));
			if (i == 3)
				mobgen('h', (rand() % 4 + 1));
			if (i == 4)
				mobgen('s', (rand() % 2 + 1));
			if (i == 5)
				mobgen('b', (rand() % 4 + 1));
		}
		
		
		if (mapnum >= 5 && mapnum <= 7){
			if (i == 8)
				mobgen('2', (rand() % 4 + 2));
			if (i == 7)
				mobgen('w',(rand() % 2 + 1));
			if (i == 3)
				mobgen('h', (rand() % 4 + 1));		
			if (i == 4)
				mobgen('s', (rand() % 2 + 1));
			if (i == 5)
				mobgen('b', (rand() % 4 + 1));
			if (i == 10)
				mobgen('z', (rand() % 2 + 1));
		}

		if (mapnum >= 8 && mapnum <= 10){
			if (i == 8)
				mobgen('2', (rand() % 2 + 1));
			if (i == 7)
				mobgen('w', (rand() % 2 + 1));
			if (i == 6)
				mobgen('e', (rand() % 6 + 2));
			if (i == 1)
				mobgen('r', (rand() % 4 + 1));
			if (i == 5)
				mobgen('b', (rand() % 4 + 1));
			if (i == 9)
				mobgen('k', (rand() % 4 + 2));
		}
		if (mapnum >= 8 && mapnum <= 10){
			if (i == 8)
				mobgen('2', (rand() % 2 + 1));
			if (i == 7)
				mobgen('w', (rand() % 2 + 1));
			if (i == 6)
				mobgen('e', (rand() % 6 + 2));
			if (i == 1)
				mobgen('r', (rand() % 4 + 1));
			if (i == 5)
				mobgen('b', (rand() % 4 + 1));
			if (i == 9)
				mobgen('k', (rand() % 4 + 2));
		}
		if (mapnum >= 11 && mapnum <= 15){
			if (i == 8)
				mobgen('2', (rand() % 2 + 1));
			if (i == 7)
				mobgen('w', (rand() % 2 + 1));
			if (i == 6)
				mobgen('e', (rand() % 6 + 2));
			if (i == 1)
				mobgen('r', (rand() % 4 + 1));
			if (i == 5)
				mobgen('b', (rand() % 4 + 1));
			if (i == 9)
				mobgen('k', (rand() % 4 + 2));
			if (i == 10)
				mobgen('z', (rand() % 2 + 1));
		}
		if (mapnum >= 16 && mapnum <= 19){
			if (i == 1)
				mobgen('r', (rand() % 4 + 1));
			if (i == 5)
				mobgen('b', (rand() % 4 + 1));
			if (i == 9)
				mobgen('k', (rand() % 4 + 2));
		}
		if (mapnum >= 21 ){
			if (i == 8)
				mobgen('2', (rand() % 2 + 1));
			if (i == 7)
				mobgen('w', (rand() % 2 + 1));
			if (i == 6)
				mobgen('e', (rand() % 6 + 2));
			if (i == 1)
				mobgen('r', (rand() % 4 + 1));
			if (i == 2)
				mobgen('p', (rand() % 3 + 2));
			if (i == 3)
				mobgen('h', (rand() % 4 + 1));
			if (i == 5)
				mobgen('b', (rand() % 4 + 1));
			if (i == 9)
				mobgen('k', (rand() % 4 + 2));
			if (i == 10)
				mobgen('z', (rand() % 2 + 1));
		}
		
	}

	//персонаж и выход
	int qq, ww, aa;
	for (;;){
		aa = 0;
		qq = rand() % ((SIZE2 - 1) + 1 - 1) + 1;
		ww = rand() % ((SIZE1 - 1) + 1 - 1) + 1;
		if (n[ww][qq] == 3 && m[ww][qq] == '.'){
			m[ww][qq] = '1';
			aa = 1;
		}
		if (aa == 1)
			break;
	}
	//может потом надо будет изменить генерацию эту, сделать ее покруче, но ведь мы не будем знать куда идти так что пока оставлю
	if ((rand() % 4 + 1) == 1)
		for (;;){
		aa = 0;
		qq = rand() % ((SIZE2 - 1) + 1 - 1) + 1;
		ww = rand() % ((SIZE1 - 1) + 1 - 1) + 1;
		if (n[ww][qq] == 3 && m[ww][qq] == '.'){
			m[ww][qq] = 'S';
			aa = 1;
		}
		if (aa == 1)
			break;
		}

	for (;;){
		aa = 0;
		qq = rand() % ((SIZE2 - 1) + 1 - 1) + 1;
		ww = rand() % ((SIZE1 - 1) + 1 - 1) + 1;
		if (n[ww][qq] == 3 && m[ww][qq] == '.'){
			m[ww][qq] = '@';
			aa = 1;
		}
		if (aa == 1)
			break;
	}
	//if ((rand()%5)==1)
	for (int i = 0; i < 2; i++)
		for (;;){
			aa = 0;
			qq = rand() % ((SIZE2 - 1) + 1 - 1) + 1;
			ww = rand() % ((SIZE1 - 1) + 1 - 1) + 1;
			if (n[ww][qq] == 3){
				oops[ww][qq] = 3;
				m[ww][qq] = '*';
				aa = 1;
			}
			if (aa == 1)
				break;
		}
	


	FILE *mapgen;
	fopen_s(&mapgen, "data\\mapgen", "w");
	for (int i = 0; i < SIZE1; i++){
		for (int j = 0; j < SIZE2; j++)
			putc(m[i][j], mapgen);
		putc('\n', mapgen);

	}
	fclose(mapgen);













	/*COORD position;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 0; i < SIZE1; i++){
		for (int j = 0; j < SIZE2; j++){
			//printf("%d",n[i][b]);
			switch (m[i][j])
			{
			case '#':
				SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 6));
				printf("%c", m[i][j]);
				break;
			case ',':case ';':
				SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 2));
				printf("%c", m[i][j]);
				break;
			case 'B':case 'R':case 'T':case 'F':
				SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 3));
				printf("%c", m[i][j]);
				break;
			case '0':
				SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 8));
				printf("%c", m[i][j]);
				break;
			case ':':
				SetConsoleTextAttribute(hConsole, (WORD)((9 << 4) | 1));
				printf("%c", m[i][j]);
				break;
			case '@':
				SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 5));
				printf("%c", m[i][j]);
				break;
			case '.':
				SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 7));
				printf("%c", m[i][j]);
				break;
			case '\'':
				SetConsoleTextAttribute(hConsole, (WORD)((1 << 4) | 9));
				printf("%c", m[i][j]);
				break;
			default:
				SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 6));
				printf("%c", m[i][j]);
				break;
			}
		}
		printf("\n");
	}

	getch();*/

}
void mobgen(char simv,int rnd){
	int rat1, rat2;
	
	for (int i = 0; i < rnd; i++){	
		rat1 = rand() % (SIZE2 - 1) + 1;
		rat2 = rand() % (SIZE1 - 1) + 1;
		if (n[rat2][rat1] == 3 && (m[rat2][rat1] == '.' 
								|| m[rat2][rat1] == '.' 
								|| m[rat2][rat1] == ',' 
								|| m[rat2][rat1] == ':'
								|| m[rat2][rat1] == ';'))
			m[rat2][rat1] = simv;
		else
			i--;

	}
}
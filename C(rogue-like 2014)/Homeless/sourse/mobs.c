#include <stdio.h>
#include <Windows.h>//H
#include <stdlib.h>
#include "global.h"
#include "mobs.h"
#include "items.h"

void allfree();
void mainMenu();


int mapx, mapy;
char** map;
int mapnum;

void newmob1(int num, int id, int x, int y){
	switch (id){
	case 0:
		mobs1[num].id = id;
		mobs1[num].x = x;
		mobs1[num].y = y;
		mobs1[num].hp = 100;
		//mobs1[num].score = 0;
		mobs1[num].dmg = 1;
		mobs1[0].defense = 0;
		mobs1[num].simv = 1;
		mobs1[num].idEff = 0;
		mobs1[num].look = 0;
		mobs1[num].hpe = 100;
		mobs1[num].mana = 50;
		mobs1[num].manae = 100;
		mobs1[num].cri = 0;
		mobs1[num].cri2 = 1;
		//mobs1[num].lvlup = 1;
		//mobs1[num].lvl = 1;

		break;
	case 1:
		mobs1[num].id = id;
		mobs1[num].x = x;
		mobs1[num].y = y;
		mobs1[num].hp = 4;
		mobs1[num].dmg = 1;
		mobs1[num].simv = 'r';
		mobs1[num].idEff = 0;
		mobs1[num].look = 0;
		mobs1[num].cri = 0;
		mobs1[num].cri2 = 2;
		mobs1[num].score = 3;
		break;
	case 2:
		mobs1[num].id = id;
		mobs1[num].x = x;
		mobs1[num].y = y;
		mobs1[num].hp = 16;
		mobs1[num].dmg = 4;
		mobs1[num].simv = 'p';
		mobs1[num].idEff = 2;
		mobs1[num].look = 3;
		mobs1[num].cri = 0;
		mobs1[num].cri2 = 3;
		mobs1[num].score = 5;
		break;
	case 3:
		mobs1[num].id = id;
		mobs1[num].x = x;
		mobs1[num].y = y;
		mobs1[num].hp = 4;
		mobs1[num].dmg = 4;
		mobs1[num].simv = 'r';
		mobs1[num].idEff = 3;
		mobs1[num].look = 4;
		mobs1[num].cri = 1;
		mobs1[num].cri2 = 2;
		mobs1[num].score = 4;
		break;
	case 4:
		mobs1[num].id = id;
		mobs1[num].x = x;
		mobs1[num].y = y;
		mobs1[num].hp = 10;
		mobs1[num].dmg = 5;
		mobs1[num].simv = 's';
		mobs1[num].idEff = 2;
		mobs1[num].look = 5;
		mobs1[num].cri = 0;
		mobs1[num].cri2 = 4;
		mobs1[num].score = 6;
		break;
	case 5:
		mobs1[num].id = id;
		mobs1[num].x = x;
		mobs1[num].y = y;
		mobs1[num].hp = 4;
		mobs1[num].dmg = 0;
		mobs1[num].simv = 'b';
		mobs1[num].idEff = 0;
		mobs1[num].look = 5;
		mobs1[num].cri = 0;
		mobs1[num].cri2 = 1;
		mobs1[num].score = 1;
		break;
	case 6:
		mobs1[num].id = id;
		mobs1[num].x = x;
		mobs1[num].y = y;
		mobs1[num].hp = 30;
		mobs1[num].dmg = 1;
		mobs1[num].simv = 'e';
		mobs1[num].idEff = 0;
		mobs1[num].look = 1;
		mobs1[num].cri = 1;
		mobs1[num].cri2 = 5;
		mobs1[num].score = 15;
		break;
	case 7:
		mobs1[num].id = id;
		mobs1[num].x = x;
		mobs1[num].y = y;
		mobs1[num].hp = 30;
		mobs1[num].dmg = 0;
		mobs1[num].simv = 'w';
		mobs1[num].idEff = 4;
		mobs1[num].look = 1;
		mobs1[num].cri = 2;
		mobs1[num].cri2 = 3;
		mobs1[num].score = 10;
		break;
	case 8:
		mobs1[num].id = id;
		mobs1[num].x = x;
		mobs1[num].y = y;
		mobs1[num].hp = 30;
		mobs1[num].dmg = 7;
		mobs1[num].simv = 2;
		mobs1[num].idEff = 0;
		mobs1[num].look = 6;
		mobs1[num].cri = 3;
		mobs1[num].cri2 = 5;
		mobs1[num].score = 20;
		break;
	case 9:
		mobs1[num].id = id;
		mobs1[num].x = x;
		mobs1[num].y = y;
		mobs1[num].hp = 10;
		mobs1[num].dmg = 3;
		mobs1[num].simv = 'k';
		mobs1[num].idEff = 0;
		mobs1[num].look = 6;
		mobs1[num].cri = 1;
		mobs1[num].cri2 = 2;
		mobs1[num].score = 5;
		break;
	case 10:
		mobs1[num].id = id;
		mobs1[num].x = x;
		mobs1[num].y = y;
		mobs1[num].hp = 40;
		mobs1[num].dmg = 1;
		mobs1[num].simv = 'z';
		mobs1[num].idEff = 0;
		mobs1[num].look = 0;
		mobs1[num].cri = 1;
		mobs1[num].cri2 = 2;
		mobs1[num].score = 15;
		break;
	default:
		printf("Нет конструктора к такому ID!!!\n");
		getch();
		break;
	}
}
//Н внутри
void move(struct Mob1 *mob){
	FILE *save;
	int i, j,x;
	bool rbool = 0;
	bool Lbool = 0;

	switch ((*mob).id){
	case 0:
		i = getch();
		switch (i){
		case '\\':
		{
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); 
			int cc;
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 7));
			gotoxy(30, 10);
			printf("+---------------------------+");
			gotoxy(30, 11);
			printf("|  Сохранить и выйти? [Y\\N] |");
			gotoxy(30, 12);
			printf("+---------------------------+");
			gotoxy(0, 44);
			cc = getch();
			if (cc == 'y'){
				fopen_s(&save, "data\\save", "wb");
				fwrite(&pname, sizeof(pname), 1, save);
				fwrite(&form, sizeof(form), 1, save);
				fwrite(&age, sizeof(int), 1, save);
				fwrite(&wm, sizeof(int), 1, save);
				fwrite(&mobs1[0].hp, sizeof(int), 1, save);
				fwrite(&mobs1[0].dmg, sizeof(int), 1, save);
				fwrite(&mobs1[0].idEff, sizeof(int), 1, save);
				fwrite(&mobs1[0].look, sizeof(int), 1, save);
				fwrite(&mobs1[0].hpe, sizeof(int), 1, save);
				fwrite(&score, sizeof(int), 1, save);
				fwrite(&olvlup, sizeof(int), 1, save);
				fwrite(&lvl, sizeof(int), 1, save);
				fwrite(&mobs1[0].mana, sizeof(int), 1, save);
				fwrite(&mobs1[0].manae, sizeof(int), 1, save);
				fwrite(&mobs1[0].cri, sizeof(int), 1, save);
				fwrite(&mobs1[0].cri2, sizeof(int), 1, save);
				fwrite(&mobs1[0].defense, sizeof(int), 1, save);
				fwrite(&money, sizeof(int), 1, save);

				fwrite(&myinv.allitem, sizeof(int), 1, save);
				for (i = 0; i < 10; i++){
					fwrite(&myinv.consumables[i].id, sizeof(int), 1, save);
					fwrite(&myinv.consumables[i].num, sizeof(int), 1, save);
					fwrite(&myinv.consumables[i].full, sizeof(bool), 1, save);
					fwrite(&myinv.consumables[i].mind, sizeof(int), 1, save);
					fwrite(&myinv.consumables[i].onhp, sizeof(int), 1, save);
					fwrite(&myinv.consumables[i].arrow, sizeof(int), 1, save);
					fwrite(&myinv.consumables[i].onMana, sizeof(int), 1, save);

					fwrite(&myinv.equipments[i].id, sizeof(int), 1, save);
					fwrite(&myinv.equipments[i].num, sizeof(int), 1, save);
					fwrite(&myinv.equipments[i].full, sizeof(bool), 1, save);
					fwrite(&myinv.equipments[i].dmg, sizeof(int), 1, save);
					fwrite(&myinv.equipments[i].def, sizeof(int), 1, save);
					fwrite(&myinv.equipments[i].equip, sizeof(bool), 1, save);

					fwrite(&myinv.magic[i].id, sizeof(int), 1, save);
					fwrite(&myinv.magic[i].num, sizeof(int), 1, save);
					fwrite(&myinv.magic[i].full, sizeof(bool), 1, save);
					fwrite(&myinv.magic[i].equip, sizeof(bool), 1, save);
				}

				fwrite(&heroeq.bowl, sizeof(bool), 1, save);
				fwrite(&heroeq.sword, sizeof(bool), 1, save);
				fwrite(&heroeq.helmet, sizeof(bool), 1, save);
				fwrite(&heroeq.armor, sizeof(bool), 1, save);
				fwrite(&heroeq.sv_fire, sizeof(bool), 1, save);
				fwrite(&heroeq.sv_rock, sizeof(bool), 1, save);
				fwrite(&heroeq.sv_blind, sizeof(bool), 1, save);
				fwrite(&heroeq.sv_inf, sizeof(bool), 1, save);

				fwrite(&mapnum, sizeof(int), 1, save);

				fwrite(&acr, sizeof(int), 1, save);
				fwrite(&stren, sizeof(int), 1, save);
				fwrite(&mental, sizeof(int), 1, save);
				fwrite(&vig, sizeof(int), 1, save);
				fwrite(&score, sizeof(int), 1, save);
				fwrite(&lvl, sizeof(int), 1, save);
				fwrite(&olvlup, sizeof(int), 1, save);
				fwrite(&hunger, sizeof(int), 1, save);
				fwrite(&golds, sizeof(int), 1, save);
				fwrite(&kills, sizeof(int), 1, save);
				fwrite(&lows, sizeof(int), 1, save);
				fwrite(&potrs, sizeof(int), 1, save);

				fclose(save);
				log("Сохранено                        ", 0, 0);
				gotoxy(0, 44);
				exit(1);
			}
		}
				break;

		case 'a':
			travel(mob, -1, 0);
			break;
		case 'w':
			travel(mob, 0, -1);
			break;
		case 'd':
			travel(mob, 1, 0);
			break;
		case 's':
			travel(mob, 0, 1);
			break;
		case 'l':
			logdraw();
			break;
		case 't':
			for (i = -1; i < 2; i++)
				for (j = -1; j < 2; j++)
					if ((j == 0 && i != 0) || (j != 0 && i == 0))
						if (map[(*mob).y + j][(*mob).x + i] == 'S' || map[(*mob).y + j][(*mob).x + i] == 'S'){
							trade();
						}
			break;
		case 'r':
			if ((mobs1[0].mana - 4) >= 0){
				if (mobs1[0].hp < mobs1[0].hpe){
					mobs1[0].mana -= 4;
					mobs1[0].hp += 1;
					if (hunger < 50)
						hunger++;
					log("Восстановление сил и лечение      ", 0, 0);					
				}else log("Здоров и свеж                    ", 0, 0);
			}else log("Не хватает маны для отдыха(2)     ", 0, 0);
			break;
		case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9': case '0':
			i = i - '0' - 1;
			if (i == -1)
				i = 9;
			if (i < myinv.allitem)
				itemuse(i);
			break;
		case '!':
			itemdel(0);
			break;
		case '@':
			itemdel(1);
			break;
		case '#':
			itemdel(2);
			break;
		case '$':
			itemdel(3);
			break;
		case '%':
			itemdel(4);
			break;
		case '^':
			itemdel(5);
			break;
		case '&':
			itemdel(6);
			break;
		case '*':
			itemdel(7);
			break;
		case '(':
			itemdel(8);
			break;
		case ')':
			itemdel(9);
			break;
		case '?':
			system("cls");
			readme();
			break;
		case 'o':
			for (i = -1; i < 2; i++)
				for (j = -1; j < 2; j++)
					if ((j == 0 && i != 0) || (j != 0 && i == 0))
						if (map[(*mob).y + j][(*mob).x + i] == '|' || map[(*mob).y + j][(*mob).x + i] == '/'){
							if (map[(*mob).y + j][(*mob).x + i] == '|')
								map[(*mob).y + j][(*mob).x + i] = '/';
							else if (map[(*mob).y + j][(*mob).x + i] == '/')
								map[(*mob).y + j][(*mob).x + i] = '|';
						}
			//mapdraw(); //Лишний же, с инфдравом следующим
			for (i = 0; i < mob1count; i++)
				if (mobs1[i].hp>0)
					coord(mobs1[i].x, mobs1[i].y, mobs1[i].id, mobs1[i].simv);
			//infdraw();
			break;
		case ' ':
			for (int i = 1; i < mob1count; i++){
				if ((mobs1[0].x == mobs1[i].x) && (mobs1[0].y == mobs1[i].y)){
					mobs1[i].hp -= 1;
					if (mobs1[i].hp <= 0){
						int scr;
						scr = mobs1[i].score + (rand() % 4 + 1);
						score = scr;
						log("пусто", 14, scr);
						kills += 1;
					}
				}
			}
			break;
		case 'z':
			if (heroeq.sv_rock == 1 || heroeq.sv_blind == 1 || heroeq.sv_fire == 1 || heroeq.bowl == 1){

				COORD position;
				HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				int x, y;
				char c;
				x = mobs1[0].x;
				y = mobs1[0].y;
				while (1){
					position.X = 0;
					position.Y = 44;
					SetConsoleCursorPosition(hConsole, position);
					c = getch();
					switch (c){
					case 'w':
						if ((mobs1[0].y - 5)<y)
							if (map[y - 1][x] != '#' && map[y - 1][x] != '|')
								y -= 1;
						break;
					case 's':
						if ((mobs1[0].y + 5)>y)
							if (map[y + 1][x] != '#' && map[y + 1][x] != '|')
								y += 1;
						break;
					case 'a':
						if ((mobs1[0].x - 5)<x)
							if (map[y][x - 1] != '#' && map[y][x - 1] != '|')
								x -= 1;
						break;
					case 'd':
						if ((mobs1[0].x + 5)>x)
							if (map[y][x + 1] != '#' && map[y][x + 1] != '|')
								x += 1;
						break;
					}

					if (c == 'c'){
						break;
					}

					if (c == 'x'){
						int racr;
						if (acr == 1) racr = 5;
						if (acr == 2) racr = 5;
						if (acr == 3) racr = 3;
						if (acr == 4) racr = 2;
						if (acr == 5) racr = 1;
						for (i = 0; i < mob1count; i++)
						   if (mobs1[i].x == x && mobs1[i].y == y){
								if (wizardcock(mobs1[0].y, mobs1[0].x, mobs1[i].y, mobs1[i].x, 20)){
									if (heroeq.sv_blind == 1 && mobs1[0].mana >= 15){ mobs1[i].look = 0; heroeq.sv_blind = 0; mobs1[0].mana -= 15; }
									if (heroeq.sv_fire == 1 && mobs1[0].mana >= 5){ mobs1[i].hp -= 10; heroeq.sv_fire = 0;  mobs1[0].mana -= 5; }
									if (heroeq.sv_rock == 1 && mobs1[0].mana >= 5){ mobs1[i].hp -= 4; heroeq.sv_rock = 0;  mobs1[0].mana -= 5; }
									if (heroeq.bowl == 1 && myinv.consumables[4].arrow > 0)
										if((rand() % racr + 1) == 1)
											{ mobs1[i].hp -= 4; myinv.consumables[4].arrow -= 1; }
										else{ log("Промах!                    ", 0, 0);
										myinv.consumables[4].arrow -= 1;
										}
								}
								break;
						   }
						break;
					}

					mapdraw();
					for (i = 0; i < mob1count; i++){
						if (mobs1[i].hp > 0)
							coord(mobs1[i].x, mobs1[i].y, mobs1[i].id, mobs1[i].simv);
					}
					coord(x, y, 500, 'X');
				}
			}
			break;
			//Н конец
		default:
			move(mob);
			break;
		}
		break;
		////
	case 1:case 2:case 3:case 4:case 5:case 6:case 7:case 8:case 9:case 10:
		if ((*mob).look > 0){//Интеллект есть только у тех, у кого обзор видимости есть
			IImap((*mob).y, (*mob).x, (*mob).id);//находится в майн.с, забивает рабочий массив цифрами
			int ni, nk;
			_Bool p = 0;
			ni = 0;
			nk = (*mob).look;//ограничение зоны видимости
			while (ni < nk){//пока номер кольца волны меньше границы зоны видимости
				for (int i = 0; i < 31; i++){
					for (int b = 0; b < 81; b++){
						if (R[i][b] == ni){
							if (R[i + 1][b] == 49 || R[i][b + 1] == 49 || R[i - 1][b] == 49 || R[i][b - 1] == 49){//если наша волна достигла моба
								pos(&(*mob).x, &(*mob).y);//внизу ищи
								p = 1;
								if (p == 1) break;
							}
							if (R[i + 1][b] == 50){ R[i + 1][b] = ni + 1; }//построение волны
							if (R[i - 1][b] == 50){ R[i - 1][b] = ni + 1; }//
							if (R[i][b + 1] == 50){ R[i][b + 1] = ni + 1; }//
							if (R[i][b - 1] == 50){ R[i][b - 1] = ni + 1; }//
						}
						if (p == 1) break;
					}
					if (p == 1) break;
				}
				if (p == 1) break;
				ni++;
			}
			p = 0;
		}

		/*Так, послушай внимательно, однажды с эльфами у меня вылетела прога, но сколько раз я ее потом
		не тестировал я не смог выявить эту ошибку снова, так что если будешь бороться с лучниками и вдруг вылетит, дай знать*/
		
		if ((*mob).look == 1){//Лучники только те, у кого зрение 1
			for (int i = (*mob).y - 5; i < (*mob).y + 5; i++)
				for (int b = (*mob).x - 5; b < (*mob).x + 5; b++)
					if (mobs1[0].y == i && mobs1[0].x == b)
						if (wizardcock(mobs1[0].y, mobs1[0].x, (*mob).y, (*mob).x, 20)){
				switch ((*mob).id){
				case 6:mobs1[0].hp -= (*mob).dmg + (rand() % (*mob).cri2 + (*mob).cri); if (mobs1[0].hp < 0) mobs1[0].hp = 0; break;
				case 7:eff1[(*mob).idEff].efbool = 1; break;
				}
				mobsay((*mob).id);
				Lbool = 1;
						}
		}
		
		if (rbool == 0 && Lbool != 1){
			for (i = -1; i < 2; i++)
				for (j = -1; j < 2; j++)
					if ((j == 0 && i != 0) || (j != 0 && i == 0))
						if ((*mob).x + i == mobs1[0].x && (*mob).y + j == mobs1[0].y){	
							
							x = (*mob).dmg + (rand() % (*mob).cri2 + (*mob).cri) - mobs1[0].defense;
							if (x > 0){
								mobs1[0].hp -= x;
								eff1[(*mob).idEff].efbool = 1;
							}
								if (mobs1[0].hp < 0)
								mobs1[0].hp = 0;
							
							mobsay((*mob).id);
							rbool = 1;
						}
		}
		
		if (rbool == 0 || Lbool == 1){
			i = rand() % 6;
			switch (i){

			case 0:
				travel(mob, -1, 0);
				break;
			case 1:
				travel(mob, 0, -1);
				break;
			case 2:
				travel(mob, 1, 0);
				break;
			case 3:
				travel(mob, 0, 1);
				break;
			case 4: case 5:case 6:
				break;
			}
		}
		break;
	default:
		printf("Кто ходит-то?!\n");
		getch();
		break;
	}
}
//Н внутри
void travel(struct Mob1 *mob, int plusx, int plusy) {
	char x, i,j;
	bool rbool;
	x = map[(*mob).y + plusy][(*mob).x + plusx];

	switch ((*mob).id){
	case 0:
		rbool = 0;
		if (wormscount>0)
			if ((j = searchworm((*mob).x + plusx, (*mob).y + plusy)) != -1){
				rbool = 1;
				while ((*worms).prewworm != NULL)
					worms = (*worms).prewworm;
				while ((*worms).num != j)
					worms = (*worms).nextworm;
				for (i = 0; i < (*worms).dlin; i++)
					if ((*mob).y + plusy == (*worms).part[i].y && (*mob).x + plusx == (*worms).part[i].x){
						(*worms).part[i].hp -= 10;// mobs1[0].dmg;
						if ((*worms).part[i].hp <= 0){
							wormsbroke(j, i);
						}
					}
			}
		if ((i = searchmob1((*mob).x + plusx, (*mob).y + plusy)) != -1){
			attack(i);
			rbool = 1;
		}
		if (rbool == 0){
			switch (x){
			case 'B':{ //Н
				int r;
				r = rand() % 100 + 1;
				map[(*mob).y + plusy][(*mob).x + plusx] = '_';
				if (r >= 1 && r <= 70){
					if (myinv.allitem < 10)
						itemrand(-1, -1, 100);
					else{ log("Тебе больше не унести         ", 0, 0); }
				}
				else if (r >= 71 && r <= 85){
					int rm;
					rm = rand() % 20 + 1;
					money += rm;
					golds += rm;
					log("Кошель пополнился               ", 0, 0);
				}
				else if (r >= 86 && r <= 100 ){
					if (myinv.consumables[4].arrow < 11){
						myinv.consumables[4].arrow += 1;
						log("Надена стрела                   ", 0, 0);
					}
					else { log("Колчан полон           ", 0, 0); }
				}
			}
				break;
			case '#': case '\'':
				move(mob);
				break;
			case ' ': case ',': case ';': case'.': case'%': case'/':case'=':case'_':case ':':case '^':case '*':	//H
				(*mob).x = (*mob).x + plusx;
				(*mob).y = (*mob).y + plusy;
				break;
			case '0':
				mobs1[0].hp = 0;
				break;
			case'@':		//Н
				map = mapnew(++mapnum);		
				torg = 0;
				for (int i = 0; i < 31; i++)
					for (int b = 0; b < 81; b++)
							eye2[i][b] = 0;
					
				break;		//Н
			default:
				break;
			}
			break;
		}

		////
	case 1:case 2:case 3:case 4:case 6:case 7:case 8:case 9:case 10:
		if ((i = searchmob1((*mob).x + plusx, (*mob).y + plusy)) == -1){
			switch (x){
			case '#': case '0':case '@':case '\'':
				move(mob);
				break;
			case ' ': case ',': case ';': case'.': case'%': case 'B':case'/':case'_': case ':':case '^':case '*': case '='://H
				;
				_Bool i=0;
				for (int w = 1; w < mob1count; w++){
					if ((mobs1[w].x != (*mob).x) && (mobs1[w].y != (*mob).y))
						i = 1;
				}
				if (i == 1){
					(*mob).x += plusx;
					(*mob).y += plusy;
				}
				
				break;
			}
		}
		break;
	case 5:
		if ((i = searchmob1((*mob).x + plusx, (*mob).y + plusy)) == -1){
			switch (x){
			case '#':case '@':
				move(mob);
				break;
			case ' ': case ',': case ';': case'.': case'%': case 'B':case'/':case'0': case ':':case '\'':case '*':case '='://H
				(*mob).x = (*mob).x + plusx;
				(*mob).y = (*mob).y + plusy;
				break;
			}
		}
		break;

	default:
		printf("Где мои ноги?!\n");
		getch();
		break;
	}
}

int searchmob1(int x, int y){
	int i;
	for (i = 0; i < mob1count; i++)
		if (mobs1[i].x == x && mobs1[i].y == y && mobs1[i].hp > 0)
			return i;		
	return -1;
}

void attack(int num){
	switch (mobs1[num].id){
	case 1:case 2:case 3:case 4:case 5:case 6:case 7:case 8:case 9:case 10:
		mobs1[num].hp -= mobs1[0].dmg + (rand() % mobs1[0].cri2 + mobs1[0].cri);
		if (mobs1[num].hp < 1){
			int scr;
			scr = mobs1[num].score + (rand() % 4 + 1);
			score = scr;
			log("пусто", 14, scr);
			kills += 1;
		}
		break;
	}
}
//H
void allEff(){
	for (int i = 0; i <= 4; i++){
		switch (i){
		case 0://ничего
			eff1[i].cycl = 0;
			eff1[i].endc = 0;
			eff1[i].id = i;
			eff1[i].result = 0;
			eff1[i].efbool = 0;
			break;
		case 1://жизнь
			eff1[i].cycl = 15;
			eff1[i].endc = 0;
			eff1[i].id = i;
			eff1[i].result = 1;
			eff1[i].efbool = 0;
			break;
		case 2://яд
			eff1[i].cycl = 32;
			eff1[i].endc = 0;
			eff1[i].id = i;
			eff1[i].result = -1;
			eff1[i].efbool = 0;
			break;
		case 3://чума
			eff1[i].cycl = 15;
			eff1[i].endc = 0;
			eff1[i].id = i;
			eff1[i].result = -2;
			eff1[i].efbool = 0;
			break;
		case 4://возгорание
			eff1[i].cycl = 15;
			eff1[i].endc = 0;
			eff1[i].id = i;
			eff1[i].result = -1;
			eff1[i].efbool = 0;
			break;
		default:
			printf("Нет конструктора эффектов к такому ID\n");
			getch();
			break;
		}
	}
}

//H
void mobsay(int mobid){
	//массив фраз для мобов
	char *ratsay[] = {
			{ "Крыса: \"Угрюмо поглядывает\"   " },
			{ "Крыса: \"Копается в мусоре\"    " },
			{ "Крыса: \"Тяжело вздыхает\"      " },
			{ "Крыса: \"Задумалась\"           " },
			{ "Крыса: \"Сверкнула глазами\"    " },
			{ "Крыса: \"Понюхала хвост\"       " },
			{ "Крыса: \"Огляделась\"           " },
			{ "Крыса: \"Грызет старый череп\"  " },
			{ "Крыса: \"Проголодалась\"        " },
			{ "Крыса: \"Возмущена!\"           " }
	};
	char *spasay[] = {
			{ "Паук: \"Перебирает лапками\"    " },
			{ "Паук: \"Плетет паутину   \"     " },
			{ "Паук: \"Клацнул жвалом \"       " },
			{ "Паук: \"Следит\"                " },
			{ "Паук: \"Готовится к атаке\"     " },
			{ "Паук: \"Заботится о паучатах\"  " },
			{ "Паук: \"Огляделся \"            " },
			{ "Паук: \"Хочет уползти\"         " },
			{ "Паук: \"Голоден\"               " },
			{ "Паук: \"Ненавидит!\"            " }
	};
	char *snasay[] = {
			{ "Змея: \"Зло шипит\"             " },
			{ "Змея: \"Греется у щели\"        " },
			{ "Змея: \"Делает выпад\"          " },
			{ "Змея: \"Свернулась в клубок\"   " },
			{ "Змея: \"Спряталась\"            " },
			{ "Змея: \"Поймала мышонка\"       " },
			{ "Змея: \"Готовтся к броску\"     " },
			{ "Змея: \"Боится\"                " },
			{ "Змея: \"Трясет хвостом\"        " },
			{ "Змея: \"Приближается\"          " }
	};
	char *elfsay[] = {
			{ "Эльф: Квалмэ ундумэ!            " },//Бездна смерти
			{ "Эльф: Лие десиэль?              " },//Ты закончил?
			{ "Эльф: Надуруан!                 " },//Трусливый пес
			{ "Эльф: Аута микула орку          " },//Иди поцелуй орка
			{ "Эльф: Амин делота ле!           " },// Я тебя ненавижу
			{ "Эльф: Лие холма ви эдан!        " },// Пахнешь, будто человек
			{ "Эльф: Унту эн локрим            " },// Сын змея
			{ "Эльф: Долле наа лост            " },//Пустоголовый
			{ "Эльф: Туа амин!                 " },//Помогите мне!
			{ "Эльф: Уа лле сином?             " }//Кто здесь?
	};
	char *melfsay[] = {
			{ "Эльф: Бездна смерти             " },
			{ "Эльф: Ты закончил?              " },
			{ "Эльф: Трусливый пес             " },
			{ "Эльф: Иди поцелуй орка          " },
			{ "Эльф: Я тебя ненавижу           " },
			{ "Эльф: Пахнешь, будто человек    " },
			{ "Эльф: Сын змея                  " },
			{ "Эльф: Пустоголовый              " },
			{ "Эльф: Помогите мне!             " },
			{ "Эльф: Кто здесь?                " }
	};
	char *gnosay[] = {//Кхуздул
			{ "Гном: Киндз зарам...            " },//Озеро крови...
			{ "Гном: Тхану хи куз келед        " },//Мои глаза не видели неба
			{ "Гном: Кура хара – мар кирзой    " },//Увидел орка - пинай сапогом
			{ "Гном: Дох!                      " },//Животное!
			{ "Гном: Дер крурир...             " },//Злые эльфы
			{ "Гном: Тхану дум хун             " },// Моя крепость разорена
			{ "Гном: Дайайрайкрайкаруй!        " },// Окружай!
			{ "Гном: Тер казад!                " },//Добрый гном
			{ "Гном: Мену,а хир то мар исс уп! " },//Уйди, а то в глаз дам
			{ "Гном: Казад ак бар!             " }//Гном всегда готов!
	};
	char *mgnosay[] = {
			{ "Гном: Озеро крови...            " },
			{ "Гном: Мои глаза не видели неба  " },
			{ "Гном: Увидел орка-пинай сапогом " },
			{ "Гном: Животное!                 " },
			{ "Гном: Злые эльфы...             " },
			{ "Гном: Моя крепость разорена!    " },
			{ "Гном: Окружай!                  " },
			{ "Гном: Добрый гном               " },
			{ "Гном: Уйди, а то в глаз дам!    " },
			{ "Гном: Гном всегда готов!        " }
	};
	char *wizsay[] = {
			{ "Маг: Бойся моей силы            " },
			{ "Маг: Юнец!                      " },
			{ "Маг: \"Бормочет\"               " },
			{ "Маг: МЕУС КАЛМИРОН!             " },
			{ "Маг: Иди с миром,откуда пришел  " },
			{ "Маг: ПЛЕОРИМ!                   " },
			{ "Маг: Дубина стаеросовая!        " },
			{ "Маг: Не смей прикасаться,смерд  " },
			{ "Маг: Тысячи лет!                " },
			{ "Маг: Заточение! Заточение!      " }
	};
	char *cobsay[] = {
			{ "Кобольд: не трогаю мою свечууу! " },
			{ "Кобольд: Аргх!                  " },
			{ "Кобольд: желтая рожа! проклятый!" },
			{ "Кобольд: руда, мне нужна руда!  " },
			{ "Кобольд: ты не мой брат!        " },
			{ "Кобольд: свеча... свечааа...    " },
			{ "Кобольд: дай! дай! дай!         " },
			{ "Кобольд: то мое, это мое        " },
			{ "Кобольд: ихиххиххиИХИХии!       " },
			{ "Кобольд: тссс...                " }
	};
	//а для летучей мыши нет, потому что она летает себе и летает
	COORD position;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	position.X = 1;
	position.Y = 36;
	SetConsoleCursorPosition(hConsole, position);
	SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 8));
	int a, b;
	a = rand() % 10 + 1;
	if (a <= 4){
		b = rand() % 9;
		switch (mobid){
		case 1:case 3:
			log(ratsay[b],0,0);
			break;
		case 2:
			log(spasay[b], 0, 0);
			break;
		case 4:
			log(snasay[b], 0, 0);
			break;
		case 6:
			if (myinv.consumables[3].mind == 0){
				log(elfsay[b], 0, 0);
			}
			else{
				log(melfsay[b], 0, 0);
			}
			break;
		case 7:
			log(wizsay[b], 0, 0);
			break;
		case 8:
			if (myinv.consumables[3].mind == 0){
				log(gnosay[b], 0, 0);
			}
			else{
				log(mgnosay[b], 0, 0);
			}
			break;
		case 9:
			log(cobsay[b], 0, 0);
			break;
		}
	}
}

void pos(int *xm, int *ym){
	int x, y;
	int min;
	y = *ym;
	x = *xm;
	min = 51;
	//поиск пути же
	if (R[y + 1][x] < min){
		min = R[y + 1][x];
		*ym = y + 1;
		*xm = x;
	}
	if (R[y][x - 1] < min){
		min = R[y][x - 1];
		*ym = y;
		*xm = x - 1;
	}
	if (R[y - 1][x] < min){
		min = R[y - 1][x];
		*ym = y - 1;
		*xm = x;
	}
	if (R[y][x + 1] < min){
		min = R[y][x + 1];
		*ym = y;
		*xm = x + 1;
	}
}

int wizardcock(int y, int x, int yy, int xx, int look){
	for (int i = 0; i < 31; i++){
		for (int b = 0; b < 81; b++){
			R[i][b] = 50;

			if (y == i && x == b)
				R[i][b] = 0;

			if (i == yy && b == xx)
				R[i][b] = 49;
		}
	}

	int ni, nk;
	_Bool p = 0;
	ni = 0;
	nk = look;
	while (ni < nk){
		for (int i = 0; i < 31; i++){
			for (int b = 0; b < 81; b++){
				if (R[i][b] == ni){
					if (R[i + 1][b] == 49 || R[i][b + 1] == 49 || R[i - 1][b] == 49 || R[i][b - 1] == 49){
						if (wizardbock(&xx, &yy)){
							return 1;
						}
						else{ return 0; }
						p = 1;
						if (p == 1) break;
					}
					if (R[i + 1][b] == 50){ R[i + 1][b] = ni + 1; }
					if (R[i - 1][b] == 50){ R[i - 1][b] = ni + 1; }
					if (R[i][b + 1] == 50){ R[i][b + 1] = ni + 1; }
					if (R[i][b - 1] == 50){ R[i][b - 1] = ni + 1; }
				}
				if (p == 1) break;
			}
			if (p == 1) break;
		}
		if (p == 1) break;
		ni++;
	}
	p = 0;
}

int wizardbock(int *xm, int *ym){
	int x, y;
	int min;
	y = *ym;
	x = *xm;
	min = 51;
	while (1){
		if (R[y + 1][x] < min){
			min = R[y + 1][x];
			*ym = y + 1;
			*xm = x;
		}
		if (R[y][x - 1] < min){
			min = R[y][x - 1];
			*ym = y;
			*xm = x - 1;
		}
		if (R[y - 1][x] < min){
			min = R[y - 1][x];
			*ym = y - 1;
			*xm = x;
		}
		if (R[y][x + 1] < min){
			min = R[y][x + 1];
			*ym = y;
			*xm = x + 1;
		}
		if (R[y + 1][x + 1] < min){
			min = R[y][x + 1];
			*ym = y + 1;
			*xm = x + 1;
		}
		if (R[y - 1][x + 1] < min){
			min = R[y][x + 1];
			*ym = y - 1;
			*xm = x + 1;
		}
		if (R[y + 1][x - 1] < min){
			min = R[y][x + 1];
			*ym = y + 1;
			*xm = x - 1;
		}
		if (R[y - 1][x - 1] < min){
			min = R[y][x + 1];
			*ym = y - 1;
			*xm = x - 1;
		}
		if (R[*ym][*xm] == 0){
			return 1;
			break;
		}
		else{
			y = *ym;
			x = *xm;
			if (map[y][x] == '#' || map[y][x] == '|'){
				return 0;
				break;
			}
		}
	}
}

void trade(){
	char c;
	int z = 0, z2;

	gotoxy(30, 10);
	printf("+---------------------------+");
	gotoxy(30, 11);
	printf("|/ Таинственный торговец   \\|");
	gotoxy(30, 12);
	printf("|    1)                     |");
	gotoxy(30, 13);
	printf("|    2)                     |");
	gotoxy(30, 14);
	printf("|    3)                     |");
	gotoxy(30, 15);
	printf("|\\   Денег:                /|");
	gotoxy(30, 16);
	printf("+---------------------------+");
	gotoxy(42, 15); printf("%d", money);
	while (z < 4){
		z++;
		if (z == 1){
			if (torg != 1)
				z2 = rand() % 9 + 1;
			else z2 = tov[0];
			gotoxy(37, 12);
			switch (z2){
			case 1:
				printf("Бутыль жизни(20)");
				price[0] = 20;
				break;
			case 2:
				printf("Бутыль яда(5)");
				price[0] = 5;
				break;
			case 3:
				printf("Словарь языков(80)");
				price[0] = 80;
				break;
			case 4:
				printf("Бутыль маны(30)");
				price[0] = 30;
				break;
			case 5://
				printf("Яблоко(10)");
				price[0] = 5;
				break;
			case 6:
				printf("Г.яблоко(5)");
				price[0] = 5;
				break;
			case 7:
				printf("Солонина(18)");
				price[0] = 18;
				break;
			case 8:
				printf("Ч.хлеб(4)");
				price[0] = 4;
				break;
			case 9:
				printf("Г.гриб(1)");
				price[0] = 1;
				break;
			}
			tov[0] = z2;
		}
		if (z == 2){
			if (torg != 1)
				z2 = rand() % 9;
			else z2 = tov[1];
			gotoxy(37, 13);
			switch (z2){
			case 0:
				printf("Хороший меч (40)");
				price[1] = 40;
				break;
			case 1:
				printf("Хороший шлем(20)");
				price[1] = 20;
				break;
			case 2:
				printf("Хорошая броня(20)");
				price[1] = 20;
				break;
			case 3:
				printf("Хороший лук(80)");
				price[1] = 80;
				break;
			case 4:
				printf("Нож(20)");
				price[1] = 20;
				break;
			case 5:
				printf("Тяж.меч(54)");
				price[1] = 54;
				break;
			case 6:
				printf("Дубина(18)");
				price[1] = 18;
				break;
			case 7:
				printf("Дуб.лук(54)");
				price[1] = 54;
				break;
			case 8:
				printf("Осин.лук(35)");
				price[1] = 35;
				break;
			case 9:
				printf("Старый посох(15)");
				price[1] = 15;
				break;
			}
			tov[1] = z2;
		}
		if (z == 3){
			if (torg != 1)
				z2 = rand() % 3;
			else z2 = tov[2];
			gotoxy(37, 14);
			switch (z2){
			case 0:
				printf("Св.\"Огонь\"(40)");
				price[2] = 40;
				break;
			case 1:
				printf("Св.\"Обрушение\"(35)");
				price[2] = 35;
				break;
			case 2:
				printf("Св.\"Слепота\"(80)");
				price[2] = 80;
				break;
			case 3:
				printf("Св.\"Изучение\"(40)");
				price[2] = 40;
				break;
			case 4:
				printf("Пустая книга(90)");
				price[2] = 90;
				break;
			case 5:
				printf("З.книга(40)");
				price[2] = 40;
				break;
			case 6:
				printf("Мертв.книга(20)");
				price[2] = 20;
				break;
			case 7:
				printf("Книга знаний(100)");
				price[2] = 100;
				break;
			case 8:
				printf("Бурдюк(45)");
				price[2] = 45;
				break;

			}
			tov[2] = z2;
		}
	}
	gotoxy(0, 44);
	torg = 1;
	c = getch();
	if (myinv.allitem < 10)
		switch (c){
		case '1':
			if (money >= price[0]){
				money -= price[0];
				itemnew(1, tov[0]);
			}
			break;
		case '2':
			if (money >= price[1]){
				money -= price[1];
				itemnew(2, tov[1]);
			}
			break;
		case '3':
			if (money >= price[2]){
				money -= price[2];
				itemnew(3, tov[2]);
			}
			break;
	}

}


void newworm(int dlin, bool boss){
	int i;
	static int num = 0;
	struct Sworm *rsworm, *defworm;
	//Налаживание связей
	if (wormscount == 0){
		worms = (struct Sworm*)malloc(sizeof(struct Sworm));
		(*worms).prewworm = (*worms).nextworm = NULL;
		defworm = worms;
	}
	else{
		defworm = worms;
		while ((*worms).nextworm != NULL)
			worms = (*worms).nextworm;
		rsworm = worms;
		(*worms).nextworm = (struct Sworm*)malloc(sizeof(struct Sworm));
		worms = (*worms).nextworm;
		(*worms).prewworm = rsworm;
		(*worms).nextworm = NULL;
	}

	//Инициализация
	(*worms).dlin = dlin;
	(*worms).num = num++;
	(*worms).part = (struct wormpart*)malloc(dlin*sizeof(struct wormpart));

	for (i = 0; i < dlin; i++)
		(*worms).part[i].invis = true;

	(*worms).part[0].simv = 'Y';
	(*worms).part[0].head = true;
	for (i = 1; i < dlin; i++)
		(*worms).part[i].simv = 'w';

	(*worms).status = 0;
	(*worms).maxcdsbok = 4;
	(*worms).maxcdsniz = 5;
	(*worms).maxcdnew = 10;


	(*worms).cdsbok = (*worms).maxcdsbok;
	if (boss == 1){
		(*worms).cdnew = (*worms).maxcdnew;
		(*worms).cdsniz = (*worms).maxcdsniz;
	}
	else{
		(*worms).cdnew = -10;
		(*worms).cdsniz = -10;
	}

	if (boss == true){
		(*worms).boss = true;
		(*worms).part[dlin - 1].simv = 'Y';
		(*worms).part[dlin - 1].head = true;
		for (i = 1; i < dlin - 1; i++)
			(*worms).part[i].hp = 3;
		(*worms).part[0].hp = (*worms).part[dlin - 1].hp = 6;

	}
	else{
		(*worms).boss = false;
		for (i = 0; i < dlin; i++)
			(*worms).part[i].hp = 1;
	}
	for (i = 0; i < (*worms).dlin; i++)
		(*worms).part[i].x = (*worms).part[i].y = -1;
	wormscount++;
	worms = defworm;
}

void wormsmove(){
	int i, j, x;
	while ((*worms).prewworm != NULL)
		worms = (*worms).prewworm;
	while (1){
	if ((*worms).status == 0){
			if ((*worms).cdnew == 0)
				(*worms).status = 3;
			else  if ((*worms).cdsbok == 0)
				(*worms).status = 2;
			else if ((*worms).cdsniz == 0)
				(*worms).status = 1;
		}

		switch ((*worms).status){
		case 0:
			break;
		case 1:
			if ((*worms).cdsniz == 0){
				(*worms).snizx = mobs1[0].x;
				(*worms).snizy = mobs1[0].y;
				(*worms).cdsniz = -1;
				log("Земля расходится под ногами", 0, 0);
			}
			else if ((*worms).cdsniz == -1){
				(*worms).part[0].x = (*worms).snizx;
				(*worms).part[0].y = (*worms).snizy;
				(*worms).part[0].invis = 0;
				(*worms).cdsniz = (*worms).maxcdsniz;
				if ((x = searchmob1((*worms).part[0].x, (*worms).part[0].y)) != -1)
					mobs1[x].hp = 0;
			}
			else if ((*worms).cdsniz == (*worms).maxcdsniz){
				map[(*worms).part[0].y][(*worms).part[0].x] = '0';
				(*worms).part[0].x = -1;
				(*worms).part[0].y = -1;
				(*worms).part[0].invis = 1;
				(*worms).status = 0;
			}
			break;

		case 2:
			if ((*worms).cdsbok == 0){
				if (mobs1[0].x > (mapx - mobs1[0].x))
					i = mapx - mobs1[0].x;
				else i = mobs1[0].x;
				if (mobs1[0].y > (mapy - mobs1[0].y))
					j = mapy - mobs1[0].y;
				else j = mobs1[0].y;

				if (i < (*worms).dlin * 3 || j < (*worms).dlin * 3){
					if (i > j){
						if (j == mobs1[0].y)
							(*worms).part[0].y = 1;
						else
							(*worms).part[0].y = mapy - 2;
						(*worms).part[0].x = mobs1[0].x;
					}
					else {
						if (i == mobs1[0].x)
							(*worms).part[0].x = 1;
						else
							(*worms).part[0].x = mapx - 2;
						(*worms).part[0].y = mobs1[0].y;
					}
					(*worms).gotox = mobs1[0].x;
					(*worms).gotoy = mobs1[0].y;
					(*worms).part[0].invis = 0;
					(*worms).cdsbok = -1;
				}
				else (*worms).status = 0;
			}

			/*else */ if ((*worms).cdsbok == -1){
				for (i = 0; i < 1/*(*worms).dlin /2*/; i++)
					if ((*worms).part[0].x != (*worms).gotox || (*worms).part[0].y != (*worms).gotoy){
						for (j = (*worms).dlin - 1; j > 0; j--){
							(*worms).part[j].x = (*worms).part[j - 1].x;
							(*worms).part[j].y = (*worms).part[j - 1].y;
							(*worms).part[j].invis = (*worms).part[j - 1].invis;
						}
						if ((*worms).part[0].x != -1){
							if ((*worms).part[0].x > (*worms).gotox)
								(*worms).part[0].x--;
							else if ((*worms).part[0].x < (*worms).gotox)
								(*worms).part[0].x++;
							if ((*worms).part[0].y >(*worms).gotoy)
								(*worms).part[0].y--;
							else if ((*worms).part[0].y < (*worms).gotoy)
								(*worms).part[0].y++;
							if ((x = searchmob1((*worms).part[0].x, (*worms).part[0].y)) != -1)
								mobs1[x].hp = 0;
						}
					}
					else {
						if ((*worms).gotoy != -1)
							map[(*worms).gotoy][(*worms).gotox] = '0';
						(*worms).part[0].invis = 1;
						(*worms).part[0].x = (*worms).part[0].y = -1;
					}



					(*worms).cdsbok = (*worms).maxcdsbok;
					(*worms).status = 0;
					for (i = 0; i < (*worms).dlin; i++)
						if ((*worms).part[i].x != -1){
							(*worms).cdsbok = -1;
							(*worms).status = 2;
						}
			}
			break;
		case 3:
			if ((*worms).cdnew == 0){
				newworm((*worms).dlin, false);
				(*worms).cdnew = (*worms).maxcdnew;
			}
			else if ((*worms).cdnew == (*worms).maxcdnew){
				(*worms).status = 0;
			}
			break;
		}



		if ((*worms).cdsniz > 0 && (*worms).status != 1)
			(*worms).cdsniz--;
		if ((*worms).cdsbok > 0 && (*worms).status != 2)
			(*worms).cdsbok--;
		if ((*worms).cdnew > 0 && (*worms).status != 3)
			(*worms).cdnew--;


		if ((*worms).nextworm != NULL)
			worms = (*worms).nextworm;
		else {
			while ((*worms).prewworm != NULL)
				worms = (*worms).prewworm;
			return;
		}
	}
}

int searchworm(int x, int y){
	int i, num;
	struct Sworm *defworm;

	defworm = worms;

	while ((*worms).prewworm != NULL)
		worms = (*worms).prewworm;

	num = -1;
	while (worms != NULL && num == -1){
		for (i = 0; i < (*worms).dlin; i++){
			if ((*worms).part[i].x == x && (*worms).part[i].y == y){
				num = (*worms).num;
				break;
			}
		}
		worms = (*worms).nextworm;
	}
	worms = defworm;
	if (num != -1){
		return num;
	}
	else return -1;
}

void wroke(num, part){
	int  i;
	struct Sworm *defworm, *resworm;

	resworm = defworm = worms;

		
	while ((*worms).num != num)
		worms = (*worms).nextworm;

	if ((*worms).boss == true){
		if ((*worms).dlin < 4 || ((*worms).dlin == 4 && (part == 2 || part == 1))){

			if ((*worms).prewworm != NULL && (*worms).nextworm == NULL){
				(*(*worms).prewworm).nextworm = NULL;
				worms = (*worms).prewworm;
				free(resworm);
			}
			else if ((*worms).nextworm != NULL && (*worms).prewworm == NULL){
				(*(*worms).nextworm).prewworm = NULL;
				worms = (*worms).nextworm;
				free(resworm);
			}
			else if ((*worms).nextworm == NULL && (*worms).prewworm == NULL){
				free(resworm);
			}

			else if ((*worms).nextworm != NULL && (*worms).prewworm != NULL){
				(*(*worms).prewworm).nextworm = (*worms).nextworm;
				(*(*worms).nextworm).prewworm = (*worms).prewworm;
				worms = (*worms).nextworm;
				free(resworm);
			}
			wormscount--;
		}


		else if (part == (*worms).dlin - 1 || part == (*worms).dlin - 2){
			for (i = part; i < (*worms).dlin; i++){
				(*worms).part[i].x = (*worms).part[i].y = -1;
				(*worms).part[i].invis = 1;
				(*worms).part[i].hp = 0;
			}
			if ((*worms).boss == 1){
				(*worms).part[part-1 ].simv = 'Y';
				(*worms).part[part -1].head = 1;
				(*worms).part[part -1].hp = (*worms).part[0].hp;
			}
			(*worms).dlin = part;
			worms = defworm;
		}


		else{
			newworm((*worms).dlin - part - 1, true);
			while ((*resworm).nextworm != NULL)
				resworm = (*resworm).nextworm;

			for (i = 0; i < (*resworm).dlin; i++){
				(*resworm).part[i].hp = (*worms).part[(*worms).dlin - 1 - i].hp;
				(*resworm).part[i].invis = (*worms).part[(*worms).dlin - 1 - i].invis;
				(*resworm).part[i].x = (*worms).part[(*worms).dlin - 1 - i].x;
				(*resworm).part[i].y = (*worms).part[(*worms).dlin - 1 - i].y;
			}
			(*resworm).part[(*resworm).dlin - 1].hp = (*resworm).part[0].hp;
			(*resworm).status = 2;
			(*resworm).cdsbok = -1;

			(*resworm).gotox = (*resworm).part[(*resworm).dlin - 1].x;
			(*resworm).gotoy = (*resworm).part[(*resworm).dlin - 1].y;

			if (part == 0 || part == 1|| part == 2){
				resworm = worms;
				if ((*worms).prewworm != NULL && (*worms).nextworm == NULL){
					(*(*worms).prewworm).nextworm = NULL;
					worms = (*worms).prewworm;
					free(resworm);
				}
				else if ((*worms).nextworm != NULL && (*worms).prewworm == NULL){
					(*(*worms).nextworm).prewworm = NULL;
					worms = (*worms).nextworm;
					free(resworm);
				}
				else if ((*worms).nextworm == NULL && (*worms).prewworm == NULL){
					free(resworm);
				}

				else if ((*worms).nextworm != NULL && (*worms).prewworm != NULL){
					(*(*worms).prewworm).nextworm = (*worms).nextworm;
					(*(*worms).nextworm).prewworm = (*worms).prewworm;
					worms = (*worms).nextworm;
					free(resworm);
				}
				wormscount--;
			}
			else{
				for (i = part; i < (*worms).dlin; i++){
					(*worms).part[i].x = (*worms).part[i].y = -1;
					(*worms).part[i].invis = 1;
					(*worms).part[i].hp = 0;
				}
				(*worms).dlin = part;
				if (part != 2){
					(*worms).part[(*worms).dlin - 1].simv = 'Y';
					(*worms).part[(*worms).dlin - 1].hp = (*worms).part[0].hp;
				}
				worms = defworm;
			}
		}
	}



	else  if ((*worms).boss == false){ 
		 if (((*worms).dlin == 4 && part == 2) || part == 0 || part == 1|| part == 2){

			 if ((*worms).prewworm != NULL && (*worms).nextworm == NULL){
				 (*(*worms).prewworm).nextworm = NULL;
				 worms = (*worms).prewworm;
				 free(resworm);
			 }
			 else if ((*worms).nextworm != NULL && (*worms).prewworm == NULL){
				 (*(*worms).nextworm).prewworm = NULL;
				 worms = (*worms).nextworm;
				 free(resworm);
			 }
			 else if ((*worms).nextworm == NULL && (*worms).prewworm == NULL){
				 free(resworm);
			 }

			 else if ((*worms).nextworm != NULL && (*worms).prewworm != NULL){
				 (*(*worms).prewworm).nextworm = (*worms).nextworm;
				 (*(*worms).nextworm).prewworm = (*worms).prewworm;
				 worms = (*worms).nextworm;
				 free(resworm);
			 }
			 wormscount--;
		}
		else {
			for (i = part; i < (*worms).dlin; i++){
				(*worms).part[i].x = (*worms).part[i].y = -1;
				(*worms).part[i].invis = 1;
				(*worms).part[i].hp = 0;
			}
			(*worms).dlin = part;
		}		
	}
}
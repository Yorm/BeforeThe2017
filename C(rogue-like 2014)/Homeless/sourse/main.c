#include <stdio.h>
#include <Windows.h>
#include <locale.h>
#include <stdlib.h>
#include "gen.h"
#include "mobs.h"
#include "items.h"
#include "global.h"

void mainMenu();
void mapdraw();
void infdraw();
void coord(int x, int y, int id, char simv);
void readme();
void story();
void gotoxy(int y, int x);
void lvlup();
char *_infl[43] = { "         " };
int colo[43];
int dmg[43];

void inwtgen();
void traps();
void gg();


char** mapnew(int num); //Н

int mapx, mapy;


char cnum[3];
void mapgenerate(FILE *mapfile);

struct room{
	int x, y;
	int x2, y2;
	int gor, ver;
	int num;
	int roomx, roomy;//горизонтальные
	int roomx2, roomy2;//вертикальные
	int doornum;
};


main(){
	int i, j;
	int cycl=0;//цикл восстановления
	int hplog, hplog2;
	int mana, mana2;

	for (int i = 0; i < 43; i++){//Забиваем лог
		_infl[i] = "  ";
		colo[i] = 0;
		dmg[i] = 0;
	}

//
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);  //H
	system("mode con cols=120 lines=46");
	system("color 06");//цвет фона и цвет шрифта консоли(F-фон 0-шрифт), 150 - справка
	setlocale(LC_ALL, "Russian");
	srand(time(NULL));
	//system("Title Rogue -beta-");
	SetConsoleTitle(TEXT("Homeless"));
	
	wormscount = 0; //H	
	mapnum =0;
	map = mapnew(++mapnum);

	score = 0;
	olvlup = 43;
	lvl = 1;
	hunger = 0;
	money = 0;
	golds = 0;
	kills = 0;
	lows = 0;
	potrs = 0;
	allEff();
	mainMenu();
	//story();/*КАКАЯ ТО СТРАННОСТЬ ПРИ ЗАГРУЗКЕ ИСТОРИИ ПЕРЕД КАРТОЙ, КОРОЧЕ ЕСЛИ ДОБАВИТЬ 4 КАРТЫ ТО ВЫЛЕТАЕТ*/
	mapdraw();
	infdraw();
	
	for (i = 0; i < mob1count; i++)
		if (mobs1[i].hp>0)
			coord(mobs1[i].x, mobs1[i].y, mobs1[i].id, mobs1[i].simv);

	//---------------------------------------------------------------------------------------------------------------
	
	while (mobs1[0].hp>0){
		
		hplog = mobs1[0].hp;
		mana = mobs1[0].mana;

		gotoxy(0, 44);
		
		//движение мобов 
		for (i = 0; i < mob1count; i++)
			if (mobs1[i].hp > 0)
				move(&mobs1[i]);
		if (wormscount > 0)
			wormsmove();
		
		//слдующий цикл отвечает за регенерацию параметров
		cycl++;
		if (cycl == 15){
			if (mobs1[0].hp < mobs1[0].hpe - 1 && hunger <= 40)
				mobs1[0].hp++;
			if (mobs1[0].mana < mobs1[0].manae - 1 && hunger <= 40)
				mobs1[0].mana++;
			if (hunger < 50){
				hunger++;
			}
			if (hunger > 40)
				mobs1[0].hp--;
			cycl = 0;
		}
		
		//рулетка эффектов
		for (int nom = 0; nom < 5; nom++){
			if (eff1[nom].efbool == 1 && mobs1[0].hp <= mobs1[0].hpe){
				eff1[nom].endc++;
				mobs1[0].hp += eff1[nom].result;
			}
			if (eff1[nom].cycl == eff1[nom].endc){
				eff1[nom].efbool = 0;
				eff1[nom].endc = 0;
			}
		}
		
		traps();
	
		if (eff1[4].efbool == 1 && map[mobs1[0].y][mobs1[0].x]==':'){
			eff1[4].efbool = 0;
			log("Потушен                             ", 0, 0);
		}

		hplog2 = mobs1[0].hp;
		mana2 = mobs1[0].mana;
		if (hplog - hplog2 > 0){
			log("пусто", 4, hplog - hplog2);
		}
		if (hplog - hplog2 < 0){
			log("пусто", 2, hplog2  - hplog);
		}
		if (mana - mana2 > 0){
			log("пусто", 1, mana - mana2);
		}
		if (mana - mana2 < 0){
			log("пусто", 9, mana2 - mana);
		}
		if (score >= olvlup){
			lvl++;
			olvlup += (mapnum * 2 + mapnum) + (15 * (mapnum + 1));
			score = 0;
			lvlup();
		}
		mapdraw();
		for (i = 0; i < mob1count; i++){
			if (mobs1[i].hp > 0){
				coord(mobs1[i].x, mobs1[i].y, mobs1[i].id, mobs1[i].simv);
			}
			else mobs1[i].x = mobs1[i].y = 0;//Смещаем трупы в вверх дабы нам не выводились сообщения на месте их смерти о том что они напали на нас
		}




		if (wormscount > 0){
			while (1){
				for (j = 0; j < (*worms).dlin; j++)
					if ((*worms).part[j].invis == 0)
						coord((*worms).part[j].x, (*worms).part[j].y, 9, (*worms).part[j].simv);

				if ((*worms).nextworm != NULL)
					worms = (*worms).nextworm;
				else
					break;
			}
		}



		if ((rand()%50+1)==1)
			log("\"Кап-кап-кап...\"                  ",0,0);
		log("рисуем", 20, 1000);
		if (mobs1[0].hp>mobs1[0].hpe)
			mobs1[0].hp = mobs1[0].hpe;
		infdraw();

		
	}
	//----------------------------------------------------------------------------------------------------

		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 4));//H
		system("cls");
		gotoxy(50 , 5);
		printf("This Is The End\n");
		gotoxy(49, 7);
		printf("Золота собрано: %d", golds);
		gotoxy(50, 8);
		printf("Врагов убито: %d", kills);
		gotoxy(49, 9);
		printf("Ловушек вскрыто: %d", lows);
		gotoxy(48, 10);
		printf("Еды/зелий потреблено: %d", potrs);
		//printf("Your Way Is Over");
		//printf("You Life Is Over");

	getch();
	mapnew(0);
	system("pause");
	return 0;
}


void gotoxy(int x, int y){
	COORD position;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	position.X = x;
	position.Y = y;
	SetConsoleCursorPosition(hConsole, position);
}

void readme(){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	gotoxy(0, 0);
	SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 7));
	char c;
	FILE *reference;
	fopen_s(&reference, "data\\reference", "r");
	do {
		c = getc(reference);
		if (c != '$')
			printf("%c", c);
	} while (c != '$');
	getch();
	system("cls");
}

void mapdraw(){                                 
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);  
	int i, j;
	gotoxy(0, 0);
	eyes();
	for (i = 0; i < mapy; i++){
		for (j = 0; j < mapx; j++){
			if (eye2[i][j] == 1 || eye2[i][j] == 2 ||  eye2[i][j] == 9){
				switch (map[i][j])
				{
				case '#':
					SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 6));
					printf("%c", map[i][j]);
					break;
				case ',':case ';':
					SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 2));
					printf("%c", map[i][j]);
					break;
				case 'B':case 'R':case 'T':case 'F':
					SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 3));
					printf("%c", map[i][j]);
					break;
				case '0':
					SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 8));
					printf("%c", map[i][j]);
					break;
				case ':':
					SetConsoleTextAttribute(hConsole, (WORD)((9 << 4) | 1));
					printf("%c", map[i][j]);
					break;
				case '@':
					SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 5));
					printf("%c", map[i][j]);
					break;
				case '.':
					SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 7));
					printf("%c", map[i][j]);
					break;
				case '\'':
					SetConsoleTextAttribute(hConsole, (WORD)((1 << 4) | 9));
					printf("%c", map[i][j]);
					break;
				case '*':
					SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 5));
					printf("%c", map[i][j]);
					break;
				default:
					SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 6));
					printf("%c", map[i][j]);
					break;
				}
			}
			else if(eye2[i][j] == 3){	
				SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 1));
				if (map[i][j] == '^')
					coord(j,i,99,'.');
				else
					printf("%c", map[i][j]);
				}
			else {
				SetConsoleTextAttribute(hConsole, (WORD)((0 << 0) | 0));
				printf(" ");
			}

		}
		printf("\n");
	}
}


void eyes(){
	for (int i = 0; i < mapy; i++){
		for (int b = 0; b < mapx; b++){
			if (eye2[i][b] == 1 || eye2[i][b] == 2)
				eye2[i][b] = 3;
			if (map[i][b] == '+')
				eye2[i][b] = 9;
		}
	}
	for (int i = 1; i < mapy-1; i++){
		for (int b = 1; b < mapx-1; b++){
			if (map[i][b] == '.' || map[i][b] == '/' || map[i][b] == ':' || map[i][b] == ',' || map[i][b] == ';'
				|| map[i][b] == '\'' || map[i][b] == '0' || map[i][b] == 'B' || map[i][b] == '@' ||  map[i][b] == '_' 
				|| map[i][b] == 'S' || map[i][b] == '^' || map[i][b] == '*' || map[i][b] == '=')
				eye[i][b] = 50;

			if (map[i][b] == '#' || map[i][b] == '|' || map[i][b] == ' ')
				eye[i][b] = 51;

			if ( mobs1[0].y==i  &&  mobs1[0].x==b)
				eye[i][b] = 0;
		}
	}
	int ni, nk;
	ni = 0;
	nk = vig;
	while (ni < nk){
		for (int i = 0; i < mapy; i++){
			for (int b = 0; b < mapx; b++){
				if (eye[i][b] == ni){
					if (eye[i + 1][b] == 50){ eye[i + 1][b] = ni + 1; eye2[i + 1][b] = 1; eye2[i][b] = 1; }
					if (eye[i - 1][b] == 50){ eye[i - 1][b] = ni + 1; eye2[i - 1][b] = 1; eye2[i][b] = 1; }
					if (eye[i][b + 1] == 50){ eye[i][b + 1] = ni + 1; eye2[i][b + 1] = 1; eye2[i][b] = 1; }
					if (eye[i][b - 1] == 50){ eye[i][b - 1] = ni + 1; eye2[i][b - 1] = 1; eye2[i][b] = 1; }
				}
			}
		}
		ni++;
	}
	eye2[mobs1[0].y][mobs1[0].x] = 1;
	for (int i = 0; i < mapy; i++){
		for (int b = 0; b < mapx; b++){


			if (map[i][b] == '#' || map[i][b] == '|'){
				if (eye2[i + 1][b] == 1)
					eye2[i][b] = 2;
				if (eye2[i - 1][b] == 1)
					eye2[i][b] = 2;
				if (eye2[i][b + 1] == 1)
					eye2[i][b] = 2;
				if (eye2[i][b - 1] == 1)
					eye2[i][b] = 2;
			}

		}
	}
	
	

}

void log(char l[40],int typec,int t){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (t == 0){
		for (int i = 43; i > 0; i--){
			_infl[i] = _infl[i - 1];
		}
		_infl[0] = l;
	}

	for (int i = 0; i < 8; i++){
		gotoxy(2, 36 + i);//37,38,39,40,41,42,43
		switch (i){
		case 0:case 1:
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 14));
			break;
		case 2:case 3:
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));
			break;
		case 4:case 5:
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 7));
			break;
		case 6:case 7:
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 8));
			break;
		}
		printf("%s", _infl[i]);
	}

	if (t > 0 && t!=1000){
		
		for (int i = 43; i > 0; i--){
			dmg[i] = dmg[i - 1];
			colo[i] = colo[i - 1];
		}
		dmg[0] = t;
		colo[0] = typec;
		
	}
	for (int i = 0; i < 8; i++){
		gotoxy(45, 36 + i);
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | colo[i]));
		if (colo[i] == 4 || colo[i] == 1)
			printf("-");
		if (colo[i] == 2 || colo[i] == 9 )
			printf("+");
		if (colo[i] == 14)
			printf("+");
		printf("%d  ", dmg[i]);
	}
}
//H внутри
void infdraw(){
	COORD position;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int a, i, j, type;
	char *undr[] = {
			{ "не разобрать  " }, 
			{ "каменный пол  " }, 
			{ "трава         " }, 
			{ "вода          " }, 
			{ "бочка         " }, 
			{ "осколок камня " }, 
			{ "помостки      " },  
			{ "высокая трава " }, 
			{ "деревянный пол" }, 
			{ "мусор         " }, 
			{ "дверной проем " },
			{ "земля         " },
			{ "каменный пол  " },
			{ "лужа          " },
			{ "пустота       " },
			{ "телепорт      " },
			{ "ловушка       " }
	};
	gotoxy(93, 9);
	SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 5));
	switch (map[mobs1[0].y][mobs1[0].x]){
	case ',':{ a = 2; break; }
	case 'B':{ a = 4; break; }
	case '.':{ a = 1; break; }
	case '%':{ a = 6; break; }
	case ';':{ a = 7; break; }
	case '=':{a = 8; break; }
	case '_':{a = 9; break; }
	case '/':{a = 10; break; }
	case ':':{a = 13; break; }
	case ' ':{a = 14; break; }
	case '*':{a = 15; break; }
	case '^':{a = 16; break; }// Н
	default: { a = 0; }
	}


	SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 6));
	gotoxy(2, 34);
	printf("Под ногами: %s", undr[a]);//underfoot
	gotoxy(52, 36);
	SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 1));
	printf("Мана:%d/%d  ", mobs1[0].mana, mobs1[0].manae);


	gotoxy(52, 37);
	if (eff1[2].efbool == 1)
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 2));
	else if (eff1[3].efbool == 1)
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 8));
	else if (eff1[4].efbool == 1)
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 14));
	else if (eff1[1].efbool == 1)
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 7));
	else
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 4));
	printf("Жизни:%d", mobs1[0].hp);

	SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 4));
	printf("/%d  ", mobs1[0].hpe);
	SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 7));
	gotoxy(52, 38);
	printf("Меткость: %d/5", acr);
	gotoxy(52, 39);
	printf("Сила: %d/5", stren);
	gotoxy(52, 40);
	printf("Интеллект: %d/5", mental);
	

	gotoxy(52, 42);
	SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 8));
	printf("Кошель: %d", money);
	gotoxy(52, 43);
	if (myinv.consumables[4].arrow > -1){
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 7));
		printf("Стрел: %d", myinv.consumables[4].arrow);
	}	
	SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 8));
	gotoxy(15, 33);
	printf("Опыт: %d/%d (lvl.%d)", score, olvlup, lvl);
	gotoxy(69, 34);
	if (hunger >= 0 && hunger < 25){
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 2));
		printf("Не голоден    ");
	}
	if (hunger >= 25 && hunger <= 40){
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 6));
		printf("Урчит в животе");
	}
	if (hunger > 40 && hunger < 50){
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 4));
		printf("Голоден       ");
	}
	SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 6));
	gotoxy(87, 43);
	printf("Нажмите \'l\' для вызова журнала");
	gotoxy(87, 34);
	printf("Нажмите \'?\' для вызова справки");
	gotoxy(87, 33);
	printf("Нажмите \'\\\' для сохранения");
	/*gotoxy(2, 33);
	printf("Перемещение(атака)-wasd, использовать - 0..9,выбросить shift+(0..9),открыть-о,");
	gotoxy(2, 34);
	printf("выстрелить-(взять в руки)+z+(выбрать цель)+x,отмена-c,торговля(рядом с S)-t");*/
	SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 5));
	gotoxy(2, 33);
	printf("Уровень: %d", mapnum);
	gotoxy(69, 33);
	if (myinv.consumables[3].mind > 0){
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 8));
		printf("Знание языков");
	}


	SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 5));
	gotoxy(86, 2);
	printf("Рюкзак:");

	for (i = 0; i < myinv.allitem; i++){
		j = 0;

		while (j < 10){
			position.X = 87;
			position.Y = 3 + i;
			SetConsoleCursorPosition(hConsole, position);
			if (myinv.consumables[j].full == 1 && myinv.consumables[j].num == i){
				type = 1;
				break;
			}
			if (myinv.equipments[j].full == 1 && myinv.equipments[j].num == i){
				type = 2;
				break;
			}
			if (myinv.magic[j].full == 1 && myinv.magic[j].num == i){
				type = 3;
				break;
			}
			j++;
		}

		if (type == 1)
			switch (myinv.consumables[j].id){
			case 0: case 1: case 2:case 4:
				printf("%d) %s        ", i + 1, itemnames[0]);
				break;
			case 3:
				printf("%d) %s        ", i + 1, itemnames[7]);
				break;
			case 5:
				printf("%d) %s        ", i + 1, itemnames[10]);
				break;
			case 6:
				printf("%d) %s        ", i + 1, itemnames[11]);
				break;
			case 7:
				printf("%d) %s        ", i + 1, itemnames[12]);
				break;
			case 8:
				printf("%d) %s        ", i + 1, itemnames[13]);
				break;
			case 9:
				printf("%d) %s        ", i + 1, itemnames[14]);
				break;

		}
		else if (type == 2)
			switch (myinv.equipments[j].id){
			case 0:
				printf("%d) %s %c        ", i + 1, itemnames[1], myinv.equipments[j].equip ? 'e' : ' ');
				break;
			case 1:
				printf("%d) %s %c        ", i + 1, itemnames[2], myinv.equipments[j].equip ? 'e' : ' ');
				break;
			case 2:
				printf("%d) %s %c        ", i + 1, itemnames[3], myinv.equipments[j].equip ? 'e' : ' ');
				break;
			case 3:
				printf("%d) %s %c        ", i + 1, itemnames[8], myinv.equipments[j].equip ? 'e' : ' ');
				break;
			case 4:
				printf("%d) %s %c        ", i + 1, itemnames[15], myinv.equipments[j].equip ? 'e' : ' ');
				break;
			case 5:
				printf("%d) %s %c        ", i + 1, itemnames[16], myinv.equipments[j].equip ? 'e' : ' ');
				break;
			case 6:
				printf("%d) %s %c        ", i + 1, itemnames[17], myinv.equipments[j].equip ? 'e' : ' ');
				break;
			case 7:
				printf("%d) %s %c        ", i + 1, itemnames[18], myinv.equipments[j].equip ? 'e' : ' ');
				break;
			case 8:
				printf("%d) %s %c        ", i + 1, itemnames[19], myinv.equipments[j].equip ? 'e' : ' ');
				break;
			case 9:
				printf("%d) %s %c        ", i + 1, itemnames[20], myinv.equipments[j].equip ? 'e' : ' ');
				break;
		}
		else if (type == 3)
			switch (myinv.magic[j].id){
			case 0:
				printf("%d) %s %c        ", i + 1, itemnames[4], myinv.magic[j].equip ? 'e' : ' ');
				break;
			case 1:
				printf("%d) %s %c        ", i + 1, itemnames[5], myinv.magic[j].equip ? 'e' : ' ');
				break;
			case 2:
				printf("%d) %s %c        ", i + 1, itemnames[6], myinv.magic[j].equip ? 'e' : ' ');
				break;
			case 3:
				printf("%d) %s %c        ", i + 1, itemnames[9], myinv.magic[j].equip ? 'e' : ' ');
				break;
			case 4:
				printf("%d) %s           ", i + 1, itemnames[21]);
				break;
			case 5:
				printf("%d) %s           ", i + 1, itemnames[22]);
				break;
			case 6:
				printf("%d) %s           ", i + 1, itemnames[23]);
				break;
			case 7:
				printf("%d) %s           ", i + 1, itemnames[24]);
				break;
			case 8:
				printf("%d) %s           ", i + 1, itemnames[25]);
				break;
			case 9:
				printf("%d) %s           ", i + 1, itemnames[26]);
				break;
		}
	}
	while (i < 10){
		position.X = 87;
		position.Y = 3 + i;
		SetConsoleCursorPosition(hConsole, position);
		printf("                         ");
		i++;
	}


	//H
	gotoxy(0, 35);
	SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 8));
	printf("------------------------------------------------------------------------------------------------------------------------");
	gotoxy(0, 32);
	printf("------------------------------------------------------------------------------------------------------------------------");
	gotoxy(0, 44);
	printf("------------------------------------------------------------------------------------------------------------------------");
	gotoxy(83, 0);
	printf("-------------------------------------");
	for (int i = 33; i < 35; i++){
		gotoxy(0, i);
		printf("|");
		gotoxy(83, i);
		printf("|");
		gotoxy(119, i);
		printf("|");
	}
	for (int i = 36; i < 44; i++){
		gotoxy(0, i);
		printf("|");
		gotoxy(50, i);
		printf("|");
		gotoxy(42, i);
		printf("|");
		gotoxy(119, i);
		printf("|");
	}
	for (int i = 1; i < 32; i++){
		gotoxy(119, i);
		printf("|");
		gotoxy(83, i);
		printf("|");
	}
	gotoxy(65, 37);
	if (mobs1[0].hp == mobs1[0].hpe){
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));
		printf("В отличном состоянии");
	}
	gotoxy(65, 37);
	if (mobs1[0].hp < 100){
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 2));
		printf("Здоров и свеж       ");
	}
	gotoxy(65, 37);
	if (mobs1[0].hp < 76){
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 6));
		printf("Мелкие царапины     ");
	}
	gotoxy(65, 37);
	if (mobs1[0].hp < 51){
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 7));
		printf("Утомлен,подавлен    ");
	}
	gotoxy(65, 37);
	if (mobs1[0].hp < 26){
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 8));
		printf("Еле волочит ноги    ");
	}
	gotoxy(65, 37);
	if (mobs1[0].hp < 6){
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 1));
		printf("Разбит, при смерти  ");
	}
	



	if (eff1[2].efbool == 1 && eff1[2].endc == 1 ){
		log("Отравлен                           ",0,0);
	}
	if (eff1[3].efbool == 1 && eff1[3].endc == 1){
		log("Заразился чумой                    ", 0, 0);
	}
	if (eff1[4].efbool == 1 && eff1[4].endc == 1){
		log("Горит!                             ", 0, 0);
	}
	if (eff1[1].efbool == 1 && eff1[1].endc == 1){
		log("Прирост сил                        ", 0, 0);   
	}
	

	//H
	SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 7));
	for (int w = 1; w < mob1count; w++){
		if ((mobs1[w].x == mobs1[0].x) && (mobs1[w].y == mobs1[0].y))
			switch(mobs1[w].id){
			case 2:
				//gotoxy(1, 38);
				log("Паук забрался под одежду!       ", 0, 0);
				break;
			case 3:
				log("Чумная крыса вцепилась в ногу!  ", 0, 0);
				break;
			case 4:
				log("Змея обвилась вокруг шеи!       ", 0, 0);
				break;
			case 5:
				log("Летучая мышь вцепилась в волосы!", 0, 0);
				break;
		}		
	}
}

void coord(int x, int y, int id, char simv){
	COORD position;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	position.X =x;                                
	position.Y = y;                                 
	
	int  water;
	if (map[y][x] == ':')
		water = 9;
	else
		water = 0;

	switch (id){
	case 0:
		SetConsoleTextAttribute(hConsole, (WORD)((water << 4) | 15));//черный фон и голубой цвет для ГГ
		break;
	case 1:
		SetConsoleTextAttribute(hConsole, (WORD)((water << 4) | 7));//черный фон и серый для rat
		break;
	case 2:
		SetConsoleTextAttribute(hConsole, (WORD)((water << 4) | 2));
		break;
	case 3:
		SetConsoleTextAttribute(hConsole, (WORD)((water << 4) | 8));
		break;
	case 4:
		SetConsoleTextAttribute(hConsole, (WORD)((water << 4) | 5));
		break;
	case 5:
		SetConsoleTextAttribute(hConsole, (WORD)((water << 4) | 8));
		break;
	case 6:
		SetConsoleTextAttribute(hConsole, (WORD)((water << 4) | 3));
		break;
	case 7:
		SetConsoleTextAttribute(hConsole, (WORD)((water << 6) | 4));
		break;
	case 8:
		SetConsoleTextAttribute(hConsole, (WORD)((water << 4) | 15));
		break;
	case 9:
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 3));// черви
		break;
	case 10:
		SetConsoleTextAttribute(hConsole, (WORD)((water << 4) | 10));
		break;
	case 500:
		SetConsoleTextAttribute(hConsole, (WORD)((water << 4) | 15));//черный фон и голубой цвет для ГГ
		break;
	case 99:
		break;
	default:
		printf("Нет чего-то к отрисовке ID!!!\n");
		getch();
		break;
	}
		SetConsoleCursorPosition(hConsole, position);
		if (eye2[y][x]==1)
		printf("%c", simv );
		if (id==99)
			printf("%c", simv);
		
}
//Н внутри
void mainMenu(){
	FILE *save;
	int i;

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	gotoxy(0, 0);
	SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 7));
	printf("------------------------------------------------------------------------------------------------------------------------");
	printf("                    |  |                       |    Homeless     |                            |  |                      ");
	printf("                    |  |                       |-----------------|                            |  |                      ");
	printf("                    |  |                                                                      |  |                      ");
	printf("                    |  |----------------------------------------------------------------------|--|                      ");
	printf("                    | /                                                                       | /|                      ");
	printf("                    |-------------------------------------------------------------------------|| |                      ");
	printf("                    |                          ...//Главное меню                              ||/|                      ");
	printf("                    |-------------------------------------------------------------------------|                         ");
	printf("                                                                                                                        ");
	printf("                                                                                                                        ");
	printf("                                                                                                                        ");
	printf("                                                                                                                        ");
	printf("                                                                                                                        ");
	printf("                                                                                                                        ");
	printf("------------------------------------------------------------------------------------------------------------------------");
	printf(" 2015        --           -                                  --                                     -                 - ");
	printf("------------------------------------------------------------------------------------------------------------------------");
	printf("                    |  |                                                                      |  |                      ");
	printf("                    |  |----------------------------------------------------------------------|--|                      ");
	printf("                    | /                                                                       | /|                      ");
	printf("                    |-------------------------------------------------------------------------|| |                      ");
	printf("                    |                          1...//Новая игра                               ||/|                      ");
	printf("                    |-------------------------------------------------------------------------|  |                      ");
	printf("                    |  |                                                                      |  |                      ");
	printf("                    |  |----------------------------------------------------------------------|--|                      ");
	printf("                    | /                                                                       | /|                      ");
	printf("                    |-------------------------------------------------------------------------|| |                      ");
	printf("                    |                          2...//Продолжить                               ||/|                      ");
	printf("                    |-------------------------------------------------------------------------|  |                      ");
	printf("                    |  |                                                                      |  |                      ");
	printf("                    |  |----------------------------------------------------------------------|--|                      ");
	printf("                    | /                                                                       | /|                      ");
	printf("                    |-------------------------------------------------------------------------|| |                      ");
	printf("                    |                          3...//Авторы                                   ||/|                      ");
	printf("                    |-------------------------------------------------------------------------|  |                      ");
	printf("                    |  |                                                                      |  |                      ");
	printf("                    |  |----------------------------------------------------------------------|--|                      ");
	printf("                    | /                                                                       | /|                      ");
	printf("                    |-------------------------------------------------------------------------|| |                      ");
	printf("                    |                          0...//Выход                                    ||/                       ");
	printf("                    |-------------------------------------------------------------------------|                         ");
	printf("                                                                                                                        ");
	printf("                                                                                                                        ");
	printf("b1.1                                                                                                                    ");

	int c;
	c = getch();
	switch (c){
	case '0':
		system("cls");
		exit(1); 
		break;
	case '1':
		system("cls");
		gg();
		inwtgen();
		break;
	case '2':
		fopen_s(&save, "data\\save", "rb");
		fread(&pname, sizeof(pname), 1, save);
		fread(&form, sizeof(form), 1, save);
		fread(&age, sizeof(int), 1, save);
		fread(&wm, sizeof(int), 1, save);
		fread(&mobs1[0].hp, sizeof(int), 1, save);
		fread(&mobs1[0].dmg, sizeof(int), 1, save);
		fread(&mobs1[0].idEff, sizeof(int), 1, save);
		fread(&mobs1[0].look, sizeof(int), 1, save);
		fread(&mobs1[0].hpe, sizeof(int), 1, save);
		fread(&score, sizeof(int), 1, save);
		fread(&olvlup, sizeof(int), 1, save);
		fread(&lvl, sizeof(int), 1, save);
		fread(&mobs1[0].mana, sizeof(int), 1, save);
		fread(&mobs1[0].manae, sizeof(int), 1, save);
		fread(&mobs1[0].cri, sizeof(int), 1, save);
		fread(&mobs1[0].cri2, sizeof(int), 1, save);
		fread(&mobs1[0].defense, sizeof(int), 1, save);
		fread(&money, sizeof(int), 1, save);

		fread(&myinv.allitem, sizeof(int), 1, save);
		for (i = 0; i < 10; i++){
			fread(&myinv.consumables[i].id, sizeof(int), 1, save);
			fread(&myinv.consumables[i].num, sizeof(int), 1, save);
			fread(&myinv.consumables[i].full, sizeof(bool), 1, save);
			fread(&myinv.consumables[i].mind, sizeof(int), 1, save);
			fread(&myinv.consumables[i].onhp, sizeof(int), 1, save);
			fread(&myinv.consumables[i].arrow, sizeof(int), 1, save);
			fread(&myinv.consumables[i].onMana, sizeof(int), 1, save);

			fread(&myinv.equipments[i].id, sizeof(int), 1, save);
			fread(&myinv.equipments[i].num, sizeof(int), 1, save);
			fread(&myinv.equipments[i].full, sizeof(bool), 1, save);
			fread(&myinv.equipments[i].dmg, sizeof(int), 1, save);
			fread(&myinv.equipments[i].def, sizeof(int), 1, save);
			fread(&myinv.equipments[i].equip, sizeof(bool), 1, save);

			fread(&myinv.magic[i].id, sizeof(int), 1, save);
			fread(&myinv.magic[i].num, sizeof(int), 1, save);
			fread(&myinv.magic[i].full, sizeof(bool), 1, save);
			fread(&myinv.magic[i].equip, sizeof(bool), 1, save);
		}

		fread(&heroeq.bowl, sizeof(bool), 1, save);
		fread(&heroeq.sword, sizeof(bool), 1, save);
		fread(&heroeq.helmet, sizeof(bool), 1, save);
		fread(&heroeq.armor, sizeof(bool), 1, save);
		fread(&heroeq.sv_fire, sizeof(bool), 1, save);
		fread(&heroeq.sv_rock, sizeof(bool), 1, save);
		fread(&heroeq.sv_blind, sizeof(bool), 1, save);
		fread(&heroeq.sv_inf, sizeof(bool), 1, save);

		fread(&mapnum, sizeof(int), 1, save);

		fread(&acr, sizeof(int), 1, save);
		fread(&stren, sizeof(int), 1, save);
		fread(&mental, sizeof(int), 1, save);
		fread(&vig, sizeof(int), 1, save);
		fread(&score, sizeof(int), 1, save);
		fread(&lvl, sizeof(int), 1, save);
		fread(&olvlup, sizeof(int), 1, save);
		fread(&hunger, sizeof(int), 1, save);
		fread(&golds, sizeof(int), 1, save);
		fread(&kills, sizeof(int), 1, save);
		fread(&lows, sizeof(int), 1, save);
		fread(&potrs, sizeof(int), 1, save);

		fclose(save);
		system("cls");
		break;
	case '3':
		system("cls");
		printf("                                                                                                                        ");
		printf("                                                                                                                        ");
		printf("                                                                                                                        ");
		printf("                                                                                                                        ");
		printf("                                                                                                                        ");
		printf("                                    какая вам разница? а вам какое дело до этого?                                       ");
		printf("                                                                                                                        ");
		printf("                                                                                                                        ");
		printf("                  1...//Назад                     2...//Уйти                      0...//Настоять на своем               ");
		printf("                                                                                                                        ");
		printf("                                                                                                                        ");
		printf("                                                                                                                        ");
		printf("                                                                                                                        ");
		printf("                                                                                                                        ");
		printf("                                                                                                                        ");
		printf("                                                                                                                        ");
		printf("                                                                                                                        ");
		printf("                                                                                                                        ");
		printf("                                                                                                                        ");
		printf("                                                                                                                        ");
		printf("                                                                                                                        ");
		printf("                                                                                                                        ");
		printf("                                                                                                                        ");
		printf("                                                                                                                        ");
		
		c = getch();
		switch (c){
		case '0':
			system("cls");
			printf("Капустин и Головин и Подоплелов, Дмитрий и Никита и Леха\n2014\nмолви букву, друг, и вернешься");
			getch();
			mainMenu();
			break;
		case '1':case '2':
			mainMenu();
			break;
		}
		break;
	default:
		mainMenu();
		break;
	}
}
//Н
char** mapnew(int num){
	

	system("cls");

	
	struct Mob1 resmob1;
	FILE *mapfile;
	int i, j, x;
	
	
	if (mapx > 0){
		for (i = 0; i < mapy; i++)
			free(map[i]);
		free(map);
	}
	
	if (mob1count > 0){
		resmob1 = mobs1[0];
		free(mobs1);
	mob1count = 0;
	}
	
	if (num == 0)
		exit(1);
	
	

	mapx = 0;
	mapy = 0;

	gen();
	char mapname[20] = "data\\mapgen";

	
	/*	i = 2;
		cnum[2] = '\0';
		while (num > 0){
			i--;
			x = num % 10;
			num = num / 10;
			cnum[i] = x + '0';
		}

		while (i > 0){
			i--;
			cnum[i] = '0';
		}
		strcat_s(mapname, 20, cnum);*/

	/*if (mapnum == 1)
		fopen_s(&mapfile, "map01", "r");
	else*/

	fopen_s(&mapfile, mapname, "r");
	while (!feof(mapfile)) {
		x = 0;
		mapy++;
		while ((i = fgetc(mapfile)) != '\n'  && !feof(mapfile))
			x++;
		if (x > mapx)
			mapx = x;
	}
	fclose(mapfile);
	
	char **map = (char**)malloc(mapy*sizeof(char*));
	for (i = 0; i < mapy; i++)
		map[i] = (char*)malloc(mapx*sizeof(char));
	for (i = 0; i < mapy; i++)
		for (j = 0; j < mapx; j++)
			map[i][j] = ' ';
	
	fopen_s(&mapfile, mapname, "r");
	i = j = 0;
	while (!feof(mapfile)){
		x = fgetc(mapfile);
		if (x != '\n'){
			if (!feof(mapfile))
				map[i][j] = x;
			j++;
			if (j == mapx)
				j = 0;
		}
		else{
			i++;
			j = 0;
		}
	}
	fclose(mapfile);
	
	mob1count = 0;
	for (i = 0; i < mapy; i++)
		for (j = 0; j < mapx; j++)
			if (map[i][j] == 'r' || map[i][j] == '1' || map[i][j] == 'p' ||
				map[i][j] == 'h' || map[i][j] == 's' || map[i][j] == 'b' ||
				map[i][j] == 'e' || map[i][j] == 'w' || map[i][j] == '2' ||
				map[i][j] == 'k' || map[i][j] == 'z')//h - наши крысы чумные
				mob1count++;
	if (mob1count > 0)
		mobs1 = (struct Mob1*)malloc(mob1count*sizeof(struct Mob1));

	x = 0;
	for (i = 0; i < mapy; i++)
		for (j = 0; j < mapx; j++)
			if (map[i][j] == '1'){
					if (/*mob1count<0 &&*/ resmob1.hp > 0){
					mobs1[0] = resmob1;
					mobs1[0].x = j;
					mobs1[0].y = i;
				}
				else
					newmob1(x, 0, j, i);
				map[i][j] = '.';
				x++;
			}

	for (i = 0; i < mapy; i++)
		for (j = 0; j < mapx; j++)
			switch (map[i][j])
		{
			case 'r':
				newmob1(x, 1, j, i);
				map[i][j] = '.';
				x++;
				break;
			case 'p':
				newmob1(x, 2, j, i);
				map[i][j] = '.';
				x++;
				break;
			case 'h':
				newmob1(x, 3, j, i);
				map[i][j] = '.';
				x++;
				break;
			case 's':
				newmob1(x, 4, j, i);
				map[i][j] = '.';
				x++;
				break;
			case 'b':
				newmob1(x, 5, j, i);
				map[i][j] = '.';
				x++;
				break;
			case 'e':
				newmob1(x, 6, j, i);
				map[i][j] = '.';
				x++;
				break;
			case 'w':
				newmob1(x, 7, j, i);
				map[i][j] = '.';
				x++;
				break;
			case '2':
				newmob1(x, 8, j, i);
				map[i][j] = '.';
				x++;
				break;
			case 'k':
				newmob1(x, 9, j, i);
				map[i][j] = '.';
				x++;
				break;
			case 'z':
				newmob1(x, 10, j, i);
				map[i][j] = '.';
				x++;
				break;
		}
 
	//if (/*mapnum*/num > 1){
		
//		mobs1[0].hp = resmob1.hp;
//		mobs1[0].dmg = resmob1.dmg;
		
//	}
	
	// WORM
	if (num == 17)
		newworm(10, true); //H
	
	if (wormscount > 0)
		if (num == 20){
			(*worms).maxcdsniz = 5;
			(*worms).cdsbok = (*worms).maxcdsbok;
			(*worms).cdnew = (*worms).maxcdnew;
		}
		else{
			while ((*worms).nextworm != NULL)
				worms = (*worms).nextworm;
			while ((*worms).prewworm != NULL){
				worms = (*worms).prewworm;
				free((*worms).nextworm);
			}
			wormscount = 1;

			if ((*worms).boss == 0){
				free(worms);
				wormscount = 0;
			}
			else {
				(*worms).nextworm = NULL;
				(*worms).status = 0;
				(*worms).cdsniz = (*worms).maxcdsniz;
				(*worms).maxcdsniz = 20;
				(*worms).cdsbok = -10;
				(*worms).cdnew = -10;
				for (i = 0; i < (*worms).dlin; i++){
					(*worms).part[i].x = (*worms).part[i].y = -1;
					(*worms).part[i].invis = 1;
				}
			}
		}

	return map;
}
/*КАКАЯ ТО СТРАННОСТЬ ПРИ ЗАГРУЗКЕ ИСТОРИИ ПЕРЕД КАРТОЙ, КОРОЧЕ ЕСЛИ ДОБАВИТЬ 4 КАРТЫ ТО ВЫЛЕТАЕТ*/
/*void story(){
	COORD position;                                     // Объявление необходимой структуры
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);  // Получение дескриптора устройства стандартного вывода

	FILE *storytxt;	//указатель на файл
	char storyname[25] = "data\\story\\story";
	strcat_s(storyname, 21, cnum);
	fopen_s(&storytxt, storyname, "r"); //читаем файл в режиме чтения
	
/*	for (int b = 0; b < 1; b++){
		gotoxy(20, 20);
		for (int i = 0; i < 3; i++){
			Sleep(300);
			printf(" - ");
		}
		system("cls");
	}*/

	/*char g;
	gotoxy(0, 0);
	do{
		int k;
		g = getc(storytxt);
		if (g != '^'){
			printf("%c", g);
			//getch();
			//k = rand() % 100 + 0;
			//switch (g){
			//case '.':Sleep(700); break;
			//case ',':Sleep(300); break;

			//default: Sleep(20 + k); break;

			//}

		}
	} while (g != '^');
	getch();
	system("cls");
}*/

void IImap(int y, int x,int id){
	bool h;
	h = 0;
	for (int i = 0; i < mapy; i++){
		for (int b = 0; b < mapx; b++){

			if (id == 8 || id == 9){/*суть в том , что если поставить этот блок до определения пустот и стен , то моб никогда не сядет нам на шею*/
				if (mobs1[0].y == i && mobs1[0].x == b)
					R[i][b] = 0;

				if (i == y && b == x)
					R[i][b] = 49;
				h = 1;
			}

			if (map[i][b] == ' ' || map[i][b] == ',' || map[i][b] == ';' || map[i][b] == '.'
				|| map[i][b] == '%' || map[i][b] == '/' || map[i][b] == '=' || map[i][b] == '_' || map[i][b] == ':')
				R[i][b] = 50;

			if (map[i][b] == '#' || map[i][b] == '0' || map[i][b] == '|' || map[i][b] == '-' || map[i][b] == '+' || map[i][b] == 'T'
				|| map[i][b] == 'F' || map[i][b] == 'R' || map[i][b] == 'S' || map[i][b] == '\'')// - '
				R[i][b] = 51;

			if (h != 1){/*а если после, то сядет*/
				if (mobs1[0].y == i && mobs1[0].x == b)
					R[i][b] = 0;

				if (i == y && b == x)
					R[i][b] = 49;
			}

			for (int w = 1; w < mob1count; w++){
				if ((mobs1[w].x != x) && (mobs1[w].y != y))
					R[mobs1[w].y][mobs1[w].x] = 51;
			}

		}
	}

	if (id == 5){
		for (int i = 0; i < mapy; i++)
			for (int b = 0; b < mapx; b++)
				if (map[i][b] == '0')
					R[i][b] = 50;
	}
}

void logdraw(){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	
	system("cls");

	gotoxy(0, 13);
	SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 6));
	printf("                                                             День 38 от начала пути, седьмая луна                       ");
	SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 7));
	printf("                                                           ...Теперь мне приходится избегать дневного света, ОНИ искали ");
	printf("                                                           меня. Я мало слышал об этих краях,но опастности тут точно    ");
	printf("                                                           нет. После большой войны тут только пожухлая трава да овраги,");
	printf("                                                           куда стекает дождевая вода. Луна отлично освещает мой путь,  ");
	printf("                                                           кажется, я достигну цели уже через несколько дней.           ");
	printf("                                                                                                                        ");
	SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 6));
	printf("                                                             День 40 от начала пути                                     ");
	SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 7));
	printf("                                                           ...Как я ошибался! Гром и молния раскололи небеса, приходится");
	printf("                                                           идти под дождем в полной темноте. Кажется я сбился с пути,   ");
	printf("                                                           пальцы на руках деревенеют, я ошибся, ошибся.                ");
	printf("                                                                                                                        ");
	SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 6));
	printf("                                                             День 41 от начала пути                                     ");
	SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 7));
	printf("                                                           ...Я укрылся в какой то пещере, тут довольно сухо, мне       ");
	printf("                                                           даже удалось даже развести костер из веток, ?заболтиво?      ");
	printf("                                                           оставленных здесь. Пещера. Она кажется рукотворной, или тени ");
	printf("                                                           причудливо танцуют на стенах.                                ");
	printf("                                                                                                                        ");
	SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 6));
	printf("                                                             День 44 от начала пути                                     ");
	SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 7));
	printf("                                                           ...Отошел осмотреть пещеру и не заметил как потерялся.       ");
	printf("                                                           Я долго блуждал во тьМе, но в какой то момент скатился кубрем");
	printf("                                                           куда то ВНИЗ./когда я пронулся  Я 0бнарил с3бя в н6стох      ");
	printf("                                                           ката6ах. Больштво вещ45й мо... растерялось( были             ");
	printf("                                                           свор0в");
	SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 4));
	printf("анькк7). Гн              хое    //          Ъ          ");
	printf("                                                             ..       ^^^     .    /                     чанк           ");
	printf("                                                           катак0мц352        ды+!ние,1номы я ви7?^ ...       {./   уыа ");
	printf("                                                           кхазад ай мену!/   ца3к        сль111у шагицу2**  3      3е  ");
	printf("                                                           Я 12нете      //   Б0ЖЕГ   ..   вьх0д, я до(3ен2    23     ыв");
	printf("                                                               .темнота      @$5      ///.                          .   ");

	SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 7));
	for (int i = 0; i < 44; i++){
		gotoxy(0, i);
		printf("|");
		gotoxy(119, i);
		printf("|");
		if (i > 2){
			gotoxy(40, i);
			printf("|");
		}
	}
	gotoxy(0, 0);
	printf("+----------------------------------------------------------------------------------------------------------------------+");
	gotoxy(50, 1);
	printf("   Дневник");
	gotoxy(18, 4);
	printf("Журнал событий");
	gotoxy(78, 4);
	printf("        История");
	gotoxy(0, 2);
	printf("+----------------------------------------------------------------------------------------------------------------------+");
	gotoxy(60, 6);
	printf("Имя: %s", pname);
	gotoxy(60, 7);
	if (wm == 1)
		printf("Пол: мужской");
	else
		printf("Пол: женский");
	gotoxy(60, 8);
	printf("Возраст: %d", age);
	/*gotoxy(60, 9);
	printf("Внешность: %s", form);*/
	{
		int crdf, drdf, srdf;
		crdf = 60;
		drdf = 60;
		srdf = 60;
		gotoxy(crdf, 9);
		printf("Внешность: ");
		for (int i = 0; i < 200; i++){
			if (form[i] == '$')
				break;
			if (i >= 45){
				gotoxy(crdf++, 10);
				printf("%c", form[i]);
			}
			else if (i >= 90){
				gotoxy(drdf++, 11);
				printf("%c", form[i]);
			}
			else if (i >= 135){
				gotoxy(srdf++, 12);
				printf("%c", form[i]);
			}else 
				if(i<45)
					printf("%c", form[i]);


		}
	}

	for (int i = 2; i < 44; i += 2){
		gotoxy(55, i);
		printf("/");
		gotoxy(56, i);
		printf("-");
		gotoxy(57, i);
		printf("\\");
		gotoxy(55, i + 1);
		printf("|");
		gotoxy(57, i + 1);
		printf("|");
	}
	gotoxy(56, 43);
	printf("_");
	
	for (int i = 0; i < 40; i++){
		gotoxy(4, 5 + i);//37,38,39,40,41,42,43
		if (i>-1 && i <= 10)
				SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 14));
		if (i>10 && i <= 20)
				SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));
		if (i>20 && i <= 30)
				SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 7));
		if (i>30 && i<=43)
				SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 8));
		printf("%s", _infl[i]);
	}
	for (int i = 0; i < 40; i++){
		gotoxy(50, 4 + i);//37,38,39,40,41,42,43
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | colo[i]));
			if (colo[i] == 4 || colo[i] == 1)
				printf("-");
			if (colo[i] == 2 || colo[i] == 9 || colo[i] == 14)
				printf("+");
		printf("%d  ", dmg[i]);
	}
	SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 7));
	gotoxy(0, 44);
	printf("+----------------------------------------------------------------------------------------------------------------------+");
	gotoxy(118, 43);
	printf("/");
	gotoxy(1, 43);
	printf("\\");
	gotoxy(1, 3);
	printf("/");
	gotoxy(118, 3);
	printf("\\");
	gotoxy(0, 44);
	getch();
	system("cls");
}

void lvlup(){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 7));
	gotoxy(30, 10);
	printf("+---------------------------+");
	gotoxy(30, 11);
	printf("|/     Повышение уровня!   \\|");
	gotoxy(30, 12);
	printf("|    1)Мана(+10)            |");
	gotoxy(30, 13);
	printf("|    2)Живучесть(+10)       |");
	gotoxy(30, 14);
	printf("|    3)Меткость(+1)         |");
	gotoxy(30, 15);
	printf("|    4)Сила(+1)             |");
	gotoxy(30, 16);
	printf("|\\   5)Интеллект(+1)       /|");
	gotoxy(30, 17);
	printf("+---------------------------+");
	gotoxy(0, 44);
	switch (getch()){
	case '1':
		mobs1[0].mana += 10;
		mobs1[0].manae += 10;
		break;
	case '2':
		mobs1[0].hp += 10;
		mobs1[0].hpe += 10;
		break;
	case '3':
		if (acr<5)
			acr += 1;
		break;
	case '4':
		if (stren<5)
			stren += 1;
		break;
	case '5':
		if (mental<5)
			mental += 1;
		break;
	default:
		lvlup();
		break;
	}

}

void gg(){
	//Имя
		{
			char n1[20][10] = { "Диб", "Вор", "Ро", "Гал", "Фла", "Ба", "Ваз", "Дор", "Ид", "Кри", "Кеф", "Оки", "Ол", "Орф", "Фур", "Мар", "Сат", "Три", "Ре", "Ино" };//15
			char n2[11][10] = { "ел", "ти", "ла", "ери", "ви", "йо", "или", "иу", "ум", "зе", "ало", };
			char n3[10][10] = { " ", "гонт", "нд", "ий", "н", "с", "н", "г", "б", "р" };

			char nn1[15][10] = { "Ара", "Атэ", "Гли", "Дай", "Кас", "Ки", "Мар", "Мел", "Нэй", "Офе", "Соф", "Эле", "Але", "Эми", "Эй", };//женщины
			char nn2[9][10] = { "х", "н", "кер", "о", "ан", "гари", "ис", "та", "фтэ", };//женщины
			char nn3[9][10] = { "на", "ия", "дра", "ис", "ния", "тес", "а", "са", "рия" };//женщины

			int r, b;
				b = rand() % 2 + 1;
				if (b == 1){
					wm = 1;
					r = rand() % 20;
					strcpy_s(pname, 50, n1[r]);
					r = rand() % 11;
					strcat_s(pname, 50, n2[r]);
					r = rand() % 10;
					strcat_s(pname, 50, n3[r]);
				}
				else{
					wm = 0;
					r = rand() % 15;
					strcpy_s(pname, 50, nn1[r]);
					r = rand() % 9;
					strcat_s(pname, 50, nn2[r]);
					r = rand() % 9;
					strcat_s(pname, 50, nn3[r]);
				}

		}
	//Возраст и зоркость
	{
		age = rand() % (80 - 20 + 1) + 20;
		if (age >= 20 && age <= 30)
			vig = 5;
		else if (age >= 31 && age <= 50)
			vig = 4;
		else if (age >= 51 && age <= 65)
			vig = 3;
		else if (age >= 66 && age <= 80)
			vig = 2;
	}
	//меткость
	{
		acr = rand()%5 + 1;
	}
	//Внешность
	{
		switch (rand() % 7 + 1){
		case 1: strcpy_s(form, 100, "Глаза карие,"); break;
		case 2: strcpy_s(form, 100, "Глаза зеленые,"); break;
		case 3: strcpy_s(form, 100, "Глаза голубые,"); break;
		case 4: strcpy_s(form, 100, "Глаза серые,"); break;
		case 5: strcpy_s(form, 100, "Глаза болотные,"); break;
		case 6: strcpy_s(form, 100, "Глаза янтарные,"); break;
		case 7: strcpy_s(form, 100, "Глаза желтые,"); break;
		}
		if (age <= 50){
			switch (rand() % 4 + 1){
			case 1: strcat_s(form, 100, "волосы черные "); break;
			case 2: strcat_s(form, 100, "волосы рыжие "); break;
			case 3: strcat_s(form, 100, "волосы русые "); break;
			case 4: strcat_s(form, 100, "волосы светлые "); break;
			}
			if (age >= 40 && age <= 50){
				strcat_s(form, 100, "с легкой сединой, ");
			}else
				switch (rand() % (4-1+1) + 1){
				case 1: strcat_s(form, 100, "с белым оттенком, "); break;
				case 2: strcat_s(form, 100, "с рыжим оттенком, "); break;
				case 3: strcat_s(form, 100, "с темным оттенком, "); break;
				case 4: strcat_s(form, 100, "с болотистым оттенком, "); break;
			}
		}
		else
			strcat_s(form, 100, "волосы седые, ");

		switch (rand() % 3 + 1){
		case 1:stren = 5; strcat_s(form, 150, "телосложение крепкое, "); break;
		case 2: stren = 1; strcat_s(form, 150, "телосложение хилое, "); break;
		case 3: stren = 3;  strcat_s(form, 150, "телосложение среднее, "); break;
		}
		switch (rand() % 3 + 1){
		case 1:mental = 5; strcat_s(form, 200, "интеллект высокий. "); break;
		case 2:mental = 1; strcat_s(form, 200, "интеллект слабый. "); break;
		case 3: mental = 3; strcat_s(form, 200, "интеллект средний. "); break;
		}

	}
	strcat_s(form, 200, "$");
}

void traps(){
	if (oops[mobs1[0].y][mobs1[0].x] == 1 || oops[mobs1[0].y][mobs1[0].x] == 2){
		if ((rand() % 3) == 2){
			if (oops[mobs1[0].y][mobs1[0].x] == 1){
				mobs1[0].hp -= 5;
				log("Шипы!                           ", 0, 0);
				map[mobs1[0].y][mobs1[0].x] = '^';
				lows += 1;
			}
			if (oops[mobs1[0].y][mobs1[0].x] == 2){
				eff1[4].efbool = 1;
				log("Огонь!                          ", 0, 0);
				map[mobs1[0].y][mobs1[0].x] = '^';
				lows += 1;
			}
		}
		else{
			log("!Щелк!                              ", 0, 0);
			map[mobs1[0].y][mobs1[0].x] = '^';
			lows += 1;
		}
		if (hunger < 50)
			hunger++;
	}
	if (oops[mobs1[0].y][mobs1[0].x] == 3){
		bool telep = 0;;
		for (int i = 1; i < 30; i++){
			for (int j = 1; j < 80; j++)
				if (oops[i][j] == 3 && i != mobs1[0].y && j != mobs1[0].x){
				map[mobs1[0].y][mobs1[0].x] = '*';
				mobs1[0].y = i;
				mobs1[0].x = j;
				map[mobs1[0].y][mobs1[0].x] = '*';
				telep = 1;
				break;
				}
			if (telep == 1)
				break;
		}
		log("!Паф!                           ", 0, 0);
		lows += 1;
		if (hunger < 50)
			hunger++;
	}
}

void inwtgen(){
	int r,r2,c;

	c = rand() % 3 + 1;
	for (int i = 0; i < c; i++){
		r = rand() % 3 + 1;
		if (r == 1){
			r2 = rand() % 9;
			if (r2 == 3 || r2 == 6)
				;
			else itemnew(r, r2);
		}
		if (r == 2){
			r2 = rand() % (5 - 3 + 1) + 3;
			if (r2 == 5)
				itemnew(r, 9);
			else if (r2 == 3){
				itemnew(r, r2);
				myinv.consumables[4].arrow = rand() % 5 + 1;
			}
			else itemnew(r, r2);
		}
		if (r == 3){
			r2 = rand() % (4 - 3 + 1) + 3;
			if (r2==4)
				itemnew(r, r2);
			else;
		}	

	}
	money = rand() % 20;
}
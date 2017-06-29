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


char** mapnew(int num); //�

int mapx, mapy;


char cnum[3];
void mapgenerate(FILE *mapfile);

struct room{
	int x, y;
	int x2, y2;
	int gor, ver;
	int num;
	int roomx, roomy;//��������������
	int roomx2, roomy2;//������������
	int doornum;
};


main(){
	int i, j;
	int cycl=0;//���� ��������������
	int hplog, hplog2;
	int mana, mana2;

	for (int i = 0; i < 43; i++){//�������� ���
		_infl[i] = "  ";
		colo[i] = 0;
		dmg[i] = 0;
	}

//
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);  //H
	system("mode con cols=120 lines=46");
	system("color 06");//���� ���� � ���� ������ �������(F-��� 0-�����), 150 - �������
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
	//story();/*����� �� ���������� ��� �������� ������� ����� ������, ������ ���� �������� 4 ����� �� ��������*/
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
		
		//�������� ����� 
		for (i = 0; i < mob1count; i++)
			if (mobs1[i].hp > 0)
				move(&mobs1[i]);
		if (wormscount > 0)
			wormsmove();
		
		//�������� ���� �������� �� ����������� ����������
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
		
		//������� ��������
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
			log("�������                             ", 0, 0);
		}

		hplog2 = mobs1[0].hp;
		mana2 = mobs1[0].mana;
		if (hplog - hplog2 > 0){
			log("�����", 4, hplog - hplog2);
		}
		if (hplog - hplog2 < 0){
			log("�����", 2, hplog2  - hplog);
		}
		if (mana - mana2 > 0){
			log("�����", 1, mana - mana2);
		}
		if (mana - mana2 < 0){
			log("�����", 9, mana2 - mana);
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
			else mobs1[i].x = mobs1[i].y = 0;//������� ����� � ����� ���� ��� �� ���������� ��������� �� ����� �� ������ � ��� ��� ��� ������ �� ���
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
			log("\"���-���-���...\"                  ",0,0);
		log("������", 20, 1000);
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
		printf("������ �������: %d", golds);
		gotoxy(50, 8);
		printf("������ �����: %d", kills);
		gotoxy(49, 9);
		printf("������� �������: %d", lows);
		gotoxy(48, 10);
		printf("���/����� ����������: %d", potrs);
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
//H ������
void infdraw(){
	COORD position;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int a, i, j, type;
	char *undr[] = {
			{ "�� ���������  " }, 
			{ "�������� ���  " }, 
			{ "�����         " }, 
			{ "����          " }, 
			{ "�����         " }, 
			{ "������� ����� " }, 
			{ "��������      " },  
			{ "������� ����� " }, 
			{ "���������� ���" }, 
			{ "�����         " }, 
			{ "������� ����� " },
			{ "�����         " },
			{ "�������� ���  " },
			{ "����          " },
			{ "�������       " },
			{ "��������      " },
			{ "�������       " }
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
	case '^':{a = 16; break; }// �
	default: { a = 0; }
	}


	SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 6));
	gotoxy(2, 34);
	printf("��� ������: %s", undr[a]);//underfoot
	gotoxy(52, 36);
	SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 1));
	printf("����:%d/%d  ", mobs1[0].mana, mobs1[0].manae);


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
	printf("�����:%d", mobs1[0].hp);

	SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 4));
	printf("/%d  ", mobs1[0].hpe);
	SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 7));
	gotoxy(52, 38);
	printf("��������: %d/5", acr);
	gotoxy(52, 39);
	printf("����: %d/5", stren);
	gotoxy(52, 40);
	printf("���������: %d/5", mental);
	

	gotoxy(52, 42);
	SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 8));
	printf("������: %d", money);
	gotoxy(52, 43);
	if (myinv.consumables[4].arrow > -1){
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 7));
		printf("�����: %d", myinv.consumables[4].arrow);
	}	
	SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 8));
	gotoxy(15, 33);
	printf("����: %d/%d (lvl.%d)", score, olvlup, lvl);
	gotoxy(69, 34);
	if (hunger >= 0 && hunger < 25){
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 2));
		printf("�� �������    ");
	}
	if (hunger >= 25 && hunger <= 40){
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 6));
		printf("����� � ������");
	}
	if (hunger > 40 && hunger < 50){
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 4));
		printf("�������       ");
	}
	SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 6));
	gotoxy(87, 43);
	printf("������� \'l\' ��� ������ �������");
	gotoxy(87, 34);
	printf("������� \'?\' ��� ������ �������");
	gotoxy(87, 33);
	printf("������� \'\\\' ��� ����������");
	/*gotoxy(2, 33);
	printf("�����������(�����)-wasd, ������������ - 0..9,��������� shift+(0..9),�������-�,");
	gotoxy(2, 34);
	printf("����������-(����� � ����)+z+(������� ����)+x,������-c,��������(����� � S)-t");*/
	SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 5));
	gotoxy(2, 33);
	printf("�������: %d", mapnum);
	gotoxy(69, 33);
	if (myinv.consumables[3].mind > 0){
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 8));
		printf("������ ������");
	}


	SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 5));
	gotoxy(86, 2);
	printf("������:");

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
		printf("� �������� ���������");
	}
	gotoxy(65, 37);
	if (mobs1[0].hp < 100){
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 2));
		printf("������ � ����       ");
	}
	gotoxy(65, 37);
	if (mobs1[0].hp < 76){
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 6));
		printf("������ ��������     ");
	}
	gotoxy(65, 37);
	if (mobs1[0].hp < 51){
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 7));
		printf("�������,��������    ");
	}
	gotoxy(65, 37);
	if (mobs1[0].hp < 26){
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 8));
		printf("��� ������� ����    ");
	}
	gotoxy(65, 37);
	if (mobs1[0].hp < 6){
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 1));
		printf("������, ��� ������  ");
	}
	



	if (eff1[2].efbool == 1 && eff1[2].endc == 1 ){
		log("��������                           ",0,0);
	}
	if (eff1[3].efbool == 1 && eff1[3].endc == 1){
		log("��������� �����                    ", 0, 0);
	}
	if (eff1[4].efbool == 1 && eff1[4].endc == 1){
		log("�����!                             ", 0, 0);
	}
	if (eff1[1].efbool == 1 && eff1[1].endc == 1){
		log("������� ���                        ", 0, 0);   
	}
	

	//H
	SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 7));
	for (int w = 1; w < mob1count; w++){
		if ((mobs1[w].x == mobs1[0].x) && (mobs1[w].y == mobs1[0].y))
			switch(mobs1[w].id){
			case 2:
				//gotoxy(1, 38);
				log("���� �������� ��� ������!       ", 0, 0);
				break;
			case 3:
				log("������ ����� ��������� � ����!  ", 0, 0);
				break;
			case 4:
				log("���� �������� ������ ���!       ", 0, 0);
				break;
			case 5:
				log("������� ���� ��������� � ������!", 0, 0);
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
		SetConsoleTextAttribute(hConsole, (WORD)((water << 4) | 15));//������ ��� � ������� ���� ��� ��
		break;
	case 1:
		SetConsoleTextAttribute(hConsole, (WORD)((water << 4) | 7));//������ ��� � ����� ��� rat
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
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 3));// �����
		break;
	case 10:
		SetConsoleTextAttribute(hConsole, (WORD)((water << 4) | 10));
		break;
	case 500:
		SetConsoleTextAttribute(hConsole, (WORD)((water << 4) | 15));//������ ��� � ������� ���� ��� ��
		break;
	case 99:
		break;
	default:
		printf("��� ����-�� � ��������� ID!!!\n");
		getch();
		break;
	}
		SetConsoleCursorPosition(hConsole, position);
		if (eye2[y][x]==1)
		printf("%c", simv );
		if (id==99)
			printf("%c", simv);
		
}
//� ������
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
	printf("                    |                          ...//������� ����                              ||/|                      ");
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
	printf("                    |                          1...//����� ����                               ||/|                      ");
	printf("                    |-------------------------------------------------------------------------|  |                      ");
	printf("                    |  |                                                                      |  |                      ");
	printf("                    |  |----------------------------------------------------------------------|--|                      ");
	printf("                    | /                                                                       | /|                      ");
	printf("                    |-------------------------------------------------------------------------|| |                      ");
	printf("                    |                          2...//����������                               ||/|                      ");
	printf("                    |-------------------------------------------------------------------------|  |                      ");
	printf("                    |  |                                                                      |  |                      ");
	printf("                    |  |----------------------------------------------------------------------|--|                      ");
	printf("                    | /                                                                       | /|                      ");
	printf("                    |-------------------------------------------------------------------------|| |                      ");
	printf("                    |                          3...//������                                   ||/|                      ");
	printf("                    |-------------------------------------------------------------------------|  |                      ");
	printf("                    |  |                                                                      |  |                      ");
	printf("                    |  |----------------------------------------------------------------------|--|                      ");
	printf("                    | /                                                                       | /|                      ");
	printf("                    |-------------------------------------------------------------------------|| |                      ");
	printf("                    |                          0...//�����                                    ||/                       ");
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
		printf("                                    ����� ��� �������? � ��� ����� ���� �� �����?                                       ");
		printf("                                                                                                                        ");
		printf("                                                                                                                        ");
		printf("                  1...//�����                     2...//����                      0...//�������� �� �����               ");
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
			printf("�������� � ������� � ����������, ������� � ������ � ����\n2014\n����� �����, ����, � ���������");
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
//�
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
				map[i][j] == 'k' || map[i][j] == 'z')//h - ���� ����� ������
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
/*����� �� ���������� ��� �������� ������� ����� ������, ������ ���� �������� 4 ����� �� ��������*/
/*void story(){
	COORD position;                                     // ���������� ����������� ���������
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);  // ��������� ����������� ���������� ������������ ������

	FILE *storytxt;	//��������� �� ����
	char storyname[25] = "data\\story\\story";
	strcat_s(storyname, 21, cnum);
	fopen_s(&storytxt, storyname, "r"); //������ ���� � ������ ������
	
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

			if (id == 8 || id == 9){/*���� � ��� , ��� ���� ��������� ���� ���� �� ����������� ������ � ���� , �� ��� ������� �� ����� ��� �� ���*/
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

			if (h != 1){/*� ���� �����, �� �����*/
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
	printf("                                                             ���� 38 �� ������ ����, ������� ����                       ");
	SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 7));
	printf("                                                           ...������ ��� ���������� �������� �������� �����, ��� ������ ");
	printf("                                                           ����. � ���� ������ �� ���� �����,�� ���������� ��� �����    ");
	printf("                                                           ���. ����� ������� ����� ��� ������ �������� ����� �� ������,");
	printf("                                                           ���� ������� �������� ����. ���� ������� �������� ��� ����,  ");
	printf("                                                           �������, � �������� ���� ��� ����� ��������� ����.           ");
	printf("                                                                                                                        ");
	SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 6));
	printf("                                                             ���� 40 �� ������ ����                                     ");
	SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 7));
	printf("                                                           ...��� � ��������! ���� � ������ ��������� ������, ����������");
	printf("                                                           ���� ��� ������ � ������ �������. ������� � ������ � ����,   ");
	printf("                                                           ������ �� ����� ����������, � ������, ������.                ");
	printf("                                                                                                                        ");
	SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 6));
	printf("                                                             ���� 41 �� ������ ����                                     ");
	SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 7));
	printf("                                                           ...� ������� � ����� �� ������, ��� �������� ����, ���       ");
	printf("                                                           ���� ������� ���� �������� ������ �� �����, ?���������?      ");
	printf("                                                           ����������� �����. ������. ��� ������� �����������, ��� ���� ");
	printf("                                                           ���������� ������� �� ������.                                ");
	printf("                                                                                                                        ");
	SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 6));
	printf("                                                             ���� 44 �� ������ ����                                     ");
	SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 7));
	printf("                                                           ...������ ��������� ������ � �� ������� ��� ���������.       ");
	printf("                                                           � ����� ������� �� ����, �� � ����� �� ������ �������� ������");
	printf("                                                           ���� �� ����./����� � ��������  � 0������ �3�� � �6����      ");
	printf("                                                           ����6��. �������� ���45� ��... �����������( ����             ");
	printf("                                                           ����0�");
	SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 4));
	printf("�����7). ��              ���    //          �          ");
	printf("                                                             ..       ^^^     .    /                     ����           ");
	printf("                                                           �����0��352        ��+!���,1���� � ��7?^ ...       {./   ��� ");
	printf("                                                           ������ �� ����!/   ��3�        ���111� ������2**  3      3�  ");
	printf("                                                           � 12����      //   �0���   ..   ���0�, � ��(3��2    23     ��");
	printf("                                                               .�������      @$5      ///.                          .   ");

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
	printf("   �������");
	gotoxy(18, 4);
	printf("������ �������");
	gotoxy(78, 4);
	printf("        �������");
	gotoxy(0, 2);
	printf("+----------------------------------------------------------------------------------------------------------------------+");
	gotoxy(60, 6);
	printf("���: %s", pname);
	gotoxy(60, 7);
	if (wm == 1)
		printf("���: �������");
	else
		printf("���: �������");
	gotoxy(60, 8);
	printf("�������: %d", age);
	/*gotoxy(60, 9);
	printf("���������: %s", form);*/
	{
		int crdf, drdf, srdf;
		crdf = 60;
		drdf = 60;
		srdf = 60;
		gotoxy(crdf, 9);
		printf("���������: ");
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
	printf("|/     ��������� ������!   \\|");
	gotoxy(30, 12);
	printf("|    1)����(+10)            |");
	gotoxy(30, 13);
	printf("|    2)���������(+10)       |");
	gotoxy(30, 14);
	printf("|    3)��������(+1)         |");
	gotoxy(30, 15);
	printf("|    4)����(+1)             |");
	gotoxy(30, 16);
	printf("|\\   5)���������(+1)       /|");
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
	//���
		{
			char n1[20][10] = { "���", "���", "��", "���", "���", "��", "���", "���", "��", "���", "���", "���", "��", "���", "���", "���", "���", "���", "��", "���" };//15
			char n2[11][10] = { "��", "��", "��", "���", "��", "��", "���", "��", "��", "��", "���", };
			char n3[10][10] = { " ", "����", "��", "��", "�", "�", "�", "�", "�", "�" };

			char nn1[15][10] = { "���", "���", "���", "���", "���", "��", "���", "���", "���", "���", "���", "���", "���", "���", "��", };//�������
			char nn2[9][10] = { "�", "�", "���", "�", "��", "����", "��", "��", "���", };//�������
			char nn3[9][10] = { "��", "��", "���", "��", "���", "���", "�", "��", "���" };//�������

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
	//������� � ��������
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
	//��������
	{
		acr = rand()%5 + 1;
	}
	//���������
	{
		switch (rand() % 7 + 1){
		case 1: strcpy_s(form, 100, "����� �����,"); break;
		case 2: strcpy_s(form, 100, "����� �������,"); break;
		case 3: strcpy_s(form, 100, "����� �������,"); break;
		case 4: strcpy_s(form, 100, "����� �����,"); break;
		case 5: strcpy_s(form, 100, "����� ��������,"); break;
		case 6: strcpy_s(form, 100, "����� ��������,"); break;
		case 7: strcpy_s(form, 100, "����� ������,"); break;
		}
		if (age <= 50){
			switch (rand() % 4 + 1){
			case 1: strcat_s(form, 100, "������ ������ "); break;
			case 2: strcat_s(form, 100, "������ ����� "); break;
			case 3: strcat_s(form, 100, "������ ����� "); break;
			case 4: strcat_s(form, 100, "������ ������� "); break;
			}
			if (age >= 40 && age <= 50){
				strcat_s(form, 100, "� ������ �������, ");
			}else
				switch (rand() % (4-1+1) + 1){
				case 1: strcat_s(form, 100, "� ����� ��������, "); break;
				case 2: strcat_s(form, 100, "� ����� ��������, "); break;
				case 3: strcat_s(form, 100, "� ������ ��������, "); break;
				case 4: strcat_s(form, 100, "� ���������� ��������, "); break;
			}
		}
		else
			strcat_s(form, 100, "������ �����, ");

		switch (rand() % 3 + 1){
		case 1:stren = 5; strcat_s(form, 150, "������������ �������, "); break;
		case 2: stren = 1; strcat_s(form, 150, "������������ �����, "); break;
		case 3: stren = 3;  strcat_s(form, 150, "������������ �������, "); break;
		}
		switch (rand() % 3 + 1){
		case 1:mental = 5; strcat_s(form, 200, "��������� �������. "); break;
		case 2:mental = 1; strcat_s(form, 200, "��������� ������. "); break;
		case 3: mental = 3; strcat_s(form, 200, "��������� �������. "); break;
		}

	}
	strcat_s(form, 200, "$");
}

void traps(){
	if (oops[mobs1[0].y][mobs1[0].x] == 1 || oops[mobs1[0].y][mobs1[0].x] == 2){
		if ((rand() % 3) == 2){
			if (oops[mobs1[0].y][mobs1[0].x] == 1){
				mobs1[0].hp -= 5;
				log("����!                           ", 0, 0);
				map[mobs1[0].y][mobs1[0].x] = '^';
				lows += 1;
			}
			if (oops[mobs1[0].y][mobs1[0].x] == 2){
				eff1[4].efbool = 1;
				log("�����!                          ", 0, 0);
				map[mobs1[0].y][mobs1[0].x] = '^';
				lows += 1;
			}
		}
		else{
			log("!����!                              ", 0, 0);
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
		log("!���!                           ", 0, 0);
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
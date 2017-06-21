#include <stdbool.h>

void travel(struct Mob1 *mob, int plusx, int plusy);
void move(struct Mob1 *mob);
void attack(int num);
void newmob1(int num, int id, int x, int y);
int searchmob1(int x, int y);
void mobsay(int idmob);//H
void pos(int *xm, int *ym);//H
void IImap(int y, int x,int id);//H
int wizardcock(int y, int x, int yy, int xx, int look);
int wizardbock(int *xm, int *ym);
void trade();
void log(char l[46],int typec,int t);//подобные функции надо вынести в другой глобальный файл
void logdmg(int dmg,int typec,int t);
char* IntToStr(int n);
void logdraw();

void wormsmove();
void wormsmove();
void newworm(int dlin, bool boss);
int searchworm(int x, int y);
void wormsback();
void wormsbroke(num, part);



//меткость,сила,интеллект, зоркость
char pname[50] ;
char form[200];
_Bool wm;
short int age;
int acr, stren, mental, vig, score, lvl, olvlup, hunger;
int golds, kills, lows, potrs;

struct Mob1{
	int id, x, y, hp, dmg, idEff, look, hpe, score, lvlup, lvl;
	int mana, manae;
	int cri, cri2;
	int defense;
	char simv;
};
struct Mob1* mobs1;
int mob1count;
//ээффекты
struct Eff1{
	int cycl;
	int result;
	int id;
	int efbool;
	int endc;
};
struct Eff1 eff1[5];
void allEff();
int R[45][85];

int money;
int tov[3];
int price[3];
_Bool torg;
//ПЕРЕНЕСЕНО ИЗ МАЙН
int mapnum;

void eyes();
int eye[31][81];
int eye2[31][81];
/*
Black = 0,
Blue = 1,
Green = 2,
Cyan = 3,
Red = 4,
Magenta = 5,
Brown = 6,
LightGray = 7,
DarkGray = 8,
LightBlue = 9,
LightGreen = 10,
LightCyan = 11,
LightRed = 12,
LightMagenta = 13,
Yellow = 14,
White = 15
*/

struct wormpart{
	bool head;
	bool invis;

	char simv;
	int hp;
	int x;
	int y;
};

struct Sworm{
	int num;
	int dlin;
	struct Sworm *prewworm;
	struct Sworm *nextworm;
	bool boss;
	//bool invis;
	struct wormpart *part;

	int status; // занятость    0 - свободен 1-снизу 2-сбоку 3-спавнит червей

	int cdsniz;
	int maxcdsniz;
	int snizx;
	int snizy;

	int cdsbok;
	int maxcdsbok;
	int gotox;
	int gotoy;

	int cdnew;
	int maxcdnew;
};

struct Sworm* worms;
int wormscount;

//расса,ловкость(?)
//меткость,сила,интеллект, зоркость(+-)
//тяжелый меч, нож,дубина(+)
//дубовый лук(лучший),лук из осины(худший)(+)
//темная книга(что то отнимает),мудрая книга(что то прибавляет), 
//книга историй(можно прочесть историю), книга оббитая золотом(+к деньгам),чистая книга
//свиток распознавания(?), свиток телепортации(?)
//гнилое яблоко, яблоко, солонина,черствый хлеб,червивый гриб (+)
//крысиный зуб,палка,комок слизи,фекалии гнома
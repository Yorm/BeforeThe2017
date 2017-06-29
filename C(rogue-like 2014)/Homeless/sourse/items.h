#include <stdbool.h>

void itemrand(int type, int id, int chance);
void itemnew(int type, int id);
void  itemdel(int num);
void itemuse(int num); 

struct in1{ //Consumables - расходники и прочее
	int id;
	int num;
	bool full;
	int mind;
	int onhp;
	int arrow;
	int onMana;

};

struct in2{ //Equipment - экипировка
	int id;
	int num;
	bool full;

	int dmg;
	int def;
	bool equip;
};
struct in3{ //Magic - маги€ и все стрел€ющее
	int id;
	int num;
	bool full;
	bool equip;
};

struct inventory{
	int allitem;
	struct in1 consumables[10];
	struct in2 equipments[10];
	struct in3 magic[10];
	
}myinv;

struct heroequip{
	bool bowl;
	bool sword;
	bool helmet;
	bool armor;
	bool sv_fire;
	bool sv_rock;
	bool sv_blind;
	bool sv_inf;
}heroeq;

char *itemnames[];
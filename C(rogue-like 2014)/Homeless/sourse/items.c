#include <stdio.h>
#include <stdlib.h>
#include "items.h"
#include "mobs.h"
#include "global.h"



char *itemnames[] = {
		{ "Мутная колба" },//0
		{ "Хороший меч" },//1
		{ "Шлем" },
		{ "Броня" },
		{ "Св.\"Огонь\"(5)" },
		{ "Св.\"Обрушение\"(5)" },//5
		{ "Св.\"Слепота\"(15)" },
		{ "Словарик" },
		{ "Простой лук" },
		{ "Св.\"Путь\"" },
		{ "Яблоко" },//10
		{ "Гнилое яблоко" },
		{ "Солонина" },
		{ "Черствый хлеб" },
		{ "Червивый гриб" },
		{ "Нож" },//15
		{ "Тяжелый меч" },
		{ "Дубина" },
		{ "Дубовый лук" },
		{ "Осиновый лук" },
		{ "Старый посох" },//20
		{ "Пустая книга" },
		{ "Золотая книга" },
		{ "Мертвая книга" },
		{ "Книга знания" },
		{ "Бурдюк" },//25
		{ "Доска" },
		{ "Свеча" }

};
//манипуляции с шансом выпадения
void itemrand(int type, int id, int chance){
	int i;

	i = rand() % 100;
	if (i < chance){
		if (type == -1){
			type = rand() % 3 + 1;
			id = -1; //защита от ошибок
		}
		if (id == -1){
			i = rand() % 100 + 1;
			if (type == 1){ //расходники
				if (i >= 1 && i <= 10){// колба - пустышка
					id = 0;
					log("Найдена мутная колба             ", 0, 0);
				}
				else if (i >= 11 && i <= 20){// колба - лечилка
					id = 1;
					log("Найдена мутная колба             ", 0, 0);
				}
				else if (i >= 21 && i <= 30){// колба с ядом
					id = 2;
					log("Найдена мутная колба             ", 0, 0);
				}
				else if (i >= 31 && i <= 40){// словарик
					id = 3;
					log("Найден словарь языков            ", 0, 0);
				}
				else if (i >= 41 && i <= 50){// колба с маной
					id = 4;
					log("Найдена мутная колба             ", 0, 0); //5 есть + 5 еще
				}
				else if (i >= 51 && i <= 60){// яблоко
					id = 5;
					log("Найдено яблоко                   ", 0, 0);
				}
				else if (i >= 61 && i <= 70){// гнилое яблоко
					id = 6;
					log("Найдено гнилое яблоко            ", 0, 0);
				}
				else if (i >= 71 && i <= 80){// солонина
					id = 7;
					log("Найдена солонина                 ", 0, 0);
				}
				else if (i >= 81 && i <= 90){// черствый хлеб
					id = 8;
					log("Найден черствый хлеб             ", 0, 0);
				}
				else if (i >= 91 && i <= 100){// червивый гриб
					id = 9;
					log("Найден червивый гриб             ", 0, 0);
				}


			}else if (type == 2){ // экипировка
				if (i >= 1 && i <= 10){// меч
					id = 0;
					log("Найден хороший меч               ", 0, 0);
				}
				else if (i >= 11 && i <= 20){// шлем
					id = 1;
					log("Найден хороший шлем              ", 0, 0);
				}
				else if (i >= 21 && i <= 30){// броня
					id = 2;
					log("Найден хорошая броня             ", 0, 0);
				}
				else if (i >= 31 && i <= 40){// лук
					id = 3;
					log("Найден простой лук               ", 0, 0);
				}
				else if (i >= 41 && i <= 50){// нож
					id = 4;
					log("Найден нож                       ", 0, 0);
				}
				else if (i >= 51 && i <= 60){// тяжелый меч
					id = 5;
					log("Найден тяжелый меч               ", 0, 0);
				}
				else if (i >= 61 && i <= 70){// дубина
					id = 6;
					log("Найдена дубина                   ", 0, 0);
				}
				else if (i >= 71 && i <= 80){// дубовый лук
					id = 7;
					log("Найден дубовый лук               ", 0, 0);
				}
				else if (i >= 81 && i <= 90){// осиновый лук
					id = 8;
					log("Найден осиновый лук              ", 0, 0);
				}
				else if (i >= 91 && i <= 100){// посох
					id = 9;
					log("Найден старый посох              ", 0, 0);
				}
			}else if (type == 3){ // экипировка
				if (i >= 1 && i <= 10){// фаербол
					id = 0;
					log("Найден свиток \"Огонь\"           ", 0, 0);
				}
				else if (i >= 11 && i <= 20){// камни с потолка
					id = 1;
					log("Найден свиток \"Обрушение\"       ", 0, 0);
				}
				else if (i >= 21 && i <= 30){// ослепление
					id = 2;
					log("Найден свиток \"Слепота\"         ", 0, 0);
				}
				else if (i >= 31 && i <= 40){// ослепление
					id = 3;
					log("Найден свиток \"Путь\"            ", 0, 0);
				} 
				else if (i >= 41 && i <= 50){// пустая книга
					id = 4;
					log("Найдена пустая книга              ", 0, 0);
				}
				else if (i >= 51 && i <= 60){// золотая книга
					id = 5;
					log("Найдена золотая книга             ", 0, 0);
				}
				else if (i >= 61 && i <= 70){// мертвая книга
					id = 6;
					log("Найдена мертвая книга             ", 0, 0);
				}
				else if (i >= 71 && i <= 80){// книга знаний
					id = 7;
					log("Найдена книга знаний              ", 0, 0);
				}
				else if (i >= 81 && i <= 90){// бурдюк
					id = 8;
					log("Найден бурдюк                     ", 0, 0);
				}
				else if (i >= 91 && i <= 100){// доска
					id = 9;
					log("Найдена доска                     ", 0, 0);
				}
			}
		}
		itemnew(type, id);
	}
}

//1 2 eff1[i].efbool
// так как у нас 1 перс, функция работает напрямую с его инвентарем
void itemnew(int type, int id){
	int i;
	i = 0;

	if (type == 1){
		while (myinv.consumables[i].full == 1)
			i++;
		myinv.consumables[i].full = 1;
		myinv.consumables[i].id = id;
		myinv.consumables[i].num = myinv.allitem;

		switch (id){
		case 0:
			myinv.consumables[i].onhp = 0;
			break;
		case 1:
			myinv.consumables[i].onhp = 10;
			break;
		case 2:
			myinv.consumables[i].onhp = -10;
			break;
		case 3:
			myinv.consumables[i].onhp = 5;
			if (myinv.consumables[i].mind == 0)
				myinv.consumables[i].mind = 0;
			break;
		case 4:
			myinv.consumables[i].onMana = 30;
			break;
		case 5:
			myinv.consumables[i].onhp = 5;
			break;
		case 6:
			myinv.consumables[i].onhp = -5;
			break;
		case 7:
			myinv.consumables[i].onhp = 10;
			break;
		case 8:
			myinv.consumables[i].onhp = 2;
			break;
		case 9:
			myinv.consumables[i].onhp = -10;
			break;
		}


	}
	else if (type == 2){
		while (myinv.equipments[i].full == 1)
			i++;
		myinv.equipments[i].full = 1;
		myinv.equipments[i].id = id;
		myinv.equipments[i].num = myinv.allitem;

		switch (id){
		case 0: // меч
			myinv.equipments[i].dmg = 2;
			break;
		case 1: // шлем
			myinv.equipments[i].def = 1;
			break;
		case 2: // броня
			myinv.equipments[i].def = 3;
			break;
		case 3: // хороший лук
			myinv.equipments[i].dmg = 1;
			break;
		case 4: // нож
			myinv.equipments[i].dmg = 1;
			break;
		case 5: // тяжелый меч
			myinv.equipments[i].dmg = 5;
			break;
		case 6: // дубина
			myinv.equipments[i].dmg = 3;
			break;
		case 7: // дубовый лук
			myinv.equipments[i].dmg = 4;
			break;
		case 8: // осиновый лук
			myinv.equipments[i].dmg = 2;
			break;
		case 9: // посох
			myinv.equipments[i].dmg = 1;
			break;

		}
	}
	else if (type == 3){
		while (myinv.magic[i].full == 1)
			i++;
		myinv.magic[i].full = 1;
		myinv.magic[i].id = id;
		myinv.magic[i].num = myinv.allitem;
		/*Свитки никаких эффектов не несут*/
	}
	myinv.allitem++;
}


void itemuse(int num){
	int i;
	int type;

	i = 0;

	while (i < 10){
		if (myinv.consumables[i].full == 1 && myinv.consumables[i].num == num){
			type = 1;
			break;
		}
		if (myinv.equipments[i].full == 1 && myinv.equipments[i].num == num){
			type = 2;
			break;
		}
		if (myinv.magic[i].full == 1 && myinv.magic[i].num == num){
			type = 3;
			break;
		}
		i++;
	}

	if (type == 1){
		switch (myinv.consumables[i].id){
		case 0: 
			mobs1[0].hp += myinv.consumables[i].onhp;
			itemdel(myinv.consumables[i].num);
			break;
		case 1:
			eff1[1].efbool = 1;
			if ( mobs1[0].hp <= mobs1[0].hpe-1)
				mobs1[0].hp += myinv.consumables[i].onhp;
			itemdel(myinv.consumables[i].num);
			potrs += 1;
			break;
		case 2:
			eff1[2].efbool = 1;
			mobs1[0].hp += myinv.consumables[i].onhp;
			itemdel(myinv.consumables[i].num);
			potrs += 1;
			break;
		case 3:
			if (myinv.consumables[3].mind == 0){
				myinv.consumables[3].mind = 1;
				mobs1[0].hp += myinv.consumables[i].onhp;
			}
			itemdel(myinv.consumables[i].num);
			break;
		case 4:
			for (int i = 0; i < 30; i++){
				if (mobs1[0].mana < mobs1[0].manae)
					mobs1[0].mana+=1;
			}			
			itemdel(myinv.consumables[i].num);	
			potrs += 1;
			break;
		case 5:case 7:case 8:
			if (mobs1[0].hp <= mobs1[0].hpe - 1)
				mobs1[0].hp += myinv.consumables[i].onhp;
			itemdel(myinv.consumables[i].num);
			potrs += 1;
			hunger = 0;
			break;
		case 6:case 9:
			mobs1[0].hp += myinv.consumables[i].onhp;
			itemdel(myinv.consumables[i].num);
			if ((hunger - 5) >= 0)
				hunger -= 5;
			potrs += 1;
			break;
		}
	}
	else if (type == 2){
		switch (myinv.equipments[i].id){
		case 0: case 4:case 5:case 6:case 9://мечи,ножи,дубины
			if (heroeq.sword == 0 && heroeq.bowl != 1){
				if (myinv.equipments[i].id == 0 && stren >= 3 ){
					mobs1[0].dmg = myinv.equipments[i].dmg;
					heroeq.sword = 1;
					myinv.equipments[i].equip = 1;
					mobs1[0].cri = 1;
					mobs1[0].cri2 = 3;
				}
				if (myinv.equipments[i].id == 5 && stren == 5 ){
					mobs1[0].dmg = myinv.equipments[i].dmg;
					heroeq.sword = 1;
					myinv.equipments[i].equip = 1;
					mobs1[0].cri = 1;
					mobs1[0].cri2 = 3;
				}
				if (myinv.equipments[i].id == 6 && stren >= 4 ){
					mobs1[0].dmg = myinv.equipments[i].dmg;
					heroeq.sword = 1;
					myinv.equipments[i].equip = 1;
					mobs1[0].cri = 1;
					mobs1[0].cri2 = 3;
				}
				if ((myinv.equipments[i].id == 4 || myinv.equipments[i].id == 9) && (stren >= 1 )){
					mobs1[0].dmg = myinv.equipments[i].dmg;
					heroeq.sword = 1;
					myinv.equipments[i].equip = 1;
					mobs1[0].cri = 1;
					mobs1[0].cri2 = 3;
				}
			}
			else if (heroeq.sword == 1 && myinv.equipments[i].equip == 1){
				mobs1[0].dmg -= myinv.equipments[i].dmg;
				heroeq.sword = 0;
				myinv.equipments[i].equip = 0;
				mobs1[0].cri = 0;
				mobs1[0].cri2 = 1;
			}
			break;
		case 1: // шлема
			if (heroeq.helmet == 0){			
			mobs1[0].defense += myinv.equipments[i].def;
			heroeq.helmet = 1;
			myinv.equipments[i].equip = 1;
			}
			else if (heroeq.helmet == 1 && myinv.equipments[i].equip == 1){
				mobs1[0].defense -= myinv.equipments[i].def;
				heroeq.helmet = 0;
				myinv.equipments[i].equip = 0;
			}
			break;
		case 2: // броня
			if (heroeq.armor == 0){
				mobs1[0].defense += myinv.equipments[i].def;
				heroeq.armor = 1;
				myinv.equipments[i].equip = 1;
			}
			else if (heroeq.armor == 1 && myinv.equipments[i].equip == 1){
				mobs1[0].defense -= myinv.equipments[i].def;
				heroeq.armor = 0;
				myinv.equipments[i].equip = 0;
			}
			break;
		case 3:case 7:case 8: // лук
			if (heroeq.bowl == 0 && heroeq.sword != 1 && heroeq.sv_blind != 1 && heroeq.sv_fire != 1 && heroeq.sv_rock != 1 && heroeq.sv_inf != 1){
				mobs1[0].dmg = myinv.equipments[i].dmg;//+=
				heroeq.bowl = 1;
				myinv.equipments[i].equip = 1;
			}
			else if (heroeq.bowl == 1 && myinv.equipments[i].equip == 1){
				mobs1[0].dmg -= myinv.equipments[i].dmg;
				heroeq.bowl = 0;
				myinv.equipments[i].equip = 0;
			}
			break;
		}
	}
	else if (type == 3){
		switch (myinv.magic[i].id){
		case 0: //огонь
			if (heroeq.sv_fire == 0 && heroeq.sv_rock != 1 && heroeq.sv_blind != 1 && heroeq.sv_inf != 1 && heroeq.bowl != 1){//&& 
				if (mental >= 1){
					heroeq.sv_fire = 1;
					myinv.magic[i].equip = 1;
				}
			}
			else if (heroeq.sv_fire == 1 && myinv.magic[i].equip == 1){
				heroeq.sv_fire = 0;
				myinv.magic[i].equip = 0;
			}
			break;
		case 1: // камень
			if (heroeq.sv_rock == 0 && heroeq.sv_fire != 1 && heroeq.sv_blind != 1 && heroeq.sv_inf != 1 && heroeq.bowl != 1){//
				if (mental >= 3){
					heroeq.sv_rock = 1;
					myinv.magic[i].equip = 1;
				}
			}
			else if (heroeq.sv_rock == 1 && myinv.magic[i].equip == 1){
				heroeq.sv_rock = 0;
				myinv.magic[i].equip = 0;
			}
			break;
		case 2: // слеп
			if (heroeq.sv_blind == 0 && heroeq.sv_fire != 1 && heroeq.sv_rock != 1 && heroeq.sv_inf != 1 && heroeq.bowl != 1){//
				if (mental >= 4){
					heroeq.sv_blind = 1;
					myinv.magic[i].equip = 1;
				}
			}
			else if (heroeq.sv_blind == 1 && myinv.magic[i].equip == 1){
				heroeq.sv_blind = 0;
				myinv.magic[i].equip = 0;
			}
			break;
		case 3: // изучения
				if (mental == 5){
					for (int i = 1; i < 31; i++)
						for (int b = 1; b < 81; b++)
							eye2[i][b] = 3;
					heroeq.sv_inf = 1;
					itemdel(myinv.magic[i].num);
				}
			
			break;
		case 4: itemdel(myinv.magic[i].num); break;
		case 5:
		{
			int rm;
			rm = rand() % (15 - 5 + 1) + 5;
			money += rm;
			golds += rm;
			log("Кошель пополнился               ", 0, 0);
			itemdel(myinv.magic[i].num);
		}
			break;
		case 6: {
			int rr;
			rr = rand() % 5 + 1;
			if (rr == 1){
				if (mobs1[0].mana > 10)
					mobs1[0].mana -= 10;
				if (mobs1[0].manae > 10)
					mobs1[0].manae -= 10;
			}
			if (rr == 2){
				if (mobs1[0].hp > 10)
					mobs1[0].hp -= 10;
				if (mobs1[0].hpe > 10)
					mobs1[0].hpe -= 10;
			}
			if (rr == 3)
				if (acr > 1)
					acr -= 1;
			if (rr == 4)
				if (mental > 1)
					mental -= 1;
			if (rr == 5)
				if (stren > 1)
					stren -= 1;

			itemdel(myinv.magic[i].num);
		}
			break;
		case 7:{
			int rr;
			rr = rand() % 5 + 1;
			if (rr == 1){
				mobs1[0].mana += 10;
				mobs1[0].manae += 10;
			}
			if (rr == 2){
				mobs1[0].hp += 10;
				mobs1[0].hpe += 10;
			}
			if (rr == 3)
				if (acr < 5)
					acr += 1;
			if (rr == 4)
				if (mental < 5)
					mental += 1;
			if (rr == 5)
				if (stren < 5)
					stren += 1;
			itemdel(myinv.magic[i].num);
		}
			break;
		case 8:
			if (eff1[4].efbool == 1){
				eff1[4].efbool = 0;
				log("Потушен                             ", 0, 0);
			}
			if (mobs1[0].hp < mobs1[0].hpe)
				mobs1[0].hp += 1;
			itemdel(myinv.magic[i].num);
			break;
		case 9:
			for (int i = -1; i < 2; i++)
				for (int j = -1; j < 2; j++){
				if (oops[mobs1[0].y + j][mobs1[0].x + i] == 1 || oops[mobs1[0].y + j][mobs1[0].x + i] == 2){
					oops[mobs1[0].y + j][mobs1[0].x + i] = 0;
					map[mobs1[0].y + j][mobs1[0].x + i] = '=';
				}
				if (map[mobs1[0].y + j][mobs1[0].x + i] == '0'){
					map[mobs1[0].y + j][mobs1[0].x + i] = '=';
				}
				if (map[mobs1[0].y + j][mobs1[0].x + i] == '\''){
					map[mobs1[0].y + j][mobs1[0].x + i] = ':';
				}
				}
			itemdel(myinv.magic[i].num);
			break;
		}
	}
}
void itemdel(int num){
	int i;

	myinv.allitem--;

	for (i = 0; i<10; i++){
		if (myinv.consumables[i].num == num && myinv.consumables[i].full == 1)
			myinv.consumables[i].full = 0;
		if (myinv.consumables[i].num >num && myinv.consumables[i].full == 1)
			myinv.consumables[i].num--;

		if (myinv.equipments[i].num == num && myinv.equipments[i].full == 1)
			myinv.equipments[i].full = 0;
		if (myinv.equipments[i].num >num && myinv.equipments[i].full == 1)
			myinv.equipments[i].num--;

		if (myinv.magic[i].num == num && myinv.magic[i].full == 1)
			myinv.magic[i].full = 0;
		if (myinv.magic[i].num >num && myinv.magic[i].full == 1)
			myinv.magic[i].num--;
	}
}
/*
**Consumables**
0 - колба-пустышка (пишет просто колба)
1 - колба-лечилка  (пишет просто колба)
2 - колба с ядом   (пишет просто колба)

**Equipment**
0 - меч
1 - шлем
2 - броня
*/


#include <stdio.h>
#include <stdlib.h>
#include "items.h"
#include "mobs.h"
#include "global.h"



char *itemnames[] = {
		{ "������ �����" },//0
		{ "������� ���" },//1
		{ "����" },
		{ "�����" },
		{ "��.\"�����\"(5)" },
		{ "��.\"���������\"(5)" },//5
		{ "��.\"�������\"(15)" },
		{ "��������" },
		{ "������� ���" },
		{ "��.\"����\"" },
		{ "������" },//10
		{ "������ ������" },
		{ "��������" },
		{ "�������� ����" },
		{ "�������� ����" },
		{ "���" },//15
		{ "������� ���" },
		{ "������" },
		{ "������� ���" },
		{ "�������� ���" },
		{ "������ �����" },//20
		{ "������ �����" },
		{ "������� �����" },
		{ "������� �����" },
		{ "����� ������" },
		{ "������" },//25
		{ "�����" },
		{ "�����" }

};
//����������� � ������ ���������
void itemrand(int type, int id, int chance){
	int i;

	i = rand() % 100;
	if (i < chance){
		if (type == -1){
			type = rand() % 3 + 1;
			id = -1; //������ �� ������
		}
		if (id == -1){
			i = rand() % 100 + 1;
			if (type == 1){ //����������
				if (i >= 1 && i <= 10){// ����� - ��������
					id = 0;
					log("������� ������ �����             ", 0, 0);
				}
				else if (i >= 11 && i <= 20){// ����� - �������
					id = 1;
					log("������� ������ �����             ", 0, 0);
				}
				else if (i >= 21 && i <= 30){// ����� � ����
					id = 2;
					log("������� ������ �����             ", 0, 0);
				}
				else if (i >= 31 && i <= 40){// ��������
					id = 3;
					log("������ ������� ������            ", 0, 0);
				}
				else if (i >= 41 && i <= 50){// ����� � �����
					id = 4;
					log("������� ������ �����             ", 0, 0); //5 ���� + 5 ���
				}
				else if (i >= 51 && i <= 60){// ������
					id = 5;
					log("������� ������                   ", 0, 0);
				}
				else if (i >= 61 && i <= 70){// ������ ������
					id = 6;
					log("������� ������ ������            ", 0, 0);
				}
				else if (i >= 71 && i <= 80){// ��������
					id = 7;
					log("������� ��������                 ", 0, 0);
				}
				else if (i >= 81 && i <= 90){// �������� ����
					id = 8;
					log("������ �������� ����             ", 0, 0);
				}
				else if (i >= 91 && i <= 100){// �������� ����
					id = 9;
					log("������ �������� ����             ", 0, 0);
				}


			}else if (type == 2){ // ����������
				if (i >= 1 && i <= 10){// ���
					id = 0;
					log("������ ������� ���               ", 0, 0);
				}
				else if (i >= 11 && i <= 20){// ����
					id = 1;
					log("������ ������� ����              ", 0, 0);
				}
				else if (i >= 21 && i <= 30){// �����
					id = 2;
					log("������ ������� �����             ", 0, 0);
				}
				else if (i >= 31 && i <= 40){// ���
					id = 3;
					log("������ ������� ���               ", 0, 0);
				}
				else if (i >= 41 && i <= 50){// ���
					id = 4;
					log("������ ���                       ", 0, 0);
				}
				else if (i >= 51 && i <= 60){// ������� ���
					id = 5;
					log("������ ������� ���               ", 0, 0);
				}
				else if (i >= 61 && i <= 70){// ������
					id = 6;
					log("������� ������                   ", 0, 0);
				}
				else if (i >= 71 && i <= 80){// ������� ���
					id = 7;
					log("������ ������� ���               ", 0, 0);
				}
				else if (i >= 81 && i <= 90){// �������� ���
					id = 8;
					log("������ �������� ���              ", 0, 0);
				}
				else if (i >= 91 && i <= 100){// �����
					id = 9;
					log("������ ������ �����              ", 0, 0);
				}
			}else if (type == 3){ // ����������
				if (i >= 1 && i <= 10){// �������
					id = 0;
					log("������ ������ \"�����\"           ", 0, 0);
				}
				else if (i >= 11 && i <= 20){// ����� � �������
					id = 1;
					log("������ ������ \"���������\"       ", 0, 0);
				}
				else if (i >= 21 && i <= 30){// ����������
					id = 2;
					log("������ ������ \"�������\"         ", 0, 0);
				}
				else if (i >= 31 && i <= 40){// ����������
					id = 3;
					log("������ ������ \"����\"            ", 0, 0);
				} 
				else if (i >= 41 && i <= 50){// ������ �����
					id = 4;
					log("������� ������ �����              ", 0, 0);
				}
				else if (i >= 51 && i <= 60){// ������� �����
					id = 5;
					log("������� ������� �����             ", 0, 0);
				}
				else if (i >= 61 && i <= 70){// ������� �����
					id = 6;
					log("������� ������� �����             ", 0, 0);
				}
				else if (i >= 71 && i <= 80){// ����� ������
					id = 7;
					log("������� ����� ������              ", 0, 0);
				}
				else if (i >= 81 && i <= 90){// ������
					id = 8;
					log("������ ������                     ", 0, 0);
				}
				else if (i >= 91 && i <= 100){// �����
					id = 9;
					log("������� �����                     ", 0, 0);
				}
			}
		}
		itemnew(type, id);
	}
}

//1 2 eff1[i].efbool
// ��� ��� � ��� 1 ����, ������� �������� �������� � ��� ����������
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
		case 0: // ���
			myinv.equipments[i].dmg = 2;
			break;
		case 1: // ����
			myinv.equipments[i].def = 1;
			break;
		case 2: // �����
			myinv.equipments[i].def = 3;
			break;
		case 3: // ������� ���
			myinv.equipments[i].dmg = 1;
			break;
		case 4: // ���
			myinv.equipments[i].dmg = 1;
			break;
		case 5: // ������� ���
			myinv.equipments[i].dmg = 5;
			break;
		case 6: // ������
			myinv.equipments[i].dmg = 3;
			break;
		case 7: // ������� ���
			myinv.equipments[i].dmg = 4;
			break;
		case 8: // �������� ���
			myinv.equipments[i].dmg = 2;
			break;
		case 9: // �����
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
		/*������ ������� �������� �� �����*/
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
		case 0: case 4:case 5:case 6:case 9://����,����,������
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
		case 1: // �����
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
		case 2: // �����
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
		case 3:case 7:case 8: // ���
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
		case 0: //�����
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
		case 1: // ������
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
		case 2: // ����
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
		case 3: // ��������
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
			log("������ ����������               ", 0, 0);
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
				log("�������                             ", 0, 0);
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
0 - �����-�������� (����� ������ �����)
1 - �����-�������  (����� ������ �����)
2 - ����� � ����   (����� ������ �����)

**Equipment**
0 - ���
1 - ����
2 - �����
*/


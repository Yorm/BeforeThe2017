#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
using namespace sf;
using namespace std;


//#############################################//
class Pic{
public:
	String File;
	Image image;
	Texture texture;
	Sprite sprite;
	//'''''''''''''''''''''''''''''''''''''''''''''//
	Pic(String F){
		File = F;
		image.loadFromFile("pic/" + File);
		texture.loadFromImage(image);
		sprite.setTexture(texture);
	}
};
//#############################################//

class bullet
{
public:	
	struct cell
	{
		float x, y;
		int dir;

		int num;

		cell *next, *prev;
	};

	int _count;
	int w, h;
	float speed;

	cell *first, *last;

	Image image;
	Texture texture;
	Sprite sprite;
	
	/*bullet(int X,int Y,int W,int H){
		speed = 0.1;
		cell.dir = 1;
		image.loadFromFile("pic/spc_inv_tileset.png");
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		cell.x = X; cell.y = Y; cell.w = W; cell.h = H;
		sprite.setTextureRect(IntRect(0, 89, cell.w, cell.h));
	}*/
	
	bullet(int W, int H) :first(NULL), last(NULL), _count(0)
	{
		speed = 0.1;
		w = W;h = H;	

		image.loadFromFile("pic/spc_inv_tileset.png");
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setTextureRect(IntRect(0, 89, w, h));
	}

	void add(int x, int y,int dir,int num)
	{
		cell* newcell = new cell;

		newcell->x = x;
		newcell->y = y;
		newcell->dir = dir;
		newcell->num = num;
		

		newcell->next = NULL;
		if (first != NULL) //���� ������ �� ����
		{
			newcell->prev = last; 
			last->next = newcell; 
			last = newcell; 
		}
		else //���� ������ ������
		{
		/*	newcell->prev = Tail; //���������, ��� ���������� ��������� ������ ������������ ������������, ����� ��������� ������� ������������� ������
			Tail->next = newcell; //��������� �� ��������� ������������ ��� ��������������� ������ ����������� ������� ������
			Tail = newcell;       //����� ���� ��� ������� ��� ���� ��������� � ��� ����������, ���������, ��� ��������� ������������ ��� ������ ��� ����������� �������
		*/
			newcell->prev = NULL; 
			first = last = newcell; 
		}

		_count++;
		cout << _count<<endl;
	}

	void del(int num){//�������� ��������
		//���� ������� ������ �������, �� ����� ���� ����� ��������
		//� ������ ���� ������ ������, � ������ ���� ��������� ���������
		//������� ��������� ������ ����������
		if (first == NULL) return;
		if ((num == 1) && (first->next)){ //���� ������� ������, �� ���� � ������, ��
			cell *current = first;	//���������, ��� ��� ����� ������ ������
			first = first->next;	//�������� ������ �� ��������� �� ������� �������
			first->prev = NULL;	//������ ���, ���� ���������� ������ ������� ��� ������
			delete current;		//������� ��������� ������
			_count--;		//����������� ��������� �������
			cout << "������ ������ ���� ������" << _count<<endl;
			return;		//� ������� �� �������
			
		}
		else if ((num == 1) && (first == last)){ //���� ������� ������, �� � ������ ������ 1 �������

			first->next = NULL;	//�������� ��� ��� �����
			first = NULL;
			delete first;		//������� ��������� �� ������
			_count = 0;		//����������� ����������, ��� � ������ ���� ���������
			return;			//� ������� �� �������

		}

		//����� ����� ����, ��� ��������� ������� �������� ��������� ��������� ������
		if (num == _count){
			cell *current = last;	//���������, ��� ��� ����� �����
			last = last->prev;	//���������� ����� ������� �����
			last->next = NULL;	//����������, ��� ������� �� ������� �����
			delete current;	//������� ������ �� ������� ������
			_count--;		//����������� ��������� ������� ���������
			return;		//� ������� �� �������
		}

		//���� �� ��������� ������� ����� ���-�� � �������� ������, �� ����� ��� ����� �������

		cell *current = first,
			*current2; //temp-��������� �������, temp2 �����, ����� �� �������� ������

		//cout<<count_<<"\n";
		for (int i = 0; i<num - 1; i++) current = current->next;  //���� � ������ ���������� ��������

		current2 = current;	//�������� ���������� ����� ���������� ��������
		current2->prev->next = current->next;	//���������� ������, ��� ��������� �� ����� ������ ��������� ��������� - ��� ��������� �� ����������
		current2->next->prev = current->prev; //� ���������� ��� ���������� - ��� ���������� ��� ����������
		delete current; //������ ����� ����� ���������� ������, ������ ����� �� ������ ���������� ��������
		_count--; //����������� ��������� ����� ��������� � ������.
	}

	void update(float time, RenderWindow& win)
	{
		if (first == NULL) return;
		cell* current = first;
		while (current){
			switch (current->dir)//������� �� ��������� - ��������� ����
			{
			case 1: current->y += -speed*time; break;//�����
			case 2: current->y += speed*time; break;//����
			};

			collision(&current->y);

			sprite.setPosition(current->x, current->y);
			current = current->next;
			
			win.draw(sprite);// ������ � ������ ��� �����, ������ ������
		}
	}

	void collision(float *y)
	{
		if (*y < 2){ *y = 2; del(1); }
	}
};
//#############################################//
class ship{
public:
	int lives;
	int dir,//�����������
		score;  //����
	//''// ��� ��� ������� � ������������
	float x, y,
		w, h,
		dx, dy,
		speed;
	//''// ��� ��� ������� � ��������
	int num_bullet;

	Image image;
	Texture texture;
	Sprite sprite;
	//'''''''''''''''''''''''''''''''''''''''''''''//
	ship(float X, float Y, float W, float H){
		lives = 5;
		score = 0;
		speed = 0;
		dir = 0;
		w = W; h = H;
		image.loadFromFile("pic/spc_inv_tileset.png");
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		x = X; y = Y;
		sprite.setTextureRect(IntRect(0, 22, w, h));//������ �������� - ���������� �� ����, ������ - �� ������ (� �������� ��������������)
	}
	//'''''''''''''''''''''''''''''''''''''''''''''//
	void fire(bullet& bull){
		num_bullet++;
		bull.add(x+w/2-2, y-6, 1,num_bullet);
	};
	//'''''''''''''''''''''''''''''''''''''''''''''//
	void direction(int d_dir){
		switch (d_dir)
		{
			case 1: dir = 1;  break;
			case 2: dir = 2;  break;
		};
		speed = 0.1;
	}
	//'''''''''''''''''''''''''''''''''''''''''''''//
	void update(float time){//����� �����������

		switch (dir)//������� �� ��������� - ��������� ����
		{
			case 0: dx = 0; break;
			case 1: dx = -speed; break;//����
			case 2: dx = speed; break;//�����
		};

		x += dx*time;

		if (x < 2) x = 2; else if (x > 398-h) x = 398-h; //������������ ����
		
		speed = 0;//��������� ����� ��������

		sprite.setPosition(x, y);
	}
	//'''''''''''''''''''''''''''''''''''''''''''''//
};
//#############################################//
class invader{
public:
	int dir;//�����������
	//''// ��� ��� ������� � ������������
	float x, y,
		w, h,
		dx, dy,
		speed;
	//''// ��� ��� ������� � ��������
	Image image;
	Texture texture;
	Sprite sprite;
	//'''''''''''''''''''''''''''''''''''''''''''''//
	invader(){
		image.loadFromFile("pic/spc_inv_tileset.png");
		texture.loadFromImage(image);
		sprite.setTexture(texture);
	}
	invader(float X, float Y, float W, float H){
		speed = 0.03;
		dir = 2;
		w = W; h = H;
		image.loadFromFile("pic/spc_inv_tileset.png");
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		x = X; y = Y;
		sprite.setTextureRect(IntRect(0,0, w, h));//������ �������� - ���������� �� ����, ������ - �� ������ (� �������� ��������������)
	}
	//'''''''''''''''''''''''''''''''''''''''''''''//
	void direction(int d_dir){
		switch (d_dir)
		{
		case 1: dir = 1; y += 8; break;
		case 2: dir = 2; y += 8; break;
		};
	}
	//'''''''''''''''''''''''''''''''''''''''''''''//
	void update(float time){//����� �����������

		switch (dir)//������� �� ��������� - ��������� ����
		{
		case 0: dx = 0; break;
		case 1: dx = -speed; break;//����
		case 2: dx = speed; break;//�����
		};

		x += dx*time;

		if (x < 3) direction(2); else if (x > 397-h) direction(1); //������������ ����

		sprite.setPosition(x, y);
	}
	//'''''''''''''''''''''''''''''''''''''''''''''//
};
/*
class snd{
public:
	String File;
	SoundBuffer Buffer;//�� ���������
	Sound snd_s;
	//'''''''''''''''''''''''''''''''''''''''''''''//
	snd(String F){
		File = F;
		Buffer.loadFromFile("sound/" + File);
		snd_s.setBuffer(Buffer);
	}
	//'''''''''''''''''''''''''''''''''''''''''''''//
	void play(){//��������������� �����
		snd_s.play();
	}
	void stop(){//��������� �����
		snd_s.stop();
	}

};
*/

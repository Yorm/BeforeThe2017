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
		if (first != NULL) //Если список не пуст
		{
			newcell->prev = last; 
			last->next = newcell; 
			last = newcell; 
		}
		else //Если список пустой
		{
		/*	newcell->prev = Tail; //Указываем, что предыдущим элементом списка относительно добавленного, будет последний элемент существующего списка
			Tail->next = newcell; //Следующий за последним существующим это непосредственно сейчас добавляемый элемент списка
			Tail = newcell;       //После того как указали что есть настоящий и что предыдущий, объявляем, что последний существующий это только что добавленный элемент
		*/
			newcell->prev = NULL; 
			first = last = newcell; 
		}

		_count++;
		cout << _count<<endl;
	}

	void del(int num){//удаление элемента
		//Если удаляем первый элемент, то могут быть такие варианты
		//В списке есть только первый, в списке есть несколько элементов
		//Поэтому разбиваем логику выполнения
		if (first == NULL) return;
		if ((num == 1) && (first->next)){ //Если удаляем первый, но есть и другие, то
			cell *current = first;	//Указываем, что нам нужно начало списка
			first = first->next;	//Сдвигаем начало на следующий за началом элемент
			first->prev = NULL;	//Делаем так, чтоб предыдущий началу элемент был пустым
			delete current;		//Удаляем удаляемое начало
			_count--;		//Обязательно уменьшаем счетчик
			cout << "удалям первый есть другеи" << _count<<endl;
			return;		//И выходим из функции
			
		}
		else if ((num == 1) && (first == last)){ //Если удаляем первый, но в списке только 1 элемент

			first->next = NULL;	//обнуляем все что нужно
			first = NULL;
			delete first;		//Удаляем указатель на начало
			_count = 0;		//Обязательно обозначаем, что в списке ноль элементов
			return;			//и выходим из функции

		}

		//Также может быть, что удаляемый элемент является последним элементом списка
		if (num == _count){
			cell *current = last;	//Указываем, что нам нужен хвост
			last = last->prev;	//Отодвигаем хвост немного назад
			last->next = NULL;	//Обозначаем, что впереди за хвостом пусто
			delete current;	//Очищаем память от бывшего хвоста
			_count--;		//Обязательно уменьшаем счетчик элементов
			return;		//И выходим из функции
		}

		//Если же удаляемый элемент лежит где-то в середине списка, то тогда его можно удалить

		cell *current = first,
			*current2; //temp-Удаляемый элемент, temp2 нужен, чтобы не потерять данные

		//cout<<count_<<"\n";
		for (int i = 0; i<num - 1; i++) current = current->next;  //Идем к адресу удаляемого элемента

		current2 = current;	//Временно запоминаем адрес удаляемого элемента
		current2->prev->next = current->next;	//Записываем данные, что следующий за перед сейчас удаляемым элементом - это следующий от удаляемого
		current2->next->prev = current->prev; //а предыдущий для следующего - это предыдущий для удаляемого
		delete current; //теперь смело можно освободить память, удалив адрес на начало удаляемого элемента
		_count--; //Обязательно уменьшаем число элементов в списке.
	}

	void update(float time, RenderWindow& win)
	{
		if (first == NULL) return;
		cell* current = first;
		while (current){
			switch (current->dir)//смотрим на состояние - назначаем путь
			{
			case 1: current->y += -speed*time; break;//вверх
			case 2: current->y += speed*time; break;//вниз
			};

			collision(&current->y);

			sprite.setPosition(current->x, current->y);
			current = current->next;
			
			win.draw(sprite);// ахуеть я ебучий маг блять, просто пиздец
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
	int dir,//направление
		score;  //очки
	//''// все что связано с перемещением
	float x, y,
		w, h,
		dx, dy,
		speed;
	//''// все что связано с графикой
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
		sprite.setTextureRect(IntRect(0, 22, w, h));//первый параметр - координата по иксу, второй - по игрику (в тайлсете соответственно)
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
	void update(float time){//метод перемещения

		switch (dir)//смотрим на состояние - назначаем путь
		{
			case 0: dx = 0; break;
			case 1: dx = -speed; break;//лево
			case 2: dx = speed; break;//право
		};

		x += dx*time;

		if (x < 2) x = 2; else if (x > 398-h) x = 398-h; //ограничитель поля
		
		speed = 0;//остановка после действия

		sprite.setPosition(x, y);
	}
	//'''''''''''''''''''''''''''''''''''''''''''''//
};
//#############################################//
class invader{
public:
	int dir;//направление
	//''// все что связано с перемещением
	float x, y,
		w, h,
		dx, dy,
		speed;
	//''// все что связано с графикой
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
		sprite.setTextureRect(IntRect(0,0, w, h));//первый параметр - координата по иксу, второй - по игрику (в тайлсете соответственно)
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
	void update(float time){//метод перемещения

		switch (dir)//смотрим на состояние - назначаем путь
		{
		case 0: dx = 0; break;
		case 1: dx = -speed; break;//лево
		case 2: dx = speed; break;//право
		};

		x += dx*time;

		if (x < 3) direction(2); else if (x > 397-h) direction(1); //ограничитель поля

		sprite.setPosition(x, y);
	}
	//'''''''''''''''''''''''''''''''''''''''''''''//
};
/*
class snd{
public:
	String File;
	SoundBuffer Buffer;//не определен
	Sound snd_s;
	//'''''''''''''''''''''''''''''''''''''''''''''//
	snd(String F){
		File = F;
		Buffer.loadFromFile("sound/" + File);
		snd_s.setBuffer(Buffer);
	}
	//'''''''''''''''''''''''''''''''''''''''''''''//
	void play(){//воспроизведение звука
		snd_s.play();
	}
	void stop(){//остановка звука
		snd_s.stop();
	}

};
*/

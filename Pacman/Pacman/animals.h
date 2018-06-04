#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
using namespace sf;
using namespace std;

//#############################################//
class button{
public:
	String File;
	Image image;
	Texture texture;
	Sprite sprite;
	int x, y;
	//'''''''''''''''''''''''''''''''''''''''''''''//
	button(String F, int X, int Y){
		x = X; y = Y;
		File = F;
		image.loadFromFile("pic/button/" + File);
		texture.loadFromImage(image);
		sprite.setTexture(texture);
	}
	//'''''''''''''''''''''''''''''''''''''''''''''//
	void draw(){//отрисовка
		sprite.setPosition(x, y);
	}
	//'''''''''''''''''''''''''''''''''''''''''''''//
	void anim(String a_file){//смена изображения
		image.loadFromFile("pic/button/" + a_file);
		texture.loadFromImage(image);
		sprite.setTexture(texture);
	}
};
//#############################################//
class game_map{
public:
	String File;
	Image image;
	Texture texture;
	Sprite sprite;
	//'''''''''''''''''''''''''''''''''''''''''''''//
	game_map(String F){
		File = F;
		image.loadFromFile("pic/" + File);
		texture.loadFromImage(image);
		sprite.setTexture(texture);
	}
};
//#############################################//
class snd{
public:
	String File;
	SoundBuffer Buffer;
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
	/*
	Pacman_Dies.wav
	Pacman_Eating_Cherry.wav
	Pacman_Eating_Ghost.wav
	Pacman_Extra_Live.wav
	Pacman_Intermission.wav
	Pacman_Opening_Song.wav
	Pacman_Siren.wav
	Pacman_Waka_Waka.wav
	*/
};
//#############################################//
class pacman{	
public:
	int lives=3;
	int dir = 0,//направление
		score;  //очки
	//''// все что связано с перемещением
	float x, y, 
		  w, h, 
		  dx, dy,
		  speed = 0; 
	//''// все что связано с графикой
	String File; 
	Image image;
	Texture texture;
	Sprite sprite;
	//'''''''''''''''''''''''''''''''''''''''''''''//
	pacman(String F, float X, float Y, float W, float H){ 
		 lives=3;
		score = 0;
		File = F;
		w = W; h = H;
		image.loadFromFile("pic/" + File);
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		x = X; y = Y;
		sprite.setTextureRect(IntRect(128, 0, w, h)); 
	}
	//'''''''''''''''''''''''''''''''''''''''''''''//
	void path(int P){//метод-распределитель анимации/направления
		switch (P)
		{
		case 0: dir = 3;  break;
		case 1: dir = 1;   break;
		case 2: dir = 2;   break;
		case 3: dir = 0;   break;
		}
		speed = 0.1;
	}
	//'''''''''''''''''''''''''''''''''''''''''''''//
	void update(float time){//метод перемещения(определение точного положения в пространстве-перемещение-коллизии
		
		if ((static_cast<int>(y) % 32 == 0) && (static_cast<int>(x) % 32 == 0)){
			int xx = x / 32, yy = y / 32;
			if (logic_map[yy][xx] == 2){
				switch (dir)
				{
				case 0:  dx = speed; dy = 0; sprite.setTextureRect(IntRect(128, 0, 32, 32)); break;
				case 1: dx = -speed; dy = 0; sprite.setTextureRect(IntRect(128, 64, 32, 32)); break;
				case 2: dx = 0; dy = speed; sprite.setTextureRect(IntRect(128, 96, 32, 32)); break;
				case 3: dx = 0; dy = -speed; sprite.setTextureRect(IntRect(128, 32, 32, 32)); break;
				};
			}
			if (tile_map[yy][xx] == '.') {
				score++;
				tile_map[yy][xx] = ',';
			}			 
		}
		if (x < 1) x = 638;			
		if (x > 639) x = 2;
		

		x += dx*time;
		y += dy*time;
		
		speed = 0;

		sprite.setPosition(x, y); 
		collision();
	}	
	//'''''''''''''''''''''''''''''''''''''''''''''//
	void collision(){//метод столкновений

		for (int i = y / 32; i < (y + h) / 32; i++)
			for (int j = x / 32; j<(x + w) / 32; j++)
			{
			if (tile_map[i][j] != ' ' && tile_map[i][j] != '.' &&tile_map[i][j] != ','&& tile_map[i][j] != '2'&& tile_map[i][j] != '3')
				{
				if (dy>0){y = i * 32 - h;}//вниз
				if (dy<0){y = i * 32 + 31;}// вверх
				if (dx>0){x = j * 32 - w;}// вправо
				if (dx<0){x = j * 32 + 31;}//влево
				}
			}
	}
};
//#############################################//
class ghosts{
public:
	int dir = 0,
		stat;
	int logic_enemy[21][21];
	float x, y,
		ghost,
		dx, dy,
		speed = 0;
	//'''''''''''''''''''''''''''''''''''''''''''''//
	int xdot=0, ydot=0;
	int xdot2=0, ydot2=0;
	//'''''''''''''''''''''''''''''''''''''''''''''//
	bool bldot = false;
	//'''''''''''''''''''''''''''''''''''''''''''''//
	String File;
	Image image;
	Texture texture;
	Sprite sprite;
	//'''''''''''''''''''''''''''''''''''''''''''''//
	ghosts(String F, float X, float Y, int G){
		stat = 0;
		File = F;
		ghost = G;
		image.loadFromFile("pic/" + File);
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		x = X; y = Y;
		dir = 0;
		sprite.setTextureRect(IntRect(ghost*32, 0, 32, 32));
	}
	//'''''''''''''''''''''''''''''''''''''''''''''//
	void blinky_dot(int _y, int _x){// метод блинки
		_x = floor(_x + 0.5);
		_y = floor(_y + 0.5);
		int xx = static_cast<int>(_x) / 32, yy = static_cast<int>(_y) / 32;
		logic_enemy[yy][xx] = 0;

		if (stat == 1)
			logic_enemy[19][19] = 0;
	}
	//'''''''''''''''''''''''''''''''''''''''''''''//
	void pinky_dot(int pdir, int _y, int _x){//метод пинки
		int dot = 0;
		_x = floor(_x + 0.5);
		_y = floor(_y + 0.5);
		int xx = static_cast<int>(_x) / 32, yy = static_cast<int>(_y) / 32;

		switch (pdir)
		{
		case 3:
		{
			for (int q = yy; q < yy + 5; q++)
				if (logic_map[q][xx] == 0 || logic_map[q][xx] == 2 || logic_map[q][xx] == 2) dot++; else { dot -= 1; break; }
			dot -= 1;
			logic_enemy[yy + dot][xx] = 0;
		}break;
		case 2:
		{
			for (int q = yy; q > yy - 5; q--)
				if (logic_map[q][xx] == 0 || logic_map[q][xx] == 2 || logic_map[q][xx] == 2) dot--; else { dot += 1; break; }
			dot += 1;
			logic_enemy[yy + dot][xx] = 0;
		}break;
		case 1:
		{
			for (int q = xx; q <xx + 5; q++)
				if (logic_map[yy][q] == 0 || logic_map[yy][q] == 2 || logic_map[yy][q] == 3) dot++; else { dot -= 1; break; }
			dot -= 1;
			logic_enemy[yy][xx + dot] = 0;
		}break;
		case 0:{
			for (int q = xx; q > xx - 5; q--)
				if (logic_map[yy][q] == 0 || logic_map[yy][q] == 2 || logic_map[yy][q] == 3) dot--; else { dot += 1; break; }
			dot += 1;
			logic_enemy[yy][xx + dot] = 0;
		}break;
		};
		if (stat == 1)
			logic_enemy[3][19] = 0;
	}
	//'''''''''''''''''''''''''''''''''''''''''''''//
	void inky_dot(int pdir, int _y, int _x){//метод инки
		int dot = 0;
		_x = floor(_x + 0.5);
		_y = floor(_y + 0.5);
		int xx = static_cast<int>(_x) / 32, yy = static_cast<int>(_y) / 32;

			switch (pdir)
			{
			case 2:
			{
				for (int q = yy; q < yy + 5; q++)
					if (logic_map[q][xx] == 0 || logic_map[q][xx] == 2 || logic_map[q][xx] == 3) dot++; else { dot -= 1; break; }
				dot -= 1;
				logic_enemy[yy + dot][xx] = 0;
			}break;
			case 3:
			{
				for (int q = yy; q > yy - 5; q--)
					if (logic_map[q][xx] == 0 || logic_map[q][xx] == 2 || logic_map[q][xx] == 3) dot--; else { dot += 1; break; }
				dot += 1;
				logic_enemy[yy + dot][xx] = 0;
			}break;
			case 0:
			{
				for (int q = xx; q <xx + 5; q++)
					if (logic_map[yy][q] == 0 || logic_map[yy][q] == 2 || logic_map[yy][q] == 3) dot++; else { dot -= 1; break; }
				dot -= 1;
				logic_enemy[yy][xx + dot] = 0;
			}break;
			case 1:{
				for (int q = xx; q > xx - 5; q--)
					if (logic_map[yy][q] == 0 || logic_map[yy][q] == 2 || logic_map[yy][q] == 3) dot--; else { dot += 1; break; }
				dot += 1;
				logic_enemy[yy][xx + dot] = 0;
			}break;
			};

			if (stat == 1)
				logic_enemy[3][3] = 0;
	}
	
	//'''''''''''''''''''''''''''''''''''''''''''''//
	void klyde_dot(int _y, int _x, int _xg, int _yg){//метод клайда
			_x = floor(_x + 0.5);
			_y = floor(_y + 0.5);
			bool YN;
			int xx = static_cast<int>(_x) / 32, yy = static_cast<int>(_y) / 32;
			int xg = static_cast<int>(_xg) / 32, yg = static_cast<int>(_yg) / 32;

			_xg = floor(_xg + 0.5);
			_yg = floor(_yg + 0.5);

			for (int i = xg - 5; i < xg + 5; i++){
				for (int j = yg - 5; j < yg + 5; j++){
					if (i == xx && j == yy){YN = true;break;}
					else YN = false;
				}
				if (YN) break;
			}
		if (YN){logic_enemy[yy][xx] = 0;}
		else logic_enemy[3][19] = 0;

		if (stat == 1)
			logic_enemy[19][3] = 0;
		
	}
	//'''''''''''''''''''''''''''''''''''''''''''''//
	void surface(float _y, float _x){//заполенение массива видимости
		for (int i = 0; i < 21; i++)
			for (int b = 0; b < 21; b++){
				if (logic_map[i][b] == 0 || logic_map[i][b] == 2)	logic_enemy[i][b] = 50;
				if (logic_map[i][b] == 1)	logic_enemy[i][b] = 51;
			}
		_x = floor(_x + 0.5);
		_y = floor(_y + 0.5);
		int xx = static_cast<int>(_x) / 32, yy = static_cast<int>(_y) / 32;

		if (logic_enemy[yy][xx] != 51)
				logic_enemy[yy][xx] = 49;
	}
	//'''''''''''''''''''''''''''''''''''''''''''''//
	void update(float time){//поиск пути
		int ni, nk;		
		int min;
		_Bool f;
		if (!bldot){
			xdot = 0; ydot = 0;
			xdot2 = 0; ydot2 = 0;
			f = false;
			ni = 0;
			nk = 50;//ограничение зоны видимости
			while (ni < nk){//пока номер кольца волны меньше границы зоны видимости
				for (int i = 0; i < 21; i++){
					for (int b = 0; b < 21; b++){
						if (logic_enemy[i][b] == ni){
							if (logic_enemy[i + 1][b] == 49 || logic_enemy[i][b + 1] == 49 || logic_enemy[i - 1][b] == 49 || logic_enemy[i][b - 1] == 49){

								xdot = x/ 32; ydot =  y/ 32;
								min = 51;
								
								if (logic_enemy[ydot][xdot + 1] < min){
									min = logic_enemy[ydot][xdot + 1];
									ydot2 = ydot;
									xdot2 = xdot + 1;
									dir = 1;//вправо

								}
								if (logic_enemy[ydot][xdot - 1] < min){
									min = logic_enemy[ydot][xdot - 1];
									ydot2 = ydot;
									xdot2 = xdot - 1;
									dir = 2;//влево

								}

								if (logic_enemy[ydot - 1][xdot] < min){
									min = logic_enemy[ydot - 1][xdot];
									ydot2 = ydot - 1;
									xdot2 = xdot;
									dir = 3;//вверх

								}

								if (logic_enemy[ydot + 1][xdot] < min){
									min = logic_enemy[ydot + 1][xdot];
									ydot2 = ydot + 1;
									xdot2 = xdot;
									dir = 4;//вниз
								}

								bldot = true;
								f = true;
								if (f) break;
							}
							if (logic_enemy[i + 1][b] == 50){ logic_enemy[i + 1][b] = ni + 1; }//построение волны
							if (logic_enemy[i - 1][b] == 50){ logic_enemy[i - 1][b] = ni + 1; }//
							if (logic_enemy[i][b + 1] == 50){ logic_enemy[i][b + 1] = ni + 1; }//
							if (logic_enemy[i][b - 1] == 50){ logic_enemy[i][b - 1] = ni + 1; }//
						}
						if (f) break;
					}
					if (f) break;
				}
				if (f) break;
				ni++;
			}
			f = false;

		}


		speed = 0.1;
		if (x > xdot2 * 32){
			dx = -speed;
		}
		else if (x < xdot2 * 32){
			dx = speed;
		}
		else { dx = 0; bldot = false; }
			
		if (y > ydot2 * 32){
			dy = -speed;
		}
		else if (y < ydot2 * 32){
			dy = speed;

		}
		else { dy = 0; bldot = false; }

		if (x==xdot2 * 32  || y == ydot2 * 32)
		bldot = false;		
		//'''''''''''''''''''''''''''''''''''''''''''''//
		x += dx*time;
		y += dy*time;
		//'''''''''''''''''''''''''''''''''''''''''''''//
		switch (dir){		
		case 1:sprite.setTextureRect(IntRect(ghost*32, 0, 32, 32)); break;
		case 2:sprite.setTextureRect(IntRect(ghost * 32, 64, 32, 32)); break;
		case 3:sprite.setTextureRect(IntRect(ghost * 32, 32, 32, 32)); break;
		case 4: sprite.setTextureRect(IntRect(ghost * 32, 96, 32, 32)); break;
		}

		sprite.setPosition(x, y);
	}
};


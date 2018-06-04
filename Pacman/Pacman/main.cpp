#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <Windows.h>
#include "map.h"
#include "animals.h"
#include <cmath>

using namespace sf;
using namespace std;

int lvl;

void refresh();

int main()
{	
	lvl = 1;

	system("mode con cols=50 lines=20");
	SetConsoleTitle(TEXT("Pacman"));
	cout << "1.Start\n2.Exit\n";
	//'''''''''''''''''''''''''''''''''''''''''''''//
	pacman pac("pm.png", 64, 32, 31.0, 31.0);
	game_map map_1("map_t.png");
	//'''''''''''''''''''''''''''''''''''''''''''''//
	snd lvlup("Pacman_Eating_Ghost.wav");
	snd intro("Pacman_Intermission.wav");
	snd opening("Pacman_Opening_Song.wav");
	snd die("Pacman_Dies.wav");
	//'''''''''''''''''''''''''''''''''''''''''''''//
	ghosts blinky("pm.png", 320, 256,0);
	ghosts inky("pm.png", 352, 288, 1);
	ghosts pinky("pm.png", 320, 288, 2);
	ghosts klyde("pm.png", 288, 288, 3);
	blinky.sprite.setPosition(blinky.x, blinky.y);
	inky.sprite.setPosition(inky.x, inky.y);
	pinky.sprite.setPosition(pinky.x, pinky.y);
	klyde.sprite.setPosition(klyde.x, klyde.y);
	//'''''''''''''''''''''''''''''''''''''''''''''//
	Font font;
	font.loadFromFile("minecraft_font.ttf");
	Text text("", font, 20);
	//'''''''''''''''''''''''''''''''''''''''''''''//
	RenderWindow window(VideoMode(672, 700), "Pacman");//672
	//'''''''''''''''''''''''''''''''''''''''''''''//
	Clock clock;
	float C_frame = 0;
	int timerr = 0;
	//'''''''''''''''''''''''''''''''''''''''''''''//
	button back("back.png",  0, 0);
	button gameb("game.png",  184, 263);
	button contb("cont.png",  184, 263);
	button exitb("exit.png",  184, 420);
	button leg("b.png", 0, 0);
	leg.draw();
	contb.draw();
	back.draw();
	gameb.draw();
	exitb.draw();
	//'''''''''''''''''''''''''''''''''''''''''''''//
	int gam = 0;
	int statTimer = 0;
	//'''''''''''''''''''''''''''''''''''''''''''''//
	while (window.isOpen())
	{
		//'''''''''''''''''''''''''''''''''''''''''''''//
		Vector2i curs = Mouse::getPosition(window);
		Vector2f cr = window.mapPixelToCoords(curs);
		//'''''''''''''''''''''''''''''''''''''''''''''//
		Event event;
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 1200;
		//'''''''''''''''''''''''''''''''''''''''''''''//
		while (window.pollEvent(event))
		{
			//'''''''''''''''''''''''''''''''''''''''''''''//
			if (gameb.sprite.getGlobalBounds().contains(cr.x, cr.y)) gameb.anim("game2.png");
			else gameb.anim("game.png");

			if (exitb.sprite.getGlobalBounds().contains(cr.x, cr.y)) exitb.anim("exit2.png");
			else exitb.anim("exit.png");

			if (contb.sprite.getGlobalBounds().contains(cr.x, cr.y)) contb.anim("cont2.png");
			else contb.anim("cont.png");
			//'''''''''''''''''''''''''''''''''''''''''''''//
			if (event.type == Event::MouseButtonPressed)
				if (event.key.code == Mouse::Left){
					if (gameb.sprite.getGlobalBounds().contains(cr.x, cr.y)){
						gam = 1;
						//opening.play();
					}
					if (exitb.sprite.getGlobalBounds().contains(cr.x, cr.y))
						exit(1);
				}
			//'''''''''''''''''''''''''''''''''''''''''''''//
			if (event.type == Event::Closed)
				window.close();
		}
		//'''''''''''''''''''''''''''''''''''''''''''''//
		if (gam == 1){
			//'''''''''''''''''''''''''''''''''''''''''''''//
			if (Keyboard::isKeyPressed(Keyboard::W)) { pac.path(0); }
			if (Keyboard::isKeyPressed(Keyboard::A)) { pac.path(1); }
			if (Keyboard::isKeyPressed(Keyboard::S)) { pac.path(2); }
			if (Keyboard::isKeyPressed(Keyboard::D)) { pac.path(3); }
			if (Keyboard::isKeyPressed(Keyboard::Escape)) { gam = 2; opening.stop(); }
			if (Keyboard::isKeyPressed(Keyboard::B)) { refresh(); }
			//'''''''''''''''''''''''''''''''''''''''''''''//
			int xxx = pac.x / 32, yyy = pac.y / 32;
			
			if (tile_map[yyy][xxx] == '2') {
				pac.score += 1;
				tile_map[yyy][xxx] = '3';
				blinky.stat = 1;
				inky.stat = 1;
				klyde.stat = 1;
				pinky.stat = 1;
			}
			//'''''''''''''''''''''''''''''''''''''''''''''//
			if (blinky.stat == 1){
				statTimer += time;//наращиваем таймер
				if (statTimer > 2000){
					blinky.stat = 0;
					inky.stat = 0;
					klyde.stat = 0;
					pinky.stat = 0;
					statTimer = 0;
				}
			}
			//'''''''''''''''''''''''''''''''''''''''''''''//
			if (lvl*151==pac.score){
				refresh();
				cout << lvl << "=lvl" << endl;
				lvlup.play();
				lvl++;
			}
			//'''''''''''''''''''''''''''''''''''''''''''''//
			if (((xxx / 32 == blinky.xdot2) && (yyy / 32 == blinky.ydot2))
				|| ((xxx / 32 == inky.xdot2) && (yyy / 32 == inky.ydot2))
				|| ((xxx / 32 == pinky.xdot2) && (yyy / 32 == pinky.ydot2))
				|| ((xxx == klyde.xdot2)) && (yyy == klyde.ydot2))
			{
				pac.x = 64; pac.y = 32;
				pac.lives--;				
			}
			//'''''''''''''''''''''''''''''''''''''''''''''//
			if (pac.lives == 0){
				refresh();
				gam = 0;
				//'''''''''''''''''''''''''''''''''''''''''''''//
				{
					pac.x = 64; pac.y = 32;
					pac.dir = 0;
					pac.lives = 3;
					pac.score = 0;
					pac.speed = 0;
				}
				//'''''''''''''''''''''''''''''''''''''''''''''//
				{blinky.x = 320; blinky.y = 256; blinky.speed = 0; blinky.dir = 0; blinky.xdot2 = 10; blinky.ydot2 = 8; blinky.stat = 0; }
				{inky.x = 352; inky.y = 288; inky.speed = 0; inky.dir = 0; inky.xdot2 = 11; inky.ydot2 = 9; inky.stat = 0; }
				{pinky.x = 320; pinky.y = 288; pinky.speed = 0; pinky.dir = 0; pinky.xdot2 = 10; pinky.ydot2 = 9; pinky.stat = 0; }
				{klyde.x = 288; klyde.y = 288; klyde.speed = 0; klyde.dir = 0; klyde.xdot2 = 9; klyde.ydot2 = 9; klyde.stat = 0; }

				blinky.sprite.setPosition(blinky.x, blinky.y);
				inky.sprite.setPosition(inky.x, inky.y);
				pinky.sprite.setPosition(pinky.x, pinky.y);
				klyde.sprite.setPosition(klyde.x, klyde.y);
			}

			//'''''''''''''''''''''''''''''''''''''''''''''//
			pac.update(time);

			
			blinky.surface(blinky.y, blinky.x);
			blinky.blinky_dot(pac.y, pac.x);
			blinky.update(time);

			klyde.surface(klyde.y, klyde.x);
			klyde.klyde_dot(pac.y, pac.x, klyde.x, klyde.y);
			klyde.update(time);
				
			if (pac.score > 100){
				inky.surface(inky.y, inky.x);
				inky.inky_dot(pac.dir,pac.y, pac.x);
				inky.update(time);
				
				pinky.surface(inky.y, inky.x);
				pinky.pinky_dot(pac.dir, pac.y, pac.x);
				pinky.update(time);
			}
			//'''''''''''''''''''''''''''''''''''''''''''''//
			window.clear();
			//'''''''''''''''''''''''''''''''''''''''''''''//
			for (int i = 0; i < map_const; i++)
				for (int j = 0; j < map_const; j++)
				{
				if (tile_map[i][j] == '#')  map_1.sprite.setTextureRect(IntRect(32, 0, 32, 32));
				if ((tile_map[i][j] == '.')) map_1.sprite.setTextureRect(IntRect(64, 96, 32, 32));
				if ((tile_map[i][j] == ' ') ) map_1.sprite.setTextureRect(IntRect(96, 96, 32, 32));
				if ((tile_map[i][j] == '3')) map_1.sprite.setTextureRect(IntRect(96, 96, 32, 32));
				if ((tile_map[i][j] == ',')) map_1.sprite.setTextureRect(IntRect(96, 96, 32, 32));
				if (tile_map[i][j] == '|')  map_1.sprite.setTextureRect(IntRect(0, 96, 32, 32));
				if ((tile_map[i][j] == '-')) map_1.sprite.setTextureRect(IntRect(32, 96, 32, 32));

				if (tile_map[i][j] == '<')  map_1.sprite.setTextureRect(IntRect(0, 64, 32, 32));
				if ((tile_map[i][j] == '>')) map_1.sprite.setTextureRect(IntRect(64, 64, 32, 32));
				if (tile_map[i][j] == '^')  map_1.sprite.setTextureRect(IntRect(96, 64, 32, 32));
				if ((tile_map[i][j] == 'v')) map_1.sprite.setTextureRect(IntRect(32, 64, 32, 32));

				if (tile_map[i][j] == '[')  map_1.sprite.setTextureRect(IntRect(64, 32, 32, 32));
				if ((tile_map[i][j] == ']')) map_1.sprite.setTextureRect(IntRect(96, 32, 32, 32));
				if (tile_map[i][j] == '\\')  map_1.sprite.setTextureRect(IntRect(32, 32, 32, 32));
				if ((tile_map[i][j] == '/')) map_1.sprite.setTextureRect(IntRect(0, 32, 32, 32));

				if (tile_map[i][j] == '{')  map_1.sprite.setTextureRect(IntRect(96, 0, 32, 32));
				if ((tile_map[i][j] == '}')) map_1.sprite.setTextureRect(IntRect(64, 0, 32, 32));
				if ((tile_map[i][j] == '@')) map_1.sprite.setTextureRect(IntRect(0, 0, 32, 32));
				if ((tile_map[i][j] == '2')) map_1.sprite.setTextureRect(IntRect(0, 128, 32, 32));
				
				
				map_1.sprite.setPosition(j * 32, i * 32);
				window.draw(map_1.sprite);
			}
			//'''''''''''''''''''''''''''''''''''''''''''''//
			window.draw(leg.sprite);
			ostringstream score_s, lives_s, lvl_s;    
			score_s << pac.score;
			lives_s << pac.lives;
			lvl_s << lvl;
			text.setString("          " + lives_s.str() + "                                " + "LVL: " + lvl_s.str() + "                                  " + "SCORE: " + score_s.str());
			text.setPosition(20, 675);
			//'''''''''''''''''''''''''''''''''''''''''''''//			
			window.draw(pac.sprite);
			window.draw(blinky.sprite);
			window.draw(inky.sprite);
			window.draw(pinky.sprite);
			window.draw(klyde.sprite);
			window.draw(leg.sprite);
			window.draw(text);			
		}
		//'''''''''''''''''''''''''''''''''''''''''''''//
		if (gam == 0 || gam == 2){
			window.draw(back.sprite);

			if (gam == 0)
				window.draw(gameb.sprite);
			else
				window.draw(contb.sprite);

			window.draw(exitb.sprite);
		}
		//'''''''''''''''''''''''''''''''''''''''''''''//
		window.display();
	}
	return 0;
}
//'''''''''''''''''''''''''''''''''''''''''''''//
void refresh(){
	for (int i = 0; i < map_const; i++)
		for (int j = 0; j < map_const; j++)
		{
		if (tile_map[i][j] == ',')
			tile_map[i][j] = '.';
		if (tile_map[i][j] == '3')
			tile_map[i][j] = '2';
		}
}
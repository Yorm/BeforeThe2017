#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
//#include <sstream>
#include <Windows.h>
//#include <cmath>
#include "interface.h"

using namespace sf;
using namespace std;

//#############################################//
int main()
{
	system("mode con cols=50 lines=20");
	SetConsoleTitle(TEXT("cons_si"));
	RenderWindow window(VideoMode(400, 324), "Space invaders");

	Pic background("background1.png");


	ship defender(188,258,24,24);//положение на экране и размер тайла
	invader second_lvl(72, 33, 16, 16);
	//invader second_lvql[2];
	//
	bullet bull_def(3, 12);
	
	//bull_def.sprite.setPosition(b.first->x, b.first->y);
	//

	defender.sprite.setPosition(defender.x, defender.y);
	second_lvl.sprite.setPosition(second_lvl.x, second_lvl.y);



	Clock clock;
	float C_frame = 0;
	bool space_button = false;
	float time_fire1 = 0, time_fire2=0;
	while (window.isOpen())
	{
		Event event;

		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 1200;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::A)) { defender.direction(1); } //незащищено, переместить в функцию
		if (Keyboard::isKeyPressed(Keyboard::D)) { defender.direction(2); }
		if (Keyboard::isKeyPressed(Keyboard::Q)) { bull_def.del(1); }
		
		//ОПТИМИЗИРОВАТЬ МБ А?
			//sf::Event::KeyPressed // Если клавиша нажата
		//	sf::Event::KeyReleased // Если клавиша отжата

		// ПУЛЮ В КЛАСС ИГРОКА
		if (!space_button)
		if (Keyboard::isKeyPressed(Keyboard::Space)) {/* bull_def.add(198, 255, 1);*/ defender.fire(bull_def); time_fire1 = time; space_button = true; }// СЛИП ПОД ВОПРОСОМ
		if (space_button){
			time_fire2 += time;
			if (time_fire1 + 250 < time_fire2){
				space_button = false;
				time_fire2 = time_fire1 = 0;
			}

		}

		defender.update(time);
		second_lvl.update(time);
		
		//cout << defender.x<<endl;

		window.clear();
		window.draw(background.sprite);
		window.draw(defender.sprite);
		window.draw(second_lvl.sprite);
		
		/*cell* current = bull_def.first;
		while (current){
			switch (current->dir)//смотрим на состояние - назначаем путь
			{
			case 1: current->y += -bull_def.speed*time; break;//вверх
			case 2: current->y += bull_def.speed*time; break;//вниз
			};

			bull_def.sprite.setPosition(current->x, current->y);
			current = current->next;
			window.draw(bull_def.sprite);
		}*/
		bull_def.update(time, window);//ееептааа, разберись с этим
		
		window.display();
	}

	return 0;
}
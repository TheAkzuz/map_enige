#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include "map.h"
#include <iostream>
#include <Windows.h>
#include <vector>


using namespace std;
using namespace sf;

int def_x = 32;//значение по-умолчанию х и у для расположения текстур.
int def_y = 32;
string path_res = "resources/"; //папка для исходников
string log_info;
int mode_map = 0;

int map_num = 0;

int scrol_x = 1;// коррды для скролинга, а имено добавление
int scrol_y = 1;

int win_x = 1200; //window mode
int win_y = 600;

int win_mode = 0; // active type
string save_file;


int otris_map = 0;

string names_st_map[9][10];
string names_script_map[10];


class Texturs
{
public:
	Image image;
	Texture texture;
	Sprite sprite;
	string name;
	int x, y;
	
	Texturs(string way)
	{

		name = path_res+ way+".png";

		otris();
	}

	Texturs(int a, int b)
	{

	}


	void otris()
	{
		image.loadFromFile(name);
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		
	}

	void position(int xx, int yy)
	{
		x = xx;
		y = yy;
		sprite.setPosition(x, y);

	}


	

};






void crea_setka()
{
	for (int a = 0; a < 9; a++)
	{
		for (int i = 0; i < 32; i++)
		{

			map_vid[a][i] = string(32, '0');
			map_script[i] = string(32, '0');


		}
	}
}

void save_fun()
{
	ofstream save_fu(save_file+".txt");

	for (int a = 0; a < 9; a++)
	{
		for (int i = 0; i < 32; i++)
		{
			save_fu << map_vid[a][i] << endl;
		}

		for (int i = 0; i < 10; i++)
		{

			save_fu << names_st_map[a][i] << endl;
		}
	}


	for (int i = 0; i < 32; i++)
	{
		save_fu << map_script[i] << endl;
	}
	for (int i = 0; i < 10; i++)
	{

		save_fu << names_script_map[i] << endl;
	}
	save_fu.close();

}




void map_to_script()
{
	for (int i = 0; i < 32; i++)
	{
		for (int a = 0; a < 32; a++)
		{
			//if (map_vid[i][a] != map_script[i][a])
			//{
				//if (names_st_map[(int)map_vid[i][a]-48] == names_script_map[(int)map_script[i][a]-48])
			//	{
				//	cout << names_st_map[(int)map_vid[i][a] - 48] << endl;
				//	map_script[i][a] = map_vid[i][a];
			//	}
		//	}

		}
	}


}




void load_save()
{

	fstream load_file(save_file+".txt");

	for (int a = 0; a < 9; a++)
	{
		for (int i = 0; i < 32; i++)
		{
			load_file >> map_vid[a][i];
		}

		for (int i = 0; i < 10; i++)
		{

			load_file >> names_st_map[a][i];
		}
	}


	for (int i = 0; i < 32; i++)
	{
		load_file >> map_script[i];
	}
	for (int i = 0; i < 10; i++)
	{

		load_file >> names_script_map[i];
	}
	load_file.close();
}




void vibor_textur(string vibor_name_texture)
{
	if (win_mode >= 2 && win_mode<12)
	{
		if (mode_map == 0)
		{
			names_st_map[map_num][win_mode - 2] = path_res + vibor_name_texture + ".png";
		}
		if (mode_map == 1)
		{
			names_script_map[win_mode - 2] = path_res + vibor_name_texture + ".png";
		}
	}

}




////////////////////start prog

int main()
{

	setlocale(0, "Russian");
	sf::RenderWindow window(sf::VideoMode(win_x, win_y), "Massive map editor");
	window.setFramerateLimit(20);
	crea_setka();

	for (int a = 0; a < 9; a++)
	{
		for (int i = 0; i < 10; i++)
		{
			names_st_map[a][i] = path_res + "clear" + ".png";
			names_script_map[i] = path_res + "clear" + ".png";
		}
	}

	Vector2i mouse_pos = Mouse::getPosition(window);

	Font font;
	font.loadFromFile(path_res + "sansation.ttf");

	Text text;
	text.setFont(font);
	text.setFillColor(Color::Black);
	text.setCharacterSize(15);


	Texturs console_von("console_vid");
	console_von.position(win_x - 130, 0);

	Texturs save_von("red_tt");
	save_von.position(win_x - 130, 70);

	Texturs load_von("load");
	load_von.position(win_x - 130, 126);

	Texturs create_setka("create_setka");
	create_setka.position(win_x - 130, 170);

	Texturs st(2,1);

	Texturs save_f("save_file");
	save_f.position(win_x-130, 220 + 32 + (32 * 9));

	Texturs script_load("script_map");
	script_load.position(win_x - 130,save_f.y+26);


	//////////////////////////////// poka open window
	while (window.isOpen())
	{
		Vector2i mouse_pos = Mouse::getPosition(window);
		int mouse_x = mouse_pos.x;
		int mouse_y = mouse_pos.y;

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			else if (event.type == Event::TextEntered)
			{
				if (!Keyboard::isKeyPressed(Keyboard::BackSpace) && win_mode == 1)
				{
					save_file += static_cast<char>(event.text.unicode);
				}
				if (Keyboard::isKeyPressed(Keyboard::BackSpace) && win_mode == 1 && save_file.length() != 0)
				{
					save_file = save_file.replace(save_file.length() - 1, 1, "");
				}


			}

			if (event.type == Event::MouseButtonPressed && Mouse::isButtonPressed(Mouse::Left) && win_mode >= 2 && win_mode <= 11 && mouse_pos.x < 16 * 32 && mouse_pos.y < 16 * 32)
			{

				int mouse_x_c = 0;
				int mouse_y_c = 0;


				for (int i = mouse_pos.x; i >= 0; i = i - 32)
				{
					mouse_x_c++;
				}

				for (int i = mouse_pos.y; i >= 0; i = i - 32)
				{
					mouse_y_c++;
				}


				string simvol_map = to_string(win_mode - 2);
				if (mode_map ==0)
				{
				
				map_vid[map_num][mouse_x_c - 1 + (16 * (scrol_x - 1))][mouse_y_c - 1 + (16 * (scrol_y - 1))]        = simvol_map[0];
				}
				if (mode_map == 1)
				{

					map_script[mouse_x_c - 1 + (16 * (scrol_x - 1))][mouse_y_c - 1 + (16 * (scrol_y - 1))] = simvol_map[0];
				}
				//cout << mouse_x_c - 1 <<" "<< mouse_y_c - 1 << " "<< map_vid[mouse_x_c - 1][mouse_y_c - 1] << endl;

				//cout << mouse_y_c << " " << mouse_x_c << " " << mouse_pos.x << endl;
			}

			if (event.type == Event::KeyPressed)
			{
				if (Keyboard::isKeyPressed(Keyboard::Up) )
				{
					scrol_y = 1;
					cout << scrol_y << endl;
				}

				if (Keyboard::isKeyPressed(Keyboard::Down))
				{
					scrol_y = 2;
					cout << scrol_y << endl;
				}
				if (Keyboard::isKeyPressed(Keyboard::Left))
				{
					scrol_x = 1;
					cout << scrol_x << endl;
				}

				if (Keyboard::isKeyPressed(Keyboard::Right))
				{
					scrol_x = 2;
					cout << scrol_x << endl;
				}
			}




		}




		//active text path
		if (Mouse::isButtonPressed(Mouse::Left) && (mouse_x > save_von.x && mouse_x < save_von.x + 130) && (mouse_y > save_von.y && mouse_y < save_von.y + 46))
		{
			win_mode = 1;
			log_info = "console active";

		}
		else if (Mouse::isButtonPressed(Mouse::Left) && win_mode == 1)
		{
			win_mode = 0;
		}

		if (Mouse::isButtonPressed(Mouse::Left) && (mouse_x > load_von.x && mouse_x < load_von.x + 70) && (mouse_y > load_von.y && mouse_y < load_von.y + 25))
		{
			if (save_file != "")
			{
				load_save();
				log_info = "file load!";
			}

		}
		if (Mouse::isButtonPressed(Mouse::Left) && (mouse_x > create_setka.x && mouse_x < create_setka.x + 121) && (mouse_y > create_setka.y && mouse_y < create_setka.y + 34))
		{
			vibor_textur(save_file);
			log_info="texture load";
			
		}
		if (Mouse::isButtonPressed(Mouse::Left) && (mouse_x > win_x - 125 && mouse_x < save_f.x + 114) && (mouse_y > save_f.y && mouse_y < save_f.y+24))
		{
			if (save_file != "")
			{
				save_fun();
				log_info = "file save!";
			}

			cout << 132 << endl;
			Sleep(50);
		}


		if ((Mouse::isButtonPressed(Mouse::Left) && (mouse_x > script_load.x && mouse_x < script_load.x + 114) && (mouse_y > script_load.y && mouse_y < script_load.y + 24)) ||(win_mode !=1 && Keyboard::isKeyPressed(Keyboard::Space)))
		{
			cout << mode_map << endl;
			log_info = "Map smenila type";
			if (mode_map == 0)
			{
				mode_map = 1;

				map_to_script();
			}
			else
			{
				mode_map = 0;
				map_to_script();
			}
			Sleep(50);

		}
		if (win_mode != 1)
		{
			if (Keyboard::isKeyPressed(Keyboard::Num0))
			{
				map_num = 0;
				Sleep(20);
			}

			if (Keyboard::isKeyPressed(Keyboard::Num1))
			{
				map_num = 1;
				Sleep(20);
			}
			if (Keyboard::isKeyPressed(Keyboard::Num2))
			{
				map_num = 2;
				Sleep(20);
			}
			if (Keyboard::isKeyPressed(Keyboard::Num3))
			{
				map_num = 3;
				Sleep(20);
			}
			if (Keyboard::isKeyPressed(Keyboard::Num4))
			{
				map_num = 4;
				Sleep(20);
			}
			if (Keyboard::isKeyPressed(Keyboard::Num5))
			{
				map_num = 5;
				Sleep(20);
			}
			if (Keyboard::isKeyPressed(Keyboard::Num6))
			{
				map_num = 6;
				Sleep(20);
			}
			if (Keyboard::isKeyPressed(Keyboard::Num7))
			{
				map_num = 7;
				Sleep(20);
			}
			if (Keyboard::isKeyPressed(Keyboard::Num8))
			{
				map_num = 8;
				Sleep(20);
			}
		}

		

		/// <summary>
		/// //////////////////
		/// </summary>
		/// <returns></returns>



	//	cout << win_mode << endl;

		window.clear();

		
		window.draw(console_von.sprite);
		window.draw(save_von.sprite);
		window.draw(load_von.sprite);
		window.draw(create_setka.sprite);
		window.draw(save_f.sprite);
		window.draw(script_load.sprite);


		for (int i = 0; i < 10; i++)
		{
			if (mode_map == 0)
			{
				st.name = names_st_map[map_num][i];
			}
			if (mode_map == 1)
			{
				st.name = names_script_map[i];
			}
			st.otris();
			
			st.position(win_x - 125, 220 + (i * 32));

			text.setPosition(win_x - 90, 220 + (i * 32));
			text.setString(to_string(i));

			if (i == win_mode - 2)
			{
				text.setString(to_string(i) + " active");
			}

			window.draw(text);
			window.draw(st.sprite);
		}


		/// <summary>
		/// //////////////////////////////////vibiraem plitky iz bara
		/// </summary>
		/// <returns></returns>

		for (int i = 0; i < 12; i++)
		{
			if (Mouse::isButtonPressed(Mouse::Left) && (mouse_x > win_x - 125 && mouse_x < win_x - 125 + 64) && (mouse_y > 220 + (32 * i) && mouse_y < 220 + 32 + (32 * i)))
			{
				win_mode = i+2;
			}
		}

		//////// otrisovka map


		if (otris_map == 1)
		{

			for (int i = 0; i < map_y/2; i++)
			{
				for (int a = 0; a<map_x/2; a++)
				{		
					if (mode_map == 0)
					{
						st.name = names_st_map[map_num][(int)map_vid[map_num][i + (16 * (scrol_x - 1))][a + (16 * (scrol_y - 1))] - 48];
					}
					if (mode_map == 1)
					{
						st.name = names_script_map[(int)map_script[i + (16 * (scrol_x - 1))][a + (16 * (scrol_y - 1))] - 48];
					}
						st.otris();


						st.position(i * def_y, a * def_x);
						window.draw(st.sprite);
					
				}
			}
		}

		otris_map = 1;

		/// <summary>
		/// ///////////////////////////////////////////////////////////
		/// </summary>
		/// <returns></returns>
		text.setPosition(win_x - 120, 13);
		text.setString("y:"+to_string(scrol_y)+" x:" + to_string(scrol_x));
		window.draw(text);



		text.setPosition(win_x - 120, 33);			
		text.setString(log_info);
		window.draw(text);

		text.setPosition(win_x - 120, 53);
		text.setString("map #:" + to_string(map_num));
		window.draw(text);

		text.setPosition(win_x - 120, 1);
		text.setString("Map mode:"+to_string(mode_map));
		window.draw(text);


		text.setPosition(win_x - 120, 83);
		text.setString(save_file);
		window.draw(text);


		window.display();
	}

}
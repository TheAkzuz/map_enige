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

int scrol_x_mas=0;
int scrol_y_mas = 0;


int win_x = 1200; //window mode
int win_y = 600;

int win_mode = 0; // active type
int console_mode = 0;
string save_file;

string info_select_s = "------"; // info about select clik

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

	void return_size_image()
	{
		Vector2u image_size = image.getSize();
		
	}


	

};










void crea_setka()
{
	for (int a = 0; a < 9; a++)
	{
		for (int i = 0; i < map_y; i++)
		{

			map_vid[a][i] = string(map_x, '0');
			map_script[i] = string(map_x, '0');


		}
	}
	for (int i = 0; i < map_y; i++)
	{
		info_map_script[i].resize(map_x);
	}
}
/// <summary>
/// ////////////////////////// SAVE MAP
/// </summary>
void save_fun()
{
	ofstream save_fu(save_file+".txt");
	save_fu << map_x << endl;
	save_fu << map_y << endl;
	save_fu << map_z << endl;


	for (int a = 0; a < map_z; a++)
	{
		for (int i = 0; i < map_y; i++)
		{
			save_fu << map_vid[a][i] << endl;
		}

		for (int i = 0; i < 10; i++)
		{

			save_fu << names_st_map[a][i] << endl;
		}
	}


	for (int i = 0; i < map_y; i++)
	{
		save_fu << map_script[i] << endl;
	}
	for (int i = 0; i < 10; i++)
	{

		save_fu << names_script_map[i] << endl;
	}

	for (int y = 0; y < map_y; y++)
	{
		for (int i = 0; i < map_x; i++)
		{
			save_fu << info_map_script[y][i] << endl;
		}
	}
	save_fu.close();

}




void map_to_script()
{
}


void set_size_map()
{
	for (int i = 0; i < map_z; i++)
	{
		map_vid[i].resize(map_y);
	}
	map_script.resize(map_y);
	info_map_script.resize(map_y);

//	info_map_script.resize(map_y, vector<string>(map_x));
	
}



void load_save()
{

	fstream load_file(save_file+".txt");

	load_file >> map_x;
	load_file >> map_y;
	load_file >> map_z;

	for (int i = 0; i < map_z; i++)
	{
		map_vid[i].resize(map_y);
	}
	for (int i = 0; i < map_y; i++)
	{
		info_map_script[i].resize(map_x);
	}
	//map_vid.resize(map_z, vector<string>(map_y));
	map_script.resize(map_y);
	//info_map_script.resize(map_y, vector<string>(map_x));


	for (int a = 0; a < map_z; a++)
	{
		for (int i = 0; i < map_y; i++)
		{
			load_file >> map_vid[a][i];
		}

		for (int i = 0; i < 10; i++)
		{

			load_file >> names_st_map[a][i];
		}
	}


	for (int i = 0; i < map_y; i++)
	{
		load_file >> map_script[i];
	}
	for (int i = 0; i < 10; i++)
	{

		load_file >> names_script_map[i];
	}


	for (int y = 0; y < map_y; y++)
	{
		for (int i = 0; i < map_x; i++)
		{
			load_file >> info_map_script[y][i];
		}
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

	for (int a = 0; a < map_z; a++)
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
	console_von.position(win_x - 600, 0);

	Texturs save_von("red_tt");
	save_von.position(win_x - 200, 70);

	Texturs load_von("load");
	load_von.position(win_x - 130, 126);

	Texturs create_setka("create_setka");
	create_setka.position(win_x - 130, 170);

	Texturs st(2,1);

	Texturs save_f("save_file");
	save_f.position(win_x-130, 220 + 32 + (32 * 9));

	Texturs script_load("script_map");
	script_load.position(win_x - 130,save_f.y+26);

	Texturs set_y("set_y");
	set_y.position(win_x - 320, 73);

	Texturs set_x("set_x");
	set_x.position(win_x - 520, 73);

	Texturs mode_set_name("mode_set_name");
	mode_set_name.position(win_x - 520, 120);

	Texturs info_select("info_select");
	info_select.position(win_x - 400, 120);

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

			if (event.type == Event::MouseButtonPressed && Mouse::isButtonPressed(Mouse::Left) && win_mode >= 2 && win_mode <= 11 && mouse_pos.x < map_x * 32 && mouse_pos.y < map_y * 32)
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

				///////////////click on map
				string simvol_map = to_string(win_mode - 2);
				if (mode_map ==0 && console_mode == 0)
				{
				
				map_vid[map_num][mouse_y_c - 1 + scrol_y_mas][mouse_x_c - 1 + scrol_x_mas]        = simvol_map[0];
				}
				if (mode_map == 1 && console_mode == 1)
				{

					map_script[mouse_y_c - 1 + scrol_y_mas][mouse_x_c - 1 + scrol_x_mas] = simvol_map[0];

				
					info_map_script[mouse_y_c - 1 + scrol_y_mas][mouse_x_c - 1 + scrol_x_mas] = save_file + "+" + to_string(mouse_y_c - 1 + scrol_y_mas) + "+" + to_string(mouse_x_c - 1 + scrol_x_mas);
					
				}

				if (console_mode == 2)
				{
					info_select_s = "-------";
					if (info_map_script[mouse_y_c - 1 + scrol_y_mas][mouse_x_c - 1 + scrol_x_mas] != '4')
					{
						info_select_s += "\n"+ info_map_script[mouse_y_c - 1 + scrol_y_mas][mouse_x_c - 1 + scrol_x_mas];
					}

				}
			}
			////////////////////move map
			if (event.type == Event::KeyPressed)
			{
				if (Keyboard::isKeyPressed(Keyboard::Up) && scrol_y>1 )
				{
					scrol_y --;
					cout << scrol_y << endl;
				}

				if (Keyboard::isKeyPressed(Keyboard::Down) && scrol_y<map_y-15)
				{
					scrol_y ++;
					cout << scrol_y << endl;
				}
				if (Keyboard::isKeyPressed(Keyboard::Left) && scrol_x>1)
				{
					scrol_x --;
					cout << scrol_x << endl;
				}

				if (Keyboard::isKeyPressed(Keyboard::Right)&& scrol_x< map_x-15)
				{
					scrol_x ++;
					cout << scrol_x << endl;
				}


				scrol_x_mas= (scrol_x-1);
				scrol_y_mas= (scrol_y - 1) ;
			}




		}




		//////active text path
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


		////////// info about size map/////////////////////////////


		if (Mouse::isButtonPressed(Mouse::Left) && (mouse_x >set_x.x && mouse_x < set_x.x + 114) && (mouse_y > set_x.y && mouse_y < set_x.y + 24))
		{
			
			log_info = "set x";
			map_x = stoi( save_file);
			crea_setka();
		
		}

		if (Mouse::isButtonPressed(Mouse::Left) && (mouse_x > set_y.x && mouse_x < set_y.x + 114) && (mouse_y > set_y.y && mouse_y < set_y.y + 24))
		{
			
			log_info = "set y";
			map_y = stoi(save_file);
			set_size_map();
			crea_setka();
			

		}

		if (Mouse::isButtonPressed(Mouse::Left) && (mouse_x > mode_set_name.x && mouse_x < mode_set_name.x + 114) && (mouse_y > mode_set_name.y && mouse_y < mode_set_name.y + 25))
		{

			if (console_mode != 0)
			{
				log_info = "No active set name";
				console_mode = 0;
				Sleep(30);
			}
		}
		if (Mouse::isButtonPressed(Mouse::Left) && (mouse_x > mode_set_name.x && mouse_x < mode_set_name.x + 114) && (mouse_y > mode_set_name.y && mouse_y < mode_set_name.y + 25))
		{
			if (console_mode != 1)
			{
				log_info = "Active set name";
				console_mode =1;
				Sleep(30);
			}
		}



		if (Mouse::isButtonPressed(Mouse::Left) && (mouse_x > info_select.x && mouse_x < info_select.x + 114) && (mouse_y > info_select.y && mouse_y < info_select.y + 25))
		{
			if (console_mode != 2)
			{
				log_info = "On chek info select";
				console_mode = 2;
				Sleep(30);
			}
		}





	//////////it's vibor map setki

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
		window.draw(set_y.sprite);
		window.draw(set_x.sprite);
		window.draw(mode_set_name.sprite);
		window.draw(info_select.sprite);

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

			for (int i = 0; i <16 && i<=map_x; i++)
			{
				for (int a = 0; a<16 && a <= map_y; a++)
				{		
					if (mode_map == 0)
					{
						st.name = names_st_map[map_num][(int)map_vid[map_num]  [a + scrol_y_mas]   [i + scrol_x_mas] - 48];
					}
					if (mode_map == 1)
					{
						st.name = names_script_map[(int)map_script[a + scrol_y_mas][i + scrol_x_mas] - 48];
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

		text.setPosition(win_x - 320, 53);
		text.setString("Y count:" + to_string(map_y));
		window.draw(text);

		text.setPosition(win_x - 520, 53);
		text.setString("X count:" + to_string(map_x));
		window.draw(text);

		text.setPosition(win_x - 120, 1);
		text.setString("Map mode:"+to_string(mode_map));
		window.draw(text);

		///////text in console
		text.setPosition(win_x - 185, 83);
		text.setString(save_file);
		window.draw(text);

		//this print info about select
		text.setPosition(win_x - 500, 250);
		text.setString(info_select_s);
		window.draw(text);


		window.display();
	}

}
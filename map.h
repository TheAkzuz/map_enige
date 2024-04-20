#pragma once
	#include <SFML/Graphics.hpp>
	#include <SFML/Audio.hpp>
	#include <cmath>
	#include <ctime>
	#include <cstdlib>
	#include <string>
	#include <fstream>
	#include <vector>
	using namespace std;
	using namespace sf;
	
	 int map_x = 16;
	 int map_y = 32;
	 int map_z = 9;

	vector<vector<string>> map_vid(map_z,vector<string>(map_y));
	vector<string> map_script(map_y);
	//string  map_vid[9][map_y] = {};
	//string  map_script[map_y] = {};
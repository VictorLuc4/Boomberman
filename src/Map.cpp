/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Map
*/

#include "Map.hpp"

Block	*initBlocks(std::vector<std::string> map, int i, int j)
{
	switch (map[i][j]) {
		case '#':
			return new Block(WALL, "wall", j, i);
		case '+':
			return new Block(CORNER, "corner", j, i);
		case '1':
			return new Block(POWERUP1, "blastboost", j, i);
		case '2':
			return new Block(POWERUP2, "bombboost", j, i);
		case '3':
			return new Block(POWERUP3, "pushboost", j, i);
		case '4':
			return new Block(POWERUP4, "speedboost", j, i);
		case '5':
			return new Block(POWERUP5, "shieldboost", j, i);
		case '6':
			return new Block(POWERUP6, "ghostboost", j, i);
		case '@':
			return new Block(COLUMN, "column", j, i);
		case ' ':
			return new Block(EMPTY, "", j, i);
		case 'X':
			return new Block(BOX, "box", j, i);
		case 'B':
			return new Block(BOMB, "bomb", j, i);
	}
	return new Block(EMPTY, "", j, i);
}

std::string	addBoxes(int type, int len, std::string line, std::string end, int seed)
{
	int r, i = -1;

	std::srand(std::time(0) + seed);
	while(++i < len) {
		if ((type == 1 && i % 2 != 0) || (type == 2 && i % 2 == 0))
			line.push_back('@');
		else {
			r = std::rand() % 100;
			if (r % 2 == 0)
				line.push_back(' ');
			else
				line.push_back('X');
		}

	}
	return line + end;
}

std::string	addWalls(int len)
{
	std::string	walls;
	int	i = -1;

	walls.push_back('+');
	while (++i < len)
		walls.push_back('#');
	walls.push_back('+');	
	return walls;
}

std::vector<std::string>	generateRandomMap(int size)
{
	int	i = -1;
	int	seed = 2;
	std::vector<std::string> map;

	map.push_back(addWalls(13 + 2 * (size - 1)));
	map.push_back(addBoxes(0, 9 + 2 * (size - 1), "#  ", "  #", 0));
	map.push_back(addBoxes(2, 11 + 2 * (size - 1), "# ", " #", 1));
	while (++i < (1 + size)) {
		map.push_back(addBoxes(0, 13 + 2 * (size - 1), "#", "#", seed));
		map.push_back(addBoxes(1, 13 + 2 * (size - 1), "#", "#", seed + 1));
		seed += 2;
	}
	map.push_back(addBoxes(0, 13 + 2 * (size - 1), "#", "#", seed));
	map.push_back(addBoxes(2, 11 + 2 * (size - 1), "# ", " #", seed + 1));
	map.push_back(addBoxes(0, 9 + 2 * (size - 1), "#  ", "  #", seed + 2));
	map.push_back(addWalls(13 + 2 * (size - 1)));
	return map;
}

Map::Map(int size, std::vector<std::string> mapTxt)
{
	int j, i = -1;

	_size = size;
	if (mapTxt.empty())
		_mapTxt = generateRandomMap(_size);
	else
		_mapTxt = mapTxt;
	while (++i < _mapTxt.size()) {
		j = -1;
		_map.push_back({});
		while(++j < _mapTxt[i].length()) {
			_map[i].push_back(initBlocks(_mapTxt, i, j));
		}
	}
}

Map::~Map()
{
}

Block	*Map::getBlock(int x, int z)
{
	return _map[z][x];
}

std::vector<std::vector<Block *>>	Map::getMap()
{
	return _map;
}

std::vector<std::string>	&Map::getMapTxt()
{
	return _mapTxt;
}

void	Map::setBlock(TypeBlock type, std::string name, int x, int z)
{
	_map[z][x] = new Block(type, name, x, z);
}

void	Map::setBlockTxt(char c, int x, int z)
{
	_mapTxt[z][x] = c;
}

int	Map::getSize()
{
	return _size;
}
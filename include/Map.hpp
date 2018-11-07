/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Map
*/

#ifndef MAP_HPP_
	#define MAP_HPP_

#include "Block.hpp"

class Map {
	public:
		Map(int size, std::vector<std::string> mapTxt);
		~Map();
		Block *getBlock(int x, int y);
		std::vector<std::vector<Block *>> getMap();
		std::vector<std::string> &getMapTxt();
		void setBlock(TypeBlock type, std::string name, int x, int y);
		void setBlockTxt(char c, int x, int z);
		int getSize();
	private:
		std::vector<std::vector<Block *>> _map;
		std::vector<std::string> _mapTxt;
		int _size;
};

#endif /* !MAP_HPP_ */

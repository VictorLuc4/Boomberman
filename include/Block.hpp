/*
** EPITECH PROJECT, 2018
** Block.hpp
** File description:
** Block
*/

#ifndef BLOCK_HPP_
	#define BLOCK_HPP_

#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <map>
#include <thread>
#include "irrlicht.h"
#include "driverChoice.h"

using namespace irr::scene;

enum TypeBlock {
        WALL,
        CORNER,
        POWERUP1,
        POWERUP2,
        POWERUP3,
        POWERUP4,
        POWERUP5,
        POWERUP6,
        BOMB,
        FIRE,
        BOX,
        COLUMN,
        FLOOR,
        EMPTY
};

class Block {
	public:
                Block(TypeBlock type, std::string name, int x, int z);

                TypeBlock               getType();
                std::string             getName();
                std::string	        getTexturePath();
                std::string	        getMeshPath();
                int                     getPosX();
                int                     getPosZ();
                std::pair<int, int>     getPos();
                void                    setNode(IMeshSceneNode *node);
                void                    setFire(IParticleSystemSceneNode *ps);
                IMeshSceneNode          *getNode();
                IParticleSystemSceneNode        *getFire();
                float                   getRatio();
                void                    setRatio(float ratio);
                std::chrono::time_point<std::chrono::system_clock> getStart();
                std::chrono::time_point<std::chrono::system_clock> getEnd();
                void                    setStart();
                void                    setEnd();
                int                     getBlast();
                void                    setBlast(int blast);
                void                    setKick(bool kick);
                bool                    getKick();
                void                    setDir(int x, int z);
                std::pair<int, int>     getDir();
	private:
                std::pair<int, int>     _pos;
                TypeBlock               _type;
                std::string             _name;
                std::string             _meshPath;
                std::string             _texturePath;
                IMeshSceneNode          *_node;
                IParticleSystemSceneNode        *_ps;
		float			_ratio;
                std::chrono::time_point<std::chrono::system_clock> _start;
                std::chrono::time_point<std::chrono::system_clock> _end;
                int                     _blast;
                bool                    _kick;
                std::pair<int, int>     _dir;                
};

#endif /* !BLOCK_HPP_ */


/*
** EPITECH PROJECT, 2018
** Block.cpp
** File description:
** Block
*/

#include "Block.hpp"

Block::Block(TypeBlock type, std::string name, int x, int z) : _type(type), _name(name)
{
	_pos.first = x;
	_pos.second = z;
	_meshPath = "media/mediaGame/file3D/map/" + name + ".obj";
	_texturePath = "media/mediaGame/file3D/map/" + name + ".png";
	_ratio = 0;
	_blast = 1;
	_kick = false;
}

TypeBlock       Block::getType()
{
	return _type;
}

std::string	Block::getName()
{
	return _name;
}

std::string	Block::getTexturePath()
{
	return _texturePath;
}

std::string	Block::getMeshPath()
{
	return _meshPath;
}

int             Block::getPosX()
{
	return _pos.first;
}

int             Block::getPosZ()
{
	return _pos.second;
}

std::pair<int, int>     Block::getPos()
{
	return _pos;
}

void		Block::setNode(IMeshSceneNode *node)
{
	_node = node;
}

void		Block::setFire(IParticleSystemSceneNode *ps)
{
	_ps = ps;
}

IMeshSceneNode	*Block::getNode()
{
	return _node;
}

IParticleSystemSceneNode	*Block::getFire()
{		
	return _ps;
}

float		Block::getRatio()
{
	return _ratio;
}

void		Block::setRatio(float ratio)
{
	_ratio = ratio;
}

std::chrono::time_point<std::chrono::system_clock>	Block::getStart()
{
	return _start;
}

std::chrono::time_point<std::chrono::system_clock>	Block::getEnd()
{
	return _end;
}

void		Block::setStart()
{
	_start = std::chrono::system_clock::now();
}

void		Block::setEnd()
{
	_end = std::chrono::system_clock::now();
}

int		Block::getBlast()
{
	return _blast;
}

void		Block::setBlast(int blast)
{
	_blast = blast;
}

void		Block::setKick(bool kick)
{
	_kick = kick;
}

bool		Block::getKick()
{
	return _kick;
}

void		Block::setDir(int x, int z)
{
	_dir.first = x;
	_dir.second = z;
}

std::pair<int, int>	Block::getDir()
{
	return _dir;
}
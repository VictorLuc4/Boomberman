/*
** EPITECH PROJECT, 2018
** VK
** File description:
** ICharacter interface initialisation
*/

#ifndef ICHARACTER_HPP_
	#define ICHARACTER_HPP_

#include "Graphical.hpp"
#include "GameScene.hpp"
#include <vector>
#include "Map.hpp"

enum	_STATUS
{
	_S_UP,
	_S_DOWN,
	_S_LEFT,
	_S_RIGHT,
	_S_STAND
};

enum	_ACTIONS
{
	_A_RIGHT,
	_A_LEFT,
	_A_UP,
	_A_DOWN,
	_A_DROPBOMB
};

enum	_POSTGHOST
{
	_G_LEFT,
	_G_VERY_LEFT,
	_G_RIGHT,
	_G_VERY_RIGHT,
	_G_UP,
	_G_VERY_UP,
	_G_DOWN,
	_G_VERY_DOWN
};

class ICharacter {
	public:
		virtual		~ICharacter() = default;

		virtual bool	isAlive() const = 0;
		virtual void	movement() = 0;
		virtual void	setScene(ISceneManager *) = 0;
		virtual void	setGameScene(GameScene *) = 0;
		virtual void	setMap(Map *) = 0;
		virtual void	setKeys(const std::map<_ACTIONS, irr::EKEY_CODE> &) = 0;
		virtual void	setReceiver(MyEventReceiver *) = 0;
		virtual void	loadMesh(const std::string &) = 0;
		virtual void	setMapPosition(const int &, const int &) = 0;
		virtual int	getBombs() = 0;
		virtual int	getBlast() = 0;
		virtual int 	getSpeed() = 0;
		virtual std::pair<int, int> getPos() = 0;
		virtual void	setEnemyPos(const std::pair<int, int> &) = 0;
		virtual std::pair<int, int> getMapPosition() const = 0;
		virtual void 	setBombs(int bombs) = 0;
		virtual void	setBlast(int blast) = 0;
		virtual void	setSpeed(int speed) = 0;
		virtual void	addPush() = 0;
		virtual void	setIsAlive(bool isAlive) = 0;
};

#endif /* !ICHARACTER_HPP_ */

/*
** EPITECH PROJECT, 2018
** Player.hpp
** File description:
** Player
*/

#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <fstream>

#include "ICharacter.hpp"

#ifndef PLAYER_H_
#define PLAYER_H_

class Player : public ICharacter
{

public:
			Player();
			~Player() = default;

	void		loadMesh(const std::string &path);
	void		movement();
	void		dropBomb();
	bool		isAlive() const;
	void		die();
	void		restart();

	void		addTotalBomb();
	void		addPower();
	void		addScore(const int &points);
	void		addPush();
	void		addSpeed();
	void		addShield();
	void		addGhost();

	vector3df	getPosition() const;
	std::pair<int,int> getMapPosition() const;
	int		getBombPower() const;
	int		getCurrentBombNumber();
	int		getTotalBombNumber() const;
	bool		getPowerPush() const;
	std::map<_ACTIONS, irr::EKEY_CODE>	getKeys() const;

	void		setScene(ISceneManager *scene);
	void		setReceiver(MyEventReceiver *receiver);
	void		setMapPosition(const int &x, const int &y);
	void		setMap(Map *map);
	void		setGameScene(GameScene *gameScene);
	void		setKeys(const std::map<_ACTIONS, irr::EKEY_CODE> &keys);
	void		setEnemyPos(const std::pair<int, int> &enemyPos);


	int		getBombs();
	int		getBlast();
	int		getSpeed();
	std::pair<int, int>		getPos();

	void 	setBombs(int bombs);
	void	setBlast(int blast);
	void	setSpeed(int speed);
	void	setIsAlive(bool isAlive);
private:
	void		setPosition(const vector3df &pos);
	void		checkRotate(_STATUS tmp);
	void		moveLeft(vector3df &pos);
	void		moveRight(vector3df &pos);
	void		moveUp(vector3df &pos);
	void		moveDown(vector3df &pos);
	bool		checkMoveMap(const vector3df &pos);
	void		addTotalBomb(const int &nb);
	void		manageTimeBomb();
	void		checkStandingFire();
	bool		isDying();
	void		isDyingAnimation();
	bool		checkAxeCornerX(const int &x, const int &z, const int xL, const int xR);
	bool		checkAxeCornerZ(const int &x, const int &z, const int zU, const int zD);
	void		checkCollisionTime();
	bool		checkNearEmpty();
	void		tryMoveToEmpty(_POSTGHOST XG, _POSTGHOST YG);
	bool		checkRandomEmpty();
	void		enablePostShieldState();
	void		checkPostShield();

	int		_PV;
	int		_bombPower;
	int		_score;
	bool		_isAlive;
	int		_isDying;
	bool		_collision;
	int		_collisionTime;
	bool		_push;
	bool		_shield;
	bool		_postShield;
	int		_x;
	int		_y;
	int		_xFirst;
	int		_yFirst;
	irr::f32	_MOVEMENT_SPEED;
	int		_speedNb;
	int		_loopTime;
	int		_lastDropedTime;
	_STATUS		_status;
	_STATUS		_tmp;
	ISceneManager		*_scene;
	MyEventReceiver		*_receiver;
	IAnimatedMeshSceneNode	*_node;
	ISceneNode		*_n;
	Map			*_map;
	GameScene		*_gameScene;
	irr::ITimer		*_timer;
	std::vector<std::pair<int, bool>>	_Bombs;
	std::map<_ACTIONS, irr::EKEY_CODE>	_Keys;
	ISoundEngine	*_engine = createIrrKlangDevice();
};

#endif

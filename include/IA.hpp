/*
** EPITECH PROJECT, 2018
** IA.hpp
** File description:
** IA
*/

#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <fstream>

#include "ICharacter.hpp"
#include "Graphical.hpp"
#include "GameScene.hpp"
#include "Map.hpp"
#include "Player.hpp"

#ifndef IA_H_
#define IA_H_

class Ia : public ICharacter
{
public:
	                Ia();
	virtual 	~Ia() = default;

	void		loadMesh(const std::string &path);
	void		movement();
	virtual void 	dropBomb();
	bool		isAlive() const;
	virtual void 	die();

	virtual void	addTotalBomb();
	virtual void 	addPower();
	virtual void 	addScore(const int &points);
	virtual void	addPush();
	virtual void	addSpeed();
	virtual void    addShield();

	vector3df	getPosition() const;
	std::pair<int,int> getMapPosition() const;
	virtual int	getBombPower() const;
	virtual int	getCurrentBombNumber();
	virtual int	getTotalBombNumber() const;
	virtual bool	getPowerPush() const;
	virtual bool    getIsInDanger() const;

	virtual void	setScene(ISceneManager *scene);
	virtual void	setReceiver(MyEventReceiver *receiver);
	virtual void	setPosition(const vector3df &pos);
	virtual void	setMap(Map *map);
	virtual void	setGameScene(GameScene *gameScene);
	virtual void    setIsInDanger(bool danger);
	virtual void    setMapPosition(const int &x, const int &y);
	void		setKeys(const std::map<_ACTIONS, irr::EKEY_CODE> &keys);
	void		setEnemyPos(const std::pair<int, int> &enemyPos);

	virtual _STATUS  calculateMouvToEscape();
	virtual _STATUS  calculateMouvToRush();
	virtual _STATUS  chooseMouv(std::pair<_STATUS, _STATUS> mouvements);
	virtual std::pair<_STATUS, _STATUS>    calculateMouv(std::pair<int, int> vect);
	virtual std::pair<int, int>            calculateVector(std::pair<int, int> ia, std::pair<int, int> enemy);
	virtual bool     inDanger();
	virtual bool     checkBox(char box);
	virtual bool     checkUp(std::pair<int, int> pos, std::vector<std::string> map);
	virtual bool     checkDown(std::pair<int, int> pos, std::vector<std::string> map);
	virtual bool     checkRight(std::pair<int, int> pos, std::vector<std::string> map);
	virtual bool     checkLeft(std::pair<int, int> pos, std::vector<std::string> map);
	virtual bool     checkMoving();
	std::vector<_STATUS> getEscapeAroundPos(std::pair<int, int> pos);

	int		getBombs();
	int		getBlast();
	int		getSpeed();
	std::pair<int, int>		getPos();

	void 	setBombs(int bombs);
	void	setBlast(int blast);
	void	setSpeed(int speed);
	void	setIsAlive(bool isAlive);
private:
	void		checkRotate(_STATUS tmp);
	void		moveLeft(vector3df &pos);
	void		moveRight(vector3df &pos);
	void		moveUp(vector3df &pos);
	void		moveDown(vector3df &pos);
	bool		checkMoveMap(const vector3df &pos);
	void		addTotalBomb(const int &nb);
	void		manageTimeBomb();

	void            checkStandingFire();
	bool            isDying();
	void            isDyingAnimation();
	std::pair<int, int> getNearestEnemy();
	void		enablePostShieldState();
	void		checkPostShield();

	int             _lifeNumber;
	_STATUS         _mouv;
	int             _isDying;
	bool            _isMoving;
	bool            _isInDanger;
	bool		_shield;
	bool		_postShield;
	int		_PV;
	int		_bombPower;
	int		_score;
	bool		_isAlive;
	bool		_collision;
	bool		_push;
	int		_x;
	int		_y;
	irr::f32	_MOVEMENT_SPEED;
	int		_speedNb;
	int		_loopTime;
	int		_lastDropedTime;
	_STATUS		_status;
	_STATUS		_tmp;
	std::pair<int, int>	_EnemyPos;
	ISceneManager		*_scene;
	MyEventReceiver		*_receiver;
	IAnimatedMeshSceneNode	*_node;
	Map			*_map;
	GameScene		*_gameScene;
	irr::ITimer		*_timer;
	std::vector<std::pair<int, bool>>	_Bombs;
	vector3df     _nextPos;
};

#endif

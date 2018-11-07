/*
** EPITECH PROJECT, 2018
** IA.cpp
** File description:
** IA
*/

#include <iostream>
#include <random>
#include <cmath>
#include "IA.hpp"

Ia::Ia()
{
	_PV 		= 100;
	_bombPower 	= 1;
	_score 		= 0;
	_isAlive 	= true;
	_isDying	= 0;
	_collision 	= false;
	_push 		= false;
	_shield		= true;
	_postShield	= false;
	_MOVEMENT_SPEED = 2.4;
	_speedNb	= 0;
	_status 	= _S_STAND;
	_tmp 		= _S_STAND;
	_isMoving       = false;
	_nextPos        = vector3df(40, 0, -40);
	_lifeNumber     = 30;
}

void	Ia::loadMesh(const std::string &path)
{
	_node = _scene->addAnimatedMeshSceneNode(_scene->getMesh(path.c_str()));
	_node->setCurrentFrame(10);
	_node->setAnimationSpeed(0);
	_node->setRotation(vector3df(0,-90,0));
	_node->setScale(vector3df(14,14,14));
	_node->setMaterialFlag(EMF_LIGHTING, false);
}

void	Ia::movement()
{
	_isMoving = this->checkMoving();
	vector3df pos = getPosition();
	checkStandingFire();
	checkPostShield();
	if (_isDying){
		isDying();
		return;
	}
	if (_isMoving == false){
		_isMoving = true;
		std::pair<int, int> postxt = this->getMapPosition();
		_nextPos = vector3df(pos.X, pos.Y, pos.Z);
		_STATUS mouv;
		_loopTime = _timer->getTime();
		_isInDanger = this->inDanger();
		if (_isInDanger == true){
			_tmp = this->calculateMouvToEscape();
		}
		else {
		 	_tmp = this->calculateMouvToRush();
		}

		switch (_tmp) {
		case 0:
			_nextPos.Z += 40.0;
			_mouv = _STATUS::_S_UP;
			moveUp(pos);
			break;
		case 1:
			_nextPos.Z -= 40.0;
			_mouv = _STATUS::_S_DOWN;
			moveDown(pos);
			break;
		case 2:
			_nextPos.X -= 40.0;
			_mouv = _STATUS::_S_LEFT;
			moveLeft(pos);
			break;
		case 3:
			_mouv = _STATUS::_S_RIGHT;
			_nextPos.X += 40.0;
			moveRight(pos);
			break;
		case 4:
			break;
		}
		checkRotate(_tmp);
	}
	else {
		switch (_mouv) {
		case 0:
			moveUp(pos);
			break;
		case 1:
			moveDown(pos);
			break;
		case 2:
			moveLeft(pos);
			break;
		case 3:
			moveRight(pos);
			break;
		case 4:
			break;
		}

	}

}

bool Ia::checkMoving()
{
	vector3df pos = this->getPosition();
	if ((_nextPos.X <= pos.X + 2 && _nextPos.X >= pos.X - 2) && (_nextPos.Z <= pos.Z + 2 && _nextPos.Z >= pos.Z - 2)){
		_isMoving = false;
		return false;
	}
	else
		_isMoving = true;
	return true;
}

std::vector<_STATUS> Ia::getEscapeAroundPos(std::pair<int, int> pos)
{
	std::vector<_STATUS> escape;
	std::vector<std::string> &maptxt = _map->getMapTxt();

	if (this->checkUp(pos, maptxt) == true)
		escape.push_back(_STATUS::_S_UP);
	if (this->checkDown(pos, maptxt) == true)
		escape.push_back(_STATUS::_S_DOWN);
	if (this->checkLeft(pos, maptxt) == true)
		escape.push_back(_STATUS::_S_LEFT);
	if (this->checkRight(pos, maptxt) == true)
		escape.push_back(_STATUS::_S_RIGHT);

	return escape;

}

_STATUS Ia::calculateMouvToEscape()
{
	std::pair<int, int> pos = this->getMapPosition();
	std::vector<_STATUS> esc = this->getEscapeAroundPos(pos);
	unsigned int i = 0;
	int b = 1;
	std::vector<std::string> &maptxt = _map->getMapTxt();
	std::pair<int, int> xpos = std::make_pair(0, 0);

	if (esc.size() == 0)
		return _STATUS::_S_STAND;


	for (_STATUS s = esc[i]; i < esc.size(); i++){
		switch (s){
		case 0:
			for (int j = pos.second - b; j >= 1 && b <= _bombPower; b--){
				xpos = std::make_pair(pos.first, pos.second - b);
				if (this->checkLeft(xpos, maptxt) == true ||
				    this->checkRight(xpos, maptxt) == true ||
				    this->checkUp(xpos, maptxt) == true )
					return _STATUS::_S_UP;
			}
			break;
		case 1:
			for (int j = pos.second - b; j >= 1 && b < _bombPower; b--){
				xpos = std::make_pair(pos.first, pos.second - b);
				if (this->checkLeft(xpos, maptxt) == true ||
				    this->checkRight(xpos, maptxt) == true ||
				    this->checkDown(xpos, maptxt) == true )
					return _STATUS::_S_DOWN;
			}
			break;
		case 2:
			for (int j = pos.second - b; j >= 1 && b < _bombPower; b--){
				xpos = std::make_pair(pos.first, pos.second - b);
				if (this->checkDown(xpos, maptxt) == true ||
				    this->checkRight(xpos, maptxt) == true ||
				    this->checkUp(xpos, maptxt) == true )
					return _STATUS::_S_LEFT;
			}
			break;
		case 3:
			for (int j = pos.second - b; j >= 1 && b < _bombPower; b--){
				xpos = std::make_pair(pos.first, pos.second - b);
				if (this->checkLeft(xpos, maptxt) == true ||
				    this->checkDown(xpos, maptxt) == true ||
				    this->checkUp(xpos, maptxt) == true )
					return _STATUS::_S_RIGHT;
			}
			break;
		case 4:
			break;
		}
	}
	return _STATUS::_S_STAND;
}

_STATUS Ia::calculateMouvToRush()
{
	std::pair<int, int> enemyPos = _EnemyPos;
	std::pair<int, int> vect = this->calculateVector(this->getMapPosition(), enemyPos);
	std::pair<_STATUS, _STATUS> mouvements = this->calculateMouv(vect);
	_STATUS choosenMouv = this->chooseMouv(mouvements);

	return choosenMouv;
}

_STATUS Ia::chooseMouv(std::pair<_STATUS, _STATUS> mouvements)
{
	std::vector<std::string> &maptxt = _map->getMapTxt();

	std::pair<int, int> pos = this->getMapPosition();
	bool up = this->checkUp(pos, maptxt);
	bool down = this->checkDown(pos, maptxt);
	bool left = this->checkLeft(pos, maptxt);
	bool right = this->checkRight(pos, maptxt);

	std::vector<_STATUS> good;

	if (up == false && down == false && left == false && right == false)
		return _STATUS::_S_STAND;


	if (up == true){
		if (mouvements.first == _STATUS::_S_UP || mouvements.second == _STATUS::_S_UP)
			return _STATUS::_S_UP;
		good.push_back(_STATUS::_S_UP);
	}
	if (down == true){
		if (mouvements.first == _STATUS::_S_DOWN || mouvements.second == _STATUS::_S_DOWN)
			return _STATUS::_S_DOWN;
		good.push_back(_STATUS::_S_DOWN);
	}
	if (left == true){
		if (mouvements.first == _STATUS::_S_LEFT || mouvements.second == _STATUS::_S_LEFT)
			return _STATUS::_S_LEFT;
		good.push_back(_STATUS::_S_LEFT);
	}
	if (right == true){
		if (mouvements.first == _STATUS::_S_RIGHT || mouvements.second == _STATUS::_S_RIGHT)
			return _STATUS::_S_RIGHT;
		good.push_back(_STATUS::_S_RIGHT);
	}
	this->dropBomb();
	int randNum = rand()%(11-1 + 1) + 1;
	if (randNum % 2 == 0)
		return good[0];
	else {
		if (good.size() > 1)
			return good[1];
		else
			return good[0];
	}
	return _STATUS::_S_DOWN;
}

std::pair<_STATUS, _STATUS> Ia::calculateMouv(std::pair<int, int> vect)
{
	_STATUS one;
	_STATUS two;

	if (vect.first == 0){
		(vect.second < 0) ? (two = _STATUS::_S_UP) : (two = _STATUS::_S_DOWN);
		two == _STATUS::_S_DOWN ? (one = _STATUS::_S_UP) : (one = _STATUS::_S_DOWN);
		return std::make_pair(two, one);
	}
	else if (vect.second == 0){
		(vect.first < 0) ? (one = _STATUS::_S_LEFT) : (one = _STATUS::_S_RIGHT);
		one == _STATUS::_S_LEFT ? (two = _STATUS::_S_RIGHT) : (two = _STATUS::_S_LEFT);
		int randNum = rand()%(101-1 + 1) + 1;
		if (randNum % 7 == 0)
			this->dropBomb();

		return std::make_pair(one, two);
	}

	(vect.first > 0) ? (one = _STATUS::_S_RIGHT) : (one = _STATUS::_S_LEFT);
	(vect.second > 0) ? (two = _STATUS::_S_DOWN) : (two = _STATUS::_S_UP);
	return std::make_pair(one, two);
}

std::pair<int, int> Ia::calculateVector(std::pair<int, int> ia, std::pair<int, int> enemy)
{
	return std::make_pair((enemy.first - ia.first), (enemy.second - ia.second));
}

bool Ia::inDanger()
{
	std::vector<std::string> &maptxt = _map->getMapTxt();
	int hauteur = maptxt.size();
	int longeur = strlen(maptxt[0].c_str());
	std::pair<int, int> pos = this->getMapPosition();

	if (maptxt[pos.second][pos.first] == 'B'){
		return true;
	}
	for (int i = pos.first; i < hauteur && i < (pos.first + _bombPower + 1); i++){
		if (maptxt[pos.second][i] == 'B')
			return true;
	}
	for (int j = pos.first; j > 0 && j > (pos.first - (_bombPower+1) ); j--){
		if (maptxt[pos.second][j] == 'B')
			return true;
	}
	for (int k = pos.second; k > 0 && k > (pos.second - (_bombPower + 1)); k--){
		if (maptxt[k][pos.first] == 'B')
			return true;
	}
	for (int l = pos.second; l < longeur && l < (pos.second + _bombPower + 1); l++){
		if (maptxt[l][pos.first] == 'B')
			return true;
	}
	return false;
}

bool Ia::checkBox(char box)
{
	if (box == 'B' || box == '@'  || box == 'X' || box == '#' || box == 'F')
		return false;
	return true;
}

bool Ia::checkUp(std::pair<int, int> pos, std::vector<std::string> map)
{
	if (pos.second <= 1)
		return false;

	char box = map[pos.second - 1][pos.first];
	return this->checkBox(box);
}

bool Ia::checkDown(std::pair<int, int> pos, std::vector<std::string> map)
{
	int size = map.size();

	if (pos.second >= size - 2)
		return false;

	char box = map[pos.second + 1][pos.first];
	return this->checkBox(box);
}

bool Ia::checkRight(std::pair<int, int> pos, std::vector<std::string> map)
{
	int size = strlen(map[0].c_str());

	if (pos.first >= size - 1)
		return false;

	char box = map[pos.second][pos.first + 1];
	return this->checkBox(box);
}

bool Ia::checkLeft(std::pair<int, int> pos, std::vector<std::string> map)
{
	if (pos.first <= 1)
		return false;

	char box = map[pos.second][pos.first - 1];
	return this->checkBox(box);
}

bool	Ia::isAlive() const
{
	return _isAlive;
}

void	Ia::die()
{
	if (_shield)
		enablePostShieldState();
	else {
		if (_isDying == 0)
			_isDying = _timer->getTime();
		else
			isDying();
	}
}

void Ia::addShield()
{
	_shield = true;
}

void	Ia::addTotalBomb()
{
	addTotalBomb(1);
}

void	Ia::addPower()
{
	_bombPower += 1;
}

void	Ia::addScore(const int &points)
{
	_score += points;
}

void	Ia::addPush()
{
	_push = true;
}

void	Ia::addSpeed()
{
	if (_speedNb <= 2) {
		_speedNb += 1;
		_MOVEMENT_SPEED += 0.4;
	}
}

void	Ia::dropBomb()
{
	manageTimeBomb();
	if (_timer->getTime() - _lastDropedTime < 150)
		return ;
	if (_map->getBlock(_x, _y)->getType() == BOMB)
		return ;
	if (getCurrentBombNumber() > 0)
	{
		for (auto &bomb : _Bombs)
			if (bomb.second == true)
			{
				bomb.second = false;
				bomb.first = _timer->getTime();
				_gameScene->bombPose(_map->getBlock(_x, _y), getBombPower());
				_lastDropedTime = _timer->getTime();
				return ;
			}
	}
}

vector3df	Ia::getPosition() const
{
	return (_node->getPosition());
}

std::pair<int, int>	Ia::getMapPosition() const
{
	return (std::make_pair(_x, _y));
}

int	Ia::getBombPower() const
{
	return (_bombPower);
}

int 	Ia::getCurrentBombNumber()
{
	int	nb = 0;

	for (auto bomb : _Bombs)
		if (bomb.second == true)
			nb += 1;
	return (nb);
}

int 	Ia::getTotalBombNumber() const
{
	int	nb = 0;
	for (auto bomb : _Bombs)
		nb += 1;
	return (nb);
}

bool Ia::getIsInDanger() const
{
	return (_isInDanger);
}


bool	Ia::getPowerPush() const
{
	return (_push);
}

void Ia::setIsInDanger(bool danger)
{
	_isInDanger = danger;
}

void	Ia::setScene(ISceneManager *scene)
{
	_scene = scene;
}

void	Ia::setReceiver(MyEventReceiver *receiver)
{
	_receiver = receiver;
}

void	Ia::setPosition(const vector3df &pos)
{
	_node->setPosition(vector3df(pos.X, pos.Y, pos.Z));
}

void	Ia::setMap(Map *map)
{
	_map = map;
}

void    Ia::setMapPosition(const int &x, const int &y)
{
	_x = x;
	_y = y;
	setPosition(vector3df(x * 40, 2, y * (-40)));
}

void	Ia::setGameScene(GameScene *gameScene)
{
	_gameScene = gameScene;
	_timer =_gameScene->getTimer();
	addTotalBomb(1);
	_loopTime = _timer->getTime();
}

void	Ia::setKeys(const std::map<_ACTIONS, irr::EKEY_CODE> &keys)
{
}

int	Ia::getBombs()
{
	return this->getCurrentBombNumber();
}

int	Ia::getBlast()
{
	return _bombPower;
}

int	Ia::getSpeed()
{
	return _speedNb;
}

std::pair<int, int>	Ia::getPos()
{
	return this->getMapPosition();
}
void		Ia::setEnemyPos(const std::pair<int, int> &enemyPos)
{
	_EnemyPos = enemyPos;
}

void 	Ia::setBombs(int bombs)
{
	this->addTotalBomb(bombs);
}

void	Ia::setBlast(int blast)
{
	_bombPower = blast;
}

void	Ia::setSpeed(int speed)
{
	_speedNb = speed;
}

void	Ia::setIsAlive(bool isAlive)
{
	isAlive = isAlive;
}


/////////////////// PRIVATE FUNCTUONS STARTS HERE
void	Ia::checkRotate(_STATUS tmp)
{
	if (tmp != _status){
		if (tmp == _S_DOWN)
			_node->setRotation(vector3df(0,0,0));
		else if (tmp == _S_UP)
			_node->setRotation(vector3df(0,180,0));
		else if (tmp == _S_RIGHT)
			_node->setRotation(vector3df(0,-90,0));
		else if (tmp == _S_LEFT)
			_node->setRotation(vector3df(0,90,0));
		_status = tmp;
		_node->setCurrentFrame(13);
		_node->setAnimationSpeed(18 * _MOVEMENT_SPEED);
	}
	else if (tmp != _S_STAND)
		_node->setAnimationSpeed(18 * _MOVEMENT_SPEED);
	else if (tmp == _S_STAND){
		_node->setCurrentFrame(13);
		_node->setAnimationSpeed(0);;
	}
}

void	Ia::moveLeft(vector3df &pos)
{
	pos.X -= _MOVEMENT_SPEED;
	if (checkMoveMap(pos))
	        setPosition(pos);
}

void	Ia::moveRight(vector3df &pos)
{
	pos.X += _MOVEMENT_SPEED;
	if (checkMoveMap(pos))
		setPosition(pos);
}
void	Ia::moveUp(vector3df &pos)
{
	pos.Z += _MOVEMENT_SPEED;
	if (checkMoveMap(pos))
		setPosition(pos);
}
void	Ia::moveDown(vector3df &pos)
{
	pos.Z -= _MOVEMENT_SPEED;
	if (checkMoveMap(pos))
	        setPosition(pos);
}

bool	Ia::checkMoveMap(const vector3df &pos)
{
	float x, z;

	x = (pos.X) / 40 ;
	z = (((pos.Z) / 40) * (-1));

	x = round(x);
	z = round(z);

	if (_collision == true)
		return (true);
	TypeBlock tmpBlock = _map->getBlock(x, z)->getType();
	if (tmpBlock != WALL && tmpBlock != BOX && tmpBlock != COLUMN)
	{
		if (tmpBlock == POWERUP1) {
			addPower();
			_gameScene->erasePowerUp(_map->getBlock(x, z));
		}
		else if (tmpBlock == POWERUP2) {
			addTotalBomb();
			_gameScene->erasePowerUp(_map->getBlock(x, z));
		}
		else if (tmpBlock == POWERUP3) {
			addPush();
			_gameScene->erasePowerUp(_map->getBlock(x, z));

		}
		else if (tmpBlock == POWERUP4) {
			_gameScene->erasePowerUp(_map->getBlock(x, z));
			addSpeed();
		}
		else if (tmpBlock == POWERUP5) {
			_gameScene->erasePowerUp(_map->getBlock(x, z));
		}
		else if (tmpBlock == POWERUP6) {
			_gameScene->erasePowerUp(_map->getBlock(x, z));
			addShield();
		}
		if (_map->getBlock(_x, _y)->getType() == BOMB)
		{
			if (tmpBlock == BOMB && ((int)x != _x || (int)z != _y))
				return false;
			else {
				_x = x;
				_y = z;
				return true;
			}
		}
		else if (tmpBlock == BOMB)
				return (false);
		_x = x;
		_y = z;
		return true;
	}
	else
		return false;
}

void		Ia::addTotalBomb(const int &nb)
{
	for (int i = 0; i < nb; i += 1)
		_Bombs.push_back(std::make_pair(0, true));
}

void		Ia::manageTimeBomb()
{
	int	t = _timer->getTime();

	for (auto &bomb : _Bombs)
		if (t - bomb.first > 3000)
			bomb.second = true;
}

void            Ia::checkStandingFire()
{
	if (_map->getBlock(_x, _y)->getType() == FIRE)
	{
		if (_lifeNumber == 0)
			die();
		else {
			_lifeNumber -= 1;
		}
	}
}

bool            Ia::isDying()
{
	if (_isDying == 0)
		return false;
	if (_timer->getTime() - _isDying > 2000)
	{
		_node->remove();
		_isAlive = false;
		_isDying = 1;
	}
	else
		isDyingAnimation();
	return true;
}

void            Ia::isDyingAnimation()
{
	vector3df pos = getPosition();
	vector3df ang = _node->getRotation();

	pos.Y += 3;
	ang.Y += 10;
	ang.Z -= 1;
	setPosition(pos);
	_node->setRotation(ang);
}

std::pair<int, int>	Ia::getNearestEnemy()
{
	int	x;
	int	y;
	return (std::make_pair(8, 8));
}

void		Ia::enablePostShieldState()
{
	_postShield = true;
}

void		Ia::checkPostShield()
{
	if (_postShield == true)
		if (_map->getBlock(_x, _y)->getType() == EMPTY)
		{
			_postShield = false;
			_shield = false;
		}
}
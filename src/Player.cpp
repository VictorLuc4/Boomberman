/*
** EPITECH PROJECT, 2018
** Player.cpp
** File description:
** Player
*/

#include <iostream>
#include <random>
#include "Player.hpp"

Player::Player()
{
	_PV 		= 100;
	_bombPower 	= 1;
	_score 		= 0;
	_isAlive 	= true;
	_isDying	= 0;
	_collision 	= false;
	_collisionTime	= 0;
	_push 		= false;
	_shield		= false;
	_postShield	= false;
	_MOVEMENT_SPEED = 2.2;
	_speedNb	= 0;
	_status 	= _S_STAND;
	_tmp 		= _S_STAND;
}

void	Player::loadMesh(const std::string &path)
{
	_node = _scene->addAnimatedMeshSceneNode(_scene->getMesh(path.c_str()));
	_node->setCurrentFrame(10);
	_node->setAnimationSpeed(0);
	_node->setRotation(vector3df(0,-90,0));
	_node->setScale(vector3df(14,14,14));
	_node->setMaterialFlag(EMF_LIGHTING, false);
}

void	Player::movement()
{
	_loopTime = _timer->getTime();
	vector3df pos = getPosition();
	_tmp = _S_STAND;
	checkStandingFire();
	checkCollisionTime();
	checkPostShield();
	if (_receiver->IsKeyDown(irr::KEY_KEY_R))
		restart();
	if (_isDying)
	{
		isDying();
		_engine->play2D("./music/death.wav");
		return ;
	}
	if (_receiver->IsKeyDown(_Keys.at(_A_DROPBOMB))) {
		dropBomb();
		_engine->play2D("./music/clic.wav");
	}	
        if (_receiver->IsKeyDown(_Keys.at(_A_LEFT))) {
		_tmp = _S_LEFT;
		moveLeft(pos);
		_engine->play2D("./music/pas.wav");
	}
        else if (_receiver->IsKeyDown(_Keys.at(_A_RIGHT))) {
		_tmp = _S_RIGHT;
		moveRight(pos);
		_engine->play2D("./music/pas.wav");
	}
        else if (_receiver->IsKeyDown(_Keys.at(_A_UP))) {
		_tmp = _S_UP;
		moveUp(pos);
		_engine->play2D("./music/pas.wav");
	}
        else if (_receiver->IsKeyDown(_Keys.at(_A_DOWN))) {
		_tmp = _S_DOWN;
		moveDown(pos);
		_engine->play2D("./music/pas.wav");
	}
	checkRotate(_tmp);
}

bool	Player::isAlive() const
{
	return _isAlive;
}

void	Player::dropBomb()
{
	manageTimeBomb();

	if (_timer->getTime() - _lastDropedTime < 150)
		return ;
	if (_map->getBlock(_x, _y)->getType() == BOMB
		|| _map->getBlock(_x, _y)->getType() != EMPTY)
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

void	Player::die()
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

void	Player::restart()
{
	_PV 		= 100;
	_bombPower 	= 1;
	_score 		= 0;
	_isAlive 	= true;
	_isDying	= 0;
	_collision 	= false;
	_collisionTime = 0;
	_push 		= false;
	_shield		= false;
	_postShield	= false;
	_MOVEMENT_SPEED = 2.2;
	_speedNb	= 0;
	_status 	= _S_STAND;
	_tmp 		= _S_STAND;
	_lastDropedTime = 0;
	_x 		= _xFirst;
	_y		= _yFirst;
	setPosition(vector3df(_x * 40, 2, _y * (-40)));
	std::vector<std::pair<int, bool>> tmp;
	tmp.push_back(std::make_pair(0, true));
	_Bombs = tmp;
}


void	Player::addTotalBomb()
{
	addTotalBomb(1);
}

void	Player::addPower()
{
	_bombPower += 1;
}

void	Player::addScore(const int &points)
{
	_score += points;
}

void	Player::addPush()
{
	_push = true;
}

void	Player::addSpeed()
{
	if (_speedNb <= 3) {
		_speedNb += 1;
		_MOVEMENT_SPEED += 0.4;
	}
}

void	Player::addShield()
{
	_shield = true;
}

void	Player::addGhost()
{
	_collision = true;
	_collisionTime = _timer->getTime();
}

vector3df	Player::getPosition() const
{
	return (_node->getPosition());
}

std::pair<int, int>	Player::getMapPosition() const
{
	return (std::make_pair(_x, _y));
}

int	Player::getBombPower() const
{
	return (_bombPower);
}

int 	Player::getCurrentBombNumber()
{
	int	nb = 0;

	for (auto bomb : _Bombs)
		if (bomb.second == true)
			nb += 1;
	return (nb);
}

int 	Player::getTotalBombNumber() const
{
	int	nb = 0;
	for (auto bomb : _Bombs)
		nb += 1;
	return (nb);
}

bool	Player::getPowerPush() const
{
	return (_push);
}

std::map<_ACTIONS, irr::EKEY_CODE>	Player::getKeys() const
{
	return (_Keys);
}


void	Player::setScene(ISceneManager *scene)
{
	_scene = scene;
}

void	Player::setReceiver(MyEventReceiver *receiver)
{
	_receiver = receiver;
}


void	Player::setMapPosition(const int &x, const int &y)
{
	_x = _xFirst = x;
	_y = _yFirst = y;
	setPosition(vector3df((x * 40), 2, (y * (-40))));
}

void	Player::setMap(Map *map)
{
	_map = map;
}

void	Player::setGameScene(GameScene *gameScene)
{
	_gameScene = gameScene;
	_timer =_gameScene->getTimer();
	addTotalBomb(1);
	_loopTime = _timer->getTime();
}

void	Player::setKeys(const std::map<_ACTIONS, irr::EKEY_CODE> &keys)
{
	_Keys = keys;
}

int	Player::getBombs()
{
	return this->getCurrentBombNumber();
}

int	Player::getBlast()
{
	return _bombPower;
}

int	Player::getSpeed()
{
	return _speedNb;
}

std::pair<int, int>	Player::getPos()
{
	return this->getMapPosition();
}

void	Player::setEnemyPos(const std::pair<int, int> &enemyPos)
{
}

void 	Player::setBombs(int bombs)
{
	this->addTotalBomb(bombs);
}

void	Player::setBlast(int blast)
{
	_bombPower = blast;
}

void	Player::setSpeed(int speed)
{
	_speedNb = speed;
}

void	Player::setIsAlive(bool isAlive)
{
	_isAlive = isAlive;
}


/////////////////// PRIVATE FUNCTUONS STARTS HERE
void	Player::checkRotate(_STATUS tmp)
{
	if (!_isAlive)
		return ;
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
		_node->setAnimationSpeed(0);
	}
}

void	Player::moveLeft(vector3df &pos)
{
	pos.X -= _MOVEMENT_SPEED;
	if (checkMoveMap(pos))
		setPosition(pos);
}

void	Player::moveRight(vector3df &pos)
{
	pos.X += _MOVEMENT_SPEED;
	if (checkMoveMap(pos))
		setPosition(pos);
}
void	Player::moveUp(vector3df &pos)
{
	pos.Z += _MOVEMENT_SPEED;
	if (checkMoveMap(pos))
		setPosition(pos);
}
void	Player::moveDown(vector3df &pos)
{
	pos.Z -= _MOVEMENT_SPEED;
	if (checkMoveMap(pos))
		setPosition(pos);
}

bool	Player::checkMoveMap(const vector3df &pos)
{
	float x, z;
	bool moveTo = true;

	if (_tmp == _S_LEFT) {
		x = (pos.X - 30) / 40 + 1;
		z = (((pos.Z - 20) / 40) *(-1));
		int zD = z - 0.17;
		int zU = z + 0.17;
		if (zU != zD)
			moveTo = checkAxeCornerZ((int)x, (int)z, zU, zD);
	}
	else if (_tmp == _S_UP) {
		x = (pos.X - 20)/ 40 + 1;
		z = (((pos.Z - 10) / 40) *(-1));
		int xL = x - 0.17;
		int xR = x + 0.17;
		if (xL != xR)
			moveTo = checkAxeCornerX((int)x, (int)z, xL, xR);
	}
	else if (_tmp == _S_DOWN) {
		x = (pos.X - 20) / 40 + 1;
		z = (((pos.Z - 30) / 40) * (-1));
		int xL = x - 0.17;
		int xR = x + 0.17;
		if (xL != xR)
			moveTo = checkAxeCornerX((int)x, (int)z, xL, xR);
	}
	else if (_tmp == _S_RIGHT) {
		x = (pos.X - 10)  / 40 + 1;
		z = (((pos.Z - 20) / 40) * (-1));
		int zD = z - 0.17;
		int zU = z + 0.17;
		if (zU != zD)
			moveTo = checkAxeCornerZ((int)x, (int)z, zU, zD);
	}
	TypeBlock tmpBlock = _map->getBlock(x, z)->getType();
	if (_collision == true && tmpBlock != WALL)
	{
		_x = x;
		_y = z;
		return (true);
	}
	if (tmpBlock != WALL && tmpBlock != BOX && tmpBlock != COLUMN)
	{
		if (tmpBlock == FIRE && !_postShield){
			die();
			return (false);
		}
		else if (tmpBlock == POWERUP1) {
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
			addShield();
		}
		else if (tmpBlock == POWERUP6) {
			_gameScene->erasePowerUp(_map->getBlock(x, z));
			addGhost();
		}
		if (_map->getBlock(_x, _y)->getType() == BOMB)
		{
			if (tmpBlock == BOMB && ((int)x != _x || (int)z != _y))
				return false;
			else if (moveTo) {
				_x = x;
				_y = z;
				return true;
			}
		}
		else if (tmpBlock == BOMB)
		{
				if (_tmp == _S_LEFT && _push)
					_gameScene->kickBomb(_map->getBlock(x, z), 0);
				if (_tmp == _S_RIGHT && _push)
					_gameScene->kickBomb(_map->getBlock(x, z), 1);
				if (_tmp == _S_UP && _push)
					_gameScene->kickBomb(_map->getBlock(x, z), 2);
				if (_tmp == _S_DOWN && _push)
					_gameScene->kickBomb(_map->getBlock(x, z), 3);
				return (false);
		}
		if (moveTo) {
			_x = x;
			_y = z;
			return true;
		}
		return false;
	}
	else
		return false;
}

void		Player::addTotalBomb(const int &nb)
{
	for (int i = 0; i < nb; i += 1)
		_Bombs.push_back(std::make_pair(0, true));
}

void		Player::manageTimeBomb()
{
	int	t = _timer->getTime();

	for (auto &bomb : _Bombs)
		if (t - bomb.first > 3000)
			bomb.second = true;
}

void	Player::setPosition(const vector3df &pos)
{
	_node->setPosition(vector3df(pos.X, pos.Y, pos.Z));
}

void	Player::checkStandingFire()
{
	if (_map->getBlock(_x, _y)->getType() == FIRE)
		die();
}

bool	Player::isDying()
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
	return (true);
}

void	Player::isDyingAnimation()
{
	vector3df pos = getPosition();
	vector3df ang = _node->getRotation();
	pos.Y += 4;
	ang.Y += 10;
	if (_status == _S_LEFT) {
		pos.X += 3;
		ang.Z -= 1;
	}
	else if (_status ==_S_RIGHT) {
		pos.X -= 3;
		ang.Z += 1;

	}
	else if (_status == _S_UP) {
		pos.Z -= 3;
		ang.Z += 1;
	}
	else if (_status == _S_DOWN) {
		pos.Z += 3;
		ang.Z -= 1;
	}
	setPosition(pos);
	_node->setRotation(ang);
}

bool		Player::checkAxeCornerX(const int &x, const int &z, const int xL, const int xR)
{
	if (x != xL)
	{
		TypeBlock tmpBlockL = _map->getBlock(xL, z)->getType();
		if (tmpBlockL != EMPTY && tmpBlockL != BOMB)
			return false;
		else
			return true;
	}
	else if (x != xR)
	{
		TypeBlock tmpBlockR = _map->getBlock(xR, z)->getType();
		if (tmpBlockR != EMPTY && tmpBlockR != BOMB)
			return false;
		else
			return true;
	}
	return false;
}

bool		Player::checkAxeCornerZ(const int &x, const int &z, const int zU, const int zD)
{
	if (z != zU)
	{
		TypeBlock tmpBlockL = _map->getBlock(x, zU)->getType();
		if (tmpBlockL != EMPTY && tmpBlockL != BOMB)
			return false;
		else
			return true;
	}
	else if (z != zD)
	{
		TypeBlock tmpBlockR = _map->getBlock(x, zD)->getType();
		if (tmpBlockR != EMPTY && tmpBlockR != BOMB)
			return false;
		else
			return true;
	}
	return false;
}

void		Player::checkCollisionTime()
{
	if (_collision)
	{
		if (_timer->getTime() - _collisionTime > 6000)
		{
			if (checkNearEmpty())
			{
				_collision = false;
				_collisionTime = 0;
			}
		}
	}
}

bool		Player::checkNearEmpty()
{
	if (_map->getBlock(_x, _y)->getType() == EMPTY)
		return true;
	else
	{
		vector3df ang = _node->getRotation();
		vector3df pos = _node->getPosition();
		float x = ((pos.X - 20) / 40 + 1) - _x;
		float z = (((pos.Z - 20) / 40) *(-1)) - _y;
		int tmpX = _x;
		int tmpY = _y;
		_POSTGHOST XG;
		_POSTGHOST YG;
		if (x <= 0.49)
			XG = _G_LEFT;
		else if (x > 0.49 && x <= 1)
			XG = _G_RIGHT;
		if (z <= 0.49)
			YG = _G_UP;
		else if (z > 0.49 && z <= 1)
			YG = _G_DOWN;
		tryMoveToEmpty(XG, YG);
		if (tmpX != _x || tmpY != _y)
			return true;
		if (checkRandomEmpty())
			return true;
	}
	return false;
}

void		Player::tryMoveToEmpty(_POSTGHOST XG, _POSTGHOST YG)
{
	if (XG == _G_LEFT && YG == _G_UP)
	{
		if (_map->getBlock(_x - 1, _y - 1)->getType() == EMPTY)
			setMapPosition(_x - 1, _y - 1);
		else if (_map->getBlock(_x - 1, _y)->getType() == EMPTY)
			setMapPosition(_x - 1, _y);
		else if (_map->getBlock(_x - 1, _y + 1)->getType() == EMPTY)
			setMapPosition(_x - 1, _y + 1);
	}
	else if (XG == _G_RIGHT && YG == _G_UP)
	{
		if (_map->getBlock(_x + 1, _y - 1)->getType() == EMPTY)
			setMapPosition(_x + 1, _y - 1);
		else if (_map->getBlock(_x + 1, _y)->getType() == EMPTY)
			setMapPosition(_x +1, _y);
		else if (_map->getBlock(_x + 1, _y + 1)->getType() == EMPTY)
			setMapPosition(_x + 1, _y + 1);
	}
	else if (XG == _G_RIGHT && YG == _G_DOWN)
	{
		if (_map->getBlock(_x + 1, _y + 1)->getType() == EMPTY)
			setMapPosition(_x + 1, _y + 1);
		else if (_map->getBlock(_x + 1, _y)->getType() == EMPTY)
			setMapPosition(_x - 1, _y);
		else if (_map->getBlock(_x, _y - 1)->getType() == EMPTY)
			setMapPosition(_x, _y - 1);
	}
	else if (XG ==_G_LEFT && YG == _G_DOWN)
	{
		if (_map->getBlock(_x - 1, _y + 1)->getType() == EMPTY)
			setMapPosition(_x - 1, _y + 1);
		else if (_map->getBlock(_x - 1, _y)->getType() == EMPTY)
			setMapPosition(_x - 1, _y);
		else if (_map->getBlock(_x - 1, _y - 1)->getType() == EMPTY)
			setMapPosition(_x - 1, _y - 1);
	}
}

bool		Player::checkRandomEmpty()
{
	if (_map->getBlock(_x - 1, _y)->getType() == EMPTY) {
		setMapPosition(_x - 1, _y);
		return true;
	}
	else if (_map->getBlock(_x + 1, _y)->getType() == EMPTY) {
		setMapPosition(_x + 1, _y);
		return true;
	}
	else if (_map->getBlock(_x, _y - 1)->getType() == EMPTY) {
		setMapPosition(_x, _y - 1);
		return true;
	}
	else if (_map->getBlock(_x, _y + 1)->getType() == EMPTY) {
		setMapPosition(_x, _y + 1);
		return true;
	}
	return false;
}

void		Player::enablePostShieldState()
{
	_postShield = true;
}

void		Player::checkPostShield()
{
	if (_postShield == true)
		if (_map->getBlock(_x, _y)->getType() == EMPTY)
		{
			_postShield = false;
			_shield = false;
		}
}
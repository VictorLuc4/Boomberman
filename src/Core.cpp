/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Core
*/

#include "Core.hpp"
#include "GameScene.hpp"
#include "MenuScene.hpp"

Core::Core(InfoMenu *infoMenu)
{
	_gfx = new Graphical;
	_infoMenu = infoMenu;
	_config = new Config;
}

Core::~Core()
{
	_gfx->quit();
}

void	Core::createPlayer()
{
}

void	Core::createIA()
{
}

void	Core::generateMap()
{
}

void	Core::getMap()
{
}

void	Core::loadMapFromFile()
{
}

void	Core::playGame()
{
}

void	Core::startGraphical()
{
	_gfx->start(_infoMenu);
}

void	Core::initCore(MenuManager *menuManager)
{
	_scenes.emplace(GAME_SCENE, new GameScene(menuManager));
	_scenes.emplace(MENU_SCENE, new MenuScene(menuManager));

	_scenes[MENU_SCENE]->setGraphics(_gfx);
	_scenes[MENU_SCENE]->setInfoMenu(_infoMenu);
	_scenes[MENU_SCENE]->load();
	_scenes[MENU_SCENE]->setCameraPos(vector3df(90, 63, 0), vector3df(0, 60, 0));
	_currentScene = MENU_SCENE;
}

void	Core::drawScene()
{
	if (_currentScene != _infoMenu->getCurrentScene())
	{
		_scenes[MENU_SCENE]->dropMusic();
		_currentScene = _infoMenu->getCurrentScene();

		_scenes[GAME_SCENE]->setInfoMenu(_infoMenu);
		_scenes[GAME_SCENE]->setGraphics(_gfx);
		_scenes[GAME_SCENE]->load();
		_scenes[GAME_SCENE]->setCameraPos(vector3df(270, 500, -490), vector3df(270, -250, 0));

		initPlayers();
	}
	_scenes[_infoMenu->getCurrentScene()]->draw();
	if (_infoMenu->getSaved() == true) {
		_infoMenu->setSaved(false);
		this->saveGame();
	}
	if (!_players.empty()) {
		int i = 0;
		for (auto &it: _players) {
			if (it)
				if (it->isAlive()) {
					it->setEnemyPos(_players[_players.size() - 1]->getMapPosition());
					it->movement();
					i++;
				}
		}
		if (i <= 1)
			_infoMenu->setCurrentMenu(VICTORY);
	}
}

void	Core::saveGame()
{
	std::vector<std::string> map = _scenes[GAME_SCENE]->getMap()->getMapTxt();
	std::vector<CharacValue> charac = initCharac();

	_config->saveConf("continue.conf", map, charac);
}

std::vector<CharacValue>	Core::initCharac()
{
	std::vector<CharacValue> charac;

	for (int i = 0; i != _players.size(); i++) {
		charac.push_back(getCharacFromPlayer(_players[i], i));
	}
	return charac;
}

CharacValue		Core::getCharacFromPlayer(ICharacter *player, int i)
{
	CharacValue tmp;
	std::map<PlayerState, std::string> map;

	map.emplace(IA,"IA");
	map.emplace(PLAYER, "PLAYER");
	map.emplace(NONE, "NONE");
	std::vector<PlayerState> players = _infoMenu->getPlayers();

	tmp.bombs = player->getBombs();
	tmp.blast = player->getBlast();
	tmp.speed = player->getSpeed();
	tmp.push = false;
	tmp.Pos = player->getPos();
	tmp.isAlive = player->isAlive();
	tmp.type = map[players[i]];
	return tmp;
}

void	Core::initPlayers()
{
	std::vector<CharacValue> players = _infoMenu->getPlayersLoaded();

	int	nbPlayers = 0;
	std::map<_ACTIONS, irr::EKEY_CODE>    mapKeyPlayer1;
        mapKeyPlayer1.emplace(_A_RIGHT, irr::KEY_KEY_D);
        mapKeyPlayer1.emplace(_A_LEFT, irr::KEY_KEY_Q);
        mapKeyPlayer1.emplace(_A_UP, irr::KEY_KEY_Z);
        mapKeyPlayer1.emplace(_A_DOWN, irr::KEY_KEY_S);
        mapKeyPlayer1.emplace(_A_DROPBOMB, irr::KEY_SPACE);

	std::map<_ACTIONS, irr::EKEY_CODE>    mapKeyPlayer2;
        mapKeyPlayer2.emplace(_A_RIGHT, irr::KEY_RIGHT);
        mapKeyPlayer2.emplace(_A_LEFT, irr::KEY_LEFT);
        mapKeyPlayer2.emplace(_A_UP, irr::KEY_UP);
        mapKeyPlayer2.emplace(_A_DOWN, irr::KEY_DOWN);
        mapKeyPlayer2.emplace(_A_DROPBOMB, irr::KEY_RETURN);

        Map *map = _scenes[GAME_SCENE]->getMap();

	for (int i = 0; i != players.size(); i++) {
		if (players[i].type != "NONE") {
			ICharacter *newPlayer;
			std::cout << "players TYPE ==  --------------------------------------------------------------------------------------------------------------------------------" << players[i].type << "\n";
			if (players[i].type == "PLAYER")
				newPlayer = new Player;
			else
				newPlayer = new Ia;
        		newPlayer->setScene(_scenes[GAME_SCENE]->getScene());
        		newPlayer->setGameScene((GameScene *)_scenes[GAME_SCENE]);
        		newPlayer->setMap(map);
        		newPlayer->setReceiver(_gfx->getReceiver());
        		newPlayer->loadMesh("media/mediaGame/file3D/BomberMan.b3d");
        		newPlayer->setMapPosition(players[i].Pos.first, players[i].Pos.second);
			if (nbPlayers == 0)
        			newPlayer->setKeys(mapKeyPlayer1);
			else if (nbPlayers == 1)
				newPlayer->setKeys(mapKeyPlayer2);
			newPlayer->setBlast(players[i].blast);
			newPlayer->setIsAlive(players[i].isAlive);
			newPlayer->setBombs(players[i].bombs);
			if (players[i].push == true) {
				newPlayer->addPush();
			}
			nbPlayers += 1;
			_players.push_back(newPlayer);
		}
	}
}

void	Core::setCurrentScene(SceneType sceneType)
{
	_currentScene = sceneType;
}

void	Core::setInfoMenu(InfoMenu *infoMenu)
{
	_infoMenu = infoMenu;
}

Graphical *Core::getGraphical()
{
	return _gfx;
}
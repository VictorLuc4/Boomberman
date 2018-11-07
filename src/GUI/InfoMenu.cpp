/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** InfoMenu
*/

#include "InfoMenu.hpp"

InfoMenu::InfoMenu()
{
	_config = new Config;

	_config->loadFile("base.conf");
	_playersLoad = _config->getCharac();
	std::cout << "players loaded == " << _playersLoad.size() << "\n";
	_currentMenu = MAIN_MENU;
	_currentScene = MENU_SCENE;
	_mapSize = 2;
	_players.push_back(PLAYER);
	_players.push_back(PLAYER);
	_players.push_back(IA);
	_players.push_back(IA);
	std::vector<std::string> tmp;
	_mapTxt = tmp;
}

MenuType	InfoMenu::getCurrentMenu()
{
	return _currentMenu;
}

void		InfoMenu::setCurrentMenu(const MenuType &newMenu)
{
	_currentMenu = newMenu;
}

SceneType 	InfoMenu::getCurrentScene()
{
	return _currentScene;
}

void		InfoMenu::setCurrentScene(const SceneType &newScene)
{
	_currentScene = newScene;
}

void		InfoMenu::setMapSize(const int &mapSize)
{
	_mapSize = mapSize;
}

int		InfoMenu::getMapSize()
{
	return _mapSize;
}

std::vector<PlayerState> 	InfoMenu::getPlayers()
{
	return _players;
}

void		InfoMenu::incrPlayerState(int pos)
{
	_playersLoad[pos].type == "IA" ? _playersLoad[pos].type = "PLAYER" : _playersLoad[pos].type == "PLAYER" ? _playersLoad[pos].type = "NONE" : _playersLoad[pos].type == "NONE" ? _playersLoad[pos].type = "IA" : 0;
	_players[pos] == IA ? _players[pos] = PLAYER : _players[pos] == PLAYER ? _players[pos] = NONE : _players[pos] == NONE ? _players[pos] = IA : 0;
}

void		InfoMenu::setInfoMenuFromFile()
{
	Config *config = new Config;
	std::map<std::string, PlayerState> map;

	map.emplace("IA", IA);
	map.emplace("PLAYER", PLAYER);
	map.emplace("NONE", NONE);

	config->loadFile("continue.conf");
	_mapTxt = config->getMap();
	std::cout << "CONTINUE PRINTING MAP -------------------------------------------------------------------------------------------------------------------\n";
	for (int i = 0; i != _mapTxt.size(); i++) {
		std::cout << _mapTxt[i] << "\n";
	}
	_playersLoad = config->getCharac();
	for (int i = 0; i != _players.size(); i++) {
		_players[i] = map[_playersLoad[i].type];
	}
}

bool		InfoMenu::getSaved()
{
	return _saved;
}

void		InfoMenu::setSaved(bool saved)
{
	_saved = saved;
}

std::vector<std::string> InfoMenu::getMapTxt()
{
	return _mapTxt;
}

std::vector<CharacValue> InfoMenu::getPlayersLoaded()
{
	return _playersLoad;
}
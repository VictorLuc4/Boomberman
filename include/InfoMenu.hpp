/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** InfoMenu
*/

#ifndef INFOMENU_HPP_
	#define INFOMENU_HPP_
	#include <iostream>
	#include <vector>
	#include "Config.hpp"

enum MenuType
{
	MAIN_MENU,
	MAIN_MENU_AFTER_PLAY,
	OPTION_MAIN_MENU,
	NEW_GAME_MENU,
	HUD,
	PAUSE_MENU,
	VICTORY
};

enum ButtonType
{
	PLAY_BUTTON,
	OPTION_BUTTON,
	CONTINUE_BUTTON,
	NEW_GAME_BUTTON,
	PAUSE_BUTTON,
	QUIT_BUTTON,
	RETURN_BUTTON,
	SCROLL_BAR,
	SELECT_PLAYER1_STATE_BUTTON,
	SELECT_PLAYER2_STATE_BUTTON,
	SELECT_PLAYER3_STATE_BUTTON,
	SELECT_PLAYER4_STATE_BUTTON,
	SWITCH_TO_VICTORY,
	SCREEN_SIZE,
	VOLUME,
	LANGUAGE,
	RETURN_BUTTON_MENU,
	SCROLL_BAR_SETTINGS,
	MENU_BUTTON,
	RESTART_BUTTON,
	SAVE_GAME
};

enum PlayerState
{
	IA,
	PLAYER,
	NONE
};

enum SceneType
{
	GAME_SCENE,
	MENU_SCENE
};

class InfoMenu {
	public:
		InfoMenu();
		~InfoMenu() = default;

		MenuType getCurrentMenu();
		void	setCurrentMenu(const MenuType &newMenu);

		SceneType getCurrentScene();
		void	setCurrentScene(const SceneType &newScene);

		int	getMapSize();
		void	setMapSize(const int &mapSize);

		std::vector<std::string> getMapTxt();

		std::vector<PlayerState>	getPlayers();
		void	incrPlayerState(int pos);

		std::vector<CharacValue> getPlayersLoaded();

		void	setInfoMenuFromFile();
		void	setSaved(bool saved);
		bool	getSaved();
	private:
		MenuType _currentMenu;
		SceneType _currentScene;
		int	_mapSize;
		std::vector<PlayerState> _players;
		std::vector<CharacValue> _playersLoad;
		std::vector<std::string> _mapTxt;
		Config			*_config;
		bool		_saved;
};

#endif /* !INFOMENU_HPP_ */

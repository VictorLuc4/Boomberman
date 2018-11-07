/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Core
*/

#ifndef CORE_HPP_
	#define CORE_HPP_
	#include "Graphical.hpp"
	#include "ICharacter.hpp"
	#include "Player.hpp"
	#include "IA.hpp"
	#include "MenuManager.hpp"
	#include "IScene.hpp"
	#include "MyEventReceiver.hpp"
	#include <map>
	#include "Config.hpp"

class Core {
	public:
		Core(InfoMenu *infoMenu);
		~Core();
		void createPlayer();
		void createIA();

		void generateMap();
		void getMap();
		void loadMapFromFile();

		void playGame();
		void		setCurrentMenu(const MenuType &newMenu);

		Graphical	*getGraphical();
		void		startGraphical();
		void		initCore(MenuManager *);
		void		drawScene();

		void		setCurrentScene(SceneType sceneType);
		void		setInfoMenu(InfoMenu *);
		void		initPlayers();
		void		saveGame();
		std::vector<CharacValue> initCharac();
		CharacValue		getCharacFromPlayer(ICharacter *player, int i);
	private:
		// void		updatePlayersPos();
		Graphical *_gfx;
		SceneType _currentScene;
		std::map<SceneType, IScene *> _scenes;
		InfoMenu	*_infoMenu;
		std::vector<ICharacter *> _players;
		Config		*_config;
		// std::vector<
		/*Map _map;*/
		/*vector<perso> _persos;*/
		/*Menu _menu;*/
		/*Graphical _gfx;*/
};

#endif /* !CORE_HPP_ */
/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Menu
*/

#ifndef MENU_HPP_
	#define MENU_HPP_
	#include "IScene.hpp"

class Menu {
	public:
		Menu();
		~Menu();
		void		startMenu(Graphical *irr);
		void		exitMenu();
		void		option();
		void		playGame();
		void		continueGame();

		void		setScene(IScene *scene);
		IScene		*getScene() const;
	private:
		Graphical			*_irr;
		IScene				*_scene;

};

#endif /* !MENU_HPP_ */
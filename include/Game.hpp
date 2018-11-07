/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Game
*/

#ifndef GAME_HPP_
	#define GAME_HPP_
	#include "Graphical.hpp"
	#include "IScene.hpp"

class Game {
	public:
		Game(Graphical *gfx);
		~Game();

		void		play();
		void		pause();

		void		setScene(IScene *scene);
		IScene		*getScene() const;
	private:
		Graphical			*_gfx;
		IScene				*_scene;
};

#endif /* !GAME_HPP_ */

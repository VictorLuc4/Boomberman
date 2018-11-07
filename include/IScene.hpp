/*
** EPITECH PROJECT, 2018
** VK
** File description:
** Scene Interface declaration
*/

#ifndef ISCENE_HPP_
	#define ISCENE_HPP_

#include "Graphical.hpp"
#include "Map.hpp"
#include "InfoMenu.hpp"

class IScene
{
	public:
		virtual		~IScene() = default;
		virtual void	setGraphics(Graphical *) = 0;
		virtual void	load() = 0;
		virtual	void	draw() = 0;
		virtual	void	setCameraPos(const vector3df &pos, const vector3df &mir) = 0;
		virtual void	setInfoMenu(InfoMenu *) = 0;
		virtual void	dropMusic() = 0;

		virtual ISceneManager *getScene() = 0;
		virtual Map		*getMap() = 0;

		virtual void	exitWindow() = 0;
};

#endif /* !ISCENE_HPP_ */

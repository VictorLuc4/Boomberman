/*
** EPITECH PROJECT, 2018
** VK
** File description:
** test cmake
*/

#include "Core.hpp"

int 			main()
{
	InfoMenu	*infoMenu = new InfoMenu;
	Core	*core = new Core(infoMenu);
	MenuManager *menuManager;

	core->startGraphical();
	core->setInfoMenu(infoMenu);
	menuManager = new MenuManager(core->getGraphical()->getDevice(), infoMenu);
	core->initCore(menuManager);
	while (core->getGraphical()->isRunning())
		core->drawScene();
	return (0);
}

/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Menu
*/

#include "Menu.hpp"

Menu::Menu()
{
}

Menu::~Menu()
{
}

void	Menu::startMenu(Graphical *irr)
{
	_irr = irr;
}

void	Menu::exitMenu()
{
}

void	Menu::option()
{
}

void	Menu::playGame()
{
}

void	Menu::continueGame()
{
}

void	Menu::setScene(IScene *scene)
{
	_scene = scene;
}

IScene	*Menu::getScene() const
{
	return (_scene);
}

//PRIVATE Function

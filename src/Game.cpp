/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Game
*/

#include "Game.hpp"

Game::Game(Graphical *gfx): _gfx(gfx)
{
}

Game::~Game()
{
}

void	Game::play()
{
}

void	Game::pause()
{
}

void	Game::setScene(IScene *scene)
{
	_scene = scene;
}

IScene	*Game::getScene() const
{
	return _scene;
}
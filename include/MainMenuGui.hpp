/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** MainMenuGui
*/

#ifndef MAINMENUGUI_HPP_
	#define MAINMENUGUI_HPP_
	#include "MenuGui.hpp"

class MainMenuGui : public MenuGui
{
	public:
		MainMenuGui(SAppContext *context, InfoMenu *infoMenu);
		~MainMenuGui() = default;
};

#endif /* !MAINMENUGUI_HPP_ */

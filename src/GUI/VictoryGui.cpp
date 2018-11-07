/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** VictoryGui
*/

#include "VictoryGui.hpp"


VictoryGui::VictoryGui(SAppContext *context, InfoMenu *infoMenu) : MenuGui(context, infoMenu)
{

	irr::s32 X = 1920 / 2;
	irr::s32 Y = 1080 / 2;

	X = X + X / 4;
	_background = Environment->addImage(rect<irr::s32>(0, 0, 1920, 1080), this);
	_background->setImage(_context->device->getVideoDriver()->getTexture("media/mediaMenu/file2D/VictoryBackGround.png"));
	_background->setScaleImage(true);

	//creating all buttons
	_buttons.emplace(RESTART_BUTTON, Environment->addButton(rect<irr::s32>(500, Y + 40, 850, Y + 60 + 30), this, RESTART_BUTTON, L"", L"restartBouton"));
	_buttons.emplace(MENU_BUTTON, Environment->addButton(rect<irr::s32>(500 + 285 + 300, Y + 40, 850 + 300 + 300, Y + 60 + 30), this, MENU_BUTTON, L"", L"menuBouton"));
	//setting image
	this->setButtonImage(RESTART_BUTTON, "media/mediaMenu/file2D/restartBouton");
	this->setButtonImage(MENU_BUTTON, "media/mediaMenu/file2D/menuBouton");
}
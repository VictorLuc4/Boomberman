/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** MainMenuGui
*/

#include "MainMenuGui.hpp"

MainMenuGui::MainMenuGui(SAppContext *context, InfoMenu *infoMenu) : MenuGui(context, infoMenu)
{
	irr::s32 X = 1920 / 2;
	irr::s32 Y = 1080 / 2;

	//add image to background
	_background = Environment->addImage(rect<irr::s32>(0, 0, 1920, 1080), this);
	_background->setImage(_context->device->getVideoDriver()->getTexture("media/mediaMenu/backgroundMenu.png"));
	_background->setScaleImage(true);

	X = X + X / 4;

	IGUIImage *title = Environment->addImage(rect<irr::s32>(X - 100, 100, X + 500, 100 + 250), this);
	title->setImage(_context->device->getVideoDriver()->getTexture("media/bombermanTitle.png"));
	title->setScaleImage(true);


	//creating all buttons
	_buttons.emplace(NEW_GAME_BUTTON, Environment->addButton(rect<irr::s32>(X, Y - 150, X + 400, (Y + 50) + 200), this, NEW_GAME_BUTTON, L"", L"PLay"));
	_buttons.emplace(CONTINUE_BUTTON, Environment->addButton(rect<irr::s32>(X, Y, X + 400, (Y + 50) + 200), this, CONTINUE_BUTTON, L"", L"PLay"));
	_buttons.emplace(OPTION_BUTTON, Environment->addButton(rect<irr::s32>(X, Y + 150, X + 400, (Y + 100) + 120 + 200), this, OPTION_BUTTON, L"", L"Option"));
	_buttons.emplace(QUIT_BUTTON, Environment->addButton(rect<irr::s32>(X, Y + 300, X + 400, (Y + 150) + 120 + 200), this, QUIT_BUTTON, L"", L"Exit"));

	//setting image
	this->setButtonImage(CONTINUE_BUTTON, "media/mediaMenu/file2D/continue");
	this->setButtonImage(NEW_GAME_BUTTON, "media/mediaMenu/file2D/newgame");
	this->setButtonImage(OPTION_BUTTON, "media/mediaMenu/file2D/settings");
	this->setButtonImage(QUIT_BUTTON, "media/mediaMenu/file2D/exit");
}
/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** HudGui
*/

#include "HudGui.hpp"


HudGui::HudGui(SAppContext *context, InfoMenu *infoMenu) : MenuGui(context, infoMenu)
{
	IGUIImage	*player1;
	IGUIImage	*player2;
	IGUIImage	*player3;
	IGUIImage	*player4;
	irr::s32 X = 1920 / 2;
	irr::s32 Y = 1080 / 2;

	X = X + X / 4;
	// //add image to background
	// _background = Environment->addImage(rect<irr::s32>(0, 0, 1920, 1080), this);
	// _background->setImage(_context->device->getVideoDriver()->getTexture("media/mediaGame/file2D/backgroundGame.jpg"));
	// _background->setScaleImage(true);
	
	//creating all buttons
	player1 = Environment->addImage(rect<irr::s32>(100, 50, 350, 450), this);
	player1->setImage(_context->device->getVideoDriver()->getTexture("media/mediaGame/file2D/GamePlayer1.png"));
	player1->setScaleImage(true);

	player2 = Environment->addImage(rect<irr::s32>(X + 350, 50, X + 350 + 250, 450), this);
	player2->setImage(_context->device->getVideoDriver()->getTexture("media/mediaGame/file2D/GamePlayer2.png"));
	player2->setScaleImage(true);

	player3 = Environment->addImage(rect<irr::s32>(100, (Y + 100), 350, Y + 100 + 400), this);
	player3->setImage(_context->device->getVideoDriver()->getTexture("media/mediaGame/file2D/GamePlayer3.png"));
	player3->setScaleImage(true);

	player4 = Environment->addImage(rect<irr::s32>((X + 350), (Y + 100),  (X + 350 + 250), (Y + 100 + 400)), this);
	player4->setImage(_context->device->getVideoDriver()->getTexture("media/mediaGame/file2D/GamePlayer4.png"));
	player4->setScaleImage(true);
	
	// _buttons.emplace(PAUSE_BUTTON, Environment->addButton(rect<irr::s32>(0, 400, 300, 400 + 200), this, SWITCH_TO_VICTORY, L"", L"pauseButton"));
	// //setting image
	// this->setButtonImage(PAUSE_BUTTON, "media/mediaGame/file2D/pauseButton");
	_buttons.emplace(SAVE_GAME, Environment->addButton(rect<irr::s32>(0, 400, 300, 400 + 200), this, SAVE_GAME, L"", L"Return"));
	//setting image
	this->setButtonImage(SAVE_GAME, "media/mediaMenu/file2D/save");
}
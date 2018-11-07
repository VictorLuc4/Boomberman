/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** OptionMenuGui
*/

#include "OptionMenuGui.hpp"


OptionMenuGui::OptionMenuGui(SAppContext *context, InfoMenu *infoMenu) : MenuGui(context, infoMenu)
{

	irr::s32 X = 1920 / 2;
	irr::s32 Y = 1080 / 2;

	X = X + X / 4;
	//add image to background
	_background = Environment->addImage(rect<irr::s32>(0, 0, 1920, 1080), this);
	_background->setImage(_context->device->getVideoDriver()->getTexture("media/mediaMenu/file2D/backgroundSettings.png"));
	_background->setScaleImage(true);

	IGUIScrollBar* scrollbar = Environment->addScrollBar(true,
			rect<irr::s32>(500 + 285, Y + 40, 850 + 300, Y + 60 + 30), this, SCROLL_BAR_SETTINGS);
	scrollbar->setMax(100);
	scrollbar->setMin(0);
	scrollbar->setPos(50);
	//creating all buttons
	_buttons.emplace(RETURN_BUTTON_MENU, Environment->addButton(rect<irr::s32>(0, 0, 500, 150), this, RETURN_BUTTON_MENU, L"", L"Return"));
	//setting image
	this->setButtonImage(RETURN_BUTTON_MENU, "media/mediaMenu/file2D/return");
}
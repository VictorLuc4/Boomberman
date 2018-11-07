/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** MenuGui
*/

#include "MenuGui.hpp"

MenuGui::MenuGui(SAppContext *context, InfoMenu *infoMenu) : IGUIElement(context->type, context->device->getGUIEnvironment(), context->parent, context->id, context->recta)
{
	_context = context;
	_driver = context->device->getVideoDriver();
	_infoMenu = infoMenu;
}

void	MenuGui::draw()
{
	if (isVisible()) {
			list<IGUIElement*>::Iterator it = Children.begin();
			for (; it != Children.end(); ++it)
				(*it)->draw();
	}
}

void	MenuGui::setButtonImage(ButtonType buttonId, const std::string &path)
{
	std::string pathNotPushed = path + ".png";

	IGUIButton *tmp = reinterpret_cast<IGUIButton *>((_buttons[buttonId]));
	tmp->setImage(_context->device->getVideoDriver()->getTexture(pathNotPushed.c_str()));
	tmp->setMaxSize(dimension2du(400, 150));
	tmp->setScaleImage(true);
	tmp->setUseAlphaChannel(true);
	tmp->setDrawBorder(0);
}
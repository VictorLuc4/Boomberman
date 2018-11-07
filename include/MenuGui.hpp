/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** MenuGui
*/

#ifndef MENUGUI_HPP_
	#define MENUGUI_HPP_
	#include "InfoMenu.hpp"
	#include "Graphical.hpp"

typedef struct SAppContext
{
	irr::IrrlichtDevice *device;
	EGUI_ELEMENT_TYPE type;
	MenuType id;
	IGUIElement *parent;
	rect<irr::s32> recta;
}		SAppContext;

class MenuGui : public IGUIElement {
	public:
		MenuGui(SAppContext *context, InfoMenu *infoMenu);
		~MenuGui() = default;

		virtual void	draw();
		virtual void	setButtonImage(ButtonType buttonId, const std::string &path);
		
	protected:
		IGUIImage	*_background;
		std::map<ButtonType, IGUIElement *> _buttons;
		SAppContext	*_context;
		InfoMenu	*_infoMenu;
		IGUIStaticText *_mapSize;
		IVideoDriver	*_driver;
};

#endif /* !MENUGUI_HPP_ */

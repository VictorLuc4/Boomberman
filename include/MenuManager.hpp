/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** MenuManager
*/

#ifndef MENUMANAGER_HPP_
	#define MENUMANAGER_HPP_
	#include "MenuGui.hpp"
	#include "MainMenuGui.hpp"
	#include "OptionMenuGui.hpp"
	#include "NewGameMenuGui.hpp"
	#include "HudGui.hpp"
	#include "VictoryGui.hpp"

class MenuManager {
	public:
		MenuManager(irr::IrrlichtDevice *, InfoMenu *infoMenu);
		~MenuManager() = default;

		MenuGui	*getCurrentGui();
		MenuGui *getPreviousGui() const;
		InfoMenu *getInfoMenu();
	private:
		MenuGui	*_currentGui;
		MenuGui	*_previousGui;
		std::map<MenuType, MenuGui *> _menus;
		irr::IrrlichtDevice	*_device;
		InfoMenu		*_infoMenu;
};

#endif /* !MENUMANAGER_HPP_ */
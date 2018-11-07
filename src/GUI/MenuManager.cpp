/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** MenuManager
*/

#include "MenuManager.hpp"

MenuManager::MenuManager(irr::IrrlichtDevice *device, InfoMenu *infoMenu) : _device(device), _infoMenu(infoMenu)
{
	SAppContext context;

	context.device = _device;
	context.type = EGUIET_ELEMENT;
	context.id = MAIN_MENU;
	context.parent = _device->getGUIEnvironment()->getRootGUIElement();
	context.recta = rect<irr::s32>(0, 0, 1920, 1080);
	_menus.emplace(VICTORY, new VictoryGui(&context, infoMenu));
	_menus.emplace(HUD, new HudGui(&context, infoMenu));
	_menus.emplace(OPTION_MAIN_MENU, new OptionMenuGui(&context, infoMenu));
	_menus.emplace(NEW_GAME_MENU, new NewGameMenuGui(&context, infoMenu));
	_menus.emplace(MAIN_MENU, new MainMenuGui(&context, infoMenu));
	//_menus.emplace(NEW_GAME_MENU, new NewGameMenu)
	//_menus.emplace(HUD_USER, new Hud)
	//_menus.emplace(PAUSE_MENU, new PauseMenu)
	_currentGui = _menus[MAIN_MENU];
	_previousGui = _menus[MAIN_MENU];
}

MenuGui	*MenuManager::getCurrentGui()
{
	if (_menus[_infoMenu->getCurrentMenu()] != _currentGui) {
		_previousGui = _currentGui;
		_currentGui = _menus[_infoMenu->getCurrentMenu()];
		_currentGui->setVisible(true);
		_previousGui->setVisible(false);
	}
	return _currentGui;
}

MenuGui	*MenuManager::getPreviousGui() const
{
	return _previousGui;
}

InfoMenu *MenuManager::getInfoMenu()
{
	return _infoMenu;
}
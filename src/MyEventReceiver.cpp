/*
** EPITECH PROJECT, 2018
** VK
** File description:
** MyEventReceiver class implementation
*/

#include "MyEventReceiver.hpp"
#include <iostream>

MyEventReceiver::MyEventReceiver(InfoMenu *infoMenu)
{
	_infoMenu = infoMenu;
	for (irr::u32 i=0; i<irr::KEY_KEY_CODES_COUNT; ++i)
		KeyIsDown[i] = false;
}

bool		MyEventReceiver::OnEvent(const irr::SEvent& event)
{

	if (event.EventType == irr::EET_KEY_INPUT_EVENT) {
		KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
	}
	checkButtonAction(event);
	return false;
}

bool		MyEventReceiver::checkButtonAction(const irr::SEvent &event)
{
	if (event.EventType == irr::EET_GUI_EVENT) {
		irr::s32 id = event.GUIEvent.Caller->getID();

		switch(event.GUIEvent.EventType)
		{
			case EGET_SCROLL_BAR_CHANGED:
				if (id == SCROLL_BAR)
				{
					irr::s32 pos = ((IGUIScrollBar*)event.GUIEvent.Caller)->getPos();
					_infoMenu->setMapSize(pos);
				}
				break;
			case EGET_BUTTON_CLICKED:
				switch(id)
				{
					case NEW_GAME_BUTTON:
						_engine->play2D("./music/button.wav");
						_infoMenu->setCurrentMenu(NEW_GAME_MENU);
						return true;
					case CONTINUE_BUTTON:
						_infoMenu->setInfoMenuFromFile();
						_infoMenu->setCurrentMenu(HUD);
						_infoMenu->setCurrentScene(GAME_SCENE);
						return true;
					case OPTION_BUTTON:
						_engine->play2D("./music/button.wav");
						_infoMenu->setCurrentMenu(OPTION_MAIN_MENU);
						return true;
					case RETURN_BUTTON:
						_infoMenu->setCurrentMenu(MAIN_MENU);
						_engine->play2D("./music/button.wav");
						return true;
					case PLAY_BUTTON:
						_infoMenu->setCurrentScene(GAME_SCENE);
						_infoMenu->setCurrentMenu(HUD);
						_engine->play2D("./music/button.wav");
						return true;
					case SELECT_PLAYER1_STATE_BUTTON:
						_engine->play2D("./music/clic.wav");
						_infoMenu->incrPlayerState(0);
						return true;
					case SELECT_PLAYER2_STATE_BUTTON:
						_engine->play2D("./music/clic.wav");
						_infoMenu->incrPlayerState(1);
						return true;
					case SELECT_PLAYER3_STATE_BUTTON:
						_engine->play2D("./music/clic.wav");
						_infoMenu->incrPlayerState(2);
						return true;
					case SELECT_PLAYER4_STATE_BUTTON:
						_engine->play2D("./music/clic.wav");
						_infoMenu->incrPlayerState(3);
						return true;
					case SWITCH_TO_VICTORY:
						std::cout << "SWITCH TO VICOTRY\n";
						_infoMenu->setCurrentMenu(VICTORY);
						return true;
					case SAVE_GAME:
						_infoMenu->setSaved(true);
						std::cout << "SAVING\n";
						return true;
					case QUIT_BUTTON:
						//_context->device->drop();
						//_core->quit(); Decomenter cette ligne a terme
						//_context->device->drop();
						return true;
					case RETURN_BUTTON_MENU:
						_infoMenu->setCurrentMenu(MAIN_MENU);
						_engine->play2D("./music/button.wav");
						return true;
					case MENU_BUTTON:
						_infoMenu->setCurrentScene(MENU_SCENE);
						_infoMenu->setCurrentMenu(MAIN_MENU);
						_engine->play2D("./music/button.wav");
						return true;
					case RESTART_BUTTON:
						_infoMenu->setCurrentMenu(NEW_GAME_MENU);
						_engine->play2D("./music/button.wav");
						return true;
					case PAUSE_BUTTON:
						//_infoMenu->setCurrentMenu(PAUSE_MENU);
						_engine->play2D("./music/button.wav");
						return true;

						
					default:
						return false;
				}
				break;
			default:
				break;
		}
	}
	return true;
}

bool		MyEventReceiver::IsKeyDown(irr::EKEY_CODE keyCode) const
{
	return KeyIsDown[keyCode];
}

/*
** EPITECH PROJECT, 2018
** VK
** File description:
** MyEventReceiver class declaration
*/

#ifndef MYEVENTRECEIVER_HPP_
	#define MYEVENTRECEIVER_HPP_

#include "irrlicht.h"
#include "InfoMenu.hpp"
#include "irrKlang.h"

using namespace irrklang;

using namespace irr::core;
using namespace irr::scene;
using namespace irr::video;
using namespace irr::io;
using namespace irr::gui;

class MyEventReceiver : public irr::IEventReceiver
{
	public:
				MyEventReceiver(InfoMenu *infoMenu);
    		virtual bool 	OnEvent(const irr::SEvent& event);
    		virtual bool 	IsKeyDown(irr::EKEY_CODE keyCode) const;
		bool		checkButtonAction(const irr::SEvent &event);
    	private:
    		bool 		KeyIsDown[irr::KEY_KEY_CODES_COUNT];
		InfoMenu	*_infoMenu;
		ISoundEngine	*_engine = createIrrKlangDevice();
};

#endif /* !MYEVENTRECEIVER_HPP_ */

/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Graphical
*/

#ifndef GRAPHICAL_HPP_
	#define GRAPHICAL_HPP_

#include <ITimer.h>
#include "Map.hpp"
#include "MyEventReceiver.hpp"
//#include <unistd.h>

// inside IRRlicht namespace
using namespace irr::core;
using namespace irr::scene;
using namespace irr::video;
using namespace irr::io;
using namespace irr::gui;

class Graphical {
	public:
		Graphical() = default;
		~Graphical() = default;

		void			start(InfoMenu *infoMenu);
		bool			isRunning() const;
		irr::IrrlichtDevice	*getDevice() const;
		MyEventReceiver		*getReceiver();
		void			quit();

	private:
		int				_FPS = 30;
		irr::IrrlichtDevice 		*_device;
		IVideoDriver 			*_driver;
		IGUIEnvironment			*_guienv;
		MyEventReceiver			*_receiver;
};

#endif /* !GRAPHICAL_HPP_ */

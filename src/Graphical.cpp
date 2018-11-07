/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Graphical
*/

#include "Graphical.hpp"

void	Graphical::start(InfoMenu *infoMenu)
{
	_receiver = new MyEventReceiver(infoMenu);
	_device = irr::createDevice(EDT_OPENGL, dimension2d<irr::u32>(1920, 1080), 32, false, true, false, _receiver);
	if (!_device)
	{
		std::cout << "Error while creating window" << std::endl;
		exit (84);
	}
	_driver = _device->getVideoDriver();
	_guienv = _device->getGUIEnvironment();
}

irr::IrrlichtDevice		*Graphical::getDevice() const
{
	return (_device);
}

void	Graphical::quit()
{
	_device->drop();
}

bool	Graphical::isRunning() const
{
	return (_device->run());
}

MyEventReceiver *Graphical::getReceiver()
{
	return _receiver;
}

// PRIVATES FUNCTIONS
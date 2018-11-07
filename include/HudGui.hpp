/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** HudGui
*/

#ifndef HudGui_HPP_
	#define HudGui_HPP_
	#include "MenuGui.hpp"

class HudGui : public MenuGui
{
	public:
		HudGui(SAppContext *, InfoMenu *);
		~HudGui() = default;
	protected:
	private:
};

#endif /* !HudGui_HPP_ */

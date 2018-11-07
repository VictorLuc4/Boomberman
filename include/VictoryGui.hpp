/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** VictoryGui
*/

#ifndef VictoryGui_HPP_
	#define VictoryGui_HPP_
	#include "MenuGui.hpp"

class VictoryGui : public MenuGui
{
	public:
		VictoryGui(SAppContext *, InfoMenu *);
		~VictoryGui() = default;
	protected:
	private:
};

#endif /* !VictoryGui_HPP_ */

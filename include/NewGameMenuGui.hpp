/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** NewGameMenuGui
*/

#ifndef NewGameMenuGui_HPP_
	#define NewGameMenuGui_HPP_
	#include "MenuGui.hpp"
	#include <map>

class NewGameMenuGui : public MenuGui
{
	public:
		NewGameMenuGui(SAppContext *, InfoMenu *);
		~NewGameMenuGui() = default;

		void	createButtons();
		void	initPathsPlayers();
		void	checkPlayerStateChanged();
		void	draw();
		void	setButtonImage(ButtonType buttonId, const std::string &path);
	private:
		std::vector<PlayerState> _playerStates;
		std::map<ButtonType, std::map<PlayerState, std::string>> _pathsPlayerState;
};

#endif /* !NewGameMenuGui_HPP_ */

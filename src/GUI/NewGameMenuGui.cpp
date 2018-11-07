/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** NewGameMenuGui
*/

#include "NewGameMenuGui.hpp"


NewGameMenuGui::NewGameMenuGui(SAppContext *context, InfoMenu *infoMenu) : MenuGui(context, infoMenu)
{
	irr::s32 X = 1920 / 3;
	irr::s32 Y = 1080 / 3;

	X = X + X / 4;
	//add image to background
	_background = Environment->addImage(rect<irr::s32>(0, 0, 1920, 1080), this);
	_background->setImage(_context->device->getVideoDriver()->getTexture("media/NewGameBackGround.png"));
	_background->setScaleImage(true);

	_playerStates.push_back(NONE);
	_playerStates.push_back(NONE);
	_playerStates.push_back(NONE);
	_playerStates.push_back(NONE);

	IGUISkin* skin = Environment->getSkin();
	IGUIFont* font = Environment->getFont("media/fontBig.bmp");
	if (font)
		skin->setFont(font);
	skin->setFont(Environment->getBuiltInFont(), EGDF_TOOLTIP);

	stringw wideString(_infoMenu->getMapSize());
	_mapSize = Environment->addStaticText(wideString.c_str(), rect<irr::s32>(X + 100, Y + 500, X + 400, Y + 500 + 50), false, true, this, -1, false);

	IGUIScrollBar* scrollbar = Environment->addScrollBar(true,
			rect<irr::s32>(500 + 285, Y + 405, 850 + 300, Y + 405 + 30), this, SCROLL_BAR);
	scrollbar->setMax(5);
	scrollbar->setMin(1);
	scrollbar->setPos(2);

	//setting image
	this->createButtons();
	this->initPathsPlayers();
}

void	NewGameMenuGui::initPathsPlayers()
{
	std::map<PlayerState, std::string> player1Paths;
	player1Paths.emplace(PLAYER, "media/mediaMenu/file2D/Player1Clavier");
	player1Paths.emplace(IA, "media/mediaMenu/file2D/IAPlayer1");
	player1Paths.emplace(NONE, "media/mediaMenu/file2D/NoPlayerPlayer1");

	_pathsPlayerState.emplace(SELECT_PLAYER1_STATE_BUTTON, player1Paths);

	std::map<PlayerState, std::string> player2Paths;
	player2Paths.emplace(PLAYER, "media/mediaMenu/file2D/Player2Clavier");
	player2Paths.emplace(IA, "media/mediaMenu/file2D/IAPlayer2");
	player2Paths.emplace(NONE, "media/mediaMenu/file2D/NoPlayerPlayer2");

	_pathsPlayerState.emplace(SELECT_PLAYER2_STATE_BUTTON, player2Paths);

	std::map<PlayerState, std::string> player3Paths;
	player3Paths.emplace(PLAYER, "media/mediaMenu/file2D/Player3Clavier");
	player3Paths.emplace(IA, "media/mediaMenu/file2D/IAPlayer3");
	player3Paths.emplace(NONE, "media/mediaMenu/file2D/NoPlayerPlayer3");

	_pathsPlayerState.emplace(SELECT_PLAYER3_STATE_BUTTON, player3Paths);

	std::map<PlayerState, std::string> player4Paths;
	player4Paths.emplace(PLAYER, "media/mediaMenu/file2D/Player4Clavier");
	player4Paths.emplace(IA, "media/mediaMenu/file2D/IAPlayer4");
	player4Paths.emplace(NONE, "media/mediaMenu/file2D/NoPlayerPlayer4");

	_pathsPlayerState.emplace(SELECT_PLAYER4_STATE_BUTTON, player4Paths);
}

void	NewGameMenuGui::createButtons()
{
	irr::s32 X = 1920 / 3;
	irr::s32 Y = 1080 / 3;

	X = X + X / 4;
	_buttons.emplace(SELECT_PLAYER1_STATE_BUTTON,
			Environment->addButton(rect<irr::s32>(200 + 200, Y, 200 + 200 + 600, (Y + 400) + 200),
			this,
			SELECT_PLAYER1_STATE_BUTTON, L"", L"PLay"));

	_buttons.emplace(SELECT_PLAYER2_STATE_BUTTON,
			Environment->addButton(rect<irr::s32>(500 + 200, Y, 500 + 200 + 600, (Y + 400) + 200),
			this,
			SELECT_PLAYER2_STATE_BUTTON, L"", L"PLay"));

	_buttons.emplace(SELECT_PLAYER3_STATE_BUTTON,
			Environment->addButton(rect<irr::s32>(800+ 200, Y, 800 + 200 + 600, (Y + 400) + 200),
			this,
			SELECT_PLAYER3_STATE_BUTTON, L"", L"PLay"));

	_buttons.emplace(SELECT_PLAYER4_STATE_BUTTON,
			Environment->addButton(rect<irr::s32>(1100 + 200, Y, 1100 + 200 + 600, (Y + 400) + 200),
			this,
			SELECT_PLAYER4_STATE_BUTTON, L"", L"PLay"));
	_buttons.emplace(PLAY_BUTTON, Environment->addButton(rect<irr::s32>(500 + 270, Y + 500, 770 + 500, Y + 500 + 150),
			this,
			PLAY_BUTTON, L"", L"Play"));
	_buttons.emplace(RETURN_BUTTON, Environment->addButton(rect<irr::s32>(0, 0, 500, 150),
			this,
			RETURN_BUTTON, L"", L"Play"));
	MenuGui::setButtonImage(PLAY_BUTTON, "media/mediaMenu/file2D/play");
	MenuGui::setButtonImage(RETURN_BUTTON, "media/mediaMenu/file2D/return");
}

void	NewGameMenuGui::checkPlayerStateChanged()
{
	std::vector<PlayerState> players = _infoMenu->getPlayers();

	for (int i = 0; i != _playerStates.size(); i++)
	{
		if (players[i] != _playerStates[i]) {
			if (i == 0) {
				this->setButtonImage(SELECT_PLAYER1_STATE_BUTTON, _pathsPlayerState[SELECT_PLAYER1_STATE_BUTTON][players[i]]);
				_playerStates[i] = players[i];
			} else if (i == 1) {
				this->setButtonImage(SELECT_PLAYER2_STATE_BUTTON,
				_pathsPlayerState[SELECT_PLAYER2_STATE_BUTTON][players[i]]);
				_playerStates[i] = players[i];
			} else if (i == 2) {
				this->setButtonImage(SELECT_PLAYER3_STATE_BUTTON,
				_pathsPlayerState[SELECT_PLAYER3_STATE_BUTTON][players[i]]);
				_playerStates[i] = players[i];
			} else if (i == 3) {
				this->setButtonImage(SELECT_PLAYER4_STATE_BUTTON,
				_pathsPlayerState[SELECT_PLAYER4_STATE_BUTTON][players[i]]);
				_playerStates[i] = players[i];
			}
		}
	}
}

void	NewGameMenuGui::draw()
{
	 if (isVisible()) {
		 	checkPlayerStateChanged();
			stringw wideString(_infoMenu->getMapSize());
			_mapSize->setText(wideString.c_str());
			list<IGUIElement*>::Iterator it = Children.begin();
			for (; it != Children.end(); ++it)
				(*it)->draw();
	}
}

void	NewGameMenuGui::setButtonImage(ButtonType buttonId, const std::string &path)
{
	std::string pathNotPushed = path + ".png";
	std::cout << pathNotPushed << "\n";
	ITexture *texture = _driver->getTexture(pathNotPushed.c_str());

	IGUIButton *tmp = reinterpret_cast<IGUIButton *>((_buttons[buttonId]));
	tmp->setImage(texture);
	tmp->setMaxSize(dimension2du(200, 300));
	tmp->setScaleImage(true);
	tmp->setUseAlphaChannel(true);
	tmp->setDrawBorder(0);
}
/*
** EPITECH PROJECT, 2018
** VK
** File description:
** MenuScene class declaration
*/

#ifndef GAMESCENE_HPP_
	#define GAMESCENE_HPP_

#include "IScene.hpp"
#include "MenuManager.hpp"

class GameScene : public IScene
{
	public:
		GameScene(MenuManager *menuManager);
		~GameScene() = default;

		void		setGraphics(Graphical *);
		void		load();
		void		draw();
		void		setCameraPos(const vector3df &pos, const vector3df &mir);
		void		setInfoMenu(InfoMenu *);

		void		exitWindow();
		ISceneManager	*getScene();
		void		actualize();
		void		rotatePowerUp(Block *powerUp);
		void		eraseFire(Block *fire);
		void		printFire(Block *fire);
		void		erasePowerUp(Block *powerUp);
		void		blasting(int x, int z, Block *bomb);
		void		destroyBomb(Block *bomb);
		void		scaleBomb(Block *bomb);
		void		moveBomb(Block *bomb);
		void		createPowerUp(Block *block);
		void		destroyBox(Block *box);
		void		kickBomb(Block *bomb, int dir);
		void		bombPose(Block *block, int blast);
		Map		*getMap();
		irr::ITimer	*getTimer() const;
		void	dropMusic();

	private:
		void		setPaths();
		void		loadMeshes();
		void		loadTextures();
		int		getRotation(TypeBlock block, int x, int y);
		void		createFire(Block *fire);
		void		createNode(Block *block, int id);
		void		createFloor(int x, int y);
		void		printMap(std::vector<std::vector<Block *>> map);
		ITexture	*getTexture(const std::string &filename);
		void		loadSkyDome();
		void		setPathMusic();

		irr::IrrlichtDevice		*_device;
		IVideoDriver 			*_driver;
		ISceneManager			*_scene;
		IGUIEnvironment			*_guienv;
		Map				*_map;
		std::map<TypeBlock, IMesh *>			_Meshes;
		std::map<TypeBlock, ITexture *>			_Textures;
		InfoMenu			*_infoMenu;
		MenuManager			*_menuManager;
		ISceneNode* _skybox;
		ISceneNode* _skydome;
		std::map<MenuType, std::string>	_musicPath;
		ISoundEngine			*_engine;
		MenuGui				*_currentGui;
};

#endif /* !GAMESCENE_HPP_ */

/*
** EPITECH PROJECT, 2018
** VK
** File description:
** MenuScene class declaration
*/

#ifndef MENUSCENE_HPP_
	#define MENUSCENE_HPP_

#include "IScene.hpp"
#include "MenuManager.hpp"
#include "MenuGui.hpp"
#include "irrKlang.h"

using namespace irrklang;

enum BlockMenu
{
	CASTLE,
	TITLE,
	SKYBOX,
	SKYDOME
};

class MenuScene : public IScene
{
	public:
		MenuScene(MenuManager *);
		~MenuScene() = default;

		void		setGraphics(Graphical *);
		void		load();
		void		draw();
		void		setCameraPos(const vector3df &pos, const vector3df &ang);
		void		setInfoMenu(InfoMenu *);
		void		exitWindow();
		ISceneManager	*getScene();
		Map		*getMap();
		void	dropMusic();

	private:
		void		setPaths();
		void		loadMeshes();
		void		loadTextures();
		void		loadAnimations();
		void		setRotationCastle();
		void		createNodes();
		void		loadSkyDome();
		ITexture	*getTexture(const std::string &filename);
		void		loadParticuleSakura();
		

		irr::IrrlichtDevice		*_device;
		IVideoDriver 			*_driver;
		ISceneManager			*_scene;
		IGUIEnvironment			*_guienv;
		std::map<BlockMenu, IMesh *>				_Meshes;
		std::map<BlockMenu, std::string>			_MeshesPath;
		std::map<BlockMenu, ITexture *>				_Textures;
		std::map<BlockMenu, std::string>			_TexturesPath;
		std::map<BlockMenu, IMeshSceneNode *>			_Nodes;
		std::map<BlockMenu, IAnimatedMeshSceneNode *>		_Animations;
		std::map<BlockMenu, std::string>			_AnimationsPath;

		MenuManager			*_menuManager;
		MenuGui				*_currentGui;
		IParticleSystemSceneNode *_particleSystem;
		float				_posCamera = 0;
		float				_posSkyBox = 0;
		ISceneNode* _skybox;
		ISceneNode* _skydome;
		std::map<MenuType, std::string>	_musicPath;
		ISoundEngine	*_engine;
		InfoMenu	*_info;


		//IGUIElement			*_gui;
};

#endif /* !MENUSCENE_HPP_ */
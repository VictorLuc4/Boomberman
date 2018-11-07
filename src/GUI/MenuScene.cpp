/*
** EPITECH PROJECT, 2018
** VK
** File description:
** MenuScene class implementation
*/

#include "MenuScene.hpp"


MenuScene::MenuScene(MenuManager *menuManager) : _menuManager(menuManager)
{
}

void		MenuScene::setGraphics(Graphical *irr)
{
	_device = irr->getDevice();
	_driver = _device->getVideoDriver();
	_scene = _device->getSceneManager()->createNewSceneManager();
	_guienv = _device->getGUIEnvironment();
	_particleSystem = _scene->addParticleSystemSceneNode(0);
}

void		MenuScene::load()
{
	setPaths();
	loadMeshes();
	loadTextures();
	loadAnimations();
	createNodes();
	loadSkyDome();
	loadParticuleSakura();
	_engine = createIrrKlangDevice();
	_engine->play2D(_musicPath.at(_info->getCurrentMenu()).c_str(), true);
}

void		MenuScene::draw()
{
	setRotationCastle();
	_driver->beginScene(true, true, SColor(255, 100, 101, 140));
	_scene->drawAll();
	_menuManager->getCurrentGui()->draw();
	_driver->endScene();
	_posCamera += 0.1;
	_skybox->setRotation(vector3df(0, _posCamera, 0));
	if (_currentGui != _menuManager->getCurrentGui()) {
       		_engine->drop();
		ISoundEngine *engine = createIrrKlangDevice();
		_engine = engine;
        	_engine->play2D(_musicPath.at(_info->getCurrentMenu()).c_str(), true);
        	_currentGui = _menuManager->getCurrentGui();
	}

}

void	MenuScene::dropMusic()
{
	_engine->drop();
}

void		MenuScene::setCameraPos(const vector3df &pos, const vector3df &ang)
{
	_scene->addCameraSceneNode(0, pos, ang);
	ILightSceneNode * light = _scene->addLightSceneNode(0, vector3df(270,400,-400),
        SColorf(1.0f,1.0f,1.0f,1.0f), 600.0f);
    	light->setID(0);
}

void		MenuScene::setInfoMenu(InfoMenu *menu)
{
	_info = menu;
}

void		MenuScene::exitWindow()
{
	_device->drop();
}

///////////////////////////////////////////// PRIVATE FUNCTIONS

void		MenuScene::setPaths()
{
	_MeshesPath.emplace(std::pair<BlockMenu, std::string>(CASTLE, "media/mediaMenu/file3D/cloud.obj"));
	_musicPath.emplace(std::pair<MenuType, std::string>(MAIN_MENU, "./music/MusicMenu.ogg"));
	_musicPath.emplace(std::pair<MenuType, std::string>(NEW_GAME_MENU, "./music/MusicSelectionCharacter.wav"));
	_musicPath.emplace(std::pair<MenuType, std::string>(OPTION_MAIN_MENU, "./music/MusicSettings.ogg"));
}

void		MenuScene::loadMeshes()
{
	for (auto &mesh : _MeshesPath)
	{
		IMesh *meshTmp = _scene->getMesh(mesh.second.c_str());

		if (!meshTmp)
		{
			std::cout << "Error while opening: " << mesh.second << std::endl;
			exitWindow();
			exit (84);
		}
		_Meshes.emplace(std::pair<BlockMenu, IMesh *>(mesh.first, meshTmp));
	}
}

void		MenuScene::loadTextures()
{
	for (auto &texture : _TexturesPath)
	{
		ITexture *textureTmp = _driver->getTexture(texture.second.c_str());
		if (!textureTmp)
		{
			std::cout << "Error while opening: " << texture.second << std::endl;
			exitWindow();
			exit (84);
		}
		_Textures.emplace(std::pair<BlockMenu, ITexture *>(texture.first, textureTmp));
	}
}

void		MenuScene::loadAnimations()
{
	for (auto &animation : _AnimationsPath)
	{
		IAnimatedMeshSceneNode *animationTmp = _scene->addAnimatedMeshSceneNode(_scene->getMesh(animation.second.c_str()));
		if (!animationTmp)
		{
			std::cout << "Error while opening: " << animation.second << std::endl;
			exitWindow();
			exit (84);
		}
		_Animations.emplace(std::pair<BlockMenu, IAnimatedMeshSceneNode *>(animation.first, animationTmp));
	}
}

void		MenuScene::createNodes()
{
	for (auto &mesh : _Meshes)
	{
		IMeshSceneNode *tmpNode = _scene->addMeshSceneNode(mesh.second);
		//option pour block spécifique
		//if (mesh.first == XXX) where XXX == _BLOCKS du choix
		tmpNode->setMaterialFlag(EMF_LIGHTING, true);
		// tmpNode->setMaterialTexture(0, _Textures.at(mesh.first));
		_Nodes.emplace(std::pair<BlockMenu, IMeshSceneNode *>(mesh.first, tmpNode));
	}
}

ITexture	*MenuScene::getTexture(const std::string &filename)
{
		return _driver->getTexture(filename.c_str());
}

void		MenuScene::setRotationCastle()
{
	_posCamera -= 0.2;
	_Nodes[CASTLE]->setRotation(vector3df(0, _posCamera, 0));

}

void		MenuScene::loadSkyDome()
{
	_driver->setTextureCreationFlag(ETCF_CREATE_MIP_MAPS, false);

    	_skybox=_scene->addSkyBoxSceneNode(
        _driver->getTexture("media/mediaMenu/file2D/SkyBox/stormydays_up.tga"),
        _driver->getTexture("media/mediaMenu/file2D/SkyBox/stormydays_dn.tga"),
        _driver->getTexture("media/mediaMenu/file2D/SkyBox/stormydays_lf.tga"),
        _driver->getTexture("media/mediaMenu/file2D/SkyBox/stormydays_rt.tga"),
        _driver->getTexture("media/mediaMenu/file2D/SkyBox/stormydays_bk.tga"),
        _driver->getTexture("media/mediaMenu/file2D/SkyBox/stormydays_ft.tga"));
    	ISceneNode* _skydome = _scene->addSkyDomeSceneNode(_driver->getTexture("media/mediaMenu/file2D/SkyBox/skydome1.jpg"),0,0,0.95f,2.0f);
	_driver->setTextureCreationFlag(ETCF_CREATE_MIP_MAPS, true);


	_skybox->setVisible(true);
	_skydome->setVisible(false);
}

ISceneManager *MenuScene::getScene()
{
	return _scene;
}

Map	*MenuScene::getMap()
{
	return nullptr;
}

void	MenuScene::loadParticuleSakura()
{
	IParticleEmitter* emitter = _particleSystem->createBoxEmitter(
	aabbox3d<irr::f32>(0,0,0,0,0,0), // coordonnees de la boite
	vector3df(-0.3f,-0.3f,-0.0f),        // direction de diffusion
	20,40,                                       // nb particules emises a la sec min / max
	SColor(220,255,255,255),            // couleur la plus sombre
	SColor(255,255,255,255),            // couleur la plus claire
	2000, 20000,                                    // duree de vie min / max
	45,                                            // angle max d'ecart / direction prevue
	dimension2df(0.1f,0.1f),           // taille minimum
	dimension2df(0.6f,0.6f));

	_particleSystem->setEmitter(emitter);              // on attache l'emetteur
	emitter->drop();                                  // plus besoin de ca
	IParticleAffector* paf = _particleSystem->createRotationAffector(vector3df(0,0.5,0));
    	_particleSystem->addAffector(paf); // same goes for the affector
    	paf->drop();

	IParticleAffector *gravity = _particleSystem->createGravityAffector(irr::core::vector3df(0, -0.02f, 0), 200);
	_particleSystem->addAffector(gravity);
	gravity->drop();

	_particleSystem->setPosition(vector3df(80, 150, 20));
	_particleSystem->setMaterialFlag(EMF_LIGHTING, true);          // insensible a la lumiere
	_particleSystem->setMaterialTexture(0, _driver->getTexture("media/mediaMenu/file2D/rose.png"));
	_particleSystem->setMaterialType(EMT_TRANSPARENT_ALPHA_CHANNEL);     // on colle une texture
}
/*
** EPITECH PROJECT, 2018
** VK
** File description:
** GameScene class implementation
*/

#include "GameScene.hpp"

GameScene::GameScene(MenuManager *menuManager): _menuManager(menuManager)
{
}

void		GameScene::setGraphics(Graphical *irr)
{
	_device = irr->getDevice();
	_driver = _device->getVideoDriver();
	_scene = _device->getSceneManager()->createNewSceneManager();
	_guienv = _device->getGUIEnvironment();
}

void		GameScene::load()
{
	_map = new Map(_infoMenu->getMapSize(), _infoMenu->getMapTxt());
	loadMeshes();
	loadTextures();
	loadSkyDome();
	setPathMusic();
	printMap(_map->getMap());
	_engine = createIrrKlangDevice();
	_engine->play2D("./music/gong.wav");
	std::cout << _musicPath.at(_infoMenu->getCurrentMenu()).c_str() << std::endl;
	_engine->play2D(_musicPath.at(_infoMenu->getCurrentMenu()).c_str(), true);
}

void		GameScene::draw()
{
	actualize();
	_driver->beginScene(true, true, SColor(255, 100, 101, 140));
	_scene->drawAll();
	_menuManager->getCurrentGui()->draw();
	_driver->endScene();
	if (_currentGui != _menuManager->getCurrentGui()) {
       		_engine->drop();
		ISoundEngine *engine = createIrrKlangDevice();
		_engine = engine;
        	_engine->play2D(_musicPath.at(_infoMenu ->getCurrentMenu()).c_str(), true);
        	_currentGui = _menuManager->getCurrentGui();
	}
}

void	GameScene::dropMusic()
{
	_engine->drop();
}

void		GameScene::setCameraPos(const vector3df &pos, const vector3df &mir)
{
	float	s = 40 * (_map->getSize() - 1);

	_scene->addCameraSceneNode(0, pos + vector3df(s,s,-1 * s), mir + vector3df(s,0,0-s));
	ILightSceneNode * light = _scene->addLightSceneNode(0, vector3df(270 + s,400+s,-400 - s),
        SColorf(1.0f,1.0f,1.0f,1.0f), 600.0f);
    	light->setID(0);
}

void		GameScene::setInfoMenu(InfoMenu *infoMenu)
{
	_infoMenu = infoMenu;
}

void		GameScene::exitWindow()
{
	_device->drop();
}

ISceneManager	*GameScene::getScene()
{
	return _scene;
}

void	GameScene::actualize()
{
	std::vector<std::vector<Block *>> map = _map->getMap();
	int j, i = -1;

	while (++i < map.size()) {
		j = -1;
		while (++j < map[i].size()) {
			if (_map->getBlock(j, i)->getType() == POWERUP1
			|| _map->getBlock(j, i)->getType() == POWERUP2
			|| _map->getBlock(j, i)->getType() == POWERUP3
			|| _map->getBlock(j, i)->getType() == POWERUP4
			|| _map->getBlock(j, i)->getType() == POWERUP5
			|| _map->getBlock(j, i)->getType() == POWERUP6
			)
				rotatePowerUp(_map->getBlock(j, i));
			else if (_map->getBlock(j, i)->getType() == BOMB) {
				scaleBomb(_map->getBlock(j, i));
				if (_map->getBlock(j, i)->getKick() == true)
					moveBomb(_map->getBlock(j, i));
			}
			else if (_map->getBlock(j, i)->getType() == FIRE)
				eraseFire(_map->getBlock(j, i));
		}
	}
}

void	GameScene::rotatePowerUp(Block *powerUP)
{
	if (powerUP->getRatio() > 360)
		powerUP->setRatio(0);
	powerUP->getNode()->setRotation(vector3df(0, powerUP->getRatio(), 0));
	powerUP->setRatio(powerUP->getRatio() + 3);
}

void	GameScene::setPathMusic()
{
	_musicPath.emplace(std::pair<MenuType, std::string>(HUD, "./music/MusicGame.ogg"));
	_musicPath.emplace(std::pair<MenuType, std::string>(VICTORY, "./music/MusicWin.wav"));
	_musicPath.emplace(std::pair<MenuType, std::string>(PAUSE_MENU, "./music/MusicGame.ogg"));
}

void	GameScene::eraseFire(Block *fire)
{
	int chrono;

	fire->setEnd();
	if ((chrono = std::chrono::duration_cast<std::chrono::seconds> (fire->getEnd()-fire->getStart()).count()) > 0) {
		fire->getFire()->clearParticles();
		fire->getFire()->removeAllAffectors();
		_scene->addToDeletionQueue(fire->getFire());
		_map->setBlock(EMPTY, "", fire->getPosX(), fire->getPosZ());
		_map->setBlockTxt(' ', fire->getPosX(), fire->getPosZ());
	}
}

void	GameScene::printFire(Block *fire)
{
	_map->setBlock(FIRE, "", fire->getPosX(), fire->getPosZ());
	_map->setBlockTxt('F', fire->getPosX(), fire->getPosZ());
	_map->getBlock(fire->getPosX(), fire->getPosZ())->setStart();
	createFire(fire);
}

void	GameScene::erasePowerUp(Block *powerUp)
{
	_scene->addToDeletionQueue(powerUp->getNode());
	_map->setBlock(EMPTY, "", powerUp->getPosX(), powerUp->getPosZ());
	_map->setBlockTxt(' ', powerUp->getPosX(), powerUp->getPosZ());
}

void	GameScene::blasting(int x, int z, Block *bomb)
{
	int	i = 1;

	while (i <= bomb->getBlast())
	{
		if (_map->getBlock(bomb->getPosX() + x * i, bomb->getPosZ() + z * i)->getType() == EMPTY)
			printFire(_map->getBlock(bomb->getPosX() + x * i, bomb->getPosZ() + z * i));
		else if (_map->getBlock(bomb->getPosX() + x * i, bomb->getPosZ() + z * i)->getType() == POWERUP1
		|| _map->getBlock(bomb->getPosX() + x * i, bomb->getPosZ() + z * i)->getType() == POWERUP2
		|| _map->getBlock(bomb->getPosX() + x * i, bomb->getPosZ() + z * i)->getType() == POWERUP3
		|| _map->getBlock(bomb->getPosX() + x * i, bomb->getPosZ() + z * i)->getType() == POWERUP4
		|| _map->getBlock(bomb->getPosX() + x * i, bomb->getPosZ() + z * i)->getType() == POWERUP5
		|| _map->getBlock(bomb->getPosX() + x * i, bomb->getPosZ() + z * i)->getType() == POWERUP6) {
			erasePowerUp(_map->getBlock(bomb->getPosX() + x * i, bomb->getPosZ() + z * i));
			printFire(_map->getBlock(bomb->getPosX() + x * i, bomb->getPosZ() + z * i));
		}
		else if (_map->getBlock(bomb->getPosX() + x * i, bomb->getPosZ() + z * i)->getType() == BOX) {
			destroyBox(_map->getBlock(bomb->getPosX() + x * i, bomb->getPosZ() + z * i));
			return;
		}
		else if (_map->getBlock(bomb->getPosX() + x * i, bomb->getPosZ() + z * i)->getType() == BOMB) {
			destroyBomb(_map->getBlock(bomb->getPosX() + x * i, bomb->getPosZ() + z * i));
			return;
		}
		else if (_map->getBlock(bomb->getPosX() + x * i, bomb->getPosZ() + z * i)->getType() == WALL
		|| _map->getBlock(bomb->getPosX() + x * i, bomb->getPosZ() + z * i)->getType() == COLUMN)
			return;
		i += 1;
	}
}

void	GameScene::destroyBomb(Block *bomb)
{
	_scene->addToDeletionQueue(bomb->getNode());
	printFire(bomb);
	blasting(-1, 0, bomb);
	blasting(1, 0, bomb);
	blasting(0, -1, bomb);
	blasting(0, 1, bomb);
}

void	GameScene::scaleBomb(Block *bomb)
{
	int chrono;

	if (bomb->getRatio() == 0) {
		bomb->setRatio(1);
		bomb->setStart();
	}
	if (bomb->getRatio() > 1.3)
		bomb->setRatio(1);
	bomb->setEnd();
	_map->getBlock(bomb->getPosX(), bomb->getPosZ())->getNode()->setScale(vector3df(bomb->getRatio(), bomb->getRatio(), bomb->getRatio()));
	bomb->setRatio(bomb->getRatio() + 0.01);
	if ((chrono = std::chrono::duration_cast<std::chrono::seconds> (bomb->getEnd()-bomb->getStart()).count()) > 1)
		destroyBomb(_map->getBlock(bomb->getPosX(), bomb->getPosZ()));
}

void	GameScene::moveBomb(Block *bomb)
{
	vector3df		vec = _map->getBlock(bomb->getPosX(), bomb->getPosZ())->getNode()->getPosition();
	std::pair<int, int>	pos = _map->getBlock(bomb->getPosX(), bomb->getPosZ())->getDir();

	if (_map->getBlock(int(((vec.X)/40)+pos.first),int(((vec.Z)/-40)-pos.second))->getType() == EMPTY)
		_map->getBlock(bomb->getPosX(), bomb->getPosZ())->getNode()->setPosition(vector3df(vec.X+pos.first*4,0,vec.Z+pos.second*4));
	_map->setBlock(EMPTY, "", bomb->getPosX(), bomb->getPosZ());
	_map->setBlockTxt(' ', bomb->getPosX(), bomb->getPosZ());
	_map->setBlock(BOMB, "bomb", int(vec.X/40), int(vec.Z/-40));
	_map->setBlockTxt('B', int(vec.X/40), int(vec.Z/-40));
	if (_map->getBlock(int(((vec.X)/40)+pos.first),int(((vec.Z)/-40)-pos.second))->getType() == EMPTY) {
		_map->getBlock(int(vec.X/40), int(vec.Z/-40))->setStart();
		_map->getBlock(int(vec.X/40), int(vec.Z/-40))->setKick(true);
	}
	_map->getBlock(int(vec.X/40), int(vec.Z/-40))->setRatio(bomb->getRatio());
	_map->getBlock(int(vec.X/40), int(vec.Z/-40))->setNode(bomb->getNode());
	_map->getBlock(int(vec.X/40), int(vec.Z/-40))->setBlast(bomb->getBlast());
	_map->getBlock(int(vec.X/40), int(vec.Z/-40))->setDir(pos.first, pos.second);
}

void	GameScene::createPowerUp(Block *block)
{
	int r;

	std::srand(std::time(0) + block->getPosX());
	r = std::rand() % 6 + 1;
	switch (r)
	{
		case 1:
			_map->setBlock(POWERUP1, "blastboost", block->getPosX(), block->getPosZ());
			_map->setBlockTxt('1', block->getPosX(), block->getPosZ());
			break;
		case 2:
			_map->setBlock(POWERUP2, "bombboost", block->getPosX(), block->getPosZ());
			_map->setBlockTxt('2', block->getPosX(), block->getPosZ());
			break;
		case 3:
			_map->setBlock(POWERUP3, "pushboost", block->getPosX(), block->getPosZ());
			_map->setBlockTxt('3', block->getPosX(), block->getPosZ());
			break;
		case 4:
			_map->setBlock(POWERUP4, "speedboost", block->getPosX(), block->getPosZ());
			_map->setBlockTxt('4', block->getPosX(), block->getPosZ());
			break;
		case 5:
			_map->setBlock(POWERUP5, "shieldboost", block->getPosX(), block->getPosZ());
			_map->setBlockTxt('5', block->getPosX(), block->getPosZ());
			break;
		case 6:
			_map->setBlock(POWERUP6, "ghostboost", block->getPosX(), block->getPosZ());
			_map->setBlockTxt('6', block->getPosX(), block->getPosZ());
			break;
	}
	createNode(_map->getBlock(block->getPosX(), block->getPosZ()), block->getNode()->getID());
}

void	GameScene::destroyBox(Block *box)
{
	int r;

	std::srand(std::time(0) + box->getPosZ());
	r = std::rand() % 100;
	_scene->addToDeletionQueue(box->getNode());
	if (r % 2 == 0)
		printFire(box);
	else
		createPowerUp(box);
}

void	GameScene::kickBomb(Block *bomb, int dir)
{
	_map->getBlock(bomb->getPosX(), bomb->getPosZ())->setKick(true);
	switch (dir)
	{
		case 0:
		_map->getBlock(bomb->getPosX(), bomb->getPosZ())->setDir(-1, 0);
			break;
		case 1:
		_map->getBlock(bomb->getPosX(), bomb->getPosZ())->setDir(1, 0);
			break;
		case 2:
		_map->getBlock(bomb->getPosX(), bomb->getPosZ())->setDir(0, 1);
			break;
		case 3:
		_map->getBlock(bomb->getPosX(), bomb->getPosZ())->setDir(0, -1);
			break;
	}
}

void	GameScene::bombPose(Block *block, int blast)
{
	_map->setBlock(BOMB, "bomb", block->getPosX(), block->getPosZ());
	_map->setBlockTxt('B', block->getPosX(), block->getPosZ());
	_map->getBlock(block->getPosX(), block->getPosZ())->setBlast(blast);
	createNode(_map->getBlock(block->getPosX(), block->getPosZ()), -1);
}

Map	*GameScene::getMap()
{
	return _map;
}

irr::ITimer	*GameScene::getTimer() const
{
	return (_device->getTimer());
}

///////////////////////////////////////////// PRIVATE FUNCTIONS

std::vector<Block *>	getDefaultBlocks()
{
	std::vector<Block *> defaultBlocks;

	defaultBlocks.push_back(new Block(WALL, "wall", -1, -1));
	defaultBlocks.push_back(new Block(CORNER, "corner", -1, -1));
	defaultBlocks.push_back(new Block(POWERUP1, "blastboost", -1, -1));
	defaultBlocks.push_back(new Block(POWERUP2, "bombboost", -1, -1));
	defaultBlocks.push_back(new Block(POWERUP3, "pushboost", -1, -1));
	defaultBlocks.push_back(new Block(POWERUP4, "speedboost", -1, -1));
	defaultBlocks.push_back(new Block(POWERUP5, "shieldboost", -1, -1));
	defaultBlocks.push_back(new Block(POWERUP6, "ghostboost", -1, -1));
	defaultBlocks.push_back(new Block(BOMB, "bomb", -1, -1));
	defaultBlocks.push_back(new Block(BOX, "box", -1, -1));
	defaultBlocks.push_back(new Block(COLUMN, "column", -1, -1));
	defaultBlocks.push_back(new Block(FLOOR, "floor", -1, -1));
	return defaultBlocks;
}

void		GameScene::loadMeshes()
{
	int i = -1;
	std::vector<Block *> meshesPath = getDefaultBlocks();

	while (++i < meshesPath.size()) {
		IMesh *meshTmp = _scene->getMesh(meshesPath[i]->getMeshPath().c_str());
		if (!meshTmp)
		{
			std::cout << "Error while opening: " << meshesPath[i]->getMeshPath() << std::endl;
			exitWindow();
			exit (84);
		}
		_Meshes.emplace(std::pair<TypeBlock, IMesh *>(meshesPath[i]->getType(), meshTmp));
	}
}

void		GameScene::loadTextures()
{
	int i = -1;
	std::vector<Block *> texturesPath = getDefaultBlocks();

	while (++i < texturesPath.size()) {
		ITexture *textureTmp = _driver->getTexture(texturesPath[i]->getTexturePath().c_str());
		if (!textureTmp)
		{
			std::cout << "Error while opening: " << texturesPath[i]->getTexturePath() << std::endl;
			exitWindow();
			exit (84);
		}
		_Textures.emplace(std::pair<TypeBlock, ITexture *>(texturesPath[i]->getType(), textureTmp));
	}
	_Textures.emplace(std::pair<TypeBlock, ITexture *>(FIRE, getTexture("media/mediaGame/file3D/map/fireworks.png")));
}

int		GameScene::getRotation(TypeBlock block, int x, int y)
{
	switch (block) {
		case WALL:
			if (y > 0 && y < (10 + 2 * (_map->getSize() - 1)))
				return 90;
			else
				return 0;
		case CORNER:
			if (x == 0 && y == 0)
				return 90;
			else if (x != 0 && y == 0)
				return 180;
			else if (x != 0 && y != 0)
				return -90;
			else
				return 0;
		default:
			return 0;
	}
}

void		GameScene::createFire(Block *fire)
{
	irr::core::vector3df pos(40 * fire->getPosX(), 0.0f, -40 * fire->getPosZ());

	IParticleSystemSceneNode *ps = _scene->addParticleSystemSceneNode(0);
	IParticleEmitter *em = ps->createBoxEmitter(
        aabbox3d<irr::f32>(-5,0,0,12,10,12),vector3df(0.0f,0.04f,0.0f),
        10,20,SColor(255,255,255,255),SColor(255,255,255,255),
	1000,2000,0,dimension2df(30.f,30.f),dimension2df(50.f,50.f));
	ps->setEmitter(em);
    	em->drop();
	IParticleAffector* paf = ps->createRotationAffector(vector3df(0,0.5,0));
    	ps->addAffector(paf);
    	paf->drop();
	ps->setPosition(pos);
	ps->setMaterialFlag(EMF_LIGHTING, true);
	ps->setMaterialTexture(0, _Textures[FIRE]);
	ps->setMaterialType(EMT_TRANSPARENT_ALPHA_CHANNEL);
	_map->getBlock(fire->getPosX(), fire->getPosZ())->setFire(ps);
}

void		GameScene::createNode(Block *block, int id)
{
	irr::core::vector3df pos(40 * block->getPosX(), 0.0f, -40 * block->getPosZ());

	IMeshSceneNode *tmpNode = _scene->addMeshSceneNode(_Meshes[block->getType()], 0, id, pos);
	tmpNode->setMaterialFlag(irr::video::EMF_LIGHTING, true);
	tmpNode->setMaterialTexture(0, _Textures[block->getType()]);
	tmpNode->setRotation(vector3df(0, getRotation(block->getType(),  block->getPosX(), block->getPosZ()), 0));
	block->setNode(tmpNode);
}

void		GameScene::createFloor(int x, int z)
{
	irr::core::vector3df pos(40 * x, -40.0f, -40 * z);

	IMeshSceneNode *tmpNode = _scene->addMeshSceneNode(_Meshes[FLOOR], 0, -1, pos);
	tmpNode->setMaterialFlag(irr::video::EMF_LIGHTING, true);
	tmpNode->setMaterialTexture(0, _Textures[FLOOR]);
}

void		GameScene::printMap(std::vector<std::vector<Block *>> map)
{
	int i = -1;
	int j;
	int id = 0;

	while (++i < map.size()) {
		j = -1;
		while (++j < map[i].size()) {
			createFloor(j, i);
			if (map[i][j]->getType() != EMPTY)
				createNode(map[i][j], id);
			id += 1;
		}
	}
}

ITexture	*GameScene::getTexture(const std::string &filename)
{
		return _driver->getTexture(filename.c_str());
}

void		GameScene::loadSkyDome()
{
	_driver->setTextureCreationFlag(ETCF_CREATE_MIP_MAPS, false);

    	_skybox=_scene->addSkyBoxSceneNode(
        _driver->getTexture("media/mediaMenu/file2D/SkyBox/purplenebula_up.tga"),
        _driver->getTexture("media/mediaMenu/file2D/SkyBox/purplenebula_dn.tga"),
        _driver->getTexture("media/mediaMenu/file2D/SkyBox/purplenebula_lf.tga"),
        _driver->getTexture("media/mediaMenu/file2D/SkyBox/purplenebula_rt.tga"),
        _driver->getTexture("media/mediaMenu/file2D/SkyBox/purplenebula_bk.tga"),
        _driver->getTexture("media/mediaMenu/file2D/SkyBox/purplenebula_ft.tga"));
    	ISceneNode* _skydome = _scene->addSkyDomeSceneNode(_driver->getTexture("media/mediaMenu/file2D/SkyBox/skydome1.jpg"),0,0,0.95f,2.0f);
	_driver->setTextureCreationFlag(ETCF_CREATE_MIP_MAPS, true);


	_skybox->setVisible(true);
	_skydome->setVisible(false);
}
/*
** EPITECH PROJECT, 2018
** Music.cpp
** File description:
** Music
*/

#include "Music.hpp"

Music::Music()
{
        _Engine = createIrrKlangDevice();
        if (_Engine)
                std::cout << "Error starting up the engine" << std::endl;
}

Music::~Music()
{
        _engine->drop();
}

void    Music::getPath()
{
        _musicPath.emplace(std::pair<MusicDisplay, std::string>(MENU, "");
        _musicPath.emplace(std::pair<MusicDisplay, std::string>(GAME, "");
        _musicPath.emplace(std::pair<MusicDisplay, std::string>(OPTION, "");
        _musicPath.emplace(std::pair<MusicDisplay, std::string>(WIN, "");

        _soundPath.emplace(std::pair<SoundEffects, std::string>(PAS, ""));
        _soundPath.emplace(std::pair<SoundEffects, std::string>(EXPLO, ""));
        _soundPath.emplace(std::pair<SoundEffects, std::string>(BONUS, ""));
        _soundPath.emplace(std::pair<SoundEffects, std::string>(CLIC, ""));
        _soundPath.emplace(std::pair<SoundEffects, std::string>(START, ""));
        _soundPath.emplace(std::pair<SoundEffects, std::string>(VICTORY, ""))
        _soundPath.emplace(std::pair<SoundEffects, std::string>(LOOSE, ""));
        _soundPath.emplace(std::pair<SoundEffects, std::string>(SAVE, ""));
        _soundPath.emplace(std::pair<SoundEffects, std::string>(BOX, ""));
        _soundPath.emplace(std::pair<SoundEffects, std::string>(KICK, ""));
}

void    Music::loadMusic(MusicDisplay path)
{
        ISound *musictmp = _engine->Play2D(_musicsPath.at(path), true);
        if (!musictmp)
	{
		std::cout << "Error while opening: " << _musicsPath.at(path) << std::endl;
		exitWindow();
		exit (84);
	}
        _music.emplace(std::pair<BlockMenu, ISound *>(_musicsPath, musictmp))
}

void    Music::loadSoundAtPosition(SoundEffects path, vector3df pos)
{
        ISound *soundtmp = _engine->Play3D(_soundsPath.at(path), pos, true, false, true);
        if (!musicTmp)
        	{
		std::cout << "Error while opening: " << _soundsPath.at(path) << std::endl;
		exitWindow();
		exit (84);
	}
        _music.emplace(std::pair<BlockMenu, ISound *>(path, soundtmp))
}

void    Music::loadSound(SoundEffects path)
{
        ISound *soundtmp = _engine->Play2D(_soundsPath.at(path));
        if (!musicTmp)
        	{
		std::cout << "Error while opening: " << _soundsPath.at(path << std::endl;
		exitWindow();
		exit (84);
	}
        _music.emplace(std::pair<BlockMenu, ISound *>(path, soundtmp));
}

void    Music::stopMusic(SoundEffects path)
{
        _music.at(path)->drop();
}
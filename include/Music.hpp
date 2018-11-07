/*
** EPITECH PROJECT, 2018
** Music.hpp
** File description:
** Music
*/

#ifndef MUSIC_HPP_
	#define MUSIC_HPP_

#include <iostream>
#include <stdio.h>
#include <irrKlang.h>
#include <map>
#include <vector>

enum MusicDisplay
{
        MENU,
        GAME,
        OPTION,
        WIN,
}

enum SoundEffects
{
        PAS,
        EXPLO,
        BONUS,
        CLIC,
        START,
        VICTORY,
        LOOSE,
        SAVE,
        BOX,
        KICK
}

class Music {
	public:
		Music();
		~Music();
                void            getPath();
                void            loadMusic(MusicDisplay);
                void            loadSoundAtPosition(SoundEffects,vector3df pos);
                void            loadSound(SoundEffects);
                void            stopMusic(MusicDisplay);
	protected:
                std::map<MusicDisplay, std::string>        _musicsPath;
                std::map<MusicDisplay, ISound*>                 _music;
                std::map<MusicDisplay, std::string>        _soundsPath;
                std::map<MusicDisplay, ISound*>                 _music;

                ISoundEngine    *_engine;
	private:
};

#endif /* !MUSIC_HPP_ */

/*
** EPITECH PROJECT, 2018
** Config.hpp
** File description:
** Config
*/

#ifndef CONFIG_HPP_
	#define CONFIG_HPP_
        #include <string>
        #include <vector>
        #include <fstream>
        #include <map>
        #include <iostream>


enum classPos
{
        CHARAC,
        MAP
};

typedef struct CharacValue
{
        int             bombs;
        int             blast;
        int             speed;
        bool            push;
        std::pair<int, int> Pos;
        bool            isAlive;
        std::string     type;
}               CharacValue;

class Config {
	public:
		Config();
		~Config();

                void                            loadFile(std::string);
                void                            saveConf(std::string file, std::vector<std::string> map, std::vector<CharacValue> value);

                std::vector<std::string>        getMap();
                std::vector<CharacValue>        getCharac();

	protected:
                void                                                    getMapConf();
                void                                                    getPlayerConf(int);
                void                                                    getPositionConfClass();
                std::vector<std::string>                                saveCharac(CharacValue, int);
                std::vector<std::string>                                saveMap(std::vector<std::string>);
                bool                                                    verifBool(std::string var);

                classPos                        _class;
                std::map <classPos, int>        _scenes;
                std::vector<std::string>        _confFile;
                std::vector<std::string>        _map;
                std::vector<CharacValue>        _perso;
	private:
};

#endif /* !CONFIG_HPP_ */
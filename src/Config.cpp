/*
** EPITECH PROJECT, 2018
** Config.cpp
** File description:
** Config
*/

#include "Config.hpp"

Config::Config()
{
        CharacValue tmp;
        _perso.push_back(tmp);
        _perso.push_back(tmp);
        _perso.push_back(tmp);
        _perso.push_back(tmp);
}
Config::~Config()
{
}

std::vector<std::string>                            Config::saveCharac(CharacValue value, int y)
{
        std::vector <std::string>     formap;

        formap.push_back("charac" + std::to_string(y+1));
        formap.push_back("bomb:" + std::to_string(value.bombs));
        formap.push_back("blast:" + std::to_string(value.blast));
        formap.push_back("speed:" + std::to_string(value.speed));
        formap.push_back("push:" + std::to_string(value.push));
        formap.push_back("posX:" + std::to_string(value.Pos.first));
        formap.push_back("posY:" + std::to_string(value.Pos.second));
        formap.push_back("isAlive:" + std::to_string(value.isAlive));
        formap.push_back("type:" + value.type);
        return(formap);
}

std::vector<std::string>                            Config::saveMap(std::vector<std::string> map)
{
        std::vector <std::string>     formap;

        formap.push_back("map");
        formap.push_back("{");
        for (int i = 0; i < map.size(); i++) {
                formap.push_back(map[i]);
        }
        formap.push_back("}");
        return(formap);
}

void                            Config::saveConf(std::string file, std::vector<std::string> map, std::vector<CharacValue> value)
{
        std::ofstream outfile (file);
        outfile << "charac" <<std::endl;
        outfile << "{" <<std::endl;
        for (int y = 0; y < 4; y++) {
                for (int i = 0; i < saveCharac(value[y], y).size(); i++) {
                        outfile << saveCharac(value[y], y)[i] << std::endl;
                }
        }
        outfile << "}" << std::endl;
        outfile << std::endl;
        for (int i = 0; i < saveMap(map).size(); i++) {
                outfile << saveMap(map)[i] << std::endl;
        }
        outfile.close();
}


void                            Config::getMapConf()
{
        int             i = _scenes.at(MAP) + 2;

        while (_confFile[i].compare("}") != 0) {
                _map.push_back(_confFile[i]);
                i++;
        }
}

void                            Config::getPlayerConf(int y)
{
        int             i = _scenes.at(CHARAC) + 2 + (y * 9);

        _perso[y].bombs = std::stoi(_confFile[i + 1].substr(_confFile[i + 1].find(":") + 1));
        _perso[y].blast = std::stoi(_confFile[i + 2].substr(_confFile[i + 2].find(":") + 1));
        _perso[y].speed = std::stoi(_confFile[i + 3].substr(_confFile[i + 3].find(":") + 1));
        _perso[y].push = verifBool(_confFile[i + 4].substr(_confFile[i + 4].find(":") + 1));
        _perso[y].Pos.first = std::stoi(_confFile[i + 5].substr(_confFile[i + 5].find(":") + 1));
        _perso[y].Pos.second = std::stoi(_confFile[i + 6].substr(_confFile[i + 6].find(":") + 1));
        _perso[y].isAlive = verifBool(_confFile[i + 7].substr(_confFile[i + 7].find(":") + 1));
        _perso[y].type = _confFile[i + 8].substr(_confFile[i + 8].find(":") + 1);
}

bool                            Config::verifBool(std::string var)
{
        if (var.compare("1") == 0)
                return true;
        else
                return false;
}

void                             Config::getPositionConfClass()
{
        for (int i = 0; i < _confFile.size(); i++) {
                if (_confFile[i].compare("charac") == 0)
                        _scenes.insert(std::pair<classPos, int>(CHARAC, i));
                if (_confFile[i].compare("map") == 0)
                        _scenes.insert(std::pair<classPos, int>(MAP, i));
        }
        if (_scenes.size() != 2)
                std::cout << "erreur" << std::endl;
}


void                            Config::loadFile(std::string file)
{
        std::ifstream			_file(file);
	std::string                     line;
        CharacValue     value;

        if (_file) {
                while (std::getline(_file, line)) {
		        _confFile.push_back(line);
                }
        }
        getPositionConfClass();
        for (int y = 0; y < 4; y++)
                getPlayerConf(y);
        getMapConf();
}

std::vector<std::string>        Config::getMap()
{
        return _map;
}

std::vector<CharacValue>        Config::getCharac()
{
        return _perso;
}
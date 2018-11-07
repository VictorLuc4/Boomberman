/*
** EPITECH PROJECT, 2018
** Personnage.hpp
** File description:
** Personnage
*/

#ifndef PERSONNAGE_HPP_
	#define PERSONNAGE_HPP_

class Personnage {
	public:
		void    moveLeft();
                void    moveRight();
                void    moveUp();
                void    moveDown();

                void    getMove(); // verif

                int     getPos(); // verif
                int     getPosX(); // verif
                int     getPosY();

                bool    isDie();
                bool    dropBombe(); // verif
                void    getPowerUp();
	protected:
	private:
                int     _blast;
                int     _speed;
                int     _nbBombs;
                bool    _isAlive;
                int     _score;
};

#endif /* !PERSONNAGE_HPP_ */

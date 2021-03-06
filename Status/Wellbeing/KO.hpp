#ifndef __KO_HPP__
#define __KO_HPP__
/**
 * @file KO.hpp
 * @copyright WTFPL v2
 * @author Elbert NYUNTING
 * @date 23/11/2016
 * @brief Fichier hpp définissant l'etat de santé d'un joueur lorsqu'il est assomé et peut revenir après chaque mi-temps ou marquage de but
*/

#include "Wellbeing.hpp"

class KO : public virtual Wellbeing{
    public:
    	KO();
    	~KO();
	std::shared_ptr<Wellbeing> returnToGame();

	std::shared_ptr<Wellbeing> goProne();
	std::shared_ptr<Wellbeing> getUp();
	std::shared_ptr<Wellbeing> knockedDown();
	std::shared_ptr<Wellbeing> knockedOut();
	std::shared_ptr<Wellbeing> getOut();
	std::shared_ptr<Wellbeing> backToNormal();
	private:

};

#endif


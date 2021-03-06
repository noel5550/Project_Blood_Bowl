#ifndef __OUT_HPP__
#define __OUT_HPP__
/**
 * @file Out.hpp
 * @copyright WTFPL v2
 * @author Elbert NYUNTING
 * @date 23/11/2016
 * @brief Fichier hpp définissant l'etat de santé d'un joueur lorsqu'il est mis hors du jeu (blessé grave, mort, prison). Dans aucun cas ce joueur peut etre remis dans le jeu. Etat puit.
*/

#include "Wellbeing.hpp"

class Out : public virtual Wellbeing{
    public:
    Out();
    ~Out();

	std::shared_ptr<Wellbeing> goProne();
	std::shared_ptr<Wellbeing> getUp();
	std::shared_ptr<Wellbeing> knockedDown();
	std::shared_ptr<Wellbeing> knockedOut();
	std::shared_ptr<Wellbeing> getOut();
	std::shared_ptr<Wellbeing> backToNormal();
	std::shared_ptr<Wellbeing> returnToGame();
   
	
};

#endif


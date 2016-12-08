#ifndef __BLITZTACKLED_HPP__
#define __BLITZTACKLED_HPP__
/**
 * @file BlitzTackled.hpp
 * @copyright WTFPL v2
 * @author Elbert NYUNTING
 * @date 23/11/2016
 * @brief Fichier hpp définissant l'etat de jouabilité d'un joueur qui a bloqué lors de son blitz, ce qui lui permet de bouger encore plus.
*/

#include "Playability.hpp"
class BlitzTackled : public virtual Playability{
    public:
   	BlitzTackled();
    	~BlitzTackled();
    	std::shared_ptr<Playability> blitzMovement();
	std::shared_ptr<Playability> donePlaying();

	std::shared_ptr<Playability> tackle();
	std::shared_ptr<Playability> blitz();
	std::shared_ptr<Playability> moving();	
	std::shared_ptr<Playability> passer();
	std::shared_ptr<Playability> blitzTackle();
	std::shared_ptr<Playability> GoForIt();
	std::shared_ptr<Playability> startPlaying();

};

#endif


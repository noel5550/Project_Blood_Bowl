#ifndef __MOVED_HPP__
#define __MOVED_HPP__
/**
 * @file Moved.hpp
 * @copyright WTFPL v2
 * @author Elbert NYUNTING
 * @date 23/11/2016
 * @brief Fichier hpp définissant l'etat de jouabilité d'un joueur qui a bougé dans son tour, il peut maintenant soit langer la balle, soit faire un GoForIt, soit terminer son tour.
*/

#include "Playability.hpp"
#include "../../Player/Player.hpp"
class Moved : public virtual Playability{
    public:
    Moved(Player player);
    ~Moved();
	void passer();
	void donePlaying();
	void GoForIt();
	Player getPlayer();

	void tackle();
	void blitz();
	void moving();
	void blitzMovement();
	void blitzTackle();
	void startPlaying();

	private:
	Player player_;	
};

#endif

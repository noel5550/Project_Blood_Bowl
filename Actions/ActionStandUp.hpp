#ifndef __ACTIONSTANDUP_HPP__
#define __ACTIONSTANDUP_HPP__
/**
 * @file ActionStandUp.hpp
 * @copyright WTFPL v2
 * @author Elbert NYUNTING
 * @date 16/10/2016
 * @brief Fichier hpp définissant l'action d'un joueur se relève
*/

#include <queue>
#include <vector>
#include "Actions.hpp"
#include "../Player/Player.hpp"

class Actions;
class Player;
class ActionStandUp : public virtual Actions{
    public:
	ActionStandUp(Player actingPlayer);
	~ActionStandUp();
	void doAction();
	Player getActingPlayer();
	
	
    private:
	Player actingPlayer_;
};

#endif


#ifndef __ACTIONBLOCK_HPP__
#define __ACTIONBLOCK_HPP__
/**
 * @file ActionBlock.hpp
 * @copyright WTFPL v2
 * @author Elbert NYUNTING
 * @date 08/10/2016
 * @brief Fichier hpp définissant l'action de bloquer un joueur
*/

#include <queue>
#include <vector>
#include "Actions.hpp"
#include "../Player/Player.hpp"

class Actions;
class Player;
class ActionBlock: public virtual Actions {
    public:
	ActionBlock(Player actingPlayer);
	~ActionBlock();
	void doAction(Player oppoPlayer); //check surrounding, then roll dice(s), then apply changes
	int countAdvantage(Player oppoPlayer);
	void bothDown(Player actingPlayer, Player oppoPlayer);
	void pushed(Player oppoPlayer);
	void stumble(Player oppoPlayer);
	Player getActingPlayer();
	
	
    private:
	Player actingPlayer_;
	Game game_;
};

#endif

/**
 * @file ActionBlock.cpp
 * @copyright WTFPL v2
 * @author Elbert NYUNTING
 * @date 06/10/2016
 * @brief Fichier source définissant l'action de blocker un joueur adverse (et tout ce qui peut y arriver)
*/

#include <vector>
#include "ActionBlock.hpp"
#include "../Dice/Dice.hpp"
#include "../Player/Player.hpp"

class Dice;
using namespace std;

/**
 * @brief Constructeur de ActionBlock
 * @param actingPlayer le joueur actif
 * @pre actingPlayer doit être un joueur de l'équipe jouant en jeu
 */
ActionBlock::ActionBlock(Player actingPlayer){
	actingPlayer_ = actingPlayer;
}

/**
 * @brief Destructeur de ActionBlock
 */
ActionBlock::~ActionBlock(){}

/**
 * @brief méthode retournant le joueur actif
 * @return le joueur actif
 */
Player ActionBlock::getActingPlayer(){
	return actingPlayer_;
}

/**
 * @brief Méthode permettant actingPlayer_ de bloquer oppoPlayer
 * @details actingPlayer_ aura plus ou moins de chance de bloquer oppoPlayer par rapport à leur différence de STR et s'il a un avantage de support ou non
 * @details Les avantages se présente sous la forme de nombre de dés (min 1 dé, max 3 dés) et le coach peut choisir quel résultat à choisir des dés lancés
 * @details Les joueurs qui ont Block peuvent résister l'effet d'un double KO
 * @details Si oppoPlayer a Dodge, il peut changer l'effet d'un leger KO en Push
 * @details Un Push pousse oppoPlayer dans une case adjacentes disponibles aléatoirement, s'il n'y a pas de case disponible, oppoPlayer sera KO
 * @param oppoPlayer, le joueur victime d'une tentative de blockage
 */
void ActionBlock::doAction(Player oppoPlayer){
	int advantage;
	unsigned int diceRes;
	unsigned int diceChoice;
	int finalRes;
	bool inControl = true;
	vector<unsigned int> diceStack;
	Dice d6(1, 6);
	
	advantage = countAdvantage(oppoPlayer);
	if (advantage < 0){
		advantage *= -1;
		inControl = false;
	}
	
	
	std::cout << "Vous allez lancer " <<advantage<< " dés!" <<std::endl;
	if(!inControl){
		std::cout << "Mais le pire résultat sera pris!" <<std::endl;
	}
	
	
	for(int i = 0; i <= advantage; ++i){
		diceRes = d6.throwDiceSingle();
		diceStack.push_back(diceRes);
		
		std::cout<<"Lancée "<<advantage<<"!"<<std::endl;
		
		if(diceRes == 1){
			std::cout << "Blockage echoue!" << std::endl;
		}else if(diceRes == 2){
			std::cout << "Les deux jouers à terre!" << std::endl;
		}else if(diceRes == 3 || diceRes == 4){
			std::cout << "Joueur adverse poussé!" << std::endl;
		}else if(diceRes == 5){
			std::cout << "Joueur adverse à terre!" << std::endl;
		}else if(diceRes == 6){
			std::cout << "Joueur adverse VRAIMENT à terre!" << std::endl;
		}		
	}
	
	if(diceStack.size() > 1){
		if(inControl){
			std::cout << "Choisissez quel résultat vous allez choisir!" <<std::endl;
			std::cin >> diceChoice;
			if(diceChoice>diceStack.size() || diceChoice>3){
				std::cout << "OY! Ca triche pas içi!" <<std::endl;
			}
		}else{
			diceChoice = 6;
			for(unsigned int i = 0; i < diceStack.size(); ++i){
				if(diceChoice > diceStack.at(i)){
					diceChoice = diceStack.at(i);
				}
			}
		}	
	}else{
		diceChoice = 1;
	}
	
	finalRes = diceStack.at(diceChoice - 1);
	
	if(finalRes == 1){ //failed block, attacker down
		actingPlayer_.etatATerre();
		std::cout << "Et voila! Il est à terre pour tenter un blockage! Comme quoi il ne faut pas embaucher des amateurs!" <<std::endl;
	
	}else if(finalRes == 2){ 
		bothDown(actingPlayer_, oppoPlayer);		
	
	}else if(finalRes == 3 || finalRes == 4){ //pushed
		pushed(oppoPlayer);	
		
	}else if(finalRes == 5){ 
		stumble(oppoPlayer);
		
	}else if(finalRes == 6){ //knocked down, no evading this bad boy
		oppoPlayer.etatATerre();
		std::cout << "OUCH! Ca doit faire mal, ça!" <<std::endl;
	}
	
}

/**
 * @brief méthode retournant l'avantage de actifPlayer_ par rapport à oppoPlayer
 * @return le nombre d'avantage actifPlayer_ a
 * @detail advantage est le nombre de dés utilisés, donc pas plus que 3
 */

int ActionBlock::countAdvantage(Player oppoPlayer){
	int advantage = 1;
	if(actingPlayer_.getStr() > oppoPlayer.getStr()){
		++advantage;
		if(actingPlayer_.getStr() >= oppoPlayer.getStr() * 2 + 1){
			++advantage;
		}
	}else if(actingPlayer_.getStr() < oppoPlayer.getStr()){
		--advantage;
		if(actingPlayer_.getStr() <= oppoPlayer.getStr() * 2 + 1){
			--advantage;
		}
	}
	 
	if(game_.outnumbered(actingPlayer_)){
		--advantage;
	}
	
	if(game_.outnumbered(oppoPlayer)){
		++advantage;
	}
	
	if(advantage < -3){
		advantage = -3;
	}else if(advantage > 3){
		advantage = 3;
	}
	
	return advantage;
}

/**
 * @brief méthode simulant l'effet de deux joueurs se tapant desus
 * @detail le(s) joueur(s) qui a le skill Block ne sera pas à terre
 */
void ActionBlock::bothDown(Player actingPlayer, Player oppoPlayer){
	//both down, unless the guy with Block skill
	if(actingPlayer_.block() && oppoPlayer.block()){ //none down
		std::cout << "Les deux joueurs se cognent et rien ne se passe!" <<std::endl;
	}else if(actingPlayer_.block()){ //opposing player down
		oppoPlayer.etatATerre();
		std::cout << "BOOM! Ils se cognent mais un est nettement plus solide que l'autre!" <<std::endl;
	}else if(oppoPlayer.block()){//acting player down et turnover
		actingPlayer_.etatATerre();
		std::cout << "BOOM! Ils se cognent mais un est nettement plus solide que l'autre!" <<std::endl;
		game_.turnover(actingPlayer_);
	}else{ //both down, turnover
		actingPlayer_.etatATerre();
		oppoPlayer.etatATerre();
		std::cout << "HA! Ils se cognent et sont tous les deux à terre!" <<std::endl;
		game_.turnover(actingPlayer_);
	}
}

/**
 * @brief méthode simulant l'effet d'un joueur qui est poussé
 * @detail oppoPlayer sera pausé vers une case adjacente aléatoire
 * @detail Si pas de case adjacente libre, oppoPlayer sera assomé
 */
void ActionBlock::pushed(Player oppoPlayer){
	int spot = game_.freeSpot(oppoPlayer);
	if(spot>0){		//if there's space, pushed to a random space. Yes, it's not REALLY Blood Bowl, but cmon, man
		game_.pushBack(oppoPlayer);
		std::cout << "Et il s'est fait poussé!" <<std::endl;
	}else{ //if there's no space, attacking player downed
		oppoPlayer.etatATerre();
		std::cout << "Manque de place, il s'est fait terrassé" <<std::endl;
	}
}

/**
 * @brief méthode simulant l'effet d'un joueur terrassé
 * @detail si oppoPlayer a le skill Dodge, il ne sera que poussé (avec les effets qui vont avec)
 */
void ActionBlock::stumble(Player oppoPlayer){
	if(oppoPlayer.dodges()){
		pushed(oppoPlayer);
	}else{
		oppoPlayer.etatATerre();
		std::cout << "OUCH! Ca doit faire mal, ça!" <<std::endl;
	}
}


/*!
 * @file Thrower.cpp
 * @author Elbert NYUNTING
 * @brief Protoype
 */

#include <iostream>
#include <vector>
#include "Thrower.hpp"
using namespace std;

/*!
*@brief Constructeur des Throwers
*@param type: int de type de Lineman (humain, elfe ou orc)
*@pre 1 <= type <= 3
*@complexite Constante
*/
Thrower::Thrower(int type){
		if (type = 1){
			ma = 6;
			st = 3;
			ag = 3;
			av = 8;
			xp = 0;
			lvl = 1;
		}else if (type = 2){
			ma = 6;
			st = 3;
			ag = 4;
			av = 7;
			xp = 0;
			lvl = 1;
		}else if (type = 3){
			ma = 5;
			st = 3;
			ag = 3;
			av = 8;
			xp = 0;
			lvl = 1;
		}
}
#include "Block.hh"

/**
 * Funkcja inicjujaca poszczegolne Blocki - rotory
 * @param const char *StrmWe
 * @param const char *StrmWy
 * @param Vector3 scale
 * @param double angle
 * @param Vector3 trans
 * @return Block rotor
 */
Block::Block(const char * StrmWe, const char * StrmWy, Vector3 scale,
 Vector3 trans, double angle){
    
    this->Init_The_Figure(StrmWe,StrmWy,28,scale, trans, angle);
    // this->vect_in_use2 += this->vect_in_use;
    // this->vect_used2 += this->vect_used;
    // return *this;
}







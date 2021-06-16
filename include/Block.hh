#pragma once

#include "GranBlock.hh"
#include "Vector3.hh"
#include "matrix3.hh"

/**
 * \brief Klasa Block
 * 
 * Klasa pozwalajaca operowac na Blocku - Rotorze 
 * Klasa dziedziczy po klasie GranBlock
 * 
 */
class Block : public GranBlock
{
    private:

    Vector3 rotor[28];
    
    public:

    Block(){};    /**< Konstruktor poczatkowy */

    Block(const char * StrmWe, const char * StrmWy, 
    Vector3 scale, Vector3 trans, double angle);     /**< Konstruktor */

    // Block InitOne (const char * StrmWe, const char * StrmWy, 
    // double scalex, double scaley, double scalez, double trans_x, 
    // double trans_y, double trans_z, double angle);  ///<Funkcja inicjujaca figure 

};
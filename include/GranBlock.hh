#pragma once

#include "Vector3.hh"
#include "matrix3.hh"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <cassert>
#include <unistd.h>
#include <vector>

/**
 * \brief Klasa Drona
 * 
 * Klasa pozwalajaca operowac na figurze 
 * 
 */
class GranBlock{

	private:

	std::vector<Vector3> figure; /**< Pomocnicza figura ktora pozwala dzialac na prostopadloscianie i rotorach */

	public:

	// Vector3 operator[](int Ind) const { return figure[Ind];}; ///< wypisywanie

	// Vector3 &operator[](int Ind) {return figure[Ind];};	///< wpisywanie

    double toradians(double angle); ///< Funkcja zmieniajaca kat na radiany

	GranBlock Init_The_Figure(const char * StrmWe, const char * StrmWy, double num_of_peak, Vector3 scale,
 	Vector3 trans, double angle); ///<Funkcja inicjujaca figury i odpowiednio je zmienia, obraca, wykonuje translacje i skaluje

	// GranBlock (const char * StrmWe, const char * StrmWy, double num_of_peak, double scalex, double scaley, double scalez,
 	// double trans_x, double trans_y, double trans_z, double angle); 
};
#ifndef PROSTOPADL_HH
#define PROSTOPADL_HH

#include "matrix3.hh"
#include "size.hh"
#include "GranBlock.hh"
// #include "coordinates.hh"
#include "Vector3.hh"
#include <string.h>
#include <iostream>
#include <iomanip>
#include "../include/lacze_do_gnuplota.hh"
#include <unistd.h>
#include <fstream>
#include "GranBlock.hh"

/**
 * \brief Klasa Prostopadloscianu
 * 
 * Klasa pozwalajaca operowac na wierzcholkach prostopadloscianu 
 * Klasa dziedziczy po klasie GranBlock
 * 
 */
class Prostopadl : public GranBlock
{
  /*
   *  Tutaj trzeba wstawic definicje odpowiednich pol i metod prywatnych
   */
  private:

  Vector3 pro [NOPOINTS]; /**< Tablica Wektorow 3D (Wierzcholkow o trzech skladowych) */
  
  public:

  Prostopadl(Vector3 [NOPOINTS]);             //Konstruktor klasy 

  Prostopadl();                               // Konstruktor klasy

  Prostopadl get_corp(const char *Name){
    Prostopadl temp;
    double x,y,z; 
    std::ifstream FileWe(Name);
    for(int i = 0; i < NOPOINTS; ++i){
      FileWe >> x >> y >> z;
      temp(i,0) = x; 
      temp(i,1) = y;
      temp(i,2) = z;
      }
      return temp;
    };

  Vector3 mid; /**< Wspolrzedne srodka prostopadloscianu*/

  Vector3 angles; /**< katy obrotu */

  Matrix3 matrixtmp;  /**< Macierz obrotu */

  Prostopadl (const char * StrmWe, const char * StrmWY, Vector3 scale, double angle, Vector3 trans);

  // Prostopadl::Prostopadl(const std::string &name, const Vector3 &tmp, const Prostopadl &pro) : Scene_object(name,tmp,pro){

  // };

  void turnagain(); /**< Funkcja obracajaca prostopadloscian jeszcze raz */

  Prostopadl operator * (const Matrix3 &matrix); ///< Przeciazenie operatora mnozenia wierzcholkow Prostopadla razy macierz

  Prostopadl move (const Vector3 &vec);  ///<Metoda przesuniecia prostopadloscianu o wektor

  Prostopadl operator * (const Matrix<double,4> &matrix); ///< Przeciazenei operatora mnozenia wierzcholkow razy macierz wspolna translacji i obrotu

  void moving(Vector3 &vec, const char *sNazwaPliku, PzG::LaczeDoGNUPlota Lacze); ///<Animacja przesuniecia

  Prostopadl operator + (const Vector3 vec2);  ///<Przeciazenie operatora dodawania wektora do wierzcholkow prostopadloscianu

  Prostopadl operator - (const Vector3 vec2); ///<Przeciazenie operatora odejmowania wektora do wierzcholkow prostopadloscianu

  double  &operator () (unsigned int row, unsigned int column); ///<Odpowiednie operatory indeksowania i poruszania sie po wierzcholkach prostopadloscianu

  const double  &operator () (unsigned int row, unsigned int column) const; ///<Odpowiednie operatory indeksowania i poruszania sie po wierzcholkach prostopadloscianu
    
  const Vector3 &operator () (unsigned int row) const; ///<Odpowiednie operatory indeksowania i poruszania sie po wierzcholkach prostopadloscianu

  void turn(double const ang, char which, Prostopadl &loc);  ///<Metoda obrotu prostopadloscianu o dany kat i os

  void turning(Prostopadl &pro, const char *sNazwaPliku, double const ang, double const howm, PzG::LaczeDoGNUPlota Lacze, char which);   //Animacja obrotu Prostopadla2D

  bool operator == (const Prostopadl &Pr);

  double x_of_end(double x_position, double angle, double lenght);

  double y_of_end(double y_position, double angle, double lenght);

  bool Save(const char *sNazwaPliku); ///<Metoda zapisujaca wierzcholki do pliku
    
};

std::ostream& operator << ( std::ostream &stream, const Prostopadl &Pr); ///<Operator wyswietlania wierzcholkow

#endif

// Executables must have the following defined if the library contains
// doctest definitions. For builds with this disabled, e.g. code shipped to
// users, this can be left out.
#ifdef ENABLE_DOCTEST_IN_LIBRARY
#define DOCTEST_CONFIG_IMPLEMENT
#include "../tests/doctest/doctest.h"
#endif

#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <cmath>
#include <cassert>
#include <unistd.h>
#include "scena.hh"
#include "exampleConfig.h"
#include "example.h"
#include "Vector3.hh"
#include "matrix.hh"
#include "../include/lacze_do_gnuplota.hh"

using namespace std;


/*!
 * Simple main program that demontrates how access
 * CMake definitions (here the version number) from source code.
 * 
 * EDIT: dodane kreowanie wektorow i macierzy plus obsluga lacza do gnuplota
 */

int main() {
  std::cout << "Project Rotation 3D based on C++ Boiler Plate v"
            << PROJECT_VERSION_MAJOR /*duże zmiany, najczęściej brak kompatybilności wstecz */
            << "."
            << PROJECT_VERSION_MINOR /* istotne zmiany */
            << "."
            << PROJECT_VERSION_PATCH /* naprawianie bugów */
            << "."
            << PROJECT_VERSION_TWEAK /* zmiany estetyczne itd. */
            << std::endl;

PzG::LaczeDoGNUPlota Lacze;  // Ta zmienna jest potrzebna do wizualizacji
                                // rysunku Prostopadla

scena Scena;

  Lacze.ZmienTrybRys(PzG::TR_3D);
  Lacze.Inicjalizuj();
  Lacze.UstawZakresX(0,200);
  Lacze.UstawZakresY(0,200);
  Lacze.UstawZakresZ(0,120);

  Lacze.UstawRotacjeXZ(64,65);
   //-------------------------------------------------------
   //  Wspolrzedne wierzcholkow beda zapisywane w pliku "Prostopadl.dat"
   //  Ponizsze metody powoduja, ze dane z pliku beda wizualizowane
   //  na dwa sposoby:
   //   1. Rysowane jako linia ciagl o grubosci 2 piksele
   //
  Lacze.DodajNazwePliku(PLASZCZYZNA_WZ);
  
  PzG::InfoPlikuDoRysowania *col_corp = &Lacze.DodajNazwePliku(SZESCIAN_ZM);
  PzG::InfoPlikuDoRysowania *col_rot1 = &Lacze.DodajNazwePliku(ROTORY_1);
  PzG::InfoPlikuDoRysowania *col_rot2 = &Lacze.DodajNazwePliku(ROTORY_2);
  PzG::InfoPlikuDoRysowania *col_rot3 = &Lacze.DodajNazwePliku(ROTORY_3);
  PzG::InfoPlikuDoRysowania *col_rot4 = &Lacze.DodajNazwePliku(ROTORY_4);

  col_corp->ZmienKolor(1);
  col_rot1->ZmienKolor(2);
  col_rot2->ZmienKolor(2);
  col_rot3->ZmienKolor(2);
  col_rot4->ZmienKolor(2);

  PzG::InfoPlikuDoRysowania *col_corp_v2 = &Lacze.DodajNazwePliku(SZESCIAN_ZM_V2);
  PzG::InfoPlikuDoRysowania *col_rot1_v2 = &Lacze.DodajNazwePliku(ROTORY_1_V2);
  PzG::InfoPlikuDoRysowania *col_rot2_v2 = &Lacze.DodajNazwePliku(ROTORY_2_V2);
  PzG::InfoPlikuDoRysowania *col_rot3_v2 = &Lacze.DodajNazwePliku(ROTORY_3_V2);
  PzG::InfoPlikuDoRysowania *col_rot4_v2 = &Lacze.DodajNazwePliku(ROTORY_4_V2);

  col_corp_v2->ZmienKolor(3);
  col_rot1_v2->ZmienKolor(4);
  col_rot2_v2->ZmienKolor(4);
  col_rot3_v2->ZmienKolor(4);
  col_rot4_v2->ZmienKolor(4);

  
  Lacze.Rysuj();
  
  cout << "Beginning" << endl;
  Scena.Initiation_begin_obstacles(Lacze);

  Vector3 position;
  cout << "m - menu" << endl;
  cout << "a - choose active drone" << endl;
  cout << "p - parameters of the flight" << endl;
  cout << "w - number of used vectors" << endl;
  cout << "s - scout" << endl;
  cout << "o - add obstacle" << endl;
  cout << "d - delete obstacle" << endl;
  cout << "k - end" << endl;

  Drone drone1, drone2;
  Drone *drn;

  double arg1[] = {20,20,0};
  drone1.position[0] = Vector3(arg1);
  drone1.Engage2(0, drone1.position[0], NamesFilesLoc_V1, NamesFilesProp_V1,0);
  double arg2[] = {20,60,0};
  drone2.position[0] = Vector3(arg2);
  drone2.Engage2(0, drone2.position[0], NamesFilesLoc_V2, NamesFilesProp_V2,0);
  Lacze.Rysuj();

  drone1.position[1] = drone1.position[0];
  drone2.position[1] = drone2.position[0];

  drone1.set_mid(drone1.position[0]);
  drone1.set_obst(drone1.get_corp(SZESCIAN_ZM));
  drone1.set_name("Drone1");
  drone2.set_mid(drone2.position[0]);
  drone2.set_obst(drone2.get_corp(SZESCIAN_ZM_V2));
  drone2.set_name("Drone2");

  Scena.Add_drone(drone1);
  Scena.Add_drone(drone2);

  
  Scena.Objects.push_front(make_shared<Drone>(drone2));
  Scena.Objects.push_front(make_shared<Drone>(drone1));

  double choice_drone = 0;
  double angle1=0, angle2=0;
  double tmp1 = 0, tmp2 = 0;
  char choice = 'a';
  while (choice != 'k'){
  
    Lacze.Rysuj();
    switch( choice ){

      case 'p':{ 
        double lenght;
        if(choice_drone == 1){
          cout << "Enter the direction (angle in degrees): ";
          cin >> angle1;
          cout << "Enter the lenght of the flight: ";
          cin >> lenght;
          angle1 += tmp1;
          Scena.Make_Path(Lacze, choice_drone, Path_V1, lenght, angle1);
          (*drn).Relocate(Scena.Objects,choice_drone, angle1, lenght, Lacze, NamesFilesLoc_V1, NamesFilesProp_V1);
          Lacze.UsunNazwePliku(Path_V1);
          tmp1 = angle1;
          }
        else if(choice_drone == 2){
          cout << "Enter the direction (angle in degrees): ";
          cin >> angle2;
          cout << "Enter the lenght of the flight: ";
          cin >> lenght;
          angle2 += tmp2;
          Scena.Make_Path(Lacze, choice_drone, Path_V2, lenght, angle2);
          (*drn).Relocate(Scena.Objects,choice_drone, angle2,lenght, Lacze, NamesFilesLoc_V2, NamesFilesProp_V2);
          Lacze.UsunNazwePliku(Path_V2);
          tmp2 = angle2;
        }
        else{
          cout << "You have choosen wrong drone " << endl;
        }
        (*drn).position[1] = (*drn).position[0];
      break;}

      case 'm':{
        cout << "m - menu" << endl;
        cout << "a - choose active drone" << endl;
        cout << "p - parameters of the flight" << endl;
        cout << "w - number of used vectors" << endl;
        cout << "s - scout" << endl;
        cout << "o - add obstacle" << endl;
        cout << "d - delete obstacle" << endl;
        cout << "k - end" << endl;
        break;}

      case 'w':{
        cout << "Amount of Vectors in use: " << drn->position[0].amount_active_vectors() << endl;
        cout << "Amount of Vectors used: " << drn->position[0].amount_of_all_vectors() << endl;
        break;}

      case 's':{
        if(choice_drone == 1){
        (*drn).Scouting(angle1, Lacze, NamesFilesLoc_V1, NamesFilesProp_V1);}
        else if(choice_drone == 2){
        (*drn).Scouting(angle2, Lacze, NamesFilesLoc_V2, NamesFilesProp_V2);}
        break;}

      case 'k':{
        cout << "the end" << endl;
        Scena.delete_at_the_end(Lacze);
        break;}

      case 'o':{
        Scena.Create_Obstacle(Lacze);
        break;}

      case 'd':{
        Scena.Delete_Obstacle(Lacze);
        break;}

      case 'a':{
        choice_drone = 0;
        while(choice_drone != 1 && choice_drone != 2){
        cout << "choose which drone would you fly (1,2)" << endl;
        cin >> choice_drone;
        if(choice_drone == 1 || choice_drone == 2){
          Scena.choose_drone(choice_drone);
          drn = Scena.getdrone();
          cout << "You have choosen drone at the position: " << endl;
          cout << drn->position[0] << endl;}
          else{
            cout << "Wrong choice" << endl;
            choice_drone = 0;
          }}
        break;}

      default:{
        cout << "Wrong Option" << endl;
      }}

      cout << "Your choice (m-menu)" << endl;
      cin >> choice;

      if(choice_drone == 1){
          Scena.GetActiveDrone(0) = *drn;
        }
      else if(choice_drone == 2){
        Scena.GetActiveDrone(1) = *drn;
        } 
    }

  Dummy d = Dummy();
  return d.doSomething() ? 0 : -1;
}



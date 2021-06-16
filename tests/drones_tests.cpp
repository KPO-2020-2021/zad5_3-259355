#include "../tests/doctest/doctest.h"

// This is all that is needed to compile a test-runner executable.
// More tests can be added here, or in a new tests/*.cpp file.
#include "scena.hh"

TEST_CASE("Drone flight"){
    PzG::LaczeDoGNUPlota Lacze;
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
    Drone drone1;
    double arg1[] = {20,20,0};
    drone1.position[0] = Vector3(arg1);
    drone1.Engage2(0, drone1.position[0], NamesFilesLoc_V1, NamesFilesProp_V1,0);
    double angle, lenght;
    angle = 35;
    lenght = 100;
    
    SUBCASE("Cheking position after going up"){
        for(;drone1.position[0][2] <= 80; drone1.position[0][2] += 2){
            drone1.Engage2(0,drone1.position[0], NamesFilesLoc_V1, NamesFilesProp_V1, 1);
        }
        drone1.position[0][2] -= 2;        
        double x_position = 20;
        double y_position = 20;
        double z_position = 82;
    CHECK((drone1.position[1][0] - x_position) <= MIN_DIFF);
    CHECK((drone1.position[1][1] - y_position) <= MIN_DIFF);
    CHECK((drone1.position[1][2] - z_position) <= MIN_DIFF);}

    SUBCASE("Cheking position after changing orientation"){
    double angletemp = 0;
    for(; angletemp <= angle; angletemp += 5 ){
            drone1.Engage2(angletemp,drone1.position[0], NamesFilesLoc_V1, NamesFilesProp_V1, 2);
            usleep(100000);
            Lacze.Rysuj();
        }
        angletemp -= 5;        
        double x_position = 20;
        double y_position = 20;
        double z_position = 82;
    CHECK((drone1.position[1][0] - x_position) <= MIN_DIFF);
    CHECK((drone1.position[1][1] - y_position) <= MIN_DIFF);
    CHECK((drone1.position[1][2] - z_position) <= MIN_DIFF);}

    SUBCASE("Cheking end position"){
        double x_of_turn = 1;
        double y_of_turn = 1;
        double step; 
        x_of_turn = drone1.x_of_end(drone1.position[0][0],angle,lenght);
        x_of_turn = (x_of_turn - drone1.position[0][0])/60;
        y_of_turn = drone1.y_of_end(drone1.position[0][1],angle,lenght);
        y_of_turn = (y_of_turn - drone1.position[0][1])/60;

        std::cout << "Going forward ..." << std::endl;
        for(int i = 0; i <= 60; drone1.position[0][0] += x_of_turn, drone1.position[0][1] += y_of_turn, ++i){
            step = 3;
            drone1.Engage2(angle,drone1.position[0], NamesFilesLoc_V1, NamesFilesProp_V1, step);
        }
        drone1.position[0][0] -= 1;
        drone1.position[0][1] -= 1;        
        double x_position = 101.9152044289;
        double y_position = 77.3576436351;
        double z_position = 82;
    CHECK((drone1.position[1][0] - x_position) <= MIN_DIFF);
    CHECK((drone1.position[1][1] - y_position) <= MIN_DIFF);
    CHECK((drone1.position[1][2] - z_position) <= MIN_DIFF);}

    SUBCASE("Cheking end position"){
        for(;drone1.position[0][2] >= 0; drone1.position[0][2] -= 2){
            drone1.Engage2(angle,drone1.position[0], NamesFilesLoc_V1, NamesFilesProp_V1, 4);
        }
        double x_position = 101.9152044289;
        double y_position = 77.3576436351;
        double z_position = 0;
    CHECK((drone1.position[1][0] - x_position) <= MIN_DIFF);
    CHECK((drone1.position[1][1] - y_position) <= MIN_DIFF);
    CHECK((drone1.position[1][2] - z_position) <= MIN_DIFF);
    }
    SUBCASE("Checking amount of used vectors"){
        double vec_in_use = 22486;
        double vec_used = 185943;
    CHECK(drone1.position[0].amount_active_vectors() == vec_in_use);
    CHECK(drone1.position[0].amount_of_all_vectors() == vec_used);
    }
}

TEST_CASE("Inheritance of functions"){

   Prostopadl pro;
   Vector3 scale, trans;
   double angle = 0;

   pro.Init_The_Figure(NamesFilesLoc_V1[0],NamesFilesProp_V1[0], NOPOINTS, scale, trans, angle);
   CHECK( 1 == 1 ); 
}


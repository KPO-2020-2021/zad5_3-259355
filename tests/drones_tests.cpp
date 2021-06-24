#include "../tests/doctest/doctest.h"

// This is all that is needed to compile a test-runner executable.
// More tests can be added here, or in a new tests/*.cpp file.
#include "scena.hh"

TEST_CASE("Drone flight"){

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
        double vec_in_use = 21463;
        double vec_used = 171672;
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

TEST_CASE("Scene functions"){
  PzG::LaczeDoGNUPlota Lacze;
  scena Scena;
  Drone drone1, drone2;
  Drone *drn;

  double arg1[] = {20,20,0};
  drone1.position[0] = Vector3(arg1);
  drone1.Engage2(0, drone1.position[0], NamesFilesLoc_V1, NamesFilesProp_V1,0);
  double arg2[] = {20,60,0};
  drone2.position[0] = Vector3(arg2);
  drone2.Engage2(0, drone2.position[0], NamesFilesLoc_V2, NamesFilesProp_V2,0);

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

  
  Scena.Objects.push_front(std::make_shared<Drone>(drone2));
  Scena.Objects.push_front(std::make_shared<Drone>(drone1));

  SUBCASE("Index of drone and its position"){
        Scena.choose_drone(1);
        drn = Scena.getdrone();
    CHECK( Scena.get_active_num() == 0);
    CHECK((*drn).position[0] == drone1.position[0]);
  }
  SUBCASE("Checking if both drones are added"){
      CHECK(Scena.Objects.size() == 2); 
  }
  SUBCASE("Checking if both drones are added and 4 obstacles"){
      Scena.Initiation_begin_obstacles(Lacze);
      CHECK(Scena.Objects.size() == 6); 
  }
  SUBCASE("Checking types of Objects on list"){
      std::list<std::shared_ptr<Scene_object>>::iterator it = Scena.Objects.begin();
      CHECK((*it)->get_name() == "Drone1");
  }
  SUBCASE("Flying and checking if theres no obstacles"){
    int i = 0;
    for(;drone1.position[0][2] <= 80; drone1.position[0][2] += 2){
        drone1.Engage2(13,drone1.position[0], NamesFilesLoc_V1, NamesFilesProp_V1, 1);      
    }
    for(; i <= 13; i += 5 ){
        drone1.Engage2(i,drone1.position[0], NamesFilesLoc_V1, NamesFilesProp_V1, 1);
    }
    i -= 5;      
    double x_of_turn = 1;
    double y_of_turn = 1;
    double step;

    x_of_turn = drone1.x_of_end(drone1.position[0][0],13,140);
    x_of_turn = (x_of_turn - drone1.position[0][0])/60;
    y_of_turn = drone1.y_of_end(drone1.position[0][1],13,140);
    y_of_turn = (y_of_turn - drone1.position[0][1])/60;

    for(int i = 0; i <= 60; drone1.position[0][0] += x_of_turn, drone1.position[0][1] += y_of_turn, ++i){
        step = 3;
        drone1.Engage2(13,drone1.position[0], NamesFilesLoc_V1, NamesFilesProp_V1, step);
    }
    drone1.position[0][0] -= 1;
    drone1.position[0][1] -= 1;   

    drone1.set_obst(drone1.get_corp(SZESCIAN_ZM));
      while(!drone1.check_landing(1,Scena.Objects)){
        double x_of_turn = 1;
        double y_of_turn = 1;
        double step;

        x_of_turn = drone1.x_of_end(drone1.position[0][0],13,40);
        x_of_turn = (x_of_turn - drone1.position[0][0])/60;
        y_of_turn = drone1.y_of_end(drone1.position[0][1],13,40);
        y_of_turn = (y_of_turn - drone1.position[0][1])/60;

        for(int i = 0; i <= 60; drone1.position[0][0] += x_of_turn, drone1.position[0][1] += y_of_turn, ++i){
            step = 3;
            drone1.Engage2(13,drone1.position[0], NamesFilesLoc_V1, NamesFilesProp_V1, step);
        }
        drone1.position[0][0] -= 1;
        drone1.position[0][1] -= 1;  
        CHECK(drone1.check_landing(1,Scena.Objects) == false);
    }
    CHECK(drone1.position[0][0] - 186.4036261970 <= MIN_DIFF );
    CHECK(drone1.position[0][1] - 56.8790405591 <= MIN_DIFF );
    CHECK(drone1.position[0][2] - 82 <= MIN_DIFF );
  }
}




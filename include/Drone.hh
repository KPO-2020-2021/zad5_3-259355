#pragma once

#include "Prostopadl.hh"
#include "Block.hh"
#include "Vector3.hh"
#include <iomanip>
#include "Scene_object.hh"
// #include "Piramid.hh"
// #include "Cuboid_obstacle.hh"
// #include "Mount_with_ridge.hh"
#include <memory>
#include <list>


/**
 * \brief Klasa Drona
 * 
 * Klasa pozwalajaca operowac na dronie 
 * Klasa dziedziczy po klasie Block oraz Prostopadl
 * 
 */
class Drone: public Block, public Prostopadl, public Scene_object
{

    private:

    Block *rotor[4]; /**< 4 rotory */

    Prostopadl *corp; /**< Korpus Drona */

    public:

    Drone (){};

    Vector3 position[2];    /**< Wektor przetrzymujacy wspolrzedne poczatku lotu i konca*/

    void Init(const char *NamesFilesLocal[], int step);   /**< Funkcja inicjujaca poczatkowego drona */

    void Engage2(double angle, Vector3 position, const char *NamesFilesLocal[], const char *NamesFilesProper[], int step); /**< Funkcja wykonujaca operacje na dronie obraca, inicjuje i transponuje */

    // void Relocate(Vector3 begin_position,double drone_num, double angle, double lenght_of_path, PzG::LaczeDoGNUPlota &Lacze, const char *NamesFilesLocal[], const char *NamesFilesProper[]);    /**< Funkcja wykonujaca animacje lotu drona */

    void Relocate(std::list<std::shared_ptr<Scene_object>> Obstacles,unsigned int number, double angle, double lenght_of_path, PzG::LaczeDoGNUPlota &Lacze, const char *NamesFilesLocal[], const char *NamesFilesProper[]);

    void Scouting(double angle, PzG::LaczeDoGNUPlota &Lacze, const char *NamesFilesLocal[], const char *NamesFilesProper[]);

    void GoForward(double angletemp, double lenght_of_path,PzG::LaczeDoGNUPlota &Lacze, const char *NamesFilesLocal[],const char *NamesFilesProper[]);

    void Orientation(double angle, double angletemp, PzG::LaczeDoGNUPlota &Lacze, const char *NamesFilesLocal[], const char *NamesFilesProper[]);

    void GoDownAndUp(double up_down,double angletemp, PzG::LaczeDoGNUPlota &Lacze, const char *NamesFilesLocal[],const char *NamesFilesProper[]);

//     bool check_landing(unsigned int num_drone, std::list<std::shared_ptr<Scene_object>> Objects){
//     Prostopadl temp;
//     std::string name; 
//     bool tmp = true;   
//     double x_gr1, x_gr2, y1, y2;
//     double value_gr1x,value_gr2x,value_gr1y,value_gr2y;
//     std::list<std::shared_ptr<Scene_object>>::iterator it = Objects.begin();
//     if(num_drone == 1){
//         (*it)->set_mid(position[0]); 
//         ++it;
//     }
//     else if(num_drone == 2){
//         ++it;
//         (*it)->set_mid(position[0]); 
//         it = Objects.begin();
//     }
//     while( it != Objects.end()){
//         temp = (*it)->get_obst();
//         name = (*it)->get_name();
//         x_gr1 = this->position[0][0] - 7;
//         x_gr2 = this->position[0][0] + 7;
//         if(name == "Piramid"){
//            value_gr1x = temp(10,0);
//            value_gr2x = temp(13,0);
//            value_gr1y = temp(10,1);
//            value_gr2y = temp(13,1);
//         }
//         else if(name == "Cuboid"){
//            value_gr1x = temp(6,0);
//            value_gr2x = temp(1,0);
//            value_gr1y = temp(6,1);
//            value_gr2y = temp(1,1);
//         }
//         else if(name == "Mount_with_ridge"){
//            value_gr1x = temp(10,0);
//            value_gr2x = temp(13,0);
//            value_gr1y = temp(10,1);
//            value_gr2y = temp(13,1);
//         }
//         else if(name == "Drone1"){
//            (*it)->set_obst(get_corp(SZESCIAN_ZM));
//            temp = (*it)->get_obst();
//            value_gr1x = temp(6,0);
//            value_gr2x = temp(1,0);
//            value_gr1y = temp(6,1);
//            value_gr2y = temp(1,1);
//         }
//         else if(name == "Drone2"){
//         //    std::cout << temp << std::endl;
//            (*it)->set_obst(get_corp(SZESCIAN_ZM_V2));
//            temp = (*it)->get_obst();
//            value_gr1x = temp(6,0);
//            value_gr2x = temp(1,0);
//            value_gr1y = temp(6,1);
//            value_gr2y = temp(1,1);
//         }
//         if(name == "Mount_with_ridge" || name == "Piramid" || name == "Cuboid"){
//         for(int i = x_gr1; i <= x_gr2; ++i ){
//         // std::cout << i << std::endl;            
//             y1 = std::sqrt(49 - pow(i-this->position[0][0],2)) + this->position[0][1];
//             y2 = -y1;
//                 if( (i < value_gr1x && i > value_gr2x) && ((y1 < value_gr1y && y1 > value_gr2y) || (y2 < value_gr1y && y2 > value_gr2y))){
//                     tmp = false;
//                 }
//         }}
//         else if(name == "Drone1" || name == "Drone2"){
//             double distance_middle;
//             // std::cout << position[0][0] << " " << position[0][1] << " " << (*it)->get_middle() << std::endl;
//             distance_middle = sqrt(pow(position[0][0] - (*it)->get_middle()[0],2) + pow(position[0][1] - (*it)->get_middle()[1],2));
//             if(distance_middle <= 12){
//                 tmp = false;
//             }
//             if(name == "Drone1"){
//                 ++it;
//             }
//         }
//         if(tmp == false){
//             break;
//         }
//         ++it;
//     }
//     return tmp;
// };

    bool check_landing(unsigned int num_drone, std::list<std::shared_ptr<Scene_object>> Objects){
    Prostopadl temp;
    std::string name; 
    bool tmp = true;   
    double x_gr1, x_gr2;
    // double value_gr1x,value_gr2x,value_gr1y,value_gr2y;
    std::list<std::shared_ptr<Scene_object>>::iterator it = Objects.begin();
    if(num_drone == 1){
        (*it)->set_mid(position[0]); 
        ++it;
    }
    else if(num_drone == 2){
        ++it;
        (*it)->set_mid(position[0]); 
        it = Objects.begin();
    }
    while( it != Objects.end()){
        temp = (*it)->get_obst();
        name = (*it)->get_name();
        x_gr1 = this->position[0][0] - 7;
        x_gr2 = this->position[0][0] + 7;
        Vector3 middle = (*it)->get_middle();
        // if(name == "Drone1"){
        //    (*it)->set_obst(get_corp(SZESCIAN_ZM));
        //    temp = (*it)->get_obst();
        // }
        // else if(name == "Drone2"){
        //    (*it)->set_obst(get_corp(SZESCIAN_ZM_V2));
        //    temp = (*it)->get_obst();
        // }
        // else{
           tmp = (*it)->check_landing_object(middle, temp,num_drone,x_gr1,x_gr2,this->position[0]);
        // }
        // if(name == "Drone1" || name == "Drone2"){
        //     double distance_middle;
        //     distance_middle = sqrt(pow(position[0][0] - (*it)->get_middle()[0],2) + pow(position[0][1] - (*it)->get_middle()[1],2));
        //     if(distance_middle <= 12){
        //         tmp = false;
        //     }
        if(name == "Drone1"){
            ++it;
        }
        if(tmp == false){
            break;
        }
        ++it;
    }
    return tmp;
};

bool check_landing_object(Vector3 middle, Prostopadl, unsigned int, double , double ,Vector3 position) override;

};
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

    void Relocate(std::list<std::shared_ptr<Scene_object>> Obstacles,unsigned int number, double angle, double lenght_of_path, PzG::LaczeDoGNUPlota &Lacze, const char *NamesFilesLocal[], const char *NamesFilesProper[]);

    void Scouting(double angle, PzG::LaczeDoGNUPlota &Lacze, const char *NamesFilesLocal[], const char *NamesFilesProper[]);

    void GoForward(double angletemp, double lenght_of_path,PzG::LaczeDoGNUPlota &Lacze, const char *NamesFilesLocal[],const char *NamesFilesProper[]);

    void Orientation(double angle, double angletemp, PzG::LaczeDoGNUPlota &Lacze, const char *NamesFilesLocal[], const char *NamesFilesProper[]);

    void GoDownAndUp(double up_down,double angletemp, PzG::LaczeDoGNUPlota &Lacze, const char *NamesFilesLocal[],const char *NamesFilesProper[]);

    /**
     * Metoda wirtualna sprawdzajaca czy dron moze ladowac 
     * @param unsigned int num_drone
     * @param std::list<std::shared_ptr<Scene_object>> Objects
     * @return true or false
     */
    bool check_landing(unsigned int num_drone, std::list<std::shared_ptr<Scene_object>> Objects){
    Prostopadl temp;
    std::string name; 
    bool tmp = true;   
    double x_gr1, x_gr2;
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
        tmp = (*it)->check_landing_object(middle, temp,num_drone,x_gr1,x_gr2,this->position[0]);
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

    /**
     * Metoda wirtualna sprawdzajaca czy dron moze ladowac (Dron)
     * @param Vector3
     * @param Prostopadl 
     * @param unsigned int
     * @param double 
     * @param double 
     * @param Vector3 position
     * @return true or false
     */
    bool check_landing_object(Vector3 middle, Prostopadl, unsigned int, double , double ,Vector3 position) override;

};
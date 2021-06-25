#ifndef SCENA_HH
#define SCENA_HH

#include "Drone.hh"
#include "Piramid.hh"
#include "Mount_with_ridge.hh"
#include "Cuboid_obstacle.hh"
#include <string.h>
#include <memory>
#include <list>

const char *NamesFilesLoc_V1[] = {SZESCIAN_ZM_LOC,ROTORYLOC_1,ROTORYLOC_2,ROTORYLOC_3,ROTORYLOC_4, nullptr};
const char *NamesFilesProp_V1[] = {SZESCIAN_ZM,ROTORY_1,ROTORY_2,ROTORY_3,ROTORY_4, nullptr};

const char *NamesFilesLoc_V2[] = {SZESCIAN_ZM_LOC_V2,ROTORYLOC_1_V2,ROTORYLOC_2_V2,ROTORYLOC_3_V2,ROTORYLOC_4_V2, nullptr};
const char *NamesFilesProp_V2[] = {SZESCIAN_ZM_V2,ROTORY_1_V2,ROTORY_2_V2,ROTORY_3_V2,ROTORY_4_V2, nullptr};

/**
 * \brief Klasa scena
 * 
 * Klasa pozwalajaca operowac na odpowiednich figurach
 * 
 */
class scena : public Drone{
    
    private:

    std::vector<Drone> drones;  ///<Kontener dronow

    unsigned int Active_drone;  ///<Aktywny dron

    public:
    
    std::list <std::shared_ptr<Scene_object>> Objects;   ///<Lista mieszczaca wszystkie obiekty na scenie

    Drone *getdrone(){return (&drones[Active_drone]);}; ///<Funkcja dajaca dostep do danego drona

    unsigned int get_active_num(){return Active_drone;};

    std::vector<Drone> get_drone_vec(){return drones;};

    Drone GetActiveDrone(int ind){return(drones[ind]);};   

    void choose_drone(unsigned int choice){ Active_drone = choice - 1;};    ///<Funkcja zwracajaca index wybranego drona

    void Add_drone(Drone tmp){ drones.push_back(tmp);}; ///<Funkcja dodajaca drona do kontenera

    /**
     * Metoda tworzaca sciezke 
     * @param PzG::LaczeDoGNUPlota &Lacze
     * @param double choosen_drone
     * @param const char *Name_of_Path
     * @param double lenght_of_path
     * @param double angletemp
     */
    void Make_Path(PzG::LaczeDoGNUPlota &Lacze, double choosen_drone, const char *Name_of_Path, double lenght_of_path, double angletemp){    

    std::ofstream StrmWy(Name_of_Path); 

    if(!StrmWy.is_open()){
        std::cerr << std::endl
        << "Couldnt open the file: " << Name_of_Path << std::endl
        << std::endl;
    }

    if(choosen_drone == 1){
    drones[0].position[1][0] = drones[0].x_of_end(drones[0].position[0][0],angletemp,lenght_of_path) ; 
    drones[0].position[1][1] = drones[0].y_of_end(drones[0].position[0][1],angletemp,lenght_of_path) ; 
    StrmWy << this->drones[0].position[0][0] << " " << this->drones[0].position[0][1] << " 0 " << std::endl
           << this->drones[0].position[0][0] << " " << this->drones[0].position[0][1] << " 80" << std::endl
           << drones[0].position[1][0] << " " << drones[0].position[1][1] << " 80" << std::endl
           << drones[0].position[1][0] << " " << drones[0].position[1][1] << " 0" << std::endl;
    Lacze.DodajNazwePliku(Path_V1);
    Lacze.Rysuj();}
    else if(choosen_drone == 2){
    drones[1].position[1][0] = drones[1].x_of_end(drones[1].position[0][0],angletemp,lenght_of_path) ;
    drones[1].position[1][1] = drones[1].y_of_end(drones[1].position[0][1],angletemp,lenght_of_path) ;
    StrmWy << this->drones[1].position[0][0] << " " << this->drones[1].position[0][1] << " 0 " << std::endl
           << this->drones[1].position[0][0] << " " << this->drones[1].position[0][1] << " 80 " << std::endl
           << drones[1].position[1][0] << " " << drones[1].position[1][1] << " 80 " << std::endl
           << drones[1].position[1][0] << " " << drones[1].position[1][1] << " 0 " << std::endl;
    Lacze.DodajNazwePliku(Path_V2);
    Lacze.Rysuj();}
};

/**
* Metoda Inicjujaca przeszkody 
* @param PzG::LaczeDoGNUPlota &Lacze
* @param Vector3 begin_position
* @param Vector3 scale
* @param char choice
*/
void make_obstacle(PzG::LaczeDoGNUPlota &Lacze,Vector3 begin_position, Vector3 scale, char choice){
    Scene_object tmp;
    switch(choice){
        case '1':{
            Piramid tmp = Piramid(Lacze,begin_position,scale);
            Objects.push_back(std::make_shared<Piramid>(tmp));        
        break;}

        case '2':{
            Mount_with_ridge tmp = Mount_with_ridge(Lacze,begin_position,scale);
            Objects.push_back(std::make_shared<Mount_with_ridge>(tmp));
        break;}

        case '3':{
            Cuboid_obstacle tmp = Cuboid_obstacle(Lacze,begin_position,scale);
            Objects.push_back(std::make_shared<Cuboid_obstacle>(tmp));
        break;}
    }

    Lacze.Rysuj();
};

/**
* Metoda Inicjujaca przeszkody poczatkowe 
* @param PzG::LaczeDoGNUPlota &Lacze
*/
void Initiation_begin_obstacles(PzG::LaczeDoGNUPlota &Lacze){
    Vector3 arg1,arg2,arg3,arg4;
    Vector3 scale;
    double sc[] = {30,25,50};
    double ar1[] = {60,100,0};
    double ar2[] = {30,150,0};
    double ar3[] = {150, 45,0};
    double ar4[] = {120,120,0};
    arg1 = Vector3(ar1);
    arg2 = Vector3(ar2);
    arg3 = Vector3(ar3);
    arg4 = Vector3(ar4);
    scale = Vector3(sc);

    make_obstacle(Lacze,arg1,scale,'1');
    make_obstacle(Lacze,arg2,scale,'2');
    make_obstacle(Lacze,arg3,scale,'3');
    make_obstacle(Lacze,arg4,scale,'2');

};

/**
* Metoda usuwajaca przeszkody 
* @param PzG::LaczeDoGNUPlota &Lacze
*/
void Delete_Obstacle(PzG::LaczeDoGNUPlota &Lacze){
    int i = 0;
    unsigned int num_obs;
    std::list<std::shared_ptr<Scene_object>>::iterator it = Objects.begin();
    std::cout << "choose which obstacle you want to delete : " << std::endl;
    advance(it,2);
    while( it != Objects.end()){
        (*it)->show_parameters(i);
        ++it;
        ++i;
    }
    std::cin >> num_obs;
    it = Objects.begin();
    advance(it,num_obs+1);
    (*it)->delete_Obstacle(Lacze);
    Objects.erase(it);
        
    Lacze.Rysuj();
};

/**
 * Metoda usuwajaca plik przeszkody      
 * @param PzG::LaczeDoGNUPlota &Lacze
 */
void delete_at_the_end(PzG::LaczeDoGNUPlota &Lacze){
    std::list<std::shared_ptr<Scene_object>>::iterator it = Objects.begin();
    advance(it,2);
    while( it != Objects.end()){
    (*it)->delete_Obstacle(Lacze);
    ++it;
    }
};

/**
* Metoda wyboru i wytworzenia przeszkody 
* @param PzG::LaczeDoGNUPlota &Lacze
*/
void Create_Obstacle(PzG::LaczeDoGNUPlota &Lacze){
char obs_choice;
    Vector3 beg_position;
    Vector3 scale;
    std::cout << "which type of obstacle you want to add ?" << std::endl;
    std::cout << "1 - Piramid" << std::endl;
    std::cout << "2 - Mountain with ridge" << std::endl;
    std::cout << "3 - Cuboid" << std::endl;
    std::cin >> obs_choice;
    std::cout<< "where do you want the middle of obstacle write position x,y" << std::endl;
    std::cin >> beg_position[0];
    std::cin >> beg_position[1];
    std::cout<< "Choose the scale on OX, OY, OZ (for example 10 10 60): " << std::endl;
    std::cin >> scale;
    make_obstacle(Lacze,beg_position,scale,obs_choice);
    std::cout<< "Element has been added to the scene " << std::endl;
};

};


#endif
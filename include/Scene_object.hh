#ifndef SCENE_OBJECT_HH
#define SCENE_OBJECT_HH

#include "Vector3.hh"
#include "Prostopadl.hh"
#include <memory>
#include <list>

/**
 * \brief Klasa Sceny obiektow
 * 
 * Klasa pozwalajaca operowac na przeszkodach
 * 
 */
class Scene_object{

    private:

    std::string name_of_file;   ///< Zmienna przechowująca nazwe pliku przeszkody

    std::string name;   ///<Zmienna przechowujaca typ przeszkody

    Vector3 middle_pos;     ///<Zmienna przechowywujaca pozycje srodka przeszkody

    Prostopadl obst;    ///<Zmienna przechowywujaca wspolrzedne wierzcholkow przeszkody
    
    public:

    /**
     * Metoda ustawiajaca pozycje srodkowa przeszkody 
     * @param Vector3 tmp
     */
    void set_mid(Vector3 tmp){
        middle_pos = tmp;
    };

    /**
     * Metoda ustawiajaca nazwe typu przeszkody 
     * @param std::string tmp
     */
    void set_name(std::string tmp){
        name = tmp;
    };

    /**
     * Metoda ustawiajaca wierzcholki przeszkody 
     * @param Prostopadl tmp
     */
    void set_obst(Prostopadl tmp){
        obst = tmp;
    };
    /**
     * Metoda ustawiajaca pozycje srodkowa przeszkody 
     * @param Vector3 tmp
     */
    void set_name_of_file(std::string tmp){
        name_of_file = tmp;
    };

    /**
     * Metoda wyswietlajaca parametry przeszkody nazwe, numer, pozycje srodkowa 
     * @param int tmp
     */
    void show_parameters(int tmp){
        std::cout << tmp+1 << " " << name << " (" << middle_pos << ") " << std::endl;
    };

    /**
     * Metoda usuwajaca plik przeszkody 
     * @param PzG::LaczeDoGNUPlota &Lacze
     */
    void delete_Obstacle(PzG::LaczeDoGNUPlota &Lacze){
        Lacze.UsunNazwePliku(name_of_file);
        std::cout << name_of_file << std::endl;
        if(remove(name_of_file.c_str())==0){
            puts("File successfully deleted");
        }
        else{
            perror("Error deleting obstacle file");
        }
    };

    /**
     * Metoda dajaca dostep do wierzcholkow przeszkody 
     * @return Prostopadl obst
     */
    Prostopadl get_obst(){
        return obst;
    };

    /**
     * Metoda dajaca dostep do pozycji srodka przeszkody
     * @return Vector3 middle_pos
     */
    Vector3 get_middle(){
        return middle_pos;
    };

    /**
     * Metoda dajaca dostpe do typu przeszkody 
     * @return std::string name
     */
    std::string get_name(){
        return name;
    };

    virtual bool check_landing_object(Vector3, Prostopadl ,unsigned int ,double , double , Vector3 ){
        // std::cout << "no tak " << std::endl;
        return false;
    };

    /**
     * Funkcja inicjująca tworzenie przeszkody poprzez odpowiednie zmiany wierzchołkow i zapisanie ich w pliku
     * @param const char *StrmWe
     * @param const char *StrmWy
     * @param double num_of_peak
     * @param Vector3 scale
     * @param Vector3 trans
     * @param char choice
     * @return Prostopadl temp
     */
    Prostopadl Init_The_Obstacle(const char * StrmWe, const char * StrmWy, double num_of_peak, Vector3 scale,Vector3 trans, char choice){
    Prostopadl temp;
    std::ifstream FileWe(StrmWe);
    std::ofstream FileWy(StrmWy);
    FileWe.clear();
    FileWe.seekg(0);
    double x,y,z;
    assert(FileWe.good());
    assert(FileWy.good());
    for(int i = 0; i < num_of_peak; ++i){
        FileWe >> x >> y >> z;
        switch (choice){
            case '1':{
                if(z > 0.5){
                    if(x < 0){ 
                        x = fabs(x);
                    }
                }
            break;}
            case '2':{
                if(z > 0.5){
                    x = 0;
                    y = 0;
                }
                else if(z == 0.5){
                    x /= 2;
                    y /= 2;
                }
            break;}
        }
        double arg[] = {x,y,z};
        Vector3 vec = Vector3(arg);
        x = vec[0];
        y = vec[1];
        z = vec[2]; 
        temp(i,0) = (x * scale[0]) + trans[0] ;
        temp(i,1) = (y * scale[1]) + trans[1] ;
        temp(i,2) = (z * scale[2]) + trans[2] ;

        if(i%4 == 0){
        FileWy << std::endl;
        FileWy << temp(i) << std::endl;
        }
        else{
        FileWy << temp(i) << std::endl;}
    } 
    FileWe.close();
    FileWy.close();

    return temp;
    };

};

#endif
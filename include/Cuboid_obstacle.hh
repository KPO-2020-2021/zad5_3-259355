#ifndef CUBOID_OBSTACLE_HH
#define CUBOID_OBSTACLE_HH
#include "Scene_object.hh"

/**
 * \brief Klasa Cuboid
 * 
 * Klasa pozwalajaca dzialac na plaskowyzach
 * Klasa dziedziczy po klasie Scene_Object 
 * 
 */
class Cuboid_obstacle : public Scene_object{

    public:

    /**
     * Metoda inicjujaca poczatkowe wierzcholki piramidy odpowiednio deformujac prostopadloscian
     */
    void Cuboid_Init(){
        double x,y,z;
        Prostopadl tmp;
        std::ifstream FileWe(SZESCIAN_WZ);
        std::ofstream FileWy("../bryly_wzorcowe/plaskowyz_tmp.dat");
        assert(FileWe.good());
        assert(FileWy.good());
        for(int i = 0; i < NOPOINTS; ++i){
            FileWe >> x >> y >> z;
            Vector3 temp;
            double arg[] = {x,y,z};
            temp = Vector3(arg);
            if(i%4 == 0 || i%4 == 3){
                temp[2] = 0;
                FileWy << temp << std::endl;
                }
            else if ( (i < 7 || i > 15) && (i%4 == 1 || i%4 == 2)){
                temp[2] = 1;
                FileWy << temp << std::endl;
            }
            else {
                temp[2] = 0;
                FileWy << temp << std::endl;
            }
        // FileWe.close();
        // FileWy.close();
    }} 

    /**
     * Metoda tworzaca odpowiednio zmieniony prostopadloscian 
     * @param PzG::LaczeDoGNUPlota &Lacze
     * @param Vector3 begin_position
     * @param Vector3 scale
     */
    Cuboid_obstacle(PzG::LaczeDoGNUPlota &Lacze,Vector3 begin_position, Vector3 scale){
        Cuboid_Init();
        static int count3 = 1;
        std::string stream3 = "../dat/plaskowyz" + std::to_string(count3) + ".dat"; 
        char *strm3 = new char[stream3.size() + 1];
        strcpy(strm3, stream3.c_str());

        std::string stream2 = "Cuboid";

        Lacze.DodajNazwePliku(strm3);
        count3 += 1;
        this->set_name_of_file(strm3);
        this->set_name(stream2);
        this->set_mid(begin_position);
        count3 += 1;
        this->set_obst(Init_The_Obstacle("../bryly_wzorcowe/plaskowyz_tmp.dat",strm3,NOPOINTS,scale,begin_position,'3'));
    };

    /**
     * Metoda wirtualna sprawdzajaca czy dron moze ladowac (Plaskowyz)
     * @param Vector3
     * @param Prostopadl temp
     * @param unsigned int
     * @param double x_gr1
     * @param double x_gr2
     * @param Vector3 position
     * @return true or false
     */
    bool check_landing_object(Vector3, Prostopadl temp,unsigned int ,double x_gr1, double x_gr2,Vector3 position) override;

};

#endif
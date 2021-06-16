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

    bool check_landing_object(Vector3, Prostopadl temp,unsigned int ,double x_gr1, double x_gr2,Vector3 position) override;
    //     Prostopadl temp;
    //     temp = get_obst();
    //     bool tmp = true;   
    //     double value_gr1x,value_gr2x,value_gr1y,value_gr2y;
    //     double y1,y2;
    //     value_gr1x = temp(6,0);
    //     value_gr2x = temp(1,0);
    //     value_gr1y = temp(6,1);
    //     value_gr2y = temp(1,1);
    //     for(int i = x_gr1; i <= x_gr2; ++i ){
    //         y1 = std::sqrt(49 - pow(i-position[0],2)) + position[1];
    //         y2 = -y1;
    //             if( (i < value_gr1x && i > value_gr2x) && ((y1 < value_gr1y && y1 > value_gr2y) || (y2 < value_gr1y && y2 > value_gr2y))){
    //                 tmp = false;
    //             }
    //     }
    //     return tmp;
    // };
};

#endif
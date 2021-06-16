#ifndef PIRAMID_HH
#define PIRAMID_HH
#include "Scene_object.hh"


/**
 * \brief Klasa Piramidy
 * 
 * Klasa pozwalajaca dzialac na piramidach
 * Klasa dziedziczy po klasie Scene_Object 
 * 
 */
class Piramid : public Scene_object {

    public:

    /**
     * Metoda inicjujaca poczatkowe wierzcholki piramidy odpowiednio deformujac prostopadloscian
     */
    void Piramid_Init(){
        double x,y,z;
        Prostopadl tmp;
        std::ifstream FileWe(SZESCIAN_WZ);
        std::ofstream FileWy("../bryly_wzorcowe/gora_z_ostrym_szczytem_tmp.dat");
        assert(FileWe.good());
        assert(FileWy.good());
        for(int i = 0; i < NOPOINTS; ++i){
            FileWe >> x >> y >> z;
            Vector3 temp;
            double arg[] = {x,y,z};
            temp = Vector3(arg);
            if(i%4 == 0){
                tmp(i,0) = 0;
                tmp(i,1) = -0.25;
                tmp(i,2) = 0.5;
                FileWy << tmp(i) << std::endl;
                }
            else if(i%4 == 3){
                tmp(i,0) = 0;
                tmp(i,1) = 0.25;
                tmp(i,2) = 0.5;
                FileWy << tmp(i) << std::endl;}
            else if ( (i < 7 || i > 15) && (i%4 == 1 || i%4 == 2)){
                tmp(i,0) = 0;
                tmp(i,1) = 0;
                tmp(i,2) = 1;
                FileWy << tmp(i) << std::endl;
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
    Piramid(PzG::LaczeDoGNUPlota &Lacze,Vector3 begin_position, Vector3 scale){
        this->Piramid_Init();
        static int count2 = 1;
        std::string stream2 = "../dat/gora_z_ostrym_szczytem" + std::to_string(count2) + ".dat"; 
        char *strm2 = new char[stream2.size() + 1];
        strcpy(strm2, stream2.c_str());

        std::string stream3 = "Piramid"; 

        Lacze.DodajNazwePliku(strm2);
        this->set_name_of_file(strm2);
        this->set_name(stream3);
        this->set_mid(begin_position);
        count2 += 1;
        this->set_obst(Init_The_Obstacle("../bryly_wzorcowe/gora_z_ostrym_szczytem_tmp.dat",strm2,NOPOINTS,scale,begin_position,'2'));
    };

    bool check_landing_object(Vector3,Prostopadl temp,unsigned int ,double x_gr1, double x_gr2,Vector3 position) override;
    //     Prostopadl temp;
    //     bool tmp = true;   
    //     double value_gr1x,value_gr2x,value_gr1y,value_gr2y;
    //     double y1,y2;
    //     value_gr1x = temp(10,0);
    //     value_gr2x = temp(13,0);
    //     value_gr1y = temp(10,1);
    //     value_gr2y = temp(13,1);
    //     for(int i = x_gr1; i <= x_gr2; ++i ){
    //         y1 = std::sqrt(49 - pow(i-position[0],2)) + position[1];
    //         y2 = -y1;
    //             if( (i < value_gr1x && i > value_gr2x) && ((y1 < value_gr1y && y1 > value_gr2y) || (y2 < value_gr1y && y2 > value_gr2y))){
    //                 tmp = false;
    //             }
    //     }
    //     std::cout << "3" << std::endl;
    //     return tmp;
    // };


};


#endif
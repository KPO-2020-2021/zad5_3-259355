#ifndef MOUNT_WITH_RIDGE_HH
#define MOUNT_WITH_RIDGE_HH
#include "Scene_object.hh"

/**
 * \brief Klasa Mount_with_ridge
 * 
 * Klasa pozwalajaca dzialac na Gorze z grania
 * Klasa dziedziczy po klasie Scene_Object 
 * 
 */
class Mount_with_ridge : public Scene_object {

    public:


    /**
     * Metoda inicjujaca poczatkowe wierzcholki piramidy odpowiednio deformujac prostopadloscian
     */
    void Mount_with_ridge_Init(){
        double x,y,z;
        Prostopadl tmp;
        std::ifstream FileWe(SZESCIAN_WZ);
        std::ofstream FileWy("../bryly_wzorcowe/gora_z_dluga_grania_tmp.dat");
        assert(FileWe.good());
        assert(FileWy.good());
        for(int i = 0; i < NOPOINTS; ++i){
            FileWe >> x >> y >> z;
            Vector3 temp;
            double arg[] = {x,y,z};
            temp = Vector3(arg);
            if(i%4 == 0){
                tmp(i,0) = 0;
                tmp(i,1) = -0.5;
                tmp(i,2) = 0.5;
                FileWy << tmp(i) << std::endl;
                }
            else if(i%4 == 3){
                tmp(i,0) = 0;
                tmp(i,1) = 0.5;
                tmp(i,2) = 0.5;
                FileWy << tmp(i) << std::endl;}
            else if ( (i < 7 || i > 15) && (i%4 == 1 || i%4 == 2)){
                if(i%4 == 1){
                    tmp(i,0) = 0.5;
                    tmp(i,1) = -0.5;
                    tmp(i,2) = 1;
                    FileWy << tmp(i) << std::endl;}
                else if(i%4 == 2){
                    tmp(i,0) = 0.5;
                    tmp(i,1) = 0.5;
                    tmp(i,2) = 1;
                    FileWy << tmp(i) << std::endl;}
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
    Mount_with_ridge(PzG::LaczeDoGNUPlota &Lacze,Vector3 begin_position, Vector3 scale){
        Mount_with_ridge_Init();
        static int count1 = 1;
        std::string stream1 = "../dat/gora_z_dluga_grania" + std::to_string(count1) + ".dat"; 
        char *strm1 = new char[stream1.size() + 1];
        strcpy(strm1, stream1.c_str());

        std::string stream2 = "Mount_with_ridge"; 
        

        Lacze.DodajNazwePliku(strm1);
        this->set_name_of_file(strm1);
        this->set_name(stream2);
        this->set_mid(begin_position);
        count1 += 1;
        this->set_obst(Init_The_Obstacle("../bryly_wzorcowe/gora_z_dluga_grania_tmp.dat",strm1,NOPOINTS,scale,begin_position,'1'));
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
    //     return tmp;
    // };
};

// bool check_landing_object(unsigned int ,double x_gr1, double x_gr2,Vector3 position) {
//         Prostopadl temp;
//         bool tmp = true;   
//         double value_gr1x,value_gr2x,value_gr1y,value_gr2y;
//         double y1,y2;
//         value_gr1x = temp(10,0);
//         value_gr2x = temp(13,0);
//         value_gr1y = temp(10,1);
//         value_gr2y = temp(13,1);
//         for(int i = x_gr1; i <= x_gr2; ++i ){
//             y1 = std::sqrt(49 - pow(i-position[0],2)) + position[1];
//             y2 = -y1;
//                 if( (i < value_gr1x && i > value_gr2x) && ((y1 < value_gr1y && y1 > value_gr2y) || (y2 < value_gr1y && y2 > value_gr2y))){
//                     tmp = false;
//                 }
//         }
//         return tmp;
//     }

#endif
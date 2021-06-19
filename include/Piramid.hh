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

    /**
     * Metoda wirtualna sprawdzajaca czy dron moze ladowac (Piramida)
     * @param Vector3
     * @param Prostopadl temp
     * @param unsigned int
     * @param double x_gr1
     * @param double x_gr2
     * @param Vector3 position
     * @return true or false
     */
    bool check_landing_object(Vector3,Prostopadl temp,unsigned int ,double x_gr1, double x_gr2,Vector3 position) override;

};


#endif
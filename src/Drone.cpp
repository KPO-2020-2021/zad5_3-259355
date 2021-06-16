#include "Drone.hh"

/**
 * Funkcja inicjujaca poczatkowego drona 
 * Inicjuje prostopadaloscian (cialo drona)
 * Inicjuje poszczegolne rotory oraz odpowiada za animacje ich obrotu
 * @param const char *NamesFilesLocal[]
 * @param int step
 */
void Drone::Init(const char *NamesFilesLocal[], int step){

    static double angle_rotors_lf = 0;
    static double angle_rotors_rf = 0;
    static double angle_rotors_lb = 0;
    static double angle_rotors_rb = 0;
    static double angletemp = 0;

    // new Prostopadl(SZESCIAN_WZ,NamesFilesLocal[0], arg_pros_sc, 0, init_args);

    this->rotor[0] = new Block(ROTORY_BEF, NamesFilesLocal[1], arg_rotator_sc, arg_lf, angle_rotors_lf);
    this->rotor[1] = new Block(ROTORY_BEF, NamesFilesLocal[2], arg_rotator_sc, arg_rf, angle_rotors_rf);
    this->rotor[2] = new Block(ROTORY_BEF, NamesFilesLocal[3], arg_rotator_sc, arg_lb, angle_rotors_lb);
    this->rotor[3] = new Block(ROTORY_BEF, NamesFilesLocal[4], arg_rotator_sc, arg_rb, angle_rotors_rb);

    #define TURN_OF_ROTOR_UP_DOWN 10
    #define TURN_OF_ROTOR_FORWARD_BACK 15
    #define TURN_OF_ROTOR_FORWARD_FRONT 7
    if(step == 1){
        angle_rotors_lf -= TURN_OF_ROTOR_UP_DOWN;
        angle_rotors_rf += TURN_OF_ROTOR_UP_DOWN;
        angle_rotors_lb += TURN_OF_ROTOR_UP_DOWN;
        angle_rotors_rb -= TURN_OF_ROTOR_UP_DOWN;
    }
    else if(step == 2){
        angle_rotors_lf -= TURN_OF_ROTOR_UP_DOWN + 5;
        angle_rotors_rf += TURN_OF_ROTOR_UP_DOWN - 4;
        angle_rotors_lb += TURN_OF_ROTOR_UP_DOWN - 4;
        angle_rotors_rb -= TURN_OF_ROTOR_UP_DOWN + 5;
    }
    else if(step == -2){
        angle_rotors_lf -= TURN_OF_ROTOR_UP_DOWN - 5;
        angle_rotors_rf += TURN_OF_ROTOR_UP_DOWN + 4;
        angle_rotors_lb += TURN_OF_ROTOR_UP_DOWN + 4;
        angle_rotors_rb -= TURN_OF_ROTOR_UP_DOWN - 5;
    }
    else if(step == 3){
        angle_rotors_lf -= TURN_OF_ROTOR_FORWARD_FRONT;
        angle_rotors_rf += TURN_OF_ROTOR_FORWARD_FRONT;
        angle_rotors_lb += TURN_OF_ROTOR_FORWARD_BACK;
        angle_rotors_rb -= TURN_OF_ROTOR_FORWARD_BACK;
    }
    else if(step == 4){
        angletemp += 0.5;
        angle_rotors_lf -= TURN_OF_ROTOR_UP_DOWN - angletemp;
        angle_rotors_rf += TURN_OF_ROTOR_UP_DOWN - angletemp;
        angle_rotors_lb += TURN_OF_ROTOR_UP_DOWN - angletemp;
        angle_rotors_rb -= TURN_OF_ROTOR_UP_DOWN - angletemp;
    }
    else{}

}


/**
 * Funkcja inicjujaca drona
 * Inicjuje prostopadaloscian (cialo drona), obraca go i odpowiada za sposob przelotu
 * Inicjuje poszczegolne rotory oraz odpowiada za ich sposob przelotu wzgledem ciala oraz ich poczatkowy obrot
 * @param double angle
 * @param Vector3 position
 * @param const char *NamesFilesLocal[]
 * @param const char *NamesFilesProper[]
 */
void Drone::Engage2(double angle, Vector3 position, const char *NamesFilesLocal[], const char *NamesFilesProper[], int step){
    this->Init(NamesFilesLocal, step);

    new Prostopadl(NamesFilesLocal[0],NamesFilesProper[0], arg_jed, angle, position);

    for(unsigned int Idx = 1; NamesFilesLocal[Idx]!= nullptr; ++Idx){
        rotor[Idx] = new Block(NamesFilesLocal[Idx], NamesFilesProper[Idx], arg_jed, position, angle);
    }
}

/**
 * Funkcja przemieszczajaca drona wprzod
 * @param double angletemp
 * @param double lenght_of_path
 * @param PzG::LaczeDoGNUPlota &Lacze
 * @param const char *NamesFilesLocal[]
 * @param const char *NamesFilesProper[]
 */
void Drone::GoForward(double angletemp, double lenght_of_path, PzG::LaczeDoGNUPlota &Lacze, const char *NamesFilesLocal[],const char *NamesFilesProper[]){
    double x_of_turn = 1;
    double y_of_turn = 1;
    double step;

    x_of_turn = this->x_of_end(this->position[0][0],angletemp,lenght_of_path);
    x_of_turn = (x_of_turn - this->position[0][0])/60;
    y_of_turn = this->y_of_end(this->position[0][1],angletemp,lenght_of_path);
    y_of_turn = (y_of_turn - this->position[0][1])/60;

    std::cout << "Going forward ..." << std::endl;
    for(int i = 0; i <= 60; this->position[0][0] += x_of_turn, this->position[0][1] += y_of_turn, ++i){
        step = 3;
        this->Engage2(angletemp,this->position[0], NamesFilesLocal, NamesFilesProper, step);
        usleep(100000);
        Lacze.Rysuj();
    }
    this->position[0][0] -= 1;
    this->position[0][1] -= 1;
}

/**
 * Funkcja przemieszczajaca drona w gore badz w dol
 * @param double up_down
 * @param double angletemp
 * @param PzG::LaczeDoGNUPlota &Lacze
 * @param const char *NamesFilesLocal[]
 * @param const char *NamesFilesProper[]
 */
void Drone::GoDownAndUp(double up_down, double angletemp, PzG::LaczeDoGNUPlota &Lacze, const char *NamesFilesLocal[],const char *NamesFilesProper[]){
    double step;

    if(up_down == 1){
    std::cout << std::endl << "Up ..." << std::endl;
    for(;this->position[0][2] <= 80; this->position[0][2] += 2){
        step = 1;
        this->Engage2(angletemp,this->position[0], NamesFilesLocal, NamesFilesProper, step);
        usleep(100000);
        Lacze.Rysuj();
    }}
    this->position[0][2] -= 2;

    if(up_down == 2){
    std::cout << "Going down ..." << std::endl;
    for(;this->position[0][2] >= 0; this->position[0][2] -= 2){
        step = 4;
        this->Engage2(angletemp,this->position[0], NamesFilesLocal, NamesFilesProper, step);
        usleep(100000);
        Lacze.Rysuj();
    }}
}

/**
 * Funkcja zmieniajaca orientacje drona
 * @param double angle
 * @param PzG::LaczeDoGNUPlota &Lacze
 * @param const char *NamesFilesLocal[]
 * @param const char *NamesFilesProper[]
 * @return double angletemp
 */
void Drone::Orientation(double angle, double angletemp, PzG::LaczeDoGNUPlota &Lacze, const char *NamesFilesLocal[], const char *NamesFilesProper[]){
    std::cout << "Change of the orientation..." << std::endl;
    double step;
    if(angle > 0){
    for(; angletemp <= angle; angletemp += 5 ){
        step = 2;
        this->Engage2(angletemp,this->position[0], NamesFilesLocal, NamesFilesProper, step);
        usleep(100000);
        Lacze.Rysuj();
    }
    angletemp -= 5;}
    else if(angle < 0){
    for(; angletemp >= angle; angletemp -= 5 ){
        step = -2;
        this->Engage2(angletemp,this->position[0], NamesFilesLocal, NamesFilesProper, step);
        usleep(100000);
        Lacze.Rysuj();
    }
    angletemp += 5; 
    }
}

/**
 * Funkcja przemieszczajaca drona
 * Inicjuje prostopadaloscian (cialo drona), obraca go i odpowiada za sposob przelotu
 * Inicjuje poszczegolne rotory oraz odpowiada za ich sposob przelotu wzgledem ciala oraz ich poczatkowy obrot
 * @param double angle
 * @param double lenght_of_path
 * @param PzG::LaczeDoGNUPlota &Lacze
 * @param const char *NamesFilesLocal[]
 * @param const char *NamesFilesProper[]
 */
void Drone::Relocate(std::list<std::shared_ptr<Scene_object>> Objects,unsigned int number, double angle, double lenght_of_path, PzG::LaczeDoGNUPlota &Lacze, const char *NamesFilesLocal[], const char *NamesFilesProper[])
{   
    if(number == 1){
    static double angletemp1=0;
    this->GoDownAndUp(1,angletemp1,Lacze,NamesFilesLocal,NamesFilesProper);
    this->Orientation(angle, angletemp1, Lacze,NamesFilesLocal,NamesFilesProper);
    this->GoForward(angle,lenght_of_path,Lacze,NamesFilesLocal,NamesFilesProper);
    this->set_obst(get_corp(SZESCIAN_ZM));
    while(!this->check_landing(number,Objects)){
        std::cout << "Problem with landing" << std::endl;
        std::cout << "Going futher" << std::endl;
        this->GoForward(angle,30,Lacze,NamesFilesLocal,NamesFilesProper);
    }
    std::cout << "There isnt any obstacles, landing phase possible" << std::endl;
    this->GoDownAndUp(2,angle,Lacze,NamesFilesLocal,NamesFilesProper);
    angletemp1 += angle;}

    else if(number == 2){
    static double angletemp2=0;
    this->GoDownAndUp(1,angletemp2,Lacze,NamesFilesLocal,NamesFilesProper);
    this->Orientation(angle, angletemp2, Lacze,NamesFilesLocal,NamesFilesProper);
    this->GoForward(angle,lenght_of_path,Lacze,NamesFilesLocal,NamesFilesProper);
    this->set_obst(get_corp(SZESCIAN_ZM_V2));
    while(!this->check_landing(number,Objects)){
        std::cout << "Problem with landing" << std::endl;
        std::cout << "Going futher" << std::endl;
        this->GoForward(angle,30,Lacze,NamesFilesLocal,NamesFilesProper);
    }
    std::cout << "There isnt any obstacles, landing phase possible" << std::endl;
    this->GoDownAndUp(2,angle,Lacze,NamesFilesLocal,NamesFilesProper);   
    angletemp2 += angle;}
}

/**
 * Funkcja wykonujaca zwiad drona
 * Inicjuje prostopadaloscian (cialo drona), obraca go i odpowiada za sposob przelotu
 * Inicjuje poszczegolne rotory oraz odpowiada za ich sposob przelotu wzgledem ciala oraz ich poczatkowy obrot
 * @param double angle
 * @param double lenght_of_path
 * @param PzG::LaczeDoGNUPlota &Lacze
 * @param const char *NamesFilesLocal[]
 * @param const char *NamesFilesProper[]
 */
void Drone::Scouting( double angle, PzG::LaczeDoGNUPlota &Lacze, const char *NamesFilesLocal[], const char *NamesFilesProper[]){

    int step = 0;
    double circuit = 0;
    double tmp = 0;

    double angletemp = angle;
    this->GoDownAndUp(1,0,Lacze,NamesFilesLocal,NamesFilesProper);

    circuit = M_PI * (2*40);
    tmp = circuit/72;

    double x_of_turn = 1;
    double y_of_turn = 1;

    this->GoForward(angletemp,40,Lacze,NamesFilesLocal,NamesFilesProper);

    std::cout << "Change of the orientation..." << std::endl;
    for(; angletemp <= 90+angle; angletemp += 5 ){
        step = 2;
        this->Engage2(angletemp,this->position[0], NamesFilesLocal, NamesFilesProper, step);
        usleep(100000);
        Lacze.Rysuj();
    }

    angletemp -= 5; 
    double tmpang;
    tmpang = angletemp;
    std::cout << "Change of the orientation..." << std::endl;
    for(; angletemp <= tmpang+360; angletemp += 5 ){
        x_of_turn = this->x_of_end(this->position[0][0],angletemp,tmp);
        x_of_turn = (x_of_turn - this->position[0][0]);
        y_of_turn = this->y_of_end(this->position[0][1],angletemp,tmp);
        y_of_turn = (y_of_turn - this->position[0][1]);
        this->position[0][0] += x_of_turn;
        this->position[0][1] += y_of_turn;
        step = 2;
        this->Engage2(angletemp,this->position[0], NamesFilesLocal, NamesFilesProper, step);
        usleep(100000);
        Lacze.Rysuj();
    }
    angletemp -= 5; 
    tmpang = angletemp;
    std::cout << "Change of the orientation..." << std::endl;
    for(; angletemp <= 90+tmpang; angletemp += 5 ){
        step = 2;
        this->Engage2(angletemp,this->position[0], NamesFilesLocal, NamesFilesProper, step);
        usleep(100000);
        Lacze.Rysuj();
    }
    angletemp -= 5; 
    this->GoForward(angletemp,40,Lacze,NamesFilesLocal,NamesFilesProper);

    this->GoDownAndUp(2,angletemp,Lacze,NamesFilesLocal,NamesFilesProper);

}

bool Drone::check_landing_object(Vector3 middle, Prostopadl, unsigned int, double , double ,Vector3 position){
    bool tmp = true;
    double distance_middle;
    distance_middle = sqrt(pow(position[0] - middle[0],2) + pow(position[1] - middle[1],2));
    if(distance_middle <= 12){
        tmp = false;
    }
    return tmp;
}
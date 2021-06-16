#include "GranBlock.hh"

/******************************************************************************
 |  Konstruktor klasy GranBlock.                                                 |
 |  Argumenty:                                                                |
 |      Brak argumentow.                                                      |
 |  Zwraca:                                                                   |
 |      GranBlock wypelnione wartoscia 0.                                       |
 */
// GranBlock::GranBlock() {
//     for (int i = 0; i < 28; ++i) {
//         for(int j = 0; j < SIZE; ++j) {
//         figure[i][j] = 0;
//     }
//     }
// }


// /**
//  * Metoda przyjmujaca jeden argument pozwalajaca poruszac sie po tablicy wierzcholkow
//  * @param tablica wektorow 3D
//  * @return nothing
//  */ 
// GranBlock::GranBlock(Vector3 tmp[28]) {
//     for (int i = 0; i < 28; ++i) {
//         for(int j = 0; j < SIZE; ++j) {
//         figure[i][j] = tmp[i][j];
//     }
//     }
// }

// /**
//  * Przeciazenie operatora indeksowania pilnujaca czy nie wychodzi poza zakres
//  * Przyjmuje dwa argument: 
//  * @param int numer wiersza
//  * @param int numer kolumny 
//  * @return tablica wierzcholkow
//  */ 
// double &GranBlock::operator()(unsigned int row, unsigned int column) {

//     if (row >= 28) {
//         throw std::out_of_range("Error: Macierz jest poza zasiegiem");
//     }

//     if (column >= SIZE) {
//         throw std::out_of_range("Error: Macierz jest poza zasiegiem");
//     }

//     return figure[row][column];
// }


// /**
//  * Funktor Wektora (const) pilnujacy czy nie wychodzimy poza tablice wektora
//  * @param int numer wiersza
//  * @return wektor
//  */ 
// const Vector3 &GranBlock::operator () (unsigned int row) const {

//     if (row >= 28) {
//         throw std::out_of_range("Error: Vector jest poza zasiegiem");
//     }

//     return figure[row];
// }

// /**
//  * Przeciazenie operatora () (const) indeksowania dla GranBlocka z odpowiednimi zabezpieczeniami
//  * @param int numer wiersza
//  * @param int numer kolumny 
//  * @return Tablica wierzcholkow
//  */ 
// const double &GranBlock::operator () (unsigned int row, unsigned int column) const {

//     if (row >= 28) {
//         throw std::out_of_range("Error: Blockoscian jest poza zasiegiem");
//     }

//     if (column >= SIZE) {
//         throw std::out_of_range("Error: Blockoscian jest poza zasiegiem");
//     }

//     return figure[row][column];
// }

// /**
//  * Funkcja obracajaca punkty x i y wokol osi Oz
//  * @param double angle
//  * @param double &x_position
//  * @param double &y_position
//  */
// void GranBlock::TurnByOZ(double angle, double &x_position, double &y_position){

//     angle = this->toradians(angle);
    
//     double sn = sin(angle), cn = cos(angle);

//     x_position = x_position*cn - y_position*sn;
//     y_position = x_position*sn + y_position*cn; 

// }

/**
 * Funkcja zmieniajaca liczbe na radiany
 * @param double angle
 * @return double angle
 */
double GranBlock::toradians(double angle){
    angle = (angle * M_PI)/180;
    return angle;
}

/**
 * Funkcja inicjujaca poszczegolne Blocki - rotory
 * @param const char *StrmWe
 * @param const char *StrmWy
 * @param double num_of_peak
 * @param Vector3 scale
 * @param double angle
 * @param Vector3 trans
 * @return GranBlock figure
 */
GranBlock GranBlock::Init_The_Figure(const char * StrmWe, const char * StrmWy, double num_of_peak, Vector3 scale,
 Vector3 trans, double angle){

    std::ifstream FileWe(StrmWe);
    std::ofstream FileWy(StrmWy);

    Matrix3 matrixturn;
    FileWe.clear();
    FileWe.seekg(0);
    double x,y,z;
    assert(FileWe.good());
    assert(FileWy.good());
    matrixturn.angle = angle;
    matrixturn.toradians();
    for(int i = 0; i < num_of_peak; ++i){
        FileWe >> x >> y >> z;
        double arg[] = {x,y,z};
        Vector3 vec = Vector3(arg);
        vec = matrixturn.after_z() * vec;   
        x = vec[0];
        y = vec[1];
        z = vec[2]; 
        vec[0] = (x * scale[0]) + trans[0] ;
        vec[1] = (y * scale[1]) + trans[1] ;
        vec[2] = (z * scale[2]) + trans[2] ;
        this->figure.push_back(vec);
        if(i%4 == 0){
        FileWy << std::endl;
        FileWy << figure[i][0] << " " << figure[i][1] << " " << figure[i][2] << std::endl;
        }
        else{
        FileWy << figure[i][0] << " " << figure[i][1] << " " << figure[i][2] << std::endl;}
    } 
    FileWe.close();
    FileWy.close();

    return *this;
}


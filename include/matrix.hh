#pragma once

#include "size.hh"
#include "Vector3.hh"
#include <iostream>
#include <math.h>
#include <cstdlib>
#include <stdexcept>


/**
 * \brief Klasa Macierzy
 * 
 * Klasa pozwalajaca operowac na argumentach macierzy
 * Klasa jest szablonem ktory dziala dla macierzy2D i macierzy3D
 * Szablon przyjmuje wartości <typ danych, rozmiar macierzy>
 * 
 */
template<typename type, unsigned int table_size>
class Matrix {

private:
    type value[table_size][table_size];               // Wartosci macierzy

public:
    double angle; /**< kat obrotu prostopadloscianu */


    ///<Konstruktor macierzy
    Matrix(double tmp[SIZE][SIZE]){
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            value[i][j] = tmp[i][j];
        }}}                                      

    ///<Konstruktor klasy macierzy
    /**Wypelnia macierz zerami*/
    Matrix(){
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            value[i][j] = 0;
        }
    }
    };                               

    Vector3 operator * (Vector3 tmp) const;         ///< Operator mnożenia przez wektor

    ///<Przeciazenie operatora dodawania dwoch macierzy
    /**
     * @param - macierz tmp
     * @return - wynik dodawania result
    */
    Matrix operator + (Matrix tmp);
    
    ///<Metoda obliczajaca wyznacznik macierz
    /** 
     * @return deter - wyznacznik
     */ 
    double determinant(){
    double ratio;
    int i,j,k;
    for( i=0 ; i< SIZE-1 ; i++)
        {
            if(this->value[i][i] == 0.0)
            {
                std::cout<<"Mathematical Error!";
                exit(0);
            }
            for(j=i+1;j<SIZE;j++)
            {
                ratio = this->value[j][i]/this->value[i][i];

                for(k=0;k<SIZE;k++)
                {
                    this->value[j][k] = this->value[j][k] - ratio*this->value[i][k];
                }
            }
        }
    double deter = 1;
    for( i = 0; i < SIZE; ++i){
        deter *= this->value[i][i];
    }

    return deter;
};

    ///<Metoda inicjacji macierzy wartosciami obrotu o os x
    Matrix after_x();   

    ///<Metoda inicjacji macierzy wartosciami obrotu o os y
    Matrix after_y();   

    ///<Metoda inicjacji macierzy wartosciami obrotu o os z
    Matrix after_z();   

    ///<Metoda zmieniajaca wartosc pola macierzy(angle) z double na radiany
    double toradians(){
        this->angle = (this->angle * M_PI)/180;
        return this->angle;
    };

    // Matrix init(char tmp, double num, Prostopadl &pr);

    ///<Operator indeksowania Macierzy 
    /**
     * @param int row - ilosc wierszy
     * @param int column - ilosc kolumn
     * @return macierz
     */ 
    double  &operator () (unsigned int row, unsigned int column){
        if (row >= SIZE) {
        throw std::out_of_range("Error: Macierz jest poza zasiegiem");
    }

    if (column >= SIZE) {
        throw std::out_of_range("Error: Macierz jest poza zasiegiem"); 
    }

    return value[row][column];
    };
    
    const double &operator () (unsigned int row, unsigned int column) const{
        if (row >= SIZE) {
        std::cout << "Error: Macierz jest poza zasiegiem";
        exit(0); // lepiej byłoby rzucić wyjątkiem stdexcept
    }

    if (column >= SIZE) {
        std::cout << "Error: Macierz jest poza zasiegiem";
        exit(0); // lepiej byłoby rzucić wyjątkiem stdexcept
    }
    return value[row][column];
    };

    ///<Przeciazenie operatora mnozenia macierzy razy macierz 
    /**
     * @param sec - macierz
     * @return macierz tmp - wynik mnozenia
     */
    Matrix operator * (Matrix sec);

    ///<Przeciazenie porownania dwoch macierzy
    /**
     * @param tmp - macierz
     */ 
    bool operator == ( const Matrix tmp) const;

    Matrix<double,4> TurnAndTrans(Vector3 tmp);

    Matrix fill(Vector3 angles, Vector3 vec3);
};

// std::istream &operator>>(std::istream &in, Matrix &mat);

// std::ostream &operator<<(std::ostream &out, Matrix const &mat);


#pragma once

#include "size.hh"
#include <iostream>
#include <math.h>
#include <iomanip>

/**
 * \brief Klasa Wektora
 * 
 * Klasa pozwalajaca operowac na argumentach wektora
 * Klasa jest szablonem ktory dziala dla wektora2D i wektora3D
 * Szablon przyjmuje wartości <typ danych, rozmiar macierzy>
 * 
 */
template <typename type, unsigned int size_table>
class Vector {

private:

    type size[size_table];     /**< Tablica wektora */

    static unsigned int Vectors_in_use;

    static unsigned int Vectors_used;
    
public:

    ///<Konstruktor Vector
    /**
     * Wypelnia vector zerami
     */ 
    Vector();

    ~Vector(){
        --Vectors_in_use;
    };

    unsigned int amount_active_vectors(){return Vectors_in_use;};

    unsigned int amount_of_all_vectors(){return Vectors_used;};

    ///<Konstruktor wypelniajacy Vector wartosciami
    /** 
     * @param tablica double tmp[SIZE]
     * @return Wypelniona tablica wektora
     */ 
    Vector(double tmp[SIZE]){
    for (int i = 0; i < SIZE; ++i) {
        size[i] = tmp[i];
    }
    };

    ///<Konstruktor wypelniajacy Vector wartosciami
    /** 
     * @param tablica const double tmp[SIZE]
     * @return Wypelniona tablica wektora
     */ 
    Vector(const double tmp[SIZE]){
    for (int i = 0; i < SIZE; ++i) {
        size[i] = tmp[i];
    }
    };

    Vector(const std::initializer_list<type> &Sizelist);

    ///<Przeciazenie operatora dodawania wektorow
    /** 
     * @param const Vector &v 
     * @return result Vector
     */ 
    Vector operator + (const Vector &v);
    

    double toradians(){
        for(int i = 0; i < size_table; ++i){
            this->size[i] = (this->size[i] * M_PI)/180;}
            
        return *this;
    };

    ///<Przeciazenie operatora odejmowania wektorow
    /** 
     * @param const Vector &v 
     * @return result Vector
     */ 
    Vector operator - (const Vector &v);
    

    ///<Przeciazenie operatora mnozenia wektora razy cyfra
    /** 
     * @param const double &tmp - mnoznik 
     * @return result Vector
     */ 
    Vector operator * (const double &tmp);
    

    ///<Przeciazenie operatora dzielenia wektora przez cyfra
    /** 
     * @param const double &tmp - dzielnik 
     * @return result Vector
     */ 
    Vector operator / (const double &tmp);
    

    ///<Funktor wektora
    /** 
     * @param index - index wektora 
     * @return Wartosc wektora w danym miejscu tablicy jako stala
     */ 
    const double &operator [] (int index) const{
        if (index < 0 || index >= SIZE) {
            throw std::out_of_range("Error: Vector jest poza zasiegiem");    
        } 
        return size[index];    
    };

    ///<Funktor wektora
    /** 
     * @param index - index wektora 
     * @return Wartosc wektora w danym miejscu tablicy 
     */ 
    double &operator [] (int index){
        return const_cast<double &>(const_cast<const Vector *>(this)->operator[](index));
    };

    // Vector gauss(Matrix mat);

    ///<Przeciazenie operatora porownania wektorow const
    /** 
     * @param tmp - const Vector 
     * @return True or False
     */ 
    bool operator == (const Vector tmp) const ;

    ///<Przeciazenie operatora porownania (!=) wektorow const
    /** 
     * @param tmp - const Vector 
     * @return True or False
     */ 
    bool operator != (const Vector tmp) const ;

};

///<Przeciazenie operatora wyjscia Vector3D
std::ostream &operator << (std::ostream &stream, Vector<double,3> const &tmp);

///<Przeciazenie operatora wejscia Vector3D
std::istream &operator >> (std::istream &in, Vector<double,3> &tmp);

///<Przeciazenie operatora wyjscia Vector2D
std::ostream &operator << (std::ostream &stream, Vector<double,2> const &tmp);

///<Przeciazenie operatora wejscia Vector2D
std::istream &operator >> (std::istream &in, Vector<double,2> &tmp);

template<typename type, unsigned int size_table>
unsigned int Vector<type,size_table>::Vectors_in_use = 0;

template<typename type, unsigned int size_table>
unsigned int Vector<type,size_table>::Vectors_used = 0;

template<typename type, unsigned int size_table>
Vector<type,size_table>::Vector(){
    for (int i = 0; i < SIZE; ++i) {
        size[i] = 0;
        ++Vectors_in_use;
        ++Vectors_used;
    }
}

template<typename type, unsigned int size_table>
Vector<type,size_table>::Vector( const std::initializer_list<type> &Sizelist):
    Vector()
{
    assert(Sizelist.size() <= size_table);
    int Ind = -1;
    for(type Size_i : Sizelist) size[++Ind] = Size_i;
}


// template<typename type, unsigned int size_table>
// Vector<type,size_table>::Vector(const Vector &v){
//         ++Vectors_in_use;
//         ++Vectors_used;
//         for(unsigned int Ind = 0; Ind < size_table; ++Ind){
//             size[Ind] = v[Ind];
//         }
//     }






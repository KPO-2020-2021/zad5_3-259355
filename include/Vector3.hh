#ifndef Vector3_HH
#define Vector3_HH

#include "vector.hh"

typedef Vector<double, 3> Vector3;

//Definicje metod szczegolnych gdy dzialamy na wektorach3D
//Przeciazenie operatora porownania
//Przeciazenie operatora roznych
//Przeciazenie operatora wejscia i wyjscia
template<>
bool Vector3::operator == (const Vector3 tmp) const ;

template<>
bool Vector3::operator != (const Vector3 tmp) const ;

template<>
Vector3 Vector3::operator + (const Vector3 &v);

template<>
Vector3 Vector3::operator - (const Vector3 &v);

template<>
Vector3 Vector3::operator * (const double &tmp);

template<>
Vector3 Vector3::operator / (const double &tmp);

std::istream &operator >> (std::istream &in, Vector3 &tmp);
std::ostream &operator << (std::ostream &stream, Vector3 const &tmp);


#endif

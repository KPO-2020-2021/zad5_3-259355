#include "Vector3.hh"

/**
 * Przeciazenie operatora wyjsciowego
 * @param strumien wejsciowy stream
 * @param Vector3 const &tmp
 * @return strumien stream
 */
std::ostream& operator << ( std::ostream &stream, Vector3 const &tmp){

    stream << std::setw(16) << std::fixed << std::setprecision(10) << tmp[0]
           << std::setw(16) << std::fixed << std::setprecision(10) << tmp[1]
           << std::setw(16) << std::fixed << std::setprecision(10) << tmp[2];

    return stream;
}


/**
 * Przeciazenie operatora wejsciowy
 * @param strumien wejsciowy in
 * @param const Vector3 &tmp
 * @return strumien in
 */
std::istream &operator >> (std::istream &in, Vector3 &tmp) {
    for (int i = 0; i < 3; ++i) {
        in >> tmp[i];
    }
    // std::cout << std::endl;
    return in;
}

/**
 * Przeciazanei operatora porownania wektorow2D
 * @param const Vector3 tmp
 * @return True or False
 */
template<>
bool Vector3::operator == ( const Vector3 tmp) const {
    if(abs(this->size[0] - tmp[0]) <= MIN_DIFF && abs(this->size[1] - tmp[1]) <= MIN_DIFF && abs(this->size[2] - tmp[2]) <= MIN_DIFF){
        return true;
    }
    else{
        return false;
    }
}

/**
 * Przeciazanei operatora porownania != wektorow2D
 * @param const Vector3 tmp
 * @return True or False
 */template<>
bool Vector3::operator != (const Vector3 tmp) const{
    if(abs(this->size[0] - tmp[0]) > MIN_DIFF || abs(this->size[1] == tmp[1]) > MIN_DIFF || abs(this->size[2] == tmp[2]) > MIN_DIFF){
        return true;
    }
    else{
        return false;
    }
}

///<Przeciazenie operatora dodawania wektorow
    /** 
     * @param const Vector3 &v 
     * @return result Vector3
     */
    template<> 
    Vector3 Vector3::operator + (const Vector3 &v){
    Vector3 result;
    for (int i = 0; i < 3; ++i) {
        result[i] = size[i] += v[i];
    }
    return result;
    }

    ///<Przeciazenie operatora odejmowania wektorow
    /** 
     * @param const Vector3 &v 
     * @return result Vector3
     */ 
    template<>
    Vector3 Vector3::operator - (const Vector3 &v){
    Vector3 result;
    for (int i = 0; i < 3; ++i) {
        result[i] = size[i] -= v[i];
    }
    return result;
    }

    ///<Przeciazenie operatora mnozenia wektora razy cyfra
    /** 
     * @param const double &tmp - mnoznik 
     * @return result Vector3
     */ 
    template<>
    Vector3 Vector3::operator * (const double &tmp){
    Vector3 result;
    for (int i = 0; i < 3; ++i) {
        result[i] = size[i] *= tmp;
    }
    return result;
    }

    ///<Przeciazenie operatora dzielenia wektora przez cyfra
    /** 
     * @param const double &tmp - dzielnik 
     * @return result Vector3
     */ 
    template<>
    Vector3 Vector3::operator / (const double &tmp){
    Vector3 result;
    if(tmp != 0){
    for (int i = 0; i < 3; ++i) {
        result[i] = size[i] / tmp;
    }}
    else{
        throw std::invalid_argument("Division by 0");
    }
    return result;
    }


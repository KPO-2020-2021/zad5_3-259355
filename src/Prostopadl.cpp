#include "Prostopadl.hh"

/******************************************************************************
 |  Konstruktor klasy Prostopadl.                                                 |
 |  Argumenty:                                                                |
 |      Brak argumentow.                                                      |
 |  Zwraca:                                                                   |
 |      Prostopadl wypelnione wartoscia 0.                                       |
 */
Prostopadl::Prostopadl() {
    for (int i = 0; i < NOPOINTS; ++i) {
        for(int j = 0; j < SIZE; ++j) {
        pro[i][j] = 0;
    }
    }
}


/**
 * Metoda przyjmujaca jeden argument pozwalajaca poruszac sie po tablicy wierzcholkow
 * @param tablica wektorow 3D
 * @return nothing
 */ 
Prostopadl::Prostopadl(Vector3 tmp[NOPOINTS]) {
    for (int i = 0; i < NOPOINTS; ++i) {
        for(int j = 0; j < SIZE; ++j) {
        pro[i][j] = tmp[i][j];
    }
    }
}

/**
 * Przeciazenie operatora indeksowania pilnujaca czy nie wychodzi poza zakres
 * Przyjmuje dwa argument: 
 * @param int numer wiersza
 * @param int numer kolumny 
 * @return tablica wierzcholkow
 */ 
double &Prostopadl::operator()(unsigned int row, unsigned int column) {

    if (row >= NOPOINTS) {
        throw std::out_of_range("Error: Macierz jest poza zasiegiem");
    }

    if (column >= SIZE) {
        throw std::out_of_range("Error: Macierz jest poza zasiegiem");
    }

    return pro[row][column];
}


/**
 * Funktor Wektora (const) pilnujacy czy nie wychodzimy poza tablice wektora
 * @param int numer wiersza
 * @return wektor
 */ 
const Vector3 &Prostopadl::operator () (unsigned int row) const {

    if (row >= NOPOINTS) {
        throw std::out_of_range("Error: Vector jest poza zasiegiem");
    }

    // if (column >= SIZE) {
    //     std::cout << "Error: Prostopadl jest poza zasiegiem";
    //     exit(0); // lepiej byłoby rzucić wyjątkiem stdexcept
    // }

    return pro[row];
}

/**
 * Przeciazenie operatora () (const) indeksowania dla Prostopadla z odpowiednimi zabezpieczeniami
 * @param int numer wiersza
 * @param int numer kolumny 
 * @return Tablica wierzcholkow
 */ 
const double &Prostopadl::operator () (unsigned int row, unsigned int column) const {

    if (row >= NOPOINTS) {
        throw std::out_of_range("Error: Prostopadloscian jest poza zasiegiem");
    }

    if (column >= SIZE) {
        throw std::out_of_range("Error: Prostopadloscian jest poza zasiegiem");
    }

    return pro[row][column];
}

/**
 * Przeciazenie operatora mnozenia wierzcholkow razy macierz  
 * @param const macierz 3D
 * @return Prostopadloscian result
 */ 
Prostopadl Prostopadl::operator * (const Matrix3 &matrix){
    Prostopadl result;
    for (int i = 0; i < NOPOINTS; ++i){
        result.pro[i] = (matrix * this->pro[i]) + this->mid;
    }
    result.matrixtmp = this->matrixtmp;
    result.angles = this->angles;
    return result;
}

/**
 * Funkcja przyjmujaca jako argument wektor i zmieniajaca wartosci wspolrzednych Prostopadla (przesuniecie o wektor)
 * @param const Wektor 3D
 * @return Prostopadloscian 
 */ 
Prostopadl Prostopadl::move(const Vector3 &vec){
    for (int i = 0; i < NOPOINTS; ++i){
        for (int j = 0; j < SIZE; ++j){
        this->pro[i][j] += vec[j];
    }}
    return *this;
}

/**
 * Funkcja powodujaca animacje przesuniecia Prostopadla o wektor
 * @param referencja Wektor 3D vec
 * @param const char pointer sNazwaPliku
 * @param LaczeDoGnuplota 
 */ 
void Prostopadl::moving(Vector3 &vec, const char *sNazwaPliku, PzG::LaczeDoGNUPlota Lacze){

    Vector3 temp;
    temp = vec / 100.00 ;
    for(int i = 0; i < 100; ++i){
        this->move(temp);
        this->Save(sNazwaPliku);
        usleep(4000);
        Lacze.Rysuj(); 
        usleep(4000); 
    }
}

/**
 * Przeciazenie operatora przesuniecia bitowego w lewo
 * Pozwala w odpowiedni sposob wyswietlic wspolrzedne Prostopadla  
 * @param strumien wejsciowy stream
 * @param referencja const Prostopadloscian Pr
 * @return strumien wejsciowy stream
 */ 
std::ostream& operator << ( std::ostream &stream, const Prostopadl &Pr){

for (int i = 0; i < NOPOINTS; ++i){
    if( i%2 == 0 ){
            stream << std::endl;
        }
    stream << std::setw(16) << std::fixed << std::setprecision(10) << Pr(i) << std::endl;
    }
    stream << std::endl;
    stream << std::setw(16) << std::fixed << std::setprecision(10) << Pr(0) << std::endl;
    stream << std::setw(16) << std::fixed << std::setprecision(10) << Pr(1) << std::endl;
    return stream;
}

/**
 * Funkcja Void przyjmujaca kat o ktory obracamy Prostopadl wokol punktu (0,0)
 * Zmienia wartosci wspolrzednych Prostopadla o dany kata 
 * @param double const ang - kat
 * @param char which - os 
 */
void Prostopadl::turn(double const ang, char which, Prostopadl &loc){
    Matrix3 matrixx,matrixy,matrixz;
    double anglx,angly,anglz;
    if(SIZE != 3){
        matrixx.toradians();
        *this = *this * matrixx.after_x();
    }
    else{
        if( which == 'x'){

            this->angles[0] += ang;
            matrixx.angle = ang;
            anglx = this->angles[0];

            matrixx.toradians();
            this->matrixtmp = this->matrixtmp * matrixx.after_x();

            this->angles[0] = anglx;
        }
        else if( which == 'y'){

            this->angles[1] += ang;
            matrixy.angle = ang;  
            angly = this->angles[1];          
            
            matrixy.toradians();
            this->matrixtmp = this->matrixtmp * matrixy.after_y();

            this->angles[1] = angly;

        }
        else if( which == 'z'){

            this->angles[2] += ang;
            matrixz.angle = ang;
            anglz = this->angles[2];

            matrixz.toradians();
            this->matrixtmp = this->matrixtmp * matrixz.after_z();

            this->angles[2] = anglz;
        }
        else{
            std::cout << "Wrong option operation dumped" << std::endl;
    }} 
    loc.matrixtmp = matrixtmp;
    loc.angles = angles;
    *this = loc * matrixtmp;
}

void Prostopadl::turnagain(){

}

/**
 * Funkcja zapisu wspolrzednych bokow do pliku 
 * @param const char pointer sNazwaPliku
 * @return wartosc zwracana funkcji StrmPlikowy.fail()
 */
bool Prostopadl::Save(const char *sNazwaPliku)
{
  std::ofstream  StrmPlikowy;

  StrmPlikowy.open(sNazwaPliku);
  if (!StrmPlikowy.is_open())  {
    std::cerr << ":(  Operacja otwarcia do zapisu \"" << sNazwaPliku << "\"" << std::endl
	 << ":(  nie powiodla sie." << std::endl;
    return false;
  }

  StrmPlikowy << *this << std::endl;

  StrmPlikowy.close();
  return !StrmPlikowy.fail();
}

/**
 * Funkcja wykonujaca animacje obrotu Prostopadla o dany kat wykonuje sie dla mniej niz 5 powtorzen
 * @param referencja Protokat pro
 * @param const char pointer sNazwaPlikowy
 * @param double const ang - kat
 * @param double const howm - ile razy obrocic
 * @param LaczeDoGnuplota
 * @param char which - os
 */
void Prostopadl::turning(Prostopadl &pro, const char *sNazwaPliku, double const ang, double const howm, PzG::LaczeDoGNUPlota Lacze, char which)
{
  Prostopadl loc;  
  if(howm < 5){
    for(int i = 0; i < howm; ++i){
        for(int k = 0; k < abs(ang); ++k){
            pro.turn(ang/abs(ang), which,loc);
            pro.Save(sNazwaPliku);
            usleep(4000);
            Lacze.Rysuj(); 
            usleep(4000);
            }
        }
    }
  else{
      pro.turn(ang, which,loc);
      pro.Save(sNazwaPliku);
      Lacze.Rysuj();
  }
}

/**
 * Przeciazenie operatora porownania wierzcholkow prostopadloscianu
 * @param const Protokat &Pr
 * @return True or False
 */
bool Prostopadl::operator == (const Prostopadl &Pr){
    int k = 0;
    for(int i = 0; i < NOPOINTS; ++i){
    if(Pr(i) == this->pro[i])
        k++;
    }
    if(k == 8){
        return true;
    }
    else{
        return false;
    }
}

/**
 * Przeciazanie operatora dodawania do wierzcholkow prostopadloscianu vectora3D
 * @param const Vector3 vec2
 * @return Prostopadl pro
 */
Prostopadl Prostopadl::operator + (const Vector3 vec2){
    for (int i = 0; i < NOPOINTS; ++i){
        for (int j = 0; j < SIZE; ++j){
            this->pro[i][j] = this->pro[i][j] + vec2[j];
        }}
    return *this;
}

/**
 * Przeciazanie operatora odejmowania do wierzcholkow prostopadloscianu vectora3D
 * @param const Vector3 vec2
 * @return Prostopadl pro
 */
Prostopadl Prostopadl::operator - (const Vector3 vec2){
    for (int i = 0; i < NOPOINTS; ++i){
        for (int j = 0; j < SIZE; ++j){
            this->pro[i][j] = this->pro[i][j] - vec2[j];
        }}
    return *this;
}

/**
 * Funkcja inicjujaca prostopadloscian odpowiednio wyskalowany, przetransponowany i obrocony
 * @param const char *StrmWe
 * @param const char *StrmWY
 * @param Vector3 scale
 * @param double angle
 * @param Vector3 trans
 * @return Prostopadl pro
 */
// Prostopadl Prostopadl::InitPros(const char * StrmWe, const char * StrmWY, 
// double scalex, double scaley, double scalez, double angle, double tranx, double trany, double tranz){
Prostopadl::Prostopadl(const char * StrmWe, const char * StrmWY, 
Vector3 scale, double angle, Vector3 trans){
    this->Init_The_Figure(StrmWe,StrmWY,NOPOINTS,scale, trans,angle);
}

/**
 * Funkcja obliczajaca punkt w ktorym ma wyladowac dron (wspolrzedna x)
 * @param double x_position
 * @param double angle
 * @param double lenght
 * @return double x_of_end
 */
double Prostopadl::x_of_end(double x_position, double angle, double lenght){

    GranBlock temp;
    double x_of_end;

    angle = temp.toradians(angle);

    x_of_end = (cos(angle) * lenght) + x_position;

    return x_of_end;
}

/**
 * Funkcja obliczajaca punkt w ktorym ma wyladowac dron (wspolrzedna y)
 * @param double y_position
 * @param double angle
 * @param double lenght
 * @return double y_of_end
 */
double Prostopadl::y_of_end(double y_position, double angle, double lenght){

    GranBlock temp;
    double y_of_end;

    angle = temp.toradians(angle);
    
    y_of_end = (sin(angle) * lenght) + y_position;

    return y_of_end;
}

    




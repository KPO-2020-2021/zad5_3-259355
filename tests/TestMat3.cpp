// This is all that is needed to compile a test-runner executable.
// More tests can be added here, or in a new tests/*.cpp file.

#include "../tests/doctest/doctest.h"
#include "matrix3.hh"
// #include "matrix4.hh"
#include "size.hh"
#include "example.h"
#include <cmath>
#include <fstream>

// Tests Matrix3 


TEST_CASE("Matrix3 - turn by z"){

    Matrix3 matr;
    matr.angle = 180;
    matr.toradians();
    matr.after_z();
    double arg[][SIZE] = {{-1, 0.0, 0.0}, {-0.0, -1, 0.0}, {0.0, 0.0, 1}};
    Matrix3 matrtemp = Matrix3(arg);
    for(int i = 0; i < 3; ++i){
      for(int j = 0; j < 3; ++j){
        CHECK( abs(matr(i,j) - matrtemp(i,j)) <= MIN_DIFF );
    }
  }
}

TEST_CASE("Matrix3 - turn by z and x"){

    Matrix3 matr, matr2, matrwyn;
    matr.angle = 180;
    matr.toradians();
    matr.after_z();
    matr2.angle = 180;
    matr2.toradians();
    matr2.after_x();
    matrwyn = matr2 * matr; 
    double arg[][SIZE] = {{-1, 0.0, 0.0}, {-0.0, 1, 0.0}, {0.0, 0.0, -1}};
    Matrix3 matrtemp = Matrix3(arg);
    for(int i = 0; i < 3; ++i){
      for(int j = 0; j < 3; ++j){
        CHECK( abs(matrwyn(i,j) - matrtemp(i,j)) <= MIN_DIFF );
    }
  }
}

TEST_CASE("Matrix3 - turn by x"){

    Matrix3 matr;
    matr.angle = 180;
    matr.toradians();
    matr.after_x();
    double arg[][SIZE] = {{1, 0.0, 0.0}, {0.0, -1, 0.0}, {0.0, 0.0, -1}};
    Matrix3 matrtemp = Matrix3(arg);
    for(int i = 0; i < 3; ++i){
      for(int j = 0; j < 3; ++j){
        CHECK( abs(matr(i,j) - matrtemp(i,j)) <= MIN_DIFF );
    }
  }
}

TEST_CASE("Matrix3 - turn by y"){

    Matrix3 matr;
    matr.angle = 180;
    matr.toradians();
    matr.after_y();
    double arg[][SIZE] = {{-1, 0.0, 0.0}, {-0.0, 1, 0.0}, {0.0, 0.0, -1}};
    Matrix3 matrtemp = Matrix3(arg);
    for(int i = 0; i < 3; ++i){
      for(int j = 0; j < 3; ++j){
        CHECK( abs(matr(i,j) - matrtemp(i,j)) <= MIN_DIFF );
    }
  }
}

TEST_CASE("Matrix3 - toradians"){
    Matrix3 matr;
    matr.angle = 30;
    matr.toradians();
    double radangle = 0.5235987756;
    CHECK( abs(matr.angle - radangle) <= MIN_DIFF );
}

TEST_CASE("Matrix3 - sum of matrixs"){

    double arg1[][3] = {{20,20,20}, {20,20,20}, {20,20,20}};
    Matrix3 matr = Matrix3(arg1);

    double arg2[][3] = {{20,20,20}, {30,30,30}, {40,40,40}};
    Matrix3 matr2 = Matrix3(arg2);

    double argtemp[][3] = {{40,40,40}, {50,50,50}, {60,60,60}};
    Matrix3 matrtemp = Matrix3(argtemp);

    for(int i = 0; i < 3; ++i){
    CHECK( abs(matrtemp(i,i) - (matr(i,i) + matr2(i,i))) <= MIN_DIFF );
    }
}

TEST_CASE("Matrix3 - multiplication (vector)"){

    double arg1[3] = {20,20,20};
    Vector3 vec = Vector3(arg1);

    double arg2[][3] = {{20,30,0}, {20,30,0}, {20,30,0}};
    Matrix3 matr = Matrix3(arg2);

    double argtemp[3] = {1000,1000,1000};
    Vector3 vectemp = Vector3(argtemp);

    CHECK( vectemp == matr * vec );
}

TEST_CASE("Index operator"){
  double value[][3] = { {3,4,0}, {3,4,0}, {3,4,0}};
  double a, b, c;
  Matrix3 mat(value);
  a = mat(0,0);
  b = mat(0,1);
  c = mat(0,2);
  CHECK( (a == 3 && b == 4 && c == 0) );
}

TEST_CASE("Index operator values to vector"){
  double a = 3;
  double b = 4;
  double c = 0;
  double d = 5;
  Matrix3 mat;
  mat(0,0) = a;
  mat(0,1) = b;
  mat(1,0) = c;
  mat(1,1) = d;

  CHECK( (mat(0,0) == 3 && mat(0,1) == 4 && mat(1,0) == 0 && mat(1,1) == 5) );
}

TEST_CASE("Matrix3 - Constructor values in"){
  double value[][3] = {{3,4,0}, {4,5,0}, {5,6,0}};
  Matrix3 mat(value);
  CHECK( (mat(0,0) == 3 && mat(0,1) == 4 && mat(0,2) == 0 && mat(1,0) == 4 && mat(1,1) == 5 && mat(1,2) == 0 && mat(2,0) == 5 && mat(2,1) == 6 && mat(2,2) == 0)  );
}

TEST_CASE("Matrix3 - Out of range"){
  double value[][3] = {{3,4,0}, {4,5,0}};
  Matrix3 mat(value);
  WARN_THROWS( mat(3,3));
}

TEST_CASE("Matrix3 - Start Constructor"){
  Matrix3 mat;
  CHECK( (mat(0,0) == 0 && mat(0,1) == 0 && mat(0,2) == 0 && mat(1,0) == 0 && mat(1,1) == 0 && mat(1,2) == 0 && mat(2,0) == 0 && mat(2,1) == 0 && mat(2,2) == 0) );
}

TEST_CASE("Matrix3 - >> operator"){
  Matrix3 mat;
  std::istringstream in("0 0 0 1 1 1 2 2 2");
  in >> mat;
  CHECK( (mat(0,0) == 0 && mat(0,1) == 0 && mat(0,2) == 0 && mat(1,0) == 1 && mat(1,1) == 1 && mat(1,2) == 1 && mat(2,0) == 2 && mat(2,1) == 2 && mat(2,2) == 2) );
}

TEST_CASE("Matrix3 - display"){
    double value[][SIZE] = {{3,4,0}, {4,5,0}, {0,0,0}};
    Matrix3 mat(value);
    std::ostringstream stream;
    stream << mat;
    CHECK( "| 3 | | 4 | | 0 | | 4 | | 5 | | 0 | | 0 | | 0 | | 0 | " == stream.str());
}

// TEST_CASE("Matrix4 - display"){
//     double a,b,c;
//     a = 30;
//     b = 90;
//     c = 90;
//     double argm[] = {2,2,2};
//     Vector3 vec = Vector3(argm);
//     Matrix4 mat = mat.Rot_and_trans(a,b,c,vec);
//     CHECK( (mat(2,2) - 0.0) <= MIN_DIFF );
// }

TEST_CASE("Matrix3 - to radians"){
    double cos1;
    double ang;
    double t = 0;
    ang = -M_PI/2;
    cos1 = cos(ang);
    CHECK((t - cos1) <= MIN_DIFF);
}

TEST_CASE("Matrix3 - multiplication by another matrix"){
    double arg[][SIZE] = {{1,1,0}, {2,2,0}, {0,0,0}};
    double arg1[][SIZE] = {{1,2,0}, {1,2,0}, {1,2,0}};
    double res[][SIZE] = {{2,4,0}, {4,8,0}, {0,0,0}};
    Matrix3 mat1 = Matrix3(arg);
    Matrix3 mat2 = Matrix3(arg1);
    Matrix3 tmp(res);
    CHECK( tmp == mat1 * mat2);
}

TEST_CASE("Matrix3 - determinant"){
  double value[][SIZE] = {{3,3,0}, {4,5,0}, {0,0,0}};
  Matrix3 mat(value);
  double deter;
  double tmp = 3;
  deter = mat.determinant();
  CHECK( (deter - tmp) < MIN_DIFF);
}
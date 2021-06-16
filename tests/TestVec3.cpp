// This is all that is needed to compile a test-runner executable.
// More tests can be added here, or in a new tests/*.cpp file.

#include "../tests/doctest/doctest.h"
#include "Vector3.hh"
#include "size.hh"
#include "example.h"
#include <cmath>
#include <fstream>

// Tests Vector


TEST_CASE("Vector3 - sum"){
    double arg1[] = {100,100,100};
    double arg2[] = {300,300,300};
    Vector3 vec1 = Vector3(arg1);
    Vector3 vec2 = Vector3(arg2);
    double argt[] = {400,400,400};
    Vector3 temp = Vector3(argt);
    CHECK( (vec1 + vec2) == temp);
}

TEST_CASE("Vector3 - difference"){
    double arg1[SIZE] = {100,100,100};
    double arg2[SIZE] = {300,300,300};
    Vector3 vec1 = Vector3(arg1);
    Vector3 vec2 = Vector3(arg2);
    double argt[SIZE] = {-200,-200,-200};
    Vector3 temp = Vector3(argt);
    CHECK( temp == vec1 - vec2);
}

TEST_CASE("Vector3 - multiplication"){
    double arg1[SIZE] = {100,100,100};
    double arg = 2;
    Vector3 vec1 = Vector3(arg1);
    double argt[SIZE] = {200,200,200};
    Vector3 temp = Vector3(argt);
    CHECK( temp == vec1 * arg);
}

TEST_CASE("Vector3 - division (arg = 2)"){
    double arg1[SIZE] = {100,100,100};
    double arg = 2;
    Vector3 vec1 = Vector3(arg1);
    double argt[SIZE] = {50,50,50};
    Vector3 temp = Vector3(argt);
    CHECK( temp == vec1 / arg);
}

TEST_CASE("Vector3 - division (arg = 0)"){
    double arg1[SIZE] = {100,100,100};
    double arg = 0;
    Vector3 vec1 = Vector3(arg1);
    WARN_THROWS(vec1 / arg);
}

TEST_CASE("Index operator"){
  double value[] = {3,4,5};
  double a, b, c;
  Vector3 Vec(value);
  a = Vec[0];
  b = Vec[1];
  c = Vec[2];
  CHECK( (a == 3 && b == 4 && c == 5));
}

TEST_CASE("Index operator values to vector"){
  double a = 3;
  double b = 4;
  double c = 5;
  Vector3 Vec;
  Vec[0] = a;
  Vec[1] = b;
  Vec[2] = c;
  CHECK( (Vec[0] == 3 && Vec[1] == 4 && Vec[2] == 5));
}

TEST_CASE("Constructor values in"){
  double value[] = {3,4,5};
  Vector3 Vec(value);
  CHECK( (Vec[0] == 3 && Vec[1] == 4 && Vec[2] == 5));
}

TEST_CASE("Out of range"){
  double value[] = {3,4,5};
  Vector3 Vec(value);
  WARN_THROWS( Vec[3]);
}

TEST_CASE("Start Constructor"){
  Vector3 Vec;
  CHECK( (Vec[0] == 0 && Vec[1] == 0 && Vec[2] == 0));
}

TEST_CASE(">> operator"){
  Vector3 vec;
  std::istringstream in("0 1 2");
  in >> vec;
  CHECK( (vec[0] == 0 && vec[1] == 1 && vec[2] == 2) );
}

TEST_CASE("Vector3 - display"){
    double arg[] = {0,1,2};
    Vector3 vec1(arg);
    std::ostringstream stream;
    stream << vec1;
    CHECK( "    0.0000000000    1.0000000000    2.0000000000" == stream.str());
}
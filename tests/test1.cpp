#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../tests/doctest/doctest.h"

// This is all that is needed to compile a test-runner executable.
// More tests can be added here, or in a new tests/*.cpp file.

#include "Prostopadl.hh"
#include "size.hh"
#include "example.h"
#include <cmath>
#include <fstream>





// Tests which check if functions related with rectangle


TEST_CASE("Rectangle - Proper save of coordinates")
{
  double arg1[] = {100,100,150};
  double arg2[] = {50,100,150};
  double arg3[] = {100,25,150};
  double arg4[] = {50,25,150};
  double arg5[] = {100,25,75};
  double arg6[] = {50,25,75};
  double arg7[] = {100,100,75};
  double arg8[] = {50,100,75};
  Vector3 vec1 = Vector3(arg1);
  Vector3 vec2 = Vector3(arg2);
  Vector3 vec3 = Vector3(arg3);
  Vector3 vec4 = Vector3(arg4);
  Vector3 vec5 = Vector3(arg5);
  Vector3 vec6 = Vector3(arg6);
  Vector3 vec7 = Vector3(arg7);
  Vector3 vec8 = Vector3(arg8);
  Vector3 arguments1[] = { vec1, vec2, vec3, vec4, vec5, vec6, vec7, vec8}; /**< inicjacja prostopadloscianu nr 1 */
  Prostopadl pro = Prostopadl(arguments1);
  SUBCASE("First coordinate"){
      double temp1[] = {100,100,150};
      Vector3 vec1 = Vector3(temp1);
    CHECK( vec1 == pro(0));
  }
  SUBCASE("Second coordinate"){
      double temp2[] = {50,100,150};
      Vector3 vec2 = Vector3(temp2);
    CHECK( vec2 == pro(1));
  }
  SUBCASE("Third coordinate"){
      double temp3[] = {100,25,150};
      Vector3 vec3 = Vector3(temp3);
    CHECK( vec3 == pro(2));
  }
  SUBCASE("Fourth coordinate"){
      double temp4[] = {50,25,150};
      Vector3 vec4 = Vector3(temp4);
    CHECK( vec4 == pro(3));
  }
  SUBCASE("Fourth coordinate"){
      double temp4[] = {100,25,75};
      Vector3 vec4 = Vector3(temp4);
    CHECK( vec4 == pro(4));
  }
  SUBCASE("Fourth coordinate"){
      double temp4[] = {50,25,75};
      Vector3 vec4 = Vector3(temp4);
    CHECK( vec4 == pro(5));
  }
  SUBCASE("Fourth coordinate"){
      double temp4[] = {100,100,75};
      Vector3 vec4 = Vector3(temp4);
    CHECK( vec4 == pro(6));
  }
  SUBCASE("Fourth coordinate"){
      double temp4[] = {50,100,75};
      Vector3 vec4 = Vector3(temp4);
    CHECK( vec4 == pro(7));
  }
}

// TEST_CASE("Rectangle - Proper length of sides")
// {
//   double arg1[] = {100,100,150};
//   double arg2[] = {50,100,150};
//   double arg3[] = {100,25,150};
//   double arg4[] = {50,25,150};
//   double arg5[] = {100,25,75};
//   double arg6[] = {50,25,75};
//   double arg7[] = {100,100,75};
//   double arg8[] = {50,100,75};
//   Vector3 vec1 = Vector3(arg1);
//   Vector3 vec2 = Vector3(arg2);
//   Vector3 vec3 = Vector3(arg3);
//   Vector3 vec4 = Vector3(arg4);
//   Vector3 vec5 = Vector3(arg5);
//   Vector3 vec6 = Vector3(arg6);
//   Vector3 vec7 = Vector3(arg7);
//   Vector3 vec8 = Vector3(arg8);
//   Vector3 arguments1[] = { vec1, vec2, vec3, vec4, vec5, vec6, vec7, vec8}; /**< inicjacja prostopadloscianu nr 1 */
//   Prostopadl pro = Prostopadl(arguments1);
//   double mid1[] = {75,62.5,112.5};
//   double arg[][SIZE] = {{1,0,0}, {0,1,0}, {0,0,1}};
//   pro.matrixtmp = Matrix3(arg);
//   pro.mid = Vector3(mid1); 
//   pro.lenght3D();
//   CHECK((pro.lenght[0][0] == 75 && pro.lenght[1][0] == 50 && pro.lenght[2][0] == 75));
// }

TEST_CASE("Rectangle - rotate after x (angle - 360, 1 time)"){
  double arg1[] = {100,100,150};
  double arg2[] = {50,100,150};
  double arg3[] = {100,25,150};
  double arg4[] = {50,25,150};
  double arg5[] = {100,25,75};
  double arg6[] = {50,25,75};
  double arg7[] = {100,100,75};
  double arg8[] = {50,100,75};
  Vector3 vec1 = Vector3(arg1);
  Vector3 vec2 = Vector3(arg2);
  Vector3 vec3 = Vector3(arg3);
  Vector3 vec4 = Vector3(arg4);
  Vector3 vec5 = Vector3(arg5);
  Vector3 vec6 = Vector3(arg6);
  Vector3 vec7 = Vector3(arg7);
  Vector3 vec8 = Vector3(arg8);
  Vector3 arguments1[] = { vec1, vec2, vec3, vec4, vec5, vec6, vec7, vec8}; /**< inicjacja prostopadloscianu nr 1 */
  Prostopadl pro = Prostopadl(arguments1);
  double arg[][SIZE] = {{1,0,0}, {0,1,0}, {0,0,1}};
  pro.matrixtmp = Matrix3(arg);
  double mid1[] = {75,62.5,112.5};
  pro.mid = Vector3(mid1); 
  Prostopadl loc;
  loc.matrixtmp = Matrix3(arg);
  loc = pro - (pro.mid);
  loc.mid = Vector3(mid1);
  pro.turn(360,'x',loc);
  SUBCASE("First coordinate"){
      double temp1[] = {100,100,150};
      Vector3 vec1 = Vector3(temp1);
    CHECK( vec1 == pro(0));
  }
  SUBCASE("Second coordinate"){
      double temp2[] = {50,100,150};
      Vector3 vec2 = Vector3(temp2);
    CHECK( vec2 == pro(1));
  }
  SUBCASE("Third coordinate"){
      double temp3[] = {100,25,150};
      Vector3 vec3 = Vector3(temp3);
    CHECK( vec3 == pro(2));
  }
  SUBCASE("Fourth coordinate"){
      double temp4[] = {50,25,150};
      Vector3 vec4 = Vector3(temp4);
    CHECK( vec4 == pro(3));
  }
  SUBCASE("Fifth coordinate"){
      double temp4[] = {100,25,75};
      Vector3 vec4 = Vector3(temp4);
    CHECK( vec4 == pro(4));
  }
  SUBCASE("Sixth coordinate"){
      double temp4[] = {50,25,75};
      Vector3 vec4 = Vector3(temp4);
    CHECK( vec4 == pro(5));
  }
  SUBCASE("Seventh coordinate"){
      double temp4[] = {100,100,75};
      Vector3 vec4 = Vector3(temp4);
    CHECK( vec4 == pro(6));
  }
  SUBCASE("Eighth coordinate"){
      double temp4[] = {50,100,75};
      Vector3 vec4 = Vector3(temp4);
    CHECK( vec4 == pro(7));
  }
}

TEST_CASE("Rectangle - rotate after x and y (angle - 360, 1 time)"){
  double arg1[] = {100,100,150};
  double arg2[] = {50,100,150};
  double arg3[] = {100,25,150};
  double arg4[] = {50,25,150};
  double arg5[] = {100,25,75};
  double arg6[] = {50,25,75};
  double arg7[] = {100,100,75};
  double arg8[] = {50,100,75};
  Vector3 vec1 = Vector3(arg1);
  Vector3 vec2 = Vector3(arg2);
  Vector3 vec3 = Vector3(arg3);
  Vector3 vec4 = Vector3(arg4);
  Vector3 vec5 = Vector3(arg5);
  Vector3 vec6 = Vector3(arg6);
  Vector3 vec7 = Vector3(arg7);
  Vector3 vec8 = Vector3(arg8);
  Vector3 arguments1[] = { vec1, vec2, vec3, vec4, vec5, vec6, vec7, vec8}; /**< inicjacja prostopadloscianu nr 1 */
  Prostopadl pro = Prostopadl(arguments1);
  double arg[][SIZE] = {{1,0,0}, {0,1,0}, {0,0,1}};
  pro.matrixtmp = Matrix3(arg);
  double mid1[] = {75,62.5,112.5};
  pro.mid = Vector3(mid1); 
  Prostopadl loc;
  loc.matrixtmp = Matrix3(arg);
  loc = pro - (pro.mid);
  loc.mid = Vector3(mid1);
  pro.turn(360,'x',loc);
  pro.turn(360,'y',loc);
  SUBCASE("First coordinate"){
      double temp1[] = {100,100,150};
      Vector3 vec1 = Vector3(temp1);
    CHECK( vec1 == pro(0));
  }
  SUBCASE("Second coordinate"){
      double temp2[] = {50,100,150};
      Vector3 vec2 = Vector3(temp2);
    CHECK( vec2 == pro(1));
  }
  SUBCASE("Third coordinate"){
      double temp3[] = {100,25,150};
      Vector3 vec3 = Vector3(temp3);
    CHECK( vec3 == pro(2));
  }
  SUBCASE("Fourth coordinate"){
      double temp4[] = {50,25,150};
      Vector3 vec4 = Vector3(temp4);
    CHECK( vec4 == pro(3));
  }
  SUBCASE("Fifth coordinate"){
      double temp4[] = {100,25,75};
      Vector3 vec4 = Vector3(temp4);
    CHECK( vec4 == pro(4));
  }
  SUBCASE("Sixth coordinate"){
      double temp4[] = {50,25,75};
      Vector3 vec4 = Vector3(temp4);
    CHECK( vec4 == pro(5));
  }
  SUBCASE("Seventh coordinate"){
      double temp4[] = {100,100,75};
      Vector3 vec4 = Vector3(temp4);
    CHECK( vec4 == pro(6));
  }
  SUBCASE("Eighth coordinate"){
      double temp4[] = {50,100,75};
      Vector3 vec4 = Vector3(temp4);
    CHECK( vec4 == pro(7));
  }
}

TEST_CASE("Rectangle - move (vector [100,100,100])"){
  
    double arg1[] = {100,100,150};
    double arg2[] = {50,100,150};
    double arg3[] = {100,25,150};
    double arg4[] = {50,25,150};
    double arg5[] = {100,25,75};
    double arg6[] = {50,25,75};
    double arg7[] = {100,100,75};
    double arg8[] = {50,100,75};
    Vector3 vec1 = Vector3(arg1);
    Vector3 vec2 = Vector3(arg2);
    Vector3 vec3 = Vector3(arg3);
    Vector3 vec4 = Vector3(arg4);
    Vector3 vec5 = Vector3(arg5);
    Vector3 vec6 = Vector3(arg6);
    Vector3 vec7 = Vector3(arg7);
    Vector3 vec8 = Vector3(arg8);
    Vector3 arguments1[] = { vec1, vec2, vec3, vec4, vec5, vec6, vec7, vec8}; /**< inicjacja prostopadloscianu nr 1 */
    Prostopadl pro = Prostopadl(arguments1);
    double args[SIZE] = {100,100,100};
    Vector3 vec = Vector3(args);
    pro.move(vec);
    SUBCASE("First coordinate"){
      double temp1[] = {200,200,250};
      Vector3 vec1 = Vector3(temp1);
    CHECK( vec1 == pro(0));
  }
  SUBCASE("Second coordinate"){
      double temp2[] = {150,200,250};
      Vector3 vec2 = Vector3(temp2);
    CHECK( vec2 == pro(1));
  }
  SUBCASE("Third coordinate"){
      double temp3[] = {200,125,250};
      Vector3 vec3 = Vector3(temp3);
    CHECK( vec3 == pro(2));
  }
  SUBCASE("Fourth coordinate"){
      double temp4[] = {150,125,250};
      Vector3 vec4 = Vector3(temp4);
    CHECK( vec4 == pro(3));
  }
  SUBCASE("Fourth coordinate"){
      double temp4[] = {200,125,175};
      Vector3 vec4 = Vector3(temp4);
    CHECK( vec4 == pro(4));
  }
  SUBCASE("Fourth coordinate"){
      double temp4[] = {150,125,175};
      Vector3 vec4 = Vector3(temp4);
    CHECK( vec4 == pro(5));
  }
  SUBCASE("Fourth coordinate"){
      double temp4[] = {200,200,175};
      Vector3 vec4 = Vector3(temp4);
    CHECK( vec4 == pro(6));
  }
  SUBCASE("Fourth coordinate"){
      double temp4[] = {150,200,175};
      Vector3 vec4 = Vector3(temp4);
    CHECK( vec4 == pro(7));
  }
}

// TEST_CASE("Rectangle - Proper save of coordinates")
// {
//   double arg1[] = {100,100,150};
//   double arg2[] = {50,100,150};
//   double arg3[] = {100,25,150};
//   double arg4[] = {50,25,150};
//   double arg5[] = {100,25,75};
//   double arg6[] = {50,25,75};
//   double arg7[] = {100,100,75};
//   double arg8[] = {50,100,75};
//   Vector3 vec1 = Vector3(arg1);
//   Vector3 vec2 = Vector3(arg2);
//   Vector3 vec3 = Vector3(arg3);
//   Vector3 vec4 = Vector3(arg4);
//   Vector3 vec5 = Vector3(arg5);
//   Vector3 vec6 = Vector3(arg6);
//   Vector3 vec7 = Vector3(arg7);
//   Vector3 vec8 = Vector3(arg8);
//   Vector3 arguments1[] = { vec1, vec2, vec3, vec4, vec5, vec6, vec7, vec8}; /**< inicjacja prostopadloscianu nr 1 */
//   Prostopadl pro = Prostopadl(arguments1);
//   double mid1[] = {75,62.5,112.5};
//   pro.mid = Vector3(mid1); 
//   Prostopadl loc;
//   loc = pro - (pro.mid);
//   loc.mid = Vector3(mid1);

//   Matrix<double,4> mat4;
//   Matrix3 matrixx;
//   matrixx.angle = 360;
//   matrixx.toradians();

//   double argm[] = {100,100,100};
//   double argm1[] = {360,360,360};
//   Vector3 vectmp = Vector3(argm);
//   Vector3 vecang = Vector3(argm1);
//   mat4.fill(vectmp, vecang);
//   pro = loc * mat4;
//   SUBCASE("First coordinate"){
//       double temp1[] = {200,200,250};
//       Vector3 vec1 = Vector3(temp1);
//     CHECK( vec1 == pro(0));
//   }
//   SUBCASE("Second coordinate"){
//       double temp2[] = {150,200,250};
//       Vector3 vec2 = Vector3(temp2);
//     CHECK( vec2 == pro(1));
//   }
//   SUBCASE("Third coordinate"){
//       double temp3[] = {200,125,250};
//       Vector3 vec3 = Vector3(temp3);
//     CHECK( vec3 == pro(2));
//   }
//   SUBCASE("Fourth coordinate"){
//       double temp4[] = {150,125,250};
//       Vector3 vec4 = Vector3(temp4);
//     CHECK( vec4 == pro(3));
//   }
//   SUBCASE("Fourth coordinate"){
//       double temp4[] = {200,125,175};
//       Vector3 vec4 = Vector3(temp4);
//     CHECK( vec4 == pro(4));
//   }
//   SUBCASE("Fourth coordinate"){
//       double temp4[] = {150,125,175};
//       Vector3 vec4 = Vector3(temp4);
//     CHECK( vec4 == pro(5));
//   }
//   SUBCASE("Fourth coordinate"){
//       double temp4[] = {200,200,175};
//       Vector3 vec4 = Vector3(temp4);
//     CHECK( vec4 == pro(6));
//   }
//   SUBCASE("Fourth coordinate"){
//       double temp4[] = {150,200,175};
//       Vector3 vec4 = Vector3(temp4);
//     CHECK( vec4 == pro(7));
//   }
// }



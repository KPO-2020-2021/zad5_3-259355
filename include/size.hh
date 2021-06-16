#pragma once
#include <array>
// #include "Vector3.hh"

constexpr int SIZE = 3;
constexpr int NOPOINTS = 20;
constexpr double MIN_DIFF = 0.000000001;

#define SZESCIAN_WZ "../bryly_wzorcowe/szescian.dat"
#define PLASZCZYZNA_WZ "../bryly_wzorcowe/plaszczyzna.dat"
#define ROTORY_BEF "../bryly_wzorcowe/graniastoslup6.dat"
#define Path_V1 "../dat/path_of_the_drone1.dat"
#define Path_V2 "../dat/path_of_the_drone2.dat"

#define SZESCIAN_ZM "../dat/szescian_zm.dat"
#define SZESCIAN_ZM_V2 "../dat/szescian_zm_v2.dat"
#define SZESCIAN_ZM_LOC "../dat/szescian_zm_loc.dat"
#define SZESCIAN_ZM_LOC_V2 "../dat/szescian_zm_loc_v2.dat"

#define ROTORY_1 "../dat/rotor1.dat"
#define ROTORY_2 "../dat/rotor2.dat"
#define ROTORY_3 "../dat/rotor3.dat"
#define ROTORY_4 "../dat/rotor4.dat"
#define ROTORYLOC_1 "../dat/rotorloc1.dat"
#define ROTORYLOC_2 "../dat/rotorloc2.dat"
#define ROTORYLOC_3 "../dat/rotorloc3.dat"
#define ROTORYLOC_4 "../dat/rotorloc4.dat"

#define ROTORY_1_V2 "../dat/rotor1_v2.dat"
#define ROTORY_2_V2 "../dat/rotor2_v2.dat"
#define ROTORY_3_V2 "../dat/rotor3_v2.dat"
#define ROTORY_4_V2 "../dat/rotor4_v2.dat"
#define ROTORYLOC_1_V2 "../dat/rotorloc1_v2.dat"
#define ROTORYLOC_2_V2 "../dat/rotorloc2_v2.dat"
#define ROTORYLOC_3_V2 "../dat/rotorloc3_v2.dat"
#define ROTORYLOC_4_V2 "../dat/rotorloc4_v2.dat"

#define PROSTOPADL_SCALE 10,8,4
#define ROTATOR_SCALE 8,8,2
#define SKALA_JED 1,1,1
constexpr double arg_jed[] = {1,1,1};
constexpr double arg_pros_sc[] = {10,8,4};
constexpr double arg_rotator_sc[] = {8,8,2};
constexpr double init_args[] = {0,0,2};
constexpr double arg_lf[] = {5,4,5};
constexpr double arg_rf[] = {5,-4,5};
constexpr double arg_lb[] = {-5,4,5};
constexpr double arg_rb[] = {-5,-4,5};

#define TRANSLATION_LEFT_FRONT 5,4,5
#define TRANSLATION_RIGHT_FRONT 5,-4,5
#define TRANSLATION_LEFT_BACK -5,4,5
#define TRANSLATION_RIGHT_BACK -5,-4,5

#define TRANSLATION_ALL 20,20,0
const double arg_trans_all[] = {20,20,0};

// const char *NamesFilesLoc_V1[] = {SZESCIAN_ZM_LOC,ROTORYLOC_1,ROTORYLOC_2,ROTORYLOC_3,ROTORYLOC_4, nullptr};
// const char *NamesFilesProp_V1[] = {SZESCIAN_ZM,ROTORY_1,ROTORY_2,ROTORY_3,ROTORY_4, nullptr};

// const char *NamesFilesLoc_V2[] = {SZESCIAN_ZM_LOC_V2,ROTORYLOC_1_V2,ROTORYLOC_2_V2,ROTORYLOC_3_V2,ROTORYLOC_4_V2, nullptr};
// const char *NamesFilesProp_V2[] = {SZESCIAN_ZM_V2,ROTORY_1_V2,ROTORY_2_V2,ROTORY_3_V2,ROTORY_4_V2, nullptr};


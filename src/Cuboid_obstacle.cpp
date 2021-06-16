#include "Cuboid_obstacle.hh"

bool Cuboid_obstacle::check_landing_object(Vector3,Prostopadl temp,unsigned int ,double x_gr1, double x_gr2,Vector3 position) {
        // Prostopadl temp;
        // temp = get_obst();
        bool tmp = true;   
        double value_gr1x,value_gr2x,value_gr1y,value_gr2y;
        double y1,y2;
        value_gr1x = temp(6,0);
        value_gr2x = temp(1,0);
        value_gr1y = temp(6,1);
        value_gr2y = temp(1,1);
        for(int i = x_gr1; i <= x_gr2; ++i ){
            y1 = std::sqrt(49 - pow(i-position[0],2)) + position[1];
            y2 = -y1;
                if( (i < value_gr1x && i > value_gr2x) && ((y1 < value_gr1y && y1 > value_gr2y) || (y2 < value_gr1y && y2 > value_gr2y))){
                    tmp = false;
                }
        }
        return tmp;
    }

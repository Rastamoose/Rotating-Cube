#include "Screen.h"
#include <numeric>

// Conversions cause points to lose accuracy over time and thus become smaller (use -Wconversion flag to check)

struct vec3{
    float x,y,z;
};

struct connection{
    int a,b;
};

void rotate(vec3& point, float x=1, float y=1, float z=1){
    float rad = 0;
    
    rad = x;
    point.y = std::cos(rad) * point.y - std::sin(rad) * point.z;
    point.z = std::sin(rad) * point.y + std::cos(rad) * point.z;

    rad = y;
    point.x = std::cos(rad) * point.x + std::sin(rad) * point.z;
    point.z = -std::sin(rad) * point.x + std::cos(rad) * point.z;

    rad = z;
    point.x = std::cos(rad) * point.x - std::sin(rad) * point.y;
    point.y = std::sin(rad)  *point.x + std::cos(rad) * point.y;

}

void line(Screen& screen, float x1, float y1, float x2, float y2){
    float dx = x2-x1;       //difference between x values
    float dy = y2-y1;

    float length = std::sqrt(dx*dx + dy*dy);        //use pythag to find line length
    float angle = std::atan2(dy,dx);                //get angle of line
    
    for(float i = 0; i < length; i++){
        screen.pixel(x1+std::cos(angle)*i, y1+std::sin(angle)*i);
    }
}


int main(){
    Screen screen;
    
    std::vector<vec3> points {
        {100,100,100},
        {200,100,100},
        {200,200,100},
        {100,200,100},

        {100,100,200},
        {200,100,200},
        {200,200,200},
        {100,200,200}
    };

    std::vector<connection> connections{
         {0,4},
         {1,5},
         {2,6},
         {3,7},
         
         {0,1},
         {1,2},
         {2,3},
         {3,0},

         {4,5},
         {5,6},
         {6,7},
         {7,4}
    };

    // Calculate centeroid
    //
    vec3 centeroid{0,0,0};         // centre needed as reference for rotation so points dont fly off
    for(auto& p : points){
        centeroid.x += p.x;
        centeroid.y += p.y;
        centeroid.z += p.z;
    }                               // add up all points on each axis then divide by total points
    centeroid.x /= points.size();
    centeroid.y /= points.size();
    centeroid.z /= points.size();


    while(true){

        for(auto& p : points){
            p.x -= centeroid.x;         // subtract centeroid from points of each axis
            p.y -= centeroid.y;
            p.z -= centeroid.z;
            rotate(p, 0.001, 0.005, 0.002);
            p.x += centeroid.x;         // then add centeroid from points of each axis to restore points
            p.y += centeroid.y;
            p.z += centeroid.z;

            screen.pixel(p.x, p.y);
        }

        for(auto& con : connections){
            line(screen, points[con.a].x,
                         points[con.a].y,
                         points[con.b].x,
                         points[con.b].y);
        }

        screen.show();
        screen.clear();
        screen.input();
        SDL_Delay(30);      //delay in ms
    }
}

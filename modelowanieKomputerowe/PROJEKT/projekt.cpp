#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cmath>

using namespace std;



class czasteczka{
    private:
        double _x, _y, _vx, _vy, _m, _r;

        double OdlegloscOdCzastki(czasteczka *c, int i,int j){
            double x1=c[i]._x, y1=c[i]._y, x2=c[j]._x, y2=c[j]._y;
            double dx=x2-x1;
            double dy=y2-y1;
            return sqrt(dx*dx+dy*dy);
        }
    public:
        czasteczka(double x, double y, double vx, double vy, double m, double r){
            this-> _x = x;
            this-> _y = y;
            this-> _vx = vx;
            this-> _vy = vy;
            this-> _m = m;
            this-> _r = r;
        }
};




int main(){
    czasteczka *c1 = new czasteczka(1.0, 1.0, 1.0, 1.0, 1.0, 1.0);
    cout << c1;


}
#ifndef BOX_H
#define BOX_H
#include <iostream>

using namespace std;

class Box
{
  private :
    int x,y;
    int correctx,correcty;
    int numberOfTheBox;
    int ManhDist;

  public:
    Box();

    int getX(){return x;}
    int getY(){return y;}
    int getcorrectx(){return correctx;}
    int getcorrecty(){return correcty;}
    int getNumberOfTheBox(){return numberOfTheBox;}
    int getManhDist() {return ManhDist;}

    void setX(int x);
    void setY(int y);
    void setNumberOfTheBox(int numberOfTheBox);
    void setManhDist(int ManhDist);
    void setcorrectx(int correctx);
    void setcorrecty(int correcty);

    Box& operator= (const Box &);

};
#endif // BOX_H

#include "Box.h"
#include "Board.h"

Box::Box(){
  this->x=0;
  this->y=0;
  this->numberOfTheBox=0;
  this->ManhDist=0;
  this->correcty=0;
  this->correctx=0;
}

//---------------------------------------------------------
void Box::setNumberOfTheBox(int numberOfTheBox){
  this->numberOfTheBox=numberOfTheBox;
}
void Box::setX(int x){
  this->x=x;
}
void Box::setY(int y){
  this->y=y;
}
void Box::setManhDist(int ManhDist){
  this->ManhDist=ManhDist;
}
void Box::setcorrectx(int correctx){
  this->correctx=correctx;
}
void Box::setcorrecty(int correcty){
  this->correcty=correcty;
}
//---------------------------------------------------------

Box& Box::operator= (const Box &box){

  x=box.x;
  y=box.y;
  numberOfTheBox=box.numberOfTheBox;
  ManhDist=Board::GetManhDist(*this);
  return *this;
}

#include "Board.h"

Board::Board(){
  Boxes =new Box*[WIDTH];
  for(int i=0;i<WIDTH;i++)
    Boxes[i]=new Box[WIDTH];

  int count=0;
  for(int i=0;i<WIDTH;i++)
    for(int j=0;j<HEIGHT;j++){
      Boxes[i][j].setNumberOfTheBox(Initial[i][j]);
      Boxes[i][j].setX(i);
      Boxes[i][j].setY(count%WIDTH);
      count++;
    }
  SetCorrects();

  for(int i=0;i<WIDTH;i++)
    for(int j=0;j<HEIGHT;j++)
      Boxes[i][j].setManhDist(GetManhDist(Boxes[i][j]));

}

Board::~Board(){
  for(int i=0;i<WIDTH;i++)
      delete [] Boxes[i];
}


int Board::SumOfManhDist(){
  int sum=0;

  for(int i=0;i<WIDTH;i++){
    for(int j=0;j<HEIGHT;j++){
      int k=(abs(Boxes[i][j].getX()-Boxes[i][j].getcorrectx()) + abs(Boxes[i][j].getY()-Boxes[i][j].getcorrecty()));
      sum+=k;
    }
  }

    return sum;
}


void Board::Update(Board &board){
  int count=0;
  for(int i=0;i<WIDTH;i++)
    for(int j=0;j<HEIGHT;j++){
      board.Boxes[i][j].setNumberOfTheBox(board.Initial[i][j]);
      board.Boxes[i][j].setX(i);
      board.Boxes[i][j].setY(count%WIDTH);
      count++;
    }
  board.SetCorrects();

  for(int i=0;i<WIDTH;i++)
    for(int j=0;j<HEIGHT;j++)
      board.Boxes[i][j].setManhDist(GetManhDist(board.Boxes[i][j]));

}

int Board::GetManhDist(Box &B){
  return (abs(B.getX()-B.getcorrectx()) + abs(B.getY()-B.getcorrecty()));
}

long long Board::GetKey(){
  long long key=0;
  long long a=1000000000;
  for(int i=0;i<WIDTH;i++)
    for(int j=0;j<HEIGHT;j++){
        key+=Initial[i][j]*a;
        a/=10;
    }

  return key;
}

void Board::print(){

  for(int i=0;i<WIDTH;i++){
    for(int j=0;j<HEIGHT;j++)
      cout<<Boxes[i][j].getNumberOfTheBox()<<"  ";/*<<"("<<Boxes[i][j].getX()<<","<<Boxes[i][j].getY()<<")\""<<Boxes[i][j].getManhDist()<<"\" ";*/

    cout<<endl;
  }
  cout<<endl;

}

void Board::SetCorrects(){
  int count=1;
  int x=0,y=0;

  for(int i=0;i<WIDTH;i++)
    for(int j=0;j<HEIGHT;j++)
      if(Boxes[i][j].getNumberOfTheBox()==count){
          Boxes[i][j].setcorrectx(x);
          Boxes[i][j].setcorrecty(y);
          i=0;
          j=-1;
          count++;
          y++;
          if(y>2){
            y=0;
            x++;
          }
      }else if (Boxes[i][j].getNumberOfTheBox()==0){
        Boxes[i][j].setcorrectx(2);
        Boxes[i][j].setcorrecty(2);
        EmptyY=Boxes[i][j].getY();
        EmptyX=Boxes[i][j].getX();
      }

}

vector <Board *> Board::expand(){
    vector <Board *> children;
    Board *child;
    child = new Board;
    if (goUp(*child))
        children.push_back(child);
    else
        delete child;
    child = new Board;
    if (goDown(*child))
        children.push_back(child);
    else
        delete child;
    child = new Board;
    if (goLeft(*child))
        children.push_back(child);
    else
        delete child;
    child = new Board;
    if (goRight(*child))
        children.push_back(child);
    else
        delete child;

    return children;
}

bool Board::goUp(Board &child){

  if(EmptyX>0){
    child=*this;

    child.EmptyX=EmptyX-1;

    int current=child.Initial[EmptyX][EmptyY];
    child.Initial[EmptyX][EmptyY]=child.Initial[EmptyX-1][EmptyY];
    child.Initial[EmptyX-1][EmptyY]=current;
    Update(child);
    child.SetPrev(this);

    return true;
  }
  return false;
}

bool Board::goDown(Board &child){
  if(EmptyX<2){
    child=*this;

    child.EmptyX=EmptyX+1;

    int current=child.Initial[EmptyX][EmptyY];
    child.Initial[EmptyX][EmptyY]=child.Initial[EmptyX+1][EmptyY];
    child.Initial[EmptyX+1][EmptyY]=current;
    Update(child);
    child.SetPrev(this);

    return true;
  }
  return false;
}

bool Board::goLeft(Board &child){
  if(EmptyY>0){
    child=*this;

    child.EmptyY=EmptyY-1;

    int current=child.Initial[EmptyX][EmptyY];
    child.Initial[EmptyX][EmptyY]=child.Initial[EmptyX][EmptyY-1];
    child.Initial[EmptyX][EmptyY-1]=current;
    Update(child);
    child.SetPrev(this);

    return true;

  }
  return false;
}

bool Board::goRight(Board &child){
  if(EmptyY<2){
    child=*this;

    child.EmptyY=EmptyY+1;

    int current=child.Initial[EmptyX][EmptyY];
    child.Initial[EmptyX][EmptyY]=child.Initial[EmptyX][EmptyY+1];
    child.Initial[EmptyX][EmptyY+1]=current;
    Update(child);
    child.SetPrev(this);

    return true;
  }
  return false;
}

int Board::GetDepth(){
  int Count=0;
  Board *p=this;
  while(p->prev!=nullptr){
    Count++;
    p=p->prev;
  }

  return Count;
}

Board &Board::operator= (const Board &o)
{
    Boxes =new Box*[WIDTH];
    for(int i=0;i<WIDTH;i++)
      Boxes[i]=new Box[WIDTH];

    for(int i=0;i<WIDTH;i++)
      for(int j=0;j<HEIGHT;j++){
        Boxes[i][j]=o.Boxes[i][j];
        Initial[i][j]=o.Initial[i][j];
      }
    EmptyX=o.EmptyX;
    EmptyY=o.EmptyY;

    return *this;
}

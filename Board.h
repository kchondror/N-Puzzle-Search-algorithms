#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <queue>
#include <math.h>
#include "Box.h"

#define WIDTH 3
#define HEIGHT 3

using namespace std;

class Board
{
  private:
    Box **Boxes;
    int Initial[WIDTH][HEIGHT]={{3,8,1},{0,4,2},{7,6,5}};
    int EmptyX,EmptyY;
    int Hvalue;
    Board *prev;

  public:
    Board();
    ~Board();

    int SumOfManhDist();
    static int GetManhDist(Box &);
    long long GetKey();
    void print();
    void SetCorrects();
    void Update(Board &);

    int GetDepth();
    int GetHvalue(){return Hvalue;}
    Board *GetPrev(){return prev;}

    void SetPrev(Board *board){
      this->prev=board;
    }
    void SetHvalue(int value){
      this->Hvalue=value;
    }

    vector <Board *> expand();
    bool goUp(Board &);
    bool goDown(Board  &);
    bool goLeft(Board  &);
    bool goRight(Board  &);

    Board & operator= (const Board &);
};

class myComparator
{
public:
    int operator() (Board *p1 , Board *p2) const
    {
        return p1->GetHvalue()>p2->GetHvalue();
    }
};

#endif // BOARD_H

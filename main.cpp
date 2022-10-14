#include <iostream>
#include <unordered_map>
#include <queue>
#include <stack>
#include <algorithm>
#include <chrono>
#include <ctime>

#include "Box.h"
#include "Board.h"
using namespace std;

Board *DFS(Board *initial,long long &examined, long long &mem)
{
    stack<Board *> agenda;
    unordered_map <long long,Board *> closed;

    agenda.push(initial);
    examined=0;
    mem=1;
    while (agenda.size()>0)
    {
        if ( (long long)(agenda.size() + closed.size()) > mem)
            mem = agenda.size() + closed.size();

        Board *s = agenda.top();
        agenda.pop();

        if (closed.count(s->GetKey())==0)
        {
            examined++;

            if (s->SumOfManhDist()==0)
                return s;

            pair<long long,Board *> k (s->GetKey(),s);
            closed.insert(k);
            vector<Board *> children =s->expand();
            for (unsigned int i=0;i<children.size();i++)
                if (closed.count(children[i]->GetKey())==0)
                    agenda.push(children[i]);
        }
    }
    return nullptr;
}

Board *BFS(Board *initial,long long &examined, long long &mem)
{
    queue<Board *> agenda;
    unordered_map <unsigned long,Board *> closed;

    agenda.push(initial);
    examined=0;
    mem=1;
    while (agenda.size()>0)
    {
        if ( (long long)(agenda.size() + closed.size()) > mem)
            mem = agenda.size() + closed.size();

        Board *s = agenda.front();
        agenda.pop();
        if (closed.count(s->GetKey())==0)
        {

            examined++;
            if (s->SumOfManhDist()==0)
                return s;


            pair<unsigned long,Board *> k (s->GetKey(),s);
            closed.insert(k);
            vector<Board *> children =s->expand();
            for (unsigned int i=0;i<children.size();i++)
                if (closed.count(children[i]->GetKey())==0)
                    agenda.push(children[i]);
        }
    }
    return nullptr;
}

Board *BestFS(Board *initial, long long &examined, long long &mem)
{
    priority_queue <Board *, vector<Board *>, myComparator > agenda;
    unordered_map <unsigned long,Board * > closed;
    agenda.push(initial);
    examined = 0;
    mem=1;
    while (agenda.size()>0)
    {
        if ( (long long)(agenda.size() + closed.size()) > mem)
            mem = agenda.size() + closed.size();

        Board *s = agenda.top();
        agenda.pop();

        if (closed.count(s->GetKey())==0)
        {
            examined++;

            if (s->SumOfManhDist()==0)
                return s;

            pair<unsigned long,Board*> k (s->GetKey(),s);
            closed.insert(k);
            vector<Board *> children = s->expand();
            for (unsigned int i=0;i<children.size();i++)
            {
                if (closed.count(children[i]->GetKey())==0)
                {
                    children.at(i)->SetHvalue(children.at(i)->SumOfManhDist());
                    agenda.push(children.at(i));
                }
            }
        }
    }
    return nullptr;
}

Board *AStar(Board *initial, long long &examined, long long &mem){

    priority_queue <Board *, vector<Board *>, myComparator > agenda;
    unordered_map <unsigned long,Board * > closed;
    agenda.push(initial);
    examined = 0;
    mem=1;
    while (agenda.size()>0){

        if ( (long long)(agenda.size() + closed.size()) > mem)
            mem = agenda.size() + closed.size();

        Board *s = agenda.top();
        agenda.pop();

        if (closed.count(s->GetKey())==0){
            examined++;

            if (s->SumOfManhDist()==0)
                return s;

            pair<unsigned long,Board*> k (s->GetKey(),s);
            closed.insert(k);
            vector<Board *> children = s->expand();
            for (unsigned int i=0;i<children.size();i++)
                if (closed.count(children[i]->GetKey())==0){
                    children.at(i)->SetHvalue(children.at(i)->SumOfManhDist() + children.at(i)->GetDepth());
                    agenda.push(children.at(i));
                }
        }
    }
    return nullptr;
}

void PrintPath(Board *finalState){

    vector<Board *> fullPath;
    while (finalState->GetPrev()!=nullptr){
        fullPath.push_back(finalState);
        finalState=finalState->GetPrev();
    }
    fullPath.push_back(finalState);

    for(unsigned int i=fullPath.size()-1;i>0;i--)
        fullPath.at(i)->print();
    fullPath.at(0)->print();

}


int main() {
  long long examined=0,mem=0;
  Board initial;
  initial.SetPrev(nullptr);
  Board *bsol;



  cout<<"DFS: "<<endl;

  auto start = chrono::high_resolution_clock::now();
  bsol=DFS(&initial,examined,mem);
  if (bsol!=nullptr){
      auto end = chrono::high_resolution_clock::now();
      cout<<"depth = "<<bsol->GetDepth()<<", Mem: "<<mem<<", Examined: "<<examined<<" latency: "<<chrono::duration_cast<chrono::nanoseconds>(end-start).count() <<endl;
  }
  else
      cout<<"Problem unsolvable"<<endl;


  cout<<endl<<"BFS: "<<endl;

  start = chrono::high_resolution_clock::now();
  bsol=BFS(&initial,examined,mem);
  if (bsol!=nullptr){
      auto end = chrono::high_resolution_clock::now();
      cout<<"depth = "<<bsol->GetDepth()<<", Mem: "<<mem<<", Examined: "<<examined<<" latency: "<<chrono::duration_cast<chrono::nanoseconds>(end-start).count() <<endl;
  }
  else
      cout<<"Problem unsolvable"<<endl;


  cout<<endl<<"Best First: "<<endl;

  start = chrono::high_resolution_clock::now();
  bsol=BestFS(&initial,examined,mem);
  if (bsol!=nullptr){
      auto end = chrono::high_resolution_clock::now();
      cout<<"depth = "<<bsol->GetDepth()<<", Mem: "<<mem<<", Examined: "<<examined<<" latency: "<<chrono::duration_cast<chrono::nanoseconds>(end-start).count() <<endl;
  }
  else
      cout<<"Problem unsolvable"<<endl;


  cout<<endl<<"A*: "<<endl;

  start = chrono::high_resolution_clock::now();
  bsol=AStar(&initial,examined,mem);
  if (bsol!=nullptr){
      auto end = chrono::high_resolution_clock::now();
      cout<<"depth = "<<bsol->GetDepth()<<", Mem: "<<mem<<", Examined: "<<examined<<" latency: "<<chrono::duration_cast<chrono::nanoseconds>(end-start).count() <<endl;
  }
  else
      cout<<"Problem unsolvable"<<endl;


  cout<<endl<<"Path :"<<endl;
  PrintPath(bsol);







}

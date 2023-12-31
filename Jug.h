#pragma once
#include <vector>
#include <string> // It doesn't make sense for me to be using Dijkstra's shortest path algorithm, because all my nodes are directly connected 
using namespace std; 
struct Node {
  friend class Jug;
  Node();
  Node(Node*, Node*, Node*, Node*, Node*, int);
  Node* getA(); Node* getB(); Node* getC(); Node* getD(); Node* getE(); int getCost(); void setA(Node*); void setB(Node*); void setC(Node*); void setD(Node*); void setE(Node*); void setCost(int);
  /*void setCa(int a) { *Ca = a; };
  void setCb(int a) { *Cb = a; };
  void setN(int a) { *N = a; };
  void setLa(int a) { *La = a; };
  void setLb(int a) { *Lb = a; };
  void setCounter(int a) { *Counter = a; };*/
  int cost;
  Node* A;
  Node* B;
  Node* C;
  Node* D;
  Node* E;
  //int* Ca, Cb, N, La, Lb, Counter;
};
class Jug {
  public:
    Jug(int,int,int,int,int,int,int,int,int);
    /*~Jug();*/
    /*void setCa(int);
    void setCb(int);
    void setN(int);
    void setLa(int);
    void setLb(int);
    void setCounter(int);
    void setPrint(string &);
    int getCa();
    int getCb();
    int getN();
    int getLa();
    int getLb();
    int getCounter();
    vector<string> getPrint();*/
      //solve is used to check input and find the solution if one exists
      //returns -1 if invalid inputs. solution set to empty string.
      //returns 0 if inputs are valid but a solution does not exist. solution set to empty string.
      //returns 1 if solution is found and stores solution steps in solution string.
    int solve(string &solution);
    bool solve1(Node*, vector<int> &, vector<string> &, int &);
  private:
    Node* FA; Node* FB; Node* EA; Node* EB; Node* PAB; Node* PBA; vector<string> Print;
    int ca; int cb; int n; int la = 0; int lb = 0; int counter = 0; // counter will count cost
    //vector <int> counterlist; 
      //anything else you need
};

//Node* Node::getA() { return A; } Node* Node::getB() { return B; } Node* Node::getC() { return C; }
//Node* Node::getD() { return D; } Node* Node::getE() { return E; } int Node::getCost() { return cost; }
/*void Jug::setCa(int a) { ca = a; }
void Jug::setCb(int a) { cb = a; }
void Jug::setN(int a) { n = a; }
void Jug::setLa(int a) { la = a; }
void Jug::setLb(int a) { lb = a; }
void Jug::setCounter(int a) { counter = a; }
void Jug::setPrint(string & a) { Print.push_back(a); }
int Jug::getCa() { return ca; }
int Jug::getCb() { return cb; }
int Jug::getN() { return n; }
int Jug::getLa() { return la; }
int Jug::getLb() { return lb; }
int Jug::getCounter() { return counter; }
vector<string> Jug::getPrint() { return Print; }*/

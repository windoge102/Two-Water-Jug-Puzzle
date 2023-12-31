#include "Jug.h"
#include <vector>
#include <string>
#include <iostream>
using namespace std;
Node::Node() { A = nullptr; B = nullptr; C = nullptr; D = nullptr; E = nullptr; cost = 0; }
Node::Node(Node* a, Node* b, Node* c, Node* d, Node* e, int Cost/*, int &f, int &g, int &h, int &i, int &j, int &k*/) {
  A = a; B = b; C = c; D = d; E = e; cost = Cost; /*Ca = f; Cb = g; N = h; La = i; Lb = j; Counter = k;*/
}
Node* Node::getA(){return A;} Node* Node::getB(){return B;} Node* Node::getC(){return C;} Node* Node::getD(){return D;} Node* Node::getE(){return E;} int Node::getCost(){return cost;}
void Node::setA(Node* a) { A = a; } void Node::setB(Node* a) { B = a; } void Node::setC(Node* a) { C = a; }
void Node::setD(Node* a) { D = a; } void Node::setE(Node* a) { E = a; } void Node::setCost(int a) { cost = a; }
Jug::Jug(int Ca, int Cb, int N, int cfA, int cfB, int ceA, int ceB, int cpAB, int cpBA) {
  //int* o1, o2, o3, o4, o5, o6; o1 = ca; o2 = cb; o3 = n; o4 = la; o5 = lb; o6 = counter;
  FA = new Node(); FB = new Node(); EA = new Node(); EB = new Node(); PAB = new Node(); PBA = new Node();
  //Node* FA1 = new Node(FB, EB, PBA, PAB, EA, cfA); Node* FB1 = new Node(EB, PBA, PAB, EA, FA, cfB); FA = FA1; FB = FB1;
  //Node* EA1 = new Node(FA, FB, EB, PBA, PAB, ceA); Node* EB1 = new Node(PBA, PAB, EA, FA, FB, ceB); EA = EA1; EB = EB1;
  //Node* PAB1 = new Node(EA, FA, FB, EB, PBA, cpAB); Node* PBA1 = new Node(PAB, EA, FA, FB, EB, cpBA); PAB = PAB1; PBA = PBA1;
  FA->setA(FB);FA->setB(EB);FA->setC(PBA);FA->setD(PAB);FA->setE(EA);FA->setCost(cfA); FB->setA(EB);FB->setB(PBA);FB->setC(PAB);FB->setD(EA);FB->setE(FA);FB->setCost(cfB);
  EA->setA(FA);EA->setB(FB);EA->setC(EB);EA->setD(PBA);EA->setE(PAB);EA->setCost(ceA); EB->setA(PBA);EB->setB(PAB);EB->setC(EA);EB->setD(FA);EB->setE(FB);EB->setCost(ceB);
  PAB->setA(EA);PAB->setB(FA);PAB->setC(FB);PAB->setD(EB);PAB->setE(PBA);PAB->setCost(cpAB);PBA->setA(PAB);PBA->setB(EA);PBA->setC(FA);PBA->setD(FB);PBA->setE(EB);PBA->setCost(cpBA);
  ca = Ca; cb = Cb; n = N;
  //Node* S = new Node(FA, FB, nullptr, nullptr, nullptr); //Node* curr = S; // curr will iterate through the graph;
}
int Jug::solve(string& solution) {
  if (!(0 < (ca) && ca <= (cb)) || !(n <= cb) || !((FA->cost && FB->cost && EA->cost && EB->cost && PAB->cost && PBA->cost) > 0) || !(cb <= 1000)) {
    solution = ""; return -1;
  }
  else { vector<int> checkprev = {0, 0}; vector<string> COUT; int mincost = 10000; int hi = mincost; string conv; // mincost has to be pass by reference in order to keep track of the most efficient solution
    bool A1, A2, A3, A4, A5, A6; // a counterlist does not make sense because how do you access the sequence to get to that counter once you have the mincost?
    A1 = solve1(FA, checkprev, COUT, mincost); if (mincost < hi) { hi = mincost; } A2 = solve1(FB, checkprev, COUT, mincost); if (mincost < hi) { hi = mincost; }
    A3 = solve1(EA, checkprev, COUT, mincost); if (mincost < hi) { hi = mincost; } A4 = solve1(EB, checkprev, COUT, mincost); if (mincost < hi) { hi = mincost; }
    A5 = solve1(PAB, checkprev, COUT, mincost); if (mincost < hi) { hi = mincost; } A6 = solve1(PBA, checkprev, COUT, mincost); if (mincost < hi) { hi = mincost; }
    if (A1 == false && A2 == false && A3 == false && A4 == false && A5 == false && A6 == false) { solution = ""; return 0; }
    else { // at least one solution exists
      for (unsigned int i = 0; i < Print.size(); i++) { solution += Print.at(i); } solution += "success "; conv = to_string(mincost); solution += conv; return 1;
    }
  } // check a node, then recursively check the 5 nodes that the node points to, then recursively check the 5 pointers of the new node, repeat until
} //either the condition is met or if no changes has been made to la/lb or if the program has iterated over 50 times
bool Jug::solve1(Node* curr, vector<int>& cPrev, vector<string>& Cout, int& minc) { // we HAVE to use pass by reference here!!!
  int a = counter; int b = curr->cost; a += b; counter = a; int y = la; int z = lb; // qla = pla; qlb = plb; pla = la; plb = lb;
  string SFA = "fill A\n"; string SFB = "fill B\n"; string SEA = "empty A\n"; string SEB = "empty B\n"; string SPAB = "pour A B\n"; string SPBA = "pour B A\n";
  if (curr == FA) { la = ca; Cout.push_back(SFA); } // FB obtains the address of FA, not the actual node
  else if (curr == FB) { lb = cb; Cout.push_back(SFB); }
  else if (curr == EA) { la = 0; Cout.push_back(SEA); }
  else if (curr == EB) { lb = 0; Cout.push_back(SEB); }
  else if (curr == PAB) { Cout.push_back(SPAB); int c = lb; int d = la; c += d;
    if (c > cb) { d = c - cb; lb = cb; la = d; } else { lb = c; la = 0; }
  }
  else if (curr == PBA) { Cout.push_back(SPBA); int c = la; int d = lb; c += d ;
    if (c > ca) { d = c - ca; la = ca; lb = d; } else { la = c; lb = 0; }
  } cPrev.push_back(la); cPrev.push_back(lb); // la will be even index, lb will be odd index
  if (lb == n && la == 0) {  // print sequence of most costefficient
    cPrev.pop_back(); cPrev.pop_back();
    if (minc == 10000 || minc > counter) { minc = counter; Print = Cout; Cout.pop_back(); counter -= curr->cost; la = y; lb = z; return true; }
    else { counter -= curr->cost; Cout.pop_back(); return false; } // the solution found is not optimal, return false
  } // true means that the solution has been found
  else if (cPrev.size() > 3) { // check all previous jug states stored in cPrev: if current jug states are the same as any previous, then return
    for (unsigned int i = 0; i < (cPrev.size() - 3); i += 2) { // cPrev.size() - 1 is a bug that makes the return value always false
      if (cPrev.at(i) == la && cPrev.at(i + 1) == lb) {
        counter -= curr->cost; cPrev.pop_back(); cPrev.pop_back(); Cout.pop_back(); la = y; lb = z; return false;
      }
    } // invalid solutions don't get to put sequences into Print
  } bool A, B, C, D, E; int f = minc; int det = 0; A = solve1(curr->getA(), cPrev, Cout, minc); //det = 1 if we choose A, det = 2 if we choose B, etc.
  if (minc < f) { f = minc; det = 1; } // else disregard A
  B = solve1(curr->getB(), cPrev, Cout, minc); if (minc < f) { f = minc; det = 2; } C = solve1(curr->getC(), cPrev, Cout, minc); if (minc < f) { f = minc; det = 3; }
  D = solve1(curr->getD(), cPrev, Cout, minc); if (minc < f) { f = minc; det = 4; } E = solve1(curr->getE(), cPrev, Cout, minc); if (minc < f) { f = minc; det = 5; }
  cPrev.pop_back(); cPrev.pop_back(); Cout.pop_back(); counter -= b; la = y; lb = z;
  if (det == 1) { return A; } else if (det == 2) { return B; } else if (det == 3) { return C; } else if (det == 4) { return D; } else if (det == 5) { return E; } else { return false; }
} // learned that vectors passed through functions cannot be properly modified unless it's pass by reference
#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include <string>
#include "Actor.h"
#include <list>
#include <stack>

using namespace std;
int min( int x, int y);
int max( int x, int y);
bool isslottaken(stack<coord> x, int m_x, int m_y);

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp




class StudentWorld : public GameWorld
{
public:
	StudentWorld(std::string assetDir)
    : GameWorld(assetDir)	{
	}

  
    virtual int init();
    
    int distance(Actor& p, Actor& q);
    
    int FrackDistance(Actor&p);


    virtual int move();
    
    bool checkRange(Actor::Direction dir,int m_x, int m_y);  // ||||||    |||||||
    


    void dirtdeleter(int x, int y , char ch);

    virtual ~StudentWorld();
    
    void morgue();
    
//    bool boulderboolean(int x, int y);

    
    virtual void cleanUp();
    
    bool contains(int& x, int& y);
    
    void nextToExit();

    void clearArea(int x, int y);
    
    void goldpick(Goodies& good);
    
    void Fillexcept();
    
    bool keepYaDistance(int x, int y);

    void autoalive();
    
    bool CheckExcept(int x, int y);
    
    bool BoulderFall(Actor& bld);
    
    bool facing_each_other(Protester& p);
    
    bool isInStraightLine ( Actor& p);
    
    void changeDirectionFace( Actor& p);
    
    bool check_around_dirt(Protester& p, Actor::Direction dir);
    
    bool checkarea(int x , int y, Actor::Direction dir );
    
    bool protestersannoyed(Actor& act);
    
    void initializeBP();
    
    bool frackfacing(Protester & p);
    
    int annoyFman();
    
//    void increaseFscore(int x);
    
    string print();
    
    string streamhelper(int x);
    
    int sonarCount( int x);
    
    void GenerateSonarAndWater();
    
    bool checkDead();
    
    void exitAlgorithm();
    
    bool completedLevel();
    
    void checkifSTONED(Actor& bld);
    
    void checkrich();
    
  //  void autosetVisible();
    
    Actor::Direction frackFace();
    
    void nuggetAround(Goodies & act);
    
    void SquirtDosomethig(int x, int , Actor::Direction dur);
    
    void Sonarstuff();
    
    void addActor(Actor*x);
    
    bool checkBlueprint(int x, int y, Actor::Direction dir);
    
    void StoreRobot(int x, int y, int c, int xcor, int ycor, Actor::Direction dir);
    
    void add2bp (char a[][64], int x, int y , char z) {a[x][63-y] = z;}
    bool checkBP( char a[][64],int x, int y , char z) {return a[x][63-y] == z;}
    int Ychanger ( int x) { return 63-x;}
    
    void addProtesters();
    
    
void stepsToReach(int sr, int sc);

private:
    std::list<Actor*> xx;
    char Blueprint[64][64];
    Dirt* dirty[64][64];
    Frack * Fman;
    coord* except[1500];
    int arraySize=(0);
    MProtester * rp;
    HProtester *hp;
    Squirt*s;
    int T = min(25, 200 - getLevel());
    int P = min(15, 2 + getLevel() * 1.5);
    int ProtesterTicks=(26);
    int giveupsound=(0);
    int Nprotesters=(0);
    int Nboulder;
};


// oil barrels. squirt, check Completion etc. comeplete by tonight the only thing u want to be left for tomrrow is maybe the coming back of the dead protesters when they finally die tbh if u get one u got all so dw too much about those.




#endif // STUDENTWORLD_H_

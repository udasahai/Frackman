#ifndef ACTOR_H_
#define ACTOR_H_
#include <random>
#include "GraphObject.h"
int randInt(int min, int max);

class StudentWorld;

using namespace std;
// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class Actor :public GraphObject
{
public:
    Actor(int imageID, int x, int y, StudentWorld* m_std, double size = 1, int Depth=0 , Direction face = right, int anpoints =0)
    :GraphObject(imageID,x,y,face,size,Depth)
    {
        m_imageID=imageID;
        setVisible(true);
        m_row = y;
        m_col = x;
        dir = face;
        this->m_std = m_std;
        m_annoyPoints = anpoints;
        
    }
    int changecount(int count =-1){m_count+=count;return m_count;}
    void setdead(){isalive=false;}
    bool getDead() { return isalive;}
    bool hasGold(){return gold;}
    void setGold(bool x = true) {gold= x;}
    int Imageid(){return m_imageID;}
    int tickwait(int x){ if(x==-10) m_tickWait=0; else m_tickWait = x;return m_tickWait;}
    int row(int y=0){m_row+=y; return m_row;}
    int col(int x=0){m_col+=x; return m_col;}
    int numberOfTicks(int x=0)
    {if (x==-10)
    {Nticks=0; return 0;}
    Nticks+=x;return Nticks;}
    bool checkrange(Direction dir,int m_x, int m_y);
    void setannoyPoints(int x) { m_annoyPoints+=x;}
    StudentWorld* getWorld();
    int getName() { return name;}
    void setName(int x){ name = x;}
    int getannoyPoints() { return m_annoyPoints;}
    int getTickwait() { return m_tickWait;}
    
    void set_leave_field(){m_isLeaveField = true;}
    bool is_leave_field() {return m_isLeaveField;}
    


    int setExitX( int x){ exitX = x; return  exitX;}
    int setExitY( int y ){exitY = y; return exitY;}
    int getExitX () { return exitX;}
    int getExitY () { return exitY;}


    int setNextX( int x){ nextX = x; return  nextX;}
    int setNextY( int y ){nextY = y; return nextY;}
    int getNextX () { return nextX;}
    int getNextY () { return nextY;}
    int barrels(int x=0) { m_barrels += x; return m_barrels;}
    void setNsteps(int x){ nextSteps = x;}
    int getNSteps() { return nextSteps;}
    Direction facing() {return dir;}
    Direction getNextDir(){ return m_nextDir;}
    void setNextDir(Direction x){m_nextDir=x;}
    void setExitDir(Direction x){m_exitDir=x;}
    Direction getExitDir(){ return m_exitDir;}
    int giveupsound(int x=0){ m_giveupsound += x; return m_giveupsound;}
    void set2increment(int x = false){toincrement = x;}
    bool get2incr(){return toincrement;}

    
    virtual void doSomething() = 0;

private:
    int m_imageID;
    int m_count=0;
    bool isalive = true;
    bool m_isLeaveField = false;
    int m_row;
    int m_col;
    int m_barrels=0;
    int Nticks=0;
    int nextX=-1;
    int nextY=-1;
    int exitX=-1;
    int exitY=-1;
    int nextSteps=-1;
    int m_annoyPoints;
    Direction m_nextDir;
    Direction m_exitDir;
    int m_giveupsound=(0);
    Direction dir;
    StudentWorld * m_std;
    int m_tickWait=(0);
    bool gold = false;
    int ticktock = 0;
    bool toincrement = true;
    int name;


    // bool setVisible=false;
    

    
};

struct coord
{
    coord(int x, int y)
    {
        m_x =x; m_y =y;
    }
    int m_x;
    int m_y;
};

class Dirt :public Actor
{
public:
    Dirt(int imageID, int x, int y):Actor(imageID,x,y,nullptr, 0.25,3){ setName(IID_DIRT);};
    void doSomething(){};
    ~Dirt(){};
private:
};


class Frack;
class Squirt :public Actor
{
public:
    Squirt(int imageID, int x, int y, Direction xx, StudentWorld* std):Actor(imageID,x,y,std,1,1,xx){ setVisible(false);setDirection(xx);setName(IID_WATER_SPURT);}
    void doSomething();
private:
};
class Sonar; 
class GoldDropping;
class Frack :public Actor
{
public:
    Frack(int imageID, int x, int y, StudentWorld*std):Actor(imageID,x,y,std){m_std=std;setName(IID_PLAYER);setannoyPoints(10);}
    
    void doSomething();
    void manageSquirt();
    void dirtDirection(char x);
    void moveSquirt( int x, int y);
    void SQvisible();
    int nuggetCount(int x=0){m_nuggetCount+=x; return m_nuggetCount;}
    int Sonarticks( int x) { m_sonarticks +=x; return m_sonarticks;}
    int Nwaterpools(int x=0) { return m_waterpool+=x;}
    int Nsonars(int x=0) { return Sonars+=x;}

private:
    StudentWorld * m_std;
    Squirt * m_ssd ;
    GoldDropping * gild;
    Sonar * s_std;
    int SQcounter=0;
    int SQobjects=0;
    int m_nuggetCount=0;
    int m_sonarticks = 0;
    int m_waterpool = 5;
    int Sonars = 1;
};

class Boulder :public Actor
{
public:
    Boulder(int imageID, int x, int y, StudentWorld * m_std):Actor(imageID,x,y, m_std,1,1, down){this->m_std = m_std; setVisible(false);setName(IID_BOULDER);}

    void doSomething();
        
private:
    StudentWorld * m_std;

};







class Protester :public Actor
{
public:
    Protester(int imageID, int x, int y, StudentWorld * m_std, int time):Actor(imageID,x,y,m_std,1,0, left, time){}
    void doSomething(){};
    int shoutTick(int x) {m_nonrestingtick+=x; return m_nonrestingtick;}
    void setnull(){m_nonrestingtick=0;}
    int numberOfSteps(int x=0){return nsteps+x;}
    void setStepsZero(){ nsteps = 0;}

  //  void setDirection(Direction x){m_dir = x;}
    void chooseNsteps(){int x=randInt(8,60);nsteps=x;}
   virtual void HPfunction(){};
    int PerpTurn (int x=0){tickPerturn+=x;return tickPerturn;}
private:
    int m_nonrestingtick =16;
    int nsteps;
    Direction m_dir;
    int tickPerturn=0;

};


class Goodies :public Actor
{
public:
    Goodies(int imageID, int x, int y, StudentWorld* std, int size = 1, int depth =1 ):Actor( imageID,  x,  y, std, size , depth) {}
    
};

class Sonar :public Goodies
{
public:
    Sonar(int imageID, int x, int y, StudentWorld* std):Goodies(imageID,x,y,std,1,2){m_std= std;setName(IID_SONAR);}
    void doSomething();
private:
    StudentWorld* m_std;
    
};

class waterPool :public Goodies
{
public:
    waterPool(int imageID, int x, int y, StudentWorld* std):Goodies(imageID,x,y,std){m_std= std; setVisible(true);setName(IID_WATER_POOL); }
    void doSomething();
private:
    StudentWorld* m_std;
    
};



class Nugget:public Goodies
{
public:
    Nugget(int imageID, int x, int y, StudentWorld* std):Goodies(imageID,x,y,std,1,2){m_std= std;setName(IID_GOLD); setVisible(false);}
    void doSomething();
private:
    StudentWorld* m_std;
    
};

class OilBarrel :public Goodies
{
public:
    OilBarrel(int imageID, int x, int y, StudentWorld* std):Goodies(imageID,x,y,std,1,2){m_std= std;setName(IID_BARREL); setVisible(false);}
    void doSomething();
private:
    StudentWorld* m_std;
    
};



class GoldDropping :public Goodies
{
public:
    GoldDropping(int imageID, int x, int y, StudentWorld* std):Goodies(imageID,x,y,std){m_std= std;setName(420);}
    void doSomething();
private:
    StudentWorld* m_std;
    
};

class MProtester :public Protester
{
public:
    MProtester(int imageID ,int x, int y, StudentWorld*m_std, int time = 5)
    :Protester(imageID,x,y,m_std,time){this->m_std = m_std; numberOfTicks();setName(IID_PROTESTER);}
   // bool is_facing_frack();
    void changeDirection();
    bool checkPerpendicular();
    void doSomething();
    bool moveInDirection();
    virtual bool howTocatch();
    int isDistance();
    int Level();
    


    
private:
    StudentWorld * m_std;
};



class HProtester :public MProtester
{
public:
    HProtester(int imageID ,int x, int y, StudentWorld*m_std)
    :MProtester(imageID,x,y,m_std,25){this->m_std = m_std;setName(IID_HARD_CORE_PROTESTER);}
    void doSomething();

   bool howTocatch();
//    void HPfunction();
private:
    StudentWorld *m_std;

    
 
};


#endif // ACTOR_H_


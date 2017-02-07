
#include "StudentWorld.h"
#include <string>
#include <math.h>
#include <queue>
#include <sstream>
#include <cmath>
using namespace std;



const int X_ADJUST = VIEW_WIDTH;
const int Y_ADJUST = 60;






GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

// Students:  Add code to this file (if you wish), StudentWorld.h, Actor.h and Actor.cpp






bool StudentWorld::keepYaDistance(int x, int y)
{
    if(xx.size()<=0)
        return true;
    
    list<Actor*>::iterator it;
    it=xx.begin();
    
    while(it!=xx.end())
    {
        int m_x = (*it)->getX();
        int m_y = (*it)->getY();
        
        double z = hypot(m_x-x, m_y-y);
        
        it++;
        
        if(z <= 6)
            return false;
    }
    
    return true;
    

}



 int StudentWorld::move()
{
    
    
    
    
    
    //
    //stepsToReach();
    
    
    if(completedLevel())
        return GWSTATUS_FINISHED_LEVEL;
    
    setGameStatText(print());
    
    if(checkDead())
    {decLives(); playSound(SOUND_PLAYER_GIVE_UP); return GWSTATUS_PLAYER_DIED;}
    
    checkrich();
    
    morgue();
    
    exitAlgorithm();
    
    nextToExit();
    
    
    stepsToReach(Fman->getX(), Fman->getY());
    
    autoalive();
    
    Fman->doSomething();
    
    list <Actor*>::iterator it;
    list <Actor*>::iterator it1;
    
    GenerateSonarAndWater();
    
    
    //addActor(rp);
    //addActor(hp);
    //        autosetVisible()
    
    if(ProtesterTicks <= T)
        ProtesterTicks++;
    else
    {addProtesters();ProtesterTicks=0;}
    
    it= xx.begin();
    
    while(it != xx.end())
    {
        //if((*it)->Imageid()==IID_BOULDER || (*it)->Imageid()== IID_GOLD)   // change this implementation later to make all actors do stf
        
        (*it)->doSomething();
        it++;
    }
    
    
    it = xx.begin();
    while( it != xx.end())
    {
        if((*it)->getDead()== false)
            it1 = xx.erase(it);
        it++;
    }
    
    
    //  exit(1);
    
    
    //decLives();
    return GWSTATUS_CONTINUE_GAME;
}



void StudentWorld::dirtdeleter(int x, int y , char ch)
{
    int z(0);
    int l(0);
    
    if(ch=='l' || ch =='r')
    {
    int yy=y+4;
;
    
        for(int ycor(y);ycor<yy;ycor++)
        {
            if(dirty[x][ycor]==nullptr)
                continue;
            else
  
            {delete dirty[x][ycor]; dirty[x][ycor]=nullptr; add2bp(Blueprint, x, ycor, '*');}
               // dirty[x][ycor]->setVisible(false);
            if(z==0)
                playSound(SOUND_DIG);z++;

        }
    }
    else if(ch == 'u' || ch =='d')
    { int xx=x+4;
    
    for(int xcor(x);xcor<xx;xcor++)
    {
        if(dirty[xcor][y]==nullptr)
            continue;
        else

        {delete dirty[xcor][y]; dirty[xcor][y]=nullptr; add2bp(Blueprint,xcor, y, '*');}
            //dirty[xcor][y]->setVisible(false);
        if(l==0)
            playSound(SOUND_DIG);l++;

          //  playSound(SOUND_DIG);

    }}
    
}


void StudentWorld::Fillexcept()
{
    int count(0);
    
    
    
    for(int x(26);x<34;x++)
        for ( int y(59);y>3;y--)
        {
            coord a(x,y);
            except[count] = &a;  //||||
            count++;
        }
    
    for(int x(0);x<VIEW_WIDTH-1;x++)
        for ( int y(VIEW_HEIGHT);y>59;y--)
        {
            coord a(x,y);
            except[count] = &a;  //||||
            count++;
        }
    
    arraySize = count;
    
}


bool StudentWorld::CheckExcept(int x, int y)
{
    int xx[7] = {27,28,29,30,31,32,33};
    int yy[8] = {64,63,62,61,60,59,58,57};
    
    
    for (int k(0);k<7;k++)
    {
        if ( xx[k] == x)
            return false;
    }
    
    for (int k(0);k<8;k++)
    {
        if ( yy[k] == y)
            return false;
    }
    
    return true; 
}




int StudentWorld::init()
{
    {
        Nprotesters=0;
//        int B  = getLevel()/2 +2;     //(current_level_number / 2 + 2, 6)
//        int G  = (5-getLevel())/2;    //Gold Nuggets in each level,
      // int L  = 2+getLevel(); //Barrels of oil in each level, where: int L = min(2 + current_level_number20)
        int G = max(5-getLevel() / 2, 2);
        int B = min(getLevel() / 2 + 2, 6);
        
        // the follwing few lines are intialising the BluePrint.
        
        for (int x(0);x<VIEW_WIDTH-1;x++)
            for( int y(0);y<VIEW_HEIGHT-1;y++)
            {
                
                //if(!isslottaken(record, x, y))
                dirty[x][y] = nullptr;
            }
       
     
        
        initializeBP();
 
        
        Fman = new Frack(IID_PLAYER,30,50,this);
     //   rp = new MProtester(IID_PROTESTER,60,60,this);
     //   rp ->chooseNsteps();
        
     //   hp = new HProtester(IID_HARD_CORE_PROTESTER, 10, 60, this);
     //   hp->chooseNsteps();
        
        for (int x(0);x<VIEW_WIDTH;x++)
            for( int y(0);y<60;y++)
            {
                
                //if(!isslottaken(record, x, y))
                dirty[x][y] = new Dirt(IID_DIRT,x,y);             }
        
        for(int x(30);x<34;x++)
            for ( int y(63);y>3;y--)
            {
               // dirty[x][y]->setVisible(false);
                delete dirty[x][y];
                dirty[x][y]=nullptr;
            }
        

        Fillexcept();
        int xcor = randInt(0, 59);
        int ycor = randInt(0, 59);
    
        //Goodies* good = new OilBarrel( IID_BARREL, xcor, ycor, this);
        
//        addActor(good);
        
 
        
        //addActor(rp); addActor(hp);

        
        for(int x(0);x<G;x++)
        {
            Actor*acty;
            int xcor = randInt(0, 59);
            int ycor = randInt(0, 59);
            
            if(!keepYaDistance(xcor, ycor)||!CheckExcept(xcor, ycor))
            {
                x--;
                continue;
            }
            
            acty = new Nugget(IID_GOLD,xcor,ycor,this);
            
           // cout << acty->getY() << endl;
            
            xx.push_front(acty);
            //xx.front()->setVisible(true);
        }
        
        int L = min(2 + getLevel(), 20);
        Nboulder=L;
        
        for(int x(0);x<L;x++)
        {
            Actor*acty;
            int xcor = randInt(0, 59);
            int ycor = randInt(0, 59);
            
            if(!keepYaDistance(xcor, ycor)||!CheckExcept(xcor, ycor))
            {
                x--;
                continue;
            }
            
            acty = new OilBarrel(IID_BARREL,xcor,ycor,this);
            
            // cout << acty->getY() << endl;
            
            xx.push_front(acty);
            //xx.front()->setVisible(true);
        }
        
        for(int x(0);x<B;x++)
        {
            Actor*acty;
            int xcor = randInt(0, 59);
            int ycor = randInt(0, 59);
            
            if(!keepYaDistance(xcor, ycor)||!CheckExcept(xcor, ycor))
            {
                x--;
                continue;
            }
            
            clearArea(xcor, ycor);

            acty = new Boulder(IID_BOULDER,xcor,ycor, this);
            
            
            
            xx.push_front(acty);
            xx.front()->setVisible(true);
        }
        
        
        
        
        
        return GWSTATUS_CONTINUE_GAME;
    }

}

bool StudentWorld::checkRange(Actor::Direction dir,int m_x, int m_y)
{
    switch(dir)
    {
        case Actor::up: if(m_y > 63) return false; return true; break;
        case Actor::down: if(m_y < 0) return false; return true; break;
        case Actor::right: if(m_x > 63) return false; return true; break;
        case Actor::left: if(m_x < 0) return false; else return true; break;
        default: return false;
            
    }
    return false;
}



void StudentWorld::clearArea(int x, int y)
{
    int xx=x+4;
    int yy=y+4;
    
    for(int xcor(x);xcor<xx;xcor++)
        for(int ycor(y);ycor<yy;ycor++)
        { delete dirty[xcor][ycor]; dirty[xcor][ycor]=nullptr;}
}

/*
bool StudentWorld::BoulderFall()
{
    list<Actor*>::iterator it;
    
    for(;it!=xx.end();it++)
    {
        if((*it)->Imageid() != IID_BOULDER)
            continue;
        {if((*it)->numberOfTicks()<20)
            (*it)->numberOfTicks(1);
            else
            {
                
            }
        }
    }
}
*/


void StudentWorld::addProtesters()
{
    if(Nprotesters >= P)
        return;
    
    Nprotesters++;
    int probabilityOfHardcore = min(90, getLevel() * 10 + 30);
    
    int probs = randInt(0, 100);
    
    if(probs <= probabilityOfHardcore)
    {
        Actor* acty = new HProtester(IID_HARD_CORE_PROTESTER,60, 60, this);
        addActor(acty);
        return;
    }
    
    Actor* acty = new MProtester(IID_PROTESTER,60, 60, this);
    addActor(acty);
    return; 

    
}


void StudentWorld::autoalive()
{
    list<Actor*>::iterator it;
    it = xx.begin();
    
    while( it != xx.end())
    {
        if( FrackDistance(*(*it)) <= 4)
            (*it)->setVisible(true);
        it++;
    }
}



void StudentWorld::checkifSTONED(Actor& bld)
{
   if(distance(*Fman, bld) <=3)
   { Fman->setannoyPoints(-100); return;}
    
    list <Actor*>::iterator it;
    it = xx.begin();
    
    
    while(it != xx.end())
    {
        if(distance( *(*it) , bld) <= 3 && (*it)->Imageid() != IID_BOULDER)
        {(*it)->setannoyPoints(-100);increaseScore(500);}
        it++;
    }
    
}


bool StudentWorld::BoulderFall(Actor& bld)
{

    int xx = bld.getX()+4;
    

    for( int x(bld.getX());x < xx;x++)
    {
        if(dirty[x][bld.getY()-1] !=nullptr||(bld.getY()-1 < 0))  // dirty holds all the dirt.
        {
            if(bld.numberOfTicks()>=30)
            {if(bld.getDead())
            {bld.setVisible(false);bld.setdead();}}
            else
        return false;
        }    }
    
    while(bld.numberOfTicks() < 30)
    { bld.numberOfTicks(1); return false;}
    
   // bld.numberOfTicks(1);
    if(bld.numberOfTicks()==30)
    {playSound(SOUND_FALLING_ROCK);bld.numberOfTicks(1);}
    
  //  if(bld.getY()-1 < 0)
    //    return true;
    if(bld.getDead())
        
    
     bld.moveTo(bld.getX(), bld.getY()-1);
    checkifSTONED(bld);
    
    bld.row(-1);
    
  //  BoulderFall(bld);
    
    return true;
}

Actor::Direction StudentWorld::frackFace()
{
    return Fman->facing();
}


void StudentWorld:: cleanUp()
{
    delete Fman;
    
    list<Actor*>::iterator it;
    list<Actor*>::iterator it1;

    it = xx.begin();
    
    while( it != xx.end())
    {
        delete (*it);
        it1 = it;
        it++;
        xx.erase(it1);
    }
    
    
    
    for (int x(0);x<64;x++)
        for( int y(0);y<64;y++)
        {
            delete dirty[x][y];
        }
}


int StudentWorld::annoyFman()
{
    Fman->setannoyPoints(-2);
    return Fman->getannoyPoints();
}

StudentWorld::~StudentWorld()
{
    delete Fman;
    
    list<Actor*>::iterator it;
    list<Actor*>::iterator it1;
    
    it = xx.begin();
    
    while( it != xx.end())
    {
        delete (*it);
        it1 = it;
        it++;
        xx.erase(it1);
    }

    for (int x(0);x<64;x++)
        for( int y(0);y<64;y++)
        {
            delete dirty[x][y];
        }

}

bool StudentWorld::facing_each_other(Protester& p)
{
    if(p.facing() == Actor::down &&  Fman->facing() == Actor::up)
        if(p.getY()>= Fman->getY() && p.getX()==Fman->getX())
            return true;
    if(p.facing() == Actor::up &&  Fman->facing() == Actor::down)
        if(p.getY()<= Fman->getY() && p.getX()==Fman->getX())
            return true;
    if(p.facing() == Actor::right &&  Fman->facing() == Actor::left)
        if(p.getX()<= Fman->getX() && p.getY()==Fman->getY())
            return true;
    if(p.facing() == Actor::left &&  Fman->facing() == Actor::right)
        if(p.getX()>= Fman->getX() && p.getY()==Fman->getY())
            return true;
    return false;
}

bool StudentWorld::frackfacing(Protester & p)
{
        if(p.getY()>= Fman->getY() && p.getX()==Fman->getX())
            return true;
        if(p.getY()<= Fman->getY() && p.getX()==Fman->getX())
            return true;
        if(p.getX()<= Fman->getX() && p.getY()==Fman->getY())
            return true;
        if(p.getX()>= Fman->getX() && p.getY()==Fman->getY())
            return true;
    return false;
}


int StudentWorld::FrackDistance(Actor &p)
{
    return distance(p, *Fman);
}

int StudentWorld::distance(Actor& p, Actor& q)
{
    int m_r = q.getX();
    int m_row = p.getX();
    
    int m_c = q.getY();
    int m_col = p.getY();
 
   // int z = sqrt(pow(m_r-m_row, 2)+pow(m_c-m_col, 2));
    
    int z= hypot(m_r-m_row, m_c-m_col);
    
    return z;
    
}

bool StudentWorld::isInStraightLine ( Actor& p)
{
    if( Fman->getY()!=p.getY() && Fman->getX()!=p.getX())
        return false;
    
    if(Fman->getX()==p.getX())
    {
        if(Fman->getY() > p.getY())
        {
            int xx = Fman->getX()+3;
            for (int x(p.getX());x< xx;x++)
                for(int y(p.getY());y<Fman->getY();y++)
                {
                    if(dirty[x][y] != nullptr)
                        return false;
                }
            return true;
        }
        
        
        if(Fman->getY() < p.getY())
        {
          //  cout << p.getY() << endl;
            int xx = Fman->getX()+3;
            for (int x(Fman->getX());x< xx;x++)
                for(int y(Fman->getY());y<p.getY();y++)
                {
                    if(dirty[x][y] != nullptr)
                        return false;
                }
            return true;
        }
    }
    
    else
        
        if(Fman->getY() == p.getY())
        {
            if(Fman->getX() < p.getX())
            {
                int xx = Fman->getY()+3;
                
                for (int x(Fman->getX());x<p.getX();x++)
                    for(int y(Fman->getY());y < xx;y++)
                    {
                        if(dirty[x][y] != nullptr)
                            return false;
                    }
                return true;
            }
            
            
            if(Fman->getX() > p.getX())
            {
                int xx = Fman->getY()+3;
                
                for (int x(p.getX());x<Fman->getX();x++)
                    for(int y(Fman->getY());y < xx;y++)
                    {
                        if(dirty[x][y] != nullptr)
                            return false;
                    }
                return true;
            }
        }
    return false;
}



void StudentWorld::changeDirectionFace(Actor& p)
{
    if(p.getX()>Fman->getX())
    { p.setDirection(Actor::left); p.moveTo(p.getX()-1, p.getY());}
    else
        if(p.getX()<Fman->getX())
        {p.setDirection(Actor::right); p.moveTo(p.getX()+1, p.getY());}
    else
        if(p.getY()>Fman->getY())
        { p.setDirection(Actor::down); p.moveTo(p.getX(), p.getY()-1);}
    else
        if(p.getY()<Fman->getY())
        { p.setDirection(Actor::up); p.moveTo(p.getX(), p.getY()+1);}
}




bool StudentWorld::check_around_dirt(Protester& p, Actor::Direction dir)
{
    
    if(!p.checkrange(dir, p.getX(), p.getY()))
        return false;

    switch (dir)
    {

               case Actor::up:
               if(checkarea(p.getX(), p.getY()+4,  dir))
                   return true;break;
               
               case Actor::down:
               if(checkarea(p.getX(), p.getY()-1,  dir))
                   return true;break;

            
                case Actor::right:
                   if(checkarea(p.getX()+4, p.getY(),  dir))
                       return true;break;


                case Actor::left:
                      if(checkarea(p.getX()-1, p.getY(), dir))
                          return true;break;

        default:
                  return false;
        
    
    }
    return false; 
}

bool StudentWorld::checkarea(int x , int y, Actor::Direction dir )
{
    int xx = x+4;
    int yy = y+4;
    
    if(dir == Actor::up || dir == Actor::down)
    for(;x<xx;x++)
        {
            if(dirty[x][y]!=nullptr)
                return false;
        }
    
    if(dir == Actor::left || dir == Actor::right)
        for(;y<yy;y++)
        {
            if(dirty[x][y]!=nullptr)
                return false;
        }
    if(dir == Actor::none)
        for(;y<yy;y++)
        for(;x<xx;x++)
        {
            if(dirty[x][y]!=nullptr)
                return false;
        }
    
    return true;

}

bool StudentWorld::checkBlueprint(int x, int y, Actor::Direction dir)
{
    int xx = x+4;
    int yy = y+4;
    
    if(!checkRange(dir, x, y))
        return false;
    
    if(dir == Actor::up || dir == Actor::down)
        for(;x<xx;x++)
        {
            if(checkBP(Blueprint,x, y, '.'))
                return false;
        }
    
    if(dir == Actor::left || dir == Actor::right)
        for(;y<yy;y++)
        {
            if(checkBP(Blueprint,x, y, '.'))
                return false;
        }
    
    return true;
}


void StudentWorld::initializeBP()
{
    for (int x(0);x<VIEW_WIDTH-1;x++)
        for( int y(0);y<VIEW_HEIGHT-1;y++)
        {
            
            //if(!isslottaken(record, x, y))
            dirty[x][y] = nullptr;
        }
    
    
    for (int x(0);x<VIEW_WIDTH;x++)
        for( int y(0);y<64;y++)
        {    add2bp(Blueprint, x, y, '.');}
    
    for (int x(0);x<VIEW_WIDTH;x++)
        for( int y(0);y<4;y++)
        {    Blueprint[x][y] = '*';}
    
    for(int x(30);x<34;x++)
        for ( int y(63);y>3;y--)
        {
            // dirty[x][y]->setVisible(false);
            // delete dirty[x][y];
            add2bp(Blueprint, x, y, '*');
        }
}


void StudentWorld::stepsToReach(int sr, int sc)
{
    
    char BPCopy[64][64];
    
    for(int y(0);y<64;y++)
        for (int x(0);x<64;x++)
        {
            BPCopy[x][y] = Blueprint[x][y];
        }
   // BPCopy[60][3] = 'P';

    
    class Coord
    {
    public:
        Coord(int rr, int cc, int count) : m_r(rr), m_c(cc){this->m_count = count;}
        int r() const { return m_r; }
        int c() const { return m_c; }
        void setCount(int x){m_count += x;}
        int getCount() {return m_count;}
        void Setdir(Actor::Direction x){m_dir = x;}
        Actor::Direction getDir(){return m_dir;}
    private:
        int m_r;
        int m_c;
        int m_count;
        Actor::Direction m_dir;
    };
    
    
    list<Actor*>::iterator it;
    it = xx.begin();
    
    while(it != xx.end())
    {
      if((*it)->getName() == IID_HARD_CORE_PROTESTER || (*it)->getName() == IID_PROTESTER)
      {
          add2bp(BPCopy, (*it)->getX(), (*it)->getY(), 'P');
          
      }
        it++;
    }
    

    //exit(1);
    
//    sr = Fman ->getX();  sc = Fman->getY();
    
    
    
    queue<Coord> myQ;
    
    Coord z(sr, sc, 0);
    
    myQ.push(z);
    
    add2bp(BPCopy, sr, sc, '@');
    
    
    
    for(;myQ.size()!=0;)
    {
        
      //  cout << myQ.size() << endl ;
        Coord x = myQ.front();
        myQ.pop();
        
//        if(myQ.size()==0)
//            cout << "";
            // input code about hw u plan to change the private memeber next coord in Hardcore protestetds
            
        if( !checkBP(BPCopy,x.r()-1, x.c(), '@') && checkBlueprint(x.r()-1 , x.c(), Actor::left))
        {
            if(checkBP(BPCopy, x.r()-1, x.c(), 'P'))
            {
                StoreRobot(x.r(), x.c(), x.getCount(), x.r()-1, x.c(), Actor::right);
            }
            
            myQ.push(Coord(x.r()-1,x.c(),x.getCount()+1));add2bp(BPCopy,x.r()-1, x.c() , '@'); x.Setdir(Actor::left);

        }
        
        if( !checkBP(BPCopy,x.r()+1, x.c(), '@') && checkBlueprint(x.r()+4 ,x.c(), Actor::right))
        {
            if(checkBP(BPCopy, x.r()+1, x.c(), 'P'))
            {
                StoreRobot(x.r(), x.c(), x.getCount(),x.r()+1, x.c(),Actor::left);
            }
            myQ.push(Coord(x.r()+1,x.c(),x.getCount()+1));add2bp(BPCopy,x.r()+1, x.c(), '@'); x.Setdir(Actor::right);
        
        }
        
        if( !checkBP(BPCopy,x.r(), x.c()+1, '@') && checkBlueprint(x.r() , x.c()+4, Actor::up))
        {
            if(checkBP(BPCopy, x.r(), x.c()+1, 'P'))
            {
                StoreRobot(x.r(), x.c(), x.getCount(), x.r(), x.c()+1,Actor::down);
            }
            
            myQ.push(Coord(x.r(),x.c()+1,x.getCount()+1));add2bp(BPCopy,x.r(), x.c()+1, '@'); x.Setdir(Actor::up);
        }
        
        
        if( !checkBP(BPCopy,x.r(), x.c()-1, '@') && checkBlueprint(x.r() , x.c()-1, Actor::down))
        {
            if(checkBP(BPCopy, x.r(), x.c()-1, 'P'))
            {
                StoreRobot(x.r(), x.c(), x.getCount(), x.r(), x.c()-1,Actor::up);
            }
            
            myQ.push(Coord(x.r(),x.c()-1,x.getCount()+1));add2bp(BPCopy,x.r(), x.c()-1, '@'); x.Setdir(Actor::down);
        }
        
//        for(int y(0);y< 64;y++)
//        {for( int x(0);x<64;x++)
//                cout << BPCopy[x][y];
//            cout << endl;}
    
    }

    
}


void StudentWorld::nextToExit()
{
    list<Actor*>::iterator it;
    it = xx.begin();
    
    while(it != xx.end())
    {
        if((*it)->getName()==IID_PROTESTER ||(*it)->getName()==IID_HARD_CORE_PROTESTER)
        {
            (*it)->setExitX((*it)->getNextX());
            (*it)->setExitY((*it)->getNextY());
            (*it)->setExitDir((*it)->getNextDir());
            
            //(*it)->setNextX(-1);
            //(*it)->setNextY(-1);

        }
        it++;

    }
    
}


void StudentWorld::morgue()
{
    list<Actor*>::iterator it;
    it = xx.begin();
    
    while( it != xx.end())
    {
        if((*it)->is_leave_field() && (*it)->getX() == 60 && (*it)->getY() == 60)
        {
            (*it)->setdead(); (*it)->setVisible(false); 
        }
        it++;
    }
    
    
}

void StudentWorld::StoreRobot(int x, int y, int c, int xcor, int ycor, Actor::Direction dir)
{
    list<Actor*>::iterator it;
    
    it = xx.begin();
    
    while ( it != xx.end())
    {
        if((*it)->getID()== IID_HARD_CORE_PROTESTER || (*it)->getID() == IID_PROTESTER)
           if((*it)->getX() == xcor &&(*it)->getY() == ycor)
        {
            if((*it)->getX()== 60 && (*it)->getY()==60)
            {}
            
            
            (*it)->setNextX(x); (*it)->setNextY(y); (*it)->setNsteps(c);(*it)->setNextDir(dir); }
        it++;
    }
    
}
    
    
    
    /*
    char BPCopy[64][64];
    
    for(int y(0);y<64;y++)
        for (int x(0);x<64;x++)
        {
            BPCopy[x][y] = Blueprint[x][y];
        }
    
    class Coord
    {
    public:
        Coord(int rr, int cc, int count) : m_r(rr), m_c(cc){this->m_count = count;}
        int r() const { return m_r; }
        int c() const { return m_c; }
        void setCount(int x){m_count += x;}
        int getCount() {return m_count;}
        void Setdir(Actor::Direction x){m_dir = x;}
        Actor::Direction getDir(){return m_dir;}
    private:
        int m_r;
        int m_c;
        int m_count;
        Actor::Direction m_dir;
    };

    int sr,sc,er,ec;
    
    sr = p.getX(); sc = p.getY(); er = Fman->getX(); ec = Fman->getY();
    
    queue<Coord>(cord);
    
   // if(maze[sr][sc]=='X' || maze[er][ec]=='X')
    //    return false;
   // if(sr>nRows-1||sc>nCols-1||er>nRows-1||ec>nCols-1)
    //    return false;
    

    Coord yy(sr,sc,0);
    cord.push(yy);
    add2bp(BPCopy, sr, sc, '@');
    //int count(0);
    
    Coord x = cord.front();

    while(x.getCount() < M)
    {
         x = cord.front();
        cord.pop();

        if(x.r()==er && x.c()==ec)
        {return x.getDir();}
        
        
        if( !checkBP(BPCopy,x.r()-1, x.c(), '@') && checkBlueprint(x.r()-1 , x.c(), Actor::left))
            { cord.push(Coord(x.r()-1,x.c(),x.getCount()+1));add2bp(BPCopy,x.r()-1, x.c() , '@'); x.Setdir(Actor::left);}
        
        if( !checkBP(BPCopy,x.r()+1, x.c(), '@') && checkBlueprint(x.r()+4 ,x.c(), Actor::right))
            { cord.push(Coord(x.r()+1,x.c(),x.getCount()+1));add2bp(BPCopy,x.r()+1, x.c(), '@'); x.Setdir(Actor::right);}

        if( !checkBP(BPCopy,x.r(), x.c()+1, '@') && checkBlueprint(x.r() , x.c()+4, Actor::up))
        { cord.push(Coord(x.r(),x.c()-1,x.getCount()+1));add2bp(BPCopy,x.r(), x.c()+1, '@'); x.Setdir(Actor::up);}
        
        if( !checkBP(BPCopy,x.r(), x.c()-1, '@') && checkBlueprint(x.r() , x.c()-1, Actor::down))
        { cord.push(Coord(x.r(),x.c()+1,x.getCount()+1));add2bp(BPCopy,x.r(), x.c()-1, '@'); x.Setdir(Actor::down);}
        
     //   count++;
        for( int y(0); y<64;y++)
        {for ( int x(0); x<64;x++)
            cout << BPCopy [x][y];
            cout << endl;}
     
     
        
    }
    

   // initializeBP();
    return Actor::none;
     */



void StudentWorld::addActor(Actor *x)
{
    xx.push_front(x);
}


void StudentWorld::Sonarstuff()
{
    
    list<Actor*>::iterator it;
    list<Actor*>::iterator it1;
    
    list<Actor*> xy;
    
    it = xx.begin();
    it1 = xy.begin();

    
    Fman->Sonarticks(1);
    
    while( it != xx.end())
    {
        if(FrackDistance(*(*it)) <= 12)
        {
            xy.push_front(*it);
        }
        it++;
    }
    
    it1 = xy.begin();
    
    while(it1 != xy.end())
    {
        (*it1)->setVisible(true);
        it1++;
        
    }

    
    
}


 bool StudentWorld::completedLevel()
{
    list<Actor*>::iterator it;
    it = xx.begin();
    
    int count(0);
    
    while(it != xx.end())
    {
        if((*it)->getName() == IID_BARREL) count++;
        it++;
    }
    
    return count<=0;
}


bool StudentWorld::checkDead()
{
    if(Fman->getannoyPoints() <= 0)
        return true;
    
    list<Actor*>::iterator it;
    
    it = xx.begin();
    
    while(it != xx.end())
    {
        if( (*it)->getName() == IID_HARD_CORE_PROTESTER || (*it)->getName() == IID_PROTESTER)
        if((*it)->getannoyPoints() <= 0)
            {
                if((*it)->giveupsound()==0)
                { (*it)->set_leave_field(); playSound(SOUND_PROTESTER_GIVE_UP);(*it)->giveupsound(1);Nprotesters--;
                
                if((*it)->getName() == IID_HARD_CORE_PROTESTER )//|| (*it)->getName() == IID_PROTESTER
                    increaseScore(250);
                    else
                        increaseScore(100);
                
                }
            }
        it++;
    }
    return false;
}







void StudentWorld::SquirtDosomethig(int x, int y, Actor::Direction dur)
{
    if(!checkRange(dur, x, y))
       {return;}
    if(!checkarea(x, y, dur))
        return;
    
    playSound(SOUND_PLAYER_SQUIRT);
    
    Fman->SQvisible();
    
    switch (dur)
    {
        case Actor::up: Fman->moveSquirt(x, y+1);break;
        case Actor::down: Fman->moveSquirt(x, y-1);break;
        case Actor::left: Fman->moveSquirt(x-1, y);break;
        case Actor::right: Fman->moveSquirt(x+1, y);break;
            
            default: break;

    }

}


void StudentWorld::nuggetAround(Goodies& act)
{
    if(FrackDistance(act) <=3 )
    { act.setVisible(false); act.setdead();
        
        switch (act.getName())
        {
            case IID_WATER_POOL:
                Fman->Nwaterpools(5);  increaseScore(100);      playSound(SOUND_GOT_GOODIE);

                break;
            case IID_GOLD:  increaseScore(10);
                Fman->nuggetCount(1);        playSound(SOUND_GOT_GOODIE);

                break;

            case IID_SONAR:
                Fman->Nsonars(2);        playSound(SOUND_GOT_GOODIE);
increaseScore(75);
                break;

            case IID_BARREL:
                Fman->barrels(1);        playSound(SOUND_FOUND_OIL); increaseScore(1000);
increaseScore(1000);
                break;

                
                
        }
        
        }
   // cout << Fman->nuggetCount();
}


void StudentWorld::exitAlgorithm()
{
    stepsToReach(60, 60);

}


void StudentWorld::goldpick(Goodies &good)
{
    list<Actor*>::iterator it;
    it = xx.begin();
    
    while(it!= xx.end())
    {
        if((*it)->getName() == IID_HARD_CORE_PROTESTER || (*it)->getName()== IID_PROTESTER)
        {
            if(distance(good, (*(*it))) <= 3)
            {
                (*it)->setGold();
                playSound(SOUND_PROTESTER_FOUND_GOLD);
                good.setVisible(false); good.setdead();
            }
        }
        it++;
    }
}


void StudentWorld::checkrich()
{
    list<Actor*>::iterator it;
    it = xx.begin();
    
    int  ticks_to_stare = min(50, 100 - getLevel() * 10);
    
    while(it != xx.end())
    {
        if( (*it)->getName() == IID_PROTESTER && (*it)->hasGold())
        {
            (*it)->set_leave_field();
            (*it)->setGold(false);
            increaseScore(25);

        }
        
        if( (*it)->getName() == IID_HARD_CORE_PROTESTER  && (*it)->hasGold())
        {
//            if((*it)->get2incr()== true)
           (*it)->tickwait(ticks_to_stare);
            (*it)->setGold(false);
            increaseScore(50);

//            cout << (*it)->tickwait() << "base ticks to spare" << endl;
            
//            (*it)->set2increment();
        }
        it++;
    }
}


string StudentWorld::print()
{
//“Scr: 0321000 Lvl: 52 Lives: 3 Hlth: 80% Water: 20 Gld: 3 Sonar: 1 Oil Left: 2”
    string a = "Scr: ";
    string b = streamhelper(getScore());
    string c = " Lvl: ";
    string d = streamhelper(getLevel());
    string e = " Lives: ";
    string f= streamhelper(getLives());
    string g=" Hlth: ";
    string h = streamhelper(Fman->getannoyPoints()*10);
    string i = "% Water: ";
    string j = streamhelper(Fman->Nwaterpools());
    string k = " Gld: ";
    string l = streamhelper(Fman->nuggetCount());
    string m=  " Sonar: ";
    string n=  streamhelper(Fman->Nsonars());
    string o= " Oil Left: ";
    string p = streamhelper(Fman->barrels());
    
    string dad = a+b+c+d+e+f+g+h+i+j+k+l+m+n+o+p;
    
    return dad;
}


string StudentWorld::streamhelper(int x)
{
           // number to be converted to a string
    
    string Result;          // string which will contain the result
    
    ostringstream convert;   // stream used for the conversion
    
    convert << x;      // insert the textual representation of 'Number' in the characters in the stream
    
    Result = convert.str();
    
    return Result;
}


void StudentWorld::GenerateSonarAndWater()
{
    int G = (getLevel() * 25) + 300;
    
    int x= randInt(0, G);
    
    if( x==200)
    {
       int y = randInt(0, 4);
        
        Goodies * god;
        
        if(y==1)
        {
            god = new Sonar(IID_SONAR,0,60,this); addActor(god);return;
        }
    
        int xxcor ;
        int yycor ;
        
        while(true)
        {
            
            xxcor = randInt(0, 59);
            yycor = randInt(0, 59);
            if(checkarea(xxcor, yycor, Actor::none))
                break;
        }
        
         god = new waterPool( IID_WATER_POOL, xxcor, yycor, this);
        
        addActor(god);
        
            
    }
}

int StudentWorld::sonarCount(int x = 0)
{
    return Fman->Nsonars(x);
}



bool StudentWorld::protestersannoyed(Actor & act)
{
    list<Actor*>::iterator it;
    it = xx.begin();
    
    int N = min(50, 100 - getLevel() * 10);
    
    for(;it!=xx.end();it++)
    {
     
        if((*it)->getName()== IID_HARD_CORE_PROTESTER || (*it)->getName() == IID_PROTESTER)
      {
          if (distance(act, *(*it)) <= 3)
          {(*it)->setannoyPoints(-2);
              playSound(SOUND_PROTESTER_ANNOYED);
              (*it)->tickwait(N);
              
//              cout << "protester annoyed" <<  (*it)->tickwait(N) << endl;
         // cout << (*it)->getannoyPoints() <<endl;
              return true;}
      }
    }
    return false;
}



//4245272455//




int max( int x, int y)
{
  if(x>y)
      return x;
    return y;
}

int min( int x, int y)
{
    if(x<y)
        return x;
    return y;
}




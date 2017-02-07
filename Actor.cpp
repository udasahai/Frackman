  #include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp
int randInt(int min, int max)
{
    if (max < min)
        swap(max, min);
    static random_device rd;
    static mt19937 generator(rd());
    uniform_int_distribution<> distro(min, max);
    return distro(generator);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////    ACTOR   BOULDER   FRACK  IMPLEMENTATIONS        //////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////


bool Actor::checkrange(Direction dir,int m_x, int m_y)

{
    switch(dir)
    {
        case Actor::up: if(m_y+1 > 60) return false; return true; break;
        case Actor::down: if(m_y-1 < 0) return false; return true; break;
        case Actor::right: if(m_x+1 > 60) return false; return true; break;
        case Actor::left: if(m_x-1 < 0) return false; else return true; break;
        default: return false;

    }
    return false;
}

void Boulder::doSomething()
{
     m_std->BoulderFall(*this);
}



void Frack::dirtDirection(char x)
{
    
    switch (x)
    {
        case 'r':
            m_std->dirtdeleter(getX()+3, getY(),x);break;
        case 'l':
            m_std->dirtdeleter(getX(), getY(),x);break;
        case 'u':
            m_std->dirtdeleter(getX(), getY()+3,x);break;
        case 'd':
            m_std->dirtdeleter(getX(), getY(),x);break;
            
    }
}


void Frack::doSomething()
{
    int key ; m_std->getKey(key);

        switch (key) {
                
            case KEY_PRESS_LEFT:

                if(getDirection()!=left)
                    
                {setDirection(left);break;}
                if(!checkrange(left, getX(), getY()))
                {moveTo(getX(), getY());
                    break;
                }
                moveTo(getX()-1, getY());
                col(-1);
                dirtDirection('l');
                break;
                
                
            case KEY_PRESS_ESCAPE:
                setannoyPoints(-101);
                break;
                
                
            case KEY_PRESS_RIGHT:
                if(getDirection()!=right)
                {setDirection(right);break;}
                if(!checkrange(right, getX(), getY()))
                {moveTo(getX(), getY());
                    break;
                }
                this->moveTo(this->getX()+1, this->getY());
                col(1);
                dirtDirection('r');
                break;
                
            case KEY_PRESS_UP:
       
                if(getDirection()!=up)
                {setDirection(up);break;}
                if(!checkrange(up, getX(), getY()))
                {moveTo(getX(), getY());
                    break;
                }
                this->moveTo(this->getX(), this->getY()+1);
                row(1);
                dirtDirection('u');
                break;
                
                
            case KEY_PRESS_DOWN:

                if(getDirection()!=down)
                {setDirection(down);break;}
                if(!checkrange(down, getX(), getY()))
                {
                    moveTo(getX(), getY());
                    break;
                }
                this->moveTo(this->getX(), this->getY()-1);
                row(-1);
                dirtDirection('d');
                break;
                
                
            case KEY_PRESS_TAB:
                if( m_nuggetCount <=0)
                    break;
                gild = new GoldDropping(IID_GOLD, getX(), getY(),m_std);
                m_std->addActor(gild);
                m_nuggetCount--;
                break;
                
                
            case KEY_PRESS_SPACE:
                if(m_waterpool <= 0)
                    break;
                manageSquirt();
                m_waterpool--;
                break;
                
            case 'Z':
            case 'z':
                if(Nsonars() <= 0)
                    break;
                m_std->playSound(SOUND_SONAR);
                m_std->Sonarstuff();
                Nsonars(-1);
                break;
                
                
            default:
                break;
                
            
        
}

}



void Frack::manageSquirt()
{
    //turnON = true;
    Direction z = getDirection();
    
    switch(z)
    {
        case up: m_ssd = new Squirt(IID_WATER_SPURT,getX(), getY()+4,z, m_std); m_std-> SquirtDosomethig(getX(), getY()+4, z); break;
            
        case down: m_ssd = new Squirt(IID_WATER_SPURT,getX(), getY()-1,z,m_std); m_std-> SquirtDosomethig(getX(), getY()-1, z); break;
        case right: m_ssd = new Squirt(IID_WATER_SPURT,getX()+4, getY(),z,m_std); m_std-> SquirtDosomethig(getX()+4, getY(), z); break;
        case left: m_ssd = new Squirt(IID_WATER_SPURT,getX()-1, getY(),z,m_std); m_std-> SquirtDosomethig(getX()-1, getY(), z); break;
            
        default:break;
    }
    
    m_std->addActor(m_ssd);
    
}


void Frack::moveSquirt(int x, int y)
{
    m_ssd->moveTo(x, y);
    
}

void Frack::SQvisible()
{m_ssd->setVisible(true);}



////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////    MPROTESTERS         IMPLEMENTATIONS             //////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////


bool MProtester::howTocatch()
{
    if(is_leave_field())
    {
        //        setDirection(getNextDir());
        //        moveTo(getNextX(), getNextY());
        //        setNextX(-1);
        
        setDirection(getExitDir());
        moveTo(getExitX(), getExitY());
        setExitX(-1);
        return true;
    }
    
    if(m_std->isInStraightLine(*this)&& m_std->FrackDistance(*this) >4)
    {
        m_std->changeDirectionFace(*this);
        setStepsZero();
        return true;
    }
    return false;
}

int MProtester::Level(){ return m_std->getLevel();}


bool MProtester::checkPerpendicular()
{
    int count(0);
    
    if(m_std->check_around_dirt(*this, up)) count++;
    if(m_std->check_around_dirt(*this, down)) count++;
    if(m_std->check_around_dirt(*this, left)) count++;
    if(m_std->check_around_dirt(*this, right)) count++;

    
    return count >= 3;
}


void MProtester::changeDirection()
{
    int x = randInt(0, 3);
    Actor::Direction dur=none;
    switch (x)
    {
        case 0: dur=up;break;
        case 1: dur=down;break;
        case 2: dur=left;break;
        case 3: dur=right;break;
    }
    
    if(m_std->check_around_dirt(*this,dur))
    {setDirection(dur);return;}
    else
        changeDirection();
}




bool MProtester::moveInDirection()
{
    
    Direction x = getDirection();
    
    if(!checkrange(x, getX(), getY())) //|| !m_std->check_around_dirt(*this, facing()))
    { setStepsZero(); return false;}

    
        if(!m_std->check_around_dirt(*this, getDirection()))
    { setStepsZero(); return false;}
    
    
    
    switch (x)
    {
        case up: moveTo(getX(), getY()+1);return true;break;
        case down: moveTo(getX(), getY()-1);return true;break;
        case left: moveTo(getX()-1, getY());return true;break;
        case right: moveTo(getX()+1, getY());return true;break;
            
        default: return false;

    }
}




void MProtester::doSomething()
{
    //int N = min(50, 100 - m_std->getLevel() * 10);

    if( getDead() == false)
        return;
    int ticktock = max(0,3- (m_std->getLevel()/4));
//    cout << tickwait() << "dosomething" <<endl ;
    if(numberOfTicks() < ticktock +getTickwait())
    { numberOfTicks(1); return;}
    else
        numberOfTicks(-10); tickwait(-10); //set2increment(true);
    if(is_leave_field())
    {
        //execute the leaving the feild bullshit here please. Hell yeah it will be hard.
    }
    
    PerpTurn(1);
   // cout <<PerpTurn();
    shoutTick(1);

    
    if (m_std->FrackDistance(*this) <= 4)
        if( m_std->frackfacing(*this))
    {
        if(shoutTick(0) >= 15)
        {
            m_std->playSound(SOUND_PROTESTER_YELL);
            setnull();
            m_std->annoyFman();
            return;
        }
    }
    

   // HPfunction();
    
 if(howTocatch())
     return;

    
    
    //setStepsZero();
    
    numberOfSteps(-1);
    
    if(numberOfSteps() <= 0)
        changeDirection();
    
    chooseNsteps();// this is inline.
    
   // cout << PerpTurn() << endl;
   if(checkPerpendicular() && PerpTurn() > 70 )//&& PerpTurn()>200)
   {
       changeDirection();
       chooseNsteps();
       PerpTurn(-50);
   }
    
    moveInDirection();
    
    //if(!moveInDirection())
     //   setStepsZero();
 
}

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////    HPROTESTERS         IMPLEMENTATIONS             //////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////




void HProtester::doSomething()
{
   MProtester::doSomething();

}

 bool HProtester::howTocatch()
{
    
    if(is_leave_field())
    {
//        setDirection(getNextDir());
//        moveTo(getNextX(), getNextY());
//        setNextX(-1);
        
        setDirection(getExitDir());
        moveTo(getExitX(), getExitY());
        setExitX(-1);
        return true;
    }
    
    
    bool y  = true;
    
    
  //  m_std->stepsToReach();
    
   // HPfunction();
    
    int M = 16 + (m_std->getLevel()*2);
    //M = 55;
    
   // cout << getNSteps() << endl;
    if(M > getNSteps()) //&& getNSteps() != -1)
    {
        setDirection(getNextDir());
        moveTo(getNextX(), getNextY());
        setNextX(-1);
    }
    else
        y = MProtester::howTocatch();
    return y;
}





////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////    SQUIRT         IMPLEMENTATIONS             //////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

StudentWorld* Actor::getWorld()
{
    return m_std;
}


void Squirt::doSomething()
{
    if(getWorld()->protestersannoyed(*this))
    {
        cout << getDead();
        setVisible(false);
        setdead();
        return;
    }
    
    numberOfTicks(1);
    if(numberOfTicks() >= 4
       )
    {
        setVisible(false); setdead();
    }
    else
        getWorld()->SquirtDosomethig(getX(), getY(), getDirection());
    
}



void Sonar::doSomething()
{
    getWorld()->nuggetAround(*this);
    int T = min(100, 300 - 10*m_std->getLevel());
    
    numberOfTicks(1);
    if(numberOfTicks() >= T)
    {  setVisible(false); setdead();}
}


void Nugget::doSomething()
{
   m_std->nuggetAround(*this);
}


void GoldDropping::doSomething()
{
    
    m_std->goldpick(*this);
    numberOfTicks(1);
    
    if(numberOfTicks() >= 30)
    {  setVisible(false); setdead();}
    
}

void waterPool::doSomething()
{
    m_std->nuggetAround(*this);
    numberOfTicks(1);
    int T = min(100, 300 - 10*m_std->getLevel());
    
    if(numberOfTicks() >= T)
    {  setVisible(false); setdead();}
}


void OilBarrel::doSomething()
{
    m_std->nuggetAround(*this);
}





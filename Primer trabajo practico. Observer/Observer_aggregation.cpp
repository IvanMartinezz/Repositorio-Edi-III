#include <sstream>
#define TO_STRING( x ) dynamic_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()

#include <iostream>
#include <list>
#include <string>

using namespace std;

/**********************************OBSERVER INTERFACE************************************/
class Subject;
class Observer
{
    public:
        virtual ~Observer(){};
        virtual void Update(Subject* theChangedSubject) = 0;
    protected:
        Observer(){};
};

/*********************************SUBJECT ABSTRACT CLASS**********************************/
class Subject
{
    public:
    	Subject(){};
        virtual ~Subject(){}
        virtual void Attach(Observer*) = 0;
        virtual void Detach(Observer*) = 0;
        virtual void Notify() = 0;
        
};

/*********************************SUBJECT CONCRETE CLASS**********************************/

class ConcreteSubject : public Subject 
{
	public:
		ConcreteSubject(){};
         ~ConcreteSubject(){}
         void Attach(Observer*);
         void Detach(Observer*);
         void Notify();
    
    private:
    	list<Observer*> m_observers;
        
};
		
void ConcreteSubject::Attach (Observer* o)
{
    m_observers.push_front(o);
}

void ConcreteSubject::Detach (Observer* o)
{
    m_observers.remove(o);
}

void ConcreteSubject::Notify ()
{
    list<Observer*>::iterator it;

    for (it =  m_observers.begin() ; it !=  m_observers.end(); ++it)
    {
       (*it)->Update(this);
    }
}		

/*********************************CONCRET CLOCK TIMER************************************/

class ClockTimer
{
    public:
        ClockTimer(Subject* subject);
        ~ClockTimer(){ delete m_subject; }
        virtual int GetHour();
        virtual int GetMinute();
        virtual int GetSecond();
        void Tick();
    private:
        int m_hours;
        int m_minutes;
        int m_seconds;
        Subject* m_subject;
};

ClockTimer::ClockTimer(Subject* subject)
{
        m_hours = 0;
        m_minutes = 0;
        m_seconds = 0;
        m_subject = subject;
}

int ClockTimer::GetHour( void )
{
    return this->m_hours;
}

int ClockTimer::GetMinute( void )
{
    return this->m_minutes;
}

int ClockTimer::GetSecond( void )
{
    return this->m_seconds;
}

void ClockTimer::Tick ()
{
    // No update internal time-keeping state, only a demo.
    // ...
    m_seconds++;
    if(m_seconds == 60)
    {
        m_seconds = 0;
        m_minutes++;
        if(m_minutes == 60)
        {
            m_seconds = 0;
            m_minutes = 0;
            m_hours++;
            if(m_hours == 24)
            {
                m_seconds = 0;
                m_minutes = 0;
                m_hours = 0;
            }
        }
    }
    m_subject->Notify();
}

/****************************************WIDGET INTERFACE********************************/
class Widget
{
    public:
        virtual ~Widget() {}
        virtual void Draw() = 0;
};


/****************************************CONCRETE DIGITAL CLOCK********************************/

class DigitalClock: public Widget, public Observer
{
    public:
        DigitalClock(ClockTimer* timer, Subject* subject);
        virtual ~DigitalClock();
        virtual void Update(Subject*);
        // overrides Observer operation
        virtual void Draw();
        // overrides Widget operation;
        // defines how to draw the digital clock

    private:
        ClockTimer* m_timer;
        Subject* m_subject;
};

DigitalClock::DigitalClock(ClockTimer* timer, Subject* subject)
{
	m_timer = timer;
    m_subject = subject;
    subject->Attach(this);
}

DigitalClock::~DigitalClock ()
{
    m_subject->Detach(this);
}

void DigitalClock::Update (Subject* theChangedSubject)
{
    if (theChangedSubject == m_subject)
    {
        Draw();
    }
}

void DigitalClock::Draw ()
{
    // get the new values from the subject
    string hours = TO_STRING(m_timer->GetHour());
    string minutes = TO_STRING(m_timer->GetMinute());
    string seconds = TO_STRING(m_timer->GetSecond());

    // draw the digital clock
    if(hours.size() == 1){hours = "0"+hours;}
    if(minutes.size() == 1){minutes = "0"+minutes;}
    if(seconds.size() == 1){seconds = "0"+seconds;}

    cout <<"I am Digital: "<< hours<<":"<<minutes<<":"<<seconds<<endl;
}


/****************************************CONCRETE ANALOG CLOCK***********************************/

class AnalogClock: public Widget, public Observer
{
    public:
        AnalogClock(ClockTimer* timer, Subject* subject);
        virtual ~AnalogClock();

        // overrides Observer operation
        virtual void Update(Subject*);

        // overrides Widget operation;
        // defines how to draw the digital clock
        virtual void Draw();

    private:
        ClockTimer* m_timer;
        Subject* m_subject;
};

AnalogClock::AnalogClock (ClockTimer* timer, Subject* subject)
{
	m_timer = timer;
    m_subject = subject;
    subject->Attach(this);
}

AnalogClock::~AnalogClock ()
{
    m_subject->Detach(this);
}

void AnalogClock::Update (Subject* theChangedSubject)
{
    if (theChangedSubject == m_subject)
    {
        Draw();
    }
}

void AnalogClock::Draw ()
{
    // get the new values from the subject
    string hours = TO_STRING(m_timer->GetHour());
    string minutes = TO_STRING(m_timer->GetMinute());
    string seconds = TO_STRING(m_timer->GetSecond());

    if(hours.size() == 1){hours = "0"+hours;}
    if(minutes.size() == 1){minutes = "0"+minutes;}
    if(seconds.size() == 1){seconds = "0"+seconds;}

    // draw the digital clock
    cout <<"I am Analog: "<< hours<<":"<<minutes<<":"<<seconds<<endl;
}

/**MAIN**/
int main()
{
	ConcreteSubject* subject = new ConcreteSubject();
	ClockTimer* timer = new ClockTimer(subject);
	DigitalClock* digitalClock = new DigitalClock(timer, subject);
	AnalogClock* analogClock = new AnalogClock(timer, subject);	
	
	timer->Tick();
	timer->Tick();
	timer->Tick();
	timer->Tick();
	timer->Tick();
	
	delete timer;
	delete digitalClock;
	delete analogClock;

    return 0;
}

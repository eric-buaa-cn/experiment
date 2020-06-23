#include <array>
#include <vector>
#include <iostream>
#include <chrono>

class Timer
{
public:
    void start()
    {
        m_StartTime = std::chrono::system_clock::now();
        m_bRunning = true;
    }
    
    void stop()
    {
        m_EndTime = std::chrono::system_clock::now();
        m_bRunning = false;
    }
    
    double elapsedMilliseconds()
    {
        std::chrono::time_point<std::chrono::system_clock> endTime;
        
        if(m_bRunning)
        {
            endTime = std::chrono::system_clock::now();
        }
        else
        {
            endTime = m_EndTime;
        }
        
        return std::chrono::duration_cast<std::chrono::milliseconds>(endTime - m_StartTime).count();
    }
    
    double elapsedSeconds()
    {
        return elapsedMilliseconds() / 1000.0;
    }

private:
    std::chrono::time_point<std::chrono::system_clock> m_StartTime;
    std::chrono::time_point<std::chrono::system_clock> m_EndTime;
    bool                                               m_bRunning = false;
};

#define ArraySize 100

unsigned int staticCounter = 0;
unsigned int copyCount = 0;
unsigned int moveCount = 0;

class NoThrowMoveConstructible
{
public:
	NoThrowMoveConstructible() 
	{ 
		m_memberVariable = new std::array<int, ArraySize>();
		m_memberVariable->fill(staticCounter++); 
	}
	~NoThrowMoveConstructible()
	{
		if (m_memberVariable != nullptr)
		{
			delete m_memberVariable;
		}
	}
	NoThrowMoveConstructible(NoThrowMoveConstructible&&	_in) noexcept 
	{
		moveCount++;
		this->m_memberVariable = _in.m_memberVariable;
		_in.m_memberVariable = nullptr;
	}
	NoThrowMoveConstructible(const NoThrowMoveConstructible& _in) noexcept
	{ 
		copyCount++;
		this->m_memberVariable = new std::array<int, ArraySize>(*(_in.m_memberVariable));
	}

	std::array<int, ArraySize>* m_memberVariable;
};

class CantBeNoThrowMoveConstructible
{
public:
	CantBeNoThrowMoveConstructible() 
	{ 
		m_memberVariable = new std::array<int, ArraySize>(); 
		m_memberVariable->fill(staticCounter++);
	}

	~CantBeNoThrowMoveConstructible()
	{
		if (m_memberVariable != nullptr)
		{
			delete m_memberVariable;
		}
	}

	CantBeNoThrowMoveConstructible(CantBeNoThrowMoveConstructible&& _in) 
	{ 
		moveCount++;
		this->m_memberVariable = _in.m_memberVariable;
		_in.m_memberVariable = nullptr;
	}

	CantBeNoThrowMoveConstructible(const CantBeNoThrowMoveConstructible& _in) 
	{ 
		copyCount++;
		this->m_memberVariable = new std::array<int, ArraySize>(*(_in.m_memberVariable));
	}

	std::array<int, ArraySize>* m_memberVariable;
};

template< typename Y >
std::vector<Y> OutputTimeForFillingVector(unsigned int vectorSize)
{
    copyCount = 0;
	moveCount = 0;
	std::vector<Y> vectorToFill;

	Timer t;
	t.start();

	for (int i = 0; i < vectorSize; i++)
	{
		Y val;
		vectorToFill.push_back(val);
	}
	std::vector<Y> copyVector = vectorToFill;
	std::cout << "Move Operations: " << moveCount << ". Copy Operations: " << copyCount << "\n";
	std::cout << "Time taken for " << typeid(Y).name() << ": " << t.elapsedMilliseconds() << "ms.\n";

	return copyVector;
}

struct MoveProperties {
    bool MoveProperties;
    bool moveconstructible;
    bool moveTriviallyAssignable;
    bool moveTriviallyConstructible;
    bool moveNoThrowAssignable;
    bool moveNoThrowConstructible;
};

template<typename Y>
MoveProperties GetProps()
{
	MoveProperties mp;
	mp.MoveProperties               = std::is_move_assignable<Y>::value;
	mp.moveconstructible            = std::is_move_constructible<Y>::value;
	mp.moveTriviallyAssignable      = std::is_trivially_move_assignable<Y>::value;
	mp.moveTriviallyConstructible   = std::is_trivially_move_constructible<Y>::value;
	mp.moveNoThrowAssignable        = std::is_nothrow_move_assignable<Y>::value;
	mp.moveNoThrowConstructible     = std::is_nothrow_move_constructible<Y>::value;
	return mp;
}

int main()
{  
	MoveProperties NoThrowMoveable		= GetProps<NoThrowMoveConstructible>();
	MoveProperties NoneNoThrowMoveable = GetProps<CantBeNoThrowMoveConstructible>();
	
	unsigned int vecSize = 1000;
	
	std::cout << "Can do move operations: \n";
	OutputTimeForFillingVector<NoThrowMoveConstructible>(vecSize);
	std::cout << "Can't do move operations: \n";
	OutputTimeForFillingVector<CantBeNoThrowMoveConstructible>(vecSize);
	return 0;
}

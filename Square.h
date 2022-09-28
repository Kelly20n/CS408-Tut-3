
#include "Vector2.h"


using namespace ObjLibrary;

class Square
{
public:
	// declare your constructor here
	Square()
	{
		init(0.25, 0.25, 0.25, 1.0, 1.0, 0.0, 0.0, 5.0, 1.0, 0.0, 0.0, 0.0);
		age = 999999;
	}
	// declare your public member functions here
	void init(float, float, float, float, float, float, float, float, float, float, float, float);
	void update();
	void display(float key);
	bool isAlive();
	
private:
	// declare your private member functions here
	// float random0to1();
	
	// declare your member variables here
	Vector2 pos;
	Vector2 vel;
	double age;
	float red;
	float green;
	float blue;
	float transparency;
	float scale;
	float xPosition;
	float yPosition;
	float velocity;
	float degrees;
};


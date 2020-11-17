#ifndef OBSERVER_H
#define OBSERVER_H


#include "WheelMeasure.h"


class Observer
{
public:
	//si dovrá spedire tutti i dati necessari al client(es:. 4 altezze, o live measure o quello che é)
	virtual void notify(WheelMeasure& distances) = 0;
};


#endif

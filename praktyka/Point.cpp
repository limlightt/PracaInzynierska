#include "stdafx.h"
#include "Point.h"

extern double dt;
extern double dr;
extern double g[3];
extern int A;
extern double B;
extern int n;

Point::Point()
{
}

Point::Point(int j)
{
	_NN.resize(j+1);
	_NNdistance.resize(j+1);
	_bounce.resize(3, 1);
	for (int i = 0; i < 6; i++)
	{
		_vi[i] = _Fi[i] = 0;
	}
	_currPos[0] = _currPos[1] = _currPos[2] = 0;
	_momentum.resize(3);
}

Point::Point(double x, double y, double z, int NNnum=3)
{
	for (int i = 0; i < 6; i++)
	{
		_vi[i] = _Fi[i] = 0;
	}

	_NNdistance.resize(NNnum+1, 0);
	_NN.resize(NNnum+1, NULL);
	_bounce.resize(3, 1);
	_momentum.resize(3);

	_currPos[0] = x;
	_currPos[1] = y;
	_currPos[2] = z;
}

void Point::findNearestNeighbours(Point* nn1, Point* nn2, Point* nn3) {
	_NN[1] = nn1;
	_NN[2] = nn2;
	_NN[3] = nn3;
}

double Point::countDistance(Point point)
{
	return sqrt(pow(getPos(0) - point.getPos(0), 2) + pow(getPos(1) - point.getPos(1), 2) + pow(getPos(2) - point.getPos(2), 2));
}

double Point::countDistance(double x1, double y1, double z1, double x2, double y2, double z2)
{
	return sqrt( pow(x1 - x2, 2) + pow(y1 - y2, 2) + pow(z1 - z2, 2));
}

void Point::countNeighboursDistances()
{
	for (int i = 1; i < _NNdistance.size(); i++)
	{
		_NNdistance[i] = countDistance(*_NN[i]);

	}
}

void Point::countPressureDistance(double distance, Point* middle)
{
	_NN[0] = middle;
	_NNdistance[0] = distance;
}

Point::~Point()
{
	_bounce.clear();

	_NN.clear();

	_NNdistance.clear();

	_momentum.clear();

}

void Point::resetPointToPosition(double x, double y, double z)
{
	setX(x); setY(y); setZ(z);
	for (int i = 0; i < 6; i++)
	{
		_vi[i] = 0;
		_Fi[i] = 0;
	}
}

double Point::countPotentialEnergyFromNN(double distance, double r0) 
{
	return A * (pow(r0 / distance, n) + pow(distance / r0, n));
}

double Point::countPotentialEnergyFromAllNN(double drn, int k) 
{ 
	double sum = 0;

	if (k == 0) {
		for (int i = 1; i < _NNdistance.size(); i++)
		{
			sum += countPotentialEnergyFromNN(_NNdistance[i], countDistance(getPos(0) + drn, getPos(1), getPos(2), _NN[i]->getPos(0), _NN[i]->getPos(1), _NN[i]->getPos(2) ));
		}
		return sum;
	}
	else if (k == 1) {
		for (int i = 1; i < _NNdistance.size(); i++)
		{
			sum += countPotentialEnergyFromNN(_NNdistance[i], countDistance(getPos(0), getPos(1) + drn, getPos(2), _NN[i]->getPos(0), _NN[i]->getPos(1), _NN[i]->getPos(2) ));
		}
		return sum;
	}
		for (int i = 1; i < _NNdistance.size(); i++)
		{
			sum += countPotentialEnergyFromNN(_NNdistance[i], countDistance(getPos(0), getPos(1), getPos(2) + drn, _NN[i]->getPos(0), _NN[i]->getPos(1), _NN[i]->getPos(2) ));
		}

		return sum;
	
}

double Point::countPotentialEnergyGravI(double g, double i) {
	return _m * g * i;
}

double Point::countPotentialEnergy( double ri, double drn, int k) 
{
	return countPotentialEnergyFromAllNN(drn, k) + countPotentialEnergyGravI(g[k], ri + drn) + (_NN[0] == NULL ? 0 : countPotentialEnergyBallMidPoint(drn, k));
}

double Point::countPotentialEnergyBallMidPoint(double drn, double k) 
{
	if (k == 0) {
		double r0 = countDistance(getPos(0) + drn, getPos(1), getPos(2), _NN[0]->getPos(0), _NN[0]->getPos(1), _NN[0]->getPos(2));
		return A * (pow(r0 / _NNdistance[0], n) + pow(_NNdistance[0] / r0, n));
	}
	else if (k == 1) {
		double r0 = countDistance(getPos(0), getPos(1) + drn, getPos(2), _NN[0]->getPos(0), _NN[0]->getPos(1), _NN[0]->getPos(2));
		return A * (pow(r0 / _NNdistance[0], n) + pow(_NNdistance[0] / r0, n));
	}
	double r0 = countDistance(getPos(0), getPos(1), getPos(2) + drn, _NN[0]->getPos(0), _NN[0]->getPos(1), _NN[0]->getPos(2));
	return A * (pow(r0 / _NNdistance[0], n) + pow(_NNdistance[0] / r0, n));

}

void Point::countBondPotentialEnergy()
{
	_bondEp = countPotentialEnergyFromAllNN(0, 0);
}

void Point::countHeightPotentialEnergy()
{
	_heightEp = 0;
	for (int i = 0; i < 3; i++) _heightEp += countPotentialEnergyGravI(g[i], getPos(i));
}

double Point::countKineticEnergy() 
{
	return _m * pow(countVelocity(), 2) / 2.;
}

double Point::countMomentum() 
{	
	double p = 0;
	for (int i = 0; i < 3; i++)
	{
		_momentum[i] = _vi[2 * i + 1] * _m;
		p += pow(_momentum[i], 2);
	}
	return sqrt(p);
}

double Point::countVelocity()
{
	double toReturn = 0;
	for (int i = 0; i < 3; i++) toReturn += pow(_vi[2 * i], 2);
	return sqrt(toReturn);
}

void Point::countNextCoordinatesXVF()
{
	countNewPosition();
	countNewForceAndVelocity();
	countBondPotentialEnergy();
	countHeightPotentialEnergy();
}

void Point::countNewPosition()
{
	for (int i = 0; i < 3; i++) {
		_currPos[i] += dt * _vi[2 * i] + _Fi[2 * i] * pow(dt, 2) / (2 * _m);

		if (_currPos[i] <= 0)
		{
			_currPos[i] *= -1;
			_bounce[i] = -1;		//ze nalezy odbic
		}
	}
}

void Point::countNewForceAndVelocity()
{
	//nowa sila
	for (int i = 0; i < 3; i++)
	{
		_Fi[2 * i + 1] = -(countPotentialEnergy(_currPos[i], dr, i) - countPotentialEnergy( _currPos[i], -dr, i)) / (2 * dr) -B * _vi[2 * i];
	}
	//nowa predkosc
	for (int i = 0; i < 3; i++)
	{
		_vi[2 * i + 1] = _vi[2 * i] + (_Fi[2 * i] + _Fi[2 * i + 1]) * dt / (2 * _m);

		if (_bounce[i] == -1)  //jesli jest odbicie
		{
			_vi[2 * i + 1] *= -1;
			//_vi[2 * i + 1] = sqrt(pow(_vi[2 * i + 1], 2) - 4 * gi[i] * _newPos[i]); 
			//reset bounce
			_bounce[i] = 1;
		}
	}

	for (int i = 0; i < 3; i++)
	{
		_vi[2 * i] = _vi[2 * i + 1];
		_Fi[2 * i] = _Fi[2 * i + 1];
	}
}
/*
void Point::updatePosition()
{
	for(int i = 0; i < 3; i++)	_currPos[i] = _newPos[i];
}

*/
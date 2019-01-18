#include "stdafx.h"
#include "Ball.h"

Ball::Ball(double x, double y, double z) : _x(x), _y(y), _z(z)
{
	for (int i = 0; i <= 61; i++) {
		_points.push_back(new Point(3));	
	}
	_COMVelocity.resize(3);
	prepareBall();
}

Ball::~Ball() {
	for (int i = 0; i <= 61; i++) {
		delete(_points[i]);		
	}
	_points.clear();
}

bool Ball::prepareBall()
{
	fstream ballCoords;
	fstream pentagons;
	fstream hexagons;
	double x, y, z;
	char C;
	int k, nn1, nn2, nn3;
	double temp, distance = 0;

	ballCoords.open("source/ballCoordinates.xyz");
	if (ballCoords.good())
	{
		for (int i = 0; i < 60; i++)			
		{
			ballCoords >> C;
			ballCoords >> x;
			ballCoords >> y;
			ballCoords >> z;

			getPoint(i)->setX(x + _x);
			getPoint(i)->setY(y + _y);
			getPoint(i)->setZ(z + _z);

			ballCoords >> k;
			ballCoords >> nn1;
			ballCoords >> nn2;
			ballCoords >> nn3;

			getPoint(i)->findNearestNeighbours(getPoint(nn1 - 1), getPoint(nn2 - 1), getPoint(nn3 - 1));
		}
	}
	else
	{
		cout << "problem with file ballCoordinates\n";
	}

	ballCoords.close();

	pentagons.open("source/pentagons.txt");
	if (pentagons.good())
	{
		for (int i = 0; i < 12; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				pentagons >> _pentaArray[i][j];
				_pentaArray[i][j]--;
			}
		}
	}
	else
	{
		cout << "problem with file pentagons\n";
	}
	pentagons.close();


	hexagons.open("source/hexagons.txt");
	if (hexagons.good())
	{
		for (int i = 0; i < 20; i++)
		{
			for (int j = 0; j < 6; j++)
			{
				hexagons >> _hexaArray[i][j];
				_hexaArray[i][j]--;
			}
		}
	}
	else
	{
		cout << "problem with file hexagons\n";
	}
	hexagons.close();

	getPoint(60)->setX(_x);
	getPoint(60)->setY(_y);
	getPoint(60)->setZ(_z);

	getPoint(60)->_NN.resize(61);
	getPoint(60)->_NNdistance.resize(61);

	for (int i = 0; i < 60; i++)
	{
		getPoint(60)->_NN[i + 1] = getPoint(i);
	}
	getPoint(60)->_NN[0] = NULL;
	getPoint(60)->countNeighboursDistances();

	for (int i = 0; i < 60; i++)
	{
		getPoint(i)->countPressureDistance(getPoint(i)->countDistance(*getPoint(60)), getPoint(60));
		getPoint(i)->countNeighboursDistances();
	}

	for (int i = 0; i < 60; i++)
	{
		getPoint(i)->setVi(0, 3);
	}

	cout << "Ball prepared \n";

	getPoint(60)->setm(0.001);
	return true;
}


//dwa ostatnie argumenty do countPotentialEnergy: dr = 0, k = 0 - 
// - dzieki temu energia potencjalna jest liczona dla kuli nieruchomej, niewychylonej, tak jak przed przeladowaniem countDistance
double Ball::countPotentialEnergy(double g) {
	double toReturn = 0;
	for (int i = 0; i < 60; i++) {
		toReturn += getPoint(i)->countPotentialEnergy(getPoint(i)->getPos(2), 0, 0);	//w domysle z, bo przekazuje to do modulu z grawitacja
	}
	return toReturn;
}


double Ball::countMomentum()	//uwzglednia srodek kuli, a on ma mase 1 wiec wchodzi do rownania jak wszystkie inne pkty
{
	//TO NIE LICZY NIC NORMALNEGO, TRZEBA TO JESZCZE RAZ NAPISAC
	return 1.5;
}
void Ball::countBallNextCoordinatesXVF() 
{
	for (int i = 0; i < 61; i++) _points[i]->countNewPosition();
	for (int i = 0; i < 61; i++) _points[i]->countNewForceAndVelocity();

	for (int i = 0; i < 61; i++)
	{
		_points[i]->countBondPotentialEnergy();
		_points[i]->countHeightPotentialEnergy();
	}
}


double Ball::countCOMVelocity() 
{
	double up, down, vel = 0;
	for (int i = 0; i < 61; i++) _points[i]->countMomentum();
	for (int i = 0; i < 3; i++)
	{
		up = 0; down = 0;
		for (int j = 0; j < 61; j++) {
			up += _points[j]->getMomentum(i);
			down += _points[j]->getm();
		}
		_COMVelocity[i] = up / down;
		vel += pow(_COMVelocity[i], 2);
	}
	return sqrt(vel);
}

double Ball::countCOMKineticEnergy() 
{
	double mass = 0;
	for (int i = 0; i < 61; i++) mass += _points[i]->getm();
	return mass * pow(countCOMVelocity(), 2) / 2.;
}

double Ball::countCOMPos(int n)
{
	double pos = 0;
	double sumMass = 0;
	for (int i = 0; i < 61; i++)
	{
		pos += _points[i]->getm() * _points[i]->getPos(n);
		sumMass += _points[i]->getm();
	}
	return pos / sumMass;
}

double Ball::countRelativePointKineticEnergy(int n)
{
	vector<double> relativeVelocity(3);
	double vel = 0;
	countCOMVelocity();
	for (int i = 0; i < _COMVelocity.size(); i++)
	{
		relativeVelocity[i] = _points[n]->getVi(i) - _COMVelocity[i];
		vel += pow(relativeVelocity[i], 2);
	}
	return _points[n]->getm() * vel / 2.;
}


double Ball::countRelativeBallKineticEnergy()
{
	double toReturn = 0;
	for (int i = 0; i < 61; i++) toReturn += countRelativePointKineticEnergy(i);
	return toReturn;
}

double Ball::countBallBondPotentialEnergy()
{
	double toReturn = 0;
	for (int i = 0; i < 61; i++) toReturn += _points[i]->getBondEp();
	return toReturn/2.;
}

double Ball::countBallKineticEnergy()
{
	double toReturn = 0;
	for (int i = 0; i < 61; i++)
	{
		toReturn += _points[i]->countKineticEnergy();
	}
	return toReturn;
}

double Ball::countBallWholeEnergy()
{
	double toReturn = 0;
	for (int i = 0; i < 61; i++) toReturn += _points[i]->getBondEp();
	toReturn /= 2.;
	for (int i = 0; i < 61; i++)
	{
		toReturn += _points[i]->countKineticEnergy();
		toReturn += _points[i]->getHeightEp();
	}
	return toReturn;
}

double Ball::countHeightEp()
{
	double toReturn = 0;
	for (int i = 0; i < 61; i++) toReturn += _points[i]->getHeightEp();
	return toReturn;
}
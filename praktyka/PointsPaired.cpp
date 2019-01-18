#include "stdafx.h"
#include "PointsPaired.h"

PointsPaired::PointsPaired(Point* point1, Point* point2)
{
	for (int i = 0; i < 2; i++) {
		_points.push_back(new Point());
	}
	
	_points[0] = point1;
	_points[1] = point2;

	_points[0]->_NN[0] = NULL;
	_points[0]->_NNdistance[0] = 0;

	_points[1]->_NN[0] = NULL;
	_points[1]->_NNdistance[0] = 0;

	_points[0]->_NN[1] = _points[1];
	_points[0]->_NNdistance[1] = _points[0]->countDistance(*_points[1]);

	_points[1]->_NN[1] = _points[0];
	_points[1]->_NNdistance[1] = _points[1]->countDistance(*_points[0]);

	_COMVelocity.resize(3);

}


void PointsPaired::countNextCoordinatesXVF()
{
	_points[0]->countNewPosition();
	_points[1]->countNewPosition();
	_points[0]->countNewForceAndVelocity();
	_points[1]->countNewForceAndVelocity();
	
	_points[0]->countBondPotentialEnergy();
	_points[1]->countBondPotentialEnergy();
	_points[0]->countHeightPotentialEnergy();
	_points[1]->countHeightPotentialEnergy();

}


void PointsPaired::resetPointsToPositions(double x1, double y1, double z1, double x2, double y2, double z2)
{
	_points[0]->resetPointToPosition(x1, y1, z1);
	_points[1]->resetPointToPosition(x2, y2, z2);
}

vector<double> PointsPaired::countCOMRadius()
{
	vector<double> radius(3);
	double bot = _points[0]->getm() + _points[1]->getm();
	radius[0] = (_points[0]->getPos(0)*_points[0]->getm() + _points[1]->getPos(0) * _points[1]->getm()) / bot;
	radius[1] = (_points[0]->getPos(1)*_points[0]->getm() + _points[1]->getPos(1) * _points[1]->getm()) / bot;
	radius[2] = (_points[0]->getPos(2)*_points[0]->getm() + _points[1]->getPos(2) * _points[1]->getm()) / bot;
	return radius;
}

double PointsPaired::countCOMVelocity()
{
	double vel = 0;
	_points[0]->countMomentum();	
	_points[1]->countMomentum();
	for (int i = 0; i < _COMVelocity.size(); i++)
	{
		_COMVelocity[i] = (_points[0]->getMomentum(i) + _points[1]->getMomentum(i)) / (_points[0]->getm() + _points[1]->getm());
		vel += pow(_COMVelocity[i], 2);
	}
	return sqrt(vel);
}

double PointsPaired::countCOMKineticEnergy()
{
	return (_points[0]->getm() + _points[1]->getm()) * pow(countCOMVelocity(), 2) / 2.;
}

double PointsPaired::countSumHeightPotentialEnergies()
{
	return (_points[0]->getHeightEp() + _points[1]->getHeightEp());
}


double PointsPaired::countRelativePointKineticEnergy(int j)
{
	vector<double> relativeVelocity(3);
	double vel = 0;
	countCOMVelocity();
	for (int i = 0; i < _COMVelocity.size(); i++)
	{
		relativeVelocity[i] = _points[j]->getVi(i) - _COMVelocity[i];
		vel += pow(relativeVelocity[i], 2);
	}
	return _points[j]->getm() * vel / 2.;
}

PointsPaired::~PointsPaired()
{
	for (int i = 0; i < 2; i++) delete(_points[i]);
	_points.clear();
}

#pragma once
class PointsPaired
{
public:

	/* konstruktor dwuargumentowy,
	 * Point* point1 - pierwszy z pary punkt�w tworz�cych oddzia�uj�c� par�
	 * Point* point2 - drugi z pary punkt�w tworz�cych oddzia�uj�c� par�
	 * konstruktor alokuje miejsce w dwuelementowej tablicy na wska�niki do punkt�w tworz�cych par�,
	 * nast�pnie wstawia je w przygotowane kom�rki. 
	 * ka�demu punktowi w parze przypisany zostaje ten drugi punkt jako jego s�siad i obliczona zostaje odleg�o�� do tego s�siada.
	 * Pierwsza kom�rka tablic _NN ka�dego z punkt�w zostaje ustawiona na NULL, 
	 * poniewa� jest to kom�rka zarezerwowana na punkt symuluj�cy ci�nienie w modelu,
	 * kt�ry nie jest tu implementowany. Odleg�o�� od nieistniej�cego punktu w tablicy _NNdistance zostaje ustawiona na 0.
	 * w konstruktorze zostaje r�wnie� zaalokowana pami�� w wektorze przechowuj�cym warto�� pr�dko�ci �rodka masy.
	*/
	PointsPaired(Point* point1, Point* point2);

	/* destruktor obiektu,
	 * zwalnia pami�� w obiekcie:
	 * zwalnia pami�� zaalokowan� w wektorze _points
	 */
	~PointsPaired();

	/* metoda bezargumentowa inline, zwraca wska�nik na pierwszy z pary punkt�w
	*/
	Point* getPoint1() { return _points[0]; }

	/* metoda bezargumentowa inline, zwraca wska�nik na drugi z pary punkt�w
	*/
	Point* getPoint2() { return _points[1]; }

	/* metoda bezargumentowa wywo�uj�ca funkcje realizuj�ce algorytm Verleta w odpowiedniej kolejno�ci
	* najpierw wywo�ana zostaje metoda countNewPosition dla ka�dego punktu, nast�pnie countNewForceAndVelocity dla ka�dego punktu.
	* w metodzie wywo�ane s� r�wnie� funkcje wyliczaj�ce warto�ci energii potencjalnej oddzia�ywa� i wysoko�ci punkt�w tworz�cych model.
	*/
	void countNextCoordinatesXVF();

	/* metoda sze�cioargumentowa,
	 * double x1 - wsp�rz�dna X nowej pozycji pierwszego punktu
	 * double y1 - wsp�rz�dna Y nowej pozycji pierwszego punktu
	 * double z1 - wsp�rz�dna Z nowej pozycji pierwszego punktu
	 * double x2 - wsp�rz�dna X nowej pozycji drugiego punktu
	 * double y2 - wsp�rz�dna Y nowej pozycji drugiego punktu
	 * double z2 - wsp�rz�dna Z nowej pozycji drugiego punktu
	 * wywo�uje na ka�dym punkcie restPointToPosition z odpowiednimi dla niego wsp�rz�dnymi.
	 */
	void resetPointsToPositions(double x1, double y1, double z1, double x2, double y2, double z2);
	
	 /* metoda bezargumentowa, wyznacza warto�ci sk�adowych pr�dko�ci punktu �rodka masy,
	 * uzupe�nia wektor _COMVelocity warto�ciami i zwraca jego d�ugo��
	 */
	double countCOMVelocity();

	/* metoda bezargumentowa,
	 * wylicza energi� kinetyczn� uk�adu �rodka masy i zwraca t� warto�� */
	double countCOMKineticEnergy();

	/* metoda bezargumentowa,
	 * sumuje energie potencjalne wysoko�ci obu punkt�w i zwraca t� warto��
	 */
	double countSumHeightPotentialEnergies();

	/* metoda jednoargumentowa,
	 * int i - numer punktu w parze, dla kt�rego obliczana zostaje warto��
	 * oblicza i zwraca energi� kinetyczn� punktu, gdzie pr�dko�ci� u�yt� we wzorze jest 
	 * pr�dko�� punktu wzgl�dem uk�adu �rodka masy.
	 */
	double countRelativePointKineticEnergy(int i);

	/* metoda bezargumentowa, oblicza po�o�enie punktu �rodka masy i zwraca go w postaci wektora
	*/
	vector<double> countCOMRadius();

private:

	//wektor przechowuj�cy wska�niki na punkty tworz�ce model
	vector<Point*> _points;
	
	//wektor przechowuj�ce warto�ci sk�adowych pr�dko�ci punktu �rodka masy
	vector<double> _COMVelocity;

	
};


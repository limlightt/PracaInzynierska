#pragma once
class Ball
{
public:

	/* konstruktor ptrzyargumentowy
	 * double x - warto�� dodana do sk�adowej x ka�dego punktu tworz�cego model
	 * double y - warto�� dodana do sk�adowej y ka�dego punktu tworz�cego model
	 * double z - warto�� dodana do sk�adowej z ka�dego punktu tworz�cego model
	 * alokuje pami�� w wektorze _points przechowuj�cym wska�niki do wszystkich punkt�w tworz�cych model;
	 * nast�pnie wywo�uje metod� prepareBall przygkotowuj�c� obiekt do symulacji.
	 */
	Ball(double x, double y, double z);

	/* destruktor obiektu
	 * zwalnia pami�� w obiekcie: zwalnia pami�� w wektorze _points usuwaj�c wska�niki
	 */
	~Ball();

	/* metoda bezargumentowa przygotowuj�ca model do symulacji:
	 * wczytuje z pliku "ballCoordinates.xyz" wsp�rz�dne punkt�w na sferze pi�ki i ustawia na nie wsp�rz�dne punkt�w
	 * z uwzgl�dnieniem przesuni�cia ca�ej pi�ki podanego w konstruktorze obiektu;
	 * wczytuje z tego samego pliku numery punkt�w s�siaduj�cych, znajduje je w uzupe�nionej tablicy _points 
	 * i dla ka�dego punktu uzupe�nia tablic� _NN wywo�uj�c metod� findNearestNeighbours;
	 * wczytuje z pliku "pentagons.txt" numery punkt�w (odpowiadaj�ce ich numerom w pliku ballCoordinates) tworz�cych pi�ciok�ty,
	 * uzupe�nia numerami tablic� _pentaArray;
	 * wczytuje z pliku "hexagons.txt" numery punkt�w (odpowiadaj�ce ich numerom w pliku ballCoordinates) tworz�cych sze�ciok�ty,
	 * uzupe�nia numerami tablic� _hexaArray;
	 * ustala wsp�rz�dne �rodka kuli jako (0, 0, 0) przesuni�te o wsp�rz�dne podane w konstrukotrze obiektu, 
	 * a wi�c efektywnie jako (x, y, z) gdzie x, y, z to zmienne podane do konstruktora;
	 * dodaje �rodek pi�ki do wektora _points jako element 61-szej kom�rki;
	 * ustala wszystkie punkty na sferze jako s�siad�w �rodka pi�ki (pierwsza kom�rka w tablicy _NN �rodka pi�ki przyjmuje warto�� NULL),
	 * dodaje �rodek pi�ki jako s�siada wszystkich punkt�w na sferze (pierwszego w tablicy _NN);
	 * uzupe�nia tablice _NNdistance wszystkich punkt�w tworz�cych model;
	 * nadaje pi�ce pr�dko�� pocz�tkow� wzd�� osi x r�wn� 2;
	 * zwraca warto�� logiczn� true.
	 */
	bool prepareBall();
	
	/* metoda jednoargumentowa,
	 * int i - indeks punktu w wektorze przechowuj�cym wska�niki do punkt�w
	 * zwraca wska�nik do punktu w kom�rce o podanym indeksie
	 */
	Point* getPoint(int i) { return _points[i]; }				

	double countPotentialEnergy(double g);			 //never used		ZOSTAWI�, MO�E NA WYKRESY B�DZIE
	double countMomentum();							//USUN�� �LE NAPISANA, NIEU�YWANA

	double countCOMVelocity();

	double countCOMKineticEnergy();

	double countCOMPos(int n);

	double countRelativePointKineticEnergy(int i);

	double countRelativeBallKineticEnergy();

	double countBallBondPotentialEnergy();

	double countBallWholeEnergy();

	double countBallKineticEnergy();

	double countHeightEp();


	/* metoda bezargumentowa wywo�uj�ca funkcje realizuj�ce algorytm Verleta w odpowiedniej kolejno�ci
	 * najpierw wywo�ana zostaje metoda countNewPosition dla ka�dego punktu, nast�pnie countNewForceAndVelocity dla ka�dego punktu.
	 * w metodzie wywo�ane s� r�wnie� funkcje wyliczaj�ce warto�ci energii potencjalnej oddzia�ywa� i wysoko�ci punkt�w tworz�cych model.		//jeszcze nie!!!!1
	 */	void countBallNextCoordinatesXVF();

	/* metoda dwuargumentowa inline
	 * int i = pierwsza wsp�rz�dna kom�rki w tablicy _pentaArray, i = 0, ..., 11
	 * int j = druga wsp�rz�dna kom�rki w tablicy _pentaArray, j = 0, ..., 4
	 * metoda zwraca numer punktu przechowywany w _pentaArray, kom�rce o podanych wsp�rz�dnych
	 */
	Point* getPentaP(int i, int j) { return _points[_pentaArray[i][j]]; }

	/* metoda dwuargumentowa inline
	* int i = pierwsza wsp�rz�dna kom�rki w tablicy _hexaArray, i = 0, ..., 19
	* int j = druga wsp�rz�dna kom�rki w tablicy _hexaArray, j = 0, ..., 5
	* metoda zwraca numer punktu przechowywany w _hexaArray, kom�rce o podanych wsp�rz�dnych
	*/
	Point* getHexaP(int i, int j) { return _points[_hexaArray[i][j]]; }

private:

	//wektor przechowuj�cy wska�niki do punkt�w tworz�cych model
    vector<Point*> _points;		

	//tablica przechowuj�ca numery punkt�w tworz�cych pi�ciok�ty 
	int _pentaArray[12][5];

	//tablica przechowuj�ca numery punkt�w tworz�cych sze�ciok�ty
	int _hexaArray[20][6];

	//wsp�rz�dna x przesuni�cia ca�ej kuli od po�o�enia wczytanego z pliku
	double _x;

	//wsp�rz�dna y przesuni�cia ca�ej kuli od po�o�enia wczytanego z pliku
	double _y;

	//wsp�rz�dna z przesuni�cia ca�ej kuli od po�o�enia wczytanego z pliku
	double _z;

	//wektor przechowuj�ce warto�ci sk�adowych pr�dko�ci punktu �rodka masy
	vector<double> _COMVelocity;

};


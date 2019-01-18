#pragma once
class Ball
{
public:

	/* konstruktor ptrzyargumentowy
	 * double x - wartoœæ dodana do sk³adowej x ka¿dego punktu tworz¹cego model
	 * double y - wartoœæ dodana do sk³adowej y ka¿dego punktu tworz¹cego model
	 * double z - wartoœæ dodana do sk³adowej z ka¿dego punktu tworz¹cego model
	 * alokuje pamiêæ w wektorze _points przechowuj¹cym wskaŸniki do wszystkich punktów tworz¹cych model;
	 * nastêpnie wywo³uje metodê prepareBall przygkotowuj¹c¹ obiekt do symulacji.
	 */
	Ball(double x, double y, double z);

	/* destruktor obiektu
	 * zwalnia pamiêæ w obiekcie: zwalnia pamiêæ w wektorze _points usuwaj¹c wskaŸniki
	 */
	~Ball();

	/* metoda bezargumentowa przygotowuj¹ca model do symulacji:
	 * wczytuje z pliku "ballCoordinates.xyz" wspó³rzêdne punktów na sferze pi³ki i ustawia na nie wspó³rzêdne punktów
	 * z uwzglêdnieniem przesuniêcia ca³ej pi³ki podanego w konstruktorze obiektu;
	 * wczytuje z tego samego pliku numery punktów s¹siaduj¹cych, znajduje je w uzupe³nionej tablicy _points 
	 * i dla ka¿dego punktu uzupe³nia tablicê _NN wywo³uj¹c metodê findNearestNeighbours;
	 * wczytuje z pliku "pentagons.txt" numery punktów (odpowiadaj¹ce ich numerom w pliku ballCoordinates) tworz¹cych piêciok¹ty,
	 * uzupe³nia numerami tablicê _pentaArray;
	 * wczytuje z pliku "hexagons.txt" numery punktów (odpowiadaj¹ce ich numerom w pliku ballCoordinates) tworz¹cych szeœciok¹ty,
	 * uzupe³nia numerami tablicê _hexaArray;
	 * ustala wspó³rzêdne œrodka kuli jako (0, 0, 0) przesuniête o wspó³rzêdne podane w konstrukotrze obiektu, 
	 * a wiêc efektywnie jako (x, y, z) gdzie x, y, z to zmienne podane do konstruktora;
	 * dodaje œrodek pi³ki do wektora _points jako element 61-szej komórki;
	 * ustala wszystkie punkty na sferze jako s¹siadów œrodka pi³ki (pierwsza komórka w tablicy _NN œrodka pi³ki przyjmuje wartoœæ NULL),
	 * dodaje œrodek pi³ki jako s¹siada wszystkich punktów na sferze (pierwszego w tablicy _NN);
	 * uzupe³nia tablice _NNdistance wszystkich punktów tworz¹cych model;
	 * nadaje pi³ce prêdkoœæ pocz¹tkow¹ wzd³ó¿ osi x równ¹ 2;
	 * zwraca wartoœæ logiczn¹ true.
	 */
	bool prepareBall();
	
	/* metoda jednoargumentowa,
	 * int i - indeks punktu w wektorze przechowuj¹cym wskaŸniki do punktów
	 * zwraca wskaŸnik do punktu w komórce o podanym indeksie
	 */
	Point* getPoint(int i) { return _points[i]; }				

	double countPotentialEnergy(double g);			 //never used		ZOSTAWIÆ, MO¯E NA WYKRESY BÊDZIE
	double countMomentum();							//USUN¥Æ LE NAPISANA, NIEU¯YWANA

	double countCOMVelocity();

	double countCOMKineticEnergy();

	double countCOMPos(int n);

	double countRelativePointKineticEnergy(int i);

	double countRelativeBallKineticEnergy();

	double countBallBondPotentialEnergy();

	double countBallWholeEnergy();

	double countBallKineticEnergy();

	double countHeightEp();


	/* metoda bezargumentowa wywo³uj¹ca funkcje realizuj¹ce algorytm Verleta w odpowiedniej kolejnoœci
	 * najpierw wywo³ana zostaje metoda countNewPosition dla ka¿dego punktu, nastêpnie countNewForceAndVelocity dla ka¿dego punktu.
	 * w metodzie wywo³ane s¹ równie¿ funkcje wyliczaj¹ce wartoœci energii potencjalnej oddzia³ywañ i wysokoœci punktów tworz¹cych model.		//jeszcze nie!!!!1
	 */	void countBallNextCoordinatesXVF();

	/* metoda dwuargumentowa inline
	 * int i = pierwsza wspó³rzêdna komórki w tablicy _pentaArray, i = 0, ..., 11
	 * int j = druga wspó³rzêdna komórki w tablicy _pentaArray, j = 0, ..., 4
	 * metoda zwraca numer punktu przechowywany w _pentaArray, komórce o podanych wspó³rzêdnych
	 */
	Point* getPentaP(int i, int j) { return _points[_pentaArray[i][j]]; }

	/* metoda dwuargumentowa inline
	* int i = pierwsza wspó³rzêdna komórki w tablicy _hexaArray, i = 0, ..., 19
	* int j = druga wspó³rzêdna komórki w tablicy _hexaArray, j = 0, ..., 5
	* metoda zwraca numer punktu przechowywany w _hexaArray, komórce o podanych wspó³rzêdnych
	*/
	Point* getHexaP(int i, int j) { return _points[_hexaArray[i][j]]; }

private:

	//wektor przechowuj¹cy wskaŸniki do punktów tworz¹cych model
    vector<Point*> _points;		

	//tablica przechowuj¹ca numery punktów tworz¹cych piêciok¹ty 
	int _pentaArray[12][5];

	//tablica przechowuj¹ca numery punktów tworz¹cych szeœciok¹ty
	int _hexaArray[20][6];

	//wspó³rzêdna x przesuniêcia ca³ej kuli od po³o¿enia wczytanego z pliku
	double _x;

	//wspó³rzêdna y przesuniêcia ca³ej kuli od po³o¿enia wczytanego z pliku
	double _y;

	//wspó³rzêdna z przesuniêcia ca³ej kuli od po³o¿enia wczytanego z pliku
	double _z;

	//wektor przechowuj¹ce wartoœci sk³adowych prêdkoœci punktu œrodka masy
	vector<double> _COMVelocity;

};


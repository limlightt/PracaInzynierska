#pragma once


class Point
{
public:
	/* konstruktor bezargumentowy,
	 * u�ywany do alokowania pami�ci dla p�niej uzupe�nianych punkt�w 
	 */
	Point();

	/* konstruktor jednoargumentowy,
	 * int j - ilo�� s�siad�w punktu na sferze
	 * alokuje pami�� w tablicy z s�siadami punktu,
	 * alokuje pami�� w tablicy z odleg�o�ciami od s�siad�w punktu,
	 * alokuje pami�� w tablicy ze sk�adowymi wektora wodz�cego punktu,
	 * alokuje pami�� w tablicy z flagami kontroluj�cymi odbicie cia�a
	 * ustawia poni�sze wartosci na 0:
	 * sk�adowe po�o�enia punktu, si�y, pr�dko�ci
	 * konsrtuktor u�ywany przy tworzeniu obiektu typu Ball 
	 */
	Point(int j);

	/* konstruktor czteroargumentowy,
	 * double x - warto�� sk�adowej x po�o�enia punktu
	 * double y - warto�� sk�adowej y po�o�enia punktu
	 * double z - warto�� sk�adowej z po�o�enia punktu 
	 * int NNnum - domy�lnie 3, ilo�� s�siad�w punktu, znajduj�cych si� na sferze
	 * alokuje pami�� w tablicy z s�siadami punktu,
	 * alokuje pami�� w tablicy z odleg�o�ciami od s�siad�w punktu,
	 * alokuje pami�� w tablicy ze sk�adowymi wektora wodz�cego punktu,
	 * alokuje pami�� w tablicy z flagami kontroluj�cymi odbicie cia�a
	 * ustawia poni�sze wartosci na 0:
	 * sk�adowe po�o�enia punktu, si�y, pr�dko�ci
	 * konstruktor wykorzystywany przy tworzeniu punktow w zadanym przez u�ytkownika miejscu
	 */
	Point(double x, double y, double z, int NNnum);

	/* destruktor obiektu
	 * zwalnia pami�� w obiekcie:
	 * zaalokowan� przez wektor _bounce, _NN, _NNdistance i _momentum
	 */
	~Point();

	/* metoda inline ustawiaj�ca warto�� sk�adowej x
	 * double x - warto�� sk�adowej x
	 */
	void setX(double x){ _currPos[0] = x; }

	void setm(double m) { _m = m; }
	
	/* metoda inline ustawiajaca wartosc sk�adowej y
	 * double y - warto�� sk�adowej y
	 */
	void setY(double y){ _currPos[1] = y; }

	/* metoda inline ustawiaj�ca warto�� sk�adowej z
	 * double z - warto�� sk�adowej z
	 */
	void setZ(double z){ _currPos[2] = z; }

	/* metoda inline zwracaj�ca mas� punktu 
	 */
	double getm() { return _m; }

	/* metoda inline dwuargumentowa
	 * int i - numer sk�adowej dla kt�rej ustawiona b�dzie nowa warto��
	 * double val - warto�� pr�dko�ci w danym kierunku
	 * metoda ustawia warto�� sk�adowej pr�dko�ci na podan� warto�� val. Ustawiona zostaje sk�adowa pr�dko�ci aktualnej.
	 */
	void setVi(int i, double val) { _vi[2 * i] = val; }

	/* metoda inline zwracajaca wartosc skladowej polozenia punktu
	 * int i - numer komorki w tablicy _currPos z ktorej zwracana jest wartosc, i = 0, 1, 2 
	 */
	double getPos(int i)const { return _currPos[i]; }

	/* metoda inline zwracajaca wartosc skladowej aktualnej predkosci punktu
	 * int i - numer skladowej predkosci ktora ma zostac zwrocna z tablicy _vi, i = 1, 3, 5
	 */
	double getVi(int i) { return _vi[2*i+1]; }

	/* metoda inline zwracajaca wartosc skladowej pedu punktu
	* int i - numer skladowej pedu ktora ma zostac zwrocna z tablicy _momentum, i = 0, 1, 2
	*/
	double getMomentum(int i) { return _momentum[i]; }

	/*metoda inline zwracajaca wartosc zmiennej _heightEp
	*/
	double getHeightEp() { return _heightEp; }

	/*metoda inline zwracajaca wartosc zmiennej _bondEp
	*/
	double getBondEp() { return _bondEp; }

	/*metoda inline zwracajaca sume zmiennych _heightEp i _bondEp
	*/
	double getWholeEp() { return _heightEp + _bondEp; }

	/* metoda trzyargumentowa
	 * double x - wsp�rz�dna X nowej pozycji punktu
	 * double y - wsp�rz�dna Y nowej pozycji punktu
	 * double z - wsp�rz�dna Z nowej pozycji punktu
	 * przenosi punkt do miejsca wskazanego przez argumenty funkcji
	 * zeruje predkosc obiektu i sile ktora na niego dziala
	 */
	void resetPointToPosition(double x, double y, double z);

	/* metoda trzyargumentowa
	 * Point* nn1 - wskaznik na punkt ktory jest pierwszym z trzech sasiadow obiektu na swerze
	 * Point* nn2 - wskaznik na punkt ktory jest drugim z trzech sasiadow obiektu na swerze
	 * Point* nn3 - wskaznik na punkt ktory jest trzecim z trzech sasiadow obiektu na swerze
	 * metoda uzupelnia tablice _NN podanymi wskaznikami
	 */
	void findNearestNeighbours(Point* nn1, Point* nn2, Point* nn3);

	/* metoda jednoargumentowa
	 * Point point - obiekt do ktorego liczona jest odleglosc
	 * metoda oblicza odleglosc miedzy obiektem na ktorym jest wywolana, 
	 * a argumentem wywolania i zwraca te wartosc
	 */
	double countDistance(Point point);

	/* metoda szescioargumentowa
	 * double x1 - skladowa x polozenia pierwszego z dwoch punktow 
	 * double y1 - skladowa y polozenia pierwszego z dwoch punktow 
	 * double z1 - skladowa z polozenia pierwszego z dwoch punktow 
	 * double x2 - skladowa x polozenia drugiego z dw�ch punktow 
	 * double y2 - skladowa y polozenia drugiego z dwoch punktow 
	 * double z2 - skladowa z polozenia drugiego z dwoch punktow 
	 * metoda oblicza odleglosc miedzy dwoma punktami w przestrzeni. 
	 * Jest to metoda static poniewa� nie jest bezpo�rednio zwi�zana z obiektem Point, ale jest u�ywana tylko w metodach tej klasy
	 */
	static double countDistance(double x1, double y1, double z1, double x2, double y2, double z2);

	/* metoda bezargumentowa
	 * metoda oblicza odleg�o�� mi�dzy obiektem na kt�rym zosta�a wywo�ana,
	 * a obiektami kt�re s� jego najbli�szymi s�siadami i zapisuje odleg�o�� od ka�dego z nich w tablicy _NNdistance
	 */
	void countNeighboursDistances();

	/* metoda dwuargumentowa
	 * double distance - odleg�o�� obiektu od �rodka kuli
	 * Point* middle - wska�nik na obiekt typu Point kt�ry jest �rodkiem kuli
	 * metoda umieszcza wska�nik na punkt srodkowy w pierwszej kom�rce tablicy _NN,
	 * oraz w tablicy _NNdistance w pierwszej kom�rce umieszcza odleg�o�� obiektu na kt�rym wywo�ano metod�, do obiektu middle
	 */
	void countPressureDistance(double distance, Point* middle);

	/* metoda dwuargumentowa
	 * double g - sk�adowa przyspieszenia ziemskiego ta sama, co sk�adowa po�o�enia przekazana w drugim argumencie
	 * double h - sk�adowa po�o�enia obiektu dla kt�rej liczona jest warto�� energii potencjalnej
	 * metoda oblicza warto�� energii potencjalnej obiektu na kt�rym zosta�a wywo�ana, gdyby by�o ono na wysoko�ci h
	 * metoda wylicza warto�c energii tylko dla danej sk�adowej. O podanie odpowiednich danych nale�y zadba� przy wywo�aniu metody.
	 * Mo�liwe jest rozbudowanie tej metody tak, aby oblicza�a energi� potencjaln� dla wszystkich sk�adowych wektor�w g i r.
	 * W przypadku tej symulacji nie ma to jednak sensu, poniewa� wiadomo, �e g w symulacji to przyspieszenie Ziemskie normalne, 
	 * a wi�c skierowane pionowo w d� i t� metod� wywo�uje si� tylko dla sk�adowej z wektor�w.
	 */
	double countPotentialEnergyGravI(double g, double h);		
	
	/* metoda dwuargumentowa
	 * double disatance - odleg�o�� mi�dzy obiektem na kt�rym metoda zosta�a wywo�ana, a po�o�eniem r�wnowagowym jego s�siada 
	 * double r0 - odleg�o�� mi�dzy obiektem na kt�rym metoda zosta�a wywo�ana, a po�o�eniem tego samego jego s�siada w innym punkcie
	 * metoda wylicza i zwraca warto�� energii potencjalnej oddzia�ywania mi�dzy obiektem, a jego s�siadem. 
	 * r0 przyjmuje warto�� odleg�o�ci mi�dzy obiektem a jego s�siadem w punkcie przesuni�tym o dr w kierunku jednej ze sk�adowych
	 */
	double countPotentialEnergyFromNN(double distance, double r0);
	
	/* metoda dwuargumentowa
	 * double drn - warto�� przesuni�cia punktu w kierunku jednej ze sk�adowych
	 * int k - numer sk�adowej kt�ra zostaje przesuni�ta o drn, k = 0, 1, 2
	 * metoda przechodzi po tablicy _NNdistance, a wi�c wykonuje obliczenia dla ka�dego s�siada obiektu:
	 * oblicza energi� potencjaln� oddzia�ywania mi�dzy obiektem a danym s�siadem w kierunku sk�adowej okre�lonej przez k,
	 * wywo�uj�c metod� countPotentialEnergyFromNN i podaj�c odpowiednie po�o�enie r�wnowagowe i tego s�siada w danym momencie 
	 * powi�kszone o warto�� dr w kierunku k-tej sk�adowej. Metoda zwraca sum� energii potencjalnych oddzia�ywa� ze wszystkimi s�siadami punktu poza punktem �rodkowym pi�ki.
	 * warto�� dr jest zmienn� globaln� w programie, ale musi ona zosta� przekazana do metody w zmiennej drn, poniewa� zmienna globalna niesie jedynie warto��, 
	 * a zmienna drn niesie r�wnie� znak. Takie rozwi�zanie pozwala wyznacza� warto�c energii potencjalnej oddzia�ywania dla po�o�enia pomniejszonego o dr w tej samej metodzie,
	 * co z kolei jest wykorzystywane przy wyliczaniu si�y dzia�aj�cej na dany punkt.
	 */
	double countPotentialEnergyFromAllNN(double drn, int k);

	/* metoda dwuargumentowa
	 * double drn - warto�� przesuni�cia punktu w kierunku jednej ze sk�adowych
	 * int k - numer sk�adowej kt�ra zostaje przesuni�ta o dr, k = 0, 1, 2
	 * metoda wylicza warto�� energii potencjalnej oddzia�ywa� mi�dzy obiektem a �rodkiem pi�ki;
	 * metoda dzia�a analogicznie do countEnergyFromAllNN, z t� tylko r�nic� �e wylicza warto�� energii potencjalnej dla jednego konkretnego punktu, a nie przechodzi po tablicy s�siad�w obiektu.
	 * metoda nie sprawdza, czy w modelu istnieje punkt �rodkowy - nalezy o to zadba� przed jej wywo�aniem.
	 */
	double countPotentialEnergyBallMidPoint(double dr, double k);

	/* metoda bezargumentowa, wyliczaj�ca warto�� energii potencjalnej oddzia�ywa� ze wszystkimi s�siadami dla obiektu;
	 * Metoda wywo�uje countPotentialEnergyFromAllNN dla warto�ci drn = 0, co gwarantuje �e energia zostanie policzona dla rzeczwistego po�o�enia s�siad�w. 
	 * skoro warto�� drn jest r�wna 0, to warto�� drugiego argumentu nie ma znaczenia dla wyniku. Wybrano wi�c warto�� 0, aby metoda zwraca�a wynik ju� po pierwszej p�tli if.
	 * metoda zapisuje otrzymany wynik w zmiennej w obiekcie: _bondEp
	 */
	void countBondPotentialEnergy();

	/* metoda bezargumentowa, zwraca warto�� energii potencjalnej obiektu.
	 * energia wyliczana jest jako suma energii potencjalnych jakie cia�o posiada dla ka�dej sk�adowej wektora g.
	 * metoda zapisuje otrzymany wynik w zmiennej w obiekcie: _heightEp.
	 */
	void countHeightPotentialEnergy();		

	/* metoda bezargumentowa, wyznacza warto�� energii kinetycznej obiektu na podstawie danych w nim przechowywanych;
	* otrzymana warto�� energii zostaje zwr�cona.
	*/
	double countKineticEnergy();

	/* metoda trzyargumentowa
	* double ri - warto�� sk�adowej po�o�enia cia�a
    * double drn - warto�� przesuni�cia punktu w kierunku jednej ze sk�adowych
	* int k - numer sk�adowej kt�ra zostaje przesuni�ta o drn, k = 0, 1, 2
	* metoda oblicza ��czn� warto�� energii potencjalnej obiektu w kierunku wybranej sk�adowej k: 
	* sumuje jego energi� potencjaln� wysoko�ci i energi� oddzia�ywa� z s�siadami;
	* je�li w modelu zaimplementowany jest r�wnie� punkt �rodkowy, dodana zostaje r�wnie� energia oddzia�ywania z tym punktem.
	* Metoda zwraca otrzyman� sum�.
	*/
	double countPotentialEnergy( double ri, double drn, int k);

	/* metoda bezargumentowa, ustawia wartosci skladowych wektora _momentum w tablicy w obiekcie,
	 * zwr�cona zostaje jego d�ugos�
	 */
	double countMomentum();
	
	/* metoda bezargumentowa, na podstawie 1, 3, 5 kom�rki w tablicy _vi - 
	 * - a wi�c na podstawie warto�ci aktualnej pr�dko�ci obiektu - wylicza warto�� pr�dko�ci punktu jako d�ugo�� wektora.
	 * Metoda zwraca obliczon� warto��.
	 */
	double countVelocity(); 

	/* metoda bezargumentowa wyznaczaj�ca nowe po�o�enie punktu za pomoc� metody Verleta
	 * nowo wyliczone po�o�enie zostaje wpisane do tablicy _currPos. 
	 * W tej metodzie obs�u�one zostaje r�wnie� odbicie punktu od powierzchni: 
	 * je�li kt�ra� ze sk�adowych nowego po�o�enia punktu <0, zostaje ona pomno�ona przez -1
	 * oraz ustawiona zostaje flaga w zmiennej w obiekcie: _bounce dla tej sk�adowej, w celu zmiany warto�ci nowej pr�dko�ci tego obiektu w innej funkcji.
	 */
	void countNewPosition();

	/* metoda bezargumentowa wyznaczaj�ca now� pr�dko�� punktu i si��, kt�ra na niego dzia�a za pomoc� algorytmu Verleta.
	 * je�li flaga _bounce dla kt�rej� ze sk�adowych ma warto�� -1, pr�dko�� cia�a nale�y pomno�y� przez -1.
	 * nowo wyliczone sk�adow pr�dko�ci i si�y zostaj� na bie��co wpisywane do tablicy odpowiednio _vi i Fi do kom�rek 1, 3, 5.
	 * nast�pnie warto�ci te zostaj� przepisane do kom�rek 0, 2, 4 a wi�c do kom�rek przechowuj�cych warto�ci sk�adowych z poprzedniego kroku czasowego,
	 * aby nie zosta�y nadpisane przy liczeniu nowych warto�ci pr�dko�ci i si�y,w nast�pnej iteracji symulacji.
	 */
	void countNewForceAndVelocity();

	//void updatePosition();																									////////////////////////////////////

	/* metoda bezargumentowa wywo�uj�ca funkcje realizuj�ce algorytm Verleta w odpowiedniej kolejno�ci
	 * najpierw wywo�ana zostaje metoda countNewPosition, nast�pnie countNewForceAndVelocity.
	 * w metodzie wywo�ane s� r�wnie� funkcje wyliczaj�ce warto�ci energii potencjalnej oddzia�ywa� i wysoko�ci obiektu
	 */
	void countNextCoordinatesXVF();

	//flaga przechowuj�ca informacje czy w aktualnej iteracji nast�pi�o odicie punktu w kierunku kt�rej� sk�adowej
	vector<int> _bounce;

	//wektor przechowuj�cy wska�niki do s�siad�w punktu. Je�li w modelu zaimplementowano punkt �rodkowy, wska�nik do niego jest w pierwszej kom�rce.
	vector<Point*> _NN;

	//wektor przechowuj�cy odleg�o�ci r�wnowagowe od s�siad�w obiektu. Numery kom�rek w tym wektorze i wektorze _NN, odpowiadaj� sobie.
	vector<double> _NNdistance;	

private:

	//zmienna przechowuj�ca warto�� energii potencjalnej wysoko�ci punktu
	double _heightEp;

	//zmienna przechowuj�ca  warto�� energii potencjalnej oddzia�ywa� punktu
	double _bondEp;
	
	//tablica reprezentuj�ca po�o�enie punktu
	double _currPos[3];
	//double _newPos[3];		//niepotrzebne chyba			///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	double _m = 1;		
	
	//wektor reprezentuj�cy p�d punktu
	vector<double> _momentum;

	//tablice przechowuj�ca warto�ci sk�adowych odpowiednio pr�dko�ci punktu i si�y kt�ra na niego dzia�a.
	//Aktualne warto�ci sk�adowych x, y, z przechowywane s� w kom�rkach 0, 2, 4
	//Nowo wyliczone warto�ci sk�adowych s� wpisywane do kom�rek 1, 3, 5
	double _vi[6];
	double _Fi[6];
};


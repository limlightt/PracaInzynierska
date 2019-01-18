#pragma once


class Point
{
public:
	/* konstruktor bezargumentowy,
	 * u¿ywany do alokowania pamiêci dla póŸniej uzupe³nianych punktów 
	 */
	Point();

	/* konstruktor jednoargumentowy,
	 * int j - iloœæ s¹siadów punktu na sferze
	 * alokuje pamiêæ w tablicy z s¹siadami punktu,
	 * alokuje pamiêæ w tablicy z odleg³oœciami od s¹siadów punktu,
	 * alokuje pamiêæ w tablicy ze sk³adowymi wektora wodz¹cego punktu,
	 * alokuje pamiêæ w tablicy z flagami kontroluj¹cymi odbicie cia³a
	 * ustawia poni¿sze wartosci na 0:
	 * sk³adowe po³o¿enia punktu, si³y, prêdkoœci
	 * konsrtuktor u¿ywany przy tworzeniu obiektu typu Ball 
	 */
	Point(int j);

	/* konstruktor czteroargumentowy,
	 * double x - wartoœæ sk³adowej x po³o¿enia punktu
	 * double y - wartoœæ sk³adowej y po³o¿enia punktu
	 * double z - wartoœæ sk³adowej z po³o¿enia punktu 
	 * int NNnum - domyœlnie 3, iloœæ s¹siadów punktu, znajduj¹cych siê na sferze
	 * alokuje pamiêæ w tablicy z s¹siadami punktu,
	 * alokuje pamiêæ w tablicy z odleg³oœciami od s¹siadów punktu,
	 * alokuje pamiêæ w tablicy ze sk³adowymi wektora wodz¹cego punktu,
	 * alokuje pamiêæ w tablicy z flagami kontroluj¹cymi odbicie cia³a
	 * ustawia poni¿sze wartosci na 0:
	 * sk³adowe po³o¿enia punktu, si³y, prêdkoœci
	 * konstruktor wykorzystywany przy tworzeniu punktow w zadanym przez u¿ytkownika miejscu
	 */
	Point(double x, double y, double z, int NNnum);

	/* destruktor obiektu
	 * zwalnia pamiêæ w obiekcie:
	 * zaalokowan¹ przez wektor _bounce, _NN, _NNdistance i _momentum
	 */
	~Point();

	/* metoda inline ustawiaj¹ca wartoœæ sk³adowej x
	 * double x - wartoœæ sk³adowej x
	 */
	void setX(double x){ _currPos[0] = x; }

	void setm(double m) { _m = m; }
	
	/* metoda inline ustawiajaca wartosc sk³adowej y
	 * double y - wartoœæ sk³adowej y
	 */
	void setY(double y){ _currPos[1] = y; }

	/* metoda inline ustawiaj¹ca wartoœæ sk³adowej z
	 * double z - wartoœæ sk³adowej z
	 */
	void setZ(double z){ _currPos[2] = z; }

	/* metoda inline zwracaj¹ca masê punktu 
	 */
	double getm() { return _m; }

	/* metoda inline dwuargumentowa
	 * int i - numer sk³adowej dla której ustawiona bêdzie nowa wartoœæ
	 * double val - wartoœæ prêdkoœci w danym kierunku
	 * metoda ustawia wartoœæ sk³adowej prêdkoœci na podan¹ wartoœæ val. Ustawiona zostaje sk³adowa prêdkoœci aktualnej.
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
	 * double x - wspó³rzêdna X nowej pozycji punktu
	 * double y - wspó³rzêdna Y nowej pozycji punktu
	 * double z - wspó³rzêdna Z nowej pozycji punktu
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
	 * double x2 - skladowa x polozenia drugiego z dwóch punktow 
	 * double y2 - skladowa y polozenia drugiego z dwoch punktow 
	 * double z2 - skladowa z polozenia drugiego z dwoch punktow 
	 * metoda oblicza odleglosc miedzy dwoma punktami w przestrzeni. 
	 * Jest to metoda static poniewa¿ nie jest bezpoœrednio zwi¹zana z obiektem Point, ale jest u¿ywana tylko w metodach tej klasy
	 */
	static double countDistance(double x1, double y1, double z1, double x2, double y2, double z2);

	/* metoda bezargumentowa
	 * metoda oblicza odleg³oœæ miêdzy obiektem na którym zosta³a wywo³ana,
	 * a obiektami które s¹ jego najbli¿szymi s¹siadami i zapisuje odleg³oœæ od ka¿dego z nich w tablicy _NNdistance
	 */
	void countNeighboursDistances();

	/* metoda dwuargumentowa
	 * double distance - odleg³oœæ obiektu od œrodka kuli
	 * Point* middle - wskaŸnik na obiekt typu Point który jest œrodkiem kuli
	 * metoda umieszcza wskaŸnik na punkt srodkowy w pierwszej komórce tablicy _NN,
	 * oraz w tablicy _NNdistance w pierwszej komórce umieszcza odleg³oœæ obiektu na którym wywo³ano metodê, do obiektu middle
	 */
	void countPressureDistance(double distance, Point* middle);

	/* metoda dwuargumentowa
	 * double g - sk³adowa przyspieszenia ziemskiego ta sama, co sk³adowa po³o¿enia przekazana w drugim argumencie
	 * double h - sk³adowa po³o¿enia obiektu dla której liczona jest wartoœæ energii potencjalnej
	 * metoda oblicza wartoœæ energii potencjalnej obiektu na którym zosta³a wywo³ana, gdyby by³o ono na wysokoœci h
	 * metoda wylicza wartoœc energii tylko dla danej sk³adowej. O podanie odpowiednich danych nale¿y zadbaæ przy wywo³aniu metody.
	 * Mo¿liwe jest rozbudowanie tej metody tak, aby oblicza³a energiê potencjaln¹ dla wszystkich sk³adowych wektorów g i r.
	 * W przypadku tej symulacji nie ma to jednak sensu, poniewa¿ wiadomo, ¿e g w symulacji to przyspieszenie Ziemskie normalne, 
	 * a wiêc skierowane pionowo w dó³ i tê metodê wywo³uje siê tylko dla sk³adowej z wektorów.
	 */
	double countPotentialEnergyGravI(double g, double h);		
	
	/* metoda dwuargumentowa
	 * double disatance - odleg³oœæ miêdzy obiektem na którym metoda zosta³a wywo³ana, a po³o¿eniem równowagowym jego s¹siada 
	 * double r0 - odleg³oœæ miêdzy obiektem na którym metoda zosta³a wywo³ana, a po³o¿eniem tego samego jego s¹siada w innym punkcie
	 * metoda wylicza i zwraca wartoœæ energii potencjalnej oddzia³ywania miêdzy obiektem, a jego s¹siadem. 
	 * r0 przyjmuje wartoœæ odleg³oœci miêdzy obiektem a jego s¹siadem w punkcie przesuniêtym o dr w kierunku jednej ze sk³adowych
	 */
	double countPotentialEnergyFromNN(double distance, double r0);
	
	/* metoda dwuargumentowa
	 * double drn - wartoœæ przesuniêcia punktu w kierunku jednej ze sk³adowych
	 * int k - numer sk³adowej która zostaje przesuniêta o drn, k = 0, 1, 2
	 * metoda przechodzi po tablicy _NNdistance, a wiêc wykonuje obliczenia dla ka¿dego s¹siada obiektu:
	 * oblicza energiê potencjaln¹ oddzia³ywania miêdzy obiektem a danym s¹siadem w kierunku sk³adowej okreœlonej przez k,
	 * wywo³uj¹c metodê countPotentialEnergyFromNN i podaj¹c odpowiednie po³o¿enie równowagowe i tego s¹siada w danym momencie 
	 * powiêkszone o wartoœæ dr w kierunku k-tej sk³adowej. Metoda zwraca sumê energii potencjalnych oddzia³ywañ ze wszystkimi s¹siadami punktu poza punktem œrodkowym pi³ki.
	 * wartoœæ dr jest zmienn¹ globaln¹ w programie, ale musi ona zostaæ przekazana do metody w zmiennej drn, poniewa¿ zmienna globalna niesie jedynie wartoœæ, 
	 * a zmienna drn niesie równie¿ znak. Takie rozwi¹zanie pozwala wyznaczaæ wartoœc energii potencjalnej oddzia³ywania dla po³o¿enia pomniejszonego o dr w tej samej metodzie,
	 * co z kolei jest wykorzystywane przy wyliczaniu si³y dzia³aj¹cej na dany punkt.
	 */
	double countPotentialEnergyFromAllNN(double drn, int k);

	/* metoda dwuargumentowa
	 * double drn - wartoœæ przesuniêcia punktu w kierunku jednej ze sk³adowych
	 * int k - numer sk³adowej która zostaje przesuniêta o dr, k = 0, 1, 2
	 * metoda wylicza wartoœæ energii potencjalnej oddzia³ywañ miêdzy obiektem a œrodkiem pi³ki;
	 * metoda dzia³a analogicznie do countEnergyFromAllNN, z t¹ tylko ró¿nic¹ ¿e wylicza wartoœæ energii potencjalnej dla jednego konkretnego punktu, a nie przechodzi po tablicy s¹siadów obiektu.
	 * metoda nie sprawdza, czy w modelu istnieje punkt œrodkowy - nalezy o to zadbaæ przed jej wywo³aniem.
	 */
	double countPotentialEnergyBallMidPoint(double dr, double k);

	/* metoda bezargumentowa, wyliczaj¹ca wartoœæ energii potencjalnej oddzia³ywañ ze wszystkimi s¹siadami dla obiektu;
	 * Metoda wywo³uje countPotentialEnergyFromAllNN dla wartoœci drn = 0, co gwarantuje ¿e energia zostanie policzona dla rzeczwistego po³o¿enia s¹siadów. 
	 * skoro wartoœæ drn jest równa 0, to wartoœæ drugiego argumentu nie ma znaczenia dla wyniku. Wybrano wiêc wartoœæ 0, aby metoda zwraca³a wynik ju¿ po pierwszej pêtli if.
	 * metoda zapisuje otrzymany wynik w zmiennej w obiekcie: _bondEp
	 */
	void countBondPotentialEnergy();

	/* metoda bezargumentowa, zwraca wartoœæ energii potencjalnej obiektu.
	 * energia wyliczana jest jako suma energii potencjalnych jakie cia³o posiada dla ka¿dej sk³adowej wektora g.
	 * metoda zapisuje otrzymany wynik w zmiennej w obiekcie: _heightEp.
	 */
	void countHeightPotentialEnergy();		

	/* metoda bezargumentowa, wyznacza wartoœæ energii kinetycznej obiektu na podstawie danych w nim przechowywanych;
	* otrzymana wartoœæ energii zostaje zwrócona.
	*/
	double countKineticEnergy();

	/* metoda trzyargumentowa
	* double ri - wartoœæ sk³adowej po³o¿enia cia³a
    * double drn - wartoœæ przesuniêcia punktu w kierunku jednej ze sk³adowych
	* int k - numer sk³adowej która zostaje przesuniêta o drn, k = 0, 1, 2
	* metoda oblicza ³¹czn¹ wartoœæ energii potencjalnej obiektu w kierunku wybranej sk³adowej k: 
	* sumuje jego energiê potencjaln¹ wysokoœci i energiê oddzia³ywañ z s¹siadami;
	* jeœli w modelu zaimplementowany jest równie¿ punkt œrodkowy, dodana zostaje równie¿ energia oddzia³ywania z tym punktem.
	* Metoda zwraca otrzyman¹ sumê.
	*/
	double countPotentialEnergy( double ri, double drn, int k);

	/* metoda bezargumentowa, ustawia wartosci skladowych wektora _momentum w tablicy w obiekcie,
	 * zwrócona zostaje jego d³ugosæ
	 */
	double countMomentum();
	
	/* metoda bezargumentowa, na podstawie 1, 3, 5 komórki w tablicy _vi - 
	 * - a wiêc na podstawie wartoœci aktualnej prêdkoœci obiektu - wylicza wartoœæ prêdkoœci punktu jako d³ugoœæ wektora.
	 * Metoda zwraca obliczon¹ wartoœæ.
	 */
	double countVelocity(); 

	/* metoda bezargumentowa wyznaczaj¹ca nowe po³o¿enie punktu za pomoc¹ metody Verleta
	 * nowo wyliczone po³o¿enie zostaje wpisane do tablicy _currPos. 
	 * W tej metodzie obs³u¿one zostaje równie¿ odbicie punktu od powierzchni: 
	 * jeœli któraœ ze sk³adowych nowego po³o¿enia punktu <0, zostaje ona pomno¿ona przez -1
	 * oraz ustawiona zostaje flaga w zmiennej w obiekcie: _bounce dla tej sk³adowej, w celu zmiany wartoœci nowej prêdkoœci tego obiektu w innej funkcji.
	 */
	void countNewPosition();

	/* metoda bezargumentowa wyznaczaj¹ca now¹ prêdkoœæ punktu i si³ê, która na niego dzia³a za pomoc¹ algorytmu Verleta.
	 * jeœli flaga _bounce dla którejœ ze sk³adowych ma wartoœæ -1, prêdkoœæ cia³a nale¿y pomno¿yæ przez -1.
	 * nowo wyliczone sk³adow prêdkoœci i si³y zostaj¹ na bie¿¹co wpisywane do tablicy odpowiednio _vi i Fi do komórek 1, 3, 5.
	 * nastêpnie wartoœci te zostaj¹ przepisane do komórek 0, 2, 4 a wiêc do komórek przechowuj¹cych wartoœci sk³adowych z poprzedniego kroku czasowego,
	 * aby nie zosta³y nadpisane przy liczeniu nowych wartoœci prêdkoœci i si³y,w nastêpnej iteracji symulacji.
	 */
	void countNewForceAndVelocity();

	//void updatePosition();																									////////////////////////////////////

	/* metoda bezargumentowa wywo³uj¹ca funkcje realizuj¹ce algorytm Verleta w odpowiedniej kolejnoœci
	 * najpierw wywo³ana zostaje metoda countNewPosition, nastêpnie countNewForceAndVelocity.
	 * w metodzie wywo³ane s¹ równie¿ funkcje wyliczaj¹ce wartoœci energii potencjalnej oddzia³ywañ i wysokoœci obiektu
	 */
	void countNextCoordinatesXVF();

	//flaga przechowuj¹ca informacje czy w aktualnej iteracji nast¹pi³o odicie punktu w kierunku którejœ sk³adowej
	vector<int> _bounce;

	//wektor przechowuj¹cy wskaŸniki do s¹siadów punktu. Jeœli w modelu zaimplementowano punkt œrodkowy, wskaŸnik do niego jest w pierwszej komórce.
	vector<Point*> _NN;

	//wektor przechowuj¹cy odleg³oœci równowagowe od s¹siadów obiektu. Numery komórek w tym wektorze i wektorze _NN, odpowiadaj¹ sobie.
	vector<double> _NNdistance;	

private:

	//zmienna przechowuj¹ca wartoœæ energii potencjalnej wysokoœci punktu
	double _heightEp;

	//zmienna przechowuj¹ca  wartoœæ energii potencjalnej oddzia³ywañ punktu
	double _bondEp;
	
	//tablica reprezentuj¹ca po³o¿enie punktu
	double _currPos[3];
	//double _newPos[3];		//niepotrzebne chyba			///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	double _m = 1;		
	
	//wektor reprezentuj¹cy pêd punktu
	vector<double> _momentum;

	//tablice przechowuj¹ca wartoœci sk³adowych odpowiednio prêdkoœci punktu i si³y która na niego dzia³a.
	//Aktualne wartoœci sk³adowych x, y, z przechowywane s¹ w komórkach 0, 2, 4
	//Nowo wyliczone wartoœci sk³adowych s¹ wpisywane do komórek 1, 3, 5
	double _vi[6];
	double _Fi[6];
};


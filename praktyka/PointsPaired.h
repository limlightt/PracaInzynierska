#pragma once
class PointsPaired
{
public:

	/* konstruktor dwuargumentowy,
	 * Point* point1 - pierwszy z pary punktów tworz¹cych oddzia³uj¹c¹ parê
	 * Point* point2 - drugi z pary punktów tworz¹cych oddzia³uj¹c¹ parê
	 * konstruktor alokuje miejsce w dwuelementowej tablicy na wskaŸniki do punktów tworz¹cych parê,
	 * nastêpnie wstawia je w przygotowane komórki. 
	 * ka¿demu punktowi w parze przypisany zostaje ten drugi punkt jako jego s¹siad i obliczona zostaje odleg³oœæ do tego s¹siada.
	 * Pierwsza komórka tablic _NN ka¿dego z punktów zostaje ustawiona na NULL, 
	 * poniewa¿ jest to komórka zarezerwowana na punkt symuluj¹cy ciœnienie w modelu,
	 * który nie jest tu implementowany. Odleg³oœæ od nieistniej¹cego punktu w tablicy _NNdistance zostaje ustawiona na 0.
	 * w konstruktorze zostaje równie¿ zaalokowana pamiêæ w wektorze przechowuj¹cym wartoœæ prêdkoœci œrodka masy.
	*/
	PointsPaired(Point* point1, Point* point2);

	/* destruktor obiektu,
	 * zwalnia pamiêæ w obiekcie:
	 * zwalnia pamiêæ zaalokowan¹ w wektorze _points
	 */
	~PointsPaired();

	/* metoda bezargumentowa inline, zwraca wskaŸnik na pierwszy z pary punktów
	*/
	Point* getPoint1() { return _points[0]; }

	/* metoda bezargumentowa inline, zwraca wskaŸnik na drugi z pary punktów
	*/
	Point* getPoint2() { return _points[1]; }

	/* metoda bezargumentowa wywo³uj¹ca funkcje realizuj¹ce algorytm Verleta w odpowiedniej kolejnoœci
	* najpierw wywo³ana zostaje metoda countNewPosition dla ka¿dego punktu, nastêpnie countNewForceAndVelocity dla ka¿dego punktu.
	* w metodzie wywo³ane s¹ równie¿ funkcje wyliczaj¹ce wartoœci energii potencjalnej oddzia³ywañ i wysokoœci punktów tworz¹cych model.
	*/
	void countNextCoordinatesXVF();

	/* metoda szeœcioargumentowa,
	 * double x1 - wspó³rzêdna X nowej pozycji pierwszego punktu
	 * double y1 - wspó³rzêdna Y nowej pozycji pierwszego punktu
	 * double z1 - wspó³rzêdna Z nowej pozycji pierwszego punktu
	 * double x2 - wspó³rzêdna X nowej pozycji drugiego punktu
	 * double y2 - wspó³rzêdna Y nowej pozycji drugiego punktu
	 * double z2 - wspó³rzêdna Z nowej pozycji drugiego punktu
	 * wywo³uje na ka¿dym punkcie restPointToPosition z odpowiednimi dla niego wspó³rzêdnymi.
	 */
	void resetPointsToPositions(double x1, double y1, double z1, double x2, double y2, double z2);
	
	 /* metoda bezargumentowa, wyznacza wartoœci sk³adowych prêdkoœci punktu œrodka masy,
	 * uzupe³nia wektor _COMVelocity wartoœciami i zwraca jego d³ugoœæ
	 */
	double countCOMVelocity();

	/* metoda bezargumentowa,
	 * wylicza energiê kinetyczn¹ uk³adu œrodka masy i zwraca tê wartoœæ */
	double countCOMKineticEnergy();

	/* metoda bezargumentowa,
	 * sumuje energie potencjalne wysokoœci obu punktów i zwraca tê wartoœæ
	 */
	double countSumHeightPotentialEnergies();

	/* metoda jednoargumentowa,
	 * int i - numer punktu w parze, dla którego obliczana zostaje wartoœæ
	 * oblicza i zwraca energiê kinetyczn¹ punktu, gdzie prêdkoœci¹ u¿yt¹ we wzorze jest 
	 * prêdkoœæ punktu wzglêdem uk³adu œrodka masy.
	 */
	double countRelativePointKineticEnergy(int i);

	/* metoda bezargumentowa, oblicza po³o¿enie punktu œrodka masy i zwraca go w postaci wektora
	*/
	vector<double> countCOMRadius();

private:

	//wektor przechowuj¹cy wskaŸniki na punkty tworz¹ce model
	vector<Point*> _points;
	
	//wektor przechowuj¹ce wartoœci sk³adowych prêdkoœci punktu œrodka masy
	vector<double> _COMVelocity;

	
};


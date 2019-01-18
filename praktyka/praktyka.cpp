
#include "stdafx.h"

struct thread_struct
{
	bool counting;
};

//zmienne do obsługi klawiszy przez openGL:
bool keys[256], specialkeys[256];

//zmienne do obrotu kamery na sferze
int camera_radius = 40;
float camera_theta = 0.15;
float camera_fi = 1.5;

//zmienne do  ruchu kamery wzdłuż osi X
double cameraPositionX = 0;
double cameraPositionY = 0;
double cameraPositionZ = 0;

//zmienne do implementacji światła w układzie
float light_radius = 5;
float light_theta = 0.2;
float light_fi = 1.2;

// typ enunm i flaga kontrolująca tryby wyświetlania piłki: 'middle' lub 'ball'
enum Options { sphere, middle };
Options displaying = sphere;

//zmienne do wyświetlania śladu jaki zostawia po sobie środek kuli w trybie 'middle'
int buffor = 0;
vector <double> middlePointX;
vector <double> middlePointY;
vector <double> middlePointZ;

//zmienne dla symulacji:

//symulowany obiekt piłki
Ball ball(5, 5, 10);

//krok czasowy do iteracji nowych położeń, prędkości i sił
double dt = 1e-4;

//krok przesunięcia do iteracji nowych położeń, prędkości i sił
double dr = 1e-2;

//wektor przyspieszenia ziemskiego normalnego
double g[3] = { 0, 0, 9.81 };

//stała we wzorze na energię potencjalną oddziaływań, mnoży cały wzór przez swoją wartość
int A = 1000;

//stała we wzorze na energię potencjalną oddziaływań, wykładnik potęg we wzorze
int n = 2;			

//stała w członie wzoru na siłę działającą na punkt, współczynnik tarcia
double B = 0.;		// 0.3;	

//obiekt kontrolujący dostęp wątku graficznego do symulowanego obiektu ball
thread_struct thread_data;


/* funkcja jednoargumentowa
 * vector <string> filenames - wektor z nazwami plików które mają zostać usunięte
 * metoda usuwa plik o danej nazwie
 */
void deleteFiles(vector<string> filenames)
{
	for (int i = 0; i < filenames.size(); i++)
	{
		const char * c = filenames[i].c_str();
		if (remove(c) != 0) cout << ("Error deleting file, could not have been created or smth \n");
		else
			cout << ("File " + filenames[i] + " successfully deleted \n");
	}
}

/* funkcja wieloargumentowa
 * string filename - nazwa pliku do którego mają zostać dopisane dane
 * int n - liczba wartości które zostaną dopisane do pliku
 * ... - wartości dopisywane do pliku, ich ilośc jest określona przez n
 * funkcja rzekazuje podane wartości do  pliku o podanej nazwie, dopisując je na końcu.
 */
void pushChartData(string filename, int n, ...)
{
	va_list values;
	va_start(values, n);

	fstream file(filename, ios::out | ios::app);
	double val;
	if (file.good())
	{
		for (int i = 0; i < n; i++)
		{
			val = va_arg(values, double);
			file << val << "\t";
		}
		file << "\n";
	}
	else cout << "problem z plikiem \n";
	va_end(values);
	file.close();

}

/* funkcja bezargumentowa wywołująca na obsługiwanym modelu piłki metodę countBallNextCoordinatesXVF
 * oraz przekazująca do plików dane do wyświetlenia na wykresach (część zakomentowana, odkomentowanie jej powoduje ogromne spowolnienie animacji) 
 */
void manageBallModel()
{
	int j = 4;
	int k = 0;
	//nazwy plikow z danymi do wykresow
	string filename1 = "wykresy/ball/ball-Z(t)_1e-" + to_string(j) + "_MUTE.txt";
	string filename2 = "wykresy/ball/ball-Ek(t)COM_1e-" + to_string(j) + "_MUTE.txt";
	string filename3 = "wykresy/ball/ball-Ec-skladowe_1e-" + to_string(j) + "_MUTE.txt";
	string filename5 = "wykresy/ball/ball-Eint_Ec_EkCOM_Eph_EkCOM+Eph_1e-" + to_string(j) + "_MUTE.txt";

	//usuwanie plikow z poprzedniego uruchomienia
	vector<string> filenames{filename1, filename2, filename3, filename5};
	deleteFiles(filenames);
	cout << "pamparampampam \n";

	dt = pow(10, -j);
	for (int i = 0; i < 10 * pow(10, j); i++)
	{
		double t = dt * i;
		ball.countBallNextCoordinatesXVF();
		// polozenie punktow, z(t)
		pushChartData(filename1, 2, t, ball.countCOMPos(2));					//DONE
		//energia kinetyczna ukladu srodka masy									//DONE 
		//pushChartData(filename2, 2, t, ball.countCOMKineticEnergy());
		//energia calkowita, wszystkie jej skladowe
		//pushChartData(filename3, 5, t, ball.countBallBondPotentialEnergy(), ball.countBallKineticEnergy(), ball.countHeightEp(), ball.countBallWholeEnergy());
		//energia wewnetrzna, calkowita, kinetyczna COM, potencjalna grawitacji, suma dwoch poprzednich
		//pushChartData(filename5, 6, t,
		//	ball.countRelativeBallKineticEnergy() + ball.countBallBondPotentialEnergy(),
		//	ball.countBallWholeEnergy(),
		//	ball.countCOMKineticEnergy(),
		//	ball.countHeightEp(),
		//	ball.countHeightEp() + ball.countCOMKineticEnergy());
	}

}

/* funkcja bezargumentowa, symuluje ruch punktu w przestrzeni przez określony czas, dla określonego kroku czasowego.
 * wylicza wartości położeń, prędkości, sił, energii itp. w kolejnych iteracjach i zapisuje dane w odpowiednich plikach;
 * funkcję można ulepszyć, alby przyjmowała argumenty wywołania pozwalające na kontrolę nad początkowym położeniem punktu przy wywołaniu.
 */
void manage1PointModel()
{
	Point point(3, 0, 5, 0);
	for (int j = 4; j < 5; j++)
	{
		//nazwy plikow z danymi do wykresow
		string filename1 = "wykresy/1pkt-Z(t)_1e-" + to_string(j) + ".txt";
		string filename2 = "wykresy/1pkt-Ek(t)_1e-" + to_string(j) + ".txt";
		string filename3 = "wykresy/1pkt-heightEp_bondEp_wholeEp_1e-" + to_string(j) + ".txt";
		string filename4 = "wykresy/1pkt-Ec(t)_Ep(t)_Ek(t)_1e-" + to_string(j) + ".txt";
		
		//usuwanie plikow z poprzedniego uruchomienia
		vector<string> filenames { filename1, filename2, filename3, filename4 };
		deleteFiles(filenames);
		dt = pow(10, -j);
		for (int i = 0; i < 10 * pow(10, j); i++)
		{
			double t = dt * i;
			point.countNextCoordinatesXVF();

			// polozenie punktu, z(t)
			pushChartData(filename1, 2, t, point.getPos(2));
			//energia kinetyczna punktu
			pushChartData(filename2, 2, t, point.countKineticEnergy());
			//energia potencjalna punktu, wszystkie energie: wysokosciowa, wiazania, sumaryczna
			pushChartData(filename3, 4, t, point.getHeightEp(), point.getBondEp(), point.getWholeEp());
			//energia kinetyczna, sumaryczna potencjalna, calkowita
			pushChartData(filename4, 4, t, point.getWholeEp() + point.countKineticEnergy(), point.getWholeEp(), point.countKineticEnergy());
		}
		//reset polozenia punktu
		point.resetPointToPosition(3., 0., 5.);
	}
}

/* funkcja bezargumentowa, symuluje ruch pary oddziałujących punktów w przestrzeni przez określony czas, dla określonego kroku czasowego.
 * wylicza wartości położeń, prędkości, sił, energii itp. w kolejnych iteracjach i zapisuje dane w odpowiednich plikach	 
 * funkcję można ulepszyć, alby przyjmowała argumenty wywołania pozwalające na kontrolę nad początkowym położeniem punktów przy wywołaniu.
 */
void manage2PointsModel()
{

	PointsPaired points(new Point(3, 0, 5, 1), new Point(3, 0, 5.5, 1));

	for (int j = 4; j < 5; j++)
	{
		//nazwy plikow z danymi do wykresow
		string filename1 = "wykresy/2pkt/2pkt-Z(t)_1e-" + to_string(j) + ".txt";
		string filename2 = "wykresy/2pkt/2pkt-Ek(t)COM_1e-" + to_string(j) + ".txt";
		string filename3 = "wykresy/2pkt/2pkt-EpheightCOM_1e-" + to_string(j) + ".txt";
		string filename4 = "wykresy/2pkt/2pkt-Ek(t)Relative_Ekbond(t)_1e-" + to_string(j) + ".txt";
		string filename5 = "wykresy/2pkt/2pkt-Eint_Ec_EkCOM_Eph_EkCOM+Eph_1e-" + to_string(j) + ".txt";

		//usuwanie plikow z poprzedniego uruchomienia
		vector<string> filenames{ filename1, filename2, filename3, filename4, filename5 };
		deleteFiles(filenames);
		cout << "pamparampampam \n";

		dt = pow(10, -j);
		for (int i = 0; i < 40 * pow(10, j); i++)
		{
			double t = dt * i;
			points.countNextCoordinatesXVF();
			// polozenie punktow, z(t)
			pushChartData(filename1, 3, t, points.getPoint1()->getPos(2), points.getPoint2()->getPos(2));
			//energia kinetyczna ukladu srodka masy
			pushChartData(filename2, 4, t, points.countCOMKineticEnergy(), points.getPoint1()->countKineticEnergy(), points.getPoint2()->countKineticEnergy());
			//energia potencjalna ukladu
			pushChartData(filename3, 2, t, points.countSumHeightPotentialEnergies());
			//energia kinetyczna kazdego pktu dla v wew. ukladu, energia wiazania kazdego pktu (powinny sie nalozyc na siebie)
			pushChartData(filename4, 5, t, points.countRelativePointKineticEnergy(0), points.countRelativePointKineticEnergy(1), points.getPoint1()->getBondEp(), points.getPoint2()->getBondEp());
			//energia wewnetrzna, calkowita, kinetyczna COM, potencjalna grawitacji, suma dwoch poprzednich
			pushChartData(filename5, 6, t,
				points.countRelativePointKineticEnergy(0) + points.countRelativePointKineticEnergy(1) + points.getPoint1()->getBondEp(),
				points.getPoint1()->countKineticEnergy() + points.getPoint1()->getBondEp() + points.getPoint1()->getHeightEp() + points.getPoint2()->countKineticEnergy() + points.getPoint2()->getHeightEp(),//+ points.getPoint2()->getBondEp(),
				points.countCOMKineticEnergy(),
				points.getPoint1()->getHeightEp() + points.getPoint2()->getHeightEp(),
				points.countCOMKineticEnergy() + points.getPoint1()->getHeightEp() + points.getPoint2()->getHeightEp());
		}

		//reset polozenia punktow
		cout << "done\n";
	}
}

/* funkcja bezargumentowa, ustawiająca opcje związane z wyświetlaniem animacji
*/
void initOpenGL()
{
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_NORMALIZE);
}

/* funkcja bezargumentowa, określająca wpływ naciśnięcia klawiszy na animację
*/
void handleKeys()
{
	if (keys[27]) exit(0);

	if (specialkeys[100]) camera_fi -= 0.001;        //lewo
	if (specialkeys[102]) camera_fi += 0.001;        //prawo
	if (specialkeys[101]) camera_theta += 0.001;     //gora
	if (specialkeys[103]) camera_theta -= 0.001;     //dol

	if (keys['a']) cameraPositionX += 0.02;	//x+ 
	if (keys['d']) cameraPositionX -= 0.02;	//x-

	if (keys['b']) displaying = sphere;
	if (keys['m']) displaying = middle;
}

//funkcja obsługująca wątki, kontrolująca dostęp do obiektu ball wątkowi rysującemu
void thread_function()
{
	thread_data.counting = false;
	while (true)
	{
		thread_data.counting = true;
		ball.countBallNextCoordinatesXVF();
		thread_data.counting = false;
	}
}

/* funkcja bezargumentowa, rysująca w oknie
 */
void drawScene()
{
	buffor++;
	handleKeys();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();


	gluLookAt(camera_radius * cos(camera_theta) * cos(camera_fi) + cameraPositionX, camera_radius * cos(camera_theta) * sin(camera_fi) + cameraPositionY, camera_radius * sin(camera_theta) + 3 + +cameraPositionZ,
			  cameraPositionX, cameraPositionY, 0,
			  camera_radius * cos(camera_theta + 0.1) * cos(camera_fi), camera_radius * cos(camera_theta + 0.1) * sin(camera_fi), camera_radius * sin(camera_theta + 0.1));

	GLfloat light0_position[4] = {cameraPositionX + 0.1, cameraPositionY, cameraPositionZ, 0.0 };

	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

	glDisable(GL_LIGHTING);

	//x red
	glLineWidth(0.5);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex3f(-100, 0.0, 0.0);
	glVertex3f(100, 0, 0);
	glEnd();

	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINES);
	glVertex3f(0.0, -100.0, 0.0);
	glVertex3f(0, 100, 0);
	glEnd();
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINES);
	glVertex3f(00, 0.0, -100.0);
	glVertex3f(0, 0, 100);
	glEnd();

	const GLfloat BronzeAmbient[4] = { 0.25f, 0.20725f, 0.20725f, 0.922f };
	const GLfloat BronzeDiffuse[4] = { 1.0f, 0.829f, 0.829f, 0.922f };
	const GLfloat BronzeSpecular[4] = { 0.296648f, 0.296648f, 0.296648f, 0.922f };
	const GLfloat* BronzeShininess = new GLfloat(11.264);

	if (thread_data.counting) {

		glEnable(GL_LIGHTING);

		glPushMatrix();
		glColor3f(0, 0, 1);
		glTranslatef(cameraPositionX, cameraPositionY, cameraPositionZ);
		glutSolidSphere(0.5, 10, 10);
		glPopMatrix();

		//track movement
		if (buffor % 10 == 0)
		{
			middlePointX.push_back(ball.getPoint(60)->getPos(0));
			middlePointY.push_back(ball.getPoint(60)->getPos(1));
			middlePointZ.push_back(ball.getPoint(60)->getPos(2));
		}

		if (displaying == sphere)
		{
			//rysuj pieciakaty
			glDisable(GL_COLOR_MATERIAL);
			glPushMatrix();
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, BronzeAmbient);
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, BronzeDiffuse);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, BronzeSpecular);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, BronzeShininess);

			for (int i = 0; i < 12; i++) {
				glBegin(GL_POLYGON);
				for (int j = 0; j < 5; j++)
				{
					glVertex3f(ball.getPentaP(i, j)->getPos(0), ball.getPentaP(i, j)->getPos(1), ball.getPentaP(i, j)->getPos(2));
				}
				glEnd();
				glPopMatrix();
			}

			//rysuj szesciakaty
			for (int i = 0; i < 20; i++) {
				glBegin(GL_POLYGON);
				glColor3f(0, 0, 1);
				for (int j = 0; j < 6; j++)
				{
					glVertex3f(ball.getHexaP(i, j)->getPos(0), ball.getHexaP(i, j)->getPos(1), ball.getHexaP(i, j)->getPos(2));
				}
				glEnd();
			}

			glEnable(GL_COLOR_MATERIAL);

			glPointSize(4.f);
			glBegin(GL_POINTS);
			glColor3f(0.3, 0.3, 0.3);
			//rysuj pkty
			for (int i = 0; i < 61; i++)
			{
				glVertex3f(ball.getPoint(i)->getPos(0), ball.getPoint(i)->getPos(1), ball.getPoint(i)->getPos(2));
			}
			glEnd();

			//rysuj krawedzie
			for (int i = 0; i < 60; i++)
			{
				glBegin(GL_LINES);
				glColor3f(0, 0, 0);
				for (int j = 1; j < 4; j++)
				{
					glVertex3f(ball.getPoint(i)->_NN[j]->getPos(0), ball.getPoint(i)->_NN[j]->getPos(1), ball.getPoint(i)->_NN[j]->getPos(2));
					glVertex3f(ball.getPoint(i)->getPos(0), ball.getPoint(i)->getPos(1), ball.getPoint(i)->getPos(2));
				}
				glEnd();
			}
		}
		else
		{
			glPushMatrix();
			glColor3f(1, 0, 0);
			glTranslatef(ball.getPoint(60)->getPos(0), ball.getPoint(60)->getPos(1), ball.getPoint(60)->getPos(2));
			glutSolidSphere(0.5, 10, 10);
			glPopMatrix();

			//display all stored points in track
			glBegin(GL_POINTS);
			glColor3f(1., 0., 0.);
			for (int i = 0; i < middlePointX.size(); i++) glVertex3f(middlePointX[i], middlePointY[i], middlePointZ[i]);
			glEnd();
		}

		//rysowanie podlogi
		glDisable(GL_LIGHTING);
		glBegin(GL_QUADS);
		glNormal3f(0, 1, 0);
		glColor3f(163 / 255., 174 / 255., 186 / 255.);
		for (int i = -200; i < 200; i++)
		{
			for (int j = -200; j < 200; j++)
				{
					glVertex3f(i, j, 0.);
					glVertex3f(i + 1, j, 0.);
					glVertex3f(i + 1, j + 1, 0.);
					glVertex3f(i, j + 1, 0.);
				}
			}
		}
		glEnd();

	glutSwapBuffers();
	glutPostRedisplay();
}

/* funkcja dwuargumentowa,
 * int w - szerokośc okna
 * int h - wysokość okna
 * funkcja wywoływana przy zmianie rozmiarów okna animacji
 */
void reshapeScreen(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (GLfloat)w / (GLfloat)h, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/* funkcja trzyargumentowa
 * unsigned char key - znak definiujący przycisk na klawiaturze który naciśnięto
 * int x - pozycja X myszy na ekranie
 * int y - pozycja Y myszy na ekranie
 * funkcja wywoływana gdy naciśnięty zostanie klawisz na klawiaturze
 */
void keyDown(unsigned char key, int x, int y)
{
	keys[key] = true;
}

/* funkcja trzyargumentowa
* unsigned char key - znak definiujący przycisk na klawiaturze który naciśnięto
* int x - pozycja X myszy na ekranie
* int y - pozycja Y myszy na ekranie
* funkcja wywoływana gdy puszczony zostanie klawisz na klawiaturze
*/
void keyUp(unsigned char key, int x, int y)
{
	keys[key] = false;
}


/* funkcja trzyargumentowa
* unsigned char key - znak definiujący przycisk na klawiaturze który naciśnięto
* int x - pozycja X myszy na ekranie
* int y - pozycja Y myszy na ekranie
* funkcja wywoływana gdy naciśnięty zostanie specjalny klawisz na klawiaturze
*/
void specialKeyDown(int key, int x, int y)
{
	specialkeys[key] = true;
}

/* funkcja trzyargumentowa
* unsigned char key - znak definiujący przycisk na klawiaturze który naciśnięto
* int x - pozycja X myszy na ekranie
* int y - pozycja Y myszy na ekranie
* funkcja wywoływana gdy puszczony zostanie specjalny klawisz na klawiaturze
*/
void specialKeyUp(int key, int x, int y)
{
	specialkeys[key] = false;
}

/* funkcja main programu
*/
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(0, 0);

	glutCreateWindow("Bachelor animation");

	initOpenGL();
	glutDisplayFunc(drawScene);
	glutReshapeFunc(reshapeScreen);

	glutKeyboardFunc(keyDown);
	glutKeyboardUpFunc(keyUp);
	glutSpecialFunc(specialKeyDown);
	glutSpecialUpFunc(specialKeyUp);

	//////////////////////////////////////////////////////////
	thread t1(thread_function);
	glutMainLoop();
	t1.join();

	//cout << "1 pkt\n";
	//manage1PointModel();
	//cout << "2 pkt\n";
	//manage2PointsModel();
	//cout << "ball\n";
	//manageBallModel();

	cout << "end";

	int j;
	cin >> j;
	return 0;
}


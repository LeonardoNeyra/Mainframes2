/*
*@author LeonardoNeyra
*/

class Regresion {

private:
	//El uso de * significa que se asigna espacio de memoria para la variable
	//La omision de * significa que NO se asigna espacio de memoria para la variable
	double* x; 
	double* y;
	double covXY;
	double promx;
	double promy;
	double desvX;
	double desvY;
	double sx;
	double sy;
	double sxy;
	double sx2;
	double sy2;
	double r;
	double* xy; 
	double* x2;
	double* y2;
	double numero;
	double newX;
	double newY;
	//Variables para calcular Regresion No Lineal
	double* x2y;
	double* x3;
	double* x4;
	double sx2y;
	double sx3;
	double sx4;
	double Determinante;
	double DeterminanteX;
	double DeterminanteY;
	double DeterminanteZ;
	double a0;
	double a1;
	double a2;
	double num;
	double rectaY;

public:
	Regresion() {
		//Creacion del dataset, luego no será neceario porque se importará directamente
		/*double tx[] = { 14,7,13,12,16,14,18,13,12,16,13 };
		double ty[] = { 16,12,13,14,15,12,16,11,13,18,17 };
		x = &tx[0]; // puede ser tambie x = tx; Esto selecciona la posicion en memoria por medio del puntero
		y = &ty[0]; // puede ser tambie x = ty;
		*/
		xy = new double[longitud];
		x2 = new double[longitud];
		y2 = new double[longitud];
		//Inicializar variable para Regresion No Lineal
		x2y = new double[longitud];
		x3 = new double[longitud];
		x4 = new double[longitud];
		sx = 0, sy = 0, sxy = 0, sx2 = 0, sy2 = 0;
		sx3 = 0, sx4 = 0, sx2y = 0; //Inicializar variables para Regresion No Lineal
		leerArchivo();
		calcularMatriz();
		calcularPromedio();
		calcularCovarianza();
		calcularDesviaciones();
		calcularR();
		//Metodos para Regresion No Lineal
		calcularR_MinimosCuadrados();
	}

	void leerArchivo() { //Lectura directa del dataset que debe estar en la carpeta del proyecto
		ifstream arch("datos.csv");
		string registro, cadena;
		short c = 0; //contador
		x = new double[longitud];
		y = new double[longitud];
		while (getline(arch, registro)) { //Recoge linea por linea
			stringstream ss(registro); //Convierto el registro en un archivo en memoria
			getline(ss, cadena, ','); //Cogo el archivo en memoria hasta la ','
			x[c] = atof(cadena.c_str()); //2.almaceno en la var x
										 //cout << cadena << " "; //Hago un espacio
			getline(ss, cadena); // Cogo el archivo en memoria despues de la ','
			y[c] = atof(cadena.c_str()); //2.primero convierto el registro en memoria a string (con c_str) y luego lo hago flotante con atof
			c++;
		}
	}
	void calcularMatriz() {

		for (int i = 0; i < longitud; ++i)
		{
			xy[i] = x[i] * y[i];
			x2[i] = pow(x[i], 2);
			y2[i] = pow(y[i], 2);
		}
		//*************************************************//

		for (int i = 0; i < longitud; ++i)
		{
			sx = sx + x[i];
			sy = sy + y[i];
			sxy = sxy + xy[i];
			sx2 = sx2 + x2[i];
			sy2 = sy2 + y2[i];
		}
	}
	void calcularPromedio() {
		promx = sx / longitud;
		promy = sy / longitud;
	}
	void calcularCovarianza() {
		covXY = (sxy / longitud) - (promx*promy);
	}
	void calcularDesviaciones() {
		desvX = sqrt((sx2 / longitud) - pow(promx, 2));
		desvY = sqrt((sy2 / longitud) - pow(promy, 2));
	}
	void calcularR() {
		r = covXY / (desvX*desvY);
	}
	void calcularNuevaX() {
		cout << ">>>-Ingrese el valor de Y:";
		cin >> numero;
		newX = ((covXY / (pow(desvY, 2)))*(numero - promy)) + promx;
	}
	void calcularNuevaY() {
		cout << ">>>-Ingrese el valor de X:";
		cin >> numero;
		newY = ((covXY / (pow(desvX, 2)))*(numero - promx)) + promy;
	}

	/*Calculo de Regresion No Lineal mediante Minimos Cuadrados*/
	double calcularDeterminante(double a1, double b1, double c1, double a2, double b2, double c2, double a3, double b3, double c3) {
		return (a1*b2*c3 + b1 * c2*a3 + a2 * b3*c1) - (c1*b2*a3 + b1 * a2*c3 + c2 * b3*a1);
	}
	void calcularR_MinimosCuadrados() {
		for (int i = 0; i < longitud; i++)
		{
			x2y[i] = x2[i] * y[i];
			x3[i] = pow(y[i], 3);
			x4[i] = pow(y[i], 4);
		}
		for (int i = 0; i < longitud; i++)
		{
			sx3 = sx3 + x3[i];
			sx4 = sx4 + x4[i];
			sx2y = sx2y + x2y[i];
		}

		//Solucion de la matriz de tres variables (x,y,z)
		Determinante = calcularDeterminante(longitud, sx, sx2, sx, sx2, sx3, sx2, sx3, sx4);
		DeterminanteX = calcularDeterminante(sy, sx, sx2, sxy, sx2, sx3, sx2y, sx3, sx4);
		DeterminanteY = calcularDeterminante(longitud, sy, sx2, sx, sxy, sx3, sx2, sx2y, sx4);
		DeterminanteZ = calcularDeterminante(longitud, sx, sy, sx, sx2, sxy, sx2, sx3, sx2y);

		//Calculo de coeficiente de la curva
		a0 = DeterminanteX / Determinante;
		a1 = DeterminanteY / Determinante;
		a2 = DeterminanteZ / Determinante;
	}
	void calcularMedianteMC() {
		//Solo se puede encontrar "y" a partir de "x"
		cout << ">>>-Ingrese el valor de X para una Regresion NO Lineal:";
		cin >> num;
		rectaY = a0 + (a1*num) + (a2*(pow(num, 2)));
	}

	void visualizar() {
		cout << "============================================" << endl;
		cout << "--------------Regresion Lineal--------------" << endl;
		cout << "============================================" << endl;
		cout << "* El promedio de X es:" << promx << endl; //endl -> end line
		cout << "* El promedio de Y es:" << promy << endl;
		cout << "* La covarianza es:" << covXY << endl;
		cout << "* El desviacion de X es:" << desvX << endl;
		cout << "* El desviacion de Y es:" << desvY << endl;
		cout << "--------------------------------------------" << endl;
		cout << "* El coeficiente de correlacion es:" << r << endl;
		cout << "--------------------------------------------" << endl;
		cout << "*>>-- El nuevo valor de X es:" << newX << endl;
		cout << "*>>-- El nuevo valor de Y es:" << newY << endl;
		cout << "============================================" << endl;
		cout << "------------Regresion No Lineal-------------" << endl;
		cout << "============================================" << endl;
		cout << "*>>-- El nuevo valor de Y es:" << rectaY << endl;
		cout << "--------------------------------------------" << endl;
		cin.get();
	}

};
/*
*@author LeonardoNeyra
*/

#include <iostream>
#include <cmath>
#include <fstream> //Manejo de archivos
#include <string> //Manejo de cadenas
#include <sstream> //Manejo de flujos
using namespace std;
#define longitud 11
#include "Regresion.hpp"

int main() {
	//Forma alternativa --> (Regresion()).visualizar();
	//Es una forma implicita de crear obj, pero no se pueden reusar
	Regresion r;
	r.calcularNuevaX();
	r.calcularNuevaY();
	r.calcularMedianteMC();
	r.visualizar();
	r.leerArchivo();	
	cin.get();
	//trickspark - onehub?
}
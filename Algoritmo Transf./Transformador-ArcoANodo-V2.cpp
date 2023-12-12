//El presente código tiene como finalidad el recibir como entrada un archivo .dat y generar en su salida un archivo
//tsp en el cual los Arcos pasan a ser Nodos y viceversa.
//Creado por Rodolfo Valentín
#include <cctype>
#include <fstream>
#include <iostream>
#include <list>
#include <sstream>
#include <string>
#include <vector>
//Archivo a leer
#define documento "RencaVial.dat"
using namespace std;

int main() {

  ifstream archivo;
  ofstream generadorTSP;
  istringstream recorrer;
  vector<string> todoData, costos, nodosIniciales, nodosFinales;
  int contadorNodos=0, i, j;
  string linea, nodoIni, nodoFin, costo;
  

  //Verficación de si el archivo se pudo abrir.
  archivo.open(documento);
  if (!archivo.is_open()) {
    cout << "No se pudo abrir el archivo indicado" << endl;
    return EXIT_FAILURE;
  }

  //Se saltan las primeras lineas que son las que contienen
  //información relevante para ampl
  getline(archivo, linea);
  getline(archivo, linea);
  getline(archivo, linea);
  //getline(archivo, linea);
  //#define EOF (-1)

  //Se crea un ciclo while para recorrer todo el archivo .dat
  //y recolectar los nodos de inicio y fin y los costos
  while (getline(archivo, linea)) { 
    if(archivo.eof()){
      break;    
    }
    todoData.push_back(linea);
    archivo >> nodoIni >> nodoFin >> costo;
    //cout << nodoIni << endl;
    //cout << nodoFin << endl;
    //cout << costo << endl;
    nodosIniciales.push_back(nodoIni);
    nodosFinales.push_back(nodoFin);
    costos.push_back(costo);
    contadorNodos++;
  }
  archivo.close();

  
  //for (auto v : todoData) {
    //if(v == ";"){
      //break;
    //}
    //cout << v << endl;
  //}
  
//+++++++++++Creación del archivo tipo .tsp+++++++++++
  
  generadorTSP.open("RencaVial.tsp");
  generadorTSP << "NAME: RencaVial\n";
  generadorTSP << "TYPE: TSP\n";
  generadorTSP << "COMMENT: " << contadorNodos - 1 << " city problem\n";
  generadorTSP << "DIMENSION: " << contadorNodos - 1 << "\n";
  generadorTSP << "EDGE_WEIGHT_TYPE: EXPLICIT\n";
  generadorTSP << "EDGE_WEIGHT_FORMAT: LOWER_DIAG_ROW\n";
  generadorTSP << "EDGE_WEIGHT_SECTION\n";
  
  for(i=0; i < contadorNodos-1; i++){
    for(j=0; j< contadorNodos-1; j++){
      if(i == j){
        generadorTSP << " " << 0;
        //break;
      }
      // else if(j > i){
      //   break;
      // }
      
      else if(nodosIniciales[i] == nodosIniciales[j] || nodosIniciales[i] == nodosFinales[j] ){
        generadorTSP << " " << costos[j];
      }        
      else if(nodosFinales[i] == nodosIniciales[j] || nodosFinales[i] == nodosFinales[j] ){
        generadorTSP << " " << costos[j];
      }  
      else{
        generadorTSP << " " << 1000;
      }
    }
    generadorTSP << "\n";
  }

  generadorTSP << "EOF\n";
  generadorTSP.close();
}
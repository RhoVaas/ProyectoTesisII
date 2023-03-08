#include "includes.h"
#include "globales.h"

void EliminarVisitaNodo(solucion * temp){
  int nodAEliminar=0,j=0, vecesRepetido=0;
  vector <int> posibleEliminado;
  nodAEliminar = int_rand(0, (Tinstancia-1)); 

  for(int i=0; i<Tinstancia;i++){     //Se utiliza un ciclo for para ubicar todas las posiciones en dónde aparece el nodo escogido
    if(temp->tour[i]== nodAEliminar)
      vecesRepetido++;                //Se contabiliza la cantidad de veces que aparece un nodo en el tour
      posibleEliminado.push_back(i);  //Se ingresa la posición del nodo en un vector
  }
  // if(vecesRepetido == 0){
  //   return;
  // }
  //else 
  if(vecesRepetido > 1){              //Siempre y cuando la cantidad de veces que el nodo aparece es mayor a 1, se procede a eliminar una aparición de este
    j = int_rand(0,sizeof(posibleEliminado)); //Se entrega un valor entre 0 y la cantidad de posiciones del nodo
    
    // auto randomPos = find(temp->tour.begin(), temp->tour.begin(), posibleEliminado[j]); //se le entrega la posición a randomPos
    // if(randomPos != temp->tour.end()){  //Siempre y cuando no se termine el tour, se ejecuta 
    //   temp->tour.erase(randomPos);}
    temp->tour.erase(temp->tour.begin() + posibleEliminado[j]);  //se elimina del tour el nodo en la posición escogida.
  }
  validar_permutacion(temp);
  calcular_aptitud(temp);
  return;
}

// Función que permite a un nodo ser visitado en más de una ocasión.
void AgregarVisitaNodo(solucion * temp){
  int nodo, nuevaPosNodo;
  nodo = int_rand(0, (Tinstancia-1)); //se le entrega a "nodo" la posición de un Nodo aleatorio
  nuevaPosNodo =int_rand(0, (Tinstancia-1)); //Se le entrega a "nuevaPosNodo" la posición donde se insertará el nodo obtenido
  
  temp->tour.insert(temp->tour.begin() + nuevaPosNodo , nodo); //El nodo aleatorio es insertado en el vector de tours, alargando asimismo este vector
  
  validar_permutacion(temp);
  calcular_aptitud(temp);
  return;
}

void seleccionar_dos_puntos_de_corte_DosOPT(int *corte1, int *corte2){
  //seleccionar dos puntos de corte diferentes entre variables
  int c1, c2, aux;
  c1=int_rand(0,Tinstancia); //entre 0 y tamanno instancia-1
  do{
    c2=int_rand(0,Tinstancia);
  }while((c1==c2)||(abs(c1-c2)==1)||(abs(c1-c2)==Tinstancia-1));

  //revisar condicion de c1 < c2
  if(c1>c2){
    aux=c2;
    c2=c1;
    c1=aux;
  }

  *corte1=c1;
  *corte2=c2;
  return;
}

void seleccionar_dos_puntos_de_corte_SWAP(int *corte1, int *corte2){
  //seleccionar dos puntos de corte diferentes entre variables
  int c1, c2, aux;
  c1=int_rand(0,Tinstancia); //entre 0 y tamanno instancia-1
  do{
    c2=int_rand(0,Tinstancia);
  }while(c1==c2);

  //revisar condicion de c1 < c2
  if(c1>c2){
    aux=c2;
    c2=c1;
    c1=aux;
  }

  *corte1=c1;
  *corte2=c2;
  return;
}

void DosOPT(solucion * solucion_actual, solucion * candidata_solucion){
  int aux;
  //copiar la informacion de solucion actual en candidata a solucion
  *candidata_solucion=*solucion_actual;
  int corte1,corte2;
  seleccionar_dos_puntos_de_corte_DosOPT(&corte1, &corte2);
  if(debug) cout<< "\t" << corte1 << "->" << corte2;
  //Girar la informacion entre los cortes
  int i=corte1;
  int j=corte2-1;
  while(i<corte2){
    (candidata_solucion)->tour[i] = (solucion_actual)->tour[j];
    i++;
    j--;
  }
  //Validar permutacion
  validar_permutacion(candidata_solucion);
  calcular_aptitud(candidata_solucion);
  return;
}

void SWAP(solucion * solucion_actual, solucion * candidata_solucion){
  int aux;
  //copiar la informacion de solucion actual en candidata a solucion
  *candidata_solucion=*solucion_actual;
  int corte1,corte2;
  seleccionar_dos_puntos_de_corte_SWAP(&corte1, &corte2);
  if(debug) cout<< "\t" << corte1 << "->" << corte2;
  
  (candidata_solucion)->tour[corte1]=(solucion_actual)->tour[corte2];
  (candidata_solucion)->tour[corte2]=(solucion_actual)->tour[corte1];
 
  //Validar permutacion
  validar_permutacion(candidata_solucion);
  calcular_aptitud(candidata_solucion);
  return;
}

void escribir_en_archivo_resultados (void){
  ofstream res;
  res.open(archivo_resultados);
  res<<mejor_solucion<<endl;
  res.close();
  cout<<mejor_solucion<<endl;
  return;
}

void salir(void){
  escribir_en_archivo_resultados();
  //salida sin error
  exit(0);
  return;
}

void calcular_aptitud(solucion * temp){
  //cout << "-----------------------------------------------------------" << endl;
  int apt=0;
  //calcular el costo del tour
  for(int i=0; i<(temp->tour.size() -1); i++){
    apt+=(int)distancia[temp->tour[i]][temp->tour[i+1]];
    //cout<<temp->tour[i] << "-> " << temp->tour[i+1] << " : "<< (int)distancia[temp->tour[i]][temp->tour[i+1]] << endl;
  }
  apt+=(int)distancia[temp->tour[temp->tour.size() -1]][temp->tour[0]];
  
  temp->aptitud=apt;

  if(iteracion>0)
    if(apt==optimo_global.aptitud){
      mejor_solucion=*temp;
      cout<<"Optimo encontrado!"<<endl;
      salir();
    }
  return;
}

//*****
// modificar la función validar permutación 
//para que permita que aparezcan arcos repetidos.
//*****
void validar_permutacion(solucion * temp){
  int set[Tinstancia], numero, j=0;
  for(numero=0;numero<Tinstancia;numero++){
    j=0;
    for(int i=0;i<temp->tour.size();i++){
      if(temp->tour[i]== numero){
        j++;
        set[numero]= j;
      }
    }

    if(set[numero] == 0){
      cout<< "+++++++++++++++++++++++"<<endl;
      cout<< "El valor con 0 es: ";
      cout<< numero <<endl;
      cout<<"ERROR: Solucion invalida"<<endl;
      cout << temp;
      //cout<< "+++++++++++++++++++++++"<<endl;
      salir();
     }
  }
  // for(int i=0;i<temp->tour.size();i++){
  //    if(set[temp->tour[i]] == 0){
  //     cout<< "+++++++++++++++++++++++"<<endl;
  //     cout<< "El valor con 0 es: ";
  //     cout<< i <<endl;
  //     cout<<"ERROR: Solucion invalida"<<endl;
  //     //cout<< "+++++++++++++++++++++++"<<endl;
  //     salir();
  //    }

  //   //set[temp->tour[i]]=0;
  // }
  return;
}

float conv_rad(float coord){
  int int_coord=coord;
  double dif=coord-int_coord;
  return (PI*(int_coord+5.0*dif/3.0)/180.0);
}

void leer_archivo_configuracion(void){

  char instancia[1000];
  //lectura de archivo de configuracion
  FILE *configuracion;
  char buf[100];
  int i,j;

  configuracion=fopen(archivo_configuracion, "r");
  int rt=fscanf(configuracion,"%s",buf);
  while(strcmp("NODE_COORD_SECTION",buf)!=0 && strcmp("EDGE_WEIGHT_SECTION",buf)!=0 ){
      if(strcmp("EDGE_WEIGHT_TYPE",buf)==0){
        rt=fscanf(configuracion,"%s",buf); //los dos puntos que estan separados
        rt=fscanf(configuracion,"%s",buf);
        if(strcmp("GEO",buf)==0)
          tipodistancia=GEO;
        else if(strcmp("EUC_2D",buf)==0)
          tipodistancia=EUC;
        buf[0]=0;
      }
      else if(strcmp("EDGE_WEIGHT_TYPE:",buf)==0){
        int rt=fscanf(configuracion,"%s",buf);
        if (strcmp("GEO",buf)==0)
          tipodistancia=GEO;
        else if(strcmp("EUC_2D",buf)==0)
          tipodistancia=EUC;
        buf[0]=0;
      }
      else if(strcmp("DIMENSION",buf)==0){
        rt=fscanf(configuracion,"%s",buf);//los dos puntos que estan separados
        rt=fscanf(configuracion,"%d",&Tinstancia);
        buf[0]=0;
      }
      else if(strcmp("DIMENSION:",buf)==0) {
        rt=fscanf(configuracion, "%d", &Tinstancia);
        buf[0]=0;
      }
      else if(strcmp("NAME",buf)==0)
        buf[0]=0;
      else if(strcmp("NAME:",buf)==0)
        buf[0]=0;
        rt=fscanf(configuracion,"%s", buf);
    }

  if(strcmp("EDGE_WEIGHT_SECTION",buf)==0){
    if(Tinstancia==0){
      cout<<"ERROR: Problemas en la lectura del tamano de la instancia"<<endl;
      salir();
    }

    //Reserva de espacio para la matriz de distancia

    distancia=new int*[Tinstancia];
    for( int i = 0 ; i < Tinstancia ; i++ )
      distancia[i] = new int [Tinstancia];

    //Lectura de la matriz triangular inferior.
    float dist = 0;
    for(int i=0;i<(Tinstancia-1);i++){
      for(int j=0;j<i+1;j++){
        int rt=fscanf(configuracion,"%f ",&dist);
        distancia[i][j] = dist;
        distancia[j][i] = distancia[i][j];
        cout << "distancia matriz triangular entre i:" << i << " y j: " << j <<" dist: " << dist << endl;
      }
    }

  }



  if(strcmp("NODE_COORD_SECTION",buf)==0){
    if(Tinstancia==0){
      cout<<"ERROR: Problemas en la lectura del tamano de la instancia"<<endl;
      salir();
    }

    //Reserva de espacio para el arreglo de coordenadas y la matriz de distancia
    coordenadas=new coordenada[Tinstancia];
    distancia=new int*[Tinstancia];
    for( int i = 0 ; i < Tinstancia ; i++ )
      distancia[i] = new int [Tinstancia];
    //Lectura de las coordenadas de cada punto
    int id;
    float x,y;
    int contador=0;
    while(contador<Tinstancia){
      int rt=fscanf(configuracion,"%d %f %f\n",&id,&x,&y);
      coordenadas[id-1].x=x;
      coordenadas[id-1].y=y;
      contador++;
    }
  }

  //Calculo de la matriz de distancias
  for(int i=0;i<(Tinstancia-1);i++){
    for(int j=i+1;j<Tinstancia;j++){
      if(tipodistancia==EUC)
        distancia[i][j]=round(sqrt(pow((coordenadas[i].x-coordenadas[j].x),2)+pow((coordenadas[i].y-coordenadas[j].y),2)));
      else if(tipodistancia==GEO){
        float RRR=6378.388;
        float latitud1=conv_rad(coordenadas[i].x);
        float longitud1=conv_rad(coordenadas[i].y);
        float latitud2=conv_rad(coordenadas[j].x);
        float longitud2=conv_rad(coordenadas[j].y);
        float q1=cos(longitud1-longitud2);
        float q2=cos(latitud1-latitud2);
        float q3=cos(latitud1+latitud2);
        distancia[i][j]=(int)(RRR*acos(0.5*((1.0+q1)*q2-(1.0-q1)*q3))+1.0);
      }
      distancia[j][i]=distancia[i][j];
    }
  }
  if (debug){
    for(int i=0;i<Tinstancia;i++)
      for(int j=0;j<Tinstancia;j++)
        cout<<distancia[i][j]<<" ";
      cout<<endl;
  }
  strcpy(instancia,archivo_configuracion);
  int largo=strlen(instancia);
  instancia[largo-4]='\0';
  //strcat(instancia,".opt.tour");

  //FILE *lectura_optimo;
  //lectura_optimo=fopen(instancia, "r");
  //if(lectura_optimo==NULL){
  // cout<<"ERROR: Problemas en la lectura del archivo de tour optimo"<<endl;
  // salir();
  //}

  //do{
  //  int rt=fscanf(lectura_optimo,"%s",buf);
  //}while(strcmp("TOUR_SECTION", buf)!=0);

  // int tmp;
  // for(int i=0; i<Tinstancia;i++){
  //   //int rt=fscanf(lectura_optimo, "%d", &tmp);
  //   optimo_global.tour.push_back(tmp-1);
  // }
  // calcular_aptitud(&optimo_global);

  //fclose(lectura_optimo);
  fclose(configuracion);
  return;
}

void crear_solucion_aleatoria (solucion *i_temp){
  int rand;
  //creacion de la permutacion aleatoria
  int set[Tinstancia];
  for(int i=0;i<Tinstancia;i++)
    set[i]=i;

  for (int i=0;i<Tinstancia;i++){
    rand=int_rand(0,(Tinstancia-i)); // Un elemento del arreglo (entre 0 y Tinstancia-1 la primera vez y asi...)
    i_temp->tour[i]=set[rand]; 
    set[rand]=set[Tinstancia-i-1]; 
  }
  //calculo de la aptitud de la solucion
  calcular_aptitud(i_temp);
  return;
}

int int_rand (int a, int b){
  //generacion de numeros aleatorios entre a y b-1
  int retorno=0;
  if (a<b){ 
    retorno=(int)((b-a)*drand48());
    retorno=retorno+a;
  }
  else{
    retorno=(int)((a-b)*drand48());
    retorno=retorno+b;
  }
  return retorno;
}

int leer_entradas(int argc, char **argv){
  //archivo con la instancia del problema
  archivo_configuracion=(char *)(argv[1]);
  
  //archivo donde escribir los resultados de la ejecucion
  archivo_resultados=(char *)(argv[2]);
  
  //SEMILLA
  semilla=atoi(argv[3]);

  //PARAMETROS
  Ti=atoi(argv[4]); //temperatura inicial
  alpha=atof(argv[5]); //alpha
  Mi=atoi(argv[6]); 
  Mp=atoi(argv[7]);
  movimiento=atoi(argv[8]); //movimiento 0=SWAP, 1=DosOPT

  if((movimiento!=0)&&(movimiento!=1))  
    salir();

  if(debug)
    printf("Ti: %d, alpha: %.2f, Mi: %d, Mp: %d\n",Ti,alpha,Mi,Mp);
  
  debug=atoi(argv[9]);
  
  //PROBABILIDAD DE USO DE AGREGAR O ELIMINAR NODOS
  probAgregar = atoi(argv[10]);
  return 1;
}

int main (int argc, char *argv[]){
  
  //lectura de parametros
  if(!leer_entradas(argc,argv)){
    cout<<"Problemas en la lectura de los parametros";
    exit(1);
  }

  iteracion=-1;
  paso=-1;
  //lectura de instancia
  leer_archivo_configuracion();
  solucion solucion_actual, candidata_solucion, mejor_candidata;

  //semilla aleatoria
  srand48 (semilla);

  float temperatura=Ti;
  float probabilidad;
  int compAgregar = int_rand(1 , 100);
  //int contadorA = 0;
  //int contadorE = 0;
  crear_solucion_aleatoria(&solucion_actual);
  mejor_solucion=solucion_actual;
  if(debug){
    cout<<" Paso \t T° \t Iteracion \t Solucion-Actual \t\t 2-opt \t Candidata-Solucion \t\t\t Delta_eval \t Probabilidad \t  Mejor-solucion"<<endl;   
    cout<<"-------------------------------------------------------------------------------------";
    cout<<"-------------------------------------------------------------------------------------"<<endl;
  }
  for(paso=0;paso<Mp;paso++){
    for(iteracion=0;iteracion<Mi;iteracion++){
      if(debug) cout<<paso<<"\t"<<temperatura<<"\t"<<iteracion<<"\t"<<solucion_actual;
      
      if(movimiento==0)SWAP(&solucion_actual,&candidata_solucion);
      else if(movimiento==1)DosOPT(&solucion_actual,&candidata_solucion);
    
      if(int_rand(1 , 100) < probAgregar){
        printf("HOLA-> ");
        //contadorA++;
        AgregarVisitaNodo(&candidata_solucion);
        //printf("%d ", contadorA);
      }
      else{
        printf("chao-> ");
        //contadorE++;
        EliminarVisitaNodo(&candidata_solucion);
        //printf("%d ", contadorE);
      }

      if(debug) cout<<"\t"<<candidata_solucion;
      if((candidata_solucion.aptitud)<(solucion_actual.aptitud)){
        solucion_actual=candidata_solucion;
        if(debug) cout<<"\t\t\t\t";
      }
      else{
        probabilidad=exp(((solucion_actual.aptitud-candidata_solucion.aptitud)/temperatura));
        if(debug) cout<<"\t"<<solucion_actual.aptitud-candidata_solucion.aptitud<<"\t\t"<<probabilidad;
	float aleatorio=drand48();
        if(aleatorio<probabilidad)
          solucion_actual=candidata_solucion;
      }
      if(solucion_actual.aptitud < mejor_solucion.aptitud)
        mejor_solucion = solucion_actual;
      if(debug){
        cout<<"\t"<<mejor_solucion;
        cout<<endl;
        getchar();
      }
    }
    temperatura=alpha*temperatura;
  }
  salir();
}

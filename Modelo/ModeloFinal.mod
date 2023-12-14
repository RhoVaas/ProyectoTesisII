#CONJUNTOS
set N;  	#Esquinas
#set Au; := {i in N, j in N}; 	#Arcos unidireccionales, se deben visitar obligatoriamente en el sentido dado.
#set Ab; := {i in N, j in N};		#Arcos bidireccionales, se pueden visitar solo en un sentido.
set I;      #Conjunto de posibles nodos iniciales
set F;      #Conjunto de posibles nodos finales

param D{i in N, j in N};	# Distancia en kilometros del arco entre el nodo i y el nodo j 

set Ab := {i in N, j in N: D[i,j]>0 and D[j,i]>0} ;
set Au := {i in N, j in N: (D[i,j]>0 and D[j,i]=0) or (D[j,i]>0 and D[i,j]=0)};
set NotAu := {i in N, j in N: D[j,i]>0 and D[i,j]=0};
set JustAu := Au diff NotAu;

set A := Au union Ab; 		#Todos los arcos

set NotI := N diff I;
set NotF := N diff F;

#VARIABLES
var X {(i,j) in A} integer; 	#Numero de veces que un camión va de i a j;
var Y {i in N} binary;      	#Variable binaria, verifica si un nodo es elegido como nodo inicial de la ruta
var Z {i in N} binary;      	#Variable binaria, verifica si un nodo es elegido como nodo final de la ruta

minimize FO:  sum {(i,j) in A} D[i,j]*X[i,j];

#RESTRICCIONES
#Todo arco unidireccional debe ser recorrido.
R11{(i,j) in JustAu}: X[i,j] >= 1;
R12{(i,j) in NotAu}: X[i,j] = 0;

#Todo arco bidireccional puede ser recorrido en un único sentido.
R2{(i,j) in Ab}: X[i,j]+ X[j,i] >= 1;
R53{(i,j) in Ab}: X[i,j]+ X[j,i] <= 2;

#R3{i in N, j in N}: sum{(i,j) in A} X[i,j]*D[i,j] = sum{(i,j) in A} X[j,i]*D[j,i];

#Controla la secuencia de visitas en las esquinas.
R3{i in N}: Y[i] + sum{(i,j) in A} X[j,i] = sum{(i,j) in A} X[i,j] + Z[i];

R41: sum{i in I} Y[i] = 1;
R42: sum{i in NotI} Y[i] = 0;


R51: sum{i in F} Z[i] = 1;
R52: sum{i in NotF} Z[i] = 0;




from pprint import pprint
from queue import Empty
from subprocess import call
import sys
import math
import random
import os
import matplotlib.pyplot as plt
import numpy as np
from math import dist, trunc
import time

############################################Creando matriz de adyacencia y otros valores####################################################################

#Función que calcula el % de arcos
def porcentajeArcos(nod,arc):
    porcArcos = float(arc*(nod * (nod-1)))
    return(porcArcos)

#Función que crea la matriz de ayacencia "vacía"
def matrizVacia(nod):
    M = np.zeros([nod,nod])
    for i in range(nod):
        for j in range(nod):
            M[i,j] = 0
    return(M)



nombreArchivo = sys.argv[1]
nodos = sys.argv[2]
arcos = sys.argv[3]
semilla = sys.argv[4]
random.seed(semilla)



print("**********************************************")
print("Tiempo de crear algunas matrices")
print("**********************************************")

while True:
    if(nodos.isnumeric() == True):    #Nos aseguramos de que los valores entregados por el ususario sean valores numericos
        nodos = int(nodos)                              #Se asegura de que la variable sea tipo int
        arcos = float(arcos)
        matrizAdj = matrizVacia(nodos)                  #Matriz de adjacencia
        resulArc = round(porcentajeArcos(nodos,arcos))         #Resultado de porcentajeArcos se entrega a resulArc
        print(" ")
        print("Matriz actual:")                         #Se imprime la matriz de adyacencia actual para ver su contenido
        pprint(matrizAdj)
        time.sleep(2.5)
        break
    else:
        print("")
        print("Por favor ingresar un valor numerico")


#Esta función se encarga de asignar valores a la matriz de adyacencia según los nodos elegidos aleatoriamente
arcosNarcos = 0
while (arcosNarcos < resulArc):
    desde = random.randint(0,nodos-1)
    hasta = random.randint(0,nodos-1)
    if (desde == hasta):
        matrizAdj[desde][hasta] = 0
    elif(matrizAdj[desde][hasta]  == 0):
       matrizAdj[desde][hasta] = 100
       arcosNarcos += 1
    

print(" ")
print("++++++++++++++++++++++++++++++++++Resumen+++++++++++++++++++++++++++++++++++++++++++")
print("Total de nodos: " , nodos)
print("Porcentaje de arcos: ", resulArc)
print(" ")
print("++++++++++++++++++++++++++++++++++Matriz de Adyacencia++++++++++++++++++++++++++++++")
print(" ")
pprint(matrizAdj)
print(" ")
print("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++")


######################################################Generando .dat####################################################################

#Se crea el archivo en la dirección correspondiente, modificar para probar
archivo = open(nombreArchivo,'a+')
print("Ruta del arhcivo: ", os.path.dirname(os.path.abspath(nombreArchivo)),"/",nombreArchivo)

archivo.writelines(["set N:="])       #Set de nodos N

#Función que agrega la cantidad de nodos al set o param en cuestión
def agregarNodos(nodos):
    for i in range(nodos):
        if i == nodos -1:
            archivo.writelines([" ", "{}".format(i), ";\n"])
            break
        archivo.writelines([" ", "{}".format(i)])
agregarNodos(nodos)

archivo.writelines(["set I:="])     #Set de posibles nodos iniciales I
truncado = trunc(nodos/4)           #Se trunca el valor de los nodos en 4 por considerarlo la cuarta parte del todo, obteniendo así los primeros valores que pueden ser considerados para ser nodos iniciales
agregarNodos(truncado)

archivo.writelines(["set F:="])     #Set de posibles nodos finales F
pivote = nodos - truncado
while pivote <= nodos:              #Esta función se coloca en los ultimos nodos y los elige como posibles nodos finales
    if pivote == nodos-1:
            archivo.writelines([" ", "{}".format(pivote), ";\n"])
            break
    archivo.writelines([" ", "{}".format(pivote)])
    pivote += 1


archivo.writelines(["param D:\n"])

#Función que crea la matriz de adyacencia estilo AMPL
for i in range(nodos):
    if i == nodos -1:
        archivo.writelines(["   ", "{}".format(i), " :=\n"])
        break
    archivo.writelines(["   ", "{}".format(i)])
for i in range(nodos):
    archivo.writelines(["{}".format(i)])
    for j in range(nodos):
        if i == nodos -1 and j == nodos -1:
            archivo.writelines(["   ", "{}".format(math.trunc(matrizAdj[i][j])), "\n;"])
            break
        elif j == nodos -1:
            archivo.writelines(["   ", "{}".format(math.trunc(matrizAdj[i][j])), "\n"])
            break
        archivo.writelines(["   ","{}".format(math.trunc(matrizAdj[i][j]))])

archivo.close()
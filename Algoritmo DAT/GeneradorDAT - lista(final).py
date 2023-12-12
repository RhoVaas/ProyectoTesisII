#El presente código tiene como finalidad el recibir como entrada un archivo csv y transformar este en un archiv .dat para
#su posterior uso con el algoritmo Transformador-ArcoANodo-V2. Se puede optimizar.
#Creado por Rodolfo Valentín

import csv
from pprint import pprint
from queue import Empty
from subprocess import call
#import sys
#import math
#import random
import os
import matplotlib.pyplot as plt
import numpy as np
from math import dist, trunc
import time
import re

archivo = 'd:/OneDrive - UNIVERSIDAD ANDRES BELLO/U of pain/6 ° Año/Proyecto de Tesis I/Códigos/Casos Reales/CasoRealPequenioRenca.csv'
casoRenca = open('CasoRealPequenioRenca.dat','a+')
print("Ruta del arhcivo: ", os.path.dirname(os.path.abspath('CasoRealPequenioRenca.dat')),"/",'CasoRealPequenioRenca.dat')

nodos = []
arcoList = []
contadorUni = 0
contadorBi = 0

with open(archivo, newline='') as File:  
    reader = csv.reader(File, delimiter=";")
    next(reader,None)
    for column in reader:                   
        if(column[97] not in nodos):    #se guardan todos los nodos en una lista
            nodos.append(column[97])
            if(column[96] not in nodos):
                nodos.append(column[96])

        elif(column[96] not in nodos):
            nodos.append(column[96])
        
        #Función que busca los valores de las columnas del archivo csv y las guarda en una lista

        if(column[20] == column[21]):       
            desde = column[97]
            hasta = column[96]
            palta = column[20].replace(",",".")
            lechuga = column[21].replace(",",".")
            arcoList.append(((desde,hasta),('Bidireccional',palta,lechuga)))
            contadorBi += 1

        elif(column[20] == -1):
            desde = column[97]
            hasta = column[96]
            palta = column[20].replace(",",".")
            lechuga = column[21].replace(",",".")
            arcoList.append(((desde,hasta),('Unidireccional',palta,lechuga)))
            contadorUni += 1

        else:
            desde = column[97]
            hasta = column[96]
            palta = column[20].replace(",",".")
            lechuga = column[21].replace(",",".")
            arcoList.append(((desde,hasta),('Unidireccional',palta,lechuga)))
            contadorUni += 1


    
    casoRenca.writelines(["set N:="])       #Set de nodos N
    #Función que agrega la cantidad de nodos al set o param en cuestión
    def agregarNodos(nodos):
        nodos = nodos
        cantidadNodos = len(nodos)
        cantidadNodos = int(cantidadNodos)
        for i in range(cantidadNodos):
            if i == cantidadNodos -1:
                casoRenca.writelines([" ", "{}".format(nodos[i]), ";\n"])
                break
            casoRenca.writelines([" ", "{}".format(nodos[i])])
    agregarNodos(nodos)

    #nodo de enrtada: 31837
    #nodo de salida: 31492
    casoRenca.writelines(["set I:= "])     #Set de posibles nodos finales F
    casoRenca.writelines(["{}".format(31837), "; \n"])

    casoRenca.writelines(["set F:= "])     #Set de posibles nodos finales F
    casoRenca.writelines(["{}".format(31492), "; \n"])


    casoRenca.writelines(["param D default 0:= \n"])
    cantidadNodos = len(nodos)
    cantidadNodos = int(cantidadNodos)

    for i in range(len(arcoList)):
            if i == len(arcoList) -1:
                if(arcoList[i][1][2] == '-1'):
                    casoRenca.writelines(["","{}".format(arcoList[i][0][0]), " ","{}".format(arcoList[i][0][1]), " ", "{:.2f}".format(float(arcoList[i][1][1])), "\n;"])
                    break
                elif(arcoList[i][1][1] == '-1'):
                    casoRenca.writelines(["","{}".format(arcoList[i][0][1]), " ","{}".format(arcoList[i][0][0]), " ", "{:.2f}".format(float(arcoList[i][1][2])), "\n;"])                
                    break
                casoRenca.writelines(["","{}".format(arcoList[i][0][0]), " ","{}".format(arcoList[i][0][1])," ", "{:.2f}".format(float(arcoList[i][1][1])), "\n"])
                casoRenca.writelines(["","{}".format(arcoList[i][0][1]), " ","{}".format(arcoList[i][0][0])," ", "{:.2f}".format(float(arcoList[i][1][2])), "\n;"])
                break

            if(arcoList[i][1][2] == '-1'):
                casoRenca.writelines(["","{}".format(arcoList[i][0][0]), " ","{}".format(arcoList[i][0][1]), " ", "{:.2f}".format(float(arcoList[i][1][1])), "\n"])

            elif(arcoList[i][1][1] == '-1'):
                casoRenca.writelines(["","{}".format(arcoList[i][0][1]), " ","{}".format(arcoList[i][0][0]), " ", "{:.2f}".format(float(arcoList[i][1][2])), "\n"])

            else:
                casoRenca.writelines(["","{}".format(arcoList[i][0][0]), " ","{}".format(arcoList[i][0][1])," ", "{:.2f}".format(float(arcoList[i][1][1])), "\n"])
                #casoRenca.writelines(["","{}".format(arcoList[i][0][1]), " ","{}".format(arcoList[i][0][0])," ", "{:.2f}".format(float(arcoList[i][1][2])), "\n"])


print("+++++++++++++++++++++++++++++++")
print("Completado")

#print(arcoList)
# print(arcoList[0])
# print(arcoList[0][1][1])
# print(arcoList[0][1][2])
# print(arcoList[i][1][1])
# print(arcoList[0][1][2])
print("total de nodos:" , len(nodos))
print("total de arcos:" , len(arcoList))
print("total de Unidireccionales:" , contadorUni)
print("total de Bidireccionales:" , contadorBi)
#print(nodos.index(17674))


casoRenca.close()
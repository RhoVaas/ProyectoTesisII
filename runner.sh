#!/bin/bash



n=0



for i in {0..9}

do

 ./SA Instances/NuevoCasoPequenioRenca.tsp TEST-prob30-12$i.txt 12$i 100 0.99 10000 10000 0 0 30

done



for i in {0..9}

do

 ./SA Instances/NuevoCasoPequenioRenca.tsp TEST-prob50-12$i.txt 12$i 100 0.99 10000 10000 0 0 50

done



for i in {0..9}

do

 ./SA Instances/NuevoCasoPequenioRenca.tsp TEST-prob70-12$i.txt 12$i 100 0.99 10000 10000 0 0 70

done





touch comparacion.txt

echo "                                 +++++Comparaciones de semillas+++++" >>comparacion.txt



for y in {0..9}

do

 echo "-------Semilla 12$y-------">> comparacion.txt

 for x in $( seq 30 20 70)

 do

  if [[ $x -eq 30 ]]

  then

   echo "                      " >> comparacion.txt

   echo "||Probabilidad de Agregar&Eliminar: 30||" >> comparacion.txt

   echo "                      " >> comparacion.txt



  elif [[ $x -eq 50 ]]

  then

   echo "                      " >> comparacion.txt

   echo "||Probabilidad de Agregar&Eliminar: 50||" >> comparacion.txt

   echo "                      " >> comparacion.txt



  else

   echo "                      " >> comparacion.txt

   echo "||Probabilidad de Agregar&Eliminar: 70||" >> comparacion.txt

   echo "                      " >> comparacion.txt

  fi

  

  echo " ">> comparacion.txt

  cat TEST-prob$x-12$y.txt >> comparacion.txt

  echo "----------------------------------------------------">> comparacion.txt

 done

  echo "//////////////////////////////////////////////////////">> comparacion.txt

  echo "                                                       ">> comparacion.txt

done
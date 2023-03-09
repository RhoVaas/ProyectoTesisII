#!/bin/bash



n=$((30+($RANDOM%69)))



for i in {0..9}

do

# for n in $( seq 30 20 70)

# do

  ./SA Instances/NuevoCasoPequenioRenca.tsp TESTPequenio-prob$n-12$i.txt 12$i 100 0.99 10000 10000 0 0 $n

# done

done



for i in {0..9}

do

# for n in $( seq 30 20 70)

# do

  ./SA Instances/NuevoCasoMedianoRenca.tsp TESTMediano-prob$n-12$i.txt 12$i 100 0.99 10000 10000 0 0 $n

 #done

done



for i in {0..9}

do

 #for n in $( seq 30 20 70)

 #do

  ./SA Instances/NuevoCasoGrandeRenca.tsp TESTGrande-prob$n-12$i.txt 12$i 100 0.99 10000 10000 0 0 $n

 #done

done



#calidad=0



touch comparacion.txt

echo "                                 +++++Comparaciones de Casos+++++" >>comparacion.txt



#for y in {0..9}

for x in {0..2}

do

# echo "-------Semilla 12$y-------">> comparacion.txt

# for x in $( seq 30 20 70)

 for y in {0..9}

 do

  if [[ $x -eq 0 ]]

  then

  

   while IFS= read -r line;

   do

    calidad1="$line"

   done < TESTPequenio-prob$n-12$y.txt

   

   echo "Caso de Prueba Pequenio | | Probabilidad: 12$y | | Semilla: $n || Parametro de iteraciones: 10000 || Calidad Final: $calidad1 " >> comparacion.txt

   echo "             "  >> comparacion.txt

   

  elif [[ $x -eq 1 ]]

  then

  

   while IFS= read -r line;

   do

     calidad2="$line"

   done < TESTMediano-prob$n-12$y.txt

   

   echo "Caso de Prueba Mediano | | Probabilidad: 12$y | | Semilla: $n || Parametro de iteraciones: 10000 || Calidad Final: $calidad2 " >> comparacion.txt

   echo "             "  >> comparacion.txt

   

  else

   

   while IFS= read -r line;

   do

    calidad3="$line"

   done < TESTGrande-prob$n-12$y.txt

   echo "Caso de Prueba Grande | | Probabilidad: 12$y | | Semilla: $n || Parametro de iteraciones: 10000 || Calidad Final: $calidad3 " >> comparacion.txt

   echo "             "  >> comparacion.txt

  fi

#  if [[ $x -eq 30 ]]

#  then

#   echo "                      " >> comparacion.txt

#   echo "||Probabilidad de Agregar&Eliminar: 30||" >> comparacion.txt

#   echo "                      " >> comparacion.txt



#  elif [[ $x -eq 50 ]]

#  then

#   echo "                      " >> comparacion.txt

#   echo "||Probabilidad de Agregar&Eliminar: 50||" >> comparacion.txt

#   echo "                      " >> comparacion.txt



#  else

#   echo "                      " >> comparacion.txt

#   echo "||Probabilidad de Agregar&Eliminar: 70||" >> comparacion.txt

#   echo "                      " >> comparacion.txt

#  fi



#  echo " ">> comparacion.txt

#  cat TESTPequenio-prob$x-12$y.txt >> comparacion.txt

#  echo "----------------------------------------------------">> comparacion.txt

# done

#  echo "//////////////////////////////////////////////////////">> comparacion.txt

#  echo "                                                       ">> comparacion.txt

 done

done


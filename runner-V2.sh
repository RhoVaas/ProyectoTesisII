#!/bin/bash



#n=$((30+($RANDOM%69)))



touch comparacion-V2.txt

#echo "                                 +++++Comparaciones de Casos+++++" >>comparacion.txt

echo "Caso de Prueba | Semilla | Probabilidad | Parametro de iteraciones | Calidad Final" >>comparacion-V2.txt



for i in {0..9}

do

 for n1 in $( seq 30 20 70)

 do

  ./SA Instances/NuevoCasoPequenioRenca.tsp TESTPequenio-prob$n1-12$i.txt 12$i 100 0.99 10000 10000 0 0 $n1

  while IFS= read -r line;

   do

    calidad1="$line"

   done < TESTPequenio-prob$n1-12$i.txt  

   echo " Pequenio | 12$i | $n1 | 10000 | $calidad1 " >> comparacion-V2.txt

 done   

done



for i in {0..9}

do

 for n2 in $( seq 30 20 70)

 do

  ./SA Instances/NuevoCasoMedianoRenca.tsp TESTMediano-prob$n2-12$i.txt 12$i 100 0.99 10000 10000 0 0 $n2

  while IFS= read -r line;

   do

     calidad2="$line"

   done < TESTMediano-prob$n2-12$i.txt

   echo " Mediano | 12$i | $n2 | 10000 | $calidad2 " >> comparacion-V2.txt

 done

done



for i in {0..9}

do

 for n3 in $( seq 30 20 70)

 do

  ./SA Instances/NuevoCasoGrandeRenca.tsp TESTGrande-prob$n3-12$i.txt 12$i 100 0.99 10000 10000 0 0 $n3

  while IFS= read -r line;

   do

    calidad3="$line"

   done < TESTGrande-prob$n3-12$i.txt

   echo " Grande | 12$i | $n3 | 10000 | $calidad3 " >> comparacion-V2.txt

 done

done



#calidad=0



#touch comparacion-V2.txt

#echo "                                 +++++Comparaciones de Casos+++++" >>comparacion.txt

#echo "Caso de Prueba | Probabilidad | Semilla | Parametro de iteraciones | Calidad Final" >>comparacion-V2.txt





#for y in {0..9}

#for x in {0..2}

#do

# echo "-------Semilla 12$y-------">> comparacion-V2.txt

# for x in $( seq 30 20 70)

# for y in {0..9}

# do

#  if [[ $x -eq 0 ]]

#  then

  

#   while IFS= read -r line;

#   do

#    calidad1="$line"

#   done < TESTPequenio-prob$n1-12$y.txt

   

#   echo " Pequenio | 12$y | $n1 | 10000 | $calidad1 " >> comparacion-V2.txt

#   echo "             "  >> comparacion.txt

   

#  elif [[ $x -eq 1 ]]

#  then

  

#   while IFS= read -r line;

#   do

#     calidad2="$line"

#   done < TESTMediano-prob$n2-12$y.txt

   

#   echo " Mediano | 12$y | $n2 | 10000 | $calidad2 " >> comparacion-V2.txt

#   echo "             "  >> comparacion.txt

   

#  else

   

#   while IFS= read -r line;

#   do

#    calidad3="$line"

#   done < TESTGrande-prob$n3-12$y.txt

#   echo " Grande | 12$y | $n3 | 10000 | $calidad3 " >> comparacion-V2.txt

#   echo "             "  >> comparacion.txt

#  fi



# done

#done


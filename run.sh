#!/bin/bash

./comp.sh

comp=""
comp2=""
rmv=""

dep () {
	if [ "$1" == "0" ]
		then
			comp+="lib/M_Objetos/$2.o "
	fi
	return 1
}

libcomp=0
criacomp=0
listcomp=0
manual=0
vetcomp=0
arqcomp=0
for argumento in $*
do
	if [ "$argumento" == "man" ]
	then
		echo "Exec Usage:"
		echo "-lib:"
		echo "	Basic ppm operations"
		echo "-list"
		echo "	Linked lists with points and colors"
		echo "-cria:"
		echo "	Drawing functions"
		echo "-fract:"
		echo "	Fractals Drawing"
		echo "-manip:"
		echo "	Effects and other image manipulations"
		echo "-vet:"
		echo "	Vectorial images manipulation"
		echo "-let"
		echo " Letters Drawing"
		echo "-arq:"
		echo "	Interface for file manipulation in arrays"
		echo "-compress:"
		echo "	Image compression"
		echo "man:"
		echo "	Manual"
		manual=1
		break
	fi
done
if [ "$manual" == "0" ]
then
	for argumento in $*
	do
		case $argumento in
			"-lib")
				dep $libcomp libppm
				libcomp=$?
			;;
			"-list")
				dep $libcomp libppm
				libcomp=$?
				dep $listcomp listappm
				listcomp=$?
			;;
			"-cria")
				dep $libcomp libppm
				libcomp=$?
				dep $listcomp listappm
				listcomp=$?
				dep $criacomp criappm
				criacomp=$?
			;;
			"-fract")
				dep $libcomp libppm
				libcomp=$?
				dep $criacomp criappm
				criacomp=$?
				dep $listcomp listappm
				listcomp=$?
				dep $vetcomp vetppm
				vetcomp=$?
				comp+="lib/M_Objetos/fractais.o "
			;;
			"-manip")
				dep $libcomp libppm
				libcomp=$?
				comp+="lib/M_Objetos/manipppm.o "
			;;
			"-vet")
				dep $libcomp libppm
				libcomp=$?
				dep $listcomp listappm
				listcomp=$?
				dep $criacomp criappm
				criacomp=$?
				comp+="lib/M_Objetos/vetppm.o "
			;;
			"-let")
				dep $libcomp libppm
				libcomp=$?
				dep $listcomp listappm
				listcomp=$?
				dep $criacomp criappm
				criacomp=$?
				comp+="lib/M_Objetos/letra.o "
			;;
			"-arq")
				dep $arqcomp arq
				arqcomp=$?
				comp+="lib/M_Objetos/arq.o "	
			;;
			"-compress")
				dep $libcomp libppm
				libcomp=$?
				dep $listcomp listappm
				listcomp=$?
				comp+="lib/M_Objetos/compress.o "
			;;
			*)
				gcc -c $argumento;
				comp2+=" ${argumento%.c}.o "
			;;
		esac
	done
	gcc -Wall -o exe $comp $comp2 -lm
	if [ $? -ne 0 ]
	then
	    exit 1
	fi
	gcc -Wall -Werror -o exe $comp $comp2 -lm
	if [ $? -ne 0 ]
	then
	    echo "Warnings:"
	    exit 2
	else
	  	rm $comp2
		mv exe tmp/
		./tmp/exe  
	fi
fi

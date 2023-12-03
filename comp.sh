#!/bin/bash
i=0
arr=()

h[0]="ppmlib"
h[1]="arq"

hmax=1
c[0]="libppm"
c[1]="manipppm"
c[2]="criappm"
c[3]="listappm"
c[4]="vetppm"
c[5]="fractais"
c[6]="letra"
c[7]="arq"
c[8]="compress"
cmax=8
cmin=$hmax+1

while IFS='' read -r line || [[ -n "$line" ]]; do
    arr[$i]=$line
    i=$((i+1))
done < "lib/lastmod"

cd lib
	if [ $(stat arq.h -c%Y) -ne ${arr[1]} ]; then
		gcc -c arq.c
		mv arq.o M_Objetos/
	fi
	if [ $(stat ppmlib.h -c%Y) -ne ${arr[0]} ]; then
		#compila todos os .c que dependem de ppmlib
		for (( i=0; i<=cmax; i++ ))
		do
			gcc -c ${c[$i]}.c
			mv ${c[$i]}.o M_Objetos/
		done
	else
		#compila arquivos com .c modificados, ou .o deletados
		for (( i=0; i<=cmax; i++ ))
		do
			if [ $(stat ${c[$i]}.c -c%Y) -ne ${arr[$i+$cmin]} ] || [ ! -e "M_Objetos/${c[$i]}.o" ]; then
				gcc -c ${c[$i]}.c
				mv ${c[$i]}.o M_Objetos/
			fi
		done
	fi

	#salva ultima vez que o arq foi modificado
	rm lastmod
	for (( i=0; i<=hmax; i++ ))
	do
		echo $(stat ${h[$i]}.h -c%Y) >> lastmod
	done
	for (( i=0; i<=cmax; i++ ))
	do
		echo $(stat ${c[$i]}.c -c%Y) >> lastmod
	done
cd ..
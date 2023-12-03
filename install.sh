#!/bin/bash

orig=.

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


if [ ! -z $1 ]; then
	caminho=$1/lib
	if [ ! -d $caminho ]; then
	mkdir $caminho
	fi
	#copia todos os .h e .c para o caminho do parametro
	for i in {0..$hmax}
	do
		cp lib/${h[$i]}.h $caminho
	done
	for i in {0..$cmax}
	do
		cp lib/${c[$i]}.c $caminho/
	done
else
	caminho=lib
fi

if [ ! -d $caminho/../imgs ]; then
	mkdir $caminho/../imgs
fi

if [ ! -d $caminho/M_Objetos ]; then
	mkdir $caminho/M_Objetos
fi

cd $caminho

#compila todos os .c e move para a pasta
for i in seq 0 $cmax
do
	gcc -c ${c[$i]}.c
	mv ${c[$i]}.o M_Objetos/
done

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

cd $orig

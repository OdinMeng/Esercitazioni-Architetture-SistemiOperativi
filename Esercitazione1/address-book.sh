#!/bin/bash

# MAPPE FLAG $mode
# 0. default (non settata)
# 1. view mode -> 0 argomenti
# 2. search mode -> 1 argomento
# 3. insert mode -> 0 argomenti
# 4. cancel mode -> 1 argomento

mode=0
filename="./test.csv" # TO-DO: DA MODIFICARE PER LA CONSEGNA!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


# ==== Mappatura argomenti =====
# Cerco se ho 1 argomento ed è o view o cancel
if [[ $# = "1" ]]
then
	if [[ $1 = "view" ]]
	then
		mode=1

	elif [[ $1 = "insert" ]]
	then
		mode=3
	else
		echo "Error: argomento fornito invalido"
	fi
fi

# Se ho argomento, cerco se è search o cancel
if [[ $# = "2" ]]
then
	if [[ $1 = "search" ]]
		then
		mode=2
	elif [[ $1 = "cancel" ]]
		then
		mode=3
	else
		echo "Error: argomento/i fornito invalido"
	fi
fi

# View mode: stampo contenuti ordinando le voci per mail
if (( $mode == 1 ))
then
	echo "View Mode" # -- TODO: Linea da rimuovere alla consegna
	# prima determino il numero di righe presenti nel file
	lines=$(cat $filename | wc -l | cut -d " " -f 1)
	lines=$(($lines-1))
	# stampo l'header
	cat $filename | head -n 1 | column -s "," -o " " -t

	# stampo il resto del file ordinato
	cat $filename | tail -n $lines | column -s "," -o " " -t | sort -k 4 -t " "
fi

# Search mode: cerco contenuto
if (( $mode == 2 ))
then
	echo "Search Mode" # -- TODO: LInea da rismudfdidfhbghy8srghu 9gbuis
	IFS=$'\n'
	header=$(cat $filename | head -n 1)
	lines=$(cat $filename | wc -l | cut -d " " -f 1)
	lines=$(($lines-1))
	found=0
	for line in $(cat $filename | tail -n $lines)
	do
		match=$(echo $line | grep $2 )
		if [[ ! -z $match ]]
		then
			found=1
			ctr=0 # Counter to keep count if it's name, surname, phgone ,dfbpìdf ijge sdgrhu0s9v
			IFS=","
			for arg in $match
			do
				if (( ctr == 0 ))
				then
					echo "Name: $arg"
				elif (( ctr == 1 ))
					then
					echo "Surname: $arg"
				elif (( ctr == 2 ))
					then
					echo "Phone: $arg"
				elif (( ctr == 3 ))
					then
					echo "Mail: $arg"
				elif (( ctr == 4 ))
					then
					echo "City: $arg"
				elif (( ctr == 5 ))
					then
					echo "Address: $arg"
				fi
				ctr=$(($ctr + 1))
			done
		fi
	done

	if (( $found == 0 ))
	then
		echo "Not Found"
	fi
fi

# Insert mode
if (( $mode == 3 ))
then

fi

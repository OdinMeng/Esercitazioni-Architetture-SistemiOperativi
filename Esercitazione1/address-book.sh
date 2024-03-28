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
	elif [[ $1 = "delete" ]]
		then
		mode=4
	else
		echo "Error: argomento/i fornito invalido"
	fi
fi

# View mode: stampo contenuti ordinando le voci per mail
if (( $mode == 1 ))
then
#	echo "View Mode" # -- TODO: Linea da rimuovere alla consegna
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
#	echo "Search Mode" -- TODO: LInea da rismudfdidfhbghy8srghu 9gbuis
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
			ctr=1 # Counter to keep count if it's name, surname, phgone ,dfbpìdf ijge sdgrhu0s9v
			IFS=","
			for arg in $match
			do
				if (( $ctr>6 ))
				then
					ctr=1
					echo -e
				fi
				pre=$(head -1 $filename | cut -f $ctr -d ",")
				echo ${pre^}: $arg # ^ per primo caratterer maiusc.
				ctr=$(( ctr + 1 ))
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
	error=0
#	echo "Insert Mode"
	# Raccolta informazioni
	# caso 1
	pre1=$(head -1 $filename | cut -f 1 -d ",")
	echo -n "${pre1^}: "
	read var
	insert="$var"

	# caso k-esimo per 2<=k<=n (n=numero campi)
	for i in 2 3 4 5 6
	do
		pre=$(head -1 $filename | cut -f $i -d ",")
		echo -n "${pre^}: "
		read var
		insert="$insert,$var"
	done

	# controllo mail
	mail=$(echo $insert | cut -f 4 -d ",")
	matches=$(grep $mail test.csv | cut -f 4 -d ",")
	for match in $matches
	do
		if [[ $mail = $match ]]
		then
			echo "Errore: Mail già presente"
			error=1
		fi
	done
	# inserimento, se tutto ok
	if (( $error == 0 ))
	then
		echo $insert >> $filename
		echo "Added"
	fi
fi

# Delete mode
if (( $mode == 4 ))
then
#	echo "Delete Mode"
	number=-1
	matches=$(grep -n $2 $filename)
	IFS=$'\n'
	for match in $matches
	do
		num=$(echo $match | cut -f 1 -d "," | cut -f 1 -d ":")
		mail=$(echo $match | cut -f 4 -d "," )
		if [[ $mail = $2 ]]
		then
			found=1
			number=$num
		fi
	done

	if (( $number != -1 ))
	then
#		echo $number
		sed -i "${number}d" $filename

	elif (( $number == -1 ))
	then
		echo "Cannot find any record"
	fi
fi

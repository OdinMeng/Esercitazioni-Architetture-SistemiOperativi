#!/bin/bash

if(( $# < 2 ))
then
	echo "Use: ./ <filepath> <command> <optional arguments>"
	exit -1
fi

# Set variables from arguments
filepath=$1
command=${@:2}

# Check if filepath exists, refers to a file and is readable
if [[ ! -a $filepath ]]
then
	echo "$filepath does not exist"
	exit -2
fi

if [[ -d $filepath ]]
then
	echo "$filepath does not refer to a file"
	exit -2
else
	if [[ ! -r $filepath ]]
	then
		echo "File $filepath not readable"
		exit -2
	fi

fi


# Starts doing magic

# Phase 0: create temporary work file
container_filepath="./container_engine_temp4"
mkdir $container_filepath

# Phase 1: create work environment for the container
IFS=$'\n'
for line in $(cat $filepath)
do
	origin=$(echo $line | cut -d " " -f 1)
	destination=$(echo $line | cut -d " " -f 2)

	# Case directory
	if [[ -d $origin ]]
	then

		mkdir $container_filepath$destination
		bindfs --no-allow-other $origin $container_filepath$destination
	fi

	# Case file
	if [[ -f $origin ]]
	then
		# Creates every directory necessary, and deletes the last one (which should be a file)
		mkdir -p $container_filepath$destination
		rmdir $container_filepath$destination
		chmod +x $container_filepath$destination

		touch $container_filepath$destination
		cp $origin $container_filepath$destination
	fi

done

# Phase 2: execute command
fakechroot chroot $container_filepath $command

#!/bin/bash
oldName=$1
newName=$(ls "$2" | grep $3 )
echo $oldName
echo $newName
cp $oldName $newName

#!/bin/dash

# The script has one argument - temeout( in sec. )
i=0
while [ $i -lt "100" ]
do
  echo $i
  sleep $1
  ./client 
  i=`expr $i + 1`
done

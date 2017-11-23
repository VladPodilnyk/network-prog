#!/bin/dash

# The script has one argument - timeout( in sec. )
i=0

if [ $1 -eq ""]; then
  timeout=1
else
  timeout=$1
fi

while [ $i -lt "100" ]
do
  echo $i
  sleep $timeout
  ./client 
  i=`expr $i + 1`
done
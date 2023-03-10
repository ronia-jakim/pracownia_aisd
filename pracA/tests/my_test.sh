S=0
M=0
B=0

for i in {1..100}
do
	echo Testing small: $i
	#/usr/bin/time -f "Running time: %E" ./prog < small/in/$i.in > TT
	echo `./zadA < ./small/in/$i.in` > 

    if 
done
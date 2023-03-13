S=0
M=0
B=0

g++ ../zadA.cpp -o zadA

for i in {1..100}
do
	#echo Testing small: $i
	#/usr/bin/time -f "Running time: %E" ./prog < small/in/$i.in > TT
	echo `./zadA < ./small/in/$i.in` > dupa
	if cmp ./dupa small/out/$i.out; then
		((S++))
		#echo "OK"
	else
		echo "DUPA $i"
	fi
done

for i in {1..100}
do
	#echo Testing medium: $i
	#/usr/bin/time -f "Running time: %E" ./prog < small/in/$i.in > TT
	echo `./zadA < ./med/in/$i.in` > dupa
	if cmp ./dupa med/out/$i.out; then
		((M++))
		#echo "OK"
	else
		echo "DUPA $i"
	fi
done

for i in {1..10}
do
	#echo Testing fat: $i
	#/usr/bin/time -f "Running time: %E" ./prog < small/in/$i.in > TT
	echo `./zadA < ./fat/in/$i.in` > dupa
	if cmp ./dupa fat/out/$i.out; then
		((B++))
		#echo "OK"
	else
		echo "DUPA $i"
	fi
done


echo "small tests: $S/100"
echo "medium tests: $M/100"
echo "fat tests: $B/10"
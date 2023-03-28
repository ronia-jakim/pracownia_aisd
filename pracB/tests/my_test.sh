T=0
S=0
M=0
B=0

g++ ../zadB.cpp -o zadB

for i in {1..1000}
do
    echo `./zadB < ./tiny/in/$i.in` > dupa
    if cmp ./dupa tiny/out/$i.out; then
        ((T++))
    else
        echo "DUPA $i"
    fi
done

for i in {1..100}
do
	#echo Testing small: $i
	#/usr/bin/time -f "Running time: %E" ./prog < small/in/$i.in > TT
	echo `./zadB < ./small/in/$i.in` > dupa
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
	echo `./zadB < ./med/in/$i.in` > dupa
	if cmp ./dupa med/out/$i.out; then
		((M++))
		#echo "OK"
	else
		echo "DUPA $i"
	fi
done

#for i in {1..10}
#do
	#echo Testing fat: $i
	#/usr/bin/time -f "Running time: %E" ./prog < small/in/$i.in > TT
#	echo `./zadB < ./fat/in/$i.in` > dupa
#	if cmp ./dupa fat/out/$i.out; then
#		((B++))
		#echo "OK"
#	else
#		echo "DUPA $i"
#	fi
#done


echo "tiny tests: $T/1000"
echo "small tests: $S/100"
echo "medium tests: $M/100"
echo "fat tests: $B/10"

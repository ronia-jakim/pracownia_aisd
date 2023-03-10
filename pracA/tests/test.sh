echo "1st argument is the name of testing program"
echo "if 2nd arg is YES then sanitizers wil be used"

echo "Compilation"
if [ "$2" = "YES" ]; then
	echo "With sanitizers"
	g++ -O3 -fsanitize=undefined -fsanitize=address $1 -o prog
else
	echo "Without sanitizers"
	g++ -O3 $1 -o prog
fi

S=0
M=0
B=0
for i in {1..100}
do
	echo Testing small: $i
	/usr/bin/time -f "Running time: %E" ./prog < small/in/$i.in > TT
	if cmp TT small/out/$i.out; then
		((S++))
		echo "OK"
	else
		echo "WA"
	fi
done
for i in {1..100}
do
	echo Testing medium: $i
	/usr/bin/time -f "Running time: %E" ./prog < med/in/$i.in > TT
	if cmp TT med/out/$i.out; then
		((M++))
		echo "OK"
	else
		echo "WA"
	fi
done
for i in {1..10}
do
	echo Testing fat: $i
	/usr/bin/time -f "Running time: %E" ./prog < fat/in/$i.in > TT
	if cmp TT fat/out/$i.out; then
		((B++))
		echo "OK"
	else
		echo "WA"
	fi
done
echo "Small  tests passed: $S/100"
echo "Medium tests passed: $M/100"
echo "Fat    tests passed: $B/10"
rm prog
rm TT

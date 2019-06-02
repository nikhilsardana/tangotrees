for i in {0..9}; do
	for j in {20..20}; do
		sed -i "s/1u << $((j-1))u/1u << ${j}u/g" RunTests.cpp
		make
		./run-tests > ../newtests/"test${i}${j}.txt"
	done
	sed -i "s/1u << 20u/1u << 19u/g" RunTests.cpp
done


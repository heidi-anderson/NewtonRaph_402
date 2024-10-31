bin/newtonRaph: newtonRaph.cpp
	g++ -I /usr/include/eigen3/ newtonRaph.cpp -o bin/newtonRaph

clean:
	rm bin/*
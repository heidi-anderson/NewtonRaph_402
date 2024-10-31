EIGEN = /usr/include/eigen3/

bin/newtonRaph: newtonRaph.cpp
	g++ -I ${EIGEN} newtonRaph.cpp -o bin/newtonRaph

clean:
	rm bin/*
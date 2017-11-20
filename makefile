a.out: Polynomial.o driver.o
	c++ Polynomial.o driver.o

Polynomial.o: Polynomial.cpp Polynomial.h
	c++ -c Polynomial.cpp

driver.o: driver.cpp Polynomial.o
	c++ -c driver.cpp


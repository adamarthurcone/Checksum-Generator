all: checksumTest

checksumTest: checksumTest.cpp
	gcc -o checksumTest checksumTest.cpp -lssl -lcrypto -lstdc++

clean:
	rm -fr checksumTest

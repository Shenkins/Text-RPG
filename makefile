all:
	g++ -std=c++0x final.cpp data.cpp -o final

clean:
	rm -rf *.o a.out final
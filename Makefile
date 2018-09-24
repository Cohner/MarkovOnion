all: markov

markov: ourMarkov.o
	g++ ourMarkov.o -o markov #-I ./twitcurl/ -L usr/lib/ -ltwitcurl

ourMarkov.o: ourMarkov.cpp
	g++ -c ourMarkov.cpp

clean:
	rm *.o markov
	rm Twitcurl
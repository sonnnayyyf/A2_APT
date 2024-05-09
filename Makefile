.default: all

all: ftt

clean:
	rm -rf ftt *.o *.dSYM

ftt: Coin.o Node.o LinkedList.o ftt.o Bank.o
	g++ -Wall -Werror -std=c++14 -g -O -o $@ $^

%.o: %.cpp
	g++ -Wall -Werror -std=c++14 -g -O -c $^

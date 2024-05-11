.default: all

all: ftt

clean:
	rm -rf ftt *.o *.dSYM

ftt: coin.o node.o linkedList.o ftt.o bank.o helper.o fileLoader.o
	g++ -Wall -Werror -std=c++14 -g -O -o $@ $^

%.o: %.cpp
	g++ -Wall -Werror -std=c++14 -g -O -c $^

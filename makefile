

server:
	g++ -g server.cpp -o server

client:
	g++ -g client.cpp -o client

test:
	g++ -g test.cpp -o test

clean:
	rm -rf server client test *.dSYM

cleanserver:
	rm -rf server server.dSYM

cleanclient:
	rm -rf client client.dSYM

cleantest:
	rm -rf test test.dSYM



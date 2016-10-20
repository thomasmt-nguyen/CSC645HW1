

server:
	g++ -g server.cpp -o server

client:
	g++ -g client.cpp -o client

clean:
	rm -rf server client *.dSYM

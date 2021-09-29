all:
	g++ ./tester.cpp -o ./tester
	./tester
compile:
	g++ ./tester.cpp -o ./tester
run:
	./tester
push:
	git push -u origin main
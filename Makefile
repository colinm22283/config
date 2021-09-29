all:
	g++ ./tester.cpp ./json.cpp -o ./tester
	./tester
compile:
	g++ ./tester.cpp ./json.cpp -o ./tester
run:
	./tester
push:
	git add json.cpp json.h tester.cpp Makefile README.md
	git commit -m "1.0"
	git push -u origin main
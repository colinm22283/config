all:
	g++ ./tester.cpp -o ./tester
	./tester
compile:
	g++ ./tester.cpp -o ./tester
run:
	./tester
push:
	git add ./config.h ./Makefile ./README.md
	git commit -m "1.0"
	git push -u origin main
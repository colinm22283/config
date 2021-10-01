all:
	g++ ./tester.cpp -o ./tester
	./tester
compile:
	g++ ./tester.cpp -o ./tester
run:
	./tester
push:
	git add ./config.h ./Makefile ./README.md ./demo.cfg
	git commit -m "1.1"
	git push -u origin main
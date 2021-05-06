all:
	@echo "Usage: "
	@echo "make compile path=[path to boost]"
	@echo "make benchmark test=[test file]"

compile:
	g++ -I $(path) -O3 src/main.cpp src/held-karp.cpp -o out/held-karp
	g++ -I $(path) -O3 src/main.cpp src/greedy.cpp -o out/greedy
	g++ -I $(path) -O3 src/main.cpp src/best-neighbor.cpp -o out/best-neighbor
	g++ -I $(path) -O3 src/main.cpp src/two-interchange.cpp -o out/two-interchange
	g++ -I $(path) -O3 src/main.cpp src/matching.cpp -o out/matching

benchmark:
	@echo -- $(test);
	@printf "held-karp      : "; time -f "  time: %es" out/held-karp < $(test);
	@printf "greedy         : "; time -f "  time: %es" out/greedy < $(test);
	@printf "best-neighbor  : "; time -f "  time: %es" out/best-neighbor < $(test);
	@printf "two-interchange: "; time -f "  time: %es" out/two-interchange < $(test);
	@printf "matching       : "; time -f "  time: %es" out/matching_test < $(test);
BOOST = /home/szymon/boost_1_76_0
BASE = src/main.cpp src/util.cpp

all:
	@echo "Usage: "
	@echo "make compile"
	@echo "make benchmark test=[test file]"

compile:
	@echo "Compiling... 1/9"
	@g++ -I $(BOOST) -O3 $(BASE) src/select/held-karp.cpp src/finish/none.cpp src/optimize/none.cpp -o out/held-karp
	@echo "Compiling... 2/9"
	@g++ -I $(BOOST) -O3 $(BASE) src/select/none.cpp src/finish/greedy.cpp src/optimize/none.cpp -o out/none_gree_none
	@echo "Compiling... 3/9"
	@g++ -I $(BOOST) -O3 $(BASE) src/select/none.cpp src/finish/greedy.cpp src/optimize/two-interchange.cpp -o out/none_gree_2int
	@echo "Compiling... 4/9"
	@g++ -I $(BOOST) -O3 $(BASE) src/select/none.cpp src/finish/best-neighbor.cpp src/optimize/none.cpp -o out/none_neig_none
	@echo "Compiling... 5/9"
	@g++ -I $(BOOST) -O3 $(BASE) src/select/none.cpp src/finish/best-neighbor.cpp src/optimize/two-interchange.cpp -o out/none_neig_2int
	@echo "Compiling... 6/9"
	@g++ -I $(BOOST) -O3 $(BASE) src/select/matching.cpp src/finish/greedy.cpp src/optimize/none.cpp -o out/matc_gree_none
	@echo "Compiling... 7/9"
	@g++ -I $(BOOST) -O3 $(BASE) src/select/matching.cpp src/finish/greedy.cpp src/optimize/two-interchange.cpp -o out/matc_gree_2int
	@echo "Compiling... 8/9"
	@g++ -I $(BOOST) -O3 $(BASE) src/select/matching.cpp src/finish/best-neighbor.cpp src/optimize/none.cpp -o out/matc_neig_none
	@echo "Compiling... 9/9"
	@g++ -I $(BOOST) -O3 $(BASE) src/select/matching.cpp src/finish/best-neighbor.cpp src/optimize/two-interchange.cpp -o out/matc_neig_2int

benchmark:
	@echo -- $(test);
	@printf "held-karp |               |                 : "; time -f "  time: %es" out/held-karp < $(test);
	@printf "          | greedy        |                 : "; time -f "  time: %es" out/none_gree_none < $(test);
	@printf "          | greedy        | two-interchange : "; time -f "  time: %es" out/none_gree_2int < $(test);
	@printf "          | best-neighbor |                 : "; time -f "  time: %es" out/none_neig_none < $(test);
	@printf "          | best-neighbor | two-interchange : "; time -f "  time: %es" out/none_neig_2int < $(test);
	@printf "matching  | greedy        |                 : "; time -f "  time: %es" out/matc_gree_none < $(test);
	@printf "matching  | greedy        | two-interchange : "; time -f "  time: %es" out/matc_gree_2int < $(test);
	@printf "matching  | best-neighbor |                 : "; time -f "  time: %es" out/matc_neig_none < $(test);
	@printf "matching  | best-neighbor | two-interchange : "; time -f "  time: %es" out/matc_neig_2int < $(test);
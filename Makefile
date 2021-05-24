BOOST = /home/szymon/boost_1_76_0
BASE = src/main.cpp src/util.cpp

OUT_COUNT = 13

# Usage:
# make
# make benchmark test=[test file]

all: out/held-karp \
	out/none_gree_none out/none_gree_2int \
	out/none_neig_none out/none_neig_2int \
	out/matc_gree_none out/matc_gree_2int out/matc_neig_none out/matc_neig_2int \
	out/serd_gree_none out/serd_gree_2int out/serd_neig_none out/serd_neig_2int

out/held-karp: $(BASE) src/select/held-karp.cpp src/finish/none.cpp src/optimize/none.cpp
	@echo "Compiling... 1/$(OUT_COUNT)"
	@g++ -I $(BOOST) -O3 $(BASE) src/select/held-karp.cpp src/finish/none.cpp src/optimize/none.cpp -o out/held-karp

out/none_gree_none: $(BASE) src/select/none.cpp src/finish/greedy.cpp src/optimize/none.cpp
	@echo "Compiling... 2/$(OUT_COUNT)"
	@g++ -I $(BOOST) -O3 $(BASE) src/select/none.cpp src/finish/greedy.cpp src/optimize/none.cpp -o out/none_gree_none

out/none_gree_2int: $(BASE) src/select/none.cpp src/finish/greedy.cpp src/optimize/two-interchange.cpp
	@echo "Compiling... 3/$(OUT_COUNT)"
	@g++ -I $(BOOST) -O3 $(BASE) src/select/none.cpp src/finish/greedy.cpp src/optimize/two-interchange.cpp -o out/none_gree_2int

out/none_neig_none: $(BASE) src/select/none.cpp src/finish/best-neighbor.cpp src/optimize/none.cpp
	@echo "Compiling... 4/$(OUT_COUNT)"
	@g++ -I $(BOOST) -O3 $(BASE) src/select/none.cpp src/finish/best-neighbor.cpp src/optimize/none.cpp -o out/none_neig_none

out/none_neig_2int: $(BASE) src/select/none.cpp src/finish/best-neighbor.cpp src/optimize/two-interchange.cpp
	@echo "Compiling... 5/$(OUT_COUNT)"
	@g++ -I $(BOOST) -O3 $(BASE) src/select/none.cpp src/finish/best-neighbor.cpp src/optimize/two-interchange.cpp -o out/none_neig_2int

out/matc_gree_none: $(BASE) src/select/matching.cpp src/finish/greedy.cpp src/optimize/none.cpp
	@echo "Compiling... 6/$(OUT_COUNT)"
	@g++ -I $(BOOST) -O3 $(BASE) src/select/matching.cpp src/finish/greedy.cpp src/optimize/none.cpp -o out/matc_gree_none

out/matc_gree_2int: $(BASE) src/select/matching.cpp src/finish/greedy.cpp src/optimize/two-interchange.cpp
	@echo "Compiling... 7/$(OUT_COUNT)"
	@g++ -I $(BOOST) -O3 $(BASE) src/select/matching.cpp src/finish/greedy.cpp src/optimize/two-interchange.cpp -o out/matc_gree_2int
	
out/matc_neig_none: $(BASE) src/select/matching.cpp src/finish/best-neighbor.cpp src/optimize/none.cpp
	@echo "Compiling... 8/$(OUT_COUNT)"
	@g++ -I $(BOOST) -O3 $(BASE) src/select/matching.cpp src/finish/best-neighbor.cpp src/optimize/none.cpp -o out/matc_neig_none
	
out/matc_neig_2int: $(BASE) src/select/matching.cpp src/finish/best-neighbor.cpp src/optimize/two-interchange.cpp
	@echo "Compiling... 9/$(OUT_COUNT)"
	@g++ -I $(BOOST) -O3 $(BASE) src/select/matching.cpp src/finish/best-neighbor.cpp src/optimize/two-interchange.cpp -o out/matc_neig_2int

out/serd_gree_none: $(BASE) src/select/serdyukov.cpp src/finish/greedy.cpp src/optimize/none.cpp
	@echo "Compiling... 10/$(OUT_COUNT)"
	@g++ -I $(BOOST) -O3 $(BASE) src/select/serdyukov.cpp src/finish/greedy.cpp src/optimize/none.cpp -o out/serd_gree_none

out/serd_gree_2int: $(BASE) src/select/serdyukov.cpp src/finish/greedy.cpp src/optimize/two-interchange.cpp
	@echo "Compiling... 11/$(OUT_COUNT)"
	@g++ -I $(BOOST) -O3 $(BASE) src/select/serdyukov.cpp src/finish/greedy.cpp src/optimize/two-interchange.cpp -o out/serd_gree_2int
	
out/serd_neig_none: $(BASE) src/select/serdyukov.cpp src/finish/best-neighbor.cpp src/optimize/none.cpp
	@echo "Compiling... 12/$(OUT_COUNT)"
	@g++ -I $(BOOST) -O3 $(BASE) src/select/serdyukov.cpp src/finish/best-neighbor.cpp src/optimize/none.cpp -o out/serd_neig_none
	
out/serd_neig_2int: $(BASE) src/select/serdyukov.cpp src/finish/best-neighbor.cpp src/optimize/two-interchange.cpp
	@echo "Compiling... 13/$(OUT_COUNT)"
	@g++ -I $(BOOST) -O3 $(BASE) src/select/serdyukov.cpp src/finish/best-neighbor.cpp src/optimize/two-interchange.cpp -o out/serd_neig_2int


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
	@printf "serdyukov | greedy        |                 : "; time -f "  time: %es" out/serd_gree_none < $(test);
	@printf "serdyukov | greedy        | two-interchange : "; time -f "  time: %es" out/serd_gree_2int < $(test);
	@printf "serdyukov | best-neighbor |                 : "; time -f "  time: %es" out/serd_neig_none < $(test);
	@printf "serdyukov | best-neighbor | two-interchange : "; time -f "  time: %es" out/serd_neig_2int < $(test);
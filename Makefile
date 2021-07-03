BOOST = /home/szymon/boost_1_76_0
FLAGS = -Isrc/other/ -I$(BOOST) -O3
LFLAGS = -pthread

.PHONY: dirs benchmark clean

all: dirs \
	out/alg/held-karp \
	out/alg/none_gree_none out/alg/none_gree_2int \
	out/alg/none_neig_none out/alg/none_neig_2int \
	out/alg/matc_gree_none out/alg/matc_gree_2int out/alg/matc_neig_none out/alg/matc_neig_2int \
	out/alg/serd_gree_none out/alg/serd_gree_2int out/alg/serd_neig_none out/alg/serd_neig_2int

dirs:
	@mkdir -p out/ out/other/ \
	out/select/ out/finish/ out/optimize/ \
	out/alg/

out/%.o: src/%.cpp
	@echo "-- $@"
	@mkdir -p out/
	@g++ $(FLAGS) -c -o $@ $<

out/other/%.o: src/other/%.cpp
	@echo "-- $@"
	@mkdir -p out/other/
	@g++ $(FLAGS) -c -o $@ $<

out/select/%.o: src/select/%.cpp
	@echo "-- $@"
	@mkdir -p out/select/
	@g++ $(FLAGS) -c -o $@ $<

out/finish/%.o: src/finish/%.cpp
	@echo "-- $@"
	@mkdir -p out/finish/
	@g++ $(FLAGS) -c -o $@ $<

out/optimize/%.o: src/optimize/%.cpp
	@echo "-- $@"
	@mkdir -p out/optimize/
	@g++ $(FLAGS) -c -o $@ $<


out/alg/held-karp: out/main.o out/other/util.o out/select/held-karp.o out/finish/none.o out/optimize/none.o
	@echo "--- $@"
	@g++ $(LFLAGS) out/main.o out/other/util.o out/select/held-karp.o out/finish/none.o out/optimize/none.o -o out/alg/held-karp

out/alg/none_gree_none: out/main.o out/other/util.o out/select/none.o out/finish/greedy.o out/optimize/none.o
	@echo "--- $@"
	@g++ $(LFLAGS) out/main.o out/other/util.o out/select/none.o out/finish/greedy.o out/optimize/none.o -o out/alg/none_gree_none

out/alg/none_gree_2int: out/main.o out/other/util.o out/select/none.o out/finish/greedy.o out/optimize/two-interchange.o
	@echo "--- $@"
	@g++ $(LFLAGS) out/main.o out/other/util.o out/select/none.o out/finish/greedy.o out/optimize/two-interchange.o -o out/alg/none_gree_2int

out/alg/none_neig_none: out/main.o out/other/util.o out/select/none.o out/finish/best-neighbor.o out/optimize/none.o
	@echo "--- $@"
	@g++ $(LFLAGS) out/main.o out/other/util.o out/select/none.o out/finish/best-neighbor.o out/optimize/none.o -o out/alg/none_neig_none

out/alg/none_neig_2int: out/main.o out/other/util.o out/select/none.o out/finish/best-neighbor.o out/optimize/two-interchange.o
	@echo "--- $@"
	@g++ $(LFLAGS) out/main.o out/other/util.o out/select/none.o out/finish/best-neighbor.o out/optimize/two-interchange.o -o out/alg/none_neig_2int

out/alg/matc_gree_none: out/main.o out/other/util.o out/other/maximum_weighted_2_matching.o out/select/matching.o out/finish/greedy.o out/optimize/none.o
	@echo "--- $@"
	@g++ $(LFLAGS) out/main.o out/other/util.o out/other/maximum_weighted_2_matching.o out/select/matching.o out/finish/greedy.o out/optimize/none.o -o out/alg/matc_gree_none

out/alg/matc_gree_2int: out/main.o out/other/util.o out/other/maximum_weighted_2_matching.o out/select/matching.o out/finish/greedy.o out/optimize/two-interchange.o
	@echo "--- $@"
	@g++ $(LFLAGS) out/main.o out/other/util.o out/other/maximum_weighted_2_matching.o out/select/matching.o out/finish/greedy.o out/optimize/two-interchange.o -o out/alg/matc_gree_2int

out/alg/matc_neig_none: out/main.o out/other/util.o out/other/maximum_weighted_2_matching.o out/select/matching.o out/finish/best-neighbor.o out/optimize/none.o
	@echo "--- $@"
	@g++ $(LFLAGS) out/main.o out/other/util.o out/other/maximum_weighted_2_matching.o out/select/matching.o out/finish/best-neighbor.o out/optimize/none.o -o out/alg/matc_neig_none

out/alg/matc_neig_2int: out/main.o out/other/util.o out/other/maximum_weighted_2_matching.o out/select/matching.o out/finish/best-neighbor.o out/optimize/two-interchange.o
	@echo "--- $@"
	@g++ $(LFLAGS) out/main.o out/other/util.o out/other/maximum_weighted_2_matching.o out/select/matching.o out/finish/best-neighbor.o out/optimize/two-interchange.o -o out/alg/matc_neig_2int

out/alg/serd_gree_none: out/main.o out/other/util.o out/other/maximum_weighted_2_matching.o out/select/serdyukov.o out/finish/greedy.o out/optimize/none.o
	@echo "--- $@"
	@g++ $(LFLAGS) out/main.o out/other/util.o out/other/maximum_weighted_2_matching.o out/select/serdyukov.o out/finish/greedy.o out/optimize/none.o -o out/alg/serd_gree_none

out/alg/serd_gree_2int: out/main.o out/other/util.o out/other/maximum_weighted_2_matching.o out/select/serdyukov.o out/finish/greedy.o out/optimize/two-interchange.o
	@echo "--- $@"
	@g++ $(LFLAGS) out/main.o out/other/util.o out/other/maximum_weighted_2_matching.o out/select/serdyukov.o out/finish/greedy.o out/optimize/two-interchange.o -o out/alg/serd_gree_2int

out/alg/serd_neig_none: out/main.o out/other/util.o out/other/maximum_weighted_2_matching.o out/select/serdyukov.o out/finish/best-neighbor.o out/optimize/none.o
	@echo "--- $@"
	@g++ $(LFLAGS) out/main.o out/other/util.o out/other/maximum_weighted_2_matching.o out/select/serdyukov.o out/finish/best-neighbor.o out/optimize/none.o -o out/alg/serd_neig_none

out/alg/serd_neig_2int: out/main.o out/other/util.o out/other/maximum_weighted_2_matching.o out/select/serdyukov.o out/finish/best-neighbor.o out/optimize/two-interchange.o
	@echo "--- $@"
	@g++ $(LFLAGS) out/main.o out/other/util.o out/other/maximum_weighted_2_matching.o out/select/serdyukov.o out/finish/best-neighbor.o out/optimize/two-interchange.o -o out/alg/serd_neig_2int


benchmark:
	@echo -- $(path);
	@printf "held-karp |               |                 : "; time -f "  time: %es" out/alg/held-karp $(path);
	@printf "          | greedy        |                 : "; time -f "  time: %es" out/alg/none_gree_none $(path);
	@printf "          | greedy        | two-interchange : "; time -f "  time: %es" out/alg/none_gree_2int $(path);
	@printf "          | best-neighbor |                 : "; time -f "  time: %es" out/alg/none_neig_none $(path);
	@printf "          | best-neighbor | two-interchange : "; time -f "  time: %es" out/alg/none_neig_2int $(path);
	@printf "matching  | greedy        |                 : "; time -f "  time: %es" out/alg/matc_gree_none $(path);
	@printf "matching  | greedy        | two-interchange : "; time -f "  time: %es" out/alg/matc_gree_2int $(path);
	@printf "matching  | best-neighbor |                 : "; time -f "  time: %es" out/alg/matc_neig_none $(path);
	@printf "matching  | best-neighbor | two-interchange : "; time -f "  time: %es" out/alg/matc_neig_2int $(path);
	@printf "serdyukov | greedy        |                 : "; time -f "  time: %es" out/alg/serd_gree_none $(path);
	@printf "serdyukov | greedy        | two-interchange : "; time -f "  time: %es" out/alg/serd_gree_2int $(path);
	@printf "serdyukov | best-neighbor |                 : "; time -f "  time: %es" out/alg/serd_neig_none $(path);
	@printf "serdyukov | best-neighbor | two-interchange : "; time -f "  time: %es" out/alg/serd_neig_2int $(path);

clean:
	@rm -rf out/
GPP = g++
CPPFLAGS = -g

all: bin/image_disjoint_sets

bin/image_disjoint_sets: obj/image_disjoint_sets.o
	$(GPP) $(CPPFLAGS) -o bin/image_disjoint_sets obj/image_disjoint_sets.o

obj/image_disjoint_sets.o: src/image_disjoint_sets.cpp src/disjoint_set.cpp
	$(GPP) $(CPPFLAGS) -o obj/image_disjoint_sets.o -c src/image_disjoint_sets.cpp
#include <iostream>
#include "disjoint_set.cpp"

void print_vectors(const disjoint_set, int);

int main(int argc, char ** argv) {
    int size = 6;

    disjoint_set ds(size);
    
    print_vectors(ds, size);

    std::cout << "ds.join_by_size(1, 0);\n";
    ds.join_by_size(1, 0);
    
    print_vectors(ds, size);

    std::cout << "ds.join_by_size(1, 3);\n";
    ds.join_by_size(1, 3);
    
    print_vectors(ds, size);

    std::cout << "ds.join_by_size(4, 5);\n";
    ds.join_by_size(4, 5);
    
    print_vectors(ds, size);

    std::cout << "ds.join_by_size(2, 4);\n";
    ds.join_by_size(2, 4);
    
    print_vectors(ds, size);
    
    std::cout << "ds.join_by_rank(1, 2);\n";
    ds.join_by_rank(1, 2);
    
    print_vectors(ds, size);

    return 0;
}

void print_vectors(const disjoint_set ds, int size) {
    std::cout << "Sets\n";
    for (int i = 0; i < size; i++) {
        std::cout << ds.sets[i];
        if (i+1 < size)
            std::cout << ", ";
    }
    std::cout << "\n";

    std::cout << "Sizes\n";
    for (int i = 0; i < size; i++) {
        std::cout << ds.sizes[i];
        if (i+1 < size)
            std::cout << ", ";
    }
    std::cout << "\n";

    std::cout << "Ranks\n";
    for (int i = 0; i < size; i++) {
        std::cout << ds.ranks[i];
        if (i+1 < size)
            std::cout << ", ";
    }
    std::cout << "\n";
}
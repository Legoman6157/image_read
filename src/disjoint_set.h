#pragma once

#include <vector>

class disjoint_set {
    private:

    public:
        std::vector<int> sets;
        std::vector<int> sizes;
        std::vector<int> ranks;
        disjoint_set();
        disjoint_set(int n);
        void set_size(int);
        int find(int);
        int join_by_rank(int, int);
        int join_by_size(int, int);
};
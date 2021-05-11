#include "disjoint_set.h"

disjoint_set::disjoint_set() {}

disjoint_set::disjoint_set(int size) {
    this->sets.resize(size);
    this->ranks.resize(size);
    this->sizes.resize(size);
    for (int i = 0; i < size; i++) {
        sets[i] = i;
        sizes[i] = 1;
        ranks[i] = 1;
    }
}

void disjoint_set::set_size(int size) {
    this->sets.resize(size);
    for (int i = 0; i < size; i++) {
        sets[i] = i;
    }
}

int disjoint_set::find(int n) {
    if (n != this->sets[n])
        return find(this->sets[n]);
    return n;
}

int disjoint_set::join_by_rank(int n1, int n2) {
    int n1_f = find(n1),
        n2_f = find(n2);

    if (n1_f == n2_f)
        return n1_f;
    
    int p,
        c;

    if (this->ranks[n1_f] < this->ranks[n2_f]) {
        p = n2_f;
        c = n1_f;
    } else {
        p = n1_f;
        c = n2_f;
    }

    if (this->ranks[p] == this->ranks[c])
        this->ranks[p]++;

    this->sizes[p] += this->sizes[c];

    sets[c] = p;
    return p;
}

int disjoint_set::join_by_size(int n1, int n2) {
    int n1_f = find(n1),
        n2_f = find(n2);

    if (n1_f == n2_f)
        return n1_f;
    
    int p,
        c;

    if (this->sizes[n1_f] < this->sizes[n2_f]) {
        p = n2_f;
        c = n1_f;
    } else {
        p = n1_f;
        c = n2_f;
    }

    if (this->ranks[p] <= this->ranks[c]) {
        this->ranks[p] = this->ranks[c] + 1;
    }

    this->sizes[p] += this->sizes[c];

    sets[c] = p;
    return p;
}
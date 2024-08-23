#include "RegAlloc.hh"

RegAlloc::RegAlloc() {
    for (int i = 0; i < 7; i++) {
        this->reg[i] = true;
    }
}

RegAlloc::~RegAlloc() {}

int RegAlloc::newReg() {
    for (int i = 0; i < 7; i++) {
        if (this->reg[i]) {
            this->reg[i] = false;
            return i;
        }
    }
    return -1;
}

void RegAlloc::freeReg(int r) {
    this->reg[r] = true;
}

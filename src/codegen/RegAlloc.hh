#ifndef REG_ALLOC_H
#define REG_ALLOC_H

class RegAlloc {
private:
    bool reg[7];
public:
    RegAlloc();
    ~RegAlloc();
    int newReg();
    void freeReg(int r);
};

#endif
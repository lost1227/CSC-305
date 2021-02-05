#ifndef BASIC_KEY_H
#define BASIC_KEY_H

#include "Board.h"
#include "MyLib.h"
#include <typeinfo>

template<int size>
class BasicKey : public Board::Key {
public:
    bool operator==(const Board::Key &) const override;
    bool operator<(const Board::Key &) const override;

    std::istream &Read(std::istream &) override;
    std::ostream &Write(std::ostream &) const override;

    const Class *GetClass() const override;

    uint vals [size];
};

template<int size>
bool BasicKey<size>::operator==(const Board::Key &other) const {
    const BasicKey<size> *oPtr = dynamic_cast<const BasicKey<size>*>(&other);
    assert(oPtr != nullptr);
    for(int i = 0; i < size; i++) {
        if(vals[i] != oPtr->vals[i])
            return false;
    }
    return true;
}

template<int size>
bool BasicKey<size>::operator<(const Board::Key &other) const {
    const BasicKey<size> *oPtr = dynamic_cast<const BasicKey<size>*>(&other);
    assert(oPtr != nullptr);
    for(int i = 0; i < size; i++) {
        if(vals[i] != oPtr->vals[i])
            return vals[i] < oPtr->vals[i];
    }
    return false;
}

template<int size>
std::istream &BasicKey<size>::Read(std::istream &stream) {
    // FIXME: implement this stub
    throw BaseException("BasicKey<size>::Read is not implemented");
    return stream;
}

template<int size>
std::ostream &BasicKey<size>::Write(std::ostream &stream) const {
    // FIXME: implement this stub
    throw BaseException("BasicKey<size>::Write is not implemented");
    return stream;
}

template<int size>
const Class *BasicKey<size>::GetClass() const {
    // FIXME: implement this stub
    throw BaseException("BasicKey<size>::GetClass is not implemented");
    return nullptr;
}


#endif

#ifndef BASIC_KEY_H
#define BASIC_KEY_H

#include <typeinfo>

#include "Board.h"
#include "MyLib.h"

template<int size>
class BasicKey : public Board::Key {
public:
   bool operator==(const Board::Key &) const override;
   bool operator<(const Board::Key &) const override;

   std::istream &Read(std::istream &) override;
   std::ostream &Write(std::ostream &) const override;

   const Class *GetClass() const override { return &mClass; }

   static Object *Create() { return new BasicKey<size>(); }

   ulong vals[size];

   static Class mClass;
};

template<int size>
bool BasicKey<size>::operator==(const Board::Key &other) const {
   const BasicKey<size> *oPtr = dynamic_cast<const BasicKey<size> *>(&other);
   assert(oPtr != nullptr);
   for (int i = 0; i < size; i++) {
      if (vals[i] != oPtr->vals[i])
         return false;
   }
   return true;
}

template<int size>
bool BasicKey<size>::operator<(const Board::Key &other) const {
   const BasicKey<size> *oPtr = dynamic_cast<const BasicKey<size> *>(&other);
   assert(oPtr != nullptr);
   for (int i = 0; i < size; i++) {
      if (vals[i] != oPtr->vals[i])
         return vals[i] < oPtr->vals[i];
   }
   return false;
}

template<int size>
std::istream &BasicKey<size>::Read(std::istream &stream) {
   ulong readVal;
   for (auto &val : vals) {
      stream.read((char *)&readVal, sizeof(readVal));
      readVal = EndianXfer((uint)readVal);
      val = readVal;
   }
   return stream;
}

template<int size>
std::ostream &BasicKey<size>::Write(std::ostream &stream) const {
   ulong writeVal;
   for (auto &val : vals) {
      writeVal = val;
      writeVal = EndianXfer((uint)writeVal);
      stream.write((char *)&writeVal, sizeof(writeVal));
   }
   return stream;
}

template<int size>
Class BasicKey<size>::mClass(
   FString("BasicKey<%d>", size), BasicKey<size>::Create);

#endif

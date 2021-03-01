#include "C4Pop10Move.h"

#include <cassert>
#include <regex>
#include <sstream>

using namespace std;

vector<unique_ptr<C4Pop10Move, FreeListDeleter>> C4Pop10Move::mFreeList;

C4Pop10Move::C4Pop10Move(MoveType mvType, int srcCol, int dstCol)
 : mType(mvType), mSrcCol(srcCol), mDstCol(dstCol), mDidFillCol{false} {
}

C4Pop10Move::~C4Pop10Move() {
}

unique_ptr<Board::Move> C4Pop10Move::Clone() const {
   C4Pop10Move *move = new C4Pop10Move(*this);

   return unique_ptr<Board::Move>(move);
}

bool C4Pop10Move::operator==(const Board::Move &oth) const {
   const C4Pop10Move &othMov = dynamic_cast<const C4Pop10Move &>(oth);

   return mType == othMov.mType && mSrcCol == othMov.mSrcCol
    && mDstCol == othMov.mDstCol;
}

bool C4Pop10Move::operator<(const Board::Move &oth) const {
   const C4Pop10Move &c4Oth = dynamic_cast<const C4Pop10Move &>(oth);

   if (mType != c4Oth.mType)
      return mType < c4Oth.mType;
   if (mSrcCol != c4Oth.mSrcCol)
      return mSrcCol < c4Oth.mSrcCol;
   return mDstCol < c4Oth.mDstCol;
}

inline char C4Pop10Move::colToChar(const int col) const {
   return (char)('A' + col);
}

inline int C4Pop10Move::colStrToInt(const string &str) const {
   assert(str.length() == 1);
   return str[0] - 'A';
}

C4Pop10Move::operator string() const {
   ostringstream out;
   switch (mType) {
      case MoveType::PASS:
         out << "Pass";
         break;
      case MoveType::PLACE:
         out << "Place " << colToChar(mDstCol);
         break;
      case MoveType::KEEP:
         out << "Keep " << colToChar(mSrcCol);
         break;
      case MoveType::TAKE_PLACE:
         out << "Take " << colToChar(mSrcCol) << " place "
          << colToChar(mDstCol);
         break;
      default:
         assert(false);
   }

   return out.str();
}

static constexpr int IDX_MV_TYPE_PASS = 1, IDX_MV_TYPE_PLACE = 2,
 IDX_MV_TYPE_KEEP = 4, IDX_MV_TYPE_TAKE = 6;
static constexpr int IDX_PLACE_DST = 3, IDX_KEEP_SRC = 5,
 IDX_TAKE_SRC = 7, IDX_TAKE_DST = 8;

void C4Pop10Move::operator=(const string &src) {
   static regex moveMatcher(R"(^ *(?:(Pass))"
    R"(|(Place) +([A-G])|(Keep) +([A-G]))"
    R"(|(Take) +([A-G]) +place +([A-G])) *$)");
   smatch matches;

   if (!regex_match(src, matches, moveMatcher))
      throw BaseException("Bad C4Pop10 move: " + src);

   if (matches[IDX_MV_TYPE_PASS] == "Pass") {
      mType = MoveType::PASS;
      mSrcCol = -1;
      mDstCol = -1;
   } else if (matches[IDX_MV_TYPE_PLACE] == "Place") {
      mType = MoveType::PLACE;
      mSrcCol = -1;
      mDstCol = colStrToInt(matches[IDX_PLACE_DST]);
   } else if (matches[IDX_MV_TYPE_KEEP] == "Keep") {
      mType = MoveType::KEEP;
      mSrcCol = colStrToInt(matches[IDX_KEEP_SRC]);
      mDstCol = -1;
   } else {
      assert(matches[IDX_MV_TYPE_TAKE] == "Take");
      mType = MoveType::TAKE_PLACE;
      mSrcCol = colStrToInt(matches[IDX_TAKE_SRC]);
      mDstCol = colStrToInt(matches[IDX_TAKE_DST]);
   }
}

void C4Pop10Move::operator delete(void *p) {
   unique_ptr<C4Pop10Move, FreeListDeleter> ptr((C4Pop10Move *)p);

   mFreeList.push_back(move(ptr));
   mOutstanding--;
}

void *C4Pop10Move::operator new(size_t sz) {
   void *tmp;

   if (mFreeList.size()) {
      tmp = (void *)mFreeList.back().release();
      mFreeList.pop_back();
   } else {
      tmp = ::new char[sz];
   }

   mOutstanding++;
   return tmp;
}

istream &C4Pop10Move::Read(istream &in) {
   char didFillCol;

   in.read((char *)&mType, sizeof(mType));
   in.read(&mSrcCol, sizeof(mSrcCol));
   in.read(&mDstCol, sizeof(mDstCol));
   in.read(&didFillCol, sizeof(didFillCol));
   mDidFillCol = (bool)didFillCol;
   return in;
}

ostream &C4Pop10Move::Write(ostream &out) const {
   char didFillCol = (char)mDidFillCol;

   out.write((char *)&mType, sizeof(mType));
   out.write(&mSrcCol, sizeof(mSrcCol));
   out.write(&mDstCol, sizeof(mDstCol));
   out.write(&didFillCol, sizeof(didFillCol));

   return out;
}

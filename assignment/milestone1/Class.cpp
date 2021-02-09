#include "Class.h"

#include <string>

using namespace std;

Class *Class::mClsHead{nullptr};

Class::Class(const std::string &n, Object *(*c)())
    : mName(n)
    , mCreate(c)
    , mNext{mClsHead}
{
    mClsHead = this;
}

Object *Class::NewInstance() const {
    return (*mCreate)();
}

const Class *Class::ForName(const std::string &name) {
    Class *curr = mClsHead;
    while(curr && !(curr->mName == name))
        curr = curr->mNext;
    return curr;
}

BoardClass *BoardClass::mBrdClsHead{nullptr};

BoardClass::BoardClass(
    const std::string &n, Object *(*c)(),
    const std::string &fn,
    const Class *viewClass,
    const Class *dlgClass,
    void (*setOptions)(const void *),
    void *(*getOptions)(),
    bool useXPos, int minPlayers
)
    : Class(n, c)
    , mFriendlyName(fn)
    , mViewClass{viewClass}
    , mDlgClass{dlgClass}
    , mSetOptions{setOptions}
    , mGetOptions{getOptions}
    , mUseXPos{useXPos}
    , mMinPlayers{minPlayers}
    , mNext{mBrdClsHead}
{
    mBrdClsHead = this;
}

void BoardClass::SetOptions(void *options) const {
    (*mSetOptions)(options);
}

void *BoardClass::GetOptions() const {
    return (*mGetOptions)();
}

vector<const BoardClass *> BoardClass::GetAllClasses() {
    vector<const BoardClass *> classes;
    BoardClass *curr = mBrdClsHead;
    while(curr) {
        classes.push_back(curr);
        curr = curr->mNext;
    }
    return classes;
}
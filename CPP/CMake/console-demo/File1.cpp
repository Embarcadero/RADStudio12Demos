#include <vcl.h>
#include <tchar.h>
#include <stdio.h>

class TDummy : public System::TObject {
private:
  int FValue;
public:
  __fastcall TDummy(int AValue);
  int __fastcall getValue() const;
};

__fastcall TDummy::TDummy(int AValue) : FValue(AValue) {}

int __fastcall TDummy::getValue() const {
  return FValue;
}

int GetTestNum() {
  auto *d = new TDummy(100);
  int res = d->getValue();
  delete d;
  return res;
}

int _tmain(int argc, _TCHAR* argv[])
{
  printf("%d\n", GetTestNum());
}

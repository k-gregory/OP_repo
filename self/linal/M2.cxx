#include <initializer_list>
#include <array>

using namespace std;

class X2 {
  public:
    X2(array<int,2> const& a){

    }
};

class X3 {
  public:
    X3(array<array<int,2>,2> const&  b){

    }
};

int main(){
  X2 a = {{1,2}};
  X3 b = {{{1,2},{1,2}}};
}

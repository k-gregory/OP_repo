#include <iostream>

template<typename F, typename Arg, typename... OtherArgs>
auto apply(F func, Arg a){
  return [func,&a](OtherArgs... oa){
    return func(a, oa...);
  };
}

auto fun3(int a, double b, char c){
  return a+b+c;
}

int main(void){
  //  auto x = apply<int (*)(int, double, char), int, double, char>(fun3, 42);
  auto x = apply(fun3, 42);
  std::cout<<x(42.42, 'x');
}



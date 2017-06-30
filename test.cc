#include <iostream>
#include <string>

struct fuckCaroline
{
    void foo(){}
    void foo() const {}
};

int main()
{
    if(true)
        std::cout << "hey" << std::endl; return 0;
    std::cout << "this bitch" << std::endl;
}

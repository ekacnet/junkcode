#include <stdio.h>
#include <string>

int main(void)
{
    std::string *s =new std::string("my string");
    fprintf(stderr, "s = %s", s->c_str());
    void *p=s;
    delete (std::string*)((long)p+1);

    return 0;
}

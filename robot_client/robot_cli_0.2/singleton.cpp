#include "singleton.h"

singleton *p_instance = 0;

singleton::singleton()
{

}

singleton *singleton::instance()
{
    if(!p_instance) p_instance = new singleton();
    return p_instance;
}

int singleton::GetValue()
{
    return p_value;
}
void singleton::SetValue(int value)
{
    p_value = value;
}

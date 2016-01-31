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

int singleton::GetPortValue()
{
    return port_value;
}
void singleton::SetPortValue(int value)
{
    port_value = value;
}

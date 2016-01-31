#ifndef SINGLETON
#define SINGLETON

class singleton
{
private:
    singleton();
    int port_value;
public:
    static singleton * instance();
    int  GetPortValue();
    void SetPortValue(int value);
};

#endif // SINGLETON


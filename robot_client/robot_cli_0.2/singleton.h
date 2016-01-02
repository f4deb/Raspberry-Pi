#ifndef SINGLETON
#define SINGLETON

class singleton
{
private:
    singleton();
    int p_value;
public:
    static singleton * instance();
    int  GetValue();
    void SetValue(int value);
};

#endif // SINGLETON


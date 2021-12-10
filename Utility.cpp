#include "Utility.h"
#include <time.h>
#include <string>
using namespace std;

string getTime()
{
    struct tm newtime;
    __time32_t aclock;

    char buffer[26];
    errno_t errNum;
    _time32(&aclock);
    _localtime32_s(&newtime, &aclock);
    errNum = asctime_s(buffer, 26, &newtime);
    string buff(buffer);
    return buff;
}

bool isHaveIntersection(int aStart, int aEnd, int bStart, int bEnd)
{
    if (aEnd < bStart || bEnd < aStart)
        return false;
    return true;
}

int getRandomInt(int min, int max)
{
    random_device truly_random_seed;
    default_random_engine dank_engine(truly_random_seed());
    uniform_int_distribution<int> distribution(min, max);

    int random_number = distribution(dank_engine);

    return random_number;
}

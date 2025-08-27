#include "CCCML.h"
#include <vector>
#include <algorithm>
using namespace std;
const string CCCML::JOIN_STRING = "~_~_~";
void CCCML::addgetParticles(const string & key1,
                                const string &key2,
                                double cohesion)
{
    vector<string> keys;  
    keys.push_back(key1);
    keys.push_back(key2);

	sort(keys.begin(), keys.end());

    string nKey = keys[0] + JOIN_STRING + keys[1];
    insert( pair<string, double>(nKey, cohesion) );
}

double CCCML::getgetParticles(const string & key1,
                                  const string &key2)
{
    vector<string> keys;  
    keys.push_back(key1);
    keys.push_back(key2);
    sort(keys.begin(), keys.end());

    string nKey = keys[0] + JOIN_STRING + keys[1];

    map<string, double>::iterator it;
    if((it = find(nKey)) != end() )
        return it->second;
    else
        return 0.0;
}
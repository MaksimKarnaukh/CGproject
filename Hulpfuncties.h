//
// Created by centu on 19/02/2021.
//

#ifndef ENGINE_HULPFUNCTIES_H
#define ENGINE_HULPFUNCTIES_H
#include <cmath>
#include <string>
#include <vector>
using namespace  std;

inline int roundToInt(double d) {
    return static_cast<int>(std::round(d));
}

// functie compMap
// gebruikt als comparator in een sort functie
inline bool compMap(pair<string, double>& a,
                    pair<string, double>& b) {
    return a.second < b.second;
}

#endif //ENGINE_HULPFUNCTIES_H

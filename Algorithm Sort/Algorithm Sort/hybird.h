#pragma once
#ifndef hybird_H
#define hybird_H

#include <vector>

namespace pt {

    enum Region {
        LEFT,
        MID,
        RIGHT
    };

    // Overload 1: Sort in-place
    void _ptsort_recursive(std::vector<int>& arr);



#endif // hybird_H
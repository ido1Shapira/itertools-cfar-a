#include "doctest.h"
#include <iostream>
#include <vector>

#include "range.hpp"
#include "accumulate.hpp"
#include "filterfalse.hpp"
#include "compress.hpp"

using namespace itertools;
using namespace std;

// Id of collaborators 208825539 207950577

TEST_CASE("####  range:  ####") {
        vector<int> v(100);
        for(int i=0;i<101;++i){
                v[i] = i+1;
        }
        int j=0;
	for (int i: range(1,101)) {
                CHECK(i == v[j++]); // 5 6 7 8
        }
}

TEST_CASE("####  accumulate:  ####") {
        
}

TEST_CASE("####  filterfalse:  ####") {

}

TEST_CASE("####  compress:  ####") {
        
}
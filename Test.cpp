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

struct lessThan3 {
                bool operator()(int i) const { return i < 3; }
};

TEST_CASE("### demo: ###")
{       
        vector<int> ans = {5,6,7,8};
        int index = 0;
        for (int i : range(5, 9))
                CHECK(i == ans[index++]);

        vector<int> vecInt = {1, 2, 3, 4};
        vector<string> vecString = {"Hello", "Bye", "Adam"};
        vector<float> vecFloat = {-1, 0.3, 5.2, -8.3};

        ans = {5,11,18,26};
        index = 0;
        for (int i : accumulate(range(5, 9)))
                CHECK(i == ans[index++]);
        
        vector<string> ans1 = {"Hello", "HelloBye", "HelloByeAdam"};
        index = 0;
        for (string i : accumulate(vecString))
                CHECK(i == ans1[index++]);

        ans = {5, 30, 210, 1680};
        index = 0;
        for (int i : accumulate(range(5, 9), [](int x, int y) { return x * y; }))
                CHECK(i == ans[index++]);

        ans = {3, 4};
        index = 0;
        for (auto i : filterfalse(lessThan3{}, vecInt))
                CHECK(i == ans[index++]);
      
        ans = {5, 7};
        index = 0;
        for (auto i : filterfalse([](int i) { return i % 2 == 0; }, range(5, 9)))
                CHECK(i == ans[index++]);
        
        vector<char> ans2 = {'a','b','d'};
        index = 0;
        for (auto i : compress(string("abcd"), vector<bool>({true, true, false, true})))
                CHECK(i == ans2[index++]);
        
        ans = {5,6,8};
        index = 0;
        for (auto i : compress(range(5, 9), vector<bool>({true, true, false, true})))
                CHECK(i == ans[index++]);

}

TEST_CASE("####  range:  ####")
{
        vector<int> v(20);
        for (int i = 0; i < v.size(); ++i)
        {
                v[i] = i + 1;
        }
        int j = 0;
        for (int i : range(1, 21))
        {
                CHECK(i == v[j++]);
        }

        // one element
        j = 1;
        for (int i : range(1, 2))
        {
                CHECK(i == j);
        }

        // zero element
        for (int i : range(1, 1))
        {
                CHECK(i == j);
        }

        // begin > end
        CHECK_THROWS(range(2, 1));
}

TEST_CASE("####  accumulate:  ####")
{
        vector<int> v(20);
        for (int i = 0; i < v.size(); ++i)
        {
                if (i == 0)
                        v[i] = 1;
                else
                {
                        v[i] = v[i - 1] + 1+i;
                }
        }
        int index = 0;
        int sum = 1;
        for (int i : accumulate(range(1, 21)))
        {
                CHECK(i == v[index++]);
                sum += i;
        }

        vector<string> v2 = {"I ", "am ", "a ", "test ", "and ", "I ", "am ", "a ", "good ", "one"};
        vector <string> v2ans(10);
        for (int i = 0; i < v2.size(); ++i)
        {
                if (i == 0)
                        v2ans[i] = "I ";
                else
                {
                        v2ans[i] = v2ans[i - 1] + v2[i];
                }
        }
        
        int index2 = 0;
        for (string i : accumulate(v2))
        {
                CHECK( v2ans[index2]== i);
                index2++;
        }

        vector<int> v3 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        vector<int> v3ans = {1, 2, 6, 24, 120, 720, 5040, 40320, 362880};
        int index3 = 0;
        for (int i : accumulate(v3, [](int x, int y) { return x * y; }))
        {
                CHECK(i == v3ans[index3++]);
        }
}

TEST_CASE("####  filterfalse:  ####")
{
        vector<string> v4={"a", "sd","sdfs","e","rfrf","as","adfd","jdj","adfnj","adaeda","adad","hgfhg", "hf", "ahfh", "jyytf","b","j"};
	vector<string> v4ans={"sd","sdfs","e","rfrf","jdj", "hgfhg", "hf", "jyytf","b","j"};
	int index4=0;
	for (auto i : filterfalse([](string s) { return s[0]=='a'; }, v4))
                CHECK(i==v4ans[index4++]);
}

TEST_CASE("####  compress:  ####")
{
        vector<string> v5o = {"a", "sd","sdfs","e","rfrf","as","adfd","jdj","adfnj","adaeda","adad","hgfhg", "hf", "ahfh", "jyytf","b","j"};
	vector<bool> v5 = {false, true,true,true,true,false,false,true,false,false,false,true,true, false, true,true,true};
        vector<string> v4ans={"sd","sdfs","e","rfrf","jdj", "hgfhg", "hf", "jyytf","b","j"};

	int index5=0;
	
        for (auto i : compress(v5o, v5))
                CHECK(i == v4ans[index5++]);
}

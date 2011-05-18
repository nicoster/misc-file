/////////////////////////////////////////////////////////////////////// 
// 
// Compile options needed: /GX
// 
// partial_sum.cpp : Demonstrates the use of partial_sum().
// 
// Description of partial_sum(first,last,first2,init)
//                partial_sum(first,last,first2,init,binary_op):
// 
//    Assigns to every iterator i in the range
//    [result,result + (last - first)) a value correspondingly equal to
//    ((...(*first + *(first + 1)) + ...) + *(first + (i - result)))
// 
//     - or -
// 
//    binary_op(binary_op(..., binary_op(*first, *(first  +  1)),...),
//    *(first + (i - result)))
// 
//    In other words,
//    *(result+i) = init + *(first+0) + *(first+1) + ... + *(first+i)
// 
// Written by Shaun Miller
// of Microsoft Product Support Services, Languages Developer Support.
// Copyright (c) 1996 Microsoft Corporation. All rights reserved.
/////////////////////////////////////////////////////////////////////// 

#include <iostream>
#include <numeric>
#include <functional>
#include <vector>
#include <iterator>


#if _MSC_VER > 1020   // if VC++ version is > 4.2
   using namespace std;  // std c++ libs implemented in std
   #endif

typedef vector < int, allocator < int > > IntArray;
typedef ostream_iterator < int, char, char_traits<char> > IntOstreamIt;

void main ()

{

    IntOstreamIt itOstream(cout," ");

    // Initialize the array
    IntArray rgI;
    for (int i=1; i<=10; i++) rgI.push_back(i);

    // Print the arrays
    cout << "Array: ";
    copy(rgI.begin(),rgI.end(),itOstream);
    cout << endl;

    // The result array must be at least the same size as the data array
    IntArray rgIresult(rgI.size());

    // Compute the partial sum of the array
    partial_sum(rgI.begin(),rgI.end(),rgIresult.begin());

    // Print the array of partial sums
    cout << "Array of partial sums: ";
    copy(rgIresult.begin(),rgIresult.end(),itOstream);
    cout << endl;

    // Compute the partial product of the array
    partial_sum(rgI.begin(),rgI.end(),rgIresult.begin(),multiplies<int>());

    // Print the array of partial products
    cout << "Array of partial products: ";
    partial_sum(rgIresult.begin(),rgIresult.end(),itOstream);
    cout << endl;

}
				
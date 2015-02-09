//
//  main.c
//  chefString
//
//  Created by Nicholas Arduini on 2/7/15.
//  Copyright (c) 2015 Nicholas Arduini. All rights reserved.
//

/*
Chef likes strings a lot but moreover he likes good strings. Chef calls a string str a good string if str starts and ends at different characters. For eg : strings such as abab , baccba , abc are all good strings whereas strings like aba, baab , baacaab are not good at all .
Today, Chef has a special string P consisting of lower case letters "c" , "h" , "e" and "f" only. Chef wants to make some queries about his string P.
Each of chef's query has the following form a b L R. For a given query, Chef wants to count the number of good strings which starts at letter a and ends at letter b such that starting index Si and ending index Ei of a chosen substring satisfies L <= Si < Ei <= R.
NOTE
Two substrings P1 and P2 are considered to be different if either S1 != S2 or E1 != E2 where S1,E1 and S2,E2 are the starting and ending index of string P1 and string P2 respectively.
Chef is not able to accomplish this task efficiently. Can you help him ?
Input

First line of the input contains a string P denoting the chef's special string. Next line of the input contains a single integer Q denoting the number of chef's queries. Next Q lines of the input contains four space separated parameters where the first two parameters are characters denoting a and b respectively and rest two are integers denoting L and R respectively.
Output

For each chef's query, print the required answer.
Constraints

1 <= |P| <= 106
1 <= Q <= 106
1 <= L <= R <= |P|
P,a,b belongs to the set of lower case letters [c,h,e,f] and a != b.
All test files are strictly according to constraints.
Subtasks

Subtask #1: 1<=|P|,Q<=104 : 27 pts
Subtask #2: 1<=|P|,Q<=105 : 25 pts
Subtask #3: 1<=|P|,Q<=106 : 48 pts
Example

Input
checfcheff
5
c h 1 10
c f 1 10
e c 1 10
c f 1 5
c f 6 10

Output
4
8
2
2
2
Explanation

Q1 : good strings are ch , checfch , cfch , ch
Q2 : good strings are checf , checfchef , checfcheff , cf , cfchef , cfcheff , chef , cheff
Warning

Large test data set, Prefer to use faster input/output methods .
*/

#include <stdio.h>
#include <stdlib.h>
#include<string.h>

typedef struct SegArray {
    unsigned long long ch;
    unsigned long long ce;
    unsigned long long cf;
    unsigned long long ec;
    unsigned long long eh;
    unsigned long long ef;
    unsigned long long hc;
    unsigned long long he;
    unsigned long long hf;
    unsigned long long fc;
    unsigned long long fe;
    unsigned long long fh;
    unsigned long long c_mult;
    unsigned long long h_mult;
    unsigned long long e_mult;
    unsigned long long f_mult;
} SegArray;

int main(void) {
    
    char arr[1000001];
    scanf("%s", arr);
    unsigned long size = strlen(arr);
    SegArray *segs = malloc(sizeof(SegArray) * size);
    memset(segs, 0, sizeof(SegArray));
    unsigned long i;
    switch (arr[0]) {
            case 'c':   ++(segs[0].c_mult);
            break;
            case 'h':   ++(segs[0].h_mult);
            break;
            case 'e':   ++(segs[0].e_mult);
            break;
            case 'f':   ++(segs[0].f_mult);
            break;
    }
    for (i = 1; i < size; ++i) {
        segs[i] = segs[i - 1];
        switch (arr[i]) {
                case 'c':
                segs[i].c_mult += 1;
                segs[i].ec += segs[i].e_mult;
                segs[i].fc += segs[i].f_mult;
                segs[i].hc += segs[i].h_mult;
                break;
                case 'h':
                segs[i].h_mult += 1;
                segs[i].eh += segs[i].e_mult;
                segs[i].fh += segs[i].f_mult;
                segs[i].ch += segs[i].c_mult;
                break;
                case 'e':
                segs[i].e_mult += 1;
                segs[i].ce += segs[i].c_mult;
                segs[i].fe += segs[i].f_mult;
                segs[i].he += segs[i].h_mult;
                break;
                case 'f':
                segs[i].f_mult += 1;
                segs[i].ef += segs[i].e_mult;
                segs[i].cf += segs[i].c_mult;
                segs[i].hf += segs[i].h_mult;
                break;
        }
    }
    unsigned long queries;
    scanf("%lu", &queries);
    char firstC, secondC;
    unsigned long firstI, lastI;
    for (i = 0; i < queries; ++i) {
        scanf(" %c %c %lu %lu", &firstC, &secondC, &firstI, &lastI);
        --firstI, --lastI;
        unsigned long long sub_mult, times, result;
        if (firstC == 'c') {
            sub_mult = firstI ? segs[firstI - 1].c_mult : 0;
            if (secondC == 'h') {
                times = segs[lastI].h_mult - segs[firstI].h_mult;
                result = segs[lastI].ch - segs[firstI].ch - (times * sub_mult);
            }
            else if (secondC == 'e') {
                times = segs[lastI].e_mult - segs[firstI].e_mult;
                result = segs[lastI].ce - segs[firstI].ce - (times * sub_mult);
            }
            else if (secondC == 'f') {
                times = segs[lastI].f_mult - segs[firstI].f_mult;
                result = segs[lastI].cf - segs[firstI].cf - (times * sub_mult);
            }
        }
        else if (firstC == 'h') {
            sub_mult = firstI ? segs[firstI - 1].h_mult : 0;
            if (secondC == 'c') {
                times = segs[lastI].c_mult - segs[firstI].c_mult;
                result = segs[lastI].hc - segs[firstI].hc - (times * sub_mult);
            }
            else if (secondC == 'e') {
                times = segs[lastI].e_mult - segs[firstI].e_mult;
                result = segs[lastI].he - segs[firstI].he - (times * sub_mult);
            }
            else if (secondC == 'f') {
                times = segs[lastI].f_mult - segs[firstI].f_mult;
                result = segs[lastI].hf - segs[firstI].hf - (times * sub_mult);
            }
        }
        else if (firstC == 'e') {
            sub_mult = firstI ? segs[firstI - 1].e_mult : 0;
            if (secondC == 'h') {
                times = segs[lastI].h_mult - segs[firstI].h_mult;
                result = segs[lastI].eh - segs[firstI].eh - (times * sub_mult);
            }
            else if (secondC == 'c') {
                times = segs[lastI].c_mult - segs[firstI].c_mult;
                result = segs[lastI].ec - segs[firstI].ec - (times * sub_mult);
            }
            else if (secondC == 'f') {
                times = segs[lastI].f_mult - segs[firstI].f_mult;
                result = segs[lastI].ef - segs[firstI].ef - (times * sub_mult);
            }
        }
        else if (firstC == 'f') {
            sub_mult = firstI ? segs[firstI - 1].f_mult : 0;
            if (secondC == 'h') {
                times = segs[lastI].h_mult - segs[firstI].h_mult;
                result = segs[lastI].fh - segs[firstI].fh - (times * sub_mult);
            }
            else if (secondC == 'e') {
                times = segs[lastI].e_mult - segs[firstI].e_mult;
                result = segs[lastI].fe - segs[firstI].fe - (times * sub_mult);
            }
            else if (secondC == 'c') {
                times = segs[lastI].c_mult - segs[firstI].c_mult;
                result = segs[lastI].fc - segs[firstI].fc - (times * sub_mult);
            }
        }
        
        printf("%llu\n", result);
        
    }
    
    free(segs);
    
    
    return 0;
}

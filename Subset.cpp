//
//  Subset.cpp
//  test
//
//  Created by Yichao SHEN on 12/27/13.
//  Copyright (c) 2013 ZXX. All rights reserved.
//

#include "Subset.h"

vector<vector<int>> helper(vector<int> &S){
    vector<int> tmp;
    vector<vector<int>> ans;
    if (S.size() == 0) {
        ans.push_back(tmp);
        return ans;
    }
    
    vector<int> copy = S;
    int temp = S.back();
    copy.pop_back();
    vector<vector<int>> ans1 = subsets(copy);//does not contain i;
    ans = ans1;
    vector<vector<int>>::iterator vit = ans.begin();
    vector<vector<int>>::iterator ven = ans.end();
    for (; vit != ven; ++vit) {
        (*vit).push_back(temp);
    }
    ans.insert(ans.end(), ans1.begin(), ans1.end());
    return ans;
}

vector<vector<int> > subsets(vector<int> &S){
    sort(S.begin(),S.end());
    return helper(S);
}


vector<vector<int> > permute(vector<int> &num) {
    vector<int> tmp;
    vector<vector<int>> ans;
    if (num.size() == 1) {
        tmp.push_back(num[0]);
        ans.push_back(tmp);
        return ans;
    }
    int temp;
    vector<int> copy;
    for (int i = 0; i < num.size(); i++) {
        temp = num[i];
        copy = num;
        copy.erase(copy.begin() + i);
        vector<vector<int>> ans1 = permute(copy);
        vector<vector<int>>::iterator vit = ans1.begin();
        vector<vector<int>>::iterator ven = ans1.end();
        for (; vit != ven; ++vit) {
            (*vit).push_back(temp);
        }
        ans.insert(ans.end(), ans1.begin(), ans1.end());

    }
    return ans;
}


int uniquePaths(int m, int n) {
    int s[n][m];
    int i;
    int j;
    for (i = 0; i < m ; i++) {
        s[0][i] = 1;
    }
    for (i = 0; i < n; i++) {
        s[i][0] = 1;
    }
    for (i = 1 ; i < n; i++) {
        for (j = 1; j < m; j++) {
            s[i][j] = s[i - 1][j] + s[i][j - 1];
        }
    }
    
    return s[n - 1][m - 1];
}

int uniquePathsWithObstacles(vector<vector<int> > &obstacleGrid) {
    int n = (int)obstacleGrid.size();
    int m = (int)obstacleGrid[0].size();
    int s[n][m];
    int i;
    int j;
    for (i = 0; i < m ; i++) {
        if (obstacleGrid[0][i] == 1) {
            s[0][i] = 0;
            break;
        }
        else s[0][i] = 1;
    }
    for (; i < m ; i++){
        s[0][i] = 0;
    }
    for (i = 0; i < n; i++) {
        if (obstacleGrid[i][0] == 1) {
            s[i][0] = 0;
            break;
        }
        else s[i][0] = 1;
    }
    for (; i < n ; i++){
        s[i][0] = 0;
    }
    
    for (i = 1 ; i < n; i++) {
        for (j = 1; j < m; j++) {
            if (obstacleGrid[i][j] == 1) {
                s[i][j] = 0;
            }
            else
                s[i][j] = s[i - 1][j] + s[i][j - 1];
        }
    }
    return s[n - 1][m - 1];
}

void phelper(int r, int l, vector<string>& ans, string str){
    if (r == 0 && l == 0) {
        ans.push_back(str);
        return;
    }
    
    if (l > 0) {
        str.push_back('(');
        phelper(r, l - 1, ans, str);
        str.pop_back();
    }
    if (r > l) {
        str.push_back(')');
        phelper(r - 1, l, ans, str);
    }
}

vector<string> parenthes(int n){
    vector<string> ans;
    string str;
    phelper(n, n, ans, str);
    return ans;
}

void dhelper(int &k, int n, int d){
    if (n < 1) {
        return;
    }
    if (d == 1) {
        if (n - 1 == 0) {
            k++;
        }
        dhelper(k, n - 1, 1);
    }
    if (d == 5) {
        if (n - 5 == 0) {
            k++;
        }
        dhelper(k, n - 5, 5);
        dhelper(k, n - 5, 1);
    }
    if (d == 10) {
        if (n - 10 == 0) {
             k++;
        }
        dhelper(k, n - 10, 10);
        dhelper(k, n - 10, 5);
        dhelper(k, n - 10, 1);
    }
    if (d == 25) {
        if (n - 25 == 0) {
            k++;
        }
        dhelper(k, n - 25, 25);
        dhelper(k, n - 25, 10);
        dhelper(k, n - 25, 5);
        dhelper(k, n - 25, 1);
    }
}
int denominator8_7(int n){
    int k = 0;
    int k1 = 0;
    int k2 = 0;
    int k3 = 0;
    dhelper(k, n, 1);
    dhelper(k1, n, 5);
    dhelper(k2, n, 10);
    dhelper(k3, n, 25);
    int k4 = k + k1 + k2 + k3;
    return k4;
}

int makechange(int n, int denom){
    int nextDenom = 0;
    switch (denom) {
        case 25:
            nextDenom = 10;
            break;
        case 10:
            nextDenom = 5;
            break;
        case 5:
            nextDenom = 1;
            break;
        case 1:
            return 1;//if the denom is *one* then directly return *one*. This is the only choice.
    }
    int ways = 0;
    for (int i = 0; i * denom <= n; i++) {
        ways += makechange(n - i * denom, nextDenom);
    }
    return ways;
}
int makechange_dynamic(int n){
    int k[25];
    
    int i = 0;
    k[0] = 0;
    for (; i < 5; i++) {
        k[i] = 1;
    }
    for (i = 5; i < 10; i++) {
        k[i] = 2;
    }
    for (i = 10; i < 25; i++) {
        k[i] = k[i - 10] + k[i - 5] + k[i -1];
    }
    if (n <= 25) {
        return k[n];
    }
    int s[n + 1];
    for (i = 0; i <= 25; i++) {
        s[i] = k[i];
    }
    for (i = 26; i <= n; i++) {
        s[i] = s[i - 25] + s[i - 10] + s[i - 5] + s[i -1];
    }
    return s[n];
}

bool check(int row, int* array){
    for (int i = 0; i < row; i++) {
        int diff = abs(array[i] - array[row]);
        if (diff == 0 || diff == row - i) {
            return false;
        }
    }
    return true;
}
void pushtoboard(int* array, int n, vector<vector<string>> &ans){
    int k;
    vector<string> subans;
    for (int i = 0; i < n; i++) {
        string str;
        for (k = 0; k < n; k++) {
            if (k == array[i]) {
                str.push_back('Q');
            }
            else str.push_back('.');
        }
        subans.push_back(str);
    }
    ans.push_back(subans);
    
}
void placeQueen(int row, int* array, int n, vector<vector<string>> &ans){
    //static int anscount = 0;
    if (row == n) {
        pushtoboard(array, n, ans);
        //cout<<++anscount<<endl;
        return;
    }
    for (int i = 0; i < n; i++) {
        array[row] = i;
        if (check(row, array)) {
            placeQueen(row + 1, array, n,ans);
        }
    }
}

vector<vector<string>> solveNQueens(int n) {
    vector<vector<string>> ans;
    if (n == 1) {
        string str;
        str.push_back('Q');
        vector<string> subans;
        subans.push_back(str);
        ans.push_back(subans);
        return ans;
    }
    int* array = new int[n];
    placeQueen(0, array, n, ans);
    delete [] array;
    return ans;
}
bool check1(int row, int n, int* array){
    for(int i = 0; i < row; i++){
        int diff = abs(array[i] - array[row]);
        if(diff == 0 || diff == row - i)
            return false;
    }
    return true;
}
int countNQueens(int &k, int n, int* array, int row){
    if(row == n)
        return ++k;
    for(int i = 0; i < n; i++){
        array[row] = i;
        if(check1(row,n,array)){
            countNQueens(k,n,array, row + 1);
        }
    }
    return k;
}
int totalNQueens(int n) {
    if(n == 1){
        return 1;
    }
    int k = 0;
    int* array = new int [n];
    k = countNQueens(k,n,array,0);
    return k;
}
void moveUp(int i, int j, int A[], int n){//begin and end are both indexes.
    for (; j < n; j++,i++) {
        A[i] = A[j];
    }
}
int removeDuplicates(int A[], int n) {
    if (n == 1) {
        return 1;
    }
    int i;
    int j;
    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (A[i] != A[j]) {
                if (j == i + 1) {
                    break;
                }
                else {
                    moveUp(i + 1, j,A,n);//从j的位置移动到i+1的位置
                    n = n - j + i + 1;
                    break;
                    
                }
            }
        }
    }
    j = n - 2;
    while (A[n - 1] == A[j] && j >= 0) {
        j--;
        n--;
    }
    return n;
}

void combineHelper(vector<vector<int>> &ans, vector<int>& subans, int i, int n, int k){
    if(k == 0){
        ans.push_back(subans);
        return;
    }
    if(k > n - i + 1){
        return;
    }
    for(;i <= n; i++){
        subans.push_back(i);
        combineHelper(ans, subans, i + 1, n, k - 1);
        subans.pop_back();
    }
}
vector<vector<int> > combine(int n, int k) {
    vector<int> subans;
    vector<vector<int>> ans;
    if(n < k)
        return ans;
    combineHelper(ans, subans, 1 , n, k);
    return ans;
}

void combineHelperback(int index, vector<int> &subans, vector<vector<int>> &ans,int k, int n){
    if(index == k){
        ans.push_back(subans);
        return;
    }
    for(int j = index; j < n - k; j++){
        subans.push_back(j);
        combineHelperback(j + 1, subans,ans,k,n);
        subans.pop_back();
    }
}

vector<vector<int> > combineback(int n, int k) {
    vector<int> subans;
    vector<vector<int>> ans;
    combineHelperback(1,subans,ans,k,n);
    return ans;
}


double pow1(double x, int n) {
    if(x == 0 || x == 1 || n == 1)
        return x;
    if(n == 0){
        return 1.0;
    }
    if(n < 0){
        if (n == -2147483648) {
            n = n - 2;
        }
        else {n = (-1) * n;}
        return 1 / pow1(x,n);
    }
    
    if(n % 2 == 0){
        if (x < 0) {
            x = (-1) * x;
        }
        double half = pow1(x, n / 2);
        return half * half;
    }
    else{
        double half = pow1(x, n / 2);
        return half * half * x;
    }
}

void permuteUniqueHelper(vector<int> &num,vector<int> & subans,vector<bool> &used, vector<vector<int>> & ans){
    if (subans.size() == num.size()) {
        ans.push_back(subans);
        return;
    }
    for (int i = 0; i < num.size(); i++) {
        if (used[i] || (i != 0 && num[i] == num[i - 1] && used[i - 1])) continue;
        used[i] = true;
        subans.push_back(num[i]);
        permuteUniqueHelper(num,subans,used,ans);
        used[i] = false;
        subans.pop_back();
    }
}
vector<vector<int> > permuteUniqueSub(vector<int> &num) {
    sort(num.begin(),num.end());//sort the original array.
    vector<bool> used(num.size(),false);
    vector<int> subans;
    vector<vector<int>> ans;
    permuteUniqueHelper(num,subans,used,ans);
    return ans;
    
}

//the text below is used for git testing only.


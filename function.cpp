#include <iostream>
#include "function.h"

#define MAX_TIME 100000000
using namespace std;

string shop_name[10005];
int num_people[MAX_TIME];
int arrive_time[10005];

template < class T >
void mySort(T* arr, int l, int r){
    if (l >= r) return;
    else {
        int mid = (l + r)/2;
        mySort(arr, l, mid);
        mySort(arr, mid + 1, r);
        T* tmp = (T*)malloc((r-l+1) * sizeof(T));
        int idl = l, idr = mid + 1, i = 0;
        while(1) {
            if (idl > mid || idr > r || i > r-l+1) break;
            if (arr[idl] >= arr[idr]) tmp[i++] = arr[idr++];
            else if (arr[idr] > arr[idl]) tmp[i++] = arr[idl++];
        }
        while(idl > mid && idr <= r) tmp[i++] = arr[idr++];
        while(idr > r && idl <= mid) tmp[i++] = arr[idl++];

        for (int i = 0 ; i < r - l + 1 ; i++) arr[l + i] = tmp[i];
    }
}

// TODO: Implement the function to read input, process data, and output answers.
void solve() {
    int n, m, ar, le, np;
    cin >> n;
    for (int i = 0 ; i < n ; i++) {
        cin >> np >> ar >> le >> shop_name[i];
        arrive_time[i] = ar;
        for (int j = ar - 1 ; j < le - 1 ; j++)
            num_people[j] += np;
    }

    mySort<string>(shop_name, 0, n - 1);
    mySort<int>(arrive_time, 0, n - 1);
    int max_time, max_peo = 0;
    for(int i = 0 ; i < MAX_TIME ; i++) {
        if (max_peo < num_people[i]) {
            max_peo = num_people[i];
            max_time = i + 1;
        }
    }

    cin >> m;
    string instrction;
    for (int i = 0 ; i < m ; i ++) {
        cin >> instrction;
        if(instrction == "TIME_ARRIVE") {
            int time;
            cin >> time;
            cout << arrive_time[time - 1] << endl;
        }
        else if(instrction == "TRAFFIC_AT") {
            int time;
            cin >> time;
            cout << num_people[time] << endl;
        }
        else if(instrction == "MAX_TRAFFIC") {
            cout << max_time << " " << max_peo << endl;
        }
        else if(instrction == "STORE_LIST") {
            string name = shop_name[0];
            cout << name;
            for (int i = 1 ; i < n ; i++) {
                if(name != shop_name[i]) {
                    cout << " " << shop_name[i];
                    name = shop_name[i];
                }
            }
            cout << endl;
        }
    }
}

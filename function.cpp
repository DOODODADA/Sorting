#include <iostream>
#include "function.h"

using namespace std;
struct time_active{
    int np;
    int time;
};

string shop_name[10005];
int* num_people;
int arrive_time[10005];
time_active active[20010];


bool operator>(time_active A, time_active B){
    return A.time > B.time;
}

bool operator>=(time_active A, time_active B){
    return A.time >= B.time;
}
    

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

int main(void) {
    solve();
    return 0;
}

// TODO: Implement the function to read input, process data, and output answers.

void solve() {
    int n, m, ar, le, np;
    cin >> n;
    for (int i = 0 ; i < n ; i++) {
        cin >> np >> ar >> le >> shop_name[i];
        arrive_time[i] = ar;
        active[2 * i] = {np, ar};
        active[2 * i + 1] = {-np, le};
    }

    mySort<string>(shop_name, 0, n - 1);
    mySort<int>(arrive_time, 0, n - 1);
    mySort<time_active>(active, 0, 2*n - 1);
    int* number_of_people = (int*)malloc(2 * n * sizeof(int));
    int max_time, max_peo = 0;
    int ti = active[0].time;
    int nup = active[0].np;
    for (int i = 1 ; i < 2*n ; i++) {
        if(ti != active[i].time){
            if(nup > max_peo) {
                max_peo = nup;
                max_time = ti;
            }
            ti = active[i].time;
        }
        nup += active[i].np;
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
            if (time < active[0].time) cout << 0 << endl;
            else if (time >= active[2*n - 1].time) cout << 0 << endl;
            else {
                int ti = active[0].time;
                int nup = active[0].np;
                for (int i = 1 ; i < 2*n ; i++) {
                    if(ti != active[i].time){
                        if(time <= ti) {
                            cout << nup << endl;
                            break;
                        }
                        ti = active[i].time;
                    }
                    nup += active[i].np;
                }
            }
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

#include <cassert>
#include <iomanip>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

class BookManager {
public:
    BookManager()
        : users_page_count(100001, -1)
        , pages_user_count(1001)
    {
    }

    void Read(int id, int page){
        int start_page = users_page_count[id];

        users_page_count[id] = page;

        for(int i = start_page + 1; i <= page; ++i){
            pages_user_count[i] += 1;
        }
    }

    double GetInfo(int id){
        //Проверяем что пользователь читал
        if(users_page_count[id] == -1){
            return 0.;
        }

        int all_users_count = pages_user_count[0] - 1;

        //Проверяем что пользователь не один
        if(all_users_count == 0){
            return 1.;
        }

        int users_read_less = all_users_count - (pages_user_count[users_page_count[id]] - 1);

        if(users_read_less == 0){
            return 0.;
        }
        return static_cast<double>(users_read_less) / static_cast<double>(all_users_count);
    }

private:
    //индекс - пользователь, значение - номер страницы
    vector<int> users_page_count;
    //индекс - страница, значение - количество пользователей
    vector<int> pages_user_count;
};

void Tests(){
    BookManager bm;

    assert(bm.GetInfo(5) == 0);

    bm.Read(1, 10);
    assert(bm.GetInfo(1) == 1);

    bm.Read(2, 5);
    bm.Read(3, 7);
    assert(bm.GetInfo(2) <= numeric_limits<double>::epsilon());
    double x = bm.GetInfo(3);
    assert(abs(x - 0.5) <= numeric_limits<double>::epsilon());

    bm.Read(3, 10);
    x = bm.GetInfo(3);
    assert(abs(x - 0.5) <= numeric_limits<double>::epsilon());
}

int main(){
    //Tests();
    BookManager bm;

    int query_count;
    cin >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id) {
        string query_type;
        cin >> query_type;
        if(query_type == "CHEER") {
            int id;
            cin >> id;
            cout << setprecision(6) << bm.GetInfo(id) << endl;
        } else if (query_type == "READ") {
            int id, page;
            cin >> id >> page;
            bm.Read(id, page);
        }
    }

    return 0;
}
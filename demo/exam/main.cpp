#include <iostream>
#include <map>

using namespace std;

int main()
{
    int n = 0;
    int m = 0;
    map<int, int> m_map;

    while(1)
    {
        cout << "input n and m" << endl;
        cin >> n >> m;

        if( n == 0 && m == 0)
        {
            return 0;
        }

        int int_arr1[m];
        int int_arr2[m];

        for(int i = 0; i < m; i++)
        {

            cin >> int_arr1[i] >> int_arr2[i];
        }

        //cout << "test:" << n << ", " << m << endl;

        //for(int i = 0; i < m; i++)
        //{
        //    cout << int_arr1[i] << ", " << int_arr2[i] << endl;
        //}

        bool change = true;
        int same_cnt = 0;
        while(change)
        {
            for(int i = 0; i < m; i++)
            {
                if (int_arr1[i] == 1)
                {
                    if(int_arr2[i] != 1)
                    {
                        int same = int_arr2[i];

                        //cout << "same:" << same << endl;

                        same_cnt++;
                        change = true;

                        for(int i = 0; i < m; i++)
                        {
                            if(int_arr1[i] == same)
                            {
                                int_arr1[i] = 1;
                            }

                            if (int_arr2[i] == same)
                            {
                                int_arr2[i] = 1;
                            }
                        }

                        continue;
                    }
                }

                if (int_arr2[i] == 1)
                {
                    if(int_arr1[i] != 1)
                    {
                        int same = int_arr1[i];

                        //cout << "same:" << same << endl;

                        same_cnt++;
                        change = true;

                        for(int i = 0; i < m; i++)
                        {
                            if(int_arr1[i] == same)
                            {
                                int_arr1[i] = 1;
                            }

                            if (int_arr2[i] == same)
                            {
                                int_arr2[i] = 1;
                            }
                        }

                        continue;
                    }
                }

                change = false;
            }
        }

        cout << "same num cnt is :" << same_cnt << endl;
    }


    return 0;
}

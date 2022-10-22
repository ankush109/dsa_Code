//{ Driver Code Starts
#include <bits/stdc++.h>
using namespace std;

// } Driver Code Ends
class Solution
{
public:
    // Function to return the sorted array.
    vector<int> nearlySorted(int arr[], int num, int K)
    {
        priority_queue<int, vector<int>, greater<int>> min;
        vector<int> ans;

        for (int i = 0; i < num; i++)
        {
            min.push(arr[i]);

            if (min.size() > K)
            {

                ans.push_back(min.top());
                min.pop();
            }
        }
        while (!min.empty())
        {

            ans.push_back(min.top());
            min.pop();
        }
        return ans;
    }
};

//{ Driver Code Starts.

int main()
{
    int T;
    cin >> T;

    while (T--)
    {
        int num, K;
        cin >> num >> K;

        int arr[num];
        for (int i = 0; i < num; ++i)
        {
            cin >> arr[i];
        }
        Solution ob;
        vector<int> res = ob.nearlySorted(arr, num, K);
        for (int i = 0; i < res.size(); i++)
            cout << res[i] << " ";

        cout << endl;
    }

    return 0;
}

// } Driver Code Ends
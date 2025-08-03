const int Lim = 1e6 + 1; // Upper limit for prime number calculation
vector<bool> isPrime(Lim, 1); // Boolean array to mark prime numbers
vector<int> Primes; // Stores all prime numbers
int sz; // Size of the Primes vector

class Solution {
public:
    Solution()
    {
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr);
        
        // If Primes vector is already computed, avoid recomputation
        if(Primes.size()) return; 
        
        else
        {
            // Marking known non-prime numbers
            isPrime[0] = isPrime[1] = isPrime[4] = isPrime[6] = 0;

            // Eliminating numbers divisible by 2, 3, or 5
            for(int i = 0; i < Lim; ++i)
            {
                if(i % 2 == 0 || i % 3 == 0 || i % 5 == 0) isPrime[i] = 0;
            }

            // Ensuring 2, 3, and 5 are marked as prime
            isPrime[2] = isPrime[3] = isPrime[5] = 1;

            // Applying 6k ± 1 optimization to sieve prime numbers efficiently
            for(int i = 1; i * i < Lim; ++i)
            {
                int num1 = 6 * i + 1; // Form of 6k+1
                if(num1 < Lim)
                {
                    if(isPrime[num1]) // If num1 is prime, mark its multiples as non-prime
                    {
                        int j = 2;
                        while(num1 * j < Lim)
                        {
                            isPrime[num1 * j] = 0;
                            j++;
                        }
                    }
                }
                else break;

                int num2 = 6 * i + 5; // Form of 6k+5
                if(num2 < Lim)
                {
                    if(isPrime[num2]) // If num2 is prime, mark its multiples as non-prime
                    {
                        int j = 2;
                        while(num2 * j < Lim)
                        {
                            isPrime[num2 * j] = 0;
                            j++;
                        }
                    }
                }
                else break;
            }

            // Storing all prime numbers in the Primes vector
            for(int i = 0; i < Lim; ++i)
            {
                if(isPrime[i]) Primes.push_back(i);
            }

            sz = Primes.size(); // Storing the size of Primes vector for later use
        }
    }

    // Finds the Greatest Lower Bound (GLB) or largest index where Primes[index] <= toFind
    int GLB(vector<int>& arr, int low, int high, int toFind)
    {
        int n = arr.size();
        while(low <= high)
        {
            int mid = low + (high - low) / 2;
            if(arr[mid] == toFind) return mid;
            else if(arr[mid] > toFind) high = mid - 1;
            else low = mid + 1;
        }

        return min(n - 1, low) - (toFind < arr[low]); // Ensures valid index is returned
    }

    // Finds the Least Upper Bound (LUB) or smallest index where Primes[index] >= toFind
    int LUB(vector<int>& arr, int low, int high, int toFind)
    {
        int n = arr.size();
        while(low <= high)
        {
            int mid = low + (high - low) / 2;
            if(arr[mid] == toFind) return mid;
            else if(arr[mid] > toFind) high = mid - 1;
            else low = mid + 1;
        }

        return max(0, low) - (toFind > arr[low]); // Ensures valid index is returned
    }

    // Finds the closest prime numbers within the given range [left, right]
    vector<int> closestPrimes(int left, int right) {
        int l = LUB(Primes, 0, sz, left); // Find first prime >= left
        int r = GLB(Primes, 0, sz, right); // Find last prime <= right

        if(l >= r) return {-1, -1}; // If there are no two primes, return -1, -1

        // If the smallest gap is 1 or 2, return immediately
        if(Primes[l + 1] - Primes[l] == 1 || Primes[l + 1] - Primes[l] == 2) 
            return {Primes[l], Primes[l + 1]};

        int minGap = INT_MAX;
        vector<int> sol = {-1, -1};

        // Iterate over the range to find the closest prime pair
        for(int i = l; i < r; i++)
        {
            if(Primes[i+1] - Primes[i] < minGap)
            {
                minGap = Primes[i+1] - Primes[i];
                if(minGap == 2) return {Primes[i], Primes[i+1]}; // Smallest possible gap
                sol = {Primes[i], Primes[i+1]};
            }
        }

        return sol;
    }
};
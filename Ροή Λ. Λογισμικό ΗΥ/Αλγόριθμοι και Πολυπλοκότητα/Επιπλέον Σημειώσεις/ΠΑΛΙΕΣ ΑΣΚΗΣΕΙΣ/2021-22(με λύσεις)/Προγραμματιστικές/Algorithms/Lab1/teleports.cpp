#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

class disjointSet
{
    private:
        int elements;
        int *rep, *rank;


    public:
        /* Constructor, makes #elems singleton sets */
        disjointSet(int elems)
        {
            elements = elems;
            rep = new int[elems];
            rank = new int[elems];
            for (int i = 0; i < elems; i++)
            {
                rep[i] = i + 1;
                rank[i] = 0;
            }
        }

        /* Find and compress path */
        int find(int a)
        {
            if (rep[a - 1] != a) rep[a - 1] = find(rep[a - 1]);
            return rep[a - 1];
        }

        /* Unite by rank */
        void unite(int a, int b)
        {
            int aRep, bRep, aRank, bRank;

            aRep = this->find(a);
            bRep = this->find(b);
            if (aRep == bRep) return;

            aRank = rank[aRep - 1];
            bRank = rank[bRep - 1];

            if (bRank < aRank)
            {
                rep[bRep - 1] = aRep;
                this->find(b);
            }

            else
            {
                rep[aRep - 1] = bRep;
                this->find(a);
            }

            if (aRank == bRank) rank[bRep - 1]++;
        }

        /* Check if the portals used are enough for the Morty's to be at the right world */
        bool check_candidate_portals(int *morty, int no_worlds)
        {
            int morty_at_world;
            for (int i = 0; i < no_worlds; i++)
            {
                morty_at_world = morty[i];
                if (morty_at_world != i + 1)           //If true we found a Morty at the wrong world
                    if (this->find(i + 1) != this->find(morty_at_world))
                        return false;                 //He can't connect with the world he should be
            }
            return true;
        }

        void print()
        {
            cout << "Printing sets of connecting worlds: \n";
            for (int i = 0; i < elements; i ++)
                cout << rep[i] << " ";
            cout << endl;
        }

        /* Return sets to initial state, ie #elements singleton sets */
        void clear()
        {
            for (int i = 0; i < elements; i++)
            {
                rep[i] = i + 1;
                rank[i] = 0;
            }
        }

        /* Destructor */
        ~disjointSet()
        {
            delete []rank;
            delete []rep;
        }
};

struct portal
{
    private:
        int world1, world2, length;
    public:
        portal() = default;

        /* Constructor using input stream (here standard input) */
        portal(istream& in)
        {
          int w1, w2, l;
          in >> w1 >> w2 >> l;
          world1 = w1;
          world2 = w2;
          length = l;
        }

        /* Overload/define operator < for sorting later (we only care about length) */
        friend bool operator < (const portal& p1, const portal& p2)
        {return p1.length < p2.length;}
        /* Overload/define operator << for easier output */
        friend ostream& operator << (ostream& os, const portal& p)
        {return os << p.world1 << " " << p.world2 << " " << p.length;}

        friend class portals_open;
};

/* A glorified portal vector, just with some methods for our solution */
class portals_open
{
    private:
        int no_portals;
        vector<portal> portal_ind;

    public:
        /* As before this constructor needs an input stream */
        portals_open(int portals, istream& in) : no_portals(portals)
        {
            portal_ind.reserve(portals);
            for (int i = 0; i < portals; i++)
                portal_ind.push_back(portal(in));
        }

        /* If they are sorted in descending order, by their length, it saves us some time */
        bool sorted()
        {
            int prev = -1, curr;
            for (int i = 0; i < no_portals; i++)
            {
                curr = portal_ind[i].length;
                if (curr < prev) return false;
                prev = curr;
            }
            return true;
        }

        /* If not, sort, the operator < for our portals was defined earlier */
        void sort() {std::sort(portal_ind.begin(), portal_ind.end());}

        /* Make chains of worlds that can connect with portals, starting at index prev and
           ending at portal with index candidate_in (remember they are sorted in descending order) */
        void make_chains(int candidate_in, disjointSet& chains, int prev_used = 0)
        {
            int end = no_portals - 1;
            for (int i = end - prev_used; i >= end - candidate_in; i--)
                chains.unite(portal_ind[i].world1, portal_ind[i].world2);
        }

        int get_length(int i)
        {return portal_ind[i].length;}
};

/* define the array outside of main, so heap is used and not stack (stack memory smaller than heap) */
#define Nmax 500000000
int morty[Nmax];

int main()
{
    /* Fast input-output */
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    /* Read input */
    int N, M; 
    cin >> N >> M ;

    /* Read from std input where each Morty is */
    for (int i = 0; i < N; i ++) cin >> morty[i];
    /* Reads M portals from std input and stores to class */
    portals_open portals = portals_open(M, cin);
    /* Sort the portals if they aren's sorted (by length in descending order) */
    if (!portals.sorted()) portals.sort();
    /* Initialize the set of connecting worlds (at first no world connects to another one) */
    disjointSet chains = disjointSet(N);

    /* Binary search the maximum number of portals used (starting from the biggest one and continuing
       in descending order till the candidate answer), ie binary search the max{min{portal_used.length}} */
    int min_in = 0, max_in = M - 1, candidate_in = (min_in + max_in)/2, checked_portals = 0;
    while (min_in < max_in)
    {
        /* Use #candidate_in portals to connect worlds (make chains). If we had already
           checked #checked_portals don't use those again */
        portals.make_chains(candidate_in, chains, checked_portals);
        /* The portals constitute a valid solution for the Morty's,
           continue binary search to see if we can use less portals */
        if (chains.check_candidate_portals(morty, N))
        {
            max_in = candidate_in;
            chains.clear();                   //Start from scratch (remove all connections)
            checked_portals = 0;
        }
        /* Not a valid solution, we need more portals */
        else
        {
            min_in = candidate_in + 1;
            checked_portals = candidate_in + 1;   //Save used portals
        }

        /* Recompute the next candidate of the answer */
        candidate_in = (min_in + max_in)/2;
    }
    cout << portals.get_length(M - 1 - candidate_in) << endl;
    return 0;
}

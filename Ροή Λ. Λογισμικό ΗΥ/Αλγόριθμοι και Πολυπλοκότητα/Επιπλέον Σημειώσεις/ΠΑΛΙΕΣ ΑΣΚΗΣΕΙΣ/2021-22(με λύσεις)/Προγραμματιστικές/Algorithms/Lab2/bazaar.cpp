#include <stdio.h>
#include <vector>
#define min(a,b) (((a)<(b))?(a):(b))
using namespace std;

typedef unsigned int uint;
#define Nmax 5000
#define Mmax 1500
#define Nsellers 3
#define Nproducts 3
#define A 10


/* cost_of[X][Y][i] == min cost of exactly #i Y-products from seller X
    We need the costs till (#sets_needed - 1) + maximum(#prods) in an offer,
    so n - 1 + A (the problem states that the max prods offered in an offer are A).
    This is because we are interested in the minimum cost for AT LEAST n sets. */
uint cost_of[Nsellers][Nproducts][Nmax + A + 1];
/* The same, but the cost of *atleast*, not -exactly- */
uint cost_of_atleast[Nsellers][Nproducts][Nmax + A + 1];

/* seller_set_cost[x][i] == min cost of at least i sets from seller X*/
uint seller_set_cost[Nsellers][Nmax];

/* Note: the global arrays will be zero-initialized.
    So later on we treat 0s as not able to be bought / reachable. */

/* Just a pair of (product count, cost) */
struct Offer
{
    uint count, cost;
    Offer() = default;
    Offer(uint a, uint b) : count(a), cost(b) {}
};

class SellersOffers  
{
    private:
    /* SPO[x][y][z] = Seller x's zth offer for product y
        (SPO := SellerProductOffer)*/
    vector<Offer> SPO[3][3];

    public:
        SellersOffers() = default;

        void addOffer()
        {
            char c[2];
            scanf("%c%c ", c, c + 1);
            uint count, cost;
            scanf("%u %u\n", &count, &cost);

            SPO[c[0] - '1'][c[1] - 'A'].push_back(Offer(count, cost));
        }

        void compute_exact_costs(uint n);
};

void SellersOffers::compute_exact_costs(uint n)
{
    /* For every offer concerning seller s, product p:
        update the min costs for exactly #count products
        to be bought as per the relation:
                                [cost(s, p, count)                        ]
        cost(s, p, count) = min |                                         |
                                [cost(s, p, count - off.count) + off.cost ] */
    for (int s = 0; s < Nsellers; s++)
    {
        for (int p = 0; p < Nproducts; p++)
        {
            const vector<Offer> & SP = SPO[s][p];
            uint count, c;
            for (Offer off: SP)
            {
                for (count = n + A - 1; count > off.count; count--)
                {
                    c = cost_of[s][p][count - off.count];
                    if (c)
                    {
                        /* If we reached this count for the first time,
                            just update it, else check for the min */
                        cost_of[s][p][count] =
                        !cost_of[s][p][count] ? c + off.cost
                        : min(cost_of[s][p][count], c + off.cost);
                    }
                }
                cost_of[s][p][count] =
                !cost_of[s][p][count] ? off.cost
                : min(cost_of[s][p][count], off.cost);
            }
        }
    }
//O(MN)
}

void compute_costs(uint n)
{
    /* Compute the min costs for atleast #count products p from seller s.
        This is done using the relation:
                                        [cost_atleast(s, p, count + 1) ]
        cost_atleast(s, p, count) = min |                              |
                                        [cost_exact{s, p, count)       ] */
    uint exact, atleast;
    for (int s = 0; s < Nsellers; s++)
    {
        for (int p = 0; p < Nproducts; p++)
        {
            for (uint count = n + A - 1; count > 0; count--)
            {
                exact = cost_of[s][p][count];
                atleast = cost_of_atleast[s][p][count + 1];

                if(!atleast)
                    cost_of_atleast[s][p][count] = exact;
                else if (!exact)
                    cost_of_atleast[s][p][count] = atleast;
                else
                    cost_of_atleast[s][p][count] = min(exact, atleast);
            }
        }
    }
    //O(N)
}

void compute_set_costs(uint n)
{
    /* Compute the cost of #count sets from seller s using:
        set_cost(s, count) = sum(over the products p) {cost_atleast(s, p, count)} */
    uint c1, c2, c3;
    for (int i = 0; i < Nsellers; i++)
    {
        for (uint j = n + A - 1; j > 0; j--)
        {
            c1 = cost_of_atleast[i][0][j];
            c2 = cost_of_atleast[i][1][j];
            c3 = cost_of_atleast[i][2][j];
            if (c1 && c2 && c3)
            {
                seller_set_cost[i][j] =
                !seller_set_cost[i][j+1] ?
                c1 + c2 + c3
                : min(seller_set_cost[i][j+1], c1 + c2 + c3);
            }
            else
                seller_set_cost[i][j] = seller_set_cost[i][j+1];
        }
    }
    //O(N)
}

int result(uint n)
{
    uint c1, c2, c3, res = ~0;
    bool flag;
    for (uint i = 0; i <= n; i++)
    {
        for(uint j = 0; j <= n; j++)
        {
            if(i + j > n) break;
            c1 = seller_set_cost[0][i];
            c2 = seller_set_cost[1][j];
            c3 = seller_set_cost[2][n - j - i];

            /* If we can't buy at least one of the sets from a seller,
                then flag is false and we don't check for min */
            flag = ((i && c1) || !i) && ((j && c2) || !j)
            && ((n - j - i && c3) || !(n - j - i));
            if (flag)
                res = min(res, c1 + c2 + c3);
        }
    }
    return res;
    //O(N^2)
}

int main()
{

    uint n, m;
    scanf("%u %u\n", &n, &m);
    SellersOffers offers;
    for (int i = 0; i < m; i++) offers.addOffer();

    offers.compute_exact_costs(n); //O(NM)
    compute_costs(n);              //O(N)
    compute_set_costs(n);          //O(N)

    int res = result(n);           //O(N^2)
    if(res == ~0) res = -1;        //~0 = UINT_MAX

    printf("%d\n", res);
    /* Complexity: O(N^2 + NM) */
}

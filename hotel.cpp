// ============================================================
// Name    : Zion Wilson
// Course  : COSC 1437 — Programming Fundamentals II
// Date    : June 11, 2026
// Program : Chapter 4 Major Project
// Option  : B — Royalty Advisor
// Purpose : Computes projected earnings for three publishing
//           contract options and recommends the best option.
// ============================================================

/*
==============================================================
SECTION 1 — PSEUDOCODE DESIGN BLOCK
==============================================================

BEGIN PROGRAM

Display title

Input net price per copy
Validate price is greater than zero

Input estimated copies sold
Validate copies sold is greater than zero

Calculate earnings for Option 1
    Flat delivery payment + publication payment

Calculate earnings for Option 2
    Royalty rate times net price times copies sold

IF copies sold is less than or equal to threshold
    Calculate Option 3 using lower royalty rate only
ELSE
    Calculate earnings on first threshold copies
    Calculate earnings on remaining copies
    Add both amounts together
END IF

Determine best option

IF Option 1 earnings are greater than Option 2
   AND Option 1 earnings are greater than Option 3
       Best option = 1

ELSE IF Option 2 earnings are greater than Option 1
        AND Option 2 earnings are greater than Option 3
       Best option = 2

ELSE IF Option 3 earnings are greater than Option 1
        AND Option 3 earnings are greater than Option 2
       Best option = 3

ELSE
       Tie exists
END IF

Perform floating-point tie checks using epsilon

IF tie exists
    Print tie message
ELSE
    Use switch statement
       CASE 1
           Recommend Option 1
       CASE 2
           Recommend Option 2
       CASE 3
           Recommend Option 3
       DEFAULT
           Print error message
    END SWITCH
END IF

Display operator showcase

Display formatted receipt

END PROGRAM
*/

#include <iostream>
#include <iomanip>
#include <cassert>
#include <cmath>

using namespace std;

// ============================================================
// SECTION 3 — OPERATOR PRECEDENCE REFERENCE
// ============================================================

/*
Precedence
Operator(s)      Category            Associativity
1 (highest)      !                   Logical NOT      Right-to-left
2                *, /, %             Multiplicative   Left-to-right
3                +, -                Additive         Left-to-right
4                <, <=, >, >=        Relational       Left-to-right
5                ==, !=              Equality         Left-to-right
6                &&                  Logical AND      Left-to-right
7 (lowest)       ||                  Logical OR       Left-to-right

Sample Evaluation

Assume:
copies = 5000
price = 12.50

Expression:

!(copies > 0) || (price >= 10.0 && copies != 4000)

Step 1:
(copies > 0)
(5000 > 0)
true

Step 2:
!(true)
false

Step 3:
(price >= 10.0)
(12.50 >= 10.0)
true

Step 4:
(copies != 4000)
(5000 != 4000)
true

Step 5:
(true && true)
true

Step 6:
(false || true)
true

Final Result = true
*/

int main()
{
    // ============================================================
    // NAMED CONSTANTS
    // ============================================================

    constexpr double FLAT_FEE_DELIVERY = 5000.00;
    constexpr double FLAT_FEE_PUBLICATION = 20000.00;

    constexpr double ROYALTY_RATE_2 = 0.125;

    constexpr double ROYALTY_RATE_3A = 0.10;
    constexpr double ROYALTY_RATE_3B = 0.14;

    constexpr int TIER3_THRESHOLD = 4000;

    constexpr double EPSILON = 0.01;

    // ============================================================
    // SECTION 2 — INPUT & VALIDATION
    // ============================================================

    double netPricePerCopy;
    int estimatedCopies;

    cout << "========== Royalty Advisor ==========\n\n";

    cout << "Enter net price per copy: $";
    cin >> netPricePerCopy;

    // Invariant: price must be positive.
    // If this assert fires, the program terminates immediately.
    assert(netPricePerCopy > 0.0);

    cout << "Enter estimated copies sold: ";
    cin >> estimatedCopies;

    // Invariant: copies sold must be positive.
    // If this assert fires, execution stops.
    assert(estimatedCopies > 0);

    // ============================================================
    // SECTION 4 — CORE LOGIC
    // ============================================================

    double option1Earnings =
        FLAT_FEE_DELIVERY + FLAT_FEE_PUBLICATION;

    double option2Earnings =
        netPricePerCopy * estimatedCopies * ROYALTY_RATE_2;

    double option3Earnings;

    // Compound Boolean expression using <=
    // Checks whether all sales fall inside the first royalty tier.
    if (estimatedCopies <= TIER3_THRESHOLD)
    {
        option3Earnings =
            estimatedCopies *
            netPricePerCopy *
            ROYALTY_RATE_3A;
    }
    else
    {
        option3Earnings =
            (TIER3_THRESHOLD *
             netPricePerCopy *
             ROYALTY_RATE_3A)
            +
            ((estimatedCopies - TIER3_THRESHOLD)
             * netPricePerCopy *
             ROYALTY_RATE_3B);
    }

    bool tieExists = false;
    int bestOption = 0;

    // ============================================================
    // SECTION 7 — FLOATING-POINT BUG GUARD
    // ============================================================

    /*
    Floating-Point Equality Warning

    Using == with floating-point numbers is unreliable because
    decimal values cannot always be represented exactly in binary.

    Instead, this program uses an epsilon comparison:

    fabs(a - b) < EPSILON

    EPSILON = 0.01

    Since earnings are displayed as money rounded to cents,
    a tolerance of one cent is appropriate.
    */

    bool tie12 =
        fabs(option1Earnings - option2Earnings) < EPSILON;

    bool tie13 =
        fabs(option1Earnings - option3Earnings) < EPSILON;

    bool tie23 =
        fabs(option2Earnings - option3Earnings) < EPSILON;

    if (tie12 || tie13 || tie23)
    {
        tieExists = true;
    }
    else if ((option1Earnings > option2Earnings) &&
             (option1Earnings > option3Earnings))
    {
        bestOption = 1;
    }
    else if ((option2Earnings > option1Earnings) &&
             (option2Earnings > option3Earnings))
    {
        bestOption = 2;
    }
    else
    {
        bestOption = 3;
    }

    // ============================================================
    // SECTION 6 — RELATIONAL & LOGICAL OPERATOR SHOWCASE
    // ============================================================

    cout << "\n========== Operator Showcase ==========\n";

    if (estimatedCopies > TIER3_THRESHOLD) // >
        cout << "Operator > : Sales exceed royalty threshold.\n";

    if (estimatedCopies < TIER3_THRESHOLD) // <
        cout << "Operator < : Sales below royalty threshold.\n";

    if (estimatedCopies <= TIER3_THRESHOLD) // <=
        cout << "Operator <= : Sales within first royalty tier.\n";

    if (estimatedCopies >= TIER3_THRESHOLD) // >=
        cout << "Operator >= : Sales reached threshold.\n";

    if (estimatedCopies != TIER3_THRESHOLD) // !=
        cout << "Operator != : Sales not exactly 4000.\n";

    if (estimatedCopies == TIER3_THRESHOLD) // ==
        cout << "Operator == : Sales exactly 4000.\n";

    if ((netPricePerCopy >= 10.0) &&
        (estimatedCopies > 1000)) // &&
    {
        cout << "Operator && : Strong sales projection.\n";
    }

    if ((estimatedCopies < 500) ||
        (netPricePerCopy > 50.0)) // ||
    {
        cout << "Operator || : One special condition met.\n";
    }

    if (!(estimatedCopies <= 0)) // !
    {
        cout << "Operator ! : Valid positive sales amount.\n";
    }

    // ============================================================
    // SECTION 5 — SWITCH STATEMENT
    // ============================================================

    cout << "\n========== Recommendation ==========\n";

    if (tieExists)
    {
        cout << "Tie detected between contract options.\n";
        cout << "Review contract details beyond earnings.\n";
    }
    else
    {
        switch (bestOption)
        {
            case 1:
                cout << "Recommend Option 1.\n";
                cout << "Guaranteed earnings regardless of sales.\n";
                break;

            case 2:
                cout << "Recommend Option 2.\n";
                cout << "Highest projected royalty earnings.\n";
                break;

            case 3:
                cout << "Recommend Option 3.\n";
                cout << "Tiered royalties maximize income.\n";
                break;

            default:
                cout << "Unable to determine recommendation.\n";
        }
    }

    // ============================================================
    // SECTION 8 — FORMATTED OUTPUT / RECEIPT
    // ============================================================

    cout << "\n\n========== ROYALTY PROJECTION ==========\n";

    cout << fixed << setprecision(2);

    cout << left << setw(35)
         << "Net Price Per Copy:"
         << right << "$"
         << setw(10)
         << netPricePerCopy << '\n';

    cout << left << setw(35)
         << "Estimated Copies Sold:"
         << right
         << setw(11)
         << estimatedCopies << '\n';

    cout << left << setw(35)
         << "Option 1 Earnings:"
         << right << "$"
         << setw(10)
         << option1Earnings << '\n';

    cout << left << setw(35)
         << "Option 2 Earnings:"
         << right << "$"
         << setw(10)
         << option2Earnings << '\n';

    cout << left << setw(35)
         << "Option 3 Earnings:"
         << right << "$"
         << setw(10)
         << option3Earnings << '\n';

    cout << "----------------------------------------------\n";

    if (tieExists)
    {
        cout << left << setw(35)
             << "Recommended Option:"
             << "TIE\n";
    }
    else
    {
        cout << left << setw(35)
             << "Recommended Option:"
             << bestOption << '\n';
    }

    return 0;
}

/*
==============================================================
Known Bug Risks
==============================================================

1. Floating-point equality
2. Invalid user input
3. Dangling else
==============================================================
*/
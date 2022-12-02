/**********************************************************************
 *  Mönsterigenkänning readme.txt
 **********************************************************************/

/**********************************************************************
 *  Empirisk    Fyll i tabellen nedan med riktiga körtider i sekunder
 *  analys      när det känns vettigt att vänta på hela beräkningen.
 *              Ge uppskattningar av körtiden i övriga fall.
 *
 **********************************************************************/
    
      N       brute       sortering
 ----------------------------------
    150	39	14
    200	92	37
    300	271	85
    400	646	161
    800	4053	485
   1600	32196	1607
   3200	crash	5697
   6400	crash	23390
  12800	crash	102528
  

/**********************************************************************
 *  Teoretisk   Ge ordo-uttryck för värstafallstiden för programmen som
 *  analys      en funktion av N. Ge en kort motivering.
 *
 **********************************************************************/

Brute:
Det måste vara O(n^4) ty det är 4 nestlade for-loopar.

Sortering:
Får:
O(n^2(log(n))).

Eftersom vi gör en nestlad for och en sortering med tidsalgo nlog(n) inuti.

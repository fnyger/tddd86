/**********************************************************************
 *  M�nsterigenk�nning readme.txt
 **********************************************************************/

/**********************************************************************
 *  Empirisk    Fyll i tabellen nedan med riktiga k�rtider i sekunder
 *  analys      n�r det k�nns vettigt att v�nta p� hela ber�kningen.
 *              Ge uppskattningar av k�rtiden i �vriga fall.
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
 *  Teoretisk   Ge ordo-uttryck f�r v�rstafallstiden f�r programmen som
 *  analys      en funktion av N. Ge en kort motivering.
 *
 **********************************************************************/

Brute:
Det m�ste vara O(n^4) ty det �r 4 nestlade for-loopar.

Sortering:
F�r:
O(n^2(log(n))).

Eftersom vi g�r en nestlad for och en sortering med tidsalgo nlog(n) inuti.

/**********************************************************************
 *  M?nsterigenk?nning readme.txt
 **********************************************************************/

/**********************************************************************
 *  Empirisk    Fyll i tabellen nedan med riktiga k?rtider i sekunder
 *  analys      n?r det k?nns vettigt att v?nta p? hela ber?kningen.
 *              Ge uppskattningar av k?rtiden i ?vriga fall.
 *
 **********************************************************************/
    
      N       brute       sortering
 ----------------------------------
    150	39		9
    200	92		14
    300	271		45
    400	646		75
    800	4053		271
   1600	32196		1287
   3200	257568		5147
   6400	2060544	23205
  12800	16484352	99952
  

/**********************************************************************
 *  Teoretisk   Ge ordo-uttryck f?r v?rstafallstiden f?r programmen som
 *  analys      en funktion av N. Ge en kort motivering.
 *
 **********************************************************************/

Brute:
Det m?ste vara O(n^4) ty det ?r 4 nestlade for-loopar.

Sortering:
F?r:
O(n^2(log(n))).

Eftersom vi g?r en nestlad for och en sortering med tidsalgo nlog(n) inuti.




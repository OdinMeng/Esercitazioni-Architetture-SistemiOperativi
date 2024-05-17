Laboratorio 4: Sincronizzazione
===============================

Si realizzi in C un semplice programma per la gestione di un
**autonoleggio** da parte di più operatori che lavorano in maniera
concorrente.

Il programma deve gestire un **parco macchine** definito nel file
catalog.txt. Tale file contiene, uno per riga, l'identificativo di una
macchina dell'autonoleggio. Si supponga che ad esempio l'autonoleggio
disponga di tre vetture e il file catalog.txt contenga:

corsa-1

corsa-2

polo

Il programma deve permettere di conoscere lo stato di ogni vettura (busy
o free), marcare la vettura come occupata e rilasciarla alla fine del
noleggio. Il programma opera su **un ciclo infinito** chiedendo
all'operatore quale operazione effettuare tramite l'inserimento di testo
nel terminale. Il programma deve stampare un ***prompt*** (qua riportato
in rosso), mentre l'utente inserisce il **comando** (qua riportato in
verde):

Command: view

Sono possibili quattro operazioni, di seguito descritte.

In caso l'operatore inserisca una operazione errata, il programma deve
stampare:

Unknown Command

Visualizzazione
---------------

view

Stampa lo stato del parco macchine, ovvero la lista delle vetture e il
loro stato.

L'output deve essere formattato come nel seguente esempio:

Car: corsa-1, status: **free**

Car: corsa-2, status: **free**

Car: polo, status: **busy**

Noleggio vettura
----------------

lock \<vettura\>

Esegue il lock della vettura, se essa non è in uso, per marcarla come
noleggiata. In caso il noleggio vada a buon fine, il programma stampa:

Car: \<vettura\> is now locked

In caso la vettura sia già noleggiata, stampa:

Error. Car \<vettura\> already locked

In caso la vettura non esista nel catalogo, stampa:

Cannot find car \<vettura\>

Termine del noleggio
--------------------

release \<vettura\>

Rilascia il noleggio della vettura, marcandola come libera se essa era
occupata. In questo caso, il programma stampa:

Car: \<vettura\> is now free

Se la vettura era libera stampa un messaggio di errore:

Error. Car \<vettura\> already free

In caso la vettura non esista nel catalogo, stampa:

Cannot find car \<vettura\>

Uscita dal programma del noleggio
---------------------------------

quit

Il programma termina. Si noti che lo stato del programma deve persistere
a un riavvio del programma.

**Suggerimenti:**

-   Più operatori possono operare simultaneamente, eseguendo più istanze
    del programma in parallelo.

-   Lo stato del sistema è unico: tutti gli operatori operano sullo
    stesso parco macchine

-   Si consiglia di risolvere il problema usando dei *named semaphores*,
    creandone uno per vettura

-   Il programma, dopo aver letto il catalogo da file, crea, se
    necessario i semafori. Si presti attenzione ai valori di
    inizializzazione dei semafori.

Istruzioni per la consegna
==========================

Il programma fornire un output con lo ***[stesso esatto
formato]{.underline}*** usato negli esempi.

Il programma deve poter lavorare con qualsiasi dato di input. La
correzione consisterà nell'esecuzione automatizzata del programma con un
input generato dal docente.

Per la consegna del programma, usare la piattaforma disponibile su:
<http://sisop-labs.inginf.units.it/> E' necessario registrarsi con la
mail **s\<...\>\@stud.units.it** (ovvero, sostituite ds con stud vostra
mail s\<...\>\@ds.units.it). Il caricamento sulla piattaforma permette
di controllare la correttezza del laboratorio ed è richiesto per
**sostenere l'esame**.

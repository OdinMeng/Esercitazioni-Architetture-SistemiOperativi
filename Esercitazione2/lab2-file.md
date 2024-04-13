Laboratorio 2: Gestione dei file in C
=====================================

Si realizzi un programma in C che stampa i dettagli di tutti i file
contenuti in una cartella e in tutte le sue sottocartelle. In altre
parole, il programma deve visitare ricorsivamente tutte le cartelle a
partire da una cartella radice, e stampare le seguenti informazioni su
ogni file o cartella che trova:

-   **Nome**: percorso completo del file relativo alla cartella radice

-   **Numero di Inode**

-   **Tipo**: si vedano i tipi che può assumere un inode a:
    <https://man7.org/linux/man-pages/man7/inode.7.html>

    -   Si considerino solo i casi: file, directory, symbolic link e
        FIFO

    -   Si stampino esattamente le diciture indicate al punto
        precedente. Si stampi other per altri tipi di inode.

-   **Dimensione**: in Byte

-   **Utente Proprietario**: user id e username, separati da spazio (si
    consideri la funzione getpwuid)

-   **Gruppo Proprietario**: group ID e nome del gruppo, separati da
    spazio (si consideri la funzione getgrgid)

Si consideri una cartella d'esempio contenente una cartella dir, la
quale contiene il file test.

L'output deve essere **tassativamente** formattato seguendo il seguente
esempio:

**\$./list .**

Node: .

Inode: 15482892

Type: directory

Size: 4096

Owner: 1000 martino

Group: 1000 martino

Node: ./dir

Inode: 15482893

Type: directory

Size: 4096

Owner: 1000 martino

Group: 1000 martino

Node: ./dir/test

Inode: 15472878

Type: file

Size: 1

Owner: 1000 martino

Group: 1000 martino

Istruzioni per la consegna
==========================

Il programma fornire un output con lo ***[stesso esatto
formato]{.underline}*** usato negli esempi.

Il programma deve poter lavorare con qualsiasi dato di input. La
correzione consisterà nell'esecuzione automatizzata del programma con un
input generato dal docente.

Per la consegna del programma, usare la funzione *Assignments* su
Microsoft Teams, facendo l'upload di ***[un singolo file]{.underline}***
nell'*assignment* relativo a questa esercitazione. Nel caso
l'esercitazione richieda un programma in C, va consegnato il **file
sorgente** e non il programma compilato.

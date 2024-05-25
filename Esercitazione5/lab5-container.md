Laboratorio 5: Container
========================

Si realizzi in Bash una semplice Container Engine che funziona **senza
richiedere privilegi di amministratore**. Essa deve permettere di
eseguire un programma in un ambiente isolato. La Container Engine si
utilizza con la seguente sintassi:

**container-run.sh conf-file command**

Dove conf-file è **un file testuale** che elenca (gli unici) file o
cartelle che devono essere disponibili all'interno container. La
Container Engine deve costruire un opportuno albero di cartelle e file
come specificato in tale file.

Esso contiene una voce per riga, e ogni voce rappresenta un **file** o
una **cartella** da inserire nel container. Ogni voce è composta da due
path separati da spazio: il primo path è relativo al file system del
computer e indica da dove prelevare il file (o cartella), mentre il
secondo path indica dove collocare quel file (o cartella) all'interno
del container. Ad esempio, se il file contiene:

/usr/bin/ls /bin/ls

/usr/bin/ps /bin/ps

/bin/bash /bin/bash

/lib /lib

/lib64 /lib64

Significa che il file /usr/bin/ls nel file system del computer deve
essere reso disponibile nel container al path /bin/ls. Ovvero deve
essere possibile eseguire la riga di comando:

./container-run.sh conf-file.txt /bin/ls

Si osservi attentamente che il secondo argomento è **/bin/ls** e non
**~~/usr/bin/ls~~**. Similmente, la cartella /lib deve essere
disponibile nel container in /lib.

Il **secondo argomento** è il comando da eseguire all'avvio del
container, ovvero il programma da eseguire. Esso rappresenta un file
(eseguibile) valido per il container (ovvero rappresenta un file che
viene incluso nel container dal file di configurazione). Ad esempio,
considerando il file di configurazione riportato in precedenza, una riga
di comando valida è:

./container-run.sh conf-file.txt /bin/bash

Questo comando crea il container con i file e le cartelle specificate in
conf-bash.txt ed esegue il comando /bin/bash

Eventuali **argomenti successivi** devono essere passati come argomenti
al comando eseguito. Ad esempio: ./container-run.sh conf-file.txt
/bin/ls -lh /lib

deve eseguire il programma /bin/ls con argomenti -lh /lib. A tal fine
può essere utile usare l'espressione \"\${@:2}\" che fornisce la lista
di argomenti di uno script Bash ad esclusione dei primi due.

**Suggerimenti**: la *container engine* dovrà verosimilmente svolgere
questi passi:

1.  Creare una **directory temporanea** di lavoro dove collocare i file
    e le cartelle indicate nel file di configurazione.

2.  Collocare i file e le cartelle specificati nel file di
    configurazione nella directory temporanea di lavoro**. Non bisogna
    copiare le cartelle**, ma è necessario semplicemente creane un alias
    con il comando: bindfs \--no-allow-other \$ORIGIN \$DST. I **file**
    singoli (come le prime tre righe del file di configurazione
    d'esempio) invece vanno **copiati** (bindfs non monta singoli file).
    Si utilizzi un semplice ciclo for che itera sulle righe del file di
    configurazione (può essere necessario impostare la variabile
    IFS=\$\'\\n\' prima del ciclo for).

3.  Usare fakechroot per eseguire il programma richiesto "all'interno"
    della directory di lavoro, in modo che non possa quindi accedere a
    file e cartelle esterni:

    -   La sintassi è: fakechroot chroot WORKDIR COMMAND

Note
====

Per installare **BindFS** e **FakeChRoot** su Ubuntu (o su WSL) usare:

sudo apt-get install bindfs fakechroot

Su Mac, è possibile installare BindFS tramite Mac Ports, ma non
FakeChRoot.

Istruzioni per la consegna
==========================

Il programma fornire un output con lo ***[stesso esatto
formato]{.underline}*** usato negli esempi (che in questo caso è
l'output del comando lanciato nella container engine).

Il programma deve poter lavorare con qualsiasi dato di input. La
correzione consisterà nell'esecuzione automatizzata del programma con un
input generato dal docente.

Per la consegna del programma, usare la piattaforma disponibile su:
<http://sisop-labs.inginf.units.it/> E' necessario registrarsi con la
mail **s\<...\>\@stud.units.it** (ovvero, sostituite ds con stud vostra
mail s\<...\>\@ds.units.it). Il caricamento sulla piattaforma permette
di controllare la correttezza del laboratorio ed è richiesto per
**sostenere l'esame**.

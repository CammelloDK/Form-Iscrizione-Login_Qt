Il progetto richiede la creazione di un form di iscrizione e login

Le funzionalità attese sono le seguenti:

• Iscrizione con obbligo di inserire: nome, cognome, numero di cellulare o
e-mail, password, data di nascita, e genere. Prima di confermare l’iscrizione deve essere verificato che l’utente non sia già registrato (e- mail e/o numero di telefono non presenti) e sia maggiorenne. L’iscrizione viene confermata con l’apertura di una dialog che dia il benvenuto all’utente registrato;

• Login con verifica che l’utente e la password corrispondano. In caso di corrispondenza viene aperta una dialog che conferma l’accesso riuscito;

• Recupero password in cui viene aperta una dialog di conferma “e-mail con procedura di ripristino inviata” solo se si è verificata l’esistenza dell’utente (e-mail e/o password);

• Login utente admin (email: admin@pas.com, password: admin) che possa:
	- Accedere ad un elenco delle persone iscritte;
	- Visualizzare due grafici a torta:
		-- Nel primo mostrare la percentuale di uomini e donne iscritte al portale
		-- Nel secondo la percentuale di persone rispetto all’età (dividendo le età 5 in gruppi, ad esempio 18-26, 27-35, 36-44, 45-53, e 54+)


Nota 1: Utilizzate la versione 5.12 della libreria Qt.

Nota 2: Sui dati immessi in fase di iscrizione effettuare un controllo di coerenza di formato: email <testo>@<dominio>.it, 31/02/1988, ecc.

Nota 3: I dati degli utenti devono essere salvati in un file (*.csv) per poter garantire la persistenza tra sessioni diverse e altresì consentire il controllo di quali utenti siano già iscritti.

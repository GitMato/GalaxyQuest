**Course:** otekn-2017-2018 - TIE-02400 Ohjelmoinnin tekniikat 2017-2018

**Title:** Feedback from teacher

**Date:** 2017-12-30 12:51

**For:**
    Hanna Enqvist (hanna.enqvist@student.tut.fi)
    Tomi Mannila  (tomi.mannile@student.tut.fi)

**Feedback:**
```
Saitte työstänne arvosanaksi 4.
Työ oli erinomainen ja pidin grafiikasta todella paljon. Olisi kuitenkin kaivannut jonkun lisäosan 
tai pientä pelattavuuden hiomista parempaan arvosanaan.

Arvostelualueet:

SUUNNITTELU
+ Luokkajako ja luokkien vastuut ovat järkevät.
+ Ohjelmaan on toteutettu erilliset tyypit toiminnallisille osille ja käyttöliittymään piirrettäville kuville.
+ Toteutettu periytyminen kunnossa.
- Pelaaja-alusta ei periytetty Ship-luokasta. Omia actioneita ei ole periytetty Action-luokasta.
+ Omille luokille on kirjoitettu hyvät rajapintamäärittelyt.
+ Rajapintadokumentaatio niin hyvä, että siitä voidaan generoida ulkopuolinen dokumentaatio.

TOTEUTUS
+ Esi- ja jälkiehdot + invariantit tarkastetaan Hyvin
+ Poikkeukset toteutettu hyvin
* Invariantin tarkastamista rakentajassa on varsin turhaa, jos siinä vain alustetaan muuttujien arvoja.
+ Poikkeustilanteiden käsittely on hoidettu hyvin.
+ Dynaaminen muistinhallinta on tehty hyvin älykkäillä osoittimilla.
+ Hyvää C++:aa ja olio-ohjelmoinnin periaatteet kunnossa.
* Luokkien rakentajissa ei ole käytetty alustuslistoja.
* Olion tilaa muokkaamattomat metodit olisi hyvä määritellä const-avainsanalla
* Jokaiselle luokan instanssille saman arvon omaavat vakiot olisi hyvä määritellä luokkavakioiksi.
+ Qt:ta ja sen mekanismeja on käytetty erinomaisesti.
- Kääntäjä antaa koodista varoituksia. Ne olisi paras käydä läpi ja siivota pois.

TOIMINNALLISUUS
+ Peli toimii siististi.
+ Käyttöliittymään on selkeästi nähty vaivaa.
- Pienehkö miinus siitä, ettei pelaajan alus noudata muiden aluksien tapaan rajoituksia liikkumisen 
  tai toimintojen suhteen.

KOODIN ULKONÄKÖ JA TYYLI
+ Koodi on kaikinpuolin siistiä ja hyvin tehtyä.
+ Doxygen kommentointi.
+ Hyvin käytetty vakioita.
* Poiskommentoitua koodia ei kannata jättää roikkumaan. Versionhallinta on sitä varten, jos halutaan 
  palauttaa aiempia koodipätkiä. Muistilistana ok, mutta kunhan nostan esille.

YKSIKKÖTESTAUS
+ Testit ovat hyviä ja kattavia
- Yksi testitapaus sisältää kaikki metodille suoritettavat testit. Tämä vaikeuttaa esimerkiksi virheen 
  aiheuttajan paikantamista.

DOKUMENTAATIO
+ Ohjelman luokat ja niiden merkitys kuvataan hyvin.
+ Dokumentaatio sisältää ohjeet pelin pelaamiseen (kontrollit, mekaniikat, tavoitteet).
+ Omasta toteutuksesta laadittu doxygen-dokumentaatio
+ Ryhmän sisäinen työnjako kuvattu.
* Luokkakaavio olisi hyvä tuki luokkien välisten suhteiden kuvaukseen.

VERSIONHALLINNAN KÄYTTÖ
+ Commitit on tehty sopivan pienissä paloissa.
+ Lokiviestit ovat hyvin selkeitä ja kuvaavia.
+ Versiohistorian perusteella työ jakatunut tasaisesti
- Git-asetuksia ei ole laitettuna kuntoon kummallakaan.

LISÄOSAT
Lisäosa 1: Kartta seuraa pelaajan alusta.
 Ok.
Lisäosa 2: Lista lähellä sijaitsevista aluksista.
 Käytännössä tähtijärjestelmässä olevien aluksien lisäksi näytetään lähellä olevien tähtijärjestelmien 
 aluksia myös. Pieni bonus kuitenkin.
Lisäosa 3: Itse tehdyt peligrafiikat.
 Ei itsessään ole koodaamista, mutta huomioiden käytetyn aikamäärän ja käyttöliittymän tason on lisäosa 
 pisteiden arvoinen.
```

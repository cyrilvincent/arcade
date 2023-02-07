
    TTTTTTTTTTTTTT  HH          HH  OOOOOOOOOOOOOO  MM          MM
    TTTTTTTTTTTTTT  HH          HH  OOOOOOOOOOOOOO  MMM        MMM
          TT        HH          HH  OO          OO  MMMM      MMMM 
          TT        HH          HH  OO          OO  MM MM    MM MM
          TT        HH          HH  OO          OO  MM  MM  MM  MM 
          TT        HHHHHHHHHHHHHH  OO          OO  MM   MMMM   MM
          TT        HHHHHHHHHHHHHH  OO          OO  MM    MM    MM
          TT        HH          HH  OO          OO  MM          MM
          TT        HH          HH  OO          OO  MM          MM
          TT        HH          HH  OO          OO  MM          MM
          TT        HH          HH  OOOOOOOOOOOOOO  MM          MM
          TT        HH          HH  OOOOOOOOOOOOOO  MM          MM 

                       L'�mulateur Thomson TO7-70
                              version 1.5.4

    Copyright (C) 1996 Sylvain Huet, 1999-2003 Eric Botcazou.



1. Introduction
---------------
Thom est un �mulateur du micro-ordinateur Thomson TO7-70 pour PC, fonction-
nant sous MSDOS, Windows et Linux. Il est bas� sur la version 1.5 de l'�mu-
lateur FunzyTO7-70 de Sylvain Huet et y introduit de nombreuses nouveaut�s.


2. Comment l'obtenir ?
----------------------
En le t�l�chargeant depuis la page:

   http://nostalgies.thomsonistes.org/thom_home.html

L'archive principale contient le programme �x�cutable de l'�mulateur et la
documentation compl�te; pour des raisons de copyright, les ROMs du TO7-70
n�cessaires � son fonctionnement n'y sont pas incluses, vous devez les
t�l�charger � partir d'une deuxi�me archive et les installer dans le m�me
r�pertoire que le programme �x�cutable.


3. Compatibilit� avec le TO7-70
-------------------------------
La compatibilit� est proche de 100% pour les logiciels n'utilisant pas de
p�riph�riques non �mul�s et ne contenant pas de protection physique. En
d'autres termes, si un logiciel ne tourne pas sous Thom, alors probablement:
- il requiert la pr�sence d'un p�riph�rique externe autre que la souris,
  le crayon optique, les manettes, le lecteur de cassettes (et donc il ne
  tournera pas tant que ce p�riph�rique ne sera pas �mul�),
- ou sa protection physique l'a fait �chou�.

Je maintiens une liste des logiciels tournant sous Thom; si vous en poss�dez
un qui pose probl�me, envoyez-le moi, j'essaierai d'identifier la cause du
dysfonctionnement et je vous dirai s'il est possible d'y rem�dier.


4. Probl�mes connus
-------------------
- la d�tection automatique de la carte son dans la version MSDOS peut
  �chouer; vous pouvez dans ce cas sp�cifier manuellement les
  caract�ristiques de la carte (type de carte, adresse du port, canal DMA
  et num�ro d'IRQ) en �ditant le fichier allegro.cfg du r�pertoire principal.


5. Conclusion
-------------
J'esp�re que Thom r�pondra � vos attentes; n'h�sitez pas � me faire part de
vos remarques et suggestions.


Eric Botcazou
e-mail: ebotcazou@libertysurf.fr


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

                       L'émulateur Thomson TO7-70
                              version 1.5.4

    Copyright (C) 1996 Sylvain Huet, 1999-2003 Eric Botcazou.



1. Introduction
---------------
Thom est un émulateur du micro-ordinateur Thomson TO7-70 pour PC, fonction-
nant sous MSDOS, Windows et Linux. Il est basé sur la version 1.5 de l'ému-
lateur FunzyTO7-70 de Sylvain Huet et y introduit de nombreuses nouveautés.


2. Comment l'obtenir ?
----------------------
En le téléchargeant depuis la page:

   http://nostalgies.thomsonistes.org/thom_home.html

L'archive principale contient le programme éxécutable de l'émulateur et la
documentation complète; pour des raisons de copyright, les ROMs du TO7-70
nécessaires à son fonctionnement n'y sont pas incluses, vous devez les
télécharger à partir d'une deuxième archive et les installer dans le même
répertoire que le programme éxécutable.


3. Compatibilité avec le TO7-70
-------------------------------
La compatibilité est proche de 100% pour les logiciels n'utilisant pas de
périphériques non émulés et ne contenant pas de protection physique. En
d'autres termes, si un logiciel ne tourne pas sous Thom, alors probablement:
- il requiert la présence d'un périphérique externe autre que la souris,
  le crayon optique, les manettes, le lecteur de cassettes (et donc il ne
  tournera pas tant que ce périphérique ne sera pas émulé),
- ou sa protection physique l'a fait échoué.

Je maintiens une liste des logiciels tournant sous Thom; si vous en possédez
un qui pose problème, envoyez-le moi, j'essaierai d'identifier la cause du
dysfonctionnement et je vous dirai s'il est possible d'y remédier.


4. Problèmes connus
-------------------
- la détection automatique de la carte son dans la version MSDOS peut
  échouer; vous pouvez dans ce cas spécifier manuellement les
  caractéristiques de la carte (type de carte, adresse du port, canal DMA
  et numéro d'IRQ) en éditant le fichier allegro.cfg du répertoire principal.


5. Conclusion
-------------
J'espère que Thom répondra à vos attentes; n'hésitez pas à me faire part de
vos remarques et suggestions.


Eric Botcazou
e-mail: ebotcazou@libertysurf.fr

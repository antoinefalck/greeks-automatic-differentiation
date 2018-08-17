Tangent Automatic Differentiation sur une option basket
=======================================================


Prerequis
---------

Pour exectuter ce programme il vous faudra avoir installer
	- c++11
	- le package Armadillo (arma.sourceforge.net).

Il vous faudra aussi posseder le compilateur g++.


Installation
------------

Pour les utilisateurs Unix uniquement
Placez vous dans le dossier contenant les sources
Entrer la commande

	make && make clean


Utilisation
-----------

Pour lancer l'execution, apres vous etre place dans le dossier contenant l'executable, lancer la commande

	./main <precision>

où <precision> est le parametre qui gere la precision souhaitee dans la simulation de Monte Carlo (cf rapport).

Parametres
----------

Le seul parametre qui doit etre modifier dans le code est la poids sur les derivees 'a' (cf rapport)

La precision est specifiee au lancement (voir section precedente)
Pour les autres parametres (matrice de variance covariance, etc.) ils peuvent etre modifies dans les fichiers texte correspondants dans le dossier './data'.
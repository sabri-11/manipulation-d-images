Compilez et exécutez depuis un terminal sur linux à l'aide de la commande :

gcc -Wall -Wfatal-errors lodepng.c noir_et_blanc.c -o noir_et_blanc && ./noir_et_blanc image.png image_noir_et_blanc.png

Une image de chat en couleur est donnée mais vous pouvez la remplacer par l'image que vous voulez si vous le souhaitez. Il faudra cependant : soit renommer l'image que vous prenez par "image.png", soit modifier la ligne de commande d'exécution en remplançant "image.png" par le nouveau nom de votre image

------------------------------------------------------------------------------------------------------------------------------------------------------
Bonjour,

Le but de ce programme est de transformer une image en couleur en une image noire et blanc. Une image noire et blanc a la particulatité que pour chaque pixel, la quantité de rouge, de vert de de bleu est la même. Pour convertir une image couleur en noir et blanc, on remplace simplement, pour chaque pixel, la valeur de rouge, de vert et de bleu par la moyenne de ces trois valeurs.

# 1 Configurer le PORT Gpio pour l'arret du Raspberry Pi
## Ouvrir le fichier de config boot
	cd /boot/firmware/
	sudo nano config.txt

 ## Ajouter le port GPIO
	dtoverlay=gpio-shutdown,gpio_pin=25,active_low=1,gpio_pull=up

# 2 Configurer l'afficheur OLED
## Creer le fichier infoscreen.sh
	nano infoscreen.sh
##
	#!/bin/bash
	cd env
	source ~/env/bin/activate
	nohup python infoscreen.py

## Enregistrer
	CTRL+o
	CTRL+x
	
## Rendre le fichier infoscreen.sh executable
	sudo chmod +x infoscreen.sh



infoscreen.sh

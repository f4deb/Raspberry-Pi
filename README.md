# 1 Configurer le PORT Gpio pour l'arret du Raspberry Pi
## Ouvrir le fichier de config boot
	cd /boot/firmware/
	sudo nano config.txt

 ## Ajouter le port GPIO
	dtoverlay=gpio-shutdown,gpio_pin=25,active_low=1,gpio_pull=up

# 2 Configurer l'afficheur OLED
## Installer Adafruit_Blinka
	sudo apt-get update
	sudo apt-get upgrade
##
	cd ~
	python3 -m venv env --system-site-packages
##
	source env/bin/activate

## Bibliotheque adafruit !!!!

	pip3 install adafruit-circuitpython-ssd1306
	
##
	pip3 install --upgrade adafruit-python-shell
	pip3 install rpi-lgpio
	wget https://raw.githubusercontent.com/adafruit/Raspberry-Pi-Installer-Scripts/master/raspi-blinka.py
	sudo -E env PATH=$PATH python3 raspi-blinka.py

## Creer le fichier infoscreen.sh
	nano infoscreen.sh
##
	#!/bin/bash
	source env/bin/activate
	nohup python3 infoscreen.py

## Enregistrer
	CTRL+o
	CTRL+x
	
## Rendre le fichier infoscreen.sh executable
	sudo chmod +x infoscreen.sh

# créer le fichier crontab pour autostart terminal
	crontab -e

## Ajouter le texte à la fin

	@reboot python3 /home/f4deb/clignote.py
	@reboot ./infoscreen.sh

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
	pip install pillow
	pip install psutil

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

#Serveur Web
## Installer le serveur Apache2
	
	sudo apt install apache2
	sudo chown -R f4deb:www-data /var/www/html/
	sudo chmod -R 770 /var/www/html/

## Test

	http://Serveur-IP/index.html

## Installer PHP

	sudo apt install php php-mbstring
	sudo rm /var/www/html/index.html
	echo "<?php phpinfo(); ?>" > /var/www/html/index.php

## Test

	http://Serveur-IP/index.php

## Installer MySql

	sudo apt install mariadb-server php-mysql

## Se connecter à la base
	sudo mysql --user=root

## modifier l'utilisateur principal
	DROP USER 'root'@'localhost';
	CREATE USER 'root'@'localhost' IDENTIFIED BY 'password';
	GRANT ALL PRIVILEGES ON *.* TO 'root'@'localhost' WITH GRANT OPTION;

# PHPMyAdmin
## Installation	
	sudo apt install phpmyadmin

	PHPMyAdmin vous posera plusieurs questions concernant ses réglages.

	Comme nous avons déjà configurez la base de données, choisissez no à la question concernant l’utilisation de dbconfig-common. Choisissez d’utiliser PHPMyAdmin pour un serveur Apache. Pour le mot de passe root, il s’agit de celui que vous aviez utilisé pour MySQL.
	sudo phpenmod mysqli
	sudo /etc/init.d/apache2 restart
	
## Test

	http://Serveur-IP/phpmyadmin

# Changement de port SSH

	sudo nano /etc/ssh/sshd_config
	modifier #Port 22
	sudo reboot

	Nouvelle Connexion : ssh -p xxxx id@address

# Connexion par cle public	

## Générer la clé public sur le Terminal
	
	ssh-keygen -t ed25519

## Sur le serveur
	Protéger les clés
	sudo chmod 700 ~/.ssh
	sudo chmod 600 ~/.ssh/authorized_keys

	Transferer la cle publique dans
	cd ~/.ssh
	nano authorized_keys
	Ajouter la clé publique
	



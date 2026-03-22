# Ouvrir le fichier de config boot
cd /boot/firmware/
sudo nano config.txt

# ajouter le port GPIO
dtoverlay=gpio-shutdown,gpio_pin=25,active_low=1,gpio_pull=up



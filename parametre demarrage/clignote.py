# Ce code Raspberry Pi a été développé par newbiely.fr
# Ce code Raspberry Pi est mis à disposition du public sans aucune restriction.
# Pour des instructions complètes et des schémas de câblage, veuillez visiter:
# https://newbiely.fr/tutorials/raspberry-pi/raspberry-pi-led


import RPi.GPIO as GPIO
import time

# Set the GPIO mode and warning
GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)

# Define the GPIO18 pin number
led_pin = 23

# Setup the GPIO pin as an output
GPIO.setup(led_pin, GPIO.OUT)

# Function to blink the LED
def blink_led():
    GPIO.output(led_pin, GPIO.HIGH)
    time.sleep(1)  # LED on for 1 second
    GPIO.output(led_pin, GPIO.LOW)
    time.sleep(1)  # LED off for 1 second

try:
    # Run the LED blinking forever until a keyboard interrupt (Ctrl + C)
    while True:
        blink_led()

except KeyboardInterrupt:
    # Cleanup GPIO settings on keyboard interrupt
    GPIO.cleanup()

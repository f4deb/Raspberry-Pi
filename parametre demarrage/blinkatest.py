import board
import digitalio
import busio

print("Hello blinka!")

# Essayer de créer une entrée numérique
pin = digitalio.DigitalInOut(board.D17)
print("Digital IO ok!")

# Essayer de créer un périphérique I2C
i2c = busio.I2C(board.SCL, board.SDA)
print("I2C ok!")

# Essayer de créer un périphérique SPI
spi = busio.SPI(board.SCLK, board.MOSI, board.MISO)
print("SPI ok!")

print("done!")

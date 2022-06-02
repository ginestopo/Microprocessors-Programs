from machine import Pin
from time import sleep
import time
import network
from utelegram import Bot, Conversation  #telegram library

TOKEN = ""
bot = Bot(TOKEN)

led = Pin(2,Pin.OUT)

def led_trying_to_connect():
    led.value(not led.value())
    sleep(0.1)
    led.value(not led.value())
    sleep(0.1)
    led.value(not led.value())
    sleep(0.1)
    led.value(not led.value())
    sleep(0.5)


def led_wifi_connected():
    led.value(1)


def do_connect():
    wlan = network.WLAN(network.STA_IF)
    wlan.active(True)
    if not wlan.isconnected():
        print('connecting to network...')
        wlan.connect('Orange_Swiatlowod_B9A0', 'DZ36V3ULC9ZX')
        while not wlan.isconnected():
            led_trying_to_connect()
    else:
        print("Successfully connected!")
        print('network config:', wlan.ifconfig())

        led_wifi_connected()

#--------Bot functionality-----------
@bot.add_command_handler('start')
def start(update):
    print("/start received")
    update.reply('hello Ginés, how are you doing?')
#------------------------------------


def main():
    do_connect()
    #bot.start_loop()

if __name__ == "__main__":
    main()

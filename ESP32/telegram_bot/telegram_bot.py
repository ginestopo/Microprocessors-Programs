from machine import Pin
from time import sleep


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
    import network
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


def main():
    do_connect()


if __name__ == "__main__":
    main()

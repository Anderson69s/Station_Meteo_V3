# Station Météo V3 by Anderson69s

Forked from sirleech's Thingspeak <https://github.com/sirleech/thingspeak>
Forked from Nicolas Wilde's Thingspeak <https://github.com/nicholaswilde/thingspeak-raspberry-pi.git>
Forked Libraries from SeeedStudio <http://www.seeedstudio.com/wiki/index.php?title=Main_Page#Grove>

More informations :

Included :

- ThingSpeak Python scripts for the Raspberry Pi.
- Code & libraries for Arduino
- Schema

Example: https://thingspeak.com/channels/50560

YOU NEED A THINGSPEAK ACCOUNT (FREE) & YOU HAVE TO ADD YOUR PRIVATE KEY IN BOTH PYTHON SCRIPT

## Installation instructions for thingspeak_cpu_loop.py ONLY:

```
$ sudo apt-get install python-psutil
$ cd /home/pi
$ wget https://github.com/nicholaswilde/thingspeak-raspberry-pi.git
$ cd thingspeak-raspberry-pi
$ edit thingspeak_cpu_loop.py and add you key
$ sudo chmod +x thingspeak_cpu_loop.py
$ python thingspeak_cpu_loop.py
$ sudo crontab -e
$ add at end :
$ @reboot sudo python /home/pi/thingspeak-raspberry-pi/thingspeak_cpu_loop.py &
$ save and reboot




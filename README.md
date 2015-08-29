# Station Météo V3 by Anderson69s

- Forked from sirleech's Thingspeak <https://github.com/sirleech/thingspeak>
- Forked from Nicolas Wilde's Thingspeak <https://github.com/nicholaswilde/thingspeak-raspberry-pi.git>
- Forked Libraries from SeeedStudio <http://www.seeedstudio.com/wiki/index.php?title=Main_Page#Grove>

More informations on my site : <http://wp.me/p2fQa9-17f>

Included :

- ThingSpeak Python scripts for the Raspberry Pi.
- Code & libraries for Arduino
- Schema

Example : <https://thingspeak.com/channels/50560>

###YOU NEED A THINGSPEAK ACCOUNT (FREE) & YOU HAVE TO ADD YOUR PRIVATE KEY IN BOTH PYTHON SCRIPT

## Installation instructions for thingspeak_cpu_loop.py ONLY:

```
$ sudo apt-get install python-psutil
$ cd /home/pi
$ mkdir thingspeak/
$ wget https://github.com/anderson69s/Station_Meteo_V3/Raspberry/thingspeak_cpu_loop.py
$ Edit the script and add your key, 
$ Save and quit
$ sudo chmod +x thingspeak_cpu_loop.py
$ sudo crontab -e
$ Add at end :
$ @reboot sudo python /home/pi/thingspeak-raspberry-pi/thingspeak_cpu_loop.py &
$ Save and reboot




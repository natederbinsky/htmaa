# Notes

## Setup
1. Update
  * `sudo apt-get update`
  * `sudo apt-get upgrade`
1. WiFi GUI
  * `sudo apt-get install wpagui`
  * Run `wpa_gui`, configure, save
1. SSH
  * `sudo raspi-config`
  * Advanced, Enable SSH
  * Set Password
1. VNC
  * https://www.raspberrypi.org/documentation/remote-access/vnc/
  * `sudo apt-get install tightvncserver`
  * `tightvncserver` (set password)
  * `vncserver :1 -geometry 1024x768 -depth 24`
1. DNS: .local
  * `sudo apt-get install avahi-daemon`
  * `sudo raspi-config` advanced, hostname
  * Reboot

## Coding
1. Arduino/Pi Communication
  * http://www.seeedstudio.com/recipe/166-basic-pi-lt-gt-arduino-communication-over-usb.html
1. CmdArduino
  * https://github.com/joshmarinacci/CmdArduino
1. Flask
  * http://mattrichardson.com/Raspberry-Pi-Flask/
  * http://code.tutsplus.com/tutorials/creating-a-web-app-from-scratch-using-python-flask-and-mysql--cms-22972

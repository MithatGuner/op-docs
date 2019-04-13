## Installation  

```  
opkg update
opkg install ser2net
```  

## Configuration  

### Configuring ser2net

You should edit the file */etc/config/ser2net* look like:  

```  
config proxy
    option enabled 1
    option port 5002
    option protocol raw
    option timeout 0
    option device '/dev/ttyATH0'
    option baudrate 115200
    option databits 8
    option parity 'none'
    option stopbits 1
```  

**protocol**: It supports raw, telnet  
**device**: The serial device, it usually is /dev/ttyS0, but for ar9331, it should be /dev/ttyATH0

### Disable Debug Console

If the router only has one UART, you have to comment out *::askconsole:/bin/ash --login* in */etc/inittab* to disable debug console, so that you can use it to communicate with other.

```  
::sysinit:/etc/init.d/rcS S boot
::shutdown:/etc/init.d/rcS K shutdown
# ::askconsole:/bin/ash --login
```  

## Start ser2net

Reboot the unit now.  

```  
reboot
```  

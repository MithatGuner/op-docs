## General

### PS4 keeps asking for a proxy server when it connected to GL.iNet's routers?  

The presenting problem is that you are using GL.iNet's router, your Cellphone and Tablet connected via Wlan to the mini router and they’re working as aspected. When you try to connect a PS4 and it doesn’t matter how to connect it (LAN or Wlan) the PS4 keeps asking for a PROXY server and cancelled the process.

When that happens, it might causes by captive portal. Please try to turn off the DNS Rebinding Attack Protection, which can be found in MORE SETTING > Custom DNS.

### How to get Chromecast to work on GL.iNet's routers?  

The OpenWRT has disabled IGMP snooping by default, you can try to enable it.
 
```  
# opkg update
# opkg install kmod-bridge
 
# uci set network.lan.igmp_snooping=1
# uci commit network
# echo "1" > /sys/devices/virtual/net/br-lan/bridge/multicast_snooping
 
# reboot
``` 

## Network

### How to Force the modem to 4G?  

In some case, it always show 3G signal in web UI, but there has LTE band in your area, so you can try to force the modem to 4G mode only. 

SSH to the router, and execute below command.

```
echo -e "AT+QCFG=\"nwscanmode\",3,1" > /dev/ttyUSB2
```  

If you want to revert back to automatic mode, execute this command.

```  
echo -e "AT+QCFG=\"nwscanmode\",0,1" > /dev/ttyUSB2
```  

### Why the router keep rebooting after connected a LTE module to it?  

If the LTE modem module is pulling more than 500mA from the usb port then you won't be able to use it with the router. But in general, it won't pull more than 500mA. If a TLE modem module pull more than 500mA, it usually has an additional port for you to pipe-in power to it. You can connect a USB Y cable to that port.  

### How can I change the VLAN for PPPoE?  

You may be unable to make PPPoE connection with GL.iNet's mini routers. A possible reason is that VDSL providers usually require a VLAN ID set (the ID depends on the specific ISP). Such as Cyta, it requires a VLAN ID of 835.  

Take Cyta as an example, you need to edit the file */etc/config/network*. A driver-level VLAN could be created in the interface section by adding a dot (.) and the respective VLAN ID after the interface name (in the ifname option), like eth1.2 for VLAN ID 2 on eth1. So the changed looks like:  

```  
config 'interface' 'wan'
    option 'proto'     'pppoe'
    option 'ifname'    'eth0.835'
    option 'username'  'user'
    option 'password'  'pass'
    option 'timeout'   '10'
```  

Please refer to [switch_configuration](https://openwrt.org/docs/guide-user/network/vlan/switch_configuration#creating_driver-level_vlans) for more details.  

## Wireless

### Cannot Open the Login Page of Public WiFi?

When you are traveling with mini-router, you might use it as a repeater to connect a public WiFi. Most public WiFi will lead you to an authentication page, you have to be certified to access the Internet.

When your mini-router was connected to a public WiFi, and your mobile phone or laptop connects to the mini-router, but cannot popup the login page. You can check out.

- Disable all VPN connections on router
- Disable DNS rebinding protection on router, you can find it in MORE SETTING > Custom DNS
- Even then Chrome/Firefox might block the attempt to redirect because it will be expecting an ssl site. Please enter neverssl.com in the browser's address bar so that you get redirected to the captive portal

### How to Connect a Hidden AP with MT300N-V2?  

1. Connect to a non-hidden SSID on web UI  
2. Kill and remove the process **gl_health** with the command 
  ```
  killall gl_health && mv /usr/bin/gl_health /usr/bin/gl_health1
  ```  
3. Set the hidden WiFi to wireless and restart network

  ```
  uci set wireless.sta.ssid=yourssid
  uci set wireless.sta.channel=yourchannel
  uci set wireless.sta.key=yourwifikey
  uci set wireless.sta.bssid=yourbssidhere
  uci set wireless.sta.encryption=psk2
  
  uci set wireless.mt7628.channel=yourchannel
  
  uci commit wireless
  
  /etc/init.d/network restart
  ```
  
  <strong>Important: You must also set the wifi-device ‘mt7628’ to the same channel, otherwise it will not work.</strong>

## VPN

### Cannot Connect to PPTP Server?

The presenting problem is that you have a GL.iNet travel router and it has been upgraded to firmware v3.x. The unfortunate consequence is that you are no longer able to connect in a pass-through way to any PPTP server. 

First make sure the router has a connection to the Internet, because you will need this Internet connection to get the "opkg" command to work.

Also make sure you know the IP address of the router (default is 192.168.8.1). Also make sure you know the password for logging in at the web-based management interface. The default is "goodlife". Pretty likely you changed it to something else. You will need to know the root password.

ake sure you have an ssh terminal emulator, which might be built into your version of windows or might need to be installed to your computer. SSH to the router, the password is the same password you use at the web management interface. Note that at the web management interface you log in as "admin" while at the ssh shell you log in as "root".

Now you are at a unix-like command line. Do the command-line steps:

```  
opkg update && opkg install kmod-nf-nathelper-extra
echo "net.netfilter.nf_conntrack_helper = 1" >> /etc/sysctl.d/local.conf

cat <<EOT >> /etc/firewall.user
iptables -t raw -A OUTPUT -p tcp -m tcp --dport 1723 -j CT --helper pptp
EOT

reboot
```  

At this point hopefully the router will reboot. Eventually you will hopefully once again be able to connect to the router via wired ethernet or via wifi. Connect and test the Internet connectivity.

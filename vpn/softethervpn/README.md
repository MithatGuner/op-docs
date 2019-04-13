## Installation

SSH to the router and install **softethervpn**.  

```  
opkg update
opkg install softethervpn
```  

Please note that this package is very large, it might no enough space to install them for mini routers. You should have a router with NAND flash, such as AR750S.

## Configuration

### Create a Connection Account  

Type `vpncmd` in command line to enter interactive mode. Here is my steps.

```  
root@GL-AR750S:/# vpncmd 
vpncmd command - SoftEther VPN Command Line Management Utility
SoftEther VPN Command Line Management Utility (vpncmd command)
Version 4.25 Build 9656   (English)
Compiled 2018/01/15 09:33:22 by yagi at pc33
Copyright (c) SoftEther VPN Project. All Rights Reserved.

By using vpncmd program, the following can be achieved. 

1. Management of VPN Server or VPN Bridge 
2. Management of VPN Client
3. Use of VPN Tools (certificate creation and Network Traffic Speed Test Tool)

Select 1, 2 or 3: 2

Specify the host name or IP address of the computer that the destination VPN Client is operating on. 
If nothing is input and Enter is pressed, connection will be made to localhost (this computer).
Hostname of IP Address of Destination: 

Access has been denied. Possibly the password is incorrect, or perhaps you are connecting by an incorrect 
admin mode. You can try inputting the password again. To cancel, press Ctrl+D.
Password: *********

Connected to VPN Client "localhost".

VPN Client>AccountCreate
AccountCreate command - Create New VPN Connection Setting
Name of VPN Connection Setting: test

Destination VPN Server Host Name and Port Number: 192.168.17.163:5555

Destination Virtual Hub Name: glinet

Connecting User Name: test1

Used Virtual Network Adapter Name: vpn

The command completed successfully.

```  

### Set Account Password and Connect to Server  

We will use three instructions in here. **AccountPasswordSet**, **AccountPasswordSet** and **AccountList**, 

```  
VPN Client>AccountPasswordSet
AccountPasswordSet command - Set User Authentication Type of VPN Connection Setting to Password Authentication
Name of VPN Connection Setting: test

Please enter the password. To cancel press the Ctrl+D key.

Password: *********
Confirm input: *********


Specify standard or radius: standard

The command completed successfully.

VPN Client>AccountConnect
AccountConnect command - Start Connection to VPN Server using VPN Connection Setting
Name of VPN Connection Setting: test

The command completed successfully.

VPN Client>AccountList
AccountList command - Get List of VPN Connection Settings
Item                        |Value
----------------------------+----------------------------------------------
VPN Connection Setting Name |test
Status                      |Connected
VPN Server Hostname         |192.168.17.163:5555 (Direct TCP/IP Connection)
Virtual Hub                 |glinet
Virtual Network Adapter Name|vpn
The command completed successfully.

VPN Client>

```  

### Add an Interface to Network Configuration

```  
uci set network.vpn=interface
uci set network.vpn.ifname='vpn_vpn'
uci set network.vpn.proto='dhcp'
uci commit network
```  

We should restart the network now, Typing `/etc/init.d/network restart` in command line.

## Check VPN Status  

If everything works, the VPN interface will be set up.

```  
root@GL-AR750S:/# ifconfig vpn_vpn
vpn_vpn   Link encap:Ethernet  HWaddr 00:AC:84:B1:99:85  
          inet addr:192.168.17.117  Bcast:192.168.17.255  Mask:255.255.255.0
          inet6 addr: fe80::28f4:2aff:fe97:8aa4/64 Scope:Link
          UP BROADCAST RUNNING MULTICAST  MTU:1500  Metric:1
          RX packets:337 errors:0 dropped:0 overruns:0 frame:0
          TX packets:180 errors:0 dropped:0 overruns:0 carrier:0
          collisions:0 txqueuelen:1000 
          RX bytes:42671 (41.6 KiB)  TX bytes:59868 (58.4 KiB)
```

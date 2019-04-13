## Installation

```
opkg update
opkg install tor tor-geoip
```

## Configuration

### Configuring tor

Copying those lines below and paste in the router's command line, then press "Enter" key. That will override the torrc configuration file with it. 

```
cat <<EOT > /etc/tor/torrc
RunAsDaemon 1
AllowUnverifiedNodes middle,rendezvous
Log notice syslog
## Only run as a client, never a relay or exit
ClientOnly
PidFile /var/run/tor.pid
DataDirectory /var/lib/tor
User tor
SocksPort 9050
SocksPort 192.168.1.1:9050
AutomapHostsSuffixes .onion,.exit
AutomapHostsOnResolve 1
VirtualAddrNetworkIPv4 10.192.0.0/10
TransPort 192.168.1.1:9040
DNSPort 192.168.1.1:9053
ControlPort 9051
EOT
```

### Configuring firewall

Append those lines to */etc/config/firewall*.

```
config zone 'tor'
    option name 'tor'
    option network 'lan'
    option input 'REJECT'
    option output 'ACCEPT'
    option forward 'REJECT'
    option conntrack '1'
	
config rule
    option name 'Allow-Tor-DHCP'
    option src 'tor'
    option proto 'udp'
    option dest_port '67'
    option target 'ACCEPT'
    option family 'ipv4'

config rule
    option name 'Allow-Tor-DNS'
    option src 'tor'
    option proto 'udp'
    option dest_port '9053'
    option target 'ACCEPT'
    option family 'ipv4'

config rule
    option name 'Allow-Tor-Transparent'
    option src 'tor'
    option proto 'tcp'
    option dest_port '9040'
    option target 'ACCEPT'
    option family 'ipv4'

config rule
    option name 'Allow-Tor-SOCKS'
    option src 'tor'
    option proto 'tcp'
    option dest_port '9050'
    option target 'ACCEPT'
    option family 'ipv4'
```

Append those lines to */etc/firewall.user*.

```
enable_transparent_tor() {

	ifname=br-lan

	# Allow direct access to the Tor daemon
	iptables -t nat -A PREROUTING -i $ifname -p tcp --dport 9050 -j ACCEPT

	# provide transparent routing for TCP and DNS
	iptables -t nat -A PREROUTING -i $ifname -p udp --dport 53 -j REDIRECT --to-ports 9053
	iptables -t nat -A PREROUTING -i $ifname -p tcp --syn -j REDIRECT --to-ports 9040
}

enable_transparent_tor
```

## Start Tor

We have to edit Tor init script, */etc/init.d/tor* to successfully start tor at every boot. Add those lines before **procd_open_instance**.

```
lan_ip=$(uci get network.lan.ipaddr)
[ -n "$lan_ip" ] && sed -i "s/192.168\..*\..*:/$lan_ip:/g" /etc/tor/torrc
```

All things done. Let’s start tor.

```
/etc/init.d/tor restart
```

## Verify tor

Visti [check.torproject.org](http://check.torproject.org/) to see if you are in tor network. Please note, when you are using tor, the router’s UI is not accessible as well. But you can ssh to the router.
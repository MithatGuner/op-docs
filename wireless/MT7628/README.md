## Prepare

Make sure that you have got the wireless driver from MediaTek or your distributor. If you flash the v3.x firmware of MT300N-V2, it should be fine as well. 

Clone the git repository to your local machine.  

```  
git clone https://github.com/kysonlok/op-docs.git /tmp/op-docs
```  

Copy the source code to your OpenWRT buildroot.  

```  
cp -fr /tmp/op-docs/src/wlan_assoclist YOUR_BUILDROOT/package
```  

## Compile

Assume that you have known how to build a firmware, and you have built a firmware for MT300N-V2. We can execute this command to build our demonstration code.

```
make package/wlan_assoclist/{clean,compile} V=s
```

## Further development  

It is only contains a demonstration code to get wireless assoclist. You can integrate the function to your projet.

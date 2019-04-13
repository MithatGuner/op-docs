#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>

#include <linux/wireless.h>

#define MAC_ADDR_LEN			6
#define MAX_NUMBER_OF_MAC		50

typedef union _MACHTTRANSMIT_SETTING {
	struct  {
		unsigned short  MCS:7;  // MCS
		unsigned short  BW:1;   //channel bandwidth 20MHz or 40 MHz
		unsigned short  ShortGI:1;
		unsigned short  STBC:2; 
		unsigned short	rsv:1;
		unsigned short  MODE:2; 
	} field;
	unsigned short      word;
} MACHTTRANSMIT_SETTING;

typedef struct _RT_802_11_MAC_ENTRY {
	unsigned char			ApIdx;
	unsigned char           Addr[MAC_ADDR_LEN];
	unsigned char           Aid;
	unsigned char           Psm;
	unsigned char           MimoPs;
	char                    AvgRssi0;
	char                    AvgRssi1;
	char                    AvgRssi2;
	unsigned int            ConnectedTime;
	MACHTTRANSMIT_SETTING	TxRate;
	unsigned int		    LastRxRate;
	short			        StreamSnr[3];
	short			        SoundingRespSnr[3];
} RT_802_11_MAC_ENTRY;

typedef struct _RT_802_11_MAC_TABLE {
	unsigned long            Num;
	RT_802_11_MAC_ENTRY      Entry[MAX_NUMBER_OF_MAC];
} RT_802_11_MAC_TABLE;

int GetWirelessMacTable(RT_802_11_MAC_TABLE *table, char *interface)
{
	int s = 0;
	struct iwreq iwr;

	memset(&iwr, 0, sizeof(iwr));
	memset(table,0,sizeof(table));
	s = socket(AF_INET, SOCK_DGRAM, 0);
	strncpy(iwr.ifr_name, interface, strlen(interface));
	iwr.u.data.pointer = (caddr_t)table;
	if (s < 0) {
		return -1;
	}

	if (ioctl(s, 0x8BFF, &iwr) < 0) {
		close(s);
		return -1;
	}

	close(s);

	return 0;
}

int main(int argc, char **argv)
{
	int i = 0;
	int ret = 0;

	RT_802_11_MAC_TABLE table = {0};

	ret = GetWirelessMacTable(&table, "ra0");
	if (ret != 0) {
		printf("Fail to call GetWirelessMacTable\n");
		return -1;
	}

	for (i = 0; i < table.Num; i++) {
		RT_802_11_MAC_ENTRY *hpe = &(table.Entry[i]);

		printf("Client[%d]: %02X:%02X:%02X:%02X:%02X:%02X\n",i,hpe->Addr[0], hpe->Addr[1], hpe->Addr[2], hpe->Addr[3],hpe->Addr[4], hpe->Addr[5]);
	}

	return 0;
}

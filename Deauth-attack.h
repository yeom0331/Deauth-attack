#ifndef DEAUTHATTACK_H
#define DEAUTHATTACK_H

#endif // DEAUTHATTACK_H

#include <pcap.h>
#include <unistd.h>
#include <string.h>
#include <cstring>
#include <iostream>
#include "mac.h"
#define MAC_LEN 6
#define dea 0x00c0
#define version 0x00
#define pad 0x00
#define len 0x0008
#define pre 0x00000000
#define dur 0x0000
#define seq 0x0000
#define code 0x0007


using namespace std;
struct radiotap_header {
        u_int8_t        it_version;     /* set to 0 */
        u_int8_t        it_pad;
        u_int16_t       it_len;         /* entire length */
        u_int32_t       it_present;     /* fields present */
} __attribute__((__packed__));

struct deauth_header {
    u_int16_t type;
    u_int16_t duration;
    Mac dmac;
    Mac smac;
    Mac bssid;
    u_int16_t num;
};

struct wireless_management {
    u_int16_t reason_code;
};

#pragma pack(push, 1)
struct deauth {
    radiotap_header radio;
    deauth_header dth;
    wireless_management wm;
};
#pragma pack(pop)

void usage() {
    cout << "syntax : deauth-attack <interface> <ap mac> [<station mac>]" << endl;
    cout << "sample1 : deauth-attack 00:11:22:33:44:55" << endl;
    cout << "sample2 : deauth-attack 00:11:22:33:44:55 66:77:88:99:AA:BB" << endl;
}


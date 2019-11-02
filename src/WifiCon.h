#include <WiFi.h>
#include <WiFiUdp.h>
#include <string.h>

using namespace std;


class WifiCon
{
    public:
        boolean connected;
        WifiCon();
        string sendMessage(string message);
        void printWifiStatus(); 
        void connect(const char* ssid, const char* password);
        void sendCommand(string message, bool debug);
        string getResponse(bool debug);
        void sendRcCommand(int a,int b, int c, int d,bool debug);  
        const char* networkName;
        const char* networkPswd;


    private:
        //const char * networkName = "tello2";
        //const char * networkPswd = "";'
        void WiFiEvent(WiFiEvent_t event, system_event_info_t info);
        WiFiUDP udp;
        const char * udpAddress = "192.168.10.1";
        const int udpPort = 8889;  

};
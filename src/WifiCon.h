#include <WiFi.h>
#include <WiFiUdp.h>
#include <string.h>
#include "AsyncUDP.h"

using namespace std;


class WifiCon
{
    public:
        string telemetry[3]; // array containing flight data       
        bool debug; // set debug mode
        boolean connected; //bool for state of connection
        string connectedStatus;//string for feedback on connection status       
        WifiCon(String ssid, String password, bool debug); //constructor setuo credentials
        String myIp; //ip ig my unit              
        void connect();// for connecting to drono wifi
        void sendCommand(string message); // seding commands to drone
        void sendRcCommand(int a,int b, int c, int d); // sending RC command to drone
        void commandResponse(String response); // asynch UDP response port 8890
        void setIp(String ip);
        string getResponse(); // synch UDP response 9989
        


    private:
        String ssid; // id of wifi
        String password; //pass of wifi
        WiFiUDP udpSender; //wifi connection class
        const int udpPort = 8889;//ports of repsonse 
        const int asynchudpPort = 8890; //ports for listen
        AsyncUDP udp; // class for handling asynch udp
        String droneIp = "192.168.10.1"; 
        void WiFiEvent(WiFiEvent_t event, system_event_info_t info); // part of eventhandler for getting connection state
        string FilterData(string data, string find, int length);
        void ClearTelemetry();
        

};
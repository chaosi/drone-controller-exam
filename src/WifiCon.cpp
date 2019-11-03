#include <WifiCon.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <string.h>
#include <sstream>
#include <iostream>       // std::cout

using namespace std;


boolean connected;



WifiCon::WifiCon(String ssid, String password, bool debug)
{
         this->ssid = ssid;
          this->password = password;
          this->debug = debug;
          this->connectedStatus = "not connected";        
}

void WifiCon::connect()
{

    if (debug == false)
    {
        Serial.println("drone begin");
        WiFi.onEvent([this](WiFiEvent_t event, system_event_info_t info) { this->WiFiEvent(event, info); }); // run method WiFiEvent with input on event
        WiFi.mode(WIFI_STA);
        WiFi.begin(this->ssid.c_str(), this->password.c_str());
      
        // set eventlistener asynch
        if(udp.listen(asynchudpPort)) 
        {
            this->myIp = WiFi.localIP().toString();
            Serial.print("UDP Listening on IP: ");
            Serial.println(WiFi.localIP());
            udp.listenIP();
            udp.onPacket(
                [this](AsyncUDPPacket packet) -> void
                {
                    // make a string from the data
                    String s((char*)packet.data());
                    s = s.substring(0, packet.length()); 
                    s.trim();
                    // send string to method
                    this->commandResponse(s);
                }
              );
        }
        
    }
    else
    {
        Serial.println("debug begin");
    }

              
}


void WifiCon::WiFiEvent(WiFiEvent_t event, system_event_info_t info)
{
        switch (event)
        {
        case SYSTEM_EVENT_STA_GOT_IP:
                //When connected set
                Serial.print("WiFi connected! IP address: ");
                Serial.println(WiFi.localIP());
                //initializes the UDP state
                //This initializes the transfer buffer
                udpSender.begin(WiFi.localIP(), udpPort);
                this->connected = true;
                 this->connectedStatus ="connected";
                break;
        case SYSTEM_EVENT_STA_DISCONNECTED:
                Serial.println("WiFi lost connection");
                this->connected = false;
                this->connectedStatus ="lost conn";
                ClearTelemetry();               
                break;
        case SYSTEM_EVENT_AP_STOP:
                Serial.println("Lost connection to Drone");
                this->connected = false;
                this->connectedStatus ="lost conn Drone";
                ClearTelemetry();           
                break;
        }
}

void WifiCon::ClearTelemetry()
{
    this->telemetry[0] = "";
    this->telemetry[1] = "";
    this->telemetry[2] = "";
 
}

void WifiCon::commandResponse(String response)
{/*
    Serial.print("got following response: ");
    Serial.println(response.c_str());
    Serial.print("message length: ");
    Serial.println(response.length());
 */
  string stateResponce = response.c_str(); // state data from drone
  string battery = FilterData(stateResponce, "bat:", 6);
  string barometer = FilterData(stateResponce, "baro:", 8);
  string time = FilterData(stateResponce, "time:", 7);
   
    this->telemetry[0] = battery;
    this->telemetry[1] = barometer;
    this->telemetry[2] = time;

}

// finds chars in string and returns string equal to number of chars after found index
string WifiCon::FilterData(string data, string find, int length) 
{
    string out;
    std::size_t found = data.find(find);
    int index = found;

    for (int i = 0; i < length; i++)
    {
       out += data[index+i];
      
    }  
    return out;
}


void WifiCon::sendCommand(string message)
{
    string out = "Sending command '" + message + "'";
    Serial.println(out.c_str());

    //Send a packet
    if (debug == false)
    {
        udpSender.beginPacket(this->droneIp.c_str(), udpPort);
        udpSender.printf(message.c_str());
        udpSender.endPacket(); 
                   
    }
}

// RC commands for continues commands
void WifiCon::sendRcCommand(int a, int b, int c, int d)
{
    ostringstream s;
    s << "rc " << a << " " << b << " " << c << " " << d;
    string message = s.str();
    sendCommand(message);
}

void WifiCon::setIp(String ip)
{
    this->droneIp = ip;
}


string WifiCon::getResponse()
{
    if (debug == false)
    {
        string reply = "connection problem";
        int packetSize = udpSender.parsePacket();
        int tries = 0;
         do
        {
            delay(333);
            packetSize = udpSender.parsePacket();
            Serial.print(".");
            tries++;
        } while (packetSize == 0 && tries < 3);
        
        Serial.println();
        Serial.printf("packetsize: %d \r\n", packetSize);

        if (packetSize)
        {
            char packetBuffer[255];
            int len = udpSender.read(packetBuffer, 255);
            if (len > 0)
            {
                packetBuffer[len] = 0;
            }
            Serial.println(".");

            const string reply = string(packetBuffer);
            //udpSender.flush();
            return reply;
         }

       
        return reply;
    }
    return "ok";
}

       

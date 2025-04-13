#include <WiFi.h>              
#include <eth.h>
#include <EEPROM.h>
#include <SNMP_Agent.h>
#include <ESP32Ping.h>
#include <GyverPortal.h>
char* oidSysDescr = ".1.3.6.1.2.1.1.1.0";    // OctetString SysDescr
char* oidSysObjectID = ".1.3.6.1.2.1.1.2.0"; // OctetString SysObjectID
char* oidSysUptime = ".1.3.6.1.2.1.1.3.0";   // TimeTicks sysUptime (hundredths of seconds)
char* oidSysContact = ".1.3.6.1.2.1.1.4.0";  // OctetString SysContact
char* oidSysName = ".1.3.6.1.2.1.1.5.0";     // OctetString SysName
char* oidSysLocation = ".1.3.6.1.2.1.1.6.0"; // OctetString SysLocation
char* oidSysServices = ".1.3.6.1.2.1.1.7.0"; // Integer sysServices
WiFiUDP udp; 
uint32_t uptame, chipId, hour, SysServices;
int n1, n2, n3, snmp_tc[10], snmp_tf[10], rnd1, power_delay2, network;
bool power_status;
byte i, dhcp_on, ap_on, eth_on, emputy;
String about, lpip, name, ping_ret,dhcpl, hostname2, system2, dns2, location2, ip2, oid2, mask2, gw2, ssid2, pass2, login2, pass4, contact2, power_delay1, community2="public", fw="1.0.3";
char ssid1[16], pass1[16], login1[16], pass3[16], hostname1[16], community1[16], system1[16], location1[16], contact1[16], oid1[30];
#include "lp.h"
#include "portal.h"
#include "hard_reset.h"
SNMPAgent snmp = SNMPAgent();  
void setup(){
    Serial.begin(115200);
    EEPROM.begin(EEPROM_SIZE);  EEPROM.get(9,emputy);
    pinMode(KEY_RESET_CONFIG, INPUT);   pinMode(LED_POWER, INPUT);  pinMode(KEY_RESET, OUTPUT); pinMode(KEY_POWER, OUTPUT);
    digitalWrite(KEY_RESET, HIGH);  digitalWrite(KEY_POWER, HIGH);
    if (emputy != 1) hard_reset();
    if (digitalRead(KEY_RESET_CONFIG)==1) {delay(5000); if (digitalRead(KEY_RESET_CONFIG)==1) hard_reset();}
    EEPROM.get(4,power_delay1); EEPROM.get(1,dhcp_on); EEPROM.get(2,ap_on); EEPROM.get(3,eth_on); EEPROM.get(30,community1); EEPROM.get(90,hostname1); EEPROM.get(150,ssid1); EEPROM.get(210,pass1); EEPROM.get(270,oid1); EEPROM.get(360,contact1); EEPROM.get(390,system1); EEPROM.get(450,location1); EEPROM.get(60,login1); EEPROM.get(120,pass3);
    if (ap_on==0){WiFi.hostname(hostname1); WiFi.begin(ssid1, pass1);}else{WiFi.softAP(ssid1, pass1);}
   WiFi.begin("SciNet2G", "RedOctober");
   dhcp_on=1;
    if (dhcp_on==0){
    IPAddress local_IP(EEPROM.read(10), EEPROM.read(11), EEPROM.read(12), EEPROM.read(13));
    IPAddress subnet(EEPROM.read(15), EEPROM.read(16), EEPROM.read(17), EEPROM.read(18));
    IPAddress gateway(EEPROM.read(20), EEPROM.read(21), EEPROM.read(22), EEPROM.read(23));
    IPAddress primaryDNS(EEPROM.read(25), EEPROM.read(26), EEPROM.read(27), EEPROM.read(28));
    IPAddress secondaryDNS(8, 8, 8, 8); 
    WiFi.config(local_IP,gateway,subnet,primaryDNS,secondaryDNS);
                    }
    portal.attachBuild(build);
    portal.attach(action);
    portal.start();
    portal.log.start(30);
    portal.enableAuth(login1, pass3);
    snmp.setUDP(&udp);
    snmp.begin();
    std::string SysDescr = ESP.getChipModel() + ESP.getChipRevision(); 
    snmp.addReadOnlyStaticStringHandler(oidSysDescr, SysDescr);
    snmp.addReadOnlyStaticStringHandler(oidSysObjectID, "IPMI");
    snmp.addTimestampHandler(oidSysUptime, &uptame);
    snmp.addReadOnlyStaticStringHandler(oidSysContact, contact1);
    snmp.addReadOnlyStaticStringHandler(oidSysName, system1);
    snmp.addReadOnlyStaticStringHandler(oidSysLocation, location1);
    snmp.sortHandlers();
} 

void loop(){
    snmp.loop(); 
    portal.tick();          
  }


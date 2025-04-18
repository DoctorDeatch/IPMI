void hard_reset(){
delay (300);
EEPROM.put(1,1);
EEPROM.put(2,1);
EEPROM.put(3,0);
EEPROM.put(9,1);
EEPROM.put(10,192);
EEPROM.put(11,168);
EEPROM.put(12,4);
EEPROM.put(13,1);
EEPROM.put(15,255);
EEPROM.put(16,255);
EEPROM.put(17,255);
EEPROM.put(18,255);
EEPROM.put(20,192);
EEPROM.put(21,168);
EEPROM.put(22,4);
EEPROM.put(23,1);
EEPROM.put(25,8);
EEPROM.put(26,8);
EEPROM.put(27,4);
EEPROM.put(28,4);
EEPROM.put(4,3);
community2="public"; community2.toCharArray(community1, 16); EEPROM.put(30,community1);
hostname2="IPMI"; hostname2.toCharArray(hostname1, 16); EEPROM.put(90,hostname1);
ssid2="IPMI"; ssid2.toCharArray(ssid1, 16); EEPROM.put(150,ssid1);
pass2=""; pass2.toCharArray(pass1, 16); EEPROM.put(210,pass1);
oid2=".1.3.6.1.4.1.2020.1."; oid2.toCharArray(oid1, 30); EEPROM.put(270,oid1);
contact2="Admin"; contact2.toCharArray(contact1, 16); EEPROM.put(360,contact1);
system2="ESP-IPMI01"; system2.toCharArray(system1, 16); EEPROM.put(390,system1);
location2="LABORATOY"; location2.toCharArray(location1, 16); EEPROM.put(450,location1);
login2="admin"; login2.toCharArray(login1, 16); EEPROM.put(60,login1);
pass4="admin"; pass4.toCharArray(pass3, 16); EEPROM.put(120,pass3);
EEPROM.commit();
delay (300);
ESP.restart();
}
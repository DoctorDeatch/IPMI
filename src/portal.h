GyverPortal portal;
String valText;

void build() {
    String chipIde =  String(chipId);
    String hour =  String() + uptame/3600 + " Hour";
    String model = ESP.getChipModel() + ESP.getChipRevision();
    String LocalIP = String() + WiFi.localIP()[0] + "." + WiFi.localIP()[1] + "." + WiFi.localIP()[2] + "." + WiFi.localIP()[3];
    String Localsubnet = String() + WiFi.subnetMask()[0] + "." + WiFi.subnetMask()[1] + "." + WiFi.subnetMask()[2] + "." + WiFi.subnetMask()[3];
    String LocalGW = String() + WiFi.gatewayIP()[0] + "." + WiFi.gatewayIP()[1] + "." + WiFi.gatewayIP()[2] + "." + WiFi.gatewayIP()[3];
    String ip1 = String() + EEPROM.read(10) + "." + EEPROM.read(11) + "." + EEPROM.read(12) + "." + EEPROM.read(13);
    String mask1 = String() + EEPROM.read(15) + "." + EEPROM.read(16) + "." + EEPROM.read(17) + "." + EEPROM.read(18);
    String gw1 = String() + EEPROM.read(20) + "." + EEPROM.read(21) + "." + EEPROM.read(22) + "." + EEPROM.read(23);
    String dns1 = String() + EEPROM.read(25) + "." + EEPROM.read(26) + "." + EEPROM.read(27) + "." + EEPROM.read(28);
    String RSSI = String() + WiFi.RSSI() + "dB";
    String hostname = String(hostname1);
    String power_delay1 = String() + EEPROM.read(4);

  GP.BUILD_BEGIN(GP_DARK,650);
  GP.PAGE_TITLE("IPMI");
  GP.TITLE("IPMI");
  GP.ONLINE_CHECK(10000); 
  GP.UPDATE("power_status");

  GP.NAV_TABS("Control,Global,Network,SNMP,Info,Tools");

  GP.NAV_BLOCK_BEGIN();
  GP_MAKE_BLOCK_TAB("", GP.LABEL("");
  GP.LABEL("POWER OFF"); GP.SWITCH("power_status",power_status,GP_RED);GP.LABEL("POWER ON"););
  GP_MAKE_BLOCK_TAB("", GP.LABEL("");
  GP.BUTTON("shutdown", "Shutdown OS", "shutdown", GP_ORANGE); 
  GP.BUTTON("reset", "Reset system", "reset", GP_RED);  );
GP.NAV_BLOCK_END();

 GP.NAV_BLOCK_BEGIN();
    GP_MAKE_BLOCK_TAB("Global Settings", GP.LABEL("");
    GP_MAKE_BOX(GP.LABEL("Login:"); GP.TEXT("login2",login1,""););
    GP_MAKE_BOX(GP.LABEL("Password:"); GP.TEXT("pass4",pass3,""););
    GP_MAKE_BOX(GP.LABEL("Pressing delay when power is turned off:"); GP.NUMBER("power_delay2",power_delay1);GP.LABEL("Sec"););
    GP_MAKE_BOX(GP.LABEL("Wi-Fi"); GP.SWITCH("eth",eth_on,GP_BLACK);GP.LABEL("Ethernet"););
    //GP.BUTTON_MINI("global", "Save settings and restart IMM", "global");
    );
  GP.NAV_BLOCK_END();

  GP.NAV_BLOCK_BEGIN();
    GP_MAKE_BLOCK_TAB("Network Settings", GP.LABEL("");
    GP_MAKE_BOX(GP.LABEL("DHCP"); GP.SWITCH("dhcp",dhcp_on););
    GP_MAKE_BOX(GP.LABEL("IP address:"); GP.TEXT("ip2",ip1,""););
    GP_MAKE_BOX(GP.LABEL("Mask:"); GP.TEXT("mask2",mask1,""););
    GP_MAKE_BOX(GP.LABEL("Gateway:"); GP.TEXT("gw2",gw1,""););
    GP_MAKE_BOX(GP.LABEL("DNS:"); GP.TEXT("dns2",dns1,""););
    GP_MAKE_BOX(GP.LABEL("Hostname:"); GP.TEXT("hostname2",hostname,""););    
    GP_MAKE_BOX(GP.LABEL("AP Mode"); GP.SWITCH("ap", ap_on););
    GP_MAKE_BOX(GP.LABEL("AP name:"); GP.TEXT("ssid2",ssid1,""););
    GP_MAKE_BOX(GP.LABEL("AP pass:"); GP.TEXT("pass2",pass1,""););
    GP.BUTTON_MINI("network", "Apply settings and restart IMM");
   );
  GP.NAV_BLOCK_END();

GP.NAV_BLOCK_BEGIN();
   GP_MAKE_BLOCK_TAB("SNMP Settings", GP.LABEL("");
  //   GP_MAKE_BOX(GP.LABEL("Community RO:"); GP.TEXT("сommunity2",community1,""););
     GP_MAKE_BOX(GP.LABEL("System"); GP.TEXT("system2",system1,""););
     GP_MAKE_BOX(GP.LABEL("location"); GP.TEXT("location2",location1,""););
     GP_MAKE_BOX(GP.LABEL("Contact"); GP.TEXT("contact2",contact1,""););
    // GP.BUTTON_MINI("snmp", "Save settings","snmp");
   );
 GP.NAV_BLOCK_END();

 GP.NAV_BLOCK_BEGIN();
 GP_MAKE_BLOCK_TAB("System Info", GP.LABEL("");
 if (dhcp_on==1) dhcpl = "ON"; else dhcpl = "OFF";
 GP_MAKE_BOX(GP.LABEL("Chip model: "); GP.LABEL(model););
 GP_MAKE_BOX(GP.LABEL("Chip ID: "); GP.LABEL(chipIde););
 GP_MAKE_BOX(GP.LABEL("Firmware version: "); GP.LABEL(fw););
 GP_MAKE_BOX(GP.LABEL("Uptime: "); GP.LABEL(hour););
);
 GP_MAKE_BLOCK_TAB( "Network Info", GP.LABEL("");
 GP_MAKE_BOX(GP.LABEL("MAC:"); GP.LABEL(WiFi.macAddress()););
 GP_MAKE_BOX(GP.LABEL("Host Name:"); GP.LABEL(hostname););
 GP_MAKE_BOX(GP.LABEL("DHCP:"); GP.LABEL(dhcpl););
 GP_MAKE_BOX(GP.LABEL("IP:"); GP.LABEL(LocalIP););
 GP_MAKE_BOX(GP.LABEL("Subnet:"); GP.LABEL(Localsubnet););
 GP_MAKE_BOX(GP.LABEL("GW:"); GP.LABEL(LocalGW););
 GP_MAKE_BOX(GP.LABEL("RSSI:"); GP.LABEL(RSSI););
);
GP_MAKE_BLOCK_TAB( "About", GP.LABEL("");
GP.SPAN("Developed the \"Doc\".");
GP.SPAN("All rights are legally protected. ");
GP.SPAN("The product is distributed free of charge.");
GP.SPAN("Any commercial use is prohibited!");
GP.SPAN("On the issue of commercial acquisition, <a href=\"mailto:doc.fbi.2000@gmail.com\">please contact the developer</a>"););
GP.NAV_BLOCK_END();

GP.NAV_BLOCK_BEGIN();
GP_MAKE_BLOCK_TAB("Ping", GP.LABEL("");
GP_MAKE_BOX( GP.TEXT("ping", "Destination IP", lpip););
//GP.BUTTON_MINI("ping", "Send Ping");
GP.AREA_LOG(7);     );
GP.NAV_BLOCK_END();

GP.BUILD_END();
}


void action() {
  if (portal.update()) {
    if (portal.update("power_status")) portal.answer(bool(digitalRead(LED_POWER))); }
if (portal.click()){
  if (portal.click("reset"))  {
    digitalWrite(KEY_RESET, LOW); delay(300); digitalWrite(KEY_RESET, HIGH); }
    if (portal.click("shutdown"))  {
      digitalWrite(KEY_POWER, LOW); delay(300); digitalWrite(KEY_POWER, HIGH); }
  if (portal.clickInt("power_status",power_status))  {
    if (power_status=1) {digitalWrite(KEY_POWER, LOW); delay(300); digitalWrite(KEY_POWER, HIGH);}
    if (power_status=0) {digitalWrite(KEY_POWER, LOW); delay(EEPROM.read(4) * 1000); digitalWrite(KEY_POWER, HIGH);}
     } 
  if (portal.click("ping"))  {
   portal.log.println(HL(portal.getString("ping")));  }
  if (portal.clickInt("dhcp", dhcp_on)) {
    EEPROM.put(1,dhcp_on);    }
  if (portal.clickInt("ap",ap_on))  {
    EEPROM.put(2,ap_on);   }
  if (portal.clickInt("eth",eth_on))  {
    EEPROM.put(3,eth_on);  delay(1000); ESP.restart();  }
  if (portal.clickString("сommunity2",community2))  {
    community2.toCharArray(community1, 16); EEPROM.put(30,community1);   }
  if (portal.clickString("hostname2",hostname2))  {
    hostname2.toCharArray(hostname1, 16); EEPROM.put(90,hostname1);    }
  if (portal.clickString("ssid2",ssid2))  {
    ssid2.toCharArray(ssid1, 16); EEPROM.put(150,ssid1);  }
  if (portal.clickString("pass2",pass2))  {
    pass2.toCharArray(pass1, 16); EEPROM.put(210,pass1);  }
  if (portal.clickString("ip2",ip2))  {
    ip2 = portal.getString("ip2");  IPAddress ip;  ip.fromString(ip2);  for (int i = 0; i < 4; ++i) { EEPROM.put(10+i,ip[i]); }  }
  if (portal.clickString("mask2",mask2))  {
    IPAddress mask; mask.fromString(mask2); for (int i = 0; i < 4; ++i) { EEPROM.put(15+i,mask[i]); }  }
  if (portal.clickString("gw2",gw2))  {
    IPAddress gw; gw.fromString(gw2); for (int i = 0; i < 4; ++i) { EEPROM.put(20+i,gw[i]); }    }
  if (portal.clickString("dns2",gw2))  {
    IPAddress dns; dns.fromString(dns2); for (int i = 0; i < 4; ++i) { EEPROM.put(25+i,dns[i]); }    }
  if (portal.clickString("contact2",contact2))  {
    contact2.toCharArray(contact1, 16); EEPROM.put(360,contact1);   }
  if (portal.clickString("system2",system2))  {
    system2.toCharArray(system1, 16); EEPROM.put(390,system1);    }
  if (portal.clickString("location2",location2))  {
    location2.toCharArray(location1, 16); EEPROM.put(450,location1);    }
  if (portal.clickString("login2",login2))  {
    login2.toCharArray(login1, 16); EEPROM.put(60,login1);    }
  if (portal.clickString("pass4",pass4))  {
    pass4.toCharArray(pass3, 16); EEPROM.put(120,pass3);    }
  if (portal.clickInt("power_delay2",power_delay2))  {
    Serial.print("power_delay: ");      Serial.println(power_delay2);
    EEPROM.put(4,power_delay2);    }
  if (portal.click("network")){delay(300); ESP.restart();}
   //EEPROM.get(360,contact1); EEPROM.get(390,system1); EEPROM.get(450,location1); EEPROM.get(60,login1); EEPROM.get(120,pass3); EEPROM.get(4,power_delay1);
   EEPROM.commit();
}
}
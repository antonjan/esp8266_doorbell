# esp8266_doorbell
This Project will have all my code and hardware details for an Online Doorbel system.<br>
![Door Bell Diagram](Intelegint_door_bell_1.jpg?raw=true "Block diagram")<br>

# Project Status
Just started not compleet yet.

# Description
I wanted to have a doorbel button that will trigger a MQTT message and send it to several mobile phoes to let them now there is somone at My gate.
I would then look at my remote Camera on my mobile phone and they decide what to do.

# Sofware
1) MQTT server
2) NodeRed server
3) Possibly Telegram or IFTTT as message alert on mobile phone.
4) ESP2866 program to send Button state to NodeRED.

#Dependency 
1) "PubSubClient by Nick O'Leary"

# Hardware
1) Doorbell Button.
2) ESP2866 controler Board connected to button.
3) Powersupply for ESP2866.
4) Small waterproof enclosure to fit Powersupply and ESP288 close to button at gate.

# mqtt testing
1) Subscribe to button on mqtt<br>
mosquitto_sub -t "bassonia/outdoors/doorbell" -u "mqtt" -P "password"
2) Send test message
mosquitto_pub -t "bassonia/outdoors/doorbell" -m "message from mosquitto_pub client" -u "mqtt" -P "password"
3) If you power up the ESP2866 and you got connection success you should see the following message on the client in nr 1. (Doorbell connected to MQTT) 
4) If you short (GND) and (GPIO 0) on the ESP8266 you should see the "on" message. 



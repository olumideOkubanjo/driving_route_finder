/**
 * HEADER 
**/

#include "serial_handling.h"

extern shared_vars shared;

bool fillBuffer(String& l, unsigned long long timeout = 1000){
  char buffer[50];
  uint8_t bufferLen = 0;
  
  // buffer[bufferLen] = 0;

  char in_char;
  auto start = millis();
  while(timeout >= (millis()-start)){
    if(Serial.available()){
      in_char = Serial.read();
      buffer[bufferLen]=in_char;
      bufferLen++;
    }

    if(in_char == '\n' || in_char=='\r'){
      l = String(buffer);
      return true;
    }
  }

  return false;
}

lon_lat_32 parseWayPoint(String latLonString){
  int32_t iLat = (latLonString.substring(0, latLonString.indexOf(" "))).toInt();
  int32_t iLon = (latLonString.substring(latLonString.indexOf(" ")+1)).toInt();
  lon_lat_32 point;
  point.lat = iLat;
  point.lon = iLon;
  return point;
};

uint8_t get_waypoints(const lon_lat_32& start, const lon_lat_32& end) {
  // Currently this does not communicate over the serial port.
  // It just stores a path length of 0. You should make it communicate with
  // the server over Serial using the protocol in the assignment description.

  // TODO: implement the communication protocol from the assignment
  String line;

  //Request
  Serial.print("R ");
  Serial.print(start.lat);
  Serial.print(" ");
  Serial.print(start.lon);
  Serial.print(" ");
  Serial.print(end.lat);
  Serial.print(" ");
  Serial.println(end.lon);

  //Get number of waypoints
  if(fillBuffer(line, 10000)){
    if(line[0]=='N'){
      String num = line.substring(2);
      shared.num_waypoints = num.toInt();
      Serial.println("A");
    }else{
      return 0;
    }
  }else{
    return 0;
  }

  //Processs waypoint
  for(int16_t i = 0; i < shared.num_waypoints; i++){
    if(fillBuffer(line)){
      if(line[0]=='W'){
        String latLonString = line.substring(2);
        shared.waypoints[i] = parseWayPoint(latLonString);
        Serial.println("A");
      }else{
        return 0;
      }
    }else{
      return 0;
    }
  }


  return 1;
}

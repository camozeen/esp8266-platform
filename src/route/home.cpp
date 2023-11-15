#include "route/home.h"
#include "server.h"

void route_home() {
    // Serial.println("handled request");
    server.send(200, "text/plain", "hello from home!");
    // digitalWrite(led, 0);
}

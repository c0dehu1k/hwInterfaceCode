#include <SPI.h>
#include <Ethernet.h>

// MAC address from Ethernet shield sticker under board
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(10, 0, 0, 87); // IP address, may need to change depending on network
EthernetServer server(80);  // create a server at port 80

String HTTP_req;          // stores the HTTP request
{
    Ethernet.begin(mac, ip);  // initialize Ethernet device
    server.begin();           // start to listen for clients
    Serial.begin(9600);       // for diagnostics
    pinMode(2, OUTPUT);       // LED on pin 2
    pinMode(3, OUTPUT);       // LED on pin 2
    pinMode(4, OUTPUT);       // LED on pin 2
    pinMode(5, OUTPUT);       // LED on pin 2
    pinMode(6, OUTPUT);       // LED on pin 2
}

void loop()
{
    EthernetClient client = server.available();  // try to get client

    if (client) {  // got client?
        boolean currentLineIsBlank = true;
        while (client.connected()) {
            if (client.available()) {   // client data available to read
                char c = client.read(); // read 1 byte (character) from client
                HTTP_req += c;  // save the HTTP request 1 char at a time
                // last line of client request is blank and ends with \n
                // respond to client only after last line received
                if (c == '\n' && currentLineIsBlank) {
                    // send a standard http response header
                    client.println("HTTP/1.1 200 OK");
                    client.println("Content-Type: text/html");
                    client.println("Connection: close");
                    client.println();
                    // send web page
                    client.println("<!DOCTYPE html>");
                    client.println("<html>");
                    client.println("<head>");
                    client.println("<title>Arduino LED Control</title>");
                    client.println("</head>");
                    client.println("<body>");
                    client.println("<h1>LED</h1>");
                    client.println("<p>Click to switch LED on and off.</p>");
                    client.println("<form method=\"get\">");
                    ProcessCheckbox(client);
                    client.println("</form>");
                    client.println("</body>");
                    client.println("</html>");
                    Serial.print(HTTP_req);
                    HTTP_req = "";    // finished with request, empty string
                    break;
                }
                // every line of text received from the client ends with \r\n
                if (c == '\n') {
                    // last character on line of received text
                    // starting new line with next character read
                    currentLineIsBlank = true;
                } 
                else if (c != '\r') {
                    // a text character was received from client
                    currentLineIsBlank = false;
                }
            } // end if (client.available())
        } // end while (client.connected())
        delay(1);      // give the web browser time to receive the data
        client.stop(); // close the connection
    } // end if (client)
}

// switch LED and send back HTML for LED checkbox
void ProcessCheckbox(EthernetClient cl)
{
    if (HTTP_req.indexOf("LED2=ON") > -1) {  // see if checkbox was clicked
        digitalWrite(2, HIGH);
    }
    if (HTTP_req.indexOf("LED2=OFF") > -1) {  // see if checkbox was clicked
        digitalWrite(2, LOW);
    }
    if (HTTP_req.indexOf("LED3=ON") > -1) {  // see if checkbox was clicked
        digitalWrite(3, HIGH);
    }
    if (HTTP_req.indexOf("LED3=OFF") > -1) {  // see if checkbox was clicked
        digitalWrite(3, LOW);
    }
    if (HTTP_req.indexOf("LED4=ON") > -1) {  // see if checkbox was clicked
        digitalWrite(4, HIGH);
    }
    if (HTTP_req.indexOf("LED4=OFF") > -1) {  // see if checkbox was clicked
        digitalWrite(4, LOW);
    }
    if (HTTP_req.indexOf("LED5=ON") > -1) {  // see if checkbox was clicked
        digitalWrite(5, HIGH);
    }
    if (HTTP_req.indexOf("LED5=OFF") > -1) {  // see if checkbox was clicked
        digitalWrite(5, LOW);
    }
    if (HTTP_req.indexOf("LED6=ON") > -1) {  // see if checkbox was clicked
        digitalWrite(6, HIGH);
    }
    if (HTTP_req.indexOf("LED6=OFF") > -1) {  // see if checkbox was clicked
        digitalWrite(6, LOW);
    } 
    delay(100);
}

void ReturnJsonValues() {
    String response = "{";
    
    response+= "\"DuracionMensaje\": {";
    response+= "\"h\": \""+ String(hMens) +"\"";
    response+= ",\"m\": \""+ String(mMens) +"\"";
    response+= ",\"s\": \""+ String(sMens) +"\"";
    response+="}";
    //Mensaje
    response+= ",\"Mensaje\": \""+ message +"\"";
    //Velocidad
    response+= ",\"Velocidad\": \""+ String(wait) +"\"";
    //Intensidad
    response+= ",\"Intensidad\": \""+ String(Intensidad) +"\"";
    //Tiempo de Espera
    response+= ",\"TiempoEspera\": {";
    response+= "\"h\": \""+ String(hTEspera) +"\"";
    response+= ",\"m\": \""+ String(mTEspera) +"\"";
    response+= ",\"s\": \""+ String(sTEspera) +"\"";
    response+="}";
    //Mostrar Hora
    response+= ",\"MostrarHora\": \""+ String(MostrarHoraEspera) +"\"";
    //Hora en Scroll
    response+= ",\"HoraScroll\": \""+ String(HoraScroll) +"\"";
    //ScrollTexto
    response+= ",\"ScrollTexto\": \""+ String(ScrollTexto) +"\"";
    
    response+="}";
 
    server.send(200, "text/json", response);
}

void handleRoot() {
    ModoIP = false;
    //server.send(200, "text/html", htmlPage);
    ReturnJsonValues();
}


void handleGenericArgs() { //Handler

    String message = "Number of args received:";
    message += server.args();            //Get number of parameters
    message += "\n";                            //Add a new line

    for (int i = 0; i < server.args(); i++) 
    {
        message += "Arg nº" + (String)i + " –> ";   //Include the current iteration value
        message += server.argName(i) + ": ";     //Get the name of the parameter
        message += server.arg(i) + "\n";              //Get the value of the parameter
    } 
    server.send(200, "text/plain", message);       //Response to the HTTP request
}

void MostrarTexto(String cadena)
{
    for(int i = 0; i < width * cadena.length() + matrix.width() - 1 - spacer; i++){
      matrix.fillScreen(LOW);
      int letter = i / width;
      int x = (matrix.width() - 1) - i % width;
      int y = (matrix.height() - 8) / 2; // Centrar el texto
      while(x + width - spacer >= 0 && letter >= 0){
         if(letter < cadena.length()){
             matrix.drawChar(x, y, cadena[letter], HIGH, LOW, 1);
         }
         letter--;
         x -= width;
      }
      matrix.write(); // Muestra loscaracteres
      delay(wait);
   }
}

void MostrarHora()
{
    timeClient.update();
    String Horas = timeClient.getHours() < 10 ? "0" + (String)timeClient.getHours() : (String)timeClient.getHours();
    String Minutos = timeClient.getMinutes() < 10 ? "0" + (String)timeClient.getMinutes() : (String)timeClient.getMinutes();
    String cadena = (Horas + ":" + Minutos); 
    if(cadena != horaActual){
        horaActual = cadena;
        // loop for each character in 'tape'
        matrix.fillScreen(LOW);
        int y = 0;  // top of character at top of display
        // loop for each character in 'tape'
        for(int i = 0; i < cadena.length(); i++ )
        {
            int x = i * width;  // step horizontal by width of character and spacer
            matrix.drawChar(x, y, cadena[i], HIGH, LOW, 1);   // draw a character from 'tape'
        }
        matrix.write(); // Send bitmap to display
        Serial.println(cadena);
    }
}

void MostrarTextoEstatico(String cadena)
{
    // loop for each character in 'tape'
    matrix.fillScreen(LOW);
    int y = 0;  // top of character at top of display
    // loop for each character in 'tape'
    for(int i = 0; i < cadena.length(); i++ )
    {
        int x = i * width;  // step horizontal by width of character and spacer
        matrix.drawChar(x, y, cadena[i], HIGH, LOW, 1);   // draw a character from 'tape'
    }
    matrix.write(); // Send bitmap to display
    Serial.println(cadena);
}

String getFullFormattedTime() {
   time_t rawtime = timeClient.getEpochTime();
   struct tm * ti;
   ti = localtime (&rawtime);

   uint16_t year = ti->tm_year + 1900;
   String yearStr = String(year);

   uint8_t month = ti->tm_mon + 1;
   String monthStr = month < 10 ? "0" + String(month) : String(month);

   uint8_t day = ti->tm_mday;
   String dayStr = day < 10 ? "0" + String(day) : String(day);

   uint8_t hours = ti->tm_hour;
   String hoursStr = hours < 10 ? "0" + String(hours) : String(hours);

   uint8_t minutes = ti->tm_min;
   String minuteStr = minutes < 10 ? "0" + String(minutes) : String(minutes);

   uint8_t seconds = ti->tm_sec;
   String secondStr = seconds < 10 ? "0" + String(seconds) : String(seconds);

   return dayStr + "-" + monthStr + "-" + yearStr + " " +
          hoursStr + ":" + minuteStr;
}

void MostrarHoraScroll()
{
    timeClient.update();
    //String cadena = ((String)daysOfTheWeek[timeClient.getDay()] + ", " + (String)timeClient.getHours() + ":" + (String)timeClient.getMinutes()+ ":" + (String)timeClient.getSeconds()); 
    MostrarTexto((String)daysOfTheWeek[timeClient.getDay()] + ", " + getFullFormattedTime());
}

void CapturarTexto() { 
    message = "";
    if (server.arg("Texto")== "") //Parameter not found
    {     
        message = "";
    }
    else //Parameter found
    {     
        message = "";
        message += server.arg("Texto");     //Gets the value of the query parameter
    }
    t = millis();
    tesp = millis();
    YaEsperado = false;
    ModoTiempo = false;
    cadenaEstaticaMostrada = false;
    handleRoot();
}

void ChangeIntensity()
{
    String intensity = "";
    intensity += server.arg("Intensidad");     //Gets the value of the query parameter
    Intensidad = intensity.toInt();
    matrix.setIntensity(Intensidad);
    handleRoot();
}

void ChangeSpeed()
{
    String speed = "";
    speed = "";
    speed += server.arg("Velocidad");     //Gets the value of the query parameter
    wait = speed.toInt();
    handleRoot();
}

void ChangeTime()
{
    String horas = server.arg("h");
    String min = server.arg("m");
    String seg = server.arg("s");
    
    hMens = horas.toInt();
    mMens = min.toInt();
    sMens = seg.toInt();
    
    int h = hMens * 3600000;
    int m = mMens * 60000;
    int s = sMens * 1000;
    
    TiempoTotalEncendido = h+m+s;
    handleRoot();
}

void ChangeWaitTime()
{
    String horas = server.arg("h");
    String min = server.arg("m");
    String seg = server.arg("s");
    
    hTEspera = horas.toInt();
    mTEspera = min.toInt();
    sTEspera = seg.toInt();
    
    int h = hTEspera * 3600000;
    int m = mTEspera * 60000;
    int s = sTEspera * 1000;
    
    TiempoTotalEspera = h+m+s;
    handleRoot();
}

void CambiarMostrarHora()
{
    ModoTiempoBoton = !ModoTiempoBoton;
    MostrarHoraEspera = ModoTiempoBoton;
    horaActual = "";
    if(!ModoTiempoBoton && message == ""){
        matrix.fillScreen(LOW);
        matrix.write();
    }
    handleRoot();
}

void CambiarTipoHora()
{
    HoraCompleta = !HoraCompleta;
    HoraScroll = !HoraCompleta;
    horaActual = "";
    handleRoot();
}

void CambioScrollTexto()
{
    ScrollText = !ScrollText;
    ScrollTexto = ScrollText;
    horaActual = "";
    cadenaEstaticaMostrada = false;
    handleRoot();
}

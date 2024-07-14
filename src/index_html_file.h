#ifndef INDEX_HTML_FILE_H
#define INDEX_HTML_FILE_H
#include <Arduino.h>

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
  <head>

    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>HomeHeat</title>
    <style>
      body {
        font-family: Arial;
        background-color: linen;
        
      }
      .container{
        display: flex;
        flex-direction: column;
        align-items: center;
      }

      p { font-size: 1.3rem; }
      .units { font-size: 2rem;}
      .rosu{
        color: rgb(231, 12, 12);
      }
      .albastru{
        color: rgb(27, 12, 231);
      }
  
      </style>
  </head>
  <body>
    <div class="container">
 
        <h2 class="rosu">
          <span>Centrala</span>
          <span id="status">%STATUS%</span>
        </h2>  

        <h2 class="albastru">
          <span>Evacuare</span>
          <span id="temperaturee">%TEMPERATUREE%</span>
          <sup >&deg;</sup><span>C</span>
        </h2>

        <h2 class="albastru">
          <span>Apa</span>
          <span id="temperaturec">%TEMPERATUREC%</span>
          <sup >&deg;</sup><span>C</span>
        </h2>

        <h2 class="albastru">
        <span>Dormitor</span>
        <span id="dormitor">%DORMITOR%</span>
        <sup >&deg;</sup><span>C</span>
      </h2>

      <h2 class="albastru">
        <span>Dressing</span>
        <span id="dressing">%DRESSING%</span>
        <sup >&deg;</sup><span>C</span>
      </h2>

      <h2 class="albastru">
        <span>Terasa</span>
        <span id="terasa">%TERASA%</span>
        <sup >&deg;</sup><span>C</span>
      </h2>

      <h2 class="albastru">
        <span>Living</span>
        <span id="living">%LIVING%</span>
        <sup >&deg;</sup><span>C</span>
      </h2>

        <table align="center">
          <tr><td align="right">
                <p>
                  <form action="/get">
                    <label for="centrala">Centrala</label>
                    <select name="input10">
                      <option value=""></option>
                      <option value="start">START</option>
                      <option value="stop">STOP</option>
                      <option value="RESTART">RESTART</option>
                      <option value="aprind">APRIND</option>
                      <option value="resetcontor">RESETCONTOR</option>
                      <option value="of">OF</option>
                    </select>
                    <input type="submit" value="SET">
                  </form> 
                </p>
                <p>
                  <form action="/get">
                    <label for="ventilator">Ventilator</label>
                    <span id="venti">%VENTIL%</span>
                   
                    <input id="onvent" name="input14" type="submit" value="START">
                    <input id="offvent" name="input14" type="submit" value="STOP">
                  </form>
                </p>
                <p>
                  <form action="/get">
                    <label for="sneck">Sneck</label>
                    <span id="snecki">%SNECK%</span>
                    
                    <input id="onsneck" name="input15" type="submit" value="START">
                    <input id="offsneck" name="input15" type="submit" value="STOP">
                  </form>
                </p>
                <p>
                  <form action="/get">
                    <label for="rezistenta">Rezistenta</label>
                    <span id="rezisti">%REZISTENTA%</span>
                    
                    <input id="onrezist" name="input16" type="submit" value="START">
                    <input id="offrezist" name="input16" type="submit" value="STOP">
                  </form>
                </p>
                <p>
                  <form action="/get">
                    <label for="pompa">Pompa</label>
                    <span id="pompi">%POMPA%</span>
                   
                    <input id="onpomp" name="input17" type="submit" value="START">
                    <input id="offpomp" name="input17" type="submit" value="STOP">
                  </form>
                </p>
                <p>
                  <form action="/get">
                    <label for="snecktimp">Sneck timp ardere</label>
                    <span>%SNETIMARD%</span>
                    <input type="text" name="input12" size="5">
                    <input type="submit" value="SET">
                  </form>
                </p>
                <p>
                  <form action="/get">
                    <label for="centrala">Status centrala</label>
                    <span>%VALKONTOR%</span>
                    <select name="input13">
                      <option value=""></option>
                      <option value="0">Off</option>
                      <option value="1">Aprindere</option>
                      <option value="2">Stabil</option>
                      <option value="3">Ardere</option>
                      <option value="4">Stop Ardere</option>
                      <option value="5">Eroare</option>
                      <option value="6">Aprindere fara peleti</option>
                    </select>
                    <input type="submit" value="SET">
                  </form> 
                </p>
              </td>
          </tr>
        </table>
    </div>
    
    <script>

      setInterval(function ( ) {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
          if (this.readyState == 4 && this.status == 200) {
            document.getElementById("temperaturee").innerHTML = this.responseText;
          }
        };
        xhttp.open("GET", "/temperaturee", true);
        xhttp.send();
      }, 3000) ;

      setInterval(function ( ) {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
          if (this.readyState == 4 && this.status == 200) {
            document.getElementById("temperaturec").innerHTML = this.responseText;
          }
        };
        xhttp.open("GET", "/temperaturec", true);
        xhttp.send();
      }, 3000) ;

      setInterval(function ( ) {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
          if (this.readyState == 4 && this.status == 200) {
            document.getElementById("status").innerHTML = this.responseText;
          }
        };
        xhttp.open("GET", "/status", true);
        xhttp.send();
      }, 2000) ;

      setInterval(function ( ) {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
          if (this.readyState == 4 && this.status == 200) {
            document.getElementById("sneperard").innerHTML = this.responseText;
          }
        };
        xhttp.open("GET", "/sneperard", true);
        xhttp.send();
      }, 3000) ;

      setInterval(function ( ) {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
          if (this.readyState == 4 && this.status == 200) {
            document.getElementById("snetimard").innerHTML = this.responseText;
          }
        };
        xhttp.open("GET", "/snetimard", true);
        xhttp.send();
      }, 3000) ;

      setInterval(function ( ) {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
          if (this.readyState == 4 && this.status == 200) {
            document.getElementById("vKontor").innerHTML = this.responseText;
          }
        };
        xhttp.open("GET", "/vKontor", true);
        xhttp.send();
      }, 3000) ;

      setInterval(function ( ) {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
          if (this.readyState == 4 && this.status == 200) {
            document.getElementById("venti").innerHTML = this.responseText;
          }
        };
        xhttp.open("GET", "/vent1", true);
        xhttp.send();
      }, 1000) ;

      setInterval(function ( ) {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
          if (this.readyState == 4 && this.status == 200) {
            document.getElementById("snecki").innerHTML = this.responseText;
          }
        };
        xhttp.open("GET", "/sneck1", true);
        xhttp.send();
      }, 1000) ;

      setInterval(function ( ) {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
          if (this.readyState == 4 && this.status == 200) {
            document.getElementById("rezisti").innerHTML = this.responseText;
          }
        };
        xhttp.open("GET", "/rezist1", true);
        xhttp.send();
      }, 1000) ;

      setInterval(function ( ) {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
          if (this.readyState == 4 && this.status == 200) {
            document.getElementById("pompi").innerHTML = this.responseText;
          }
        };
        xhttp.open("GET", "/pompa1", true);
        xhttp.send();
      }, 1000) ;

      setInterval(function ( ) {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
          if (this.readyState == 4 && this.status == 200) {
            document.getElementById("dormitor").innerHTML = this.responseText;
          }
        };
        xhttp.open("GET", "/dormitor", true);
        xhttp.send();
      }, 10000) ;

      setInterval(function ( ) {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
          if (this.readyState == 4 && this.status == 200) {
            document.getElementById("dressing").innerHTML = this.responseText;
          }
        };
        xhttp.open("GET", "/dressing", true);
        xhttp.send();
      }, 10000) ;

      setInterval(function ( ) {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
          if (this.readyState == 4 && this.status == 200) {
            document.getElementById("terasa").innerHTML = this.responseText;
          }
        };
        xhttp.open("GET", "/terasa", true);
        xhttp.send();
      }, 10000) ;

      setInterval(function ( ) {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
          if (this.readyState == 4 && this.status == 200) {
            document.getElementById("living").innerHTML = this.responseText;
          }
        };
        xhttp.open("GET", "/living", true);
        xhttp.send();
      }, 10000) ;

      
       if (document.getElementById("venti").innerHTML == "ON") {
          document.getElementById("onvent").disabled = true;
          document.getElementById("offvent").disabled = false;
        }
        if (document.getElementById("venti").innerHTML == "OFF") {
          document.getElementById("onvent").disabled = false;
          document.getElementById("offvent").disabled = true;
        }

        if (document.getElementById("snecki").innerHTML == "ON") {
          document.getElementById("onsneck").disabled = true;
          document.getElementById("offsneck").disabled = false;
        }
        if (document.getElementById("snecki").innerHTML == "OFF") {
          document.getElementById("onsneck").disabled = false;
          document.getElementById("offsneck").disabled = true;
        }

        if (document.getElementById("rezisti").innerHTML == "ON") {
          document.getElementById("onrezist").disabled = true;
          document.getElementById("offrezist").disabled = false;
        }
        if (document.getElementById("rezisti").innerHTML == "OFF") {
          document.getElementById("onrezist").disabled = false;
          document.getElementById("offrezist").disabled = true;
        }

        if (document.getElementById("pompi").innerHTML == "ON") {
          document.getElementById("onpomp").disabled = true;
          document.getElementById("offpomp").disabled = false;
        }
        if (document.getElementById("pompi").innerHTML == "OFF") {
          document.getElementById("onpomp").disabled = false;
          document.getElementById("offpomp").disabled = true;
        }
            
      setInterval(function ( ) {
        if (document.getElementById("venti").innerHTML == "ON") {
          document.getElementById("onvent").disabled = true;
          document.getElementById("offvent").disabled = false;
        }
        if (document.getElementById("venti").innerHTML == "OFF") {
          document.getElementById("onvent").disabled = false;
          document.getElementById("offvent").disabled = true;
        }

        if (document.getElementById("snecki").innerHTML == "ON") {
          document.getElementById("onsneck").disabled = true;
          document.getElementById("offsneck").disabled = false;
        }
        if (document.getElementById("snecki").innerHTML == "OFF") {
          document.getElementById("onsneck").disabled = false;
          document.getElementById("offsneck").disabled = true;
        }

        if (document.getElementById("rezisti").innerHTML == "ON") {
          document.getElementById("onrezist").disabled = true;
          document.getElementById("offrezist").disabled = false;
        }
        if (document.getElementById("rezisti").innerHTML == "OFF") {
          document.getElementById("onrezist").disabled = false;
          document.getElementById("offrezist").disabled = true;
        }

        if (document.getElementById("pompi").innerHTML == "ON") {
          document.getElementById("onpomp").disabled = true;
          document.getElementById("offpomp").disabled = false;
        }
        if (document.getElementById("pompi").innerHTML == "OFF") {
          document.getElementById("onpomp").disabled = false;
          document.getElementById("offpomp").disabled = true;
        }
      }, 500) ;

      </script>
  </body>
</html>)rawliteral";

#endif
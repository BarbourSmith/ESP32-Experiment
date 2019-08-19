const char HTML[] PROGMEM = R"(
<head></head>
<body style = 'background-color: #0074D9; font-size: xx-large;'>
    <script language='JavaScript'>
    function formToJson(form){
        var pass=form.pass.value;
        var ssid=form.ssid.value;
        var jsonFormInfo=JSON.stringify({pass:pass, ssid: ssid});
        window.alert(jsonFormInfo);
    }
    document.errorPoints = [];
    setInterval(function ( ) {
      var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
          document.getElementById('position').innerHTML = this.responseText;
        }
      };
      xhttp.open('GET', '/position', true);
      xhttp.send();
    }, 500 ) ;
    setInterval(function ( ) {
      var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
          document.getElementById('target').innerHTML = this.responseText;
        }
      };
      xhttp.open('GET', '/target', true);
      xhttp.send();
    }, 500 ) ;
    setInterval(function ( ) {
      var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
            document.getElementById('errorDist').innerHTML = this.responseText;
            
            document.errorPoints.push(parseFloat(this.responseText));
            const canvas = document.getElementById("myCanvas");
            var ctx = canvas.getContext("2d");
            
            ctx.clearRect(0, 0, 500, 500);
            
            ctx.beginPath();
            ctx.moveTo(0, 50);
            var i = 0;
            while (i < document.errorPoints.length){
                ctx.lineTo(10*i, 50+10*document.errorPoints[i]);
                i++;
            }
            ctx.stroke();
            
            if (document.errorPoints.length > 20){
                document.errorPoints.shift();
            }
        }
      };
      xhttp.open('GET', '/errorDist', true);
      xhttp.send();
    }, 500 ) ;
    </script>
    <div style = 'margin: 0; position: absolute; top: 50%; left: 50%; -ms-transform: translate(-50%, -50%); transform: translate(-50%, -50%);'>
        <form method='post' action='/settarget' > 
            <label class='label'>Target Position:  </label>
            <input type='text' name='setpoint'/> 
            <input type='submit' value='Set'>
        </form>
        <p>
            <i class='fas fa-tint' style='color:'00add6;'></i> 
            <span class='dht-labels'>Target:  </span>
            <span id='target'> </span>
        </p>
        <p>
            <i class='fas fa-tint' style='color:'00add6;'></i> 
            <span class='dht-labels'>Position:  </span>
            <span id='position'> </span>
        </p>
        <p>
            <i class='fas fa-tint' style='color:'00add6;'></i> 
            <span class='dht-labels'>Error Dist:  </span>
            <span id='errorDist'> </span>
        </p>
    </div>
    <canvas id="myCanvas" width="200" height="100" style="border:1px solid #000000;">
    </canvas>
</body>
)";

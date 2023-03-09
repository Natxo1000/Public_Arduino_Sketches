const char htmlPage[] PROGMEM = R"=====(


<html>
<head>
    <meta http-equiv="content-type" content="text/html;charset=UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.4.1/css/bootstrap.min.css">
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js"></script>
    <script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.4.1/js/bootstrap.min.js"></script>
    <title>Letrero Web</title>
</head>

<body>
    <div class="container">
        <div class="row">
            <div class="col-lg-12">
                <h1>Letrero Web</h1>
            </div>
        </div>
        <div class="row">
            <div class="col-lg-12">
                <button id="activarModoHora" type="button" style="font-size: large;" class="btn btn-primary input-lg botonCambioHora">Mostrar/Ocultar Hora</button>
                <button id="activarModoHoraScroll" type="button" style="font-size: large;" class="btn btn-success input-lg botonCambioHoraScroll">Hora Scroll/No Scroll</button>
                <br/>
            </div>
        </div><br/>
        <div class="row">
            <div class="col-lg-12">
                <button id="cambioTexto" type="button" style="font-size: large; display: none;" class="btn btn-warning input-lg botonCambio">Escribir Texto</button>
                <button id="cambioTiempo" type="button" style="font-size: large;" class="btn btn-info input-lg botonCambio">Configurar Tiempo</button>
                <button id="cambioVelocidad" type="button" style="font-size: large;" class="btn btn-danger input-lg botonCambio">Configurar Velocidad</button>
                <button id="cambioIntensidad" type="button" style="font-size: large;" class="btn btn-warning input-lg botonCambio">Configurar Intensidad</button>
                <button id="cambioTiempoEspera" type="button" style="font-size: large;" class="btn btn-primary input-lg botonCambio">Configurar Tiempo de espera</button>
            </div>
        </div><br/>
        <div class="row timeConfig panelAccion" style="display: none;">
            <div class="col-lg-12">
                <p style="font-size: large;">Elegir la duración del mensaje.</p>
            </div>
        </div>
        <div class="row timeConfig panelAccion" style="display: none;">
            <div class="col-lg-1" style="padding-top: 10;">
                <label for="horas" style="font-size: large;">Horas </label>
            </div>
            <div class="col-lg-1">
                <input type="number" id="horas" value="0" max="99" min="0" class="form-control  input-lg">
            </div>
            <div class="col-lg-1" style="padding-top: 10;">
                <label for="minutos" style="font-size: large;">Minutos </label>
            </div>
            <div class="col-lg-1">
                <input type="number" id="minutos" value="0" max="59" min="0" class="form-control input-lg">
            </div>
            <div class="col-lg-1" style="padding-top: 10;">
                <label for="segundos" style="font-size: large;">Segundos </label>
            </div>
            <div class="col-lg-1">
                <input type="number" id="segundos" value="10" max="59" min="0" class="form-control input-lg">
            </div>
            <div class="col-lg-4">
                <button id="btnEnviarTiempo" type="button" class="btn btn-success input-lg"><span style="font-size: large;" >Enviar</span></button>
            </div>
        </div>
        <div class="row writeText panelAccion">
            <div class="col-lg-12">    
                <p style="font-size: large;">Escribir el mensaje.</p>
            </div>
        </div>
        <div class="row writeText panelAccion">
            <div class="col-lg-10">
                <input id="texto" type="text" style="width: 100% !important;" class="form-control input-lg" placeholder="Escribir texto">
            </div>
            <div class="col-lg-2">
                <button id="btnEnviar" type="button" class="btn btn-success input-lg"><span style="font-size: large;" >Enviar</span></button>
            </div>
        </div><br/>
        <div class="row writeText panelAccion">
            <div class="col-lg-3" style="padding-top: 10;">
                <span style="font-size: large; font-weight: bold;">Texto en Movimiento </span>
            </div>
            <div class="col-lg-1">
                <button id="ScrollButton" type="button" style="font-size: large;" class="btn btn-warning input-lg">On/Off</button>
            </div>
        </div>
        <div class="row VelocityConfig panelAccion" style="display: none;">
            <div class="col-lg-12">
                <p style="font-size: large;">Elegir la velocidad.</p>
            </div>
        </div>
        <div class="row VelocityConfig panelAccion" style="display: none;">
            <div class="col-lg-1" style="padding-top: 10;">
                <label for="velocidad" style="font-size: large;">Rápido </label>
            </div>
            <div class="col-lg-4" style="padding-top: 14;">
                <input type="range" id="velocidad" min="15" max="200" value="30"/>
            </div>
            <div class="col-lg-1" style="padding-top: 10;">
                <label for="velocidad" style="font-size: large;"> Lento </label>
            </div>
            <div class="col-lg-4">
                <button id="btnEnviarVelocidad" type="button" class="btn btn-success input-lg"><span style="font-size: large;" >Enviar</span></button>
            </div>
        </div>
        <div class="row IntensityConfig panelAccion" style="display: none;">
            <div class="col-lg-12">
                <p style="font-size: large;">Elegir la intensidad del led.</p>
            </div>
        </div>
        <div class="row IntensityConfig panelAccion" style="display: none;">
            <div class="col-lg-1" style="padding-top: 10;">
                <label for="intensidad" style="font-size: large;">Menos</label>
            </div>
            <div class="col-lg-4" style="padding-top: 14;">
                <input type="range" id="intensidad" min="1" max="15" value="2" />
            </div>
            <div class="col-lg-1" style="padding-top: 10;">
                <label for="intensidad" style="font-size: large;"> Más </label>
            </div>
            <div class="col-lg-4">
                <button id="btnEnviarIntensidad" type="button" class="btn btn-success input-lg"><span style="font-size: large;" >Enviar</span></button>
            </div>
        </div>
        <div class="row WaitTimeConfig panelAccion" style="display: none;">
            <div class="col-lg-12">
                <p style="font-size: large;">Elegir el timepo de espera.</p>
            </div>
        </div>
        <div class="row WaitTimeConfig panelAccion" style="display: none;">
            <div class="col-lg-1" style="padding-top: 10;">
                <label for="horasEspera" style="font-size: large;">Horas </label>
            </div>
            <div class="col-lg-1">
                <input type="number" id="horasEspera" value="0" max="99" min="0" class="form-control  input-lg">
            </div>
            <div class="col-lg-1" style="padding-top: 10;">
                <label for="minutosEspera" style="font-size: large;">Minutos </label>
            </div>
            <div class="col-lg-1">
                <input type="number" id="minutosEspera" value="0" max="59" min="0" class="form-control input-lg">
            </div>
            <div class="col-lg-1" style="padding-top: 10;">
                <label for="segundosEspera" style="font-size: large;">Segundos </label>
            </div>
            <div class="col-lg-1">
                <input type="number" id="segundosEspera" value="0" max="59" min="0" class="form-control input-lg">
            </div>
            <div class="col-lg-4">
                <button id="btnEnviarTiempoEspera" type="button" class="btn btn-success input-lg"><span style="font-size: large;" >Enviar</span></button>
            </div>
        </div>
    </div>
    <script>
        $('#texto').on('keypress',function(e) {
            if(e.which == 13) {
                $('#btnEnviar').click();
            }
        });

        $('#btnEnviar').bind("click", function(){
            window.location.href = "/Escribir?Texto=" + $('#texto').val();
        });

        $('.botonCambioHora').bind("click", function(){
            window.location.href = "/MostrarHora";
        });

        $('.botonCambioHoraScroll').bind("click", function(){
            window.location.href = "/CambioTipoHora";
        });

        $('#ScrollButton').bind("click", function(){
            window.location.href = "/CambioScrollTexto";
        });

        $('#cambioTiempo').bind("click", function(){
            $('.botonCambio').show();
            $('#cambioTiempo').hide();
            $('.panelAccion').hide();
            $('.timeConfig').show();
        });

        $('#cambioTexto').bind("click", function(){
            $('.botonCambio').show();
            $('#cambioTexto').hide();
            $('.panelAccion').hide();
            $('.writeText').show();
            $("#texto").focus();
        });

        $('#cambioVelocidad').bind("click", function(){
            $('.botonCambio').show();
            $('#cambioVelocidad').hide();
            $('.panelAccion').hide();
            $('.VelocityConfig').show();
        });

        $('#cambioIntensidad').bind("click", function(){
            $('.botonCambio').show();
            $('#cambioIntensidad').hide();
            $('.panelAccion').hide();
            $('.IntensityConfig').show();
        });

        $('#cambioTiempoEspera').bind("click", function(){
            $('.botonCambio').show();
            $('#cambioTiempoEspera').hide();
            $('.panelAccion').hide();
            $('.WaitTimeConfig').show();
        });

        $('#btnEnviarTiempo').bind("click", function(){
            var horas = $('#horas').val();
            var minutos = $('#minutos').val();
            var segundos = $('#segundos').val();
            window.location.href = "/Tiempo?h=" + horas + "&m=" + minutos + "&s=" + segundos;
        });

        $('#btnEnviarVelocidad').bind("click", function(){
            window.location.href = "/Velocidad?Velocidad=" + $('#velocidad').val();
        });

        $('#btnEnviarIntensidad').bind("click", function(){
            window.location.href = "/Intensidad?Intensidad=" + $('#intensidad').val();
        });

        $('#btnEnviarTiempoEspera').bind("click", function(){
            var horas = $('#horasEspera').val();
            var minutos = $('#minutosEspera').val();
            var segundos = $('#segundosEspera').val();
            window.location.href = "/TiempoEspera?h=" + horas + "&m=" + minutos + "&s=" + segundos;
        });

        $("#texto").focus();
    </script>
</body>
</html>


)=====";
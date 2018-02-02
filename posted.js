        var Firebase = require('firebase');
        
        var bdDate = new Date()
        var year = bdDate.getFullYear();
        var month = bdDate.getMonth();
        var day = bdDate.getDate();
        var hour = bdDate.getHours();
        
        var myRootRef=new Firebase( 'https://glowing-fire-8205.firebaseio.com/raspberry-rm5/' + year + month + day + hour );

        var humi = process.argv[3];
        var hour = process.argv[5];
        var date = process.argv[4];
        var temp = process.argv[2];
        myRootRef.push({name: "raspberry RM5", mensaje: "todo ok", fecha: date, temperatura: temp, humedad: humi, hora: hour});
        console.log(process.argv);
        myRootRef.on('child_added', closeconnection);
        function closeconnection(message){
                var humisaved = message.humedad;
                var tempsaved = message.temperatura;
                process.exit(1);
        }
	

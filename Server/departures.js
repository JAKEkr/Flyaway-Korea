//Departures
require('dotenv').config()
const convert = require('xml2json');
const fs=require('fs');
const cron=require('node-cron')
var Request = require("request");
var options = {object: false,
    reversible: false,
    coerce: false,
    sanitize: true,
    trim: true,
    arrayNotation: false,
    alternateTextNode: false};


Request.get("http://openapi.airport.kr/openapi/service/StatusOfPassengerFlights/getPassengerDepartures?ServiceKey=K3POVg15ZxYOa9zrxuVXDEuHy6bi8AZ9jcKR7QalKz2m7ZBBBv4wDYqIXuEy39oHLHo5rmWozqgEzVkSyK%2By2g%3D%3D", (error, response, body) => {
    if(error) {
        return console.dir(error);
    }
        cron.schedule('30 * * * * *',function(){

            fs.writeFile("C:/Users/USER/Flyaway-Korea/Server/departuresJson.txt",(convert.toJson(body, options)), function(err) {
                if(err) {
                return console.log(err);
            }
            console.log("Departures updated after 30s");
        });
    }); 
});
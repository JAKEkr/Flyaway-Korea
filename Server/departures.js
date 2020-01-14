//Departures
require('dotenv').config()
const convert = require('xml-js');
const fs=require('fs');
//var xml = fs.readFileSync('test.xml');
// var options = {compact:true , ignoreComment:true, spaces: 4};
var options = {compact:true , ignoreComment:true, spaces: 4,textKey: null, attributesKey: '$', commentKey: 'value'};

//var result=convert.xml2json(body, options);
const cron=require('node-cron')

const Agenda = require('agenda');
var Request = require("request");
Request.get("http://openapi.airport.kr/openapi/service/StatusOfPassengerFlights/getPassengerDepartures?ServiceKey=K3POVg15ZxYOa9zrxuVXDEuHy6bi8AZ9jcKR7QalKz2m7ZBBBv4wDYqIXuEy39oHLHo5rmWozqgEzVkSyK%2By2g%3D%3D", (error, response, body) => {
    if(error) {
        return console.dir(error);
    }
        cron.schedule('30 * * * * *',function(){
            console.log('running test after 30s');

            fs.writeFile("C:/Users/USER/Flyaway-Korea/Server/departuresJson.txt",(convert.xml2json(body, options)), function(err) {
                if(err) {
                return console.log(err);
            }
            console.log("The file was saved!");
        });
    }); 
});
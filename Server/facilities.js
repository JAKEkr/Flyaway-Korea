//Facilities
require('dotenv').config()
const convert = require('xml2json');
const fs=require('fs');
var options = {object: false,
    reversible: false,
    coerce: false,
    sanitize: true,
    trim: true,
    arrayNotation: false,
    alternateTextNode: false};
var Request = require("request");

Request.get("http://openapi.airport.kr/openapi/service/FacilitiesInformation/getFacilitesInfo?ServiceKey=K3POVg15ZxYOa9zrxuVXDEuHy6bi8AZ9jcKR7QalKz2m7ZBBBv4wDYqIXuEy39oHLHo5rmWozqgEzVkSyK%2By2g%3D%3D", (error, response, body) => {
    if(error) {
        return console.dir(error);
    }

    fs.writeFile("C:/Users/USER/Flyaway-Korea/Server/facilitiesJson.txt",(convert.toJson(body, options)), function(err) {
        if(err) {
            return console.log(err);
        }
        console.log("Facilities");
    });

});

require('dotenv').config();

const cron = require('node-cron');
const converter = require('xml2json');
const request = require("request");

const Facility = require('../models/facility');
const Arrival = require('../models/schedule/arrival');
const Departure = require('../models/schedule/departure');
const Parkinglot = require('../models/parkinglot');

const arrival_url = "http://openapi.airport.kr/openapi/service/StatusOfPassengerFlights/getPassengerArrivals?ServiceKey=";
const departure_url = "http://openapi.airport.kr/openapi/service/StatusOfPassengerFlights/getPassengerDepartures?ServiceKey=";
const facility_url = "http://openapi.airport.kr/openapi/service/FacilitiesInformation/getFacilitesInfo?numOfRows=500&ServiceKey=";
const parkinglot_url = "http://openapi.airport.kr/openapi/service/StatusOfParking/getTrackingParking?numOfRows=20&ServiceKey=";

var options = {
    object: true,
    reversible: false,
    coerce: false,
    sanitize: true,
    trim: true,
    arrayNotation: false,
    alternateTextNode: false
};

module.exports.start = async () => {
    await getData(facility_url, Facility);

    cron.schedule('30 * * * * *', () => {
        getData(departure_url, Departure);
        getData(arrival_url, Arrival);
        getData(parkinglot_url, Parkinglot);

        console.log('Data updated after 30s');
    });
};

function getData(url, model) {
    request.get(url + process.env.SERVICE_KEY, async (err, res, body) => {
        const data = await converter.toJson(body, options);

        await model.deleteMany({})
            .then(() => model.create(data.response.body.items.item))
            .catch(err => console.log(err));
    });
}

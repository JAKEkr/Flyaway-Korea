"use strict";

const router = require('express').Router();
const Arrival = require('../models/schedule/arrival');
const Departure = require('../models/schedule/departure');

router.get('/arrivals', function(req, res) {
    Arrival.find()
        .then(arrival => res.send({success: true, type: "arrival", arrival}))
        .catch(error => res.send({success: false, error}));
});

router.get('/departures', function(req, res) {
    Departure.find()
        .then(departure => res.send({success: true, type: "departure", departure}))
        .catch(error => res.send({success: false, error}));
});

module.exports = router;
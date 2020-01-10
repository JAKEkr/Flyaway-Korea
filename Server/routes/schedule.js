"use strict";

const router = require('express').Router();
const Arrival = require('../models/schedule/arrival');
const Departure = require('../models/schedule/departure');

router.get('/arrivals', function(req, res) {
    Arrival.find()
        .then(schedules => res.send({success: true, schedules}))
        .catch(error => res.send({success: false, error}));
});

router.get('/departures', function(req, res) {
    Departure.find()
        .then(schedules => res.send({success: true, schedules}))
        .catch(error => res.send({success: false, error}));
});

module.exports = router;
"use strict";

const router = require('express').Router();
const Parkinglot = require('../models/parkinglot');

router.get('/', function(req, res) {
    Parkinglot.find()
        .then(parkinglot => res.send({success: true, parkinglot}))
        .catch(error => res.send({success: false, error}));
});

module.exports = router;
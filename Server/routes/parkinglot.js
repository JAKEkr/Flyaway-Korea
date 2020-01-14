"use strict";

const router = require('express').Router();
const Parkinglot = require('../models/parkinglot');

router.get('/:terminal', function(req, res) {
    const terminal = new RegExp(req.params.terminal);
    Parkinglot.find({floor: terminal})
        .then(parkinglot => res.send({success: true, type: "parkinglot", parkinglot}))
        .catch(error => res.send({success: false, error}));
});

module.exports = router;
"use strict";

const router = require('express').Router();
const Facility = require('../models/facility');

router.get('/:keyword', function(req, res) {
    const keyword = new RegExp(req.params.keyword);
    Facility.find({$or: [{facilitynm: keyword}, {facilityitem: keyword}, {mcategorynm: keyword}, {lcategorynm: keyword}]})
        .then(facility => res.send({success: true, type: "facility", facility}))
        .catch(error => res.send({success: false, error}));
});

module.exports = router;
"use strict";

const mongoose = require('mongoose');

// Define user schema
const ParkinglotSchema = new mongoose.Schema({
    floor: {type: String, trim: true},          // 주차장 구분
    parking: {type: String, trim: true},        // 주차구역 주차수
    parkingarea: {type: String, trim: true},    // 주차구역 총 주차면수
    datetm: {type: String, trim: true}          // 주차 현황 시간
});

// Create Model & Export
module.exports = mongoose.model('Parkinglot', ParkinglotSchema);
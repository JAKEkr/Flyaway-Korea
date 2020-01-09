"use strict";

const mongoose = require('mongoose');

// Define user schema
const DepartureSchema = [new mongoose.Schema({
    airline: {type: String, trim: true, required: true},    // 항공사
    flightId: {type: String, trim: true},                   // 편명
    scheduleDateTime: {type: String, trim: true},           // 예정시간
    estimatedDateTime: {type: String, trim: true},          // 변경시간
    airport: {type: String, trim: true, required: true},    // 도착지공항
    gatenumber: {type: String, trim: true},                 // 탑승구
    remark: {type: String, trim: true},                     // 현황
    airportCode: {type: String, trim: true},                // 도착지공항코드
    cityCode: {type: String, trim: true},                   // 도착지국가코드
    terminalId: {type: String, trim: true}                  // 터미널
})]; // array list schema

// Create new user document
DepartureSchema.statics.create = function(payload) {
    // this === Model
    let user = new this(payload);
    return user.save();
};

// Create Model & Export
module.exports = mongoose.model('Departure', DepartureSchema);
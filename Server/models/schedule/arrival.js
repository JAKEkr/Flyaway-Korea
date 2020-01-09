"use strict";

const mongoose = require('mongoose');

// Define user schema
const ArrivalSchema = [new mongoose.Schema({
    airline: {type: String, trim: true, required: true},    // 항공사
    flightId: {type: String, trim: true},                   // 편명
    scheduleDateTime: {type: String, trim: true},           // 예정시간
    estimatedDateTime: {type: String, trim: true},          // 변경시간
    airport: {type: String, trim: true, required: true},    // 출발공항
    gatenumber: {type: String, trim: true},                 // 탑승구
    carousel: {type: String, trim: true},                   // 수하물수취대
    exitnumber: {type: String, trim: true},                 // 출구
    remark: {type: String, trim: true},                     // 현황
    airportCode: {type: String, trim: true},                // 출발공항코드
    terminalId: {type: String, trim: true},                 // 터미널
    elapsetime: {type: String, trim: true},                 // 소요시간
    cityCode: {type: String, trim: true}                    // 출발국가코드
})]; // array list schema

// Create new user document
ArrivalSchema.statics.create = function(payload) {
    // this === Model
    let user = new this(payload);
    return user.save();
};

// Create Model & Export
module.exports = mongoose.model('Arrival', ArrivalSchema);
"use strict";

const mongoose = require('mongoose');

// Define user schema
const FacilitySchema = new mongoose.Schema({
    sn: {type: String, trim: true},             // 시설번호
    arrordep: {type: String, trim: true},       // 입/출국 구분
    facilityitem: {type: String, trim: true},   // 품목
    facilitynm: {type: String, trim: true},     // 시설명
    lcnm: {type: String, trim: true},           // 위치
    lcategorynm: {type: String, trim: true},    // 대분류
    mcategorynm: {type: String, trim: true},    // 중분류
    scategorynm: {type: String, trim: true},    // 소분류
    servicetime: {type: String, trim: true},    // 서비스 시간
    lcduty: {type: String, trim: true},         // 지역구분
    terminalid: {type: String, trim: true},     // 터미널구분
    floorinfo: {type: String, trim: true},      // 층구분
    tel: {type: String, trim: true}             // 전화번호
});

// Create Model & Export
module.exports = mongoose.model('Facility', FacilitySchema);
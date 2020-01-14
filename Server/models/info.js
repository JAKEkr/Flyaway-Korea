const mongoose=require('mongoose')

const parkinglotSchema=new mongoose.Schema({           
    floor: {
        type: String, 
        trim: true, 
        required: true
    }, 
    parking: {
        type: String, 
        trim: true, 
        required: true
    },
    parkingarea:{
        type: String, 
        trim: true, 
        required: true
    }
});

module.exports=mongoose.model('Parking Lot',parkinglotSchema)
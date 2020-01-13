const express=require('express')
const router=express.Router()
const parkinginfo=require('../models/info')

//all parking
router.get('/parking/:id', getparkinglot ,async (req,res)=>{
    try{
        // res.send(res.info)
        const parkinglot=await parkinginfo.find()
        res.info
        res.json(parkinglot)
    }catch{
        res.status(500).json({message:err.message})
    }
})

//one airport code
router.get('/:id',getparkinglot,(req,res)=>{
    res.send(res.info)
})

async function getparkinglot(req,res,next){
    let info
    try{
        info=await parkinginfo.findById(req.params.id)
        if(info=null){
            return res.status(401).json({message:'None'})
        }
    }catch(err){
        return res.status(500).json({message:err.message})
    }
    res.info=info
    next()

}

module.exports=router
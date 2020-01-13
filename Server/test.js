require('dotenv').config()

const express=require('express')
const app=express();
const mongoose=require('mongoose',{})

const cron=require('node-cron')

cron.schedule('* * * * * *',function(){
  console.log('running test after 1s');
}); 

// mongoose.connect(process.env.DATABASE_URL, { useNewUrlParser: true, useUnifiedTopology:true })

// const db=mongoose.connection

// db.on('error',(error)=>console.error(error))
// db.once('open',()=>console.log('Connected to Database'))

// app.use(express.json())

// const infoRouter= require('./routes/info')
// app.use('/info',infoRouter)


// app.listen(3000,()=> console.log('Server Started'))







//mongodb://27.96.135.10:27017


































// /**
//  * Changes XML to JSON
//  * Modified version from here: http://davidwalsh.name/convert-xml-json
//  * @param {string} xml XML DOM tree
//  */
// function xmlToJson(xml) {
//     // Create the return object
//     const response = fetch('http://openapi.airport.kr/openapi/service/StatusOfParking/getTrackingParking?ServiceKey=K3POVg15ZxYOa9zrxuVXDEuHy6bi8AZ9jcKR7QalKz2m7ZBBBv4wDYqIXuEy39oHLHo5rmWozqgEzVkSyK%2By2g%3D%3D');
    
//     const xmlString = response.text();
//     var XmlNode = new DOMParser().parseFromString(xmlString, 'text/xml');

//     var obj = {};
  
//     if (xml.nodeType == 1) {
//       // element
//       // do attributes
//       if (xml.attributes.length > 0) {
//         obj["@attributes"] = {};
//         for (var j = 0; j < xml.attributes.length; j++) {
//           var attribute = xml.attributes.item(j);
//           obj["@attributes"][attribute.nodeName] = attribute.nodeValue;
//         }
//       }
//     } else if (xml.nodeType == 3) {
//       // text
//       obj = xml.nodeValue;
//     }
  
//     // do children
//     // If all text nodes inside, get concatenated text from them.
//     var textNodes = [].slice.call(xml.childNodes).filter(function(node) {
//       return node.nodeType === 3;
//     });
//     if (xml.hasChildNodes() && xml.childNodes.length === textNodes.length) {
//       obj = [].slice.call(xml.childNodes).reduce(function(text, node) {
//         return text + node.nodeValue;
//       }, "");
//     } else if (xml.hasChildNodes()) {
//       for (var i = 0; i < xml.childNodes.length; i++) {
//         var item = xml.childNodes.item(i);
//         var nodeName = item.nodeName;
//         if (typeof obj[nodeName] == "text/xml") {
//           obj[nodeName] = xmlToJson(item);
//         } else {
//           if (typeof obj[nodeName].push == "undefined") {
//             var old = obj[nodeName];
//             obj[nodeName] = [];
//             obj[nodeName].push(old);
//           }
//           obj[nodeName].push(xmlToJson(item));
//         }
//       }
//     }
//     return obj;
//   }
  
//   /*
//   Usage:
//   1. If you have an XML file URL:
//   const response = await fetch('file_url');
//   const xmlString = await response.text();
//   var XmlNode = new DOMParser().parseFromString(xmlString, 'text/xml');
//   xmlToJson(XmlNode);
//   2. If you have an XML as string:
//   var XmlNode = new DOMParser().parseFromString(yourXmlString, 'text/xml');
//   xmlToJson(XmlNode);
//   3. If you have the XML as a DOM Node:
//   xmlToJson(YourXmlNode);
//   */
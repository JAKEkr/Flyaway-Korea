require('dotenv').config();

const express = require('express');
const http = require('http');
const winston = require('./config/winston');
const morgan = require('morgan');
const mongoose = require('mongoose');
const scheduleRoute = require('./routes/schedule');
const facilityRoute = require('./routes/facility_info');
const parkinglotRoute = require('./routes/parkinglot');

const app = express();

app.use(express.json()); // Json parser
app.use(morgan('combined', {stream: winston.stream}));
app.use('/schedule', scheduleRoute);
app.use('/facility_info', facilityRoute);
app.use('/parkinglot', parkinglotRoute);

mongoose.Promise = global.Promise;
mongoose.set('useNewUrlParser', true);
mongoose.set('useFindAndModify', false);
mongoose.set('useCreateIndex', true);
mongoose.set('useUnifiedTopology', true);
mongoose.connect(process.env.MONGO_URI)
    .then(console.log('Successfully connected to mongodb'))
    .catch(error => console.error(error));

// Set TCP port
const port = process.env.PORT || '8888';
app.set('port', port);

// Set server
const server = http.createServer(app);

server.listen(port);
server.on('error', onError);
server.on('listening', onListening);

function onError(error) {
    if (error.syscall !== 'listen')
        throw error;

    const bind = typeof port === 'string'
        ? 'Pipe ' + port
        : 'Port ' + port;

    // handle specific listen errors with friendly messages
    switch (error.code) {
        case 'EACCES':
            winston.info(bind + ' requires elevated privileges');
            process.exit(1);
            break;
        case 'EADDRINUSE':
            winston.info(bind + ' is already in use');
            process.exit(1);
            break;
        default:
            throw error;
    }
} // onError()

function onListening() {
    const addr = server.address();
    const bind = typeof addr === 'string'
        ? 'pipe ' + addr
        : 'port ' + addr.port;
    winston.info('Listening on ' + bind);
} // onListening()

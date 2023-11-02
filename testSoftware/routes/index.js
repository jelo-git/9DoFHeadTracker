const express = require('express');
const router = express.Router();
const { SerialPort } = require('serialport');

//set up the routes
router.get('/', (req, res) => {
    res.render('index', { title: '9 Degrees of Freedom Sandbox', ports: ports });
});

router.post('/serials', (req, res) => {
    SerialPort.list().then((ports) => {
        res.json(ports);
    });
});

module.exports = router;
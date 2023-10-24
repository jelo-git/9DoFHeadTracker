const express = require('express');
const router = express.Router();


//set up the routes
router.get('/', (req, res) => {
    res.render('index', { title: '9 Degrees of Freedom Sandbox' });
});

module.exports = router;
//basic local server set up
const express = require('express');
const app = express();
const port = 3000;
const path = require('path');

//set up the server to serve static files
app.use(express.static(path.join(__dirname, 'public')));

//set up the view engine
app.set('view engine', 'ejs');

//set up routes
app.use('/', require(path.join(__dirname, 'routes', 'index.js')));

//set up 404 page
app.all('*', (req, res) => {
    res.status(404);
    switch (req.accepts(['html', 'json'])) {
        case 'html':
            res.render('404', { url: req.url });
            break;
        case 'json':
            res.json({ success: false, error: 'Not Found' });
            break;
        default:
            res.send('Not Found');
            break;
    }
});

//start the server
app.listen(port, () => {
    console.log(`Testing app available at http://localhost:${port}`);
});
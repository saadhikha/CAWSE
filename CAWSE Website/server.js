//Start server
const { response } = require('express')
const express = require('express')
const app = express()
const server = require('http').createServer(app)
const io = require('socket.io')(server)

const port = process.env.PORT || 3000
server.listen(port, () => {
    console.log(`Express server listening on port ${port}`)
})

//Connect datatbase to server
const { Client } = require('pg')
const { isObject } = require('util')
const client = new Client ({
    user: 'postgres',
    password: 'Rajashri@11',
    host: 'localhost',
    database: 'medigo',
    port: 5432,
})
client.connect(function(err) {
    if (err) throw err;
    console.log("Postgres connected!");
});

//Display database data there - For testing - Working fine
/*app.get("/", function(req, response){    
	client
        .query('SELECT * from  hospitals')
        .then(res => {
                console.log(JSON.stringify(res.rows))
                return response.send(res.rows)
            })
        .catch(e => console.error(e.stack))
});*/

//Serve the home page in the web
//app.use('/', express.static('MEDI-GO_08-10-21/MEDI-GO/MEDI-GO'))
app.use('/', express.static('Beckn_io'))

//Variables
var sockets = [];

io.on('connection', (socket) => {
    console.log('Socket connected successfully');
    socket.on('emergency', function(request) {
        client
            .query('select name, contact from ambulances where location=$1 and servicing=$2', 
                [request, false])
            .then(res => {
                    console.log(JSON.stringify(res.rows))
                    socket.emit('returning_result', res.rows)
                })
            .catch(e => console.error(e.stack))
    });
    socket.on('search_review', function(city, hospital) {
        client
            .query('select content from reviews where city=$1 and hospital_id=(select id from hospitals where name=$2)',
                [city, hospital])
            .then(res => {
                console.log(JSON.stringify(res.rows))
                socket.emit('returning_result', res.rows)
                })
            .catch(e => console.error(e.stack))
    });
    socket.on('leave_review', function(city, hospital, content) {
        client
            .query('insert into reviews values((select max(id)+1 from reviews), $1, (select id from hospitals where name=$2), $3)',
                [city, hospital, content])
            .then(res => {
                console.log(JSON.stringify(res.rows))
                })
            .catch(e => console.error(e.stack))
    });
    socket.on('review_ambulance', function(city, hospital, content) {
        client
            .query('insert into ambulance_reviews values((select max(id)+1 from ambulance_reviews), $1, (select id from ambulances where name=$2), $3)',
                [city, hospital, content])
            .then(res => {
                console.log(JSON.stringify(res.rows))
                })
            .catch(e => console.error(e.stack))
    });
    socket.on('hospital_beds', function(request) {
        client
            .query('select name, category, beds_available, beds_available_icu, beds_available_normal, beds_available_ventilation from hospitals where location=$1', 
                [request])
            .then(res => {
                    console.log(JSON.stringify(res.rows))
                    socket.emit('returning_result', res.rows)
                })
            .catch(e => console.error(e.stack))
    });
    socket.on('blood_availability', function(state, blood_group) {
        var type;
        if(blood_group=='A+') type = 1
        else if(blood_group=='A-') type = 2
        else if(blood_group=='B+') type = 3
        else if(blood_group=='B-') type = 4
        else if(blood_group=='AB+') type = 5
        else if(blood_group=='AB+') type = 6
        else if(blood_group=='O+') type = 7
        else if(blood_group=='O-') type = 8
        client
            .query('select name, location, blood_groups[$1] from blood_banks where location = $2',
                [type, state])
            .then(res => {
                console.log(JSON.stringify(res.rows))
                socket.emit('returning_result', res.rows)
                })
            .catch(e => console.error(e.stack))
    });
    socket.on('signing_up', function(firstname, lastname, gender, address, phonenumber, password) {
        client
            .query('insert into users values($1, $2, $3, $4, $5, %6)', 
                [firstname, lastname, gender, address, phonenumber, password])
            .then(res => {
                console.log(JSON.stringify(res.rows))
                })
            .catch(e => console.error(e.stack))
    });
    socket.on('doctors_availability', function(location, specialisation) {
        client
            .query('select d.name as name, d.contact, d.age, h.name as hospital_name, h.category as hospital_category from doctors d, hospitals h where h.id = d.hospital_id and d.specialisation=$2 and h.location = $1;',
                [location, specialisation])
            .then(res => {
                console.log(JSON.stringify(res.rows))
                socket.emit('returning_result', res.rows)
                })
            .catch(e => console.error(e.stack))
    });
    socket.on('schedule_blood_donation', function(firstname, lastname, gender, address, phonenumber, blood_group, medical_history, date) {
        client
            .query('insert into blood_donors values((select max(id)+1 from blood_donors), $1, $2, $3, $4, $5, $6, $7, $8)', 
                [firstname, lastname, gender, address, phonenumber, blood_group, medical_history, date])
            .then(res => {
                console.log(JSON.stringify(res.rows))
                })
            .catch(e => console.error(e.stack))
    });
})
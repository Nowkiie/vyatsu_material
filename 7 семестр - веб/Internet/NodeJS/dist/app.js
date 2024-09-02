"use strict";
let dataw = "Проверка 1";
let datar = "Проверка 2";
let datau = "Проверка 3";
/* ----------soket----------*/
const http = require("http");
const qs = require("qs");
const WebSocket_ = require("ws");
// import {database} from "../dist/pgdatabase.js";
const database = require("../dist/pgdatabase.js");
const db_ = database;
const wsServer = new WebSocket_.Server({ port: 8081 });
const users = [];
// подключение
wsServer.on("connection", function w(ws) {
    // подключение пользователя
    const user = { connection: ws };
    users.push(user);
    // Получаем сообщение от клиента
    ws.on("message", function m(message) {
        const soketdatamessage = qs.parse(message.toString());
        // отправка сообщения
        if (soketdatamessage.id === "autorization")
            db_.autorization_db(users, soketdatamessage);
        if (soketdatamessage.id === "home")
            db_.home_db(users, soketdatamessage);
        if (soketdatamessage.id === "drivers")
            db_.drivers_db(users, soketdatamessage);
        /* if (soket_datamessage.id == "new_person")
              db_.newperson_db(users, soket_datamessage);*/
        if (soketdatamessage.id === "adminapplication")
            db_.adminapplication_db(users);
        if (soketdatamessage.id === "changework")
            db_.chapplication_db(users, soketdatamessage.el);
        if (soketdatamessage.id === "adminreport")
            db_.adminreport_db(users);
        if (soketdatamessage.id === "changereport")
            db_.chreport_db(users, soketdatamessage.el);
        if (soketdatamessage.id === "adminuser")
            db_.adminuser_db(users);
        if (soketdatamessage.id === "admin") {
            db_.adminapplication_db(users);
            db_.adminreport_db(users);
            db_.adminuser_db(users);
        }
        if (soketdatamessage.id === "w1")
            dataw = soketdatamessage.data;
        if (soketdatamessage.id === "r1")
            datar = soketdatamessage.data;
        if (soketdatamessage.id === "u1")
            datau = soketdatamessage.data;
    });
    // выход пользователя
    ws.on("close", function c() {
        const id = users.indexOf(user);
        users.splice(id, 1);
    });
});
/* ----------/soket----------*/
const server = http.createServer((req, res) => {
    /* ----------ejs----------*/
    const ejs = require("ejs");
    const filename = "C://Una/Internet/NodeJS/dinamic/admin_page.ejs";
    ejs.renderFile(filename, {
        work: dataw,
        report: datar,
        user: datau,
    }, function e(err, data) {
        res.end(data);
    });
    /* ----------/ejs----------*/
    /* const urlPath = req.url;
    if (urlPath === "/overview") {
      res.end('Welcome to the "overview page" of the nginX project');
    } else if (urlPath === "/api") {
      res.writeHead(200, { "Content-Type": "application/json" });
      res.end(
        JSON.stringify({
          product_id: "xyz12u3",
          product_name: "NginX injector",
        })
      );
    } else {
      res.end("Successfully started a server");
    }*/
});
server.listen(3001, "localhost", () => {
    console.log("Listening for request");
});
